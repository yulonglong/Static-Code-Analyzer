#ifndef QUERYPARSER_H
#define QUERYPARSER_H

#include "Query.h"
#include "Relationship.h"
#include "TypeTable.h"
#include <string>
#include <vector>
#include <cstring>

using namespace std;

class QueryParser{
private:
	// RECORD ALL THE QUERIES PARSED
	vector<Query> queries;

	// ADD ONE QUERY TO THE QUERIES RECORD
	void addQuery(Query);
	
	// PARSE THE SYNONYMS DECLARATION
	unordered_map<string, Query::SType> parseSynonyms(string);

	// PARSE ONE QUERY STRING TO A VECTOR OF TOKENS
	vector<string> parseQuery(string);

	// MAKE A QUERY OBJECT FROM A VECTOR OF TOKENS AND A SYNONYM MAP
	Query makeQuery(vector<string>, unordered_map<string, Query::SType>);

	// MAP OF SYNONYMS AND THEIR TYPES
	unordered_map<string, Query::SType> synMap;

public:
	// DEFAULT CONSTRUCTOR
	QueryParser();

	// GET ALL THE QUERIES PARSED IN THIS SESSION
	vector<Query> getQueries();

	// PARSE ONE STRING CONTAINING SYNONYMS DECLARATION AND QUERY WITH LIMITATIONS:
	// 1. can only handle synonym declaration for assign, while and if.
	// 2. query is limited to follows, followsstar, parent, parentstar
	// 3. relationship and select keywords must be CAPITALIZED, e.g. Select a such that FOLLOWS(a, 2);
	// 4. boolean keyword must be in uppercase, i.e. BOOLEAN
	// other keywords are expected to be in lowercase, i.e. such that, assign, while, if.
	Query parse(string);
};

#endif