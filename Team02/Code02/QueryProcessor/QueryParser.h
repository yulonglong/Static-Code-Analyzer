#ifndef QUERYPARSER_H
#define QUERYPARSER_H

#include "Query.h"
#include "Relationship.h"
#include <string>
#include <vector>

using namespace std;

class QueryParser{
private:
	// VALIDATION 
	int sLength;
	int declarationCounter;
	int selectCounter;
	int statementCounter;
	int tokenCounter;
	int expressionTokenCounter;
	int selectCase;
	string s;
	string nextToken;
	string statement;
	vector<string> statements;
	vector<string> tokens;
	vector<string> expressionTokens;
	vector<string> selectStatement;

	void bootstrap();

	void generateTokens();
	bool generateDeclarationTokens();
	string getFirstToken();
	string getNextToken();
	bool generateStatements();
	string getNextStatement();
	bool generateSelectTokens();
	bool generateExpressionTokens();
	string getNextExpressionToken();

	bool match(string);
	bool declaration();
	bool select();
	bool designEntity();
	bool synonym();
	bool ident();
	bool relRef();
	bool entRef();
	bool stmtRef();
	bool integer();
	bool suchThat();
	bool pattern();
	bool tokenizePattern(string);
	bool tokenizeSuchthat(string);

	bool synAssign();
	bool expressionSpec();
	bool xpSpec1();
	bool xpSpec2();
	bool xpSpec3();
	bool factor();
	bool varName();

	bool modifiesS();
	bool usesS();
	bool parent(); 
	bool parentT(); 
	bool follows(); 
	bool followsT();

	// PARSING
	// RECORD ALL THE QUERIES PARSED
	vector<Query> queries;

	// ADD ONE QUERY TO THE QUERIES RECORD
	void addQuery(Query);
	
	// PARSE THE SYNONYMS DECLARATION
	// unordered_map<string, TypeTable::SynType> parseSynonyms();

	// PARSE ONE QUERY STRING TO A VECTOR OF TOKENS
	vector<string> parseQuery(string);

	// MAKE A QUERY OBJECT FROM A VECTOR OF TOKENS AND A SYNONYM MAP
	Query makeQuery(vector<string>, unordered_map<string, TypeTable::SynType>);

	// MAP OF SYNONYMS AND THEIR TYPES
	unordered_map<string, TypeTable::SynType> synMap;

public:
	QueryParser();

	// VALIDATION
	bool validate(string);
	vector<string> getStatements();

	// PARSING
	vector<Query> getQueries();
	Query parse();
};

#endif