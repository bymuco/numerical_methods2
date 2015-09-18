#include "Optimization.hpp"

int main() {
	int ch;
	Optimization o;
	o.getInput();
	while (1) {
		cout << "\n ________________ MENU ________________";;
		cout << "\n 1. North-West Corner Method";
		cout << "\n 2. Least-Cost Method";
		cout << "\n 3. Vogel's Approximation Method";
		cout << "\n\t Enter your choice :: ";
		cin >>  ch;
		switch (ch) {
		case 1:
			o.northwest();
			break;
		case 2:
			o.leastcost();
			break;
		case 3:
			o.vam();
			break;
		default:
			exit(0);
		}
	}
	return 0;
}
