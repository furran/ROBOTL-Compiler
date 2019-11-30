#ifndef LEXER_H_
#define LEXER_H_


#include "buffer.h"
#include "token.cpp"


class Lexer{
private:
	char peek;
	Token curToken;
public:
	int line;
	Buffer buffer;

	Lexer(std::string filename);
	Token getCurrentToken();
	void install(Token w);
	void deleteUntilDelimiter();
	Token scan();
};

#endif
