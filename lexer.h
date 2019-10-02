#include "header.h"

class Lexer{
private:
	char peek;

public:
	int line = 1;
	Buffer buffer;
	void install(Token w) {
		table.insert(std::make_pair((std::string) w.lexeme, w));
	}

	//precarrega na tabela as palavras reservadas
	Lexer(std::string filename)
	: buffer(filename)
	{
		peek = ' ';
		for(int i = 0, keyword= PROGRAMAINICIO;i<NUMBER_OF_KEYWORDS;i++, keyword++){
			Token w(keyword, keywords[i]);
			install(w);
		}
	}

	void deleteUntilDelimiter(){
		while(!isDelimiter(buffer.lookAhead())){
			peek = buffer.next();
		}
	}



	Token scan(){

		peek = buffer.next();
		//consome caracteres em branco, linhas de comentario
		//,LF,CR até o próximo caractere válido.
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
			}else break;
			peek = buffer.next();
		}

		//tokeniza id ou keyword
		if(isalpha(peek) || peek == '_'){
			std::string lex("");
			lex+= peek;
			char look = buffer.lookAhead();
			while(isdigit(look) || isalpha(look) ||  look == '_'){
				peek = buffer.next();
				look = buffer.lookAhead();
				lex+= peek;

				if (lex.size() > 150) {
					std::cout << "AVISO::LINHA:" << line
							<< ": Limite de caracteres(150) excedido para o identificador. Desconsiderando caracteres seguintes....>>"
							<< lex << "<<" << std::endl;
					deleteUntilDelimiter();
					Token w(ID, lex);
					table.insert(std::make_pair(lex, w));
					return w;
				}

			}

			if(!isDelimiter(buffer.lookAhead())){
				std::string tmp;
				while(!isDelimiter(buffer.lookAhead())){
					peek = buffer.next();
					tmp += peek;
				}
				std::cout << "AVISO::LINHA:" << line << ": Simbolos estranhos sendo ignorados. >> " << tmp << " <<" << std::endl;

			}

			std::string lowercase_lex;
			lowercase_lex.resize(lex.size());
			transform(lex.begin(), lex.end(), lowercase_lex.begin(), ::tolower);
			std::unordered_map<std::string,Token>::iterator it = table.find(lowercase_lex);

			if(it != table.end()){
				return it->second;
			}

			Token w(ID,lowercase_lex);
			table.insert(std::make_pair(lowercase_lex,w));
			return w;
		}
		// tokeniza numero
		if(isdigit(peek)){
			std::string lex("");
			lex += peek;
			while(isdigit(buffer.lookAhead())){
				peek = buffer.next();
				lex+= peek;
				if(lex.size() > 9){
					deleteUntilDelimiter();
					std::cout << "ERRO::LINHA:" << line << ": O numero execede o limite de digitos(9),  >>" << lex << "<<.\n";
					return Token(ERROR, "NUMBER_TOO_BIG");
				}
			}

			if(!isDelimiter(buffer.lookAhead())){
				while(!isDelimiter(buffer.lookAhead())){
					lex+=buffer.next();
					if(lex.size()>150){
						deleteUntilDelimiter();
						break;
					}
				}
				std::cout << "ERRO::LINHA:" << line << ": Numero mal formado. >> " << lex << " <<\n";

				return Token(ERROR, "NUMBER_MALFORMED");
			}

			Token num(NUMBER,lex);
			return num;
		}
		if (peek == END_FILE) {
			Token t(END_OF_FILE, "");
			return t;
		} else{
			std::string lex("");
			while(!isDelimiter(buffer.lookAhead())){
				lex+= peek;
				peek = buffer.next();
			}
			std::cout<<"ERRO::LINHA:"<< line <<": Impossivel associar simbolos a qualquer padrao conhecido. >> " << lex << "\n";
		}


		Token t(ERROR, "");
		return t;
	}
};
