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
		Token w(keyword, keywords[i]);
		install(w);
	}
}

void Lexer::install(Token w) {
	symbolTable.insert(std::make_pair((std::string) w.lexeme, w)); // @suppress("Invalid arguments")
}

void Lexer::deleteUntilDelimiter() {
	while (!isDelimiter(buffer.lookAhead())) {
		peek = buffer.next();
	}
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
					Token t(END_OF_FILE, "");
					return t;
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
				Token w(ID, lex);
				symbolTable.insert(std::make_pair(lex, w)); // @suppress("Invalid arguments")
				return w;
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


		std::unordered_map<std::string, Token>::iterator it = symbolTable.find(
				lex);

		if (it != symbolTable.end()) {
			return it->second;
		}

		Token w(ID, lex);
		symbolTable.insert(std::make_pair(lex, w));
		return w;
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
						<< ": O numero execede o limite de digitos(9),  >>"
						<< lex << "<<.\n";
				return Token(ERROR, "NUMBER_TOO_BIG");
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

			return Token(ERROR, "NUMBER_MALFORMED");
		}

		Token num(NUMBER, lex);
		return num;
	}
	if (peek == END_FILE) {
		Token t(END_OF_FILE, "");
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

	Token t(ERROR, "");
	return t;
}

