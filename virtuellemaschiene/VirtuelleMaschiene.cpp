#include "VirtuelleMaschiene.h"
#include <fstream>
#include <iostream>
using namespace std;

VirtuelleMaschiene::VirtuelleMaschiene(char fileLocation [])
{
	for (short i = 0; i < 16; i++){
		reg[i] = 0;
	}
	for (short i = 0; i < 4096; i++){
		memory[i] = 0;
	}
	ifstream f(fileLocation, ios::in);
	char c[80];
	unsigned short progLine(0);
	short memIndex(0);
	while (!f.eof()){
		f.getline(c, sizeof(c));
		progLine = 0;
		for (short i = 0; i < 16; i++){
			progLine += (c[i]-48)*pow(2,15-i);
//			cout << progLine << endl;
		}
//		cout << progLine<< endl;
		memory[memIndex++] = progLine;
	}
	f.close();
}

void VirtuelleMaschiene::printMem(short start, short end){
	for (short i = start; i < end; i++){
		cout << "Zelle	" << i << ":" << memory[i] << endl;
	}
}

VirtuelleMaschiene::~VirtuelleMaschiene()
{
}
