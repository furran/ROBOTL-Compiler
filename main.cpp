#include "lexer.h"
#include <vector>

using namespace std;

int main(){
	string filename;
	Buffer buffer;
	cout << "lol" << endl;
	filename = "teste.txt";

	int buff_length = buffer.length;
	std::ifstream in(filename, std::ios::in | std::ios::binary);

	int p;
	if (in)
	{
		in.seekg(0, std::ios::end);
		int size = in.tellg();
		in.seekg(0, std::ios::beg);
		buffer.buff.resize(buffer.length);

		p =min(buff_length, size);

		in.read(&buffer.buff[0], min(buff_length, size));
		in.close();
	}

	buffer.buff[p] = 0;

	cout << "BUFFER: " << buffer.buff << endl;

	Lexer lexer(buffer);

	std::vector<std::string> keys;
	keys.reserve(lexer.table.size());
	std::vector<Token> vals;
	vals.reserve(lexer.table.size());

	for(auto kv : lexer.table) {
	    keys.push_back(kv.first);
	    vals.push_back(kv.second);
	}

	for(auto k : keys){
		cout << k<< " | ";
	}
	cout << endl;
	for(auto v : vals){
			cout << v.tag << " | ";
		}
	cout << endl;
	while(buff_length--){
		Token t = lexer.scan();
		int tag = t.getTag();
			cout << "tag" << tag << "\n";

		if(tag == 0)break;
	}

	cout << "sucesso xd?" << endl;


}
