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
	machine.writeProfile("code.txt");
	
	cout << endl;
	return 0;
}


