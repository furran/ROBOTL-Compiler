#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include <vector>
#include "lexer.h"

struct node;

class Parser{
public:
	Lexer lexer;
	Parser(std::string filename);
	virtual ~Parser();
	Token getNextToken();
	node * parse();
};

#endif
