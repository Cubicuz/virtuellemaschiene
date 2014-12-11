#ifndef VirtuelleMaschieneInit
#define VirtuelleMaschieneInit
#include "FArray.h"
class VirtuelleMaschiene
{
public:
	VirtuelleMaschiene(char[]);
	virtual ~VirtuelleMaschiene();
	void printMem(short start, short end);
	void printReg();
	void run();
	void writeProfile(char []);
private:
	int profiler [4096];
	short programCounter;
	unsigned short memory [4096];
	unsigned short reg[16];
	unsigned short stack[4096];
	unsigned short* stackPointer;
};
#endif