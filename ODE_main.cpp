#include "ODE.hpp"

int main() {
	ODE o;
	int ch;
	o.getInput();
	while (1) {
		ch = o.menu();
		switch (ch) {
		case 1:
			o.eulerSeries();
			o.plot();
			break;
		case 2:
			o.taylorSeries2();
			o.plot();
			break;
		case 3:
			o.taylorSeries3();
			o.plot();
			break;
		case 4:
			o.improvedTangent();
			o.plot();
			break;
		case 5:
			o.eulerCauchy();
			o.plot();
			break;
		case 6:
			o.NystromMethod();
			o.plot();
			break;
		case 7:
			o.HeunMethod();
			o.plot();
			break;
		case 8:
			o.ClassicalMethod();
			o.plot();
			break;
		case 9:
			o.RK();
			o.plot();
			break;
		case 10:
			o.classicalRK();
			o.plot();
			break;
		case 11:
			o.imRK2();
			o.plot();
			break;
		case 12:
			o.imRK4();
			o.plot();
			break;
			/*	o.AdamsBashforth1();
			 o.plot();
			 o.AdamsBashforth2();
			 o.plot();
			 o.AdamsBashforth3();
			 o.plot();
			 o.NystromMethod1();
			 o.plot();
			 o.NystromMethod2();
			 o.plot();
			 //o.AdamsMoulton1();
			 */
		default:
			cout << "choose valid menu...!";
		}
	}
}
