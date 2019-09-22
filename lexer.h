#include "header.h"

class Lexer{
private:
	char peek;

public:
	int line = 1;
	Buffer buffer;
	std::unordered_map<std::string, Token> table;
	void reserve(Word w) {
		table.insert(std::make_pair((std::string) w.lexeme, w));
	}

	//precarrega na tabela as palavras reservadas
	Lexer(Buffer b)
	: buffer(b)
	{
		std::cout << b.buff << std::endl;
		for(int i = 0;i<NUMBER_OF_KEYWORDS;i++){
			Word w(KEYWORD, keywords[i]);
			reserve(w);
		}
	}

	Token scan(){
		//consome caracteres em branco, linhas de comentario e conta o numero de linhas lidas(EOF);
		peek = buffer.next();
		std:: cout << "peek: " <<  peek << std::endl;
		while(true){
			if(peek == ' ' || peek==EOF);
			else if(peek=='\n') line++;
			else if(peek=='#'){
				while(peek!='\n'){
					peek = buffer.next();
				}
			}
			else break;
			peek = buffer.next();
		}
		// tokeniza numero
		if(isdigit(peek)){
			int v =0;

			while(isdigit(peek)){
				v = 10*v+digit(peek);
				peek = buffer.next();
				printf("%c",peek);
			}
			std::cout << "NUMBER: " << v << std::endl;
			Number num(v);
			return num;
		}
		//tokeniza id ou keyword
		if(isalpha(peek)){
			std::string lex("");
			while(isdigit(peek) || isalpha(peek)){
				lex+= peek;
				peek = buffer.next();
			}

			std::unordered_map<std::string,Token>::iterator it = table.find(lex);
			std::cout << "ALPHANUMERIC: " << lex << std::endl;
			if(it!= table.end()){
				printf("palavra chave: %d ",it->second.tag); std::cout << lex << std::endl;
				return it->second;
			}

			Word w(ID,lex);
			table.insert(std::make_pair(lex,w));
			return w;
		}
		if(peek == 0){
			Token t(0);
			return t;
		}
		else printf("Caractere desconhecido.\n");

		peek = ' ';
		Token t(1);
		return t;
	}
};
