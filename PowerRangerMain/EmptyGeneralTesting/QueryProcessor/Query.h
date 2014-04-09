#pragma once
#ifndef QUERY_H
#define QUERY_H

#include "Relationship.h"
#include "PKB.h"
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Query
{
    public:
        Query();
		string getSelectedSyn();
		void setSelectedSyn(string s);
        vector<Relationship> getRelVect();
		unordered_map<string, TypeTable::SynType> getSynTable();
		void setSynTable(unordered_map<string, TypeTable::SynType>);
		void addRelationship(Relationship);

	private:
		string selectedSyn; 
        vector<Relationship> relVect;
		unordered_map<string, TypeTable::SynType> synTable;
};

#endif // QUERY_H_INCLUDED
