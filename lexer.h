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
		std::cout << b.buff << std::endl;
		for(int i = 0;i<NUMBER_OF_KEYWORDS;i++){
			Token w(KEYWORD, keywords[i]);
			reserve(w);
		}
	}

	Token scan(){
		//consome caracteres em branco, linhas de comentario e conta o numero de linhas lidas(EOF);

		peek = buffer.next();
		std:: cout << "peek: " <<  peek << std::endl; // remove this
		while(true){
			if(peek == ' ');
			else if(peek=='\n') line++;
			else if(peek=='#'){
				while(peek!='\n'){
					peek = buffer.next();
				}
			}
			else break;
			peek = buffer.next();
		}

		//tokeniza id ou keyword
		if(isalpha(peek)){
			std::string lex("");
			while(isdigit(peek) || isalpha(peek)){
				lex+= peek;
				peek = buffer.next();
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
			lex+=peek;
			while(isdigit(buffer.lookAhead())){
				peek = buffer.next();
				lex+=peek;
				printf("%c",peek); //remove this
			}
			std::cout << "\nNUMBER: " << lex << std::endl;
			if(!isWS(buffer.lookAhead())){
				do{
					lex += peek;
					peek = buffer.next();
				}while(!isWS(peek));
				std::cout << "ERRO::LINHA:"<<line<<": Numero mal formado. >> "<<lex<<" <<" << std::endl;
			}

			Token num(NUMBER,lex);
			return num;
		}

		if(peek == 0){
			Token t(0,"ENDFILE");
			return t;
		}
		else printf("ERRO::LINHA:%d: Impossivel associar simbolo a qualquer padrao conhecido.\n", line);

		Token t(1, "ERROR");
		return t;
	}
};
