#ifndef LEXER_H_
#define LEXER_H_


#include "buffer.h"
#include "token.cpp"


class Lexer{
private:
	char peek;
	Token* curToken;
	Buffer buffer;
	int line;
	std::unordered_map<std::string, Token> reservedWords;
public:
	Lexer(std::string filename);
	int getLinesRead();
	void install(Token w);
	void deleteUntilDelimiter();
	Token* getCurrentToken();
	Token* scan();
};

#endif
