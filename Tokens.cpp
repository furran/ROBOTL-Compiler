#define NUMBER 256
#define ID 257
#define KEYWORD 258

class Token {
public:
	const int tag;

	Token(int t)
	: tag(t)
	{
	}

	const int getTag(){
		return tag;
	}

};

class Number: public Token {
public:
	const int value;
	Number(int v)	: Token(NUMBER), value(v)
	{
	}

	const int getValue(){
		return value;
	}

};


class Word: public Token {
public:
	const std::string lexeme;
	Word(int t, const std::string s)
	: Token(t), lexeme(s)
	{
	}

	const std::string getLexeme(){
		return lexeme;
	}

};
