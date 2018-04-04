#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include <sys/time.h>

class Timer{
public:
	void Start();
	void Stop();
	double Time();
private:
	struct timeval startTime;
	struct timeval endTime;
};
