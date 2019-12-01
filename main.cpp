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

	cout << "++++++++++++++" << endl;

	node * tree = parser.parse();

	cout << "++++++++++++++" << endl;
	printTree(tree);
	printf("##################\n");
	printf("##################\n");
	cout << "LINES READ: " << parser.lexer.getLinesRead() << endl;
	cout << "sucesso" << endl;

}
