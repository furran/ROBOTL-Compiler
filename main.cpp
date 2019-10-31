#include <vector>
#include <unordered_map>
#include "lexer.cpp"
#include "table.cpp"
#include "buffer.cpp"
#include "parser.cpp"
#include "semantic.cpp"

using namespace std;

int main(){
	string filename;

	cout << "Digite o nome do arquivo: " << endl;
	cin >> filename;
	Lexer lexer(filename);
	vector<Token> v;
	int length = 4096;
	v.resize(length);

	int i =  0;
	int j = 1;
	while(true){

		v[i] =lexer.scan();
		if(v[i].getTag()== END_OF_FILE) break;
		i++;
		if(i >= 4096) {
			j++;
			v.resize(length*j);
		}

	}

	Parser parser;

	cout << "++++++++++++++" << endl;

	node * tree = parser.parse(v);

	cout << "++++++++++++++" << endl;
	cout << "LINES READ: " << lexer.line << endl;
	cout << "sucesso" << endl;
	printTree(tree);
	printf("##################\n");
	printLeaves(tree);
	printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
	analyse(tree);

}
