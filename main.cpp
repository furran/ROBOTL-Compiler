#include "lexer.h"
#include <vector>

using namespace std;

int main(){
	Lexer lexer("teste.txt");

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

	cout << "LOLE: " << lexer.buffer.curBuff->operator [](1) << endl;

	cout << "++++++++++++++" << endl;
	while(true){
		Token t = lexer.scan();
		int tag = t.getTag();

		cout << "tag:" << tag << "\n";

		if(tag == END_FILE)break;
	}
	cout << "++++++++++++++" << endl;
	cout << "LINES READ: " << lexer.line << endl;
	cout << "sucesso xd?" << endl;


}
