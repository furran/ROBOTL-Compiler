#define NUMBER 256
#define ID 257
#define KEYWORD 258

class Token {
public:
	const int tag;
	const std::string lexeme;
	Token(int t, std::string lex)
	: tag(t), lexeme(lex)
	{
	}

	const int getTag(){
		return tag;
	}

	const std::string getLexeme(){
		return lexeme;
	}

};
