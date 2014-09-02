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
	//lexical rules
	static const string DIGIT;
	static const string LETTER;
	static const string INTEGER;
	static const string IDENT;

	//auxiliary grammar rules
	static const string synonym;
	static const string attrName;
	static const string entRef;
	static const string varRef;
	static const string stmtRef;
	static const string lineRef;
	static const string designEntity;
	static const string attrRef;
	static const string elem;
	static const string tuple;
	static const string resultCl;

	static const string select;
	static const string such;
	static const string that;
	static const string freeString;
	static const string expr;

	static const string ModifiesP;
	static const string ModifiesS;
	static const string UsesP;
	static const string UsesS;
	static const string Calls;
	static const string CallsT;
	static const string Parent;
	static const string ParentT;
	static const string Follows;
	static const string FollowsT;
	static const string Next;
	static const string NextT;
	static const string Affects;
	static const string AffectsT;
	static const string TESTSTR;

	static const string relRef;
	static const string relCond;
	static const string suchThatCl;
	static const string selectCl;

	static const string expressionSpec;
	static const string assignCl;
	static const string whileCl;
	static const string ifCl;
	static const string pattern;
	static const string patternCond;
	static const string patternCl;
	

	//constant string
	static const string BOOLEAN;
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
	static const string PATTERN;
	static const string WITH;

	//clauses param
	static const string modifiesParam[2];
	static const string usesParam[2];
	static const string callsParam[2];
	static const string callsStarParam[2];
	static const string parentParam[2];
	static const string parentStarParam[2];
	static const string followsParam[2];
	static const string followsStarParam[2];
	static const string nextParam[2];
	static const string nextStarParam[2];
	static const string affectsParam[2];
	static const string affectsStarParam[2];

	//query class table
	vector<string> selectStatement;
	unordered_map<string, TypeTable::SynType> synMap;

	//common methods
	string stringToLower(string);
	bool regexMatch(string, string);
	bool regexMatchWithResult(string, string, vector<string>&);

	//QueryParser methods
	bool parseDesignEntity(string);
	bool parseSelectOnly(string);
	bool parsePattern(string);
	bool parseRelational(string);
	bool parseRelationalWithPattern(string);

	//QueryValidatior methods
	void deepCopyTableParam(string[2], string);
	Query constructAndValidateQuery(vector<string>, unordered_map<string, TypeTable::SynType>,bool&);

public:
	QueryParser();
	Query queryParse(string queryStr, bool& valid);
};

#endif