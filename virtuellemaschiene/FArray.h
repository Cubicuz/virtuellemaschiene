/************************************************************************
* \brief: This code implements the f-array, which is internally a two 
*         dimensional array. the two array-indices are computed as follows
*         index1 = index%1000 ; index2 = index/1000. One dimension is allocated
*         in the constructor. Each pointer of this dimenion points to a block of
*         memory, which is allocated if a value is stored or read out of the array.
*														
* (c) copyright by Jörn Fischer							
*                                                         
*															
* @autor: Prof.Dr.Jörn Fischer									
* @email: j.fischer@hs-mannheim.de									
*                                                                     
* @file : FArray.h                                                    
*************************************************************************/
/*******************************************************************
* The class FArray enables the user to create an Array of Huge size
* without reserving all the space.
* Blocks of 1024 elements are allocated if a value is read or written
* into the array!
*********************************************************************/
#include <stdio.h>
#include <stdlib.h>

#ifndef FARRAY_H
#define FARRAY_H

#define STEP_SIZE 1024

class  FArray
{
private:
	double dummy;
	double **value;	
	bool *reserved;
	unsigned long maxSize;

	
public:
	// constructor initializes the variables
	FArray(unsigned long maxSize)
	{
		value = new double*[(maxSize>>10)];
		for (unsigned long t=0;t< (maxSize>>10); t++){
			value[t] = NULL;
		}
		this->maxSize = maxSize;
	}
	// destructor frees the memory
	~FArray(){
		if (value != NULL){
			for (unsigned long t=0;t<maxSize/1024;t++){
				if (value[t]!= NULL){
					delete[] value[t];
				}
			}
			delete[] value;
		}
	}
/************************************************************************
* function: &operator[] 
*************************************************************************/
	// the & deals as reference, so that data may be read and written into the array
	double &operator[] (unsigned long index){
		//index = 0;
		if (index>maxSize-1 || index<0){
			printf("ERROR: Array-> Index too big or negative\n");
			system("pause");
			return dummy;
		}
		unsigned long index1 = index&1023;  // %STEP_SIZE;
		unsigned long index2 = index>>10;   // /STEP_SIZE;

		if (value[index2] == NULL){
			value[index2] = new double[STEP_SIZE];			
		}
		
		return value[index2][index1];
	}
};

#endif // FARRAY_H


