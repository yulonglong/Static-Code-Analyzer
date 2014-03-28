#ifndef QUERY_H
#define QUERY_H
#include "Relationship.h"
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Query
{
    public:
        Query(string);
		string getSelectedSyn();
        void addRelationship(Relationship);
        vector<Relationship> getRelVect();
		enum SType{ASSIGN, IF, WHILE, BOOLEAN};
		void addSynTable(unordered_map<string, SType>);
		unordered_map<string, SType> getSynTable();

	private:
        string selectedSyn; 
        vector<Relationship> relVect;
		unordered_map<string, SType> synTable;
};

#endif // QUERY_H_INCLUDED
