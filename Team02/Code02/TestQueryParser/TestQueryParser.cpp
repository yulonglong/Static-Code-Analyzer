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
	for(int i=0;i<expectedSynTable.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedIter->first,iter->first);
		CPPUNIT_ASSERT_EQUAL(expectedIter->second,iter->second);
		iter++;
		expectedIter++;
	}
	return;
}

void QueryParserTest::testQueryAssignVariableSelectModifies(){
	string query = " assign a; variable v; Select a such that Modifies (a,v) ";
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
	Relationship tempRel("Modifies","a","v");
	expectedRelVect.push_back(tempRel);
	unordered_map<string, TypeTable::SynType> expectedSynTable;
	expectedSynTable.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
	expectedSynTable.insert(make_pair("a", TypeTable::ASSIGN));
	expectedSynTable.insert(make_pair("v", TypeTable::VARIABLE));

	unordered_map<string, TypeTable::SynType>::iterator expectedIter;
	expectedIter= expectedSynTable.begin();

	CPPUNIT_ASSERT_EQUAL(expectedSelectedSyn,selectedSyn);
	CPPUNIT_ASSERT_EQUAL(expectedPatternSyn,patternSyn);
	CPPUNIT_ASSERT_EQUAL(expectedRelVect[0].getRelType(),relVect[0].getRelType());
	CPPUNIT_ASSERT_EQUAL(expectedRelVect[0].getToken1(),relVect[0].getToken1());
	CPPUNIT_ASSERT_EQUAL(expectedRelVect[0].getToken2(),relVect[0].getToken2());
	for(int i=0;i<expectedSynTable.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedIter->first,iter->first);
		CPPUNIT_ASSERT_EQUAL(expectedIter->second,iter->second);
		iter++;
		expectedIter++;
	}

	return;
}

void QueryParserTest::testQueryStmtSelectUses(){
	string query = "  stmt s  ; Select s such that Uses (s,\"delta\")  ";
	QueryParser qp;
	bool isValid = true;
	Query parsedQuery = qp.parse(query,isValid);
	
	string selectedSyn = parsedQuery.getSelectedSyn();
	string patternSyn = parsedQuery.getPatternSyn();
	vector<Relationship> relVect = parsedQuery.getRelVect();
	unordered_map<string, TypeTable::SynType> synTable = parsedQuery.getSynTable();

	unordered_map<string, TypeTable::SynType>::iterator iter;
	iter= synTable.begin();

	string expectedSelectedSyn = "s";
	string expectedPatternSyn = "";
	vector<Relationship> expectedRelVect;
	Relationship tempRel("Uses","s","\"delta\"");
	expectedRelVect.push_back(tempRel);
	unordered_map<string, TypeTable::SynType> expectedSynTable;
	expectedSynTable.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
	expectedSynTable.insert(make_pair("s", TypeTable::STMT));

	unordered_map<string, TypeTable::SynType>::iterator expectedIter;
	expectedIter= expectedSynTable.begin();

	CPPUNIT_ASSERT_EQUAL(expectedSelectedSyn,selectedSyn);
	CPPUNIT_ASSERT_EQUAL(expectedPatternSyn,patternSyn);
	CPPUNIT_ASSERT_EQUAL(expectedRelVect[0].getRelType(),relVect[0].getRelType());
	CPPUNIT_ASSERT_EQUAL(expectedRelVect[0].getToken1(),relVect[0].getToken1());
	CPPUNIT_ASSERT_EQUAL(expectedRelVect[0].getToken2(),relVect[0].getToken2());
	for(int i=0;i<expectedSynTable.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedIter->first,iter->first);
		CPPUNIT_ASSERT_EQUAL(expectedIter->second,iter->second);
		iter++;
		expectedIter++;
	}
	return;
}


