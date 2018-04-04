#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include <sys/time.h>

class Utility{
public:
	bool isOpenMP();
	float megaMult();
	float speedUp();
	void timerStart();
	void timerStop();
	double Time();
private:
	struct timeval startTime;
	struct timeval endTime;
};
