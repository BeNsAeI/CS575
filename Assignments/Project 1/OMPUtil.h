#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include <sys/time.h>

class Utility{
public:
	Utility();
	bool isOpenMP();
	double megaMult(long op, float time);
	float speedUp();
	float pf(float speedup);
	float TS;
	float TM;
	float speedUp(float ts, float tm);
	void timerStart();
	void timerStop();
	double Time();
private:
	struct timeval startTime;
	struct timeval endTime;
};
