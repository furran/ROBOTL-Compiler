

enum {  NUMBER=256, ID, PROGRAMAINICIO, FIMPROGRAMA, EXECUCAOINICIO,
		FIMEXECUCAO, DEFINAINSTRUCAO, COMO, INICIO, FIM, REPITA,
		VEZES, FIMREPITA, ENQUANTO, FACA, FIMPARA, SE, ENTAO,
		FIMSE, SENAO, FIMSENAO, MOVA, PASSOS, VIRE, PARA, PARE,
		FINALIZE, APAGUE, LAMPADA, ACENDA, AGUARDE,ATE,
		ROBO ,PRONTO, OCUPADO, PARADO, MOVIMENTANDO,
		BLOQUEADA, ACESA,A ,FRENTE,APAGADA, ESQUERDA, DIREITA, ERROR };

class Token {
public:
	int tag;
	const std::string lexeme;
	Token(int t, std::string lex)
	: tag(t), lexeme(lex)
	{
	}

	int getTag(){
		return tag;
	}

	const std::string getLexeme(){
		return lexeme;
	}

};
