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
        enum RelType{FOLLOWS, FOLLOWSSTAR, PARENT, PARENTSTAR};

        Relationship(string, string, string);

        RelType getRelType();
        string getToken1();
        string getToken2();
};

#endif // RELATIONSHIP_H_INCLUDED