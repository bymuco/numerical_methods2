#include<iostream>
#include<cmath>
#include<stdlib.h>
#include<fstream>
using namespace std;

class Simplex
{
	public:
	long nov, noc, *coeff, *cj, *cb, *xb, *ratio, **mesh, *zjcj, sum, *soln;
	char *b, *variables, ch, *fn;
	int artvar, k;
	void getInput();
	void getInputSimplex();
	void init();
	void displayDataSimplex();
	void subtract_zjcj();
	void simplexMethod();
	void displayOptimalSol();
	void displaySol();
	int checkPositive();
	void replace_variables(int m, int l);
	void makeZeros(int m, int l, double pivot);
	void makeOnes(int m, double pivot);
	void findRatio(int l);
	int getMin(long *A, long n);
};