void QueryParserTest::testQueryStmtSelectParentStar(){
	string query = "stmt   s ;   Select   s  such  that Parent*(5,s)  ";
	QueryParser qp;
	bool isValid = true;
	Query parsedQuery = qp.parse(query,isValid);
	
	string selectedSyn = parsedQuery.getSelectedSyn();
	string patternSyn = parsedQuery.getPatternSyn();
	vector<Relationship> relVect = parsedQuery.getRelVect();
	unordered_map<string, TypeTable::SynType> synTable = parsedQuery.getSynTable();

	unordered_map<string, TypeTable::SynType>::iterator iter;
	iter= synTable.begin();

	string expectedSelectedSyn = "s";
	string expectedPatternSyn = "";
	vector<Relationship> expectedRelVect;
	Relationship tempRel("Parent*","5","s");
	expectedRelVect.push_back(tempRel);
	unordered_map<string, TypeTable::SynType> expectedSynTable;
	expectedSynTable.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
	expectedSynTable.insert(make_pair("s", TypeTable::STMT));

	unordered_map<string, TypeTable::SynType>::iterator expectedIter;
	expectedIter= expectedSynTable.begin();

	CPPUNIT_ASSERT_EQUAL(expectedSelectedSyn,selectedSyn);
	CPPUNIT_ASSERT_EQUAL(expectedPatternSyn,patternSyn);
	CPPUNIT_ASSERT_EQUAL(expectedRelVect[0].getRelType(),relVect[0].getRelType());
	CPPUNIT_ASSERT_EQUAL(expectedRelVect[0].getToken1(),relVect[0].getToken1());
	CPPUNIT_ASSERT_EQUAL(expectedRelVect[0].getToken2(),relVect[0].getToken2());
	for(int i=0;i<expectedSynTable.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedIter->first,iter->first);
		CPPUNIT_ASSERT_EQUAL(expectedIter->second,iter->second);
		iter++;
		expectedIter++;
	}
	return;
}



void QueryParserTest::testQueryAssignSelectModifiesPattern(){
	string query = "assign a, a1; Select a such that Modifies (a, \"x\") pattern a1(_,_) ";
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
	string expectedPatternSyn = "a1";
	vector<Relationship> expectedRelVect;
	Relationship tempRel1("Modifies","a","\"x\"");
	expectedRelVect.push_back(tempRel1);
	Relationship tempRel2("pattern","_","_");
	expectedRelVect.push_back(tempRel2);
	unordered_map<string, TypeTable::SynType> expectedSynTable;
	expectedSynTable.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
	expectedSynTable.insert(make_pair("a", TypeTable::ASSIGN));
	expectedSynTable.insert(make_pair("a1", TypeTable::ASSIGN));

	unordered_map<string, TypeTable::SynType>::iterator expectedIter;
	expectedIter= expectedSynTable.begin();

	CPPUNIT_ASSERT_EQUAL(expectedSelectedSyn,selectedSyn);
	CPPUNIT_ASSERT_EQUAL(expectedPatternSyn,patternSyn);
	for(int i=0;i<expectedRelVect.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getRelType(),relVect[i].getRelType());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1(),relVect[i].getToken1());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2(),relVect[i].getToken2());
	}
	for(int i=0;i<expectedSynTable.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedIter->first,iter->first);
		CPPUNIT_ASSERT_EQUAL(expectedIter->second,iter->second);
		iter++;
		expectedIter++;
	}
	return;
}


void QueryParserTest::testQueryComplex1(){
	string query = " assign a  ;  stmt s; variable v; assign a1; variable v2; Select a such that Uses (s,v) pattern a1  (v2,  _\"asd\"_  )  ";
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
	string expectedPatternSyn = "a1";
	vector<Relationship> expectedRelVect;
	Relationship tempRel1("Uses","s","v");
	expectedRelVect.push_back(tempRel1);
	Relationship tempRel2("pattern","v2","_\"asd\"_");
	expectedRelVect.push_back(tempRel2);
	unordered_map<string, TypeTable::SynType> expectedSynTable;
	expectedSynTable.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
	expectedSynTable.insert(make_pair("a", TypeTable::ASSIGN));
	expectedSynTable.insert(make_pair("s", TypeTable::STMT));
	expectedSynTable.insert(make_pair("v2", TypeTable::VARIABLE));
	expectedSynTable.insert(make_pair("a1", TypeTable::ASSIGN));
	expectedSynTable.insert(make_pair("v", TypeTable::VARIABLE));
	

	unordered_map<string, TypeTable::SynType>::iterator expectedIter;
	expectedIter= expectedSynTable.begin();

	CPPUNIT_ASSERT_EQUAL(expectedSelectedSyn,selectedSyn);
	CPPUNIT_ASSERT_EQUAL(expectedPatternSyn,patternSyn);
	for(int i=0;i<expectedRelVect.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getRelType(),relVect[i].getRelType());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1(),relVect[i].getToken1());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2(),relVect[i].getToken2());
	}
	for(int i=0;i<expectedSynTable.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedIter->first,iter->first);
		CPPUNIT_ASSERT_EQUAL(expectedIter->second,iter->second);
		iter++;
		expectedIter++;
	}
	return;
}