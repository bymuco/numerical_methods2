#include "Optimization.hpp"
/*
 long nor, noc, **mat, **alloc, *suppply, *demand;

 Optimization::Optimization() {

 cout << "how many rows & columns: ";
 cin >> nor >> noc;

 mat = new long *[nor];
 for (int i = 0; i < nor; i++) {
 mat[i] = new long[noc];
 }

 cout << "\nenter the " << nor << " x " << noc << " cost matrix :\n";
 for (int i = 0; i < nor; i++) {
 for (int j = 0; j < noc; j++) {
 cin >> mat[i][j];
 }
 }

 alloc = new long *[nor];
 for (int i = 0; i < nor; i++) {
 alloc[i] = new long[noc];
 }

 for (int i = 0; i < nor; i++) {
 for (int j = 0; j < noc; j++) {
 alloc[i][j] = 0;
 }
 }

 suppply = new long[noc];
 demand = new long[nor];
 cout << "enter capacities :\n";
 for (int i = 0; i < nor; i++) {
 cin >> suppply[i];
 }

 cout << "enter demands :\n";
 for (int i = 0; i < noc; i++) {
 cin >> demand[i];
 }
 }

 void Optimization::display() {
 cout << "\nyour " << nor << " x " << noc << " matrix :\n";
 for (int i = 0; i < nor; i++) {
 for (int j = 0; j < noc; j++) {
 cout << mat[i][j] << " ";
 }
 cout << endl;
 }
 cout << "capacities are:\n";
 for (int i = 0; i < nor; i++) {
 cout << suppply[i] << endl;
 }

 cout << "demands are:\n";
 for (int i = 0; i < noc; i++) {
 cout << demand[i] << " ";
 }
 }

 long p, q;
 void Optimization::findMin() {
 long min = mat[0][0];
 for (int i = 0; i < nor; i++) {
 for (int j = 0; j < noc; j++) {
 if (mat[i][j] < min) {
 min = mat[i][j];
 p = i;
 q = j;
 }
 }
 }
 //cout << "min : " << min;
 }

 void Optimization::LCM() {
 long x, y;
 long dem = new long[demand];
 long sup = new long[suppply];
 for (int i = 0; i < noc; i++)
 dem[i] = demand[i];
 for (int i = 0; i < nor; i++)
 sup[i] = suppply[i];
 while (nor > 0 && noc > 0) {
 findMin();
 if (sup[p] < dem[q])
 x = sup[p];
 else
 x = dem[q];
 }
 }
 */

int c[20][20], m, n, dem1[20], sup1[20];
int i, j, sum;

//function to get required input from user
void Optimization::getInput() {
	int s1 = 0, s2 = 0;
	cout << "\n Enter the row & column i.e. cost matrix :: ";
	cin >> m >> n;

	cout << "\n Enter the cost matrix :: ";
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++)
			cin >> c[i][j];
	}

	cout << "\n Enter the demand rows :: ";
	for (i = 0; i < n; i++)
		cin >> dem1[i];

	cout << "\n Enter the supply column :: ";
	for (i = 0; i < m; i++)
		cin >> sup1[i];

	for (i = 0; i < n; i++)
		s1 += dem1[i];
	for (i = 0; i < m; i++)
		s2 += sup1[i];

	cout << "\n Matrix :: \n";
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++)
			cout << c[i][j];
		cout << sup1[i];
		cout << "\n";
	}
	for (j = 0; j < n; j++)
		cout << dem1[j];

	if (s1 == s2)
		cout << "\n Problem is balanced ";
	else {
		cout << "\n Problem is not balanced ";
		exit(0);
	}
}

//function to find optimized value of Z by using North-West Corner Method
void Optimization::northwest() {
	int dem[20], sup[20];
	for (i = 0; i < n; ++i)
		dem[i] = dem1[i]; //stored into another array for further processing
	for (i = 0; i < m; ++i)
		sup[i] = sup1[i]; //stored into another array for further processing

	for (i = 0, j = 0; (i < m && j < n);) {
		if (sup[i] < dem[j]) { //when supply < demands
			sum += c[i][j] * sup[i];
			dem[j] -= sup[i];
			i++;
		} else if (sup[i] > dem[j]) { //when supply > demands
			sum += c[i][j] * dem[j];
			sup[i] -= dem[j];
			j++;
		} else if (sup[i] == dem[j]) { //when supply = demands
			sum += c[i][j] * dem[j];
			i++;
			j++;
		}
	}
	cout << "\n\n Cost by North-West Corner method :: " << sum << endl;
	sum = 0;
}

