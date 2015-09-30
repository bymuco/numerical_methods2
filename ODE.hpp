#include <cstdlib>
#include <cmath>
#include <fstream>
#include <iostream>
#include <iomanip>

#define PI 3.1415

using namespace std;
class ODE {
public:
	fstream fout;
	void getInput();
	void eulerSeries();
	void taylorSeries2();
	void taylorSeries3();

	//second order methods
	void improvedTangent();
	void eulerCauchy();

	//third order methods
	void NystromMethod();
	void HeunMethod();
	void ClassicalMethod();

	//fourth order methods
	void RK();
	void classicalRK();

	//implicit RK methods
	void imRK2();
	void imRK4();

	void AdamsBashforth1();
	void AdamsBashforth2();
	void AdamsBashforth3();
	void NystromMethod1();
	void NystromMethod2();
	void AdamsMoulton1();
	void AdamsMoulton2();
	void AdamsMoulton3();

	int menu();
	void plot();

	double f(double, double);
	double f1(double, double);
	double f2(double, double);
};
