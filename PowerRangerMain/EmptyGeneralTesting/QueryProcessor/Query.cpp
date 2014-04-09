#include "Query.h"

Query::Query()
{
}

void Query::setSelectedSyn(string s){
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

void Query::setSynTable(unordered_map<string, TypeTable::SynType> map)
{
	synTable = map;
}

unordered_map<string, TypeTable::SynType> Query::getSynTable()
{
	return synTable;
}
