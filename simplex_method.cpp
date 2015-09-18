//============================================================================
// Name        : simplexMethod.cpp
// Author      : tushar
// Version     :
// Copyright   : 
// Description : Simplex method in C++, Ansi-style
//============================================================================

#include "simplex_method.hpp"

void Simplex::getInput() {
	getInputSimplex();
	ratio = new long[noc];
	zjcj = new long[nov];
	soln = new long[nov];
	k = 0;
	init();
}

void Simplex::getInputSimplex() {
	/*int i, j;
	 cout << "# The Maximization Problem : ";
	 cout << "\n# Enter the no. of Variables : ";
	 cin >> nov;

	 cout << "\n# Enter the no. of Constraints : ";
	 cin >> noc;

	 mesh = new long *[nov];

	 for (i = 0; i < nov; i++)
	 mesh[i] = new long[noc];

	 coeff = new long[nov];
	 cout << "\n# Enter the Coefficients for Objective Function : ";
	 for (i = 0; i < nov; i++) {
	 cin >> coeff[i];
	 mesh[0][i] = coeff[i];
	 }

	 cout << "\n# Enter the Coefficients for Constraints : ";
	 for (i = 1; i < nov; i++) {
	 for (j = 0; j < noc; j++) {
	 cin >> coeff[j];
	 mesh[i][j] = coeff[j];
	 }
	 }

	 cout << "\n# Enter Cj array : ";
	 cj = new long[nov + noc];
	 for (i = 0; i < nov + noc; i++) {
	 cin >> cj[i];
	 }*/

	fn = new char[10];
	cout << "\n Enter input file : ";
	cin >> fn;
	cout << "file name=" << fn;
	ifstream in(fn);

	while (!in) {
		cout << "\n File not found !";
		cout << "\n Enter input file : ";
		cin >> fn;
		cout << "file name=" << fn;
		ifstream in(fn);
	}

	//cout<<"\n Is it Maximize [y/n] ?";
	in >> ch;
	if (ch == 'n') {

		cout << "\n Minimize...";
		exit(5);
	}
	//cout<<"\nHow many constraints ? ";
	do {
		in >> noc;
	} while (noc <= 0);

	//cout<<"\nHow many variables ? ";
	do {
		in >> nov;
	} while (nov <= 0);

	mesh = new long *[noc];

	if (mesh == NULL || xb == NULL) {
		cout << "\n Memory Error: No enough space available on disk !";
		exit(1);
	}
	for (int i = 0; i < noc; i++) {
		mesh[i] = new long[nov];
	}

	//cout<<"\n Accept mesh : ";

	for (int i = 0; i < noc; i++) {
		for (int j = 0; j < nov; j++) {
			in >> mesh[i][j];
		}

	}

	xb = new long[noc];
	for (int j = 0; j < noc; j++) {
		cout << "\n Enter XB : ";
		in >> xb[j];
	}

	variables = new char[nov];
	cj = new long[nov];
	if (variables == NULL || cj == NULL) {
		cout << "\n Memory Error: No enough space available on disk !";
		exit(2);
	}
	cout << "\n Enter non-zero-variables :";
	for (int i = 0; i < nov; i++) {
		cout << "\nEnter variable [char only]: ";
		in >> variables[i];
	}

	for (int i = 0; i < nov; i++) {
		cout << "\nEnter coefficient : ";
		in >> cj[i];
	}

	//cout<<"How many slack/surplus/artificial variables ?";
	in >> artvar;
	b = new char[artvar];
	cb = new long[artvar];
	if (b == NULL || cb == NULL) {
		cout << "\n Memory Error: No enough space available on disk !";
		exit(3);
	}

	for (int i = 0; i < artvar; i++) {
		//cout<<"\nEnter Variable[char only] : ";
		in >> b[i];
		//cout<<"\nEnter coefficient : ";
		in >> cb[i];
	}
}

void Simplex::init() {
	for (int i = 0; i < noc; i++) {
		ratio[i] = 0;
	}
	for (int i = 0; i < nov; i++) {
		zjcj[i] = 0;
	}
	for (int i = 0; i < nov; i++) {
		soln[i] = -1;
	}
}

void Simplex::displayDataSimplex() {
	cout
			<< "\n\n-----------------------------------------------------------------------------\n";
	cout << "\n\t\tcj";
	for (int i = 0; i < nov; i++) {
		cout << "\t" << cj[i];
	}
	cout << "\nCB\tB\tXB";
	for (int i = 0; i < nov; i++) {
		cout << "\t" << variables[i];
	}
	cout << "\tRatio";

	for (int i = 0; i < noc; i++) {
		cout << "\n" << cb[i] << "\t";
		cout << b[i] << "\t";
		cout << xb[i];
		for (int j = 0; j < nov; j++) {
			cout << "\t" << mesh[i][j];
		}
		cout << "\t" << ratio[i];

	}
	cout << "\n\t\tZjCj";
	for (int i = 0; i < nov; i++) {
		cout << "\t" << zjcj[i];

	}
	cout
			<< "\n\n-----------------------------------------------------------------------------\n";

}

void Simplex::subtract_zjcj() {
	for (int i = 0; i < nov; i++) {
		sum = 0;
		for (int j = 0; j < noc; j++) {
			sum += cb[j] * mesh[j][i];
		}
		zjcj[i] = sum - cj[i];
	}
}

void Simplex::simplexMethod() {
	subtract_zjcj();
	int flag = checkPositive();

	if (flag) {
		int l = getMin(zjcj, nov);
		findRatio(l);
		displayDataSimplex();
		int m = getMin(ratio, noc);
		cout << "\n PIVOT=" << mesh[m][l];
		makeOnes(m, mesh[m][l]);
		makeZeros(m, l, mesh[m][l]);
		replace_variables(m, l);
		displayOptimalSol();
		simplexMethod();
	} else {
		displayDataSimplex();
		displaySol();
	}

}

void Simplex::displayOptimalSol() {
	double op_sol = 0;
	int cval;
	double point[5];

	for (int i = 0; i < nov; i++) {
		if (soln[i] != -1) {
			cval = soln[i];
			op_sol += xb[cval] * cj[i];
		}
	}
	cout << "\nZopt = " << op_sol << "\n\n";
}

void Simplex::displaySol() {
	cout << "\n\nOptimized Soution : ";
	displayOptimalSol();
	exit(4);
}

int Simplex::checkPositive() {
	for (int i = 0; i < nov; i++) {
		if (zjcj[i] < 0) {
			return 1;
		}
	}
	return 0;
}

void Simplex::replace_variables(int m, int l) {

	b[m] = variables[l];
	cb[m] = cj[l];
	soln[k] = m;
	k++;
}

void Simplex::makeZeros(int m, int l, double pivot) {
	double p;
	int update_flag;
	for (int i = 0; i < noc; i++) {
		p = mesh[i][l];
		update_flag = 0;
		for (int j = 0; j < nov; j++) {
			if (i != m) {
				mesh[i][j] -= p * mesh[m][j];
				if (update_flag == 0) {
					xb[i] -= p * xb[m];
					update_flag = 1;
				}
			}

		}

	}
}

void Simplex::makeOnes(int m, double pivot) {
	int pivot_update_flag = 0;
	for (int i = 0; i < nov; i++) {
		mesh[m][i] /= pivot;
		if (pivot_update_flag == 0) {
			xb[m] /= pivot;
			pivot_update_flag = 1;
		}
	}
}

void Simplex::findRatio(int l) {
	for (int i = 0; i < noc; i++) {
		ratio[i] = xb[i] / mesh[i][l];
		if (ratio[i] < 0) {
			ratio[i] = 9999999; //unsigned long
		}
	}

}

int Simplex::getMin(long *A, long n) {
	double min = A[0];
	int index = 0;
	for (int i = 0; i < n; i++) {
		if (min > A[i]) {
			min = A[i];
			index = i;
		}
	}
	cout << "\n Founded Min is : " << min << "\tindex : " << index;
	return index;
}
