#include <iostream>
#include "VirtuelleMaschiene.h"
using namespace std;

int main(){
	unsigned int a(0);
	cout << a << endl;
	a--;
	cout << a << std::endl;
	unsigned short b(0);
	b--;
	cout << b << endl;
	
	VirtuelleMaschiene machine("program.in");
	machine.printMem(0,10);
	
	machine.~VirtuelleMaschiene();
	return 0;
}


