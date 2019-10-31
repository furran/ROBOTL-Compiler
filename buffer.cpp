#include "buffer.h"

Buffer::Buffer(std::string filename) :
		length(4096), buff1(), buff2(), beginLex(0), forward(0)
{
	buff1.resize(length);
	buff2.resize(length);
	file.open(filename, std::ios::in | std::ios::binary);
	int length = this->length;
	if (file) {
		file.read(&buff1[0], length);
		if (file.eof()) {
			int p = file.gcount();
			buff1[p] = -1;
		}
		transform(buff1.begin(), buff1.end(), buff1.begin(), ::tolower);
	} else {
		std::cout << "ERRO:: Falha ao abrir o arquivo: >> " << filename
				<< " << " << std::endl;
		buff1[0] = -1;
	}
	curBuff = &buff1;
}

std::string* Buffer::getOtherBuffer(){

	if(curBuff == &buff1){
		return &buff2;
	}
	else if(curBuff == &buff2){
		return &buff1;
	}
	printf("error:: Buffer::getOtherBuffer() falhou. (in file  >> token.cpp <<)\n");
	return NULL;

}

void Buffer::load(){
	int length = this->length;
	if (file) {
		file.read(&curBuff->operator [](0), length);
		transform(curBuff->begin(), curBuff->end(), curBuff->begin(), ::tolower);
		if(file.eof()){
			int howManyLeft = file.gcount();
			(*curBuff)[howManyLeft] = -1;
		}
	}
}

char Buffer::next(){
	int x = forward;
	std::string * buff = curBuff;
	forward++;
	if(forward==length){
		forward = 0;
		curBuff = this->getOtherBuffer();
		this->load();
	}
	return (*buff)[x];
}

void Buffer::retract(){
	forward--;
}

void Buffer::fail(){
	forward=beginLex;
}

char Buffer::lookAhead(){
	return (*curBuff)[forward];
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

