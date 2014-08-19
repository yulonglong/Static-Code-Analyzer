#include <cppunit/config/SourcePrefix.h>
#include "Relationship.h"
#include "Query.h"
#include "QueryParser.h"
#include "TestQueryParser.h"
#include "PKB.h"

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void 
QueryParserTest::setUp(){
}

void 
QueryParserTest::tearDown(){
}

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( QueryParserTest );

void QueryParserTest::testQueryAssignSelectModifies(){
	string query = "assign a; Select a such that Modifies(a, \"oSCar\")";
	QueryParser qp;
	bool isValid = true;
	Query parsedQuery = qp.parse(query,isValid);
	
	string selectedSyn = parsedQuery.getSelectedSyn();
	string patternSyn = parsedQuery.getPatternSyn();
	vector<Relationship> relVect = parsedQuery.getRelVect();
	unordered_map<string, TypeTable::SynType> synTable = parsedQuery.getSynTable();

	unordered_map<string, TypeTable::SynType>::iterator iter;
	iter= synTable.begin();

	string expectedSelectedSyn = "a";
	string expectedPatternSyn = "";
	vector<Relationship> expectedRelVect;
	Relationship tempRel("Modifies","a","\"oSCar\"");
	expectedRelVect.push_back(tempRel);
	unordered_map<string, TypeTable::SynType> expectedSynTable;
	expectedSynTable.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
	expectedSynTable.insert(make_pair("a", TypeTable::ASSIGN));

	unordered_map<string, TypeTable::SynType>::iterator expectedIter;
	expectedIter= expectedSynTable.begin();

	CPPUNIT_ASSERT_EQUAL(expectedSelectedSyn,selectedSyn);
	CPPUNIT_ASSERT_EQUAL(expectedPatternSyn,patternSyn);
	CPPUNIT_ASSERT_EQUAL(expectedRelVect[0].getRelType(),relVect[0].getRelType());
	CPPUNIT_ASSERT_EQUAL(expectedRelVect[0].getToken1(),relVect[0].getToken1());
	CPPUNIT_ASSERT_EQUAL(expectedRelVect[0].getToken2(),relVect[0].getToken2());
	CPPUNIT_ASSERT_EQUAL(expectedIter->first,iter->first);
	CPPUNIT_ASSERT_EQUAL(expectedIter->second,iter->second);
	iter++; expectedIter++;
	CPPUNIT_ASSERT_EQUAL(expectedIter->first,iter->first);
	CPPUNIT_ASSERT_EQUAL(expectedIter->second,iter->second);

	return;
}
