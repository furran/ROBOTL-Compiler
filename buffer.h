
class Buffer{
private:
	std::string* getOtherBuffer();
	void load();
public:
	const unsigned int length = 4096;
	std::ifstream file;
	std::string *curBuff;
	std::string buff1;
	std::string buff2;
	int beginLex;
	int forward;
	Buffer(std::string filename)
	: buff1(),buff2(), forward(0), beginLex(0)
	{
		buff1.resize(length);
		buff2.resize(length);
		file.open(filename, std::ios::in | std::ios::binary);
		int length = this->length;
		int size;
		if (file) {
			file.read(&buff1[0], length);
			if(file.eof()){
				int p = file.gcount();
				buff1[p] = END_FILE;
			}
		}
		else std::cout << "ERRO:: Falha ao abrir o arquivo: >> " << filename << " << " << std::endl;
		curBuff = &buff1;
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

void Buffer::load(){
	int p;
	int length = this->length;
	if (file) {
		file.read(&curBuff->operator [](0), length);
		if(file.eof()){
			int howManyLeft = file.gcount();
			std::cout << "HOOOOOOOOOOW MANY LEEEEEEEEEEFT: " << howManyLeft << std::endl;//remove this
			curBuff->operator [](howManyLeft) = END_FILE;
		}
	}
}

//esse codigo ta mangueado mas fzer o q
char Buffer::next(){
	int x = forward;
	std::string * buff = curBuff;
	forward++;
	if(forward==length){
		forward = 0;
		curBuff = this->getOtherBuffer();
		this->load();
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




