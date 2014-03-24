#include <iostream>
#include <string>
#include "Query.h"

using namespace std;

Query::Query(string s)
{
    selectedSyn = s;
}

string Query::getSelectedSyn()
{
    return selectedSyn;
}

void Query::addRelationship(Relationship r)
{
    relVect.push_back(r);
}

vector<Relationship> Query::getRelVect()
{
    return relVect;
}

void Query::addSynTable(unordered_map<string, SType> map)
{
	synTable = map;
}

unordered_map<std::string, SType> Query::getSynTable()
{
	return synTable;
}
