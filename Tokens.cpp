class Word {
public:
	const int tag;
	const char *lexeme;
	Word(int t, char *s){
		tag = t;
		lexeme = s;
	}
};

class Number {
public:
	const int tag;
	const int value;
	Number(int t, int v){
		tag = t;
		value = v;
	}
};
