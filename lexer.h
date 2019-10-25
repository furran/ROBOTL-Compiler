#ifndef LEXER_H_
#define LEXER_H_


#include "buffer.h"
#include "token.cpp"


class Lexer{
private:
	char peek;

public:
	int line;
	Buffer buffer;

	Lexer(std::string filename);
	void install(Token w);
	void deleteUntilDelimiter();
	Token scan();
};

#endif
