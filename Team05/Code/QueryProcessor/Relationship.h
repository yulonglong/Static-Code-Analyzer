#pragma once
#ifndef RELATIONSHIP_H
#define RELATIONSHIP_H

#include <string>
#include <iostream>
#include <string>

using namespace std;

class Relationship
{	
	public:
		enum RelType{FOLLOWS, FOLLOWSSTAR, PARENT, PARENTSTAR, MODIFIES, USES, CALLS, CALLSSTAR, NEXT, NEXTSTAR, AFFECTS, AFFECTSSTAR, WITH, PATTERN, INVALIDREL};
		static RelType getRelType(string);
		enum TokenType{ SYNONYM, IDENTIFIER, INTEGER, UNDERSCORE, UNDERSCOREIDENT, INVALIDTOKEN};
		static TokenType getTokenType(string);

    private:
		string relName;
		RelType relType;
		string patternSyn; //for pattern
        string token1;
        string token2;
		TokenType token1Type;
		TokenType token2Type;

    public:
		//blank relationship
		Relationship();
		//constructor for clause, token1, token2
        Relationship(string, string, string);
		//constructor for clause, patternSyn, token1, token2
		Relationship(string, string, string, string);
		//constructor for clause, token1, token1type, token2, token2type
		Relationship(string, string, TokenType, string ,TokenType);
		//constructor for clause, patternSyn, token1, token1type, token2, token2type
		Relationship(string, string, string, TokenType, string ,TokenType);
        
		//getter
		string getRelName();
		RelType getRelType();
		string getPatternSyn();
        string getToken1();
        string getToken2();
		TokenType getToken1Type();
		TokenType getToken2Type();
		
		//setter
		void setRelName(string);
		void setRelType(RelType);
		void setToken1(string);
		void setToken2(string);
		void setToken1Type(TokenType);
		void setToken2Type(TokenType);
		void setPatternSyn(string);

};

#endif // RELATIONSHIP_H_INCLUDED