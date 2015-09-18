//============================================================================
// Name        : ODE.cpp
// Author      : tushar
// Version     :
// Copyright   : 
// Description : ODEs in C++, Ansi-style
//============================================================================

#include "ODE.hpp"
int a, b, n;
double yi;
//function to get input for euler series
void ODE::getInput() {
	cout << "enter (a, b) : "; //Lower & Upper limits
	cin >> a >> b;
	cout << "\nenter y(0) : "; //Initial y
	cin >> yi;
	cout << "\nenter n : "; //No. of steps
	cin >> n;
}

void ODE::eulerSeries() {
	double y = yi, actval = 0.37, error = 0;
	double h = (double) (b - a) / n;
	fstream fout("eulerop.txt");
	cout << "  h   y   error\n";
	for (double t = a; t < b; t += h) {
		cout << fixed << setprecision(3) << t << " " << y << " " << error
				<< "\n";
		fout << fixed << setprecision(3) << t << " " << error << endl;
		y += h * f(t, y);
		error = actval - y;
	}
	fout.close();
	cout << "done\n";
}

void ODE::taylorSeries2() {
	double y = yi, actval = 0.37, error = 0;
	double h = (double) (b - a) / n;
	fstream fout("taylor2op.txt");
	cout << "  h   y   error\n";
	for (double t = a; t < b; t += h) {
		cout << fixed << setprecision(3) << t << " " << y << " " << error
				<< "\n";
		fout << fixed << setprecision(3) << t << " " << error << endl;
		y += h * f(t, y) + (((h * h) / 2) * f1(t, y));
		error = actval - y;
	}
	fout.close();
	cout << "done\n";
}

void ODE::taylorSeries3() {
	double y = yi, actval = 0.37, error = 0;
	double h = (double) (b - a) / n;
	fstream fout("taylor3op.txt");
	cout << "  h   y   error\n";
	for (double t = a; t < b; t += h) {
		cout << fixed << setprecision(3) << t << " " << y << " " << error
				<< "\n";
		fout << fixed << setprecision(3) << t << " " << error << endl;
		y += h * f(t, y) + (((h * h) / 2) * f1(t, y))
				+ (((h * h * h) / 6) * f2(t, y));
		error = actval - y;
	}
	fout.close();
	cout << "done\n";
}

void ODE::RK() {
	double y = yi, actval = 0.37, error = 0;
	double h = (double) (b - a) / n;
	double k1, k2, k3, k4;
	ofstream fout("RKop.txt");
	cout << "  h   y   error\n";
	for (double t = a; t < b; t += h) {
		cout << fixed << setprecision(3) << t << " " << y << " " << error
				<< "\n";
		fout << fixed << setprecision(3) << t << " " << error << endl;

		k1 = h * f(t, y);
		k2 = h * f(t + 0.33 * h, y + 0.33 * k1);
		k3 = h * f(t + 0.66 * h, y - 0.33 * k1 + k2);
		k4 = h * f(t + h, y + k1 - k2 + k3);

		//cout << "k1 : " << k1 << "\tk2 : " << k2 << "\tk3 : " << k3 << "\tk4 : "
		//		<< k4 << endl;
		y += ((1 / double(8)) * (k1 + 3 * k2 + 3 * k3 + k4));
		error = actval - y;
	}
	fout.close();
	cout << "done\n";
}

void ODE::classicalRK() {
	double y = yi, actval = 0.37, error = 0;
	double h = (double) (b - a) / n;
	double k1, k2, k3, k4;
	ofstream fout("classicalRKop.txt");
	cout << "  h   y   error\n";
	for (double t = a; t < b; t += h) {
		cout << fixed << setprecision(3) << t << " " << y << " " << error
				<< "\n";
		fout << fixed << setprecision(3) << t << " " << error << endl;

		k1 = h * f(t, y);
		k2 = h * f(t + 0.5 * h, y + 0.5 * k1);
		k3 = h * f(t + 0.5 * h, y + 0.5 * k2);
		k4 = h * f(t + h, y + k3);

		//cout << "k1 : " << k1 << "\tk2 : " << k2 << "\tk3 : " << k3 << "\tk4 : "
		//		<< k4 << endl;
		y += (1 / double(6)) * (k1 + 2 * k2 + 2 * k3 + k4);
		error = actval - y;
	}
	fout.close();
	cout << "done\n";
}

void ODE::imRK2() {
	double y = yi, actval = 0.37, error = 0;
	double h = (double) (b - a) / n;
	double k1;
	ofstream fout("imRK2op.txt");
	cout << "  h   y   error\n";
	for (double t = a; t < b; t += h) {
		cout << fixed << setprecision(3) << t << " " << y << " " << error
				<< "\n";
		fout << fixed << setprecision(3) << t << " " << error << endl;

		k1 = h * f(t + 0.5 * h, y + 0.5 * k1);

		//cout << "k1 : " << k1 << endl;
		y += k1;
		error = actval - y;
	}
	fout.close();
	cout << "done\n";
}

void ODE::imRK4() {
	double y = yi, actval = 0.37, error = 0;
	double h = (double) (b - a) / n;
	double k1, k2;
	ofstream fout("imRK4op.txt");
	cout << "  h   y   error\n";
	for (double t = a; t < b; t += h) {
		cout << fixed << setprecision(3) << t << " " << y << " " << error
				<< "\n";
		fout << fixed << setprecision(3) << t << " " << error << endl;

		k1 = h * f(t + 0.2113 * h, y + 0.25 * k1 + 0.2887 * k2);
		k2 = h * f(t + 0.7887 * h, y + 0.5387 * k1 + 0.25 * k2);

		//cout << "k1 : " << k1 << "k2 : " << k2 << endl;
		y += 0.5 * (k1 + k2);
		error = actval - y;
	}
	fout.close();
	cout << "done\n";
}

double ODE::f(double x, double y) {
	return (-2 * x * y);
}

double ODE::f1(double x, double y) {
	return ((-2 * y) + (4 * x * x * y));
}

double ODE::f2(double x, double y) {
	return ((-4 * x * y) + (8 * x * y) - (2 * x * x * x * y));
}

/*
 void ODE::plot(){
 Gnuplot plot1("This is a Euler's Simple Plot");
 plot1 << "plot 'eulerop.txt' w l";
 }
 */
