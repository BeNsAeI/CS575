#include "OMPUtil.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include <sys/time.h>
#include <iostream>

Utility::Utility()
{
	TS = 0;
	TM = 0;
}
bool Utility::isOpenMP(bool DEBUG)
{
	#ifndef _OPENMP
		fprintf(stderr, "OpenMP is not suppoerted!\n");
		exit(-1);
	#endif
	if(DEBUG)
		std::cout << "OpenMP is ready!" << std::endl;
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
float Utility::pf(float speedup)
{
	return (4.0/3.0)*( 1.0 - (1.0/(float)speedup) );
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
