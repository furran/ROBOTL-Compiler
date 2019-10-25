#ifndef TOKEN_H_
#define TOKEN_H_

class Token {
public:
	int tag;
	const std::string lexeme;
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
