#pragma once
class VirtuelleMaschiene
{
public:
	VirtuelleMaschiene(char[]);
	virtual ~VirtuelleMaschiene();
	void printMem(short start, short end);
private:
	unsigned short memory [4096];
	unsigned short reg[16];
};

