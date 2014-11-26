#include "Assembler.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
Assembler::Assembler(char inFileName[], char outFileName[])
{
		ifstream fin(inFileName, ios::in);
		ofstream fout(outFileName, ios::out);
		char lineIn[40];
		char lineOut[17];
		lineOut[16] = '\0';
		int op(0);
		while (!fin.eof()){
			for (int i = 0; i < 16; i++){
				lineOut[i] = '0';
			}
			fin.getline(lineIn, sizeof(lineIn));
			if (lineIn[0] != '/'){
				op = getOperation(lineIn);
				string param(lineIn);
				if ((op == 0) || (op == 13)){	//NOP RTS
				}
				else {
					param = param.substr(5, string::npos);
					cout << param << endl;
				}

				if ((op == 1) || ((op > 8) && (op < 13))){	//#WERT
					int wert = atoi(param.c_str());
					for (int i = 0; i < 12; i++){
						lineOut[11 - i] = (wert % 2) + 48;
						wert /= 2;
					}

				}
				else if ((op == 7) || (op == 8)){					// ein Parameter
					param = param.substr(1);
					int wert = atoi(param.c_str());
					for (int i = 0; i < 4; i++){
						lineIn[11 - i] = (wert % 2) + 48;
						wert /= 2;
					}
				}
				else if ((op >= 2) && (op <= 6)){											// zwei Parameter
					string param1 = param.substr(0, param.find(','));
					if ((param1.at(0) == '(') && (param1.at(param1.length() - 1) == ')')){	// To Mem
						cout << "klammer" << endl;
						lineOut[2] = '1';
						param1 = param1.substr(2, param1.length() - 3);
					}
					else {
						param1 = param1.substr(1);
					}
					int wert1 = atoi(param1.c_str());
					for (int i = 0; i < 4; i++){
						lineOut[11 - i] = (wert1 % 2) + 48;
						wert1 /= 2;
					}

					string param2 = param.substr(param.find(',') + 1, string::npos);
					if ((param2.at(0) == '(') && (param2.at(param2.length() - 1) == ')')){	// From Mem
						cout << "klammer" << endl;
						lineOut[3] = '1';
						param2 = param2.substr(2, param2.length() - 3);
					}
					else {
						param2 = param2.substr(1);
					}
					int wert2 = atoi(param2.c_str());
					for (int i = 0; i < 4; i++){
						lineOut[7 - i] = (wert2 % 2) + 48;
						wert2 /= 2;
					}
				}
				// Befehlsbits schreiben
				for (int i = 0; i < 4; i++){
					lineOut[15 - i] = (op % 2) + 48;
					op /= 2;
				}

				fout << lineOut << endl;
			}
		}
}


Assembler::~Assembler()
{
}

int Assembler::getOperation(char line[]){
	int operationChars = line[0];
	for (int i = 1; i < 4; i++){
		operationChars = operationChars << 8;
		operationChars += line[i];
	}
	int allOperations[] = {		
		1313820704,
		1280262468,
		1297045024,
		1094992928,
		1398096416,
		1297435680,
		1145656864,
		1347769160,
		1347375136,
		1246580768,
		1246321184,
		1246316576,
		1246974496,
		1381258016
	};
	for (int i = 0; i < 14; i++){
		if (operationChars == allOperations[i])
			return i;
	}
	return 0;
}