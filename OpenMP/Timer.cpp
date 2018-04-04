#include "Timer.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include <sys/time.h>

void Timer::Start()
{
	gettimeofday(&startTime,NULL);
}
void Timer::Stop()
{
	gettimeofday(&endTime,NULL);
}
double Timer::Time()
{
	return (((endTime.tv_sec - startTime.tv_sec) * 1000000u + endTime.tv_usec - startTime.tv_usec) / 1.e6);
}
