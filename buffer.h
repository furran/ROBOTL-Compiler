
class Buffer{
private:
	std::string* getOtherBuffer();

public:
	static const unsigned int length = 4096;
	std::string *curBuff;
	std::string buff1;
	std::string buff2;
	int beginLex;
	int forward;
	Buffer()
	: buff1(),buff2(), forward(0), beginLex(0)
	{
		curBuff = &buff1;
		buff1.resize(length);
		buff2.resize(length);
	}
	char next();
	void retract();
	void fail();
	char lookAhead();
	void beginLexeme();
	std::string getLexeme();

};

std::string* Buffer::getOtherBuffer(){
	if(curBuff == &buff1){
		return &buff2;
	}
	else if(curBuff == &buff2){
		return &buff1;
	}
	printf("error:: Buffer::getOtherBuffer() failed. (in file  >> token.cpp <<)\n");
	return NULL;

}
//esse codigo ta mangueado mas fzer o q
char Buffer::next(){
	int x = forward;
	std::string * buff = curBuff;
	forward++;
	if(forward==length){
		forward = 0;
		curBuff = this->getOtherBuffer();
	}
	return buff->operator [](x);
}

void Buffer::retract(){
	forward--;
}

void Buffer::fail(){
	forward=beginLex;
}

char Buffer::lookAhead(){
	return curBuff->operator [](forward);
}

void Buffer::beginLexeme(){
	beginLex = forward;
}

std::string Buffer::getLexeme(){
	if(forward<=beginLex){
		return (this->getOtherBuffer())->substr(beginLex,length-beginLex)+
				curBuff->substr(0, forward);
	}
	else return curBuff->substr(beginLex, forward-beginLex);
}




