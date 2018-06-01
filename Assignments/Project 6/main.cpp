#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <math.h>
#include <cmath>
#include <omp.h>
#include <time.h>
#include <algorithm>

#include "OMPUtil.h"
#include "color.h"
#include "const.h"

#define MAXDAYS  72 /*378*/

class Agent{
public:
	int GR; //GrothRate
	int DR; //DeathRate
	int Pop; //Population
	int tmpPop;
	bool isAlive();
	void Rep(); //Reproduce
};
void Agent::Rep()
{
	if(Pop > 1)
		Pop += std::min(std::max(GR,0),Pop/2);
	Pop -= std::max(DR,0);
	Pop = std::max(Pop,0);
}
bool Agent::isAlive()
{
	if(Pop > 0)
		return true;
	else
		return false;
}
Agent Grain;
Agent Deer;
Agent Wolf;
Agent Noah;
omp_lock_t GrainLock;
omp_lock_t DeerLock;
omp_lock_t WolfLock;

bool dayPass = false;
float NowTemp;
float NowPrecip;

float Ranf( float low, float high, unsigned int* seed )
{
	float r = (float) rand_r(seed);
	return( low + r * ( high - low ) / (float)RAND_MAX );
}
float CM(float inches)
{
	return inches * 2.54;
}
float Inches(float cm)
{
	return cm / 2.54 ;
}
float C(float f)
{
	return (5./9.)*(f-32);
}
float F(float c)
{
	return (c/(5.0/9.0)) + 32;
}
void pGrain()
{
	// reproduce
	int i = 0;
	Grain.tmpPop = Grain.Pop;
	for(i = 0; i < MAXDAYS;)
	{
		if (Grain.isAlive())
		{
			omp_set_lock(&GrainLock);
			Grain.Rep();
			omp_unset_lock(&GrainLock);
			if (Grain.tmpPop > Grain.Pop)
				printf( ANSI_COLOR_YELLOW "- Month %d: Dear Diary; Some of the grain was eaten by Noah and Deer(%d)(temp: %#f, precip: %#f).\n" ANSI_COLOR_RESET,i,Grain.Pop,NowTemp,NowPrecip);
			if (Grain.tmpPop < Grain.Pop)
				printf( ANSI_COLOR_CYAN "- Month %d: Dear Diary; Grain grew by %d amount.(%d)(temp: %#f, precip: %#f)\n"ANSI_COLOR_RESET, i, Grain.Pop - Grain.tmpPop,Grain.Pop,NowTemp,NowPrecip);
			Grain.tmpPop = Grain.Pop;
			Grain.GR = (25 + (int)NowTemp)*30;
			Grain.DR = 0;
		}
		#pragma omp barrier
		i++;
	}
	if(!Grain.isAlive())
	{
		printf( ANSI_COLOR_RED "- Month %d: Dear Diary; Noah ran out of Grain!\n"ANSI_COLOR_RESET, i);
	}
	std::cout << "Grain population:" << Grain.Pop << std:: endl;
	omp_unset_lock(&GrainLock);
	omp_unset_lock(&DeerLock);
	omp_unset_lock(&WolfLock);
}
void pDeer()
{
	int i = 0;
	Deer.tmpPop = Deer.Pop;
	for(i = 0; i < MAXDAYS;)
	{
		// reproduce
		if (i % 7 == 0 && Deer.isAlive())
		{
			omp_set_lock(&DeerLock);
			Deer.Rep();
			omp_unset_lock(&DeerLock);
			if (Deer.tmpPop > Deer.Pop)
				printf( ANSI_COLOR_YELLOW "- Month %d: Dear Diary; %d of the Deers got eaten or starved top death.(P: %d, GR:%d , DR:%d, Grain: %d )\n" ANSI_COLOR_RESET,i, Deer.tmpPop - Deer.Pop,Deer.Pop,Deer.GR,Deer.DR, Grain.Pop);printf( ANSI_COLOR_YELLOW "- Month %d: Dear Diary; %d of the Deers got eaten or starved top death.(P: %d, GR:%d , DR:%d, Grain: %d )\n" ANSI_COLOR_RESET,i, Deer.tmpPop - Deer.Pop,Deer.Pop,Deer.GR,Deer.DR, Grain.Pop);
			if (Deer.tmpPop < Deer.Pop)
				printf( ANSI_COLOR_CYAN "- Month %d: Dear Diary; Deer population grew by %d amount.(P: %d, GR:%d , DR:%d, Grain: %d )\n" ANSI_COLOR_RESET, i , Deer.Pop - Deer.tmpPop,Deer.Pop,Deer.GR,Deer.DR,Grain.Pop);
			if (Deer.tmpPop == Deer.Pop)
				printf( ANSI_COLOR_CYAN "- Month %d: Dear Diary; Deer population did not change.(P: %d, GR:%d , DR:%d, Grain: %d )\n" ANSI_COLOR_RESET, i ,Deer.Pop,Deer.GR,Deer.DR,Grain.Pop);
			Deer.tmpPop = Deer.Pop;
		}
		if(Deer.isAlive())
		{
			omp_set_lock(&GrainLock);
			Grain.Pop -= Deer.Pop * 3;
			omp_unset_lock(&GrainLock);
			Deer.GR = (Grain.Pop - Deer.Pop * 3 * 30)/90 - Deer.Pop - 1;
			Deer.DR = std::min(Deer.Pop - (Grain.Pop - Deer.Pop * 3 * 30)/21,Deer.Pop/2) + 1;
		}
		else
		{
			Deer.GR = 0;
			Deer.DR = 0;
			Deer.Pop = 0;
		}
		#pragma omp barrier
		i++;
	}
	if(!Deer.isAlive())
	{
		printf( ANSI_COLOR_RED "- Month %d: Dear Diary; All deers are dead.(GR: %d, DR: %d)\n"ANSI_COLOR_RESET,i,Deer.GR, Deer.DR);
	}
	for(int j = 0; j < 100000000; j++);
	std::cout << "Deer population:" << Deer.Pop << std:: endl;
	omp_unset_lock(&GrainLock);
	omp_unset_lock(&DeerLock);
	omp_unset_lock(&WolfLock);
}

void pWolf()
{
	int i = 0;
	Wolf.tmpPop = Wolf.Pop;
	for(i = 0; i < MAXDAYS;)
	{
		// reproduce
		if (i % 14 == 0 && Wolf.isAlive())
                {
			omp_set_lock(&WolfLock);
			Wolf.Rep();
			omp_unset_lock(&WolfLock);
			if (Wolf.tmpPop > Wolf.Pop)
				printf( ANSI_COLOR_YELLOW "- Month %d: Dear Diary; %d of the Wolves got eaten or starved top death.(P: %d, GR:%d , DR:%d, Deer: %d )\n" ANSI_COLOR_RESET,i, Wolf.tmpPop - Wolf.Pop,Wolf.Pop,Wolf.GR,Wolf.DR, Deer.Pop);
			if (Wolf.tmpPop < Wolf.Pop)
				printf( ANSI_COLOR_CYAN "- Month %d: Dear Diary; Wolf population grew by %d amount.(P: %d, GR:%d , DR:%d, Deer: %d )\n" ANSI_COLOR_RESET, i , Wolf.Pop - Wolf.tmpPop,Wolf.Pop,Wolf.GR,Wolf.DR,Deer.Pop);
			Wolf.tmpPop = Wolf.Pop;
		}
		// eat
		if (Wolf.isAlive())
		{
			omp_set_lock(&DeerLock);
			Deer.Pop -= 1;
			omp_unset_lock(&DeerLock);
		}
		if(Wolf.isAlive())
		{
			Wolf.GR = (Deer.Pop - Wolf.Pop/3) - 1;
			Wolf.DR = (Wolf.Pop - Deer.Pop*3) + 1;
		}
		else
		{
			Wolf.GR = 0;
			Wolf.DR = 0;
			Wolf.Pop = 0;
		}
		#pragma omp barrier
		i++;

	}
	if(!Wolf.isAlive())
		printf( ANSI_COLOR_RED "- Month %d: Dear Diary; All wolves are dead.(GR: %d, DR: %d)\n"ANSI_COLOR_RESET,i,Wolf.GR, Wolf.DR);
	for(int j = 0; j < 200000000; j++);
	std::cout << "Wolf population:" << Wolf.Pop << std:: endl;
	omp_unset_lock(&GrainLock);
	omp_unset_lock(&DeerLock);
	omp_unset_lock(&WolfLock);
}
void setWeather(float * NowPrecip, int NowMonth , float * NowTemp, unsigned int seed);
void pNoah(float * NowPrecip, int NowMonth , float * NowTemp, unsigned int seed)
{
	int i = 0;
	Noah.tmpPop = Noah.Pop;
	for(i = 0; i < MAXDAYS;)
	{
		// eat
		if(Grain.Pop < 1 && Deer.Pop < 1 && Wolf.Pop < 1)
			Noah.Pop = 0;
		if(Noah.isAlive())
		{
			if (Grain.Pop > Deer.Pop && Grain.Pop > Wolf.Pop)
			{
				omp_set_lock(&GrainLock);
				Grain.Pop -= 90;
				omp_unset_lock(&GrainLock);
			}
			if (Deer.Pop > Grain.Pop && Deer.Pop > Wolf.Pop)
			{
				omp_set_lock(&DeerLock);
				Deer.Pop -= 1;
				omp_unset_lock(&DeerLock);
			}
			if (Wolf.Pop > Deer.Pop && Wolf.Pop > Grain.Pop)
			{
				omp_set_lock(&WolfLock);
				Wolf.Pop -= 1;
				omp_unset_lock(&WolfLock);
			}
		}
		#pragma omp barrier
		i++;
		seed = rand();
		setWeather(NowPrecip, NowMonth , NowTemp, seed);
	}
	if(!Noah.isAlive())
		printf( ANSI_COLOR_RED "- Month %d: Noah starved to death...(Grain: %d, Deer: %d, Wolf: %d)\n"ANSI_COLOR_RESET,i,Grain.Pop, Deer.Pop, Wolf.Pop);
	for(int j = 0; j < 300000000; j++);
	if(Noah.isAlive())
		std::cout << "Noah Survived!" << std::endl;
	else
		std::cout << "Noah did not Survive!" << std::endl;
	omp_unset_lock(&GrainLock);
	omp_unset_lock(&DeerLock);
	omp_unset_lock(&WolfLock);
}
void setWeather(float * NowPrecip, int NowMonth , float * NowTemp, unsigned int seed)
{
	float ang = (  30.*(float)NowMonth + 15.  ) * ( M_PI / 180. );
	float temp = AVG_TEMP - AMP_TEMP * cos( ang );
	*NowTemp = temp + Ranf( -RANDOM_TEMP, RANDOM_TEMP, &seed );
	float precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin( ang );
	*NowPrecip = precip + Ranf( -RANDOM_PRECIP, RANDOM_PRECIP, &seed );
	if( *NowPrecip < 0. )
		*NowPrecip = 0.;
}
int main( int argc, char *argv[])
{
	srand(time(NULL));
	unsigned int seed = rand();
	int  NowYear = 2014;		// 2014 - 2019
	int  NowMonth = 0;		// 0 - 11

//	float NowPrecip;		// inches of rain per month
	//float NowTemp;			// temperature this month
	float NowHeight = 1.0;		// grain height in inches
	int  NowNumDeer = 1;		// current deer population

	int NUMTHREADS = 1;
	bool supress = false;
	if (argc > 1)
		NUMTHREADS = atoi(argv[1]);
	if (argc > 2)
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
			" threads.\n", NUMTHREADS);
		printf(ANSI_COLOR_BLUE "===========================================\n\n" ANSI_COLOR_RESET);
	}
	omp_set_num_threads(NUMTHREADS);
	int numProcessors = omp_get_num_procs( );

	Grain.GR = 50*30;
	Grain.DR = 0;
	Grain.Pop = rand() % 1000 + 1000;

	Deer.GR = 0;
	Deer.DR = 0;
	Deer.Pop = rand() % 20 + 20;

	Wolf.GR = 0;
	Wolf.DR = 0;
	Wolf.Pop = rand() % 20 + 20;

	Noah.GR = 0;
	Noah.DR = 0;
	Noah.Pop = 1;

	omp_init_lock(&GrainLock);
	omp_init_lock(&DeerLock);
	omp_init_lock(&WolfLock);


	if(!supress)
	{
		std::cout << "Story time!" << std::endl<< std::endl;
		std::cout << "   So God said to Noah, I am going to put an end to all people, for the"<< std::endl;
		std::cout << "earth is filled with some wicked s**t because of them! I am surely"<< std::endl;
		std::cout << "going to destroy both them and the earth because ... it's more dramatic that way! " << std::endl << std::endl;
		std::cout << "   Go build an arc and take a pair of each animal (don't forget the Dodo" << std::endl;
		std::cout << "They look liek birds, but they can't fly ... I guess chickens too)." << std::endl << std::endl;
		std::cout << "  - \"But god Jesus was good at carpenting, not me \" said Noah to God" << std::endl;
		std::cout << "  - Not with the whole \"ow your son this and that\" again replied God" << std::endl;
		std::cout << "    Just build a canoe or a small fishing boat would do, I\'ll shrink everything!"<< std::endl << std::endl;
		std::cout << "So Noah built the boat, but God got busy with planning his next religion" << std::endl;
		std::cout << "and forgot to shrink the animals." << std::endl;
		std::cout << "Noah decided to teach God a lesson, and only brought some grain," << std::endl;
		std::cout << Deer.Pop << " Deers and "<< Wolf.Pop << " Wolves to his boat." << std::endl << std::endl;
		std::cout << "Here is what happened next according to Noah's Diary:" << std::endl << std::endl;
	}
	// Routine:
	myUtil.timerStart();
	#pragma omp parallel sections shared(Grain,Deer,Wolf,Noah)
	{
		#pragma omp section
		{
			pGrain();
		}
		#pragma omp section
		{
			pDeer();
		}
		#pragma omp section
		{
			pWolf();
		}
		#pragma omp section
		{
			pNoah(&NowPrecip, NowMonth , &NowTemp, seed);
		}
		// Please note the reason the weather is not run is because it is called in Noah
		// agent, Noah controls the weather! (he is a profit after all!)

		// implied barrier
	}
	// End of routine
	myUtil.timerStop();
	if(!supress)
		printf("The process took ");
	printf("%#f",myUtil.Time());
	if(!supress)
		printf(" seconds.\n");
	if(!supress)
		printf(ANSI_COLOR_YELLOW "Done!\n" ANSI_COLOR_RESET);
	return 0;
}
