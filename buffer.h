
class Buffer{
public:
	static const unsigned int length = 4096;
	std::string buff;
	char *beginPtr;
	char *forward;
	int curIndex;
	Buffer()
	: buff(),  curIndex(0)
	{
	}
	char next(){
		char c = buff[curIndex++];
		return c;
	}

};




