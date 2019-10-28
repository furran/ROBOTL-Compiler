#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include <vector>

struct node;

class Parser : public Lexer{
private:
	std::vector<Token> tokenBuffer;
	const unsigned int tokenBufferLength = 2048;
public:

	Parser(std::string filename);
	virtual ~Parser();

	void loadBuffer();
	void error();
	Token getNextToken();
	node * parse();
};

#endif
