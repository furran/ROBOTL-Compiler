#include <iostream>
#include <vector>
#include "table.cpp"
/*
 * ROTINAS SEMANTICAS:
 * #1 VERIFICA SE ID JA FOI DECLARADA, SE NAO ADICIONA ID NA TABELA DE SIMBOLOS
 * #2 VERIFICA SE ID JA FOI DECLARADA
 * #3 "VIRE PARA ESQUERDA" NAO PODE SER SEGUIDO IMEDIATAMENTE POR "VIRE PARA DIREITA"
 * #4 "VIRE PARA DIREITA" NAO PODE SER SEGUIDO IMEDIATAMENTE POR "VIRE PARA ESQUERDA"
 * #5 "MOVA NUMBER" DEVE SER SEGUIDO POR "AGUARDE ATE CONDICAO"
 */


void analyse(node* n,std::vector<node*> &v){
	for (node * a : n->children) {
		analyse(a,v);
	}

	if (n->children.empty() && n->token.getTag() != VAZIO) {
		v.push_back(n);
	}
}

node * analyse(node * n) {
	std::vector<node*> v;
	for (node * a : n->children) {
		analyse(a, v);
	}

	for(int i=0;i<v.size();i++){
		switch (v[i]->token.getTag()) {
			case REGRA1: {
				if(symbolTable.count(v[i]->token.getLexeme()) == false){
					symbolTable[v[i-1]->token.getLexeme()] = v[i-1]->token;
				}
				else printf("ERRO::LINHA:%d: Mais de uma instrucao o com mesmo identicador foram detectadas.\n",v[i-1]->token.getLine());
				break;
			}
			case REGRA2: {
				if (symbolTable.count(v[i]->token.getLexeme()) == false) {
					printf("ERRO::LINHA:%d: Referencia a instrucao nao declarada.\n",v[i - 1]->token.getLine());
				}
				break;
			}
			case REGRA3: {
				int x = i-5;
				if(x>=0 && v[x]->token.getTag() == DIREITA){
					printf("ERRO::LINHA:%d: VIRE PARA ESQUERDA seguido por VIRE A DIREITA eh redundante.\n",v[i - 1]->token.getLine());
				}
				break;
			}
			case REGRA4: {
				int x = i - 5;
				if (x >= 0 && v[x]->token.getTag() == ESQUERDA) {
					printf("ERRO::LINHA:%d: VIRE PARA DIREITA seguido por VIRE A ESQUERDA eh redundante.\n",v[i - 1]->token.getLine());
				}
				break;
			}
			case REGRA5: {
				int x = i +1;
				if (!(x < v.size()) || !(v[x]->token.getTag() == AGUARDE)) {
					printf("ERRO::LINHA:%d: MOVA N deve ser seguido por AGUARDE ATE ...\n",v[i - 1]->token.getLine());
				}
				break;
			}

		}
	}


	printf("\n");


	return n;
}
