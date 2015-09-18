#include <stdio.h>
#include<stdlib.h>
#include<math.h>
#include<fstream>
#include <iostream>
#include <iomanip>
//#include "gnu_i.hpp"
#define PI 3.1415

using namespace std;
class ODE {
public:
	fstream fout;
	void getInput();
	void eulerSeries();
	void taylorSeries2();
	void taylorSeries3();
	void RK();
	void classicalRK();
	void imRK2();
	void imRK4();
	void plot();
	double f(double, double);
	double f1(double, double);
	double f2(double, double);
};
