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
        string relName;
        string token1;
        string token2;

    public:
        enum RelType{FOLLOWS, FOLLOWSSTAR, PARENT, PARENTSTAR, MODIFIES, USES, PATTERN};

        Relationship(string, string, string);

        RelType getRelType();
        string getToken1();
        string getToken2();
		void setToken1(string);
		void setToken2(string);

};

#endif // RELATIONSHIP_H_INCLUDED