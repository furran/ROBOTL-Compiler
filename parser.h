#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include <vector>

struct node;

class Parser{
private:
	std::vector<Token> tokenBuffer;
public:

	Parser();
	virtual ~Parser();

	void loadBuffer(std::vector<Token>& v);
	void error();
	Token getNextToken();
	node * parse(std::vector<Token> &v);
};

#endif
