//@author Steven Kester Yuwono
//QueryParser.h

#ifndef QUERYPARSER_H
#define QUERYPARSER_H

#include "Query.h"
#include "Relationship.h"
#include <string>
#include <vector>

using namespace std;

class QueryParser{
private:
	//regex string
	string varName;
	string select;
	string suchThat;
	string freeString;
	string designEntity;
	string relRef;
	string pattern;

	//query class table
	vector<string> selectStatement;
	unordered_map<string, TypeTable::SynType> synMap;

	//methods
	bool parseDesignEntity(string);
	bool parseSelectOnly(string);
	bool parsePattern(string);
	bool parseRelational(string);
	bool parseRelationalWithPattern(string);
	Query makeQuery(vector<string>, unordered_map<string, TypeTable::SynType>);

public:
	QueryParser();
	Query parse(string, bool &);
};

#endif