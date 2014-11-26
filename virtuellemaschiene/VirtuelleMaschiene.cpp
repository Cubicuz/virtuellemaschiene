#include "VirtuelleMaschiene.h"
#include <fstream>
#include <iostream>
using namespace std;

enum CMD
{
	NOP,
	LOAD,
	MOV,
	ADD,
	SUB,
	MUL,
	DIV,
	PUSH,
	POP,
	JMP,
	JIZ,
	JIH,
	JSR,
	RTS
};

void VirtuelleMaschiene::run(){
	while (true){
		switch (memory[programCounter] & 0xF)
		{
		case NOP:	//NOP
			break;
		case LOAD:	//LOAD
			reg[0] = (memory[programCounter] >> 4);
			break;
		case MOV:	//MOV
			switch ((memory[programCounter] >> 12) & 0x3)
			{
			case 0:
				reg[((memory[programCounter] & 0xF0) >> 4)] = reg[((memory[programCounter] & 0xF00) >> 8)];
				break;
			case 1: // From Mem
				reg[((memory[programCounter] & 0xF0) >> 4)] = memory[reg[((memory[programCounter] & 0xF00) >> 8)]];
				break;
			case 2: // To Mem
				memory[reg[((memory[programCounter] & 0xF0) >> 4)]] = reg[((memory[programCounter] & 0xF00) >> 8)];
				break;
			case 3: // From Mem To Mem
				memory[reg[((memory[programCounter] & 0xF0) >> 4)]] = memory[reg[((memory[programCounter] & 0xF00) >> 8)]];
				break;
			default:
				cout << "MOV fehler";
				break;
			}
			break;
		case ADD:	//ADD
			reg[((memory[programCounter] & 0xF0) >> 4)] += reg[((memory[programCounter] & 0xF00) >> 8)];
			break;
		case SUB:	//SUB
			reg[((memory[programCounter] & 0xF0) >> 4)] -= reg[((memory[programCounter] & 0xF00) >> 8)];
			break;
		case MUL:	//MUL
			reg[((memory[programCounter] & 0xF0) >> 4)] *= reg[((memory[programCounter] & 0xF00) >> 8)];
			break;
		case DIV:	//DIV
			reg[((memory[programCounter] & 0xF0) >> 4)] /= reg[((memory[programCounter] & 0xF00) >> 8)];
			break;
		case PUSH:	//PUSH
			if ((stackPointer - stack) > 15){
				cout << "stack ist voll";
			}
			else {
				*stackPointer = reg[((memory[programCounter] & 0xF0) >> 4)];
				stackPointer++;
			}
			break;
		case POP:	//POP
			if ((stackPointer - stack) == 0){
				cout << "stack ist leer";
			}
			else {
				reg[((memory[programCounter] & 0xF0) >> 4)] = *stackPointer;
				stackPointer--;
			}
			break;
		case JMP:	//JMP
			programCounter = (memory[programCounter] >> 4)-1;
			break;
		case JIZ:	//JIZ
			if (reg[0] == 0) {
				programCounter = (memory[programCounter] >> 4) - 1;
			}
			break;
		case JIH:	//JIH
			if (reg[0] != 0){
				programCounter = (memory[programCounter] >> 4) - 1;
			}
			break;
		case JSR:	//JSR
			if ((stackPointer - stack) > 4095){
				cout << "subStack voll";
			}
			else {
				*stackPointer = programCounter;
				stackPointer++;
				for (int i = 0; i < 16; i++){
					*stackPointer = reg[i];
					reg[i] = 0;
					stackPointer++;
				}
				programCounter = (memory[programCounter] >> 4)-1;
			}
			break;
		case RTS:	//RTS
			if (stack == stackPointer)
				return;
			for (int i = 15; i >= 0; i--){
				stackPointer--;
				reg[i] = *stackPointer;
			}
			stackPointer--;
			programCounter = *stackPointer;
			break;
		default:
			cout << "shit just got realy real" << endl;
			break;
		}
		cout << programCounter << endl;
		programCounter++;
		if (programCounter > 4090){
			cout << "PC over 4000";
			return;
		}
	}
}
VirtuelleMaschiene::VirtuelleMaschiene(char fileLocation[])
: programCounter(0), stackPointer(stack)
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

void VirtuelleMaschiene::printReg(void){
	for (short i(0); i < 16; i++){
		cout << "Reg " << i << ":" << reg[i] << endl;
	}
}

VirtuelleMaschiene::~VirtuelleMaschiene()
{
}


