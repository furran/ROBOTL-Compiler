#include "lexer.h"
#include <vector>

using namespace std;

int main(){
	string filename;

	cout << "Digite o nome do arquivo: " << endl;
	cin >> filename;

	Lexer lexer(filename);

	std::vector<std::string> padroes;
	padroes.reserve(table.size());
	std::vector<Token> tokens;
	tokens.reserve(table.size());

	for(auto kv : table) {
	    padroes.push_back(kv.first);
	    tokens.push_back(kv.second);
	}
	cout << "# Padroes: ";
	for(auto k : padroes){
		cout << k<< " | ";
	}
	cout << endl << "# Tags: ";
	for(auto v : tag){
			cout << v << " | ";
		}
	cout << endl;

	cout << "++++++++++++++" << endl;
	while(true){
		Token t = lexer.scan();
		int tipo = t.getTag();
		cout << "Token: < " << tag[tipo] << " , " << t.lexeme << " >\n";

		if(tipo == END_OF_FILE)break;
	}
	cout << "++++++++++++++" << endl;
	cout << "LINES READ: " << lexer.line << endl;
	cout << "sucesso" << endl;


}
