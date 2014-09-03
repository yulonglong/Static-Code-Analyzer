//@author Steven Kester Yuwono
//TestQueryParser.cpp

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
	Query parsedQuery = qp.queryParse(query,isValid);

	bool expectedIsValid = true;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	
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
	Query parsedQuery = qp.queryParse(query,isValid);

	bool expectedIsValid = true;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	
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
	Query parsedQuery = qp.queryParse(query,isValid);

	bool expectedIsValid = true;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	
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
	Query parsedQuery = qp.queryParse(query,isValid);

	bool expectedIsValid = true;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	
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
	Query parsedQuery = qp.queryParse(query,isValid);

	bool expectedIsValid = true;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	
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
	Query parsedQuery = qp.queryParse(query,isValid);

	bool expectedIsValid = true;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	
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
	expectedSynTable.insert(make_pair("v", TypeTable::VARIABLE));
	expectedSynTable.insert(make_pair("a1", TypeTable::ASSIGN));
	expectedSynTable.insert(make_pair("v2", TypeTable::VARIABLE));
	

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


void QueryParserTest::testQueryFollows1(){
	string query = " assign a; while w; Select a such that Follows(w, a)";
	QueryParser qp;
	bool isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	bool expectedIsValid = true;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	
	string selectedSyn = parsedQuery.getSelectedSyn();
	string patternSyn = parsedQuery.getPatternSyn();
	vector<Relationship> relVect = parsedQuery.getRelVect();
	unordered_map<string, TypeTable::SynType> synTable = parsedQuery.getSynTable();

	unordered_map<string, TypeTable::SynType>::iterator iter;
	iter= synTable.begin();

	string expectedSelectedSyn = "a";
	string expectedPatternSyn = "";
	vector<Relationship> expectedRelVect;
	Relationship tempRel("Follows","w","a");
	expectedRelVect.push_back(tempRel);
	unordered_map<string, TypeTable::SynType> expectedSynTable;
	expectedSynTable.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
	expectedSynTable.insert(make_pair("a", TypeTable::ASSIGN));
	expectedSynTable.insert(make_pair("w", TypeTable::WHILE));

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


void QueryParserTest::testQueryModifies1(){
	string query = "variable v; assign a; Select v such that Modifies(a, v)";
	QueryParser qp;
	bool isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	bool expectedIsValid = true;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	
	string selectedSyn = parsedQuery.getSelectedSyn();
	string patternSyn = parsedQuery.getPatternSyn();
	vector<Relationship> relVect = parsedQuery.getRelVect();
	unordered_map<string, TypeTable::SynType> synTable = parsedQuery.getSynTable();

	unordered_map<string, TypeTable::SynType>::iterator iter;
	iter= synTable.begin();

	string expectedSelectedSyn = "v";
	string expectedPatternSyn = "";
	vector<Relationship> expectedRelVect;
	Relationship tempRel("Modifies","a","v");
	expectedRelVect.push_back(tempRel);
	unordered_map<string, TypeTable::SynType> expectedSynTable;
	expectedSynTable.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
	expectedSynTable.insert(make_pair("v", TypeTable::VARIABLE));
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


void QueryParserTest::testQueryModifies2(){
	string query = "assign a, a1; Select a such that Modifies(a,a1)";
	QueryParser qp;
	bool isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	bool expectedIsValid = true;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	
	string selectedSyn = parsedQuery.getSelectedSyn();
	string patternSyn = parsedQuery.getPatternSyn();
	vector<Relationship> relVect = parsedQuery.getRelVect();
	unordered_map<string, TypeTable::SynType> synTable = parsedQuery.getSynTable();

	unordered_map<string, TypeTable::SynType>::iterator iter;
	iter= synTable.begin();

	string expectedSelectedSyn = "a";
	string expectedPatternSyn = "";
	vector<Relationship> expectedRelVect;
	Relationship tempRel("Modifies","a","a1");
	expectedRelVect.push_back(tempRel);
	unordered_map<string, TypeTable::SynType> expectedSynTable;
	expectedSynTable.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
	expectedSynTable.insert(make_pair("a", TypeTable::ASSIGN));
	expectedSynTable.insert(make_pair("a1", TypeTable::ASSIGN));

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

void QueryParserTest::testQueryPattern1(){
	string query = "assign a; Select a pattern a(a,_)";
	QueryParser qp;
	bool isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	bool expectedIsValid = true;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	
	string selectedSyn = parsedQuery.getSelectedSyn();
	string patternSyn = parsedQuery.getPatternSyn();
	vector<Relationship> relVect = parsedQuery.getRelVect();
	unordered_map<string, TypeTable::SynType> synTable = parsedQuery.getSynTable();

	unordered_map<string, TypeTable::SynType>::iterator iter;
	iter= synTable.begin();

	string expectedSelectedSyn = "a";
	string expectedPatternSyn = "a";
	vector<Relationship> expectedRelVect;
	Relationship tempRel("pattern","a","_");
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

void QueryParserTest::testQueryWith1(){
	string query = "variable v; procedure p; Select p with p.procName = v.varName ";
	QueryParser qp;
	bool isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	bool expectedIsValid = true;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	
	string selectedSyn = parsedQuery.getSelectedSyn();
	string patternSyn = parsedQuery.getPatternSyn();
	vector<Relationship> relVect = parsedQuery.getRelVect();
	unordered_map<string, TypeTable::SynType> synTable = parsedQuery.getSynTable();

	unordered_map<string, TypeTable::SynType>::iterator iter;
	iter= synTable.begin();

	string expectedSelectedSyn = "p";
	vector<Relationship> expectedRelVect;
	Relationship tempRel("with","procName","varName");
	tempRel.setWithSyn("p",0);
	tempRel.setWithSyn("v",1);
	expectedRelVect.push_back(tempRel);
	unordered_map<string, TypeTable::SynType> expectedSynTable;
	expectedSynTable.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
	expectedSynTable.insert(make_pair("v", TypeTable::VARIABLE));
	expectedSynTable.insert(make_pair("p", TypeTable::PROCEDURE));

	unordered_map<string, TypeTable::SynType>::iterator expectedIter;
	expectedIter= expectedSynTable.begin();

	CPPUNIT_ASSERT_EQUAL(expectedSelectedSyn,selectedSyn);
	CPPUNIT_ASSERT_EQUAL(expectedRelVect[0].getRelType(),relVect[0].getRelType());
	CPPUNIT_ASSERT_EQUAL(expectedRelVect[0].getToken1(),relVect[0].getToken1());
	CPPUNIT_ASSERT_EQUAL(expectedRelVect[0].getToken2(),relVect[0].getToken2());
	CPPUNIT_ASSERT_EQUAL(expectedRelVect[0].getWithSyn(0),relVect[0].getWithSyn(0));
	CPPUNIT_ASSERT_EQUAL(expectedRelVect[0].getWithSyn(1),relVect[0].getWithSyn(1));
	for(int i=0;i<expectedSynTable.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedIter->first,iter->first);
		CPPUNIT_ASSERT_EQUAL(expectedIter->second,iter->second);
		iter++;
		expectedIter++;
	}

	return;
}

void QueryParserTest::testQueryWith2(){
	string query = "stmt s; constant c; Select s with s.stmt#=c.value ";
	QueryParser qp;
	bool isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	bool expectedIsValid = true;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	
	string selectedSyn = parsedQuery.getSelectedSyn();
	string patternSyn = parsedQuery.getPatternSyn();
	vector<Relationship> relVect = parsedQuery.getRelVect();
	unordered_map<string, TypeTable::SynType> synTable = parsedQuery.getSynTable();

	unordered_map<string, TypeTable::SynType>::iterator iter;
	iter= synTable.begin();

	string expectedSelectedSyn = "s";
	vector<Relationship> expectedRelVect;
	Relationship tempRel("with","stmt#","value");
	tempRel.setWithSyn("s",0);
	tempRel.setWithSyn("c",1);
	expectedRelVect.push_back(tempRel);
	unordered_map<string, TypeTable::SynType> expectedSynTable;
	expectedSynTable.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
	expectedSynTable.insert(make_pair("s", TypeTable::STMT));
	expectedSynTable.insert(make_pair("c", TypeTable::CONSTANT));

	unordered_map<string, TypeTable::SynType>::iterator expectedIter;
	expectedIter= expectedSynTable.begin();

	CPPUNIT_ASSERT_EQUAL(expectedSelectedSyn,selectedSyn);
	CPPUNIT_ASSERT_EQUAL(expectedRelVect[0].getRelType(),relVect[0].getRelType());
	CPPUNIT_ASSERT_EQUAL(expectedRelVect[0].getToken1(),relVect[0].getToken1());
	CPPUNIT_ASSERT_EQUAL(expectedRelVect[0].getToken2(),relVect[0].getToken2());
	CPPUNIT_ASSERT_EQUAL(expectedRelVect[0].getWithSyn(0),relVect[0].getWithSyn(0));
	CPPUNIT_ASSERT_EQUAL(expectedRelVect[0].getWithSyn(1),relVect[0].getWithSyn(1));
	for(int i=0;i<expectedSynTable.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedIter->first,iter->first);
		CPPUNIT_ASSERT_EQUAL(expectedIter->second,iter->second);
		iter++;
		expectedIter++;
	}

	return;
}

void QueryParserTest::testQueryWith3(){
	string query = "prog_line n; stmt s; Select s such that Follows*(n,s) with n=10";
	QueryParser qp;
	bool isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	bool expectedIsValid = true;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	
	string selectedSyn = parsedQuery.getSelectedSyn();
	string patternSyn = parsedQuery.getPatternSyn();
	vector<Relationship> relVect = parsedQuery.getRelVect();
	unordered_map<string, TypeTable::SynType> synTable = parsedQuery.getSynTable();

	unordered_map<string, TypeTable::SynType>::iterator iter;
	iter= synTable.begin();

	string expectedSelectedSyn = "s";

	vector<Relationship> expectedRelVect;
	Relationship tempRel("Follows*","n","s");
	expectedRelVect.push_back(tempRel);

	Relationship tempRel2("with","n","10");
	expectedRelVect.push_back(tempRel2);

	unordered_map<string, TypeTable::SynType> expectedSynTable;
	expectedSynTable.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
	expectedSynTable.insert(make_pair("n", TypeTable::PROGLINE));
	expectedSynTable.insert(make_pair("s", TypeTable::STMT));

	unordered_map<string, TypeTable::SynType>::iterator expectedIter;
	expectedIter= expectedSynTable.begin();

	CPPUNIT_ASSERT_EQUAL(expectedSelectedSyn,selectedSyn);
	for(int i=0;i<(int)expectedRelVect.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getRelType(),relVect[i].getRelType());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1(),relVect[i].getToken1());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2(),relVect[i].getToken2());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getWithSyn(0),relVect[i].getWithSyn(0));
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getWithSyn(1),relVect[i].getWithSyn(1));
	}
	
	for(int i=0;i<expectedSynTable.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedIter->first,iter->first);
		CPPUNIT_ASSERT_EQUAL(expectedIter->second,iter->second);
		iter++;
		expectedIter++;
	}

	return;
}

