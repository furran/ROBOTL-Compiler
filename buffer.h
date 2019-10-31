#ifndef BUFFER_H_
#define BUFFER_H_

#include <iostream>
#include <fstream>

class Buffer{
private:
	std::string* getOtherBuffer();
	void load();
public:
	const unsigned int length;
	std::ifstream file;
	std::string *curBuff;
	std::string buff1;
	std::string buff2;
	int beginLex;
	int forward;
	Buffer(std::string filename);

	char next();
	void retract();
	void fail();
	char lookAhead();
	void beginLexeme();
	std::string getLexeme();
};

#endif

