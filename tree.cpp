
#include <vector>
#include <iostream>
#include "table.cpp"




typedef struct node{

	Token* token;

	std::vector<node*> children;
} node;

void printNode(std::string s, int i);
void printTree(node *n);
void printTree(node *n, int indetation);
void printLeaves(node* n);

void printNode(std::string s, int i){
	while(i--){
		printf("   ");
	}
	std::cout << "-" << s << std::endl;;
}

void printTree(node* n)
{
    printTree(n, 0);
}

void printTree(node* n, int indentation)
{

	printNode(debug[n->token->getTag()], indentation);
	for (auto a : n->children) {
		printTree(a, indentation + 1);
	}
}

void printLeaves(node* n){
	for (auto a : n->children) {
		printLeaves(a);
	}
	if(n->children.empty()) std::cout <<n->token->getLexeme() << std::endl;
}

