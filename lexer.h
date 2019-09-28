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
	Lexer(Buffer b)
	: buffer(b)
	{
		peek = ' ';
		std::cout << b.buff1 << std::endl;
		for(int i = 0, keyword= NUMBER;i<NUMBER_OF_KEYWORDS;i++){
			Token w(keyword++, keywords[i]);
			install(w);
		}
	}

#define temp 10

	void consumeDelimiters(){
		while(true){
			if(peek == ' ' || peek == '\r');
			else if(peek=='\n') line++;
			else if(peek=='#'){
				while(true){
					peek = buffer.next();
					if(peek == '\n'){
						line++;
						break;
					}
					else if(peek == END_FILE){
						break;
					}
				}
			}
			else break;
			peek = buffer.next();
		}
	}

	Token scan(){

		std:: cout << "first_peek: " <<  peek << std::endl; // remove this
		peek = buffer.next();
		std:: cout << "second_peek: " <<  peek << std::endl; // remove this
		//consome caracteres em branco, linhas de comentario
		//,LF,CR até o próximo caractere válido.
		consumeDelimiters();

		buffer.beginLexeme();



		//tokeniza id ou keyword
		if(isalpha(peek) || peek == '_'){
			std::string lex("");
			lex+= peek;
			char look = buffer.lookAhead();
			while(isdigit(look) || isalpha(look) ||  look == '_'){
				peek = buffer.next();
				look = buffer.lookAhead();
				lex+= peek;

				if(lex.size() > 100){
					std::cout << "AVISO::LINHA:" << line << ": Limite de caracteres(50) excedido para o identificador >>"<< lex <<"<<" << std::endl;
					break;
				}

			}
			std::cout << "ALPHANUMERIC: " << lex << std::endl;//remove this
			if(!isDelimiter(buffer.lookAhead())){
				std::string tmp;
				while(!isDelimiter(buffer.lookAhead())){
					peek = buffer.next();
					tmp += peek;
				}
				std::cout << "AVISO::LINHA:" << line << ": Simbolos estranhos sendo ignorados. >> " << tmp << " <<" << std::endl;

			}

			std::string tmp;
			transform(lex.begin(), lex.end(), tmp.begin(), ::tolower);
			std::unordered_map<std::string,Token>::iterator it = table.find(tmp);

			if(it!= table.end()){
				printf("palavra reservada: %d ",it->second.tag); std::cout << lex << std::endl; //remove this
				return it->second;
			}

			Token w(ID,tmp);
			table.insert(std::make_pair(tmp,w));
			return w;
		}
		// tokeniza numero
		if(isdigit(peek)){
			std::string lex("");
			lex += peek;
			while(isdigit(buffer.lookAhead())){
				peek = buffer.next();
				lex+= peek;
				if(lex.size() > 10){
					std::cout << "ERRO::LINHA:" << line << ": O numero execede o limite de digitos(10) >>" << lex << "<<.\n";
					break;
				}
			}

			if(!isDelimiter(buffer.lookAhead()) && buffer.lookAhead() != END_FILE){
				while(!isDelimiter(buffer.lookAhead()) && buffer.lookAhead() != END_FILE){
					lex+=buffer.next();
				}

				std::cout << "ERRO::LINHA:" << line << ": Numero mal formado. >> " << lex << " <<\n";
			}

			std::cout << "LINHA:" << line << ":NUMBER: " << lex << " LOOKAHEAD: " << buffer.lookAhead() << std::endl;
			std::cout << "PEEK: " << peek << std::endl;
			Token num(NUMBER,lex);
			return num;
		}

		if(peek == END_FILE){
			Token t(0,"END_FILE");
			return t;
		}
		else printf("ERRO::LINHA:%d: Impossivel associar simbolo a qualquer padrao conhecido.\n", line);

		Token t(ERROR, "ERROR");
		return t;
	}
};
