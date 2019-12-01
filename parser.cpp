#include <iostream>
#include <unordered_map>
#include <stack>
#include <vector>
#include "parser.h"
#include "tree.cpp"

//mais informacao sobre tabela sintatica e a gramatica adaptada(ll(1)) nos documentos excel e word, respectivamente


typedef std::pair<int,int> pair;
//FUNCAO HASH PARA PAR DE CHAVES
struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const std::pair<T1, T2>& p) const
    {
        auto hash1 = std::hash<T1>{}(p.first);
        auto hash2 = std::hash<T2>{}(p.second);
        return hash1 ^ hash2;
    }
};

std::unordered_map<pair,std::vector<int>,hash_pair> map;


Parser::Parser(std::string filename)
:lexer(filename)
	{

	//++++ CRIA TABELA SINTATICA +++++

	//PROGRAMA
	map[std::make_pair(pPROGRAMA,PROGRAMAINICIO)] = {PROGRAMAINICIO,pDECLARACAO,EXECUCAOINICIO,pCOMANDOLISTA,FIMEXECUCAO,FIMPROGRAMA};
	//DECLARACAO
	//vazio
	map[std::make_pair(pDECLARACAO,DEFINAINSTRUCAO)] = {DEFINAINSTRUCAO,ID,REGRA1,COMO,pCOMANDO,pDECLARACAO}; // << REGRA 1
	map[std::make_pair(pDECLARACAO,VAZIO)] = {};
	//BLOCO
	map[std::make_pair(pBLOCO,INICIO)] = {INICIO,pCOMANDOLISTA,FIM};

	//COMANDOLISTA
	//vazio
	map[std::make_pair(pCOMANDOLISTA,INICIO)] = {pCOMANDO,pCOMANDOLISTA};
	map[std::make_pair(pCOMANDOLISTA,REPITA)] = {pCOMANDO,pCOMANDOLISTA};
	map[std::make_pair(pCOMANDOLISTA,ENQUANTO)] = {pCOMANDO,pCOMANDOLISTA};
	map[std::make_pair(pCOMANDOLISTA,SE)] = {pCOMANDO,pCOMANDOLISTA};
	map[std::make_pair(pCOMANDOLISTA,MOVA)] = {pCOMANDO,pCOMANDOLISTA};
	map[std::make_pair(pCOMANDOLISTA,VIRE)] = {pCOMANDO,pCOMANDOLISTA};
	map[std::make_pair(pCOMANDOLISTA,ID)] = {pCOMANDO,pCOMANDOLISTA};
	map[std::make_pair(pCOMANDOLISTA,PARE)] = {pCOMANDO,pCOMANDOLISTA};
	map[std::make_pair(pCOMANDOLISTA,FINALIZE)] = {pCOMANDO,pCOMANDOLISTA};
	map[std::make_pair(pCOMANDOLISTA,APAGUE)] = {pCOMANDO,pCOMANDOLISTA};
	map[std::make_pair(pCOMANDOLISTA,ACENDA)] = {pCOMANDO,pCOMANDOLISTA};
	map[std::make_pair(pCOMANDOLISTA,AGUARDE)] = {pCOMANDO,pCOMANDOLISTA};
	map[std::make_pair(pCOMANDOLISTA,VAZIO)] = {};
	//COMANDO
	map[std::make_pair(pCOMANDO,INICIO)] = {pBLOCO};
	map[std::make_pair(pCOMANDO,REPITA)] = {pITERACAO};
	map[std::make_pair(pCOMANDO,ENQUANTO)] = {pLACO};
	map[std::make_pair(pCOMANDO,SE)] = {pCONDICIONAL};
	map[std::make_pair(pCOMANDO,MOVA)] = {pINSTRUCAO};
	map[std::make_pair(pCOMANDO,VIRE)] = {pINSTRUCAO};
	map[std::make_pair(pCOMANDO,ID)] = {pINSTRUCAO};
	map[std::make_pair(pCOMANDO,PARE)] = {pINSTRUCAO};
	map[std::make_pair(pCOMANDO,FINALIZE)] = {pINSTRUCAO};
	map[std::make_pair(pCOMANDO,APAGUE)] = {pINSTRUCAO};
	map[std::make_pair(pCOMANDO,ACENDA)] = {pINSTRUCAO};
	map[std::make_pair(pCOMANDO,AGUARDE)] = {pINSTRUCAO};
	//ITERACAO
	map[std::make_pair(pITERACAO,REPITA)] = {REPITA,NUMERO,VEZES,pCOMANDO,FIMREPITA};
	//LACO
	map[std::make_pair(pLACO,ENQUANTO)] = {ENQUANTO,pCONDICAO,FACA,pCOMANDO,FIMPARA};
	//CONDICIONAL
	map[std::make_pair(pCONDICIONAL,SE)] = {SE,pCONDICAO,ENTAO,pCOMANDO,FIMSE,pCONDICIONALOPT};
	//CONDICIONALOPT
	//vazio
	map[std::make_pair(pCONDICIONALOPT,SENAO)] = {SENAO,pCOMANDO,FIMSENAO};
	map[std::make_pair(pCONDICIONALOPT,VAZIO)] = {};
	//INSTRUCAO
	map[std::make_pair(pINSTRUCAO,MOVA)] = {MOVA,pNUMEROOPT,pINSTRUCAOOPT, REGRA5}; // << REGRA 5
	map[std::make_pair(pINSTRUCAO,VIRE)] = {VIRE,PARA,pSENTIDO};
	map[std::make_pair(pINSTRUCAO,ID)] = {ID, REGRA2}; // << REGRA 2
	map[std::make_pair(pINSTRUCAO,PARE)] = {PARE};
	map[std::make_pair(pINSTRUCAO,FINALIZE)] = {FINALIZE};
	map[std::make_pair(pINSTRUCAO,APAGUE)] = {APAGUE,LAMPADA};
	map[std::make_pair(pINSTRUCAO,ACENDA)] = {ACENDA,LAMPADA};
	map[std::make_pair(pINSTRUCAO,AGUARDE)] = {AGUARDE,ATE,pCONDICAO};
	//INSTRUCAOOPT
	//VAZIO
	map[std::make_pair(pINSTRUCAOOPT,PASSOS)] = {PASSOS};
	map[std::make_pair(pINSTRUCAOOPT,VAZIO)] = {};
	//NUMEROOPT
	//VAZIO
	map[std::make_pair(pNUMEROOPT,NUMERO)] = {NUMERO};
	map[std::make_pair(pNUMEROOPT,VAZIO)] = {};
	//CONDICAO
	map[std::make_pair(pCONDICAO,ROBO)] = {pCONDICAOROBO};
	map[std::make_pair(pCONDICAO,LAMPADA)] = {pCONDICAOLAMPADA};
	map[std::make_pair(pCONDICAO,PASSOS)] = {pCONDICAOROBO};
	map[std::make_pair(pCONDICAO,FRENTE)] = {pCONDICAODIRECAO};
	map[std::make_pair(pCONDICAO,ESQUERDA)] = {pCONDICAODIRECAO};
	map[std::make_pair(pCONDICAO,DIREITA)] = {pCONDICAODIRECAO};
	//CONDICAOROBO
	map[std::make_pair(pCONDICAOROBO,ROBO)] = {ROBO,pESTADOROBO};
	//ESTADOROBO
	map[std::make_pair(pESTADOROBO,PRONTO)] = {PRONTO};
	map[std::make_pair(pESTADOROBO,OCUPADO)] = {OCUPADO};
	map[std::make_pair(pESTADOROBO,PARADO)] = {PARADO};
	map[std::make_pair(pESTADOROBO,MOVIMENTANDO)] = {MOVIMENTANDO};
	//CONDIAODIRECAO
	map[std::make_pair(pCONDICAODIRECAO,FRENTE)] = {FRENTE,ROBO,BLOQUEADA};
	map[std::make_pair(pCONDICAODIRECAO,ESQUERDA)] = {ESQUERDA,ROBO,BLOQUEADA};
	map[std::make_pair(pCONDICAODIRECAO,DIREITA)] = {DIREITA,ROBO,BLOQUEADA};
	//CONDICAOLAMPADA
	map[std::make_pair(pCONDICAOLAMPADA,LAMPADA)] = {LAMPADA,pESTADOLAMPADA,A,pDIRECAO};
	//DIRECAO
	map[std::make_pair(pDIRECAO,FRENTE)] = {FRENTE};
	map[std::make_pair(pDIRECAO,ESQUERDA)] = {ESQUERDA};
	map[std::make_pair(pDIRECAO,DIREITA)] = {DIREITA};
	//ESTADOLAMPADA
	map[std::make_pair(pESTADOLAMPADA,APAGADA)] = {APAGADA};
	map[std::make_pair(pESTADOLAMPADA,ACESA)] = {ACESA};
	//SENTIDO
	map[std::make_pair(pSENTIDO,ESQUERDA)] = {ESQUERDA, REGRA3}; // REGRA 3
	map[std::make_pair(pSENTIDO,DIREITA)] = {DIREITA, REGRA4}; // REGRA 4


}

