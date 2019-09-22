#include <iostream>
#include <algorithm>
#include "Tokens.cpp"
#include <stdio.h>
#include <string>
#include <fstream>
#include "buffer.h"
#include <unordered_map>



char const *keywords[] = { "programainicio", "fimprograma", "execucaoinicio",
		"fimexecucao", "definainstrucao", "como", "inicio", "fim", "repita",
		"vezes", "fimrepita", "enquanto", "faca", "fimpara", "se", "entao",
		"fimse", "senao", "fimsenao", "mova", "passos", "vire", "para", "pare",
		"finalize", "apague", "lampada", "acenda", "aguarde","ate",
		"robo","pronto", "ocupado", "parado", "movimentando",
		"bloqueada", "acesa","a" ,"frente","apagada", "esquerda", "direita" };

#define NUMBER_OF_KEYWORDS 42

int digit(char c){
	return c-'0';
}
