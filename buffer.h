
class Buffer{
public:
	static const unsigned int length = 4096;
	std::string buff;
	char *beginPtr;
	int forward;
	int curIndex;
	Buffer()
	: buff(),  curIndex(0), forward(1)
	{
		buff.resize(length);
	}
	char next(){
		forward++;
		return buff[curIndex++];
	}

	char lookAhead(){
		return buff[forward];
	}

};




