#pragma once
#ifndef QUERY_H
#define QUERY_H

#include "Relationship.h"
#include <string>
#include "TypeTable.h"
#include <vector>
#include <unordered_map>

using namespace std;

class Query
{
    public:
        Query();
		vector<int> getSelectedSyn();
		void setSelectedSyn(vector<int> s);
		string getPatternSyn();
		void setPatternSyn(string s);
        vector<Relationship> getRelVect();
		unordered_map<string, TypeTable::SynType> getSynTable();
		void setSynTable(unordered_map<string, TypeTable::SynType>);
		void addRelationship(Relationship);

	private:
		vector<int> selectedSyn; 
		string patternSyn;
        vector<Relationship> relVect;
		unordered_map<string, TypeTable::SynType> synTable;
};

#endif // QUERY_H_INCLUDED
