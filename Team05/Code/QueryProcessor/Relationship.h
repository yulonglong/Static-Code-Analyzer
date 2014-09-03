#pragma once
#ifndef RELATIONSHIP_H
#define RELATIONSHIP_H

#include <string>
#include <iostream>
#include <string>

using namespace std;

class Relationship
{
    private:
		string patternSyn; //for pattern
		string withSyn[2]; //there are two possible with syn
        string relName;
        string token1;
        string token2;

    public:
        enum RelType{FOLLOWS, FOLLOWSSTAR, PARENT, PARENTSTAR, MODIFIES, USES, CALLS, CALLSSTAR, NEXT, NEXTSTAR, AFFECTS, AFFECTSSTAR, WITH, PATTERN};

        Relationship(string, string, string);

        RelType getRelType();
        string getToken1();
        string getToken2();
		string getPatternSyn();
		string getWithSyn(int);
		
		void setToken1(string);
		void setToken2(string);
		void setPatternSyn(string);
		void setWithSyn(string,int);

};

#endif // RELATIONSHIP_H_INCLUDED