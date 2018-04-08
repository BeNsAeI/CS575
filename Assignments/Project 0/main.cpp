#include <omp.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "color.h"
#include "OMPUtil.h"

#define NUMT	         4
#define DEBUG 0
#define ARRAYSIZE       50000	// you decide
#define NUMTRIES        50000	// you decide

float A[ARRAYSIZE];
float B[ARRAYSIZE];
float C[ARRAYSIZE];

int
main(int argc, char**argv)
{
#ifndef _OPENMP
	fprintf( stderr, "OpenMP is not supported here -- sorry.\n" );
	return 1;
#endif
	int numThreads = 1;
	bool supress = false;
	if(argc > 1)
		numThreads = atoi(argv[1]);
	if(argc > 2)
		supress = true;
	if (DEBUG)
		std::cout << argv[1] << ", " << numThreads << std::endl;

	if(!supress)
		printf("Initiating the utility tools...\n");
	Utility myUtil;
	if(!supress)
		myUtil.isOpenMP();

	omp_set_num_threads( numThreads );
	if(!supress)
		fprintf( stderr, "Using " ANSI_COLOR_CYAN "%d" ANSI_COLOR_RESET " threads\n", numThreads );
	double maxMegaMults = 0.;
	double sumMegaMults = 0.;
	double totalTime;
	for( int t = 0; t < NUMTRIES; t++ )
	{
		double time0 = omp_get_wtime( );

		#pragma omp parallel for
		for( int i = 0; i < ARRAYSIZE; i++ )
		{
			C[i] = A[i] * B[i];
		}

		double time1 = omp_get_wtime( );
		double megaMults = (double)ARRAYSIZE/(time1-time0)/1000000.;
		sumMegaMults += megaMults;
		if( megaMults > maxMegaMults )
			maxMegaMults = megaMults;
		totalTime += (time1-time0);
	}

	double avgMegaMults = sumMegaMults/(double)NUMTRIES;
	if(!supress)
	{
		printf( "   Peak Performance = " ANSI_COLOR_YELLOW "%8.2lf" ANSI_COLOR_RESET " MegaMults/Sec\n", maxMegaMults );
		printf( "Average Performance = " ANSI_COLOR_YELLOW "%8.2lf" ANSI_COLOR_RESET " MegaMults/Sec\n", avgMegaMults );
		printf( " Total time is: " ANSI_COLOR_YELLOW "%g.\n" ANSI_COLOR_RESET, totalTime);
	}else{
		printf("%g\n",totalTime);
	}
	// note: %lf stands for "long float", which is how printf prints a "double"
	//        %d stands for "decimal integer", not "double"

	return 0;
}
