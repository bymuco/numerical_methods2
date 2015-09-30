//============================================================================
// Name        : ODE.cpp
// Author      : tushar
// Version     :
// Copyright   :
// Description : ODEs in C++, Ansi-style
//============================================================================

#include "ODE.hpp"
#include "gnuplot_i.hpp"
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
	ofstream fout("op.txt");
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
	ofstream fout("op.txt");
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
	ofstream fout("op.txt");
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

void ODE::improvedTangent() {
	double y = yi, actval = 0.37, error = 0;
	double h = (double) (b - a) / n;
	double k1, k2;
	ofstream fout("op.txt");
	cout << "  h   y   error\n";
	for (double t = a; t < b; t += h) {
		cout << fixed << setprecision(3) << t << " " << y << " " << error
				<< "\n";
		fout << fixed << setprecision(3) << t << " " << error << endl;

		k1 = h * f(t, y);
		k2 = h * f(t + 0.5 * h, y + 0.5 * k1);

		//cout << "k1 : " << k1 << "\tk2 : " << k2  << endl;
		y += k2;
		error = actval - y;
	}
	fout.close();
	cout << "done\n";
}

void ODE::eulerCauchy() {
	double y = yi, actval = 0.37, error = 0;
	double h = (double) (b - a) / n;
	double k1, k2;
	ofstream fout("op.txt");
	cout << "  h   y   error\n";
	for (double t = a; t < b; t += h) {
		cout << fixed << setprecision(3) << t << " " << y << " " << error
				<< "\n";
		fout << fixed << setprecision(3) << t << " " << error << endl;

		k1 = h * f(t, y);
		k2 = h * f(t + h, y + k1);

		//cout << "k1 : " << k1 << "\tk2 : " << k2 << endl;
		y += 0.5 * (k1 + k2);
		error = actval - y;
	}
	fout.close();
	cout << "done\n";
}

void ODE::NystromMethod() {
	double y = yi, actval = 0.37, error = 0;
	double h = (double) (b - a) / n;
	double k1, k2, k3;
	ofstream fout("op.txt");
	cout << "  h   y   error\n";
	for (double t = a; t < b; t += h) {
		cout << fixed << setprecision(3) << t << " " << y << " " << error
				<< "\n";
		fout << fixed << setprecision(3) << t << " " << error << endl;

		k1 = h * f(t, y);
		k2 = h * f(t + 0.67 * h, y + 0.67 * k1);
		k3 = h * f(t + 0.67 * h, y + 0.67 * k2);
		//cout << "k1 : " << k1 << "\tk2 : " << k2 << "\tk3 : " << k3 << endl;
		y += 0.125 * (2 * k1 + 3 * k2 + 3 * k3);
		error = actval - y;
	}
	fout.close();
	cout << "done\n";
}

void ODE::HeunMethod() {
	double y = yi, actval = 0.37, error = 0;
	double h = (double) (b - a) / n;
	double k1, k2, k3;
	ofstream fout("op.txt");
	cout << "  h   y   error\n";
	for (double t = a; t < b; t += h) {
		cout << fixed << setprecision(3) << t << " " << y << " " << error
				<< "\n";
		fout << fixed << setprecision(3) << t << " " << error << endl;

		k1 = h * f(t, y);
		k2 = h * f(t + 0.33 * h, y + 0.33 * k1);
		k3 = h * f(t + 0.67 * h, y + 0.67 * k2);
		//cout << "k1 : " << k1 << "\tk2 : " << k2 << "\tk3 : " << k3 << endl;
		y += 0.25 * (k1 + 3 * k3);
		error = actval - y;
	}
	fout.close();
	cout << "done\n";
}

void ODE::ClassicalMethod() {
	double y = yi, actval = 0.37, error = 0;
	double h = (double) (b - a) / n;
	double k1, k2, k3;
	ofstream fout("op.txt");
	cout << "  h   y   error\n";
	for (double t = a; t < b; t += h) {
		cout << fixed << setprecision(3) << t << " " << y << " " << error
				<< "\n";
		fout << fixed << setprecision(3) << t << " " << error << endl;

		k1 = h * f(t, y);
		k2 = h * f(t + 0.5 * h, y + 0.5 * k1);
		k3 = h * f(t + h, y - k1 + 2 * k2);
		//cout << "k1 : " << k1 << "\tk2 : " << k2 << "\tk3 : " << k3 << endl;
		y += 0.17 * (k1 + 4 * k2 + k3);
		error = actval - y;
	}
	fout.close();
	cout << "done\n";
}

