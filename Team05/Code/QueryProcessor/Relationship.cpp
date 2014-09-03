#include "Relationship.h"

//function to convert a string to lowercase
string stringToLower(string word){
	for(int i=0;i<(int)word.length();i++){
		word[i] = tolower(word[i]);
	}
	return word;
}

//constructor for normal clause
Relationship::Relationship(string newRel, string newToken1, string newToken2)
{
    relName = stringToLower(newRel);
    token1 = newToken1;
    token2 = newToken2;
}


//get Relationship Type
Relationship::RelType Relationship::getRelType(){
     if (relName == "follows") {
        return FOLLOWS;
    } else if (relName == "follows*"){
        return FOLLOWSSTAR;
    } else if (relName == "parent"){
        return PARENT;
	} else if (relName == "parent*") {
	    return PARENTSTAR;
    } else if (relName == "modifies"){
		return MODIFIES;
	} else if (relName=="uses"){
		return USES;
	} else if (relName=="calls"){
		return CALLS;
	} else if (relName=="calls*"){
		return CALLSSTAR;
	} else if (relName=="next"){
		return NEXT;
	} else if (relName=="next*"){
		return NEXTSTAR;
	} else if (relName=="affects"){
		return AFFECTS;
	} else if (relName=="affects*"){
		return AFFECTSSTAR;
	} else if (relName=="with"){
		return WITH;
	} else if (relName=="pattern"){
		return PATTERN;
	}
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

string Relationship::getWithSyn(int index){
	return withSyn[index];
}

void Relationship::setToken1(string tk1){
	token1 = tk1;
}

void Relationship::setToken2(string tk2){
	token2 = tk2;
}

void Relationship::setPatternSyn(string newPatternSyn){
	patternSyn = newPatternSyn;
}

void Relationship::setWithSyn(string newWithSyn,int index){
	withSyn[index] = newWithSyn;
}