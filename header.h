#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string>
#include <fstream>
#include "buffer.h"
#include <unordered_map>
#include "token.cpp"


#define END_FILE 0



char const *keywords[] = { "programainicio", "fimprograma", "execucaoinicio",
		"fimexecucao", "definainstrucao", "como", "inicio", "fim", "repita",
		"vezes", "fimrepita", "enquanto", "faca", "fimpara", "se", "entao",
		"fimse", "senao", "fimsenao", "mova", "passos", "vire", "para", "pare",
		"finalize", "apague", "lampada", "acenda", "aguarde","ate",
		"robo","pronto", "ocupado", "parado", "movimentando",
		"bloqueada", "acesa","a" ,"frente","apagada", "esquerda", "direita" };

#define NUMBER_OF_KEYWORDS 42

std::unordered_map<std::string, Token> table;

bool isWS(char peek){ //ve se o caractere eh o que consideramos como "espaco em branco"
	if(peek == ' ' || peek == '\n' || peek == '\t'  || peek == '\r' || peek == '#'){
		return true;
	}
	else return false;
}

