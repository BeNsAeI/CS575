#include <iostream>
#include <omp.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include <sys/time.h>
#include "OMPUtil.h"
#include "color.h"

using std::cin;
using std::cout;
using std::endl;

int main(int argc, char ** argv)
{
	cout << "Creating the Utility tools." << endl<< endl;
	Utility myUtil;
	myUtil.isOpenMP();
	cout << "Hello OpenMP" << endl;
	cout << "Number of available threads is " << omp_get_max_threads() << "." << endl;
	omp_set_num_threads(omp_get_max_threads());
	cout << "Number of used threads is " << omp_get_num_threads() << "." << endl << endl;
	long stress = 10;
	long second = 420000000;
	cout << "Performing stress test of size " << (double)((double)stress*(double)second) << " samples." << endl;
	cout << "Single thread started" << endl;
	myUtil.timerStart();
	for(int i = 0; i < stress; i++)
	{
		for(int j = 0; j < second; j++);
		int thread = omp_get_thread_num();
		printf("%d -> %d\n",thread,i);
	}
	myUtil.timerStop();
	myUtil.TS = myUtil.Time();
	cout << "Single thread ended in ";
	printf(ANSI_COLOR_YELLOW "%g" ANSI_COLOR_RESET,myUtil.TS);
	cout << " seconds." << endl;
	
	printf("There were " ANSI_COLOR_CYAN "%g" ANSI_COLOR_RESET " Mega Ops per second.\n",myUtil.megaMult(stress*second, myUtil.TS));
	
	cout << "Multi thread (Out of Order) started" << endl;
	myUtil.timerStart();
	#pragma omp parallel for
		for(int i = 0; i < stress; i++)
		{
			for(int j = 0; j < second; j++);
			int thread = omp_get_thread_num();
			printf("%d -> %d\n",thread,i);
		}
	myUtil.timerStop();
	myUtil.TM = myUtil.Time();
	cout << "Multi thread ended in ";
	printf(ANSI_COLOR_YELLOW "%g" ANSI_COLOR_RESET,myUtil.TM);
	cout  << " seconds." << endl;
	printf("There were " ANSI_COLOR_CYAN "%g" ANSI_COLOR_RESET " Mega Ops per second.\n",myUtil.megaMult(stress*second, myUtil.TM));
	printf("SpeedUp is about " ANSI_COLOR_CYAN "%g" ANSI_COLOR_RESET ".\n", myUtil.speedUp());
	cout << "Multi thread (In Order) started" << endl;
	myUtil.timerStart();
	#pragma omp parallel for
		for(int i = 0; i < stress; i++)
		{
			for(int j = 0; j < second; j++);
			int thread = omp_get_thread_num();
			printf("%d -> %d\n",thread,i);
		}
	myUtil.timerStop();
	myUtil.TM = myUtil.Time();
	printf("Multi thread ended in " ANSI_COLOR_YELLOW "%g" ANSI_COLOR_RESET " seconds.\n",myUtil.TM);
	printf("There were " ANSI_COLOR_CYAN "%g" ANSI_COLOR_RESET " Mega Ops per second.\n",myUtil.megaMult(stress*second, myUtil.TM));
	printf("SpeedUp is about " ANSI_COLOR_CYAN "%g" ANSI_COLOR_RESET ".\n", myUtil.speedUp());
	return 0;
}
