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
	//public:
		//enum SynType{ASSIGN, IF, WHILE, STMT, BOOLEAN, CALL,INVALID};
		//static SynType getSynType(std::string);
    public:
        Query(string);
		string getSelectedSyn();
        void addRelationship(Relationship);
        vector<Relationship> getRelVect();
		
		void addSynTable(unordered_map<string, TypeTable::SynType>);
		unordered_map<string, TypeTable::SynType> getSynTable();

	private:
        string selectedSyn; 
        vector<Relationship> relVect;
		unordered_map<string, TypeTable::SynType> synTable;
};

#endif // QUERY_H_INCLUDED
