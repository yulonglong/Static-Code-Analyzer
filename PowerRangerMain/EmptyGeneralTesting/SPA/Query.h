#ifndef QUERY_H
#define QUERY_H
#include "Relationship.h"
#include <string>
#include <vector>
#include <unordered_map>

class Query
{
    public:
        Query(std::string);
		std::string getSelectedSyn();
        void addRelationship(Relationship);
        std::vector<Relationship> getRelVect();
		enum SType{ASSIGN, IF, WHILE, BOOLEAN};
		void addSynTable(std::unordered_map<std::string, Query::SType>);
		std::unordered_map<std::string, Query::SType> getSynTable();

	private:
        std::string selectedSyn; 
        std::vector<Relationship> relVect;
		std::unordered_map<std::string, Query::SType> synTable;
};

#endif // QUERY_H_INCLUDED
