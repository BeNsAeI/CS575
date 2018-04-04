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
	int stress = 10;
	int second = 420000000;
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
	cout << "Single thread ended in " << myUtil.Time() << " seconds." << endl;
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
	cout << "Multi thread ended in " << myUtil.Time() << " seconds." << endl;
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
	cout << "Multi thread ended in " << myUtil.Time() << " seconds." << endl;

	return 0;
}
