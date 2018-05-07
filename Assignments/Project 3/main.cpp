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

#ifdef FIX1
	struct s
	{
		float value;
		int pad[PADDING];
	} Array[4];
#endif
#ifdef FIX2
	struct s
	{
		float value;
	} Array[4];
#endif
int main( int argc, char *argv[])
{

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
			" threads and " ANSI_COLOR_CYAN "%d" ANSI_COLOR_RESET
			" paddings.\n", NUMTHREADS, PADDING);
		#ifdef FIX1
			printf("Applying " ANSI_COLOR_YELLOW "FIX 1" ANSI_COLOR_RESET ".\n");
		#endif
		#ifdef FIX2
			printf("Applying " ANSI_COLOR_YELLOW "FIX 2" ANSI_COLOR_RESET ".\n");
		#endif
		printf(ANSI_COLOR_BLUE "===========================================\n\n" ANSI_COLOR_RESET);
	}
	omp_set_num_threads(NUMTHREADS);
	int numProcessors = omp_get_num_procs( );

	// Routine:
	int someBigNumber = 250000000;
	myUtil.timerStart();
	#pragma omp parallel for
	for( int i = 0; i < 4; i++ )
	{
		for( int j = 0; j < someBigNumber; j++ )
		{
			#ifdef FIX1
				Array[ i ].value = Array[ i ].value + 2.;
			#endif
			#ifdef FIX2
				float tmp = Array[ i ].value + 2.;
				Array[ i ].value = tmp;
			#endif
		}
	}
	myUtil.timerStop();
	// End of routine

	if(!supress)
		printf("The process took ");
	printf("%#f",myUtil.Time());
	if(!supress)
		printf(" seconds.\n");
	if(!supress)
		printf(ANSI_COLOR_YELLOW "Done!\n" ANSI_COLOR_RESET);
	return 0;
}
