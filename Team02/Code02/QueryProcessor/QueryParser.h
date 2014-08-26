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
	//constant string
	static const string MODIFIES;
	static const string USES;
	static const string CALLS;
	static const string CALLSSTAR;
	static const string PARENT;
	static const string PARENTSTAR;
	static const string FOLLOWS;
	static const string FOLLOWSSTAR;
	static const string NEXT;
	static const string NEXTSTAR;
	static const string AFFECTS;
	static const string AFFECTSSTAR;

	//regex string
	static const string IDENT;
	static const string select;
	static const string suchThat;
	static const string freeString;
	static const string designEntity;
	static const string relRef;
	static const string pattern;

	//query class table
	vector<string> selectStatement;
	unordered_map<string, TypeTable::SynType> synMap;

	//methods
	bool parseDesignEntity(string);
	bool parseSelectOnly(string);
	bool parsePattern(string);
	bool parseRelational(string);
	bool parseRelationalWithPattern(string);
	Query constructAndValidateQuery(vector<string>, unordered_map<string, TypeTable::SynType>,bool&);

public:
	QueryParser();
	Query queryParse(string queryStr, bool& valid);
};

#endif