
#include <vector>
#include <iostream>
#include "table.cpp"




typedef struct node{

	int token;

	std::vector<node*> children;
} node;

void printNode(std::string s, int i);
void printTree(node *n);
void printTree(node *n, int indetation);

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

    printNode(debug[n->token], indentation);
    for(auto a : n->children)
    {
        printTree(a, indentation + 1);
    }
}


