#include "ODE.hpp"

int main(){
	ODE o;
	o.getInput();
//	o.eulerSeries();
//	o.taylorSeries2();
//	o.taylorSeries3();
	o.RK();
	o.classicalRK();
	o.imRK2();
	o.imRK4();
}
