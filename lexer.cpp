#include <iostream>
#include <algorithm>
#include "lexer.h"
#include "table.cpp"

//precarrega na tabela as palavras reservadas
Lexer::Lexer(std::string filename) :
	line(1),buffer(filename)
{
	peek = ' ';
	for (int i = 0, keyword = PROGRAMAINICIO; i < NUMBER_OF_KEYWORDS;
			i++, keyword++) {
		Token w(keyword,0, keywords[i]);
		install(w);
	}
}

void Lexer::install(Token w) {
	reservedWords.insert(std::make_pair((std::string) w.lexeme, w)); // @suppress("Invalid arguments")
}

void Lexer::deleteUntilDelimiter() {
	while (!isDelimiter(buffer.lookAhead())) {
		peek = buffer.next();
	}
}

Token Lexer::getCurrentToken(){
	return curToken;
}

Token Lexer::scan() {

	peek = buffer.next();
	//consome caracteres em branco, linhas de comentario
	//,LF,CR at� o pr�ximo caractere v�lido.
	while (true) {
		if (peek == ' ' || peek == '\t' || peek == '\r');
		else if (peek == '\n')
			line++;
		else if (peek == '#') {
			while (true) {
				peek = buffer.next();
				if (peek == '\n') {
					line++;
					break;
				} else if (peek == END_FILE) {
					curToken = Token(END_OF_FILE, line, "");
					return curToken;
				}
			}
		} else
			break;
		peek = buffer.next();
	}

	//tokeniza id ou keyword
	if (isalpha(peek) || peek == '_') {
		std::string lex("");
		lex += peek;
		char look = buffer.lookAhead();
		while (isdigit(look) || isalpha(look) || look == '_') {
			peek = buffer.next();
			look = buffer.lookAhead();
			lex += peek;

			if (lex.size() > 150) {
				std::cout << "AVISO::LINHA:" << line
						<< ": Limite de caracteres(150) excedido para o identificador. Desconsiderando caracteres seguintes....>>"
						<< lex << "<<" << std::endl;
				deleteUntilDelimiter();
			}

		}

		if (!isDelimiter(buffer.lookAhead())) {
			std::string tmp;
			while (!isDelimiter(buffer.lookAhead())) {
				peek = buffer.next();
				tmp += peek;
			}
			std::cout << "AVISO::LINHA:" << line
					<< ": Simbolos estranhos sendo ignorados. >> " << tmp
					<< " <<" << std::endl;

		}


		std::unordered_map<std::string, Token>::iterator it = reservedWords.find(
				lex);

		if (it != reservedWords.end()) {
			curToken = Token(it->second.getTag(),line,it->second.getLexeme());

			return curToken;
		}

		curToken = Token(ID,line ,lex);
		return curToken;
	}
	// tokeniza numero
	if (isdigit(peek)) {
		std::string lex("");
		lex += peek;
		while (isdigit(buffer.lookAhead())) {
			peek = buffer.next();
			lex += peek;
			if (lex.size() > 9) {
				deleteUntilDelimiter();
				std::cout << "ERRO::LINHA:" << line
						<< ": O numero excede o limite de digitos(9),  >>"
						<< lex << "<<.\n";
				curToken = Token(ERROR,line, "NUMBER_TOO_BIG");
				return curToken;
			}
		}

		if (!isDelimiter(buffer.lookAhead())) {
			while (!isDelimiter(buffer.lookAhead())) {
				lex += buffer.next();
				if (lex.size() > 150) {
					deleteUntilDelimiter();
					break;
				}
			}
			std::cout << "ERRO::LINHA:" << line << ": Numero mal formado. >> "
					<< lex << " <<\n";
			curToken = Token(ERROR,line, "NUMBER_MALFORMED");
			return curToken;
		}

		curToken = Token(NUMERO,line, lex);
		return curToken;
	}
	if (peek == END_FILE) {
		Token t(END_OF_FILE,line, "");
		return t;
	} else {
		std::string lex("");
		while (!isDelimiter(buffer.lookAhead())) {
			lex += peek;
			peek = buffer.next();
		}
		std::cout << "ERRO::LINHA:" << line
				<< ": Impossivel associar simbolos a qualquer padrao conhecido. >> "
				<< lex << "\n";
	}

	curToken = Token(ERROR,line, "");
	return curToken;
}

