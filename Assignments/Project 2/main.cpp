#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <math.h>
#include <omp.h>
#include "OMPUtil.h"
#include "color.h"

#define DEBUG 1
#define Q(x) #x
#define QUOTE(x) Q(x)

// constants:
const double G  = 6.67300e-11;   // m^3 / ( kg s^2 )
const double EARTH_MASS  = 5.9742e24;     // kg
const double EARTH_DIAMETER       = 12756000.32;   // meters
const double TIMESTEP    =   1.0; // secs

struct body
{
	float mass;
	float x, y, z;   // position
	float vx, vy, vz;// velocity
	float fx, fy, fz;// forces
	float xnew, ynew, znew;
	float vxnew, vynew, vznew;
};

typedef struct body Body;

// function prototypes:
float GetDistanceSquared( Body *, Body * );
float GetUnitVector( Body *, Body *, float *, float *, float * );
float Ranf( float, float );
int Ranf( int, int );

int main( int argc, char *argv[])
{
	int NUMBODIES = 100;
	int NUMSTEPS = 200;
	int NUMTHREADS = 1;
	bool supress = false;
	if (argc > 1)
		NUMTHREADS = atoi(argv[1]);
	if(argc > 2)
		NUMBODIES = atoi(argv[2]);
	if (argc > 3)
		NUMSTEPS = atoi(argv[3]);
	if (argc > 4)
		supress = true;
	if (DEBUG && !supress)
		printf(ANSI_COLOR_YELLOW "Initializing the Utility tools\n" ANSI_COLOR_RESET);

	Utility myUtil;
	omp_set_num_threads(NUMTHREADS);
	if(!supress)
	{
		printf(ANSI_COLOR_BLUE"\n=============== " ANSI_COLOR_YELLOW "INFORMATION" ANSI_COLOR_BLUE " ===============\n" ANSI_COLOR_RESET);
		myUtil.isOpenMP(DEBUG && !supress);
		printf( "Using " ANSI_COLOR_CYAN "%d" ANSI_COLOR_RESET
			" threads, " ANSI_COLOR_CYAN "%d" ANSI_COLOR_RESET
			" Bodies and " ANSI_COLOR_CYAN "%d" ANSI_COLOR_RESET
			" Steps. \n", NUMTHREADS,NUMBODIES,NUMSTEPS);
		printf("The scheduling type is " ANSI_COLOR_YELLOW "%s" ANSI_COLOR_RESET ".\n", QUOTE(PTYPE));
		#ifdef CG
			printf("Parallelism is " ANSI_COLOR_YELLOW "course " ANSI_COLOR_RESET "grain.\n");
		#endif
		#ifdef FG
			printf("Parallelism is " ANSI_COLOR_YELLOW "fine " ANSI_COLOR_RESET "grain.\n");
		#endif
		printf(ANSI_COLOR_BLUE "===========================================\n\n" ANSI_COLOR_RESET);
	}
	omp_set_num_threads(NUMTHREADS);
	int numProcessors = omp_get_num_procs( );

	Body Bodies[NUMBODIES];

	#pragma omp parallel for schedule(PTYPE, 1)
	for( int i = 0; i < NUMBODIES; i++ )
	{
		Bodies[i].mass = EARTH_MASS  * Ranf( 0.5f, 10.f );
		Bodies[i].x = EARTH_DIAMETER * Ranf( -100.f, 100.f );
		Bodies[i].y = EARTH_DIAMETER * Ranf( -100.f, 100.f );
		Bodies[i].z = EARTH_DIAMETER * Ranf( -100.f, 100.f );
		Bodies[i].vx = Ranf( -100.f, 100.f );;
		Bodies[i].vy = Ranf( -100.f, 100.f );;
		Bodies[i].vz = Ranf( -100.f, 100.f );;
	};
	myUtil.timerStart();
	double time0 = omp_get_wtime( );
	for( int t = 0; t < NUMSTEPS; t++ )
	{
		#ifdef CG
		#pragma omp parallel for schedule(PTYPE, 1)
		#endif
		for( int i = 0; i < NUMBODIES; i++ )
		{
			float fx = 0.;
			float fy = 0.;
			float fz = 0.;
			Body *bi = &Bodies[i];
			#ifdef FG
			#pragma omp parallel for schedule(PTYPE, 1),reduction(+:fx),reduction(+:fy),reduction(+:fz)
			#endif
			for( int j = 0; j < NUMBODIES; j++ )
			{
				if( j == i )
					continue;
				Body *bj = &Bodies[j];
				float rsqd = GetDistanceSquared( bi, bj );
				if( rsqd > 0. )
				{
					float f = G * bi->mass * bj->mass / rsqd;
					float ux, uy, uz;
					GetUnitVector( bi, bj,   &ux, &uy, &uz );
					fx += f * ux;
					fy += f * uy;
					fz += f * uz;
				}
			}
			float ax = fx / Bodies[i].mass;
			float ay = fy / Bodies[i].mass;
			float az = fz / Bodies[i].mass;
			Bodies[i].xnew = Bodies[i].x + Bodies[i].vx*TIMESTEP + 0.5*ax*TIMESTEP*TIMESTEP;
			Bodies[i].ynew = Bodies[i].y + Bodies[i].vy*TIMESTEP + 0.5*ay*TIMESTEP*TIMESTEP;
			Bodies[i].znew = Bodies[i].z + Bodies[i].vz*TIMESTEP + 0.5*az*TIMESTEP*TIMESTEP;
			Bodies[i].vxnew = Bodies[i].vx + ax*TIMESTEP;
			Bodies[i].vynew = Bodies[i].vy + ay*TIMESTEP;
			Bodies[i].vznew = Bodies[i].vz + az*TIMESTEP;
		}
		// setup the state for the next animation step:
		for( int i = 0; i < NUMBODIES; i++ )
		{
			Bodies[i].x = Bodies[i].xnew;
			Bodies[i].y = Bodies[i].ynew;
			Bodies[i].z = Bodies[i].znew;
			Bodies[i].vx = Bodies[i].vxnew;
			Bodies[i].vy = Bodies[i].vynew;
			Bodies[i].vz = Bodies[i].vznew;
		}
	}  //
	myUtil.timerStop();
	//double time1 = omp_get_wtime( );
	// print performance here:::
	if(!supress)
		printf("The process took ");
	printf("%#f",myUtil.Time());
	if(!supress)
		printf(" seconds.\n");
	if(!supress)
		printf(ANSI_COLOR_YELLOW "Done!\n" ANSI_COLOR_RESET);
	return 0;
}

float GetDistanceSquared( Body *bi, Body *bj )
{
	float dx = bi->x - bj->x;
	float dy = bi->y - bj->y;
	float dz = bi->z - bj->z;
	return dx*dx + dy*dy + dz*dz;
}

float GetUnitVector( Body *from, Body *to, float *ux, float *uy, float *uz )
{
	float dx = to->x - from->x;
	float dy = to->y - from->y;
	float dz = to->z - from->z;
	float d = sqrt( dx*dx + dy*dy + dz*dz );
	if( d > 0. )
	{
	dx /= d;
	dy /= d;
	dz /= d;
	}
	*ux = dx;
	*uy = dy;
	*uz = dz;
	return d;
}

float Ranf( float low, float high )
{
	float r = (float) rand();// 0 - RAND_MAX
	return(   low  +  r * ( high - low ) / (float)RAND_MAX   );
}

int Ranf( int ilow, int ihigh )
{
	float low = (float)ilow;
	float high = (float)ihigh + 0.9999f;
	return (int)(  Ranf(low,high) );
}