void QueryParserTest::testQueryValidationModifies1(){
	string query = "assign a; Select a such that Modifies(a, 2)";
	QueryParser qp;
	bool isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	bool expectedIsValid = false;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	return;
}

void QueryParserTest::testQueryValidationModifies2(){
	string query = "assign a; Select b such that Modifies(b, 2)";
	QueryParser qp;
	bool isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	bool expectedIsValid = false;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	return;
}

void QueryParserTest::testQueryValidationModifies3(){
	string query = "assign a; Select a such that Modifies(a, \"b\"):";
	QueryParser qp;
	bool isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	bool expectedIsValid = false;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	return;
}

void QueryParserTest::testQueryValidationPattern1(){
	string query = "assign a; Select a such that Modifies(a, \"b\") pattern a (a, \"_a  *b_\" )";
	QueryParser qp;
	bool isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	bool expectedIsValid = false;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	return;
}

void QueryParserTest::testQueryValidationPattern2(){
	string query = "assign a; Select a such that Modifies(a, \"b\") pattern a (a, _\"a*b\" )";
	QueryParser qp;
	bool isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	bool expectedIsValid = false;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	return;
}

void QueryParserTest::testQueryValidationPattern3(){
	string query = "assign a; Select a such that Modifies(a, \"b\") pattern b (a, \"a*b\" )";
	QueryParser qp;
	bool isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	bool expectedIsValid = false;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	return;
}

void QueryParserTest::testQueryValidationWith1(){
	string query = "variable v; procedure z; Select p with p.procName= v.VarName  ";
	QueryParser qp;
	bool isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	bool expectedIsValid = false;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	return;
}
