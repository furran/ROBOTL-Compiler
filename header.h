#define END_FILE -1

#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string>
#include <fstream>
#include <unordered_map>
#include "token.cpp"
#include "buffer.h"




std::string keywords[] = { "programainicio", "fimprograma", "execucaoinicio",
		"fimexecucao", "definainstrucao", "como", "inicio", "fim", "repita",
		"vezes", "fimrepita", "enquanto", "faca", "fimpara", "se", "entao",
		"fimse", "senao", "fimsenao", "mova", "passos", "passo", "vire", "para", "pare",
		"finalize", "apague", "lampada", "acenda", "aguarde","ate",
		"robo","pronto", "ocupado", "parado", "movimentando",
		"bloqueada", "acesa","a" ,"frente","apagada", "esquerda", "direita" };



enum {  PROGRAMAINICIO, FIMPROGRAMA, EXECUCAOINICIO,
		FIMEXECUCAO, DEFINAINSTRUCAO, COMO, INICIO, FIM, REPITA,
		VEZES, FIMREPITA, ENQUANTO, FACA, FIMPARA, SE, ENTAO,
		FIMSE, SENAO, FIMSENAO, MOVA, PASSOS, PASSO, VIRE, PARA, PARE,
		FINALIZE, APAGUE, LAMPADA, ACENDA, AGUARDE,ATE,
		ROBO ,PRONTO, OCUPADO, PARADO, MOVIMENTANDO,
		BLOQUEADA, ACESA,A ,FRENTE,APAGADA, ESQUERDA, DIREITA,
		ERROR, NUMBER, ID, END_OF_FILE};


std::string tag[]{
		"PROGRAMAINICIO", "FIMPROGRAMA", "EXECUCAOINICIO",
		"FIMEXECUCAO", "DEFINAINSTRUCAO", "COMO", "INICIO", "FIM", "REPITA",
		"VEZES", "FIMREPITA", "ENQUANTO", "FACA", "FIMPARA", "SE", "ENTAO",
		"FIMSE", "SENAO", "FIMSENAO", "MOVA", "PASSOS", "PASSO", "VIRE", "PARA", "PARE",
		"FINALIZE", "APAGUE", "LAMPADA", "ACENDA", "AGUARDE", "ATE",
		"ROBO", "PRONTO", "OCUPADO", "PARADO", "MOVIMENTANDO",
		"BLOQUEADA", "ACESA", "A", "FRENTE", "APAGADA", "ESQUERDA", "DIREITA", "ERROR",
		"NUMBER", "ID", "END_OF_FILE"
};


#define NUMBER_OF_KEYWORDS 43

std::unordered_map<std::string, Token> table;

bool isDelimiter(char peek){ //ve se o caractere eh o que consideramos como "espaco em branco"
	if(peek == ' ' || peek == '\n' || peek == '\t' || peek == '\r' || peek == '#' || peek == END_FILE){
		return true;
	}
	else return false;
}

