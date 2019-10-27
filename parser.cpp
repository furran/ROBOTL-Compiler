#include <iostream>
#include <unordered_map>
#include <stack>
#include <vector>
#include "parser.h"

//mais informacao sobre tabela sintatica e a gramatica ll(1) nos documentos excel e word, respectivamente


typedef std::pair<int,int> pair;

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
	: Lexer(filename)
	{
	tokenBuffer.resize(tokenBufferLength);
	//criar tabela sintatica
	map[std::make_pair(pPROGRAMA,PROGRAMAINICIO)] = {PROGRAMAINICIO,pDECLARACAO,EXECUCAOINICIO,pCOMANDOLISTA,FIMEXECUCAO,FIMPROGRAMA};

	for(int i=PROGRAMAINICIO;i<$;i++){
		map[std::make_pair(pDECLARACAO,i)] = {};
	}
	map[std::make_pair(pDECLARACAO,DEFINAINSTRUCAO)] = {DEFINAINSTRUCAO,ID,COMO,pCOMANDO,pDECLARACAO};

	map[std::make_pair(pBLOCO,INICIO)] = {INICIO,pCOMANDOLISTA,FIM};


	for(int i= PROGRAMAINICIO;i<$;i++){
		map[std::make_pair(pCOMANDOLISTA,i)] = {};
	}
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

	map[std::make_pair(pITERACAO,REPITA)] = {REPITA,NUMBER,VEZES,pCOMANDO,FIMREPITA};

	map[std::make_pair(pLACO,ENQUANTO)] = {ENQUANTO,pCONDICAO,FACA,pCOMANDO,FIMPARA};

	map[std::make_pair(pCONDICIONAL,SE)] = {SE,pCONDICAO,ENTAO,pCOMANDO,FIMSE,pCONDICIONALOPT};

	for(int i= PROGRAMAINICIO;i<$;i++){
		map[std::make_pair(pCONDICIONALOPT,i)] = {};
	}
	map[std::make_pair(pCONDICIONALOPT,SENAO)] = {SENAO,pCOMANDO,FIMSENAO};

	map[std::make_pair(pINSTRUCAO,MOVA)] = {MOVA,NUMBER,pINSTRUCAOOPT};
	map[std::make_pair(pINSTRUCAO,VIRE)] = {VIRE,PARA,pSENTIDO};
	map[std::make_pair(pINSTRUCAO,ID)] = {ID};
	map[std::make_pair(pINSTRUCAO,PARE)] = {PARE};
	map[std::make_pair(pINSTRUCAO,FINALIZE)] = {FINALIZE};
	map[std::make_pair(pINSTRUCAO,APAGUE)] = {APAGUE,LAMPADA};
	map[std::make_pair(pINSTRUCAO,ACENDA)] = {ACENDA,LAMPADA};
	map[std::make_pair(pINSTRUCAO,AGUARDE)] = {AGUARDE,ATE,pCONDICAO};

	for(int i= PROGRAMAINICIO;i<$;i++){
		map[std::make_pair(pINSTRUCAOOPT,i)] = {};
	}
	map[std::make_pair(pINSTRUCAOOPT,PASSOS)] = {PASSOS};

	map[std::make_pair(pCONDICAO,ROBO)] = {pCONDICAOROBO};
	map[std::make_pair(pCONDICAO,LAMPADA)] = {pCONDICAOLAMPADA};
	map[std::make_pair(pCONDICAO,PASSOS)] = {pCONDICAOROBO};
	map[std::make_pair(pCONDICAO,FRENTE)] = {pCONDICAODIRECAO};
	map[std::make_pair(pCONDICAO,ESQUERDA)] = {pCONDICAODIRECAO};
	map[std::make_pair(pCONDICAO,DIREITA)] = {pCONDICAODIRECAO};

	map[std::make_pair(pCONDICAOROBO,ROBO)] = {ROBO,pESTADOROBO};

	map[std::make_pair(pESTADOROBO,PRONTO)] = {PRONTO};
	map[std::make_pair(pESTADOROBO,OCUPADO)] = {OCUPADO};
	map[std::make_pair(pESTADOROBO,PARADO)] = {PARADO};
	map[std::make_pair(pESTADOROBO,MOVIMENTANDO)] = {MOVIMENTANDO};

	map[std::make_pair(pCONDICAODIRECAO,FRENTE)] = {pDIRECAO,ROBO,BLOQUEADA};
	map[std::make_pair(pCONDICAODIRECAO,ESQUERDA)] = {pDIRECAO,ROBO,BLOQUEADA};
	map[std::make_pair(pCONDICAODIRECAO,DIREITA)] = {pDIRECAO,ROBO,BLOQUEADA};

	map[std::make_pair(pCONDICAOLAMPADA,LAMPADA)] = {LAMPADA,pESTADOLAMPADA,A,pDIRECAO};

	map[std::make_pair(pDIRECAO,FRENTE)] = {FRENTE};
	map[std::make_pair(pDIRECAO,ESQUERDA)] = {ESQUERDA};
	map[std::make_pair(pDIRECAO,DIREITA)] = {DIREITA};

	map[std::make_pair(pESTADOLAMPADA,APAGADA)] = {APAGADA};
	map[std::make_pair(pESTADOLAMPADA,ACESA)] = {ACESA};

	map[std::make_pair(pSENTIDO,ESQUERDA)] = {ESQUERDA};
	map[std::make_pair(pSENTIDO,DIREITA)] = {DIREITA};

}

Parser::~Parser() {

}

void Parser::loadBuffer(){
	for(int i=0;i<tokenBufferLength;i++){
		tokenBuffer[i] = scan();
		if(tokenBuffer[i].getTag()==END_OF_FILE)break;
	}
}


void Parser::error(){
	printf("ERRO\n");
}

void Parser::parse(){
	std::stack<int> s;
	std::unordered_map<pair,std::vector<int>,hash_pair>::iterator it;
	s.push($);
	s.push(pPROGRAMA);
	loadBuffer();
	int x = s.top();
	printf("x=%d\n",debug[x]);
	int index = 0;
	Token t;
	while(x!=$){
		t = tokenBuffer[index];
		std::cout<<"token= " << tag[t.getTag()]<<std::endl;
		std::cout << "Pilha >>" << debug[x] << std::endl;
		if(x==t.getTag()){
			s.pop();
			printf("x==w\n");
			index++;
		}
		else if(isTerminal(x)){
			printf("ERRO::Terminal nao bate.\n");
			s.pop();
			index++;
		}
		else if(isNonTerminal(x)){
			it = map.find(std::make_pair(x,t.getTag()));
			if(it!=map.end()){
				s.pop();
				for(int i=it->second.size()-1;i>=0;i--){
					s.push(it->second[i]);
				}
			}
			else {
				printf("ERRO: producao nao mapeada\n");
				s.pop();
				index++;
			}
		}
		x=s.top();
	}
	std::cout << std::endl;
}
//teste

