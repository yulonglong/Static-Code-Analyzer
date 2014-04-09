#include "Relationship.h"

Relationship::Relationship(string rn, string v1, string v2)
{
    relName = rn;
    token1 = v1;
    token2 = v2;
}


Relationship::RelType Relationship::getRelType()
{
     if (relName == "Follows") {
        return FOLLOWS;
    } else if (relName == "Follows*"){
        return FOLLOWSSTAR;
    } else if (relName == "Parent"){
        return PARENT;
    } else if(relName == "Modifies"){
		return MODIFIES;
	} else if(relName=="Uses"){
		return USES;
	}else{
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
