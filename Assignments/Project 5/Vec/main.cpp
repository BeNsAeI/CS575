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

#define Q(x) #x
#define QUOTE(x) Q(x)

int main( int argc, char *argv[])
{
	srand(time(NULL));
	double * A;
	double * C;
	A = new double [NUMS];
	C = new double [NUMS];
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
		printf("Array size is " ANSI_COLOR_YELLOW "%s" ANSI_COLOR_RESET ".\n", QUOTE(NUMS));
		printf(ANSI_COLOR_BLUE "===========================================\n\n" ANSI_COLOR_RESET);
	}
	omp_set_num_threads(NUMTHREADS);
	int numProcessors = omp_get_num_procs( );
	// Populate the Arrays
	#pragma omp parallel for shared(C,A)
	for( int i = 0; i < NUMS; i++ )
	{
		A[i] = rand() % 1000;
	}
	//End of array population


	// Routine:
	myUtil.timerStart();

	#pragma omp parallel for shared(C,A)
	for( int i = 0; i < NUMS; i++ )
	{
		C[i] = sqrt( A[i] );
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
	delete A;
	delete C;
	A = NULL;
	C = NULL;
	return 0;
}
