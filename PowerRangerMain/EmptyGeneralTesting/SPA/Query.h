
#ifndef QUERY_H
#define QUERY_H
#include "Relationship.h"
#include <string>
#include <vector>

class Query
{
    private:
        std::string qVarName;
        std::vector<Relationship> relVect;

    public:
        Query(std::string);
        std::string getQVarName();
        void addRelationship(Relationship);
        std::vector<Relationship> getRelVect();
};

#endif // QUERY_H_INCLUDED
