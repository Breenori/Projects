#ifndef TEXT_CODER_H
#define TEXT_CODER_H
#include<iostream>
#include "coding_token.h"

class TextCoder {
private:
	CodingToken cd;
public:
	TextCoder() 
	{
		cd = CodingToken("testfile.txt");
		cd.print_frequency_table();
	}
};

#endif