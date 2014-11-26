#include <iostream>
#include <fstream>
#include "VirtuelleMaschiene.h"
#include "Assembler.h"
using namespace std;

int main(){
	Assembler test("code.txt", "output.txt");
	VirtuelleMaschiene machine("output.txt");
	machine.run();
	machine.printMem(995, 1025);
	
//	machine.printReg();
	cout << endl;
/*	char blabla[40];
	ofstream file("output.txt", ios::out);
	ifstream infile("code.txt", ios::in);
	while (!infile.eof()){
		infile.getline(blabla, 40);
		cout << Assembler::getOperation(blabla) << endl;
	}
	
	
	unsigned int a(0);
	cout << a << endl;
	a--;
	cout << a << std::endl;
	unsigned short b(0);
	b--;
	cout << b << endl;
	VirtuelleMaschiene machine("program.in");
	machine.printMem(0,10);
	machine.run();
	machine.run();

	machine.printMem(0, 20);
	machine.printReg();
	
	machine.~VirtuelleMaschiene();
	return 0;
	*/
	return 0;
}


