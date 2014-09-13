#include "Relationship.h"

//function to convert a string to lowercase
string stringToLower(string word){
	for(int i=0;i<(int)word.length();i++){
		word[i] = tolower(word[i]);
	}
	return word;
}


//get Relationship Type
Relationship::RelType Relationship::getRelType(string relStr){
    if (relStr == "follows") {
        return FOLLOWS;
    } else if (relStr == "follows*"){
        return FOLLOWSSTAR;
    } else if (relStr == "parent"){
        return PARENT;
	} else if (relStr == "parent*") {
	    return PARENTSTAR;
    } else if (relStr == "modifies"){
		return MODIFIES;
	} else if (relStr=="uses"){
		return USES;
	} else if (relStr=="calls"){
		return CALLS;
	} else if (relStr=="calls*"){
		return CALLSSTAR;
	} else if (relStr=="next"){
		return NEXT;
	} else if (relStr=="next*"){
		return NEXTSTAR;
	} else if (relStr=="affects"){
		return AFFECTS;
	} else if (relStr=="affects*"){
		return AFFECTSSTAR;
	} else if (relStr=="with"){
		return WITH;
	} else if (relStr=="pattern"){
		return PATTERN;
	}
}

//get Relationship Type
Relationship::TokenType Relationship::getTokenType(string tokenStr){
	if (tokenStr == "_") {
        return UNDERSCORE;
    } else if (tokenStr == "identifier"){
        return IDENTIFIER;
    } else if (tokenStr == "synonym"){
        return SYNONYM;
	} else if (tokenStr == "integer") {
	    return INTEGER;
    } else {
		return INVALID;
	}
}


//constructor for normal clause
Relationship::Relationship(string newRel, string newToken1, string newToken2)
{
    relName = stringToLower(newRel);
	relType = getRelType(relName);
    token1 = newToken1;
    token2 = newToken2;
}

//constructor for pattern clause
Relationship::Relationship(string newRel, string newPatternSyn, string newToken1, string newToken2)
{
    relName = stringToLower(newRel);
	relType = getRelType(relName);
	patternSyn = newPatternSyn;
    token1 = newToken1;
    token2 = newToken2;
}

//constructor for normal clause with type
Relationship::Relationship(string newRel, string newToken1, TokenType newType1, string newToken2, TokenType newType2 )
{
    relName = stringToLower(newRel);
	relType = getRelType(relName);
    token1 = newToken1;
	token1Type = newType1;
    token2 = newToken2;
	token2Type = newType2;
}

//getter implementation

string Relationship::getRelName(){
	return relName;
}

Relationship::RelType Relationship::getRelType(){
	return relType;
}

string Relationship::getToken1(){
    return token1;
}

string Relationship::getToken2(){
    return token2;
}

string Relationship::getPatternSyn(){
	return patternSyn;
}

Relationship::TokenType Relationship::getToken1Type(){
	return token1Type;
}

Relationship::TokenType Relationship::getToken2Type(){
	return token2Type;
}


//setter implementation

void Relationship::setRelName(string newRelName){
	relName = newRelName;
}

void Relationship::setRelType(Relationship::RelType newType){
	relType = newType;
}

void Relationship::setToken1(string tk1){
	token1 = tk1;
}

void Relationship::setToken2(string tk2){
	token2 = tk2;
}

void Relationship::setToken1Type(Relationship::TokenType newType1){
	token1Type = newType1;
}

void Relationship::setToken2Type(Relationship::TokenType newType2){
	token1Type = newType2;
}

void Relationship::setPatternSyn(string newPatternSyn){
	patternSyn = newPatternSyn;
}
