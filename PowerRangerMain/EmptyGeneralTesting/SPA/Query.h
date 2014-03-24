#ifndef QUERY_H
#define QUERY_H
#include "Relationship.h"
#include <string>
#include <vector>
#include <unordered_map>
#include "TypeTable.h"

class Query
{
    public:
        Query(std::string);
		std::string getSelectedSyn();
        void addRelationship(Relationship);
        std::vector<Relationship> getRelVect();
		void addSynTable(std::unordered_map<std::string, SType>);
		std::unordered_map<std::string, SType> getSynTable();

	private:
        std::string selectedSyn; 
        std::vector<Relationship> relVect;
		std::unordered_map<std::string, SType> synTable;
};

#endif // QUERY_H_INCLUDED
