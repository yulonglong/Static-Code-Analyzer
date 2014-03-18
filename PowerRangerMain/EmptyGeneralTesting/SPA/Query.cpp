
#include <iostream>
#include <string>
#include "Query.h"

using namespace std;

Query::Query(string v)
{
    qVarName = v;
}

string Query::getQVarName()
{
    return qVarName;
}

void Query::addRelationship(Relationship r)
{
    relVect.push_back(r);
}

vector<Relationship> Query::getRelVect()
{
    return relVect;
}