Parser::~Parser() {

}

node * Parser::parse(){
	std::stack<node*> s;
	std::unordered_map<pair,std::vector<int>,hash_pair>::iterator it;

	node *Z = new node;
	node *head = new node;//<<
	node *cur = head;
	node *pai = cur;
	node *tmp;

	head->token.tag=pPROGRAMA;//<<
	Z->token.tag = $;

	s.push(Z);
	s.push(head);

	int x = s.top()->token.getTag();

	Token t;
	t = lexer.scan();

	while(x!=$){
		t = lexer.getCurrentToken();
		std::cout << "Token >> " << tag[t.getTag()]<<std::endl;
		std::cout << "Pilha >> " << debug[x] << std::endl;
		if(x==t.getTag()){ // SE FOR TERMINAL E BATE COM O TOKEN
			s.pop();
			lexer.scan();
			cur->token = t;
		}
		else if(isTerminal(x)){ //SE FOR UM TERMINAL E NAO BATE COM O TOKEN ATUAL
			s.pop();
			lexer.scan();

			tmp = new node;
			tmp->token = t;
			cur->children.push_back(tmp);

			printf("ERRO::LINHA:%d: Terminal nao bate.\n", t.getLine());
		}
		else if (isNonTerminal(x)) { //SE FOR UMA VARIAVEL
			pai = s.top();
			s.pop();
			it = map.find(std::make_pair(x, t.getTag()));
			if (it != map.end()) {
				node *arr[it->second.size()];
				for (int i = it->second.size() - 1; i >= 0; i--) {
					arr[i] = new node;
					(arr[i])->token.tag = it->second[i];
					s.push(arr[i]);
				}

				cur->children.insert(cur->children.begin(), arr,
						arr + it->second.size());
			} else { //SE TIVER PRODUCAO VAZIA
				it = map.find(std::make_pair(x, VAZIO));
				if (it != map.end()) {
					tmp = new node;
					tmp->token.tag = VAZIO;
					cur->children.push_back(tmp);
				} else
					printf("ERRO::LINHA:%d: Producao incapaz de gerar o token.\n",t.getLine());
			}
		}
		else if(isRegra(x)){
			s.pop();
		}
		cur = s.top();
		x = s.top()->token.getTag();
	}


	return head;
}

