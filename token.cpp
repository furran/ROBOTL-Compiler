#ifndef TOKEN_CPP_
#define TOKEN_CPP_

#include <string>

class Token {
public:
	int tag;
	int line;
	int value;
	std::string lexeme;

	Token()
	: tag(-1)
	{
	}

	Token(int t,int l, std::string lex)
	: tag(t), line(l), value(0), lexeme(lex)
	{
	}

	int getTag(){
		return tag;
	}

	int getLine(){
		return line;
	}

	std::string getLexeme(){
		return lexeme;
	}

	void setValue(int v){
		value = v;
	}

	int getValue(){
		return value;
	}
};

#endif
