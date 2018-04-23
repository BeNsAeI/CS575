#include <omp.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "color.h"
#include "OMPUtil.h"
#include "const.h"

float Height( int iu, int iv, int NUMNODES)
{
	float u = (float)iu / (float)(NUMNODES-1);
	float v = (float)iv / (float)(NUMNODES-1);

	float bu0 = (1.-u) * (1.-u) * (1.-u);
	float bu1 = 3. * u * (1.-u) * (1.-u);
	float bu2 = 3. * u * u * (1.-u);
	float bu3 = u * u * u;

	float bv0 = (1.-v) * (1.-v) * (1.-v);
	float bv1 = 3. * v * (1.-v) * (1.-v);
	float bv2 = 3. * v * v * (1.-v);
	float bv3 = v * v * v;

        float top = bu0 * ( bv0*TOPZ00 + bv1*TOPZ01 + bv2*TOPZ02 + bv3*TOPZ03 )
		  + bu1 * ( bv0*TOPZ10 + bv1*TOPZ11 + bv2*TOPZ12 + bv3*TOPZ13 )
		  + bu2 * ( bv0*TOPZ20 + bv1*TOPZ21 + bv2*TOPZ22 + bv3*TOPZ23 )
		  + bu3 * ( bv0*TOPZ30 + bv1*TOPZ31 + bv2*TOPZ32 + bv3*TOPZ33 );

        float bot = bu0 * ( bv0*BOTZ00 + bv1*BOTZ01 + bv2*BOTZ02 + bv3*BOTZ03 )
		  + bu1 * ( bv0*BOTZ10 + bv1*BOTZ11 + bv2*BOTZ12 + bv3*BOTZ13 )
		  + bu2 * ( bv0*BOTZ20 + bv1*BOTZ21 + bv2*BOTZ22 + bv3*BOTZ23 )
		  + bu3 * ( bv0*BOTZ30 + bv1*BOTZ31 + bv2*BOTZ32 + bv3*BOTZ33 );

        return top - bot;
}

int main( int argc, char ** argv )
{
	int numThreads = 1;
	int NUMNODES = 1;
	bool supress = false;
	if (argc > 1)
		numThreads = atoi(argv[1]);
	if(argc > 2)
		NUMNODES = atoi(argv[2]);
	if (argc > 3)
		supress = true;
	if (DEBUG && !supress)
		printf(ANSI_COLOR_YELLOW "Initializing the Utility tools\n" ANSI_COLOR_RESET);

	Utility myUtil;
	if(!supress)
		myUtil.isOpenMP(DEBUG && !supress);

	omp_set_num_threads( numThreads );
	if(!supress)
		fprintf( stderr, "Using " ANSI_COLOR_CYAN "%d" ANSI_COLOR_RESET " threads\n", numThreads );

	

	float fullTileArea = (((XMAX - XMIN)/(float)(NUMNODES-1))*((YMAX - YMIN)/(float)(NUMNODES-1)))/4;

	double volume = 0;
	double pVolume = 0;
	myUtil.timerStart();
	#pragma omp parallel for collapse(2) reduction(+:volume),private(pVolume)
	for( int iv = 0; iv < NUMNODES; iv++ )
	{
		for( int iu = 0; iu < NUMNODES; iu++ )
		{
			pVolume = fullTileArea * Height(iu,iv,NUMNODES);
			volume = volume + pVolume;
			if(iv > 0 && iv + 1 < NUMNODES)
				pVolume *=2;
			if(iu > 0 && iu + 1 < NUMNODES)
				pVolume *=2;
			if(DEBUG && !supress)
				printf("Thread: %d computed: %#f.\n",omp_get_thread_num(),pVolume);
		}
	}
	myUtil.timerStop();
	if(!supress)
		printf(ANSI_COLOR_RED "Total Time was: "ANSI_COLOR_RESET);
	printf("%#f",myUtil.Time());
	if(!supress)
		printf(ANSI_COLOR_RED " seconds.\n" ANSI_COLOR_RESET);
	if(!supress)
		printf("Computed volume is " ANSI_COLOR_CYAN "%#f" ANSI_COLOR_RESET " units.\n" ,volume);
}
