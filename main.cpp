#include "lexer.h"
#include <vector>

using namespace std;

int main(){
	string filename;
	Buffer buffer;
	cout << "lol" << endl;
	filename = "teste.txt";
	string s = "OMEGA";
	string* ptr = &s;
	cout << ptr->operator [](2) << endl;
	int buff_length = buffer.length;
	std::ifstream in(filename, std::ios::in | std::ios::binary);

	int p;
	if (in)
	{
		in.seekg(0, std::ios::end);
		int size = in.tellg();
		in.seekg(0, std::ios::beg);

		p =min(buff_length, size);

		in.read(&buffer.buff1[0], buff_length);
		in.close();
	}

	buffer.buff1[p] = END_FILE;

	cout << "BUFFER: " << *buffer.curBuff << endl;

	Lexer lexer(buffer);

	std::vector<std::string> lexemes;
	lexemes.reserve(table.size());
	std::vector<Token> tokens;
	tokens.reserve(table.size());

	for(auto kv : table) {
	    lexemes.push_back(kv.first);
	    tokens.push_back(kv.second);
	}

	for(auto k : lexemes){
		cout << k<< " | ";
	}
	cout << endl;
	for(auto v : tokens){
			cout << v.tag << " | ";
		}
	cout << endl;

	cout << "LOLE: " << buffer.curBuff->operator [](1) << endl;

	cout << "++++++++++++++" << endl;
	while(buff_length--){
		Token t = lexer.scan();
		int tag = t.getTag();

		cout << "tag:" << tag << "\n";

		if(tag == 0)break;
	}
	cout << "++++++++++++++" << endl;
	cout << "LINES READ: " << lexer.line << endl;
	cout << "sucesso xd?" << endl;


}
