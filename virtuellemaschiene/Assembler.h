#ifndef AssemblerInit
#define AssemblerInit
class Assembler
{
public:
	Assembler(char [], char[]);
	virtual ~Assembler();
//private:
static	int getOperation(char line[]);
};
#endif
