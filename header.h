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
		"fimse", "senao", "fimsenao", "mova", "passos", "vire para", "pare",
		"finalize", "apague lampada", "acenda lampada", "aguarde ate",
		"robo pronto", "robo ocupado", "robo parado", "robo movimentando",
		"frente robo bloqueada", "direita robo bloqueada",
		"esquerda robo_bloqueada", "lampada acesa a frente",
		"lampada apagada a frente", "lampada acesa a esquerda",
		"lampada apagada a esquerda", "lampada acesa a direita",
		"lampada apagada a direita", "esquerda", "direita" };

#define NUMBER_OF_KEYWORDS 42

int digit(char c){
	return c-'0';
}