//function to find optimized value of Z by using Least-Cost Method
void Optimization::leastcost() {
	int b, d, c1, c2, p, q;
	int rf[20], cf[20];
	int min;
	int dem[20], sup[20];
	for (i = 0; i < n; ++i)
		dem[i] = dem1[i];
	for (i = 0; i < m; ++i)
		sup[i] = sup1[i];

	for (i = 0; i < m; i++)
		rf[i] = 0;
	for (i = 0; i < n; i++)
		cf[i] = 0;
	b = m;
	d = n;
	while (b > 0 && d > 0) {
		min = 1000; //to compare with other values
		for (i = 0; i < m; i++) //to find minimum element from cost matrix
				{
			if (rf[i] != 1) {
				for (j = 0; j < n; j++) {
					if (cf[j] != 1) {
						if (min > c[i][j]) {
							min = c[i][j];
							p = i; //storing index of minimum element
							q = j; //storing index of minimum element
						}
					}
				}
			}
		}
		if (sup[p] < dem[q])
			c1 = sup[p];
		else
			c1 = dem[q];
		for (i = 0; i < m; i++) // parse whole matrix again considering minimum element
				{
			if (rf[i] != 1) {
				for (j = 0; j < n; j++) {
					if (cf[j] != 1) {
						if (min == c[i][j]) {
							if (sup[i] < dem[j])
								c2 = sup[i];
							else
								c2 = dem[j];
							if (c2 > c1) {
								c1 = c2;
								p = i; //storing index
								q = j; //storing index
							}
						}
					}
				}
			}
		}
		// cout << min << p << q;
		if (sup[p] < dem[q]) // allocate supply
				{
			sum = sum + c[p][q] * sup[p];
			dem[q] -= sup[p];
			rf[p] = 1;
			b--;
		} else if (sup[p] > dem[q]) // allocate demand
				{
			sum = sum + c[p][q] * dem[q];
			sup[p] -= dem[q];
			cf[q] = 1;
			d--;
		} else if (sup[p] == dem[q]) // balanced end condition
				{
			sum = sum + c[p][q] * sup[p];
			rf[p] = 1;
			cf[q] = 1;
			b--;
			d--;
		}
		//cout <<"\n %d",sum);
	} //while
	cout << "\n\n Cost by Least cost method :: " << sum << endl;
	sum = 0;
}

//function to find optimized value of Z by using Vogel's Approximation Method
void Optimization::vam() {
	int k, b, d, p;
	int a[20], rf[20], cf[20], cp[20], rp[20];
	int max, min, s, t;
	int dem[20], sup[20];
	for (i = 0; i < n; ++i)
		dem[i] = dem1[i];
	for (i = 0; i < m; ++i)
		sup[i] = sup1[i];

	for (i = 0; i < m; i++)
		rf[i] = 0; // row freq
	for (i = 0; i < n; i++)
		cf[i] = 0; // col freq

	b = m, d = n;
	while (b > 0 && d > 0) {
		for (i = 0; i < m; i++)
			rp[i] = -1; // row penalties
		for (i = 0; i < n; i++)
			cp[i] = -1; // col penalties

		for (i = 0; i < m; i++) {
			k = 0;
			if (rf[i] != 1) {
				for (j = 0; j < n; j++) {
					if (cf[j] != 1)
						a[k++] = c[i][j];
				}
				if (k == 1)
					rp[i] = a[0];
				else {
					sort(a, k);
					rp[i] = a[1] - a[0]; // substraction of two min elements of row
				}
			}
		}
		for (i = 0; i < n; i++) {
			k = 0;
			if (cf[i] != 1) {
				for (j = 0; j < m; j++) {
					if (rf[j] != 1)
						a[k++] = c[j][i];
				}
				if (k == 1)
					cp[i] = a[0];
				else {
					sort(a, k);
					cp[i] = a[1] - a[0]; // substraction of two min elements of col
				}
			}
		}
		for (i = 0; i < m; i++)
			a[i] = rp[i]; // row
		for (j = 0; j < n; j++)
			a[i + j] = cp[j]; // col
		max = a[0];
		p = 0;
		for (i = 1; i < m + n; i++) // get max from all panelties
				{
			if (max < a[i]) {
				max = a[i];
				p = i;
			}
		}
		//cout << max << p;
		min = 1000;
		if (p > m - 1) // row min
				{
			p = p - m;
			if (cf[p] != 1) {
				for (i = 0; i < m; i++) // row loop
						{
					if (rf[i] != 1) {
						if (min > c[i][p]) {
							min = c[i][p];
							s = i;
							t = p;
						}
					}
				}
			}
		} else // col min
		{
			if (rf[p] != 1) {
				for (i = 0; i < n; i++) // col loop
						{
					if (cf[i] != 1) {
						if (min > c[p][i]) {
							min = c[p][i];
							s = p;			//storing index
							t = i;			//storing index
						}
					}
				}
			}
		}

		if (sup[s] < dem[t]) // allocate supply
				{
			sum += c[s][t] * sup[s];
			dem[t] -= sup[s];
			rf[s] = 1;
			b--;
		} else if (sup[s] > dem[t]) // allocate demand
				{
			sum += c[s][t] * dem[t];
			sup[s] -= dem[t];
			cf[t] = 1;
			d--;
		} else if (sup[s] == dem[t]) // balanced end condition
				{
			sum += c[s][t] * dem[t];
			cf[t] = 1;
			rf[s] = 1;
			b--;
			d--;
		}
	} // while
	cout << "\n\n Cost by VAM method :: " << sum << endl;
	sum = 0;
}

void Optimization::sort(int a[], int n) {
	int temp, j, k;
	for (j = 0; j < n; j++)
		for (k = j + 1; k < n; k++)
			if (a[j] > a[k]) {
				temp = a[j];
				a[j] = a[k];
				a[k] = temp;
			}
}