void ODE::RK() {
	double y = yi, actval = 0.37, error = 0;
	double h = (double) (b - a) / n;
	double k1, k2, k3, k4;
	ofstream fout("op.txt");
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
	ofstream fout("op.txt");
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
	ofstream fout("op.txt");
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
	ofstream fout("op.txt");
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

void ODE::AdamsBashforth1() {
	double y = yi, actval = 0.37, error = 0;
	double h = (double) (b - a) / n;
	ofstream fout("op.txt");
	cout << "  h   y   error\n";
	for (double t = a; t < b; t += h) {
		cout << fixed << setprecision(3) << t << " " << y << " " << error
				<< "\n";
		fout << fixed << setprecision(3) << t << " " << error << endl;

		y += h * f1(t, y);
		error = actval - y;
	}
	fout.close();
	cout << "done\n";
}

void ODE::AdamsBashforth2() {
	double y = yi, actval = 0.37, error = 0, y1 = 0;
	double h = (double) (b - a) / n;
	ofstream fout("op.txt");
	cout << "  h   y   error\n";
	for (double t = a; t < b; t += h) {
		cout << fixed << setprecision(3) << t << " " << y << " " << error
				<< "\n";
		fout << fixed << setprecision(3) << t << " " << error << endl;
		y += (h / 2) * (3 * f1(t, y) - f1(t, y1));
		y1 = y;

		error = actval - y;
	}
	fout.close();
	cout << "done\n";
}

void ODE::AdamsBashforth3() {
	double y = yi, actval = 0.37, error = 0, y1 = 0, y2 = 0;
	double h = (double) (b - a) / n;
	ofstream fout("op.txt");
	cout << "  h   y   error\n";
	for (double t = a; t < b; t += h) {
		cout << fixed << setprecision(3) << t << " " << y << " " << error
				<< "\n";
		fout << fixed << setprecision(3) << t << " " << error << endl;
		y += (h / 2) * (23 * f1(t, y) - 16 * f1(t, y1) + 5 * f1(t, y2));
		y1 = y2;
		y2 = y;

		error = actval - y;
	}
	fout.close();
	cout << "done\n";
}

void ODE::NystromMethod1() {
	double y = yi, actval = 0.37, error = 0, y1 = 0;
	double h = (double) (b - a) / n;
	ofstream fout("op.txt");
	cout << "  h   y   error\n";
	for (double t = a; t < b; t += h) {
		cout << fixed << setprecision(3) << t << " " << y << " " << error
				<< "\n";
		fout << fixed << setprecision(3) << t << " " << error << endl;
		y = y1 + 2 * h * f1(t, y);
		y1 = y;

		error = actval - y;
	}
	fout.close();
	cout << "done\n";
}

void ODE::NystromMethod2() {
	double y = yi, actval = 0.37, error = 0, y1 = 0, y2 = 0;
	double h = (double) (b - a) / n;
	ofstream fout("op.txt");
	cout << "  h   y   error\n";
	for (double t = a; t < b; t += h) {
		cout << fixed << setprecision(3) << t << " " << y << " " << error
				<< "\n";
		fout << fixed << setprecision(3) << t << " " << error << endl;
		y += y1 + h / 3 * (7 * f1(t, y) - 2 * f1(t, y1) + f1(t, y2));
		y1 = y2;
		y2 = y;

		error = actval - y;
	}
	fout.close();
	cout << "done\n";
}
/*
 void ODE::AdamsMoulton1() {
 int i;
 double *y, actval = 0.37, error = 0;
 double h = (double) (b - a) / n;
 y = new double[n];
 y[0] = yi;
 ofstream fout("AM1op.txt");
 cout << "  h   y   error\n";
 for (double t = a, i = 0; t < b, i < n; t += h, i++) {
 cout << fixed << setprecision(3) << t << " " << y << " " << error
 << "\n";
 fout << fixed << setprecision(3) << t << " " << error << endl;
 y[i + 1] = y[i] + h / 2 * (f1(t, y[i + 1]) + f1(t, y[i]));
 error = actval - y[i + 1];
 }
 fout.close();
 cout << "done\n";
 }
 */

int ODE::menu() {
	int ch;
	cout << "1. Euler Series" << endl;
	cout << "2. Taylor Series 2nd" << endl;
	cout << "3. Taylor Series 3rd" << endl;
	cout << "4. Improved Tangent Method" << endl;
	cout << "5. Euler Cauchy Method" << endl;
	cout << "6. Nystrom Method" << endl;
	cout << "7. Heun Method" << endl;
	cout << "8. Classical Method" << endl;
	cout << "9. Runge Kutta Method" << endl;
	cout << "10. Classical Runge Kutta Method" << endl;
	cout << "11. Implicit Runge Kutta Method 2nd" << endl;
	cout << "12. Implicit Runge Kutta Method 4th" << endl;

	cin >> ch;
	return ch;
}

void ODE::plot() {
	int c;
	Gnuplot plot1("ODE");
	plot1 << "set xlabel 'stepsize'";
	plot1 << "set ylabel 'error'";
	plot1 << "plot 'op.txt' w l";
	cin >> c;
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
