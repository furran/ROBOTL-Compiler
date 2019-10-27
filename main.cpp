#include <vector>
#include <unordered_map>
#include "lexer.cpp"
#include "table.cpp"
#include "buffer.cpp"
#include "parser.cpp"


using namespace std;

int main(){
	string filename;

	cout << "Digite o nome do arquivo: " << endl;
	cin >> filename;
	Parser parser(filename);

	unordered_map<int,int> m;

	m[1] = 2;

	m[1] = 10;

	cout << m[1] << endl;

	cout << "++++++++++++++" << endl;

	parser.parse();


	cout << "++++++++++++++" << endl;
	cout << "LINES READ: " << parser.line << endl;
	cout << "sucesso" << endl;


}
