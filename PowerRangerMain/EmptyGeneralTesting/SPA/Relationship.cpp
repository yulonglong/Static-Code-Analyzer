
#include <iostream>
#include <string>
#include "Relationship.h"

using namespace std;

Relationship::Relationship(string rn, string v1, string v2)
{
    relName = rn;
    token1 = v1;
    token2 = v2;
}

Relationship::RelType Relationship::getRelType()
{
     if (relName == "FOLLOWS") {
        return FOLLOWS;
    } else if (relName == "FOLLOWSSTAR"){
        return FOLLOWSSTAR;
    } else if (relName == "PARENT"){
        return PARENT;
    } else if (relName == "PARENTSTAR"){
        return PARENTSTAR;
    }
}

string Relationship::getToken1()
{
    return token1;
}

string Relationship::getToken2()
{
    return token2;
}
