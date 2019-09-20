#ifndef TOKENS_H_
#define TOKENS_H_

class Word {
public:
	Word(int t, char *s);
	const int tag;
	const char *lexeme;
};

class Number {
public:
	Number(int t, int v);
	const int tag;
	const int value;
};

#endif /* TOKENS_H_ */
