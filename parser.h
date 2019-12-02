#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include <vector>
#include "lexer.h"

struct node;

typedef std::pair<int,int> pair;
//FUNCAO HASH PARA PAR DE CHAVES
struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const std::pair<T1, T2>& p) const
    {
        auto hash1 = std::hash<T1>{}(p.first);
        auto hash2 = std::hash<T2>{}(p.second);
        return hash1 ^ hash2;
    }
};

class Parser{
public:
	Lexer lexer;
	std::unordered_map<pair,std::vector<int>,hash_pair> analysisTable;
	Parser(std::string filename);
	virtual ~Parser();
	node * parse();
};

#endif
