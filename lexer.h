#include "header.h"

class Lexer{
private:
	char peek;

public:
	int line = 1;
	Buffer buffer;
	void reserve(Token w) {
		table.insert(std::make_pair((std::string) w.lexeme, w));
	}

	//precarrega na tabela as palavras reservadas
	Lexer(Buffer b)
	: buffer(b)
	{
		peek = ' ';
		std::cout << b.buff1 << std::endl;
		for(int i = 0;i<NUMBER_OF_KEYWORDS;i++){
			Token w(KEYWORD, keywords[i]);
			reserve(w);
		}
	}

	Token scan(){
		std:: cout << "first_peek: " <<  peek << std::endl; // remove this
		peek = buffer.next();
		std:: cout << "second_peek: " <<  peek << std::endl; // remove this
		//consome caracteres em branco, linhas de comentario e conta o numero de linhas lidas(EOF);
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

		//tokeniza id ou keyword
		if(isalpha(peek)){
			std::string lex("");
			lex+= peek;
			while(isdigit(buffer.lookAhead()) || isalpha(buffer.lookAhead())){
				peek = buffer.next();
				lex+= peek;
			}


			std::unordered_map<std::string,Token>::iterator it = table.find(lex);
			std::cout << "ALPHANUMERIC: " << lex << std::endl;//remove this
			if(it!= table.end()){
				printf("palavra chave: %d ",it->second.tag); std::cout << lex << std::endl; //remove this
				return it->second;
			}

			Token w(ID,lex);
			table.insert(std::make_pair(lex,w));
			return w;
		}
		// tokeniza numero
		if(isdigit(peek)){
			std::string lex("");
			lex += peek;
			while(isdigit(buffer.lookAhead())){
				peek = buffer.next();
				lex+= peek;
			}

			if(!isWS(buffer.lookAhead()) && buffer.lookAhead() != END_FILE){
				while(!isWS(buffer.lookAhead()) && buffer.lookAhead() != END_FILE){
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
			Token t(0,"ENDFILE");
			return t;
		}
		else printf("ERRO::LINHA:%d: Impossivel associar simbolo a qualquer padrao conhecido.\n", line);

		Token t(1, "ERROR");
		return t;
	}
};
