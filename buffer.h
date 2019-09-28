
class Buffer{
private:
	std::string* getOtherBuffer();

public:
	static const unsigned int length = 4096;
	std::string *curBuff;
	std::string buff1;
	std::string buff2;
	int beginLex;
	int curIndex;
	Buffer()
	: buff1(),buff2(), curIndex(0)
	{
		curBuff = &buff1;
		buff1.resize(length);
		buff2.resize(length);
	}
	char next();
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
	int x = curIndex;
	std::string * buff = curBuff;
	curIndex++;
	if(curIndex==length){
		curIndex = 0;
		curBuff = this->getOtherBuffer();
	}
	return buff->operator [](x);
}

char Buffer::lookAhead(){
	return curBuff->operator [](curIndex);
}

void Buffer::beginLexeme(){
	beginLex = curIndex;
}

std::string Buffer::getLexeme(){
	if(curIndex<=beginLex){
		return (this->getOtherBuffer())->substr(beginLex,length-beginLex)+
				curBuff->substr(0, curIndex);
	}
	else return curBuff->substr(beginLex, curIndex-beginLex);
}




