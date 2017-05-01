#include "stdafx.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <fstream>


int main()
{
	const int N = 11; //Number of particles (min of 2)
	double epsilon = 0.1;
	double delta_t = 2 * M_PI / N;
	const int steps = 100 ;
	double Result[steps][2 * N]; // omega_1,theta_1, ..., omega_N, theta_N

	for (int i = 0; i < steps; i++)
	{
		for (int j = 0; j < 2*N; j++)
		{
			Result[i][j] = 0.0;
		}
	}

	//INITIALIZE POINTS
	srand(time(NULL));
	for (int i = 0; i < N; i++) {
		double omega = -1.0 + (2.0 * i / (N - 1));
		double theta = (double)rand() / (double)RAND_MAX * 2.0 * M_PI;
		Result[0][2*i] = omega;
		Result[0][2*i+1] = theta;
	}

	//EVOLUTION
	for (int n = 1; n < steps; n++) {
		for (int i = 0; i < N; i++) {
			Result[n][2 * i + 1] = delta_t*Result[n-1][2 * i] + Result[n - 1][2 * i + 1] - 2* M_PI * floor((delta_t*Result[n - 1][2 * i] + Result[n - 1][2 * i + 1]) / (2 * M_PI));
			Result[n][2 * i] = delta_t * epsilon * (sin(Result[n][2 * i + 1]-n*delta_t) + sin(Result[n][2 * i + 1] + n*delta_t)) + Result[n - 1][2 * i];
		}
	}

	std::ofstream myfile;
	myfile.open("CMHW7.txt");

	for (int i = 0; i < steps; i++)
	{
		for (int j = 0; j < 2*N; j++)
		{
			myfile << Result[i][j] << ' ';
			std::cout << Result[i][j] << ' ';
		}
		myfile << std::endl;
		std::cout << std::endl;
	}
    return 0;
}

