#include "Query.h"

Query::SynType Query::getSynType(string word)
{
	if(word=="assign"){
		return Query::ASSIGN;
	}
	else if(word=="if"){
		return Query::IF;
	}
	else if(word=="while"){
		return Query::WHILE;
	}
	else if(word=="stmt"){
		return Query::STMT;
	}
	else if(word=="boolean"){
		return Query::BOOLEAN;
	}
	else if(word=="call"){
		return Query::CALL;
	}
	else{
		return Query::INVALID;
	}
}

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

void Query::addSynTable(unordered_map<string, SynType> map)
{
	synTable = map;
}

unordered_map<string, Query::SynType> Query::getSynTable()
{
	return synTable;
}
