#ifndef TABLE_CPP_
#define TABLE_CPP_

#define END_FILE -1

#include <string>
#include <unordered_map>
#include "token.cpp"


std::string keywords[] = { "programainicio", "fimprograma", "execucaoinicio",
		"fimexecucao", "definainstrucao", "como", "inicio", "fim", "repita",
		"vezes", "fimrepita", "enquanto", "faca", "fimpara", "se", "entao",
		"fimse", "senao", "fimsenao", "mova", "passos", "vire", "para", "pare",
		"finalize", "apague", "lampada", "acenda", "aguarde", "ate", "robo",
		"pronto", "ocupado", "parado", "movimentando", "bloqueada", "acesa",
		"a", "frente", "apagada", "esquerda", "direita" };


enum terminals{
	//terminais
		PROGRAMAINICIO=0, FIMPROGRAMA, EXECUCAOINICIO,
		FIMEXECUCAO, DEFINAINSTRUCAO, COMO, INICIO, FIM, REPITA,
		VEZES, FIMREPITA, ENQUANTO, FACA, FIMPARA, SE, ENTAO,
		FIMSE, SENAO, FIMSENAO, MOVA, PASSOS, VIRE, PARA, PARE,
		FINALIZE, APAGUE, LAMPADA, ACENDA, AGUARDE,ATE,
		ROBO ,PRONTO, OCUPADO, PARADO, MOVIMENTANDO,
		BLOQUEADA, ACESA,A ,FRENTE,APAGADA, ESQUERDA, DIREITA,
		ERROR, NUMERO, ID, END_OF_FILE, VAZIO, $
};

enum productions{
	//producoes
	pPROGRAMA=$+1, pDECLARACAO, pBLOCO, pCOMANDOLISTA, pCOMANDO, pITERACAO, pLACO,
	pCONDICIONAL, pCONDICIONALOPT, pINSTRUCAO, pINSTRUCAOOPT, pNUMEROOPT, pCONDICAO, pCONDICAOROBO,
	pESTADOROBO,pCONDICAODIRECAO, pCONDICAOLAMPADA, pDIRECAO, pESTADOLAMPADA, pSENTIDO
};

enum regras {
	REGRA1 = pSENTIDO+1, REGRA2 , REGRA3, REGRA4, REGRA5
};


std::string tag[] { "PROGRAMAINICIO", "FIMPROGRAMA", "EXECUCAOINICIO",
		"FIMEXECUCAO", "DEFINAINSTRUCAO", "COMO", "INICIO", "FIM", "REPITA",
		"VEZES", "FIMREPITA", "ENQUANTO", "FACA", "FIMPARA", "SE", "ENTAO",
		"FIMSE", "SENAO", "FIMSENAO", "MOVA", "PASSOS", "VIRE", "PARA", "PARE",
		"FINALIZE", "APAGUE", "LAMPADA", "ACENDA", "AGUARDE", "ATE", "ROBO",
		"PRONTO", "OCUPADO", "PARADO", "MOVIMENTANDO", "BLOQUEADA", "ACESA",
		"A", "FRENTE", "APAGADA", "ESQUERDA", "DIREITA", "ERROR", "NUMBER",
		"ID", "END_OF_FILE", "VAZIO" };

std::string debug[] { "PROGRAMAINICIO", "FIMPROGRAMA", "EXECUCAOINICIO",
		"FIMEXECUCAO", "DEFINAINSTRUCAO", "COMO", "INICIO", "FIM", "REPITA",
		"VEZES", "FIMREPITA", "ENQUANTO", "FACA", "FIMPARA", "SE", "ENTAO",
		"FIMSE", "SENAO", "FIMSENAO", "MOVA", "PASSOS", "VIRE", "PARA", "PARE",
		"FINALIZE", "APAGUE", "LAMPADA", "ACENDA", "AGUARDE", "ATE", "ROBO",
		"PRONTO", "OCUPADO", "PARADO", "MOVIMENTANDO", "BLOQUEADA", "ACESA",
		"A", "FRENTE", "APAGADA", "ESQUERDA", "DIREITA", "ERROR", "NUMBER",
		"ID", "END_OF_FILE", "VAZIO", "$",

		"pPROGRAMA", "pDECLARACAO", "pBLOCO",
		"pCOMANDOLISTA", "pCOMANDO", "pITERACAO", "pLACO", "pCONDICIONAL",
		"pCONDICIONALOPT", "pINSTRUCAO", "pINSTRUCAOOPT", "pNUMEROOPT",
		"pCONDICAO", "pCONDICAOROBO", "pESTADOROBO", "pCONDICAODIRECAO",
		"pCONDICAOLAMPADA", "pDIRECAO", "pESTADOLAMPADA", "pSENTIDO",

		"REGRA1", "REGRA2", "REGRA3","REGRA4", "REGRA5" };


#define NUMBER_OF_KEYWORDS 42

std::unordered_map<std::string, Token> symbolTable;




bool isDelimiter(char peek){ //ve se o caractere eh o que consideramos como "espaco em branco"
	if(peek == ' ' || peek == '\n' || peek == '\t' || peek == '\r' || peek == '#' || peek == END_FILE){
		return true;
	}
	else return false;
}

bool isTerminal(int t){
	if(t>=PROGRAMAINICIO && t<$){
		return true;
	}
	else return false;
}

bool isNonTerminal(int t){
	if(t>=pPROGRAMA && t<=pSENTIDO){
		return true;
	}
	else return false;
}

bool isRegra(int r){
	if(r>=REGRA1 && r<=REGRA5){
		return true;
	}
	else return false;
}

#endif
