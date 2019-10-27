#ifndef TOKEN_H_
#define TOKEN_H_

#include <string>

class Token {
public:
	int tag;
	std::string lexeme;

	Token()
	: tag(-1)
	{
	}

	Token(int t, std::string lex)
	: tag(t), lexeme(lex)
	{
	}

	int getTag(){
		return tag;
	}

	const std::string getLexeme(){
		return lexeme;
	}

};

#endif
