#include "OMPUtil.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include <sys/time.h>
#include <iostream>
#include "color.h"

Utility::Utility()
{
	TS = 0;
	TM = 0;
}
bool Utility::isOpenMP()
{
	printf("Checking if OpenMP is Supported...\n");
	#ifndef _OPENMP
		fprintf(stderr, ANSI_COLOR_RED "OpenMP is not suppoerted!\n" ANSI_COLOR_RESET);
		exit(-1);
	#endif
	printf(ANSI_COLOR_GREEN "OpenMP is ready!\n" ANSI_COLOR_RESET);
	return true;
}
double Utility::megaMult(long op, float time)
{
	return ((double)op/time)/1000000.0;
}
float Utility::speedUp()
{
	return  (float)(TS)/(float)(TM);
}
float Utility::speedUp(float ts, float tm)
{
	return  (float)(ts)/(float)(tm);
}
void Utility::timerStart()
{
	gettimeofday(&startTime,NULL);
}
void Utility::timerStop()
{
	gettimeofday(&endTime,NULL);
}
double Utility::Time()
{
	return (((endTime.tv_sec - startTime.tv_sec) * 1000000u + endTime.tv_usec - startTime.tv_usec) / 1.e6);
}
