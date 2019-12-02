#include <iostream>
#include <unordered_map>
#include <stack>
#include <vector>
#include "parser.h"
#include "tree.cpp"

//mais informacao sobre tabela sintatica e a gramatica adaptada(ll(1)) nos documentos excel e word, respectivamente

Parser::Parser(std::string filename)
:lexer(filename)
	{

	//++++ CRIA TABELA SINTATICA +++++

	//PROGRAMA
	analysisTable[std::make_pair(pPROGRAMA,PROGRAMAINICIO)] = {PROGRAMAINICIO,pDECLARACAO,EXECUCAOINICIO,pCOMANDOLISTA,FIMEXECUCAO,FIMPROGRAMA};
	//DECLARACAO
	//vazio
	analysisTable[std::make_pair(pDECLARACAO,DEFINAINSTRUCAO)] = {DEFINAINSTRUCAO,ID,REGRA1,COMO,pCOMANDO,pDECLARACAO}; // << REGRA 1
	analysisTable[std::make_pair(pDECLARACAO,VAZIO)] = {};
	//BLOCO
	analysisTable[std::make_pair(pBLOCO,INICIO)] = {INICIO,pCOMANDOLISTA,FIM};

	//COMANDOLISTA
	//vazio
	analysisTable[std::make_pair(pCOMANDOLISTA,INICIO)] = {pCOMANDO,pCOMANDOLISTA};
	analysisTable[std::make_pair(pCOMANDOLISTA,REPITA)] = {pCOMANDO,pCOMANDOLISTA};
	analysisTable[std::make_pair(pCOMANDOLISTA,ENQUANTO)] = {pCOMANDO,pCOMANDOLISTA};
	analysisTable[std::make_pair(pCOMANDOLISTA,SE)] = {pCOMANDO,pCOMANDOLISTA};
	analysisTable[std::make_pair(pCOMANDOLISTA,MOVA)] = {pCOMANDO,pCOMANDOLISTA};
	analysisTable[std::make_pair(pCOMANDOLISTA,VIRE)] = {pCOMANDO,pCOMANDOLISTA};
	analysisTable[std::make_pair(pCOMANDOLISTA,ID)] = {pCOMANDO,pCOMANDOLISTA};
	analysisTable[std::make_pair(pCOMANDOLISTA,PARE)] = {pCOMANDO,pCOMANDOLISTA};
	analysisTable[std::make_pair(pCOMANDOLISTA,FINALIZE)] = {pCOMANDO,pCOMANDOLISTA};
	analysisTable[std::make_pair(pCOMANDOLISTA,APAGUE)] = {pCOMANDO,pCOMANDOLISTA};
	analysisTable[std::make_pair(pCOMANDOLISTA,ACENDA)] = {pCOMANDO,pCOMANDOLISTA};
	analysisTable[std::make_pair(pCOMANDOLISTA,AGUARDE)] = {pCOMANDO,pCOMANDOLISTA};
	analysisTable[std::make_pair(pCOMANDOLISTA,VAZIO)] = {};
	//COMANDO
	analysisTable[std::make_pair(pCOMANDO,INICIO)] = {pBLOCO};
	analysisTable[std::make_pair(pCOMANDO,REPITA)] = {pITERACAO};
	analysisTable[std::make_pair(pCOMANDO,ENQUANTO)] = {pLACO};
	analysisTable[std::make_pair(pCOMANDO,SE)] = {pCONDICIONAL};
	analysisTable[std::make_pair(pCOMANDO,MOVA)] = {pINSTRUCAO};
	analysisTable[std::make_pair(pCOMANDO,VIRE)] = {pINSTRUCAO};
	analysisTable[std::make_pair(pCOMANDO,ID)] = {pINSTRUCAO};
	analysisTable[std::make_pair(pCOMANDO,PARE)] = {pINSTRUCAO};
	analysisTable[std::make_pair(pCOMANDO,FINALIZE)] = {pINSTRUCAO};
	analysisTable[std::make_pair(pCOMANDO,APAGUE)] = {pINSTRUCAO};
	analysisTable[std::make_pair(pCOMANDO,ACENDA)] = {pINSTRUCAO};
	analysisTable[std::make_pair(pCOMANDO,AGUARDE)] = {pINSTRUCAO};
	//ITERACAO
	analysisTable[std::make_pair(pITERACAO,REPITA)] = {REPITA,NUMERO,VEZES,pCOMANDO,FIMREPITA};
	//LACO
	analysisTable[std::make_pair(pLACO,ENQUANTO)] = {ENQUANTO,pCONDICAO,FACA,pCOMANDO,FIMPARA};
	//CONDICIONAL
	analysisTable[std::make_pair(pCONDICIONAL,SE)] = {SE,pCONDICAO,ENTAO,pCOMANDO,FIMSE,pCONDICIONALOPT};
	//CONDICIONALOPT
	//vazio
	analysisTable[std::make_pair(pCONDICIONALOPT,SENAO)] = {SENAO,pCOMANDO,FIMSENAO};
	analysisTable[std::make_pair(pCONDICIONALOPT,VAZIO)] = {};
	//INSTRUCAO
	analysisTable[std::make_pair(pINSTRUCAO,MOVA)] = {REGRA5,MOVA,pNUMEROOPT,pINSTRUCAOOPT}; // << REGRA 5
	analysisTable[std::make_pair(pINSTRUCAO,VIRE)] = {VIRE,PARA,pSENTIDO};
	analysisTable[std::make_pair(pINSTRUCAO,ID)] = {ID, REGRA2}; // << REGRA 2
	analysisTable[std::make_pair(pINSTRUCAO,PARE)] = {PARE};
	analysisTable[std::make_pair(pINSTRUCAO,FINALIZE)] = {FINALIZE};
	analysisTable[std::make_pair(pINSTRUCAO,APAGUE)] = {APAGUE,LAMPADA};
	analysisTable[std::make_pair(pINSTRUCAO,ACENDA)] = {ACENDA,LAMPADA};
	analysisTable[std::make_pair(pINSTRUCAO,AGUARDE)] = {AGUARDE,ATE,pCONDICAO};
	//INSTRUCAOOPT
	//VAZIO
	analysisTable[std::make_pair(pINSTRUCAOOPT,PASSOS)] = {PASSOS};
	analysisTable[std::make_pair(pINSTRUCAOOPT,VAZIO)] = {};
	//NUMEROOPT
	//VAZIO
	analysisTable[std::make_pair(pNUMEROOPT,NUMERO)] = {NUMERO};
	analysisTable[std::make_pair(pNUMEROOPT,VAZIO)] = {};
	//CONDICAO
	analysisTable[std::make_pair(pCONDICAO,ROBO)] = {pCONDICAOROBO};
	analysisTable[std::make_pair(pCONDICAO,LAMPADA)] = {pCONDICAOLAMPADA};
	analysisTable[std::make_pair(pCONDICAO,PASSOS)] = {pCONDICAOROBO};
	analysisTable[std::make_pair(pCONDICAO,FRENTE)] = {pCONDICAODIRECAO};
	analysisTable[std::make_pair(pCONDICAO,ESQUERDA)] = {pCONDICAODIRECAO};
	analysisTable[std::make_pair(pCONDICAO,DIREITA)] = {pCONDICAODIRECAO};
	//CONDICAOROBO
	analysisTable[std::make_pair(pCONDICAOROBO,ROBO)] = {ROBO,pESTADOROBO};
	//ESTADOROBO
	analysisTable[std::make_pair(pESTADOROBO,PRONTO)] = {PRONTO};
	analysisTable[std::make_pair(pESTADOROBO,OCUPADO)] = {OCUPADO};
	analysisTable[std::make_pair(pESTADOROBO,PARADO)] = {PARADO};
	analysisTable[std::make_pair(pESTADOROBO,MOVIMENTANDO)] = {MOVIMENTANDO};
	//CONDIAODIRECAO
	analysisTable[std::make_pair(pCONDICAODIRECAO,FRENTE)] = {FRENTE,ROBO,BLOQUEADA};
	analysisTable[std::make_pair(pCONDICAODIRECAO,ESQUERDA)] = {ESQUERDA,ROBO,BLOQUEADA};
	analysisTable[std::make_pair(pCONDICAODIRECAO,DIREITA)] = {DIREITA,ROBO,BLOQUEADA};
	//CONDICAOLAMPADA
	analysisTable[std::make_pair(pCONDICAOLAMPADA,LAMPADA)] = {LAMPADA,pESTADOLAMPADA,A,pDIRECAO};
	//DIRECAO
	analysisTable[std::make_pair(pDIRECAO,FRENTE)] = {FRENTE};
	analysisTable[std::make_pair(pDIRECAO,ESQUERDA)] = {ESQUERDA};
	analysisTable[std::make_pair(pDIRECAO,DIREITA)] = {DIREITA};
	//ESTADOLAMPADA
	analysisTable[std::make_pair(pESTADOLAMPADA,APAGADA)] = {APAGADA};
	analysisTable[std::make_pair(pESTADOLAMPADA,ACESA)] = {ACESA};
	//SENTIDO
	analysisTable[std::make_pair(pSENTIDO,ESQUERDA)] = {ESQUERDA, REGRA3}; // REGRA 3
	analysisTable[std::make_pair(pSENTIDO,DIREITA)] = {DIREITA, REGRA4}; // REGRA 4


}

Parser::~Parser() {

}

node * Parser::parse(){
	std::stack<node*> s;
	std::unordered_map<pair,std::vector<int>,hash_pair>::iterator it;
	std::vector<Token*> leaves;
	int index = 0;
	node *Z = new node;
	node *head = new node;//<<
	node *cur = head;
	node *pai = cur;
	node *tmp;

	head->token = new Token(pPROGRAMA,0,"");//<<
	Z->token = new Token($,0,"");

	s.push(Z);
	s.push(head);
	node* no= s.top();
	int x = s.top()->token->tag;
	Token *t;
	t = lexer.scan();

	while(x!=$){

		t = lexer.getCurrentToken();
		if(x==(*t).getTag()){ // caso 1
			s.pop();
			lexer.scan();
			cur->token = t;
			leaves.push_back(t);
			index++;

		}
		else if(isTerminal(x)){ // caso 2
			s.pop();
			lexer.scan();

			tmp = new node;
			tmp->token = t;
			cur->children.push_back(tmp);

			printf("ERRO::LINHA:%d: Terminal nao bate.\n", (*t).getLine());
		}
		else if (isNonTerminal(x)) {//caso 3
			pai = s.top();
			s.pop();
			it = analysisTable.find(std::make_pair(x, (*t).getTag()));
			if (it != analysisTable.end()) {
				node *arr[it->second.size()];
				for (int i = it->second.size() - 1; i >= 0; i--) {
					arr[i] = new node;
					(arr[i])->token = new Token(it->second[i],0,"");
					s.push(arr[i]);
				}
				cur->children.insert(cur->children.begin(), arr,arr + it->second.size());
			} else { //caso 4
				it = analysisTable.find(std::make_pair(x, VAZIO));
				if (it != analysisTable.end()) {
					tmp = new node;
					tmp->token = new Token(VAZIO,0,"");
					cur->children.push_back(tmp);
				} else
					printf("ERRO::LINHA:%d: Producao incapaz de gerar o token.\n",(*t).getLine());
			}
		}
		else if(isRegra(x)){
			if(index-5>=0)
			switch (x) {
			case REGRA1: {
				int var = index - 1;
				if (var >= 0 && symbolTable.count(leaves[var]->getLexeme()) == false) {
					symbolTable[leaves[var]->getLexeme()] = *leaves[var];
				} else
					printf(
							"ERRO::LINHA:%d: Mais de uma instrucao com o mesmo identicador foram declaradas.\n",
							leaves[var]->getLine());
				break;
			}
			case REGRA2: {
				int var = index - 1;
				if (var >= 0 && symbolTable.count(leaves[var]->getLexeme())== false) {
					printf(
							"ERRO::LINHA:%d: Referencia a instrucao nao declarada.\n",
							leaves[var]->getLine());
				}
				break;
			}
			case REGRA3: {
				int var = index - 4;
				if (var >= 0 && leaves[var]->getTag() == DIREITA) {
					printf(
							"ERRO::LINHA:%d: [VIRE PARA ESQUERDA] seguido por [VIRE PARA DIREITA].\n",
							leaves[var]->getLine());
				}
				break;
			}
			case REGRA4: {
				int var = index - 4;
				if (var >= 0 && leaves[var]->getTag() == ESQUERDA) {
					printf(
							"ERRO::LINHA:%d: [VIRE PARA DIREITA] seguido por [VIRE PARA ESQUERDA].\n",
							leaves[var]->getLine());
				}
				break;
			}
			case REGRA5: {
				int var = index - 1;
				if (var >= 0 && !(leaves[var]->getTag() == PRONTO)) {
					printf(
							"ERRO::LINHA:%d: [MOVA N] deve ser precedido por [AGUARDE ATE PRONTO]\n",
							leaves[var]->getLine());
				}
				break;
			}
			}
			s.pop();
		}
		cur = s.top();
		x = s.top()->token->getTag();
	}
	return head;//retorna raiz da arvore
}

