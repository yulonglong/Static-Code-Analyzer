#include <iostream>
#include <string>
#include "Query.h"

Query(string s)
{
    selectedSyn = s;
}

string getSelectedSyn()
{
    return selectedSyn;
}

void addRelationship(Relationship r)
{
    relVect.push_back(r);
}

vector<Relationship> getRelVect()
{
    return relVect;
}

void addSynTable(unordered_map<string, SType> map)
{
	synTable = map;
}

unordered_map<string, SType> getSynTable()
{
	return synTable;
}
