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

void QueryParserTest::testQuerySelectOnly(){
	//INIT BEGIN
	string query = "assign a; Select a ";
	QueryParser qp;
	bool isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	bool expectedIsValid = true;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	//INIT END

	//SELECTEDSYN BEGIN
	//actual selected syn
	vector<string> selectedSyn = parsedQuery.getSelectedSyn();
	//expected selected syn
	vector<string> expectedSelectedSyn;
	expectedSelectedSyn.push_back("a");
	//assert selected syn
	for(int i=0;i<(int)expectedSelectedSyn.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedSelectedSyn[i],selectedSyn[i]);
	}
	//SELECTEDSYN END

	//SYNTABLE BEGIN
	//actual syn table
	unordered_map<string, TypeTable::SynType> synTable = parsedQuery.getSynTable();
	unordered_map<string, TypeTable::SynType>::iterator iter;
	iter = synTable.begin();
	//expected syn table
	unordered_map<string, TypeTable::SynType> expectedSynTable;
	expectedSynTable.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
	expectedSynTable.insert(make_pair("a", TypeTable::ASSIGN));
	unordered_map<string, TypeTable::SynType>::iterator expectedIter;
	expectedIter= expectedSynTable.begin();
	//assert syn table
	for(int i=0;i<expectedSynTable.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedIter->first,iter->first);
		CPPUNIT_ASSERT_EQUAL(expectedIter->second,iter->second);
		iter++;
		expectedIter++;
	}
	//SYNTABLE END


	return;
}

void QueryParserTest::testQueryAssignSelectModifies(){
	//INIT BEGIN
	string query = "assign a; Select a such that Modifies(a, \"oSCar\")";
	QueryParser qp;
	bool isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	bool expectedIsValid = true;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	//INIT END
	
	//SELECTEDSYN BEGIN
	//actual selected syn
	vector<string> selectedSyn = parsedQuery.getSelectedSyn();
	//expected selected syn
	vector<string> expectedSelectedSyn;
	expectedSelectedSyn.push_back("a");
	//assert selected syn
	for(int i=0;i<(int)expectedSelectedSyn.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedSelectedSyn[i],selectedSyn[i]);
	}
	//SELECTEDSYN END

	//SYNTABLE BEGIN
	//actual syn table
	unordered_map<string, TypeTable::SynType> synTable = parsedQuery.getSynTable();
	unordered_map<string, TypeTable::SynType>::iterator iter;
	iter = synTable.begin();
	//expected syn table
	unordered_map<string, TypeTable::SynType> expectedSynTable;
	expectedSynTable.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
	expectedSynTable.insert(make_pair("a", TypeTable::ASSIGN));
	unordered_map<string, TypeTable::SynType>::iterator expectedIter;
	expectedIter= expectedSynTable.begin();
	//assert syn table
	for(int i=0;i<expectedSynTable.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedIter->first,iter->first);
		CPPUNIT_ASSERT_EQUAL(expectedIter->second,iter->second);
		iter++;
		expectedIter++;
	}
	//SYNTABLE END

	//RELATIONSHIP BEGIN
	//actual relationship
	vector<Relationship> relVect = parsedQuery.getRelVect();
	//expected relationship
	vector<Relationship> expectedRelVect;
	expectedRelVect.push_back(Relationship("Modifies","a",Relationship::SYNONYM,"\"oSCar\"",Relationship::IDENTIFIER));
	//assert relationship
	for(int i=0;i<(int)expectedRelVect.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getRelType(),relVect[i].getRelType());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getPatternSyn(),relVect[i].getPatternSyn());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1(),relVect[i].getToken1());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1Type(),relVect[i].getToken1Type());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2(),relVect[i].getToken2());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2Type(),relVect[i].getToken2Type());
	}
	//RELATIONSHIP END
	
	return;
}

void QueryParserTest::testQueryAssignVariableSelectModifies(){
	//INIT BEGIN
	string query = " assign a; variable v; Select a such that Modifies (a,v) ";
	QueryParser qp;
	bool isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	bool expectedIsValid = true;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	//INIT END
	
	//SELECTEDSYN BEGIN
	//actual selected syn
	vector<string> selectedSyn = parsedQuery.getSelectedSyn();
	//expected selected syn
	vector<string> expectedSelectedSyn;
	expectedSelectedSyn.push_back("a");
	//assert selected syn
	for(int i=0;i<(int)expectedSelectedSyn.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedSelectedSyn[i],selectedSyn[i]);
	}
	//SELECTEDSYN END

	//SYNTABLE BEGIN
	//actual syn table
	unordered_map<string, TypeTable::SynType> synTable = parsedQuery.getSynTable();
	unordered_map<string, TypeTable::SynType>::iterator iter;
	iter = synTable.begin();
	//expected syn table
	unordered_map<string, TypeTable::SynType> expectedSynTable;
	expectedSynTable.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
	expectedSynTable.insert(make_pair("a", TypeTable::ASSIGN));
	expectedSynTable.insert(make_pair("v", TypeTable::VARIABLE));
	unordered_map<string, TypeTable::SynType>::iterator expectedIter;
	expectedIter= expectedSynTable.begin();
	//assert syn table
	for(int i=0;i<expectedSynTable.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedIter->first,iter->first);
		CPPUNIT_ASSERT_EQUAL(expectedIter->second,iter->second);
		iter++;
		expectedIter++;
	}
	//SYNTABLE END

	//RELATIONSHIP BEGIN
	//actual relationship
	vector<Relationship> relVect = parsedQuery.getRelVect();
	//expected relationship
	vector<Relationship> expectedRelVect;
	expectedRelVect.push_back(Relationship("Modifies","a",Relationship::SYNONYM,"v",Relationship::SYNONYM));
	//assert relationship
	for(int i=0;i<(int)expectedRelVect.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getRelType(),relVect[i].getRelType());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getPatternSyn(),relVect[i].getPatternSyn());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1(),relVect[i].getToken1());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1Type(),relVect[i].getToken1Type());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2(),relVect[i].getToken2());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2Type(),relVect[i].getToken2Type());
	}
	//RELATIONSHIP END

	return;
}

void QueryParserTest::testQueryStmtSelectUses(){
	//INIT BEGIN
	string query = "  stmt s  ; Select s such that Uses (s,\"delta\")  ";
	QueryParser qp;
	bool isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	bool expectedIsValid = true;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	//INIT END
	
	//SELECTEDSYN BEGIN
	//actual selected syn
	vector<string> selectedSyn = parsedQuery.getSelectedSyn();
	//expected selected syn
	vector<string> expectedSelectedSyn;
	expectedSelectedSyn.push_back("s");
	//assert selected syn
	for(int i=0;i<(int)expectedSelectedSyn.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedSelectedSyn[i],selectedSyn[i]);
	}
	//SELECTEDSYN END

	//SYNTABLE BEGIN
	//actual syn table
	unordered_map<string, TypeTable::SynType> synTable = parsedQuery.getSynTable();
	unordered_map<string, TypeTable::SynType>::iterator iter;
	iter = synTable.begin();
	//expected syn table
	unordered_map<string, TypeTable::SynType> expectedSynTable;
	expectedSynTable.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
	expectedSynTable.insert(make_pair("s", TypeTable::STMT));
	unordered_map<string, TypeTable::SynType>::iterator expectedIter;
	expectedIter= expectedSynTable.begin();
	//assert syn table
	for(int i=0;i<expectedSynTable.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedIter->first,iter->first);
		CPPUNIT_ASSERT_EQUAL(expectedIter->second,iter->second);
		iter++;
		expectedIter++;
	}
	//SYNTABLE END

	//RELATIONSHIP BEGIN
	//actual relationship
	vector<Relationship> relVect = parsedQuery.getRelVect();
	//expected relationship
	vector<Relationship> expectedRelVect;
	expectedRelVect.push_back(Relationship("Uses","s",Relationship::SYNONYM,"\"delta\"",Relationship::IDENTIFIER));
	//assert relationship
	for(int i=0;i<(int)expectedRelVect.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getRelType(),relVect[i].getRelType());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getPatternSyn(),relVect[i].getPatternSyn());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1(),relVect[i].getToken1());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1Type(),relVect[i].getToken1Type());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2(),relVect[i].getToken2());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2Type(),relVect[i].getToken2Type());
	}
	//RELATIONSHIP END

	return;
}

void QueryParserTest::testQueryStmtSelectParentStar(){
	//INIT BEGIN
	string query = "stmt   s ;   Select   s  such  that Parent*(5,s)  ";
	QueryParser qp;
	bool isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	bool expectedIsValid = true;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	//INIT END
	
	//SELECTEDSYN BEGIN
	//actual selected syn
	vector<string> selectedSyn = parsedQuery.getSelectedSyn();
	//expected selected syn
	vector<string> expectedSelectedSyn;
	expectedSelectedSyn.push_back("s");
	//assert selected syn
	for(int i=0;i<(int)expectedSelectedSyn.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedSelectedSyn[i],selectedSyn[i]);
	}
	//SELECTEDSYN END

	//SYNTABLE BEGIN
	//actual syn table
	unordered_map<string, TypeTable::SynType> synTable = parsedQuery.getSynTable();
	unordered_map<string, TypeTable::SynType>::iterator iter;
	iter = synTable.begin();
	//expected syn table
	unordered_map<string, TypeTable::SynType> expectedSynTable;
	expectedSynTable.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
	expectedSynTable.insert(make_pair("s", TypeTable::STMT));
	unordered_map<string, TypeTable::SynType>::iterator expectedIter;
	expectedIter= expectedSynTable.begin();
	//assert syn table
	for(int i=0;i<expectedSynTable.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedIter->first,iter->first);
		CPPUNIT_ASSERT_EQUAL(expectedIter->second,iter->second);
		iter++;
		expectedIter++;
	}
	//SYNTABLE END

	//RELATIONSHIP BEGIN
	//actual relationship
	vector<Relationship> relVect = parsedQuery.getRelVect();
	//expected relationship
	vector<Relationship> expectedRelVect;
	expectedRelVect.push_back(Relationship("Parent*","5",Relationship::INTEGER,"s",Relationship::SYNONYM));
	//assert relationship
	for(int i=0;i<(int)expectedRelVect.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getRelType(),relVect[i].getRelType());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getPatternSyn(),relVect[i].getPatternSyn());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1(),relVect[i].getToken1());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1Type(),relVect[i].getToken1Type());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2(),relVect[i].getToken2());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2Type(),relVect[i].getToken2Type());
	}
	//RELATIONSHIP END
	return;
}

void QueryParserTest::testQueryAssignSelectModifiesPattern(){
	//INIT BEGIN
	string query = "assign a, a1; Select a such that Modifies (a, \"x\") pattern a1(_,_) ";
	QueryParser qp;
	bool isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	bool expectedIsValid = true;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	//INIT END
	
	//SELECTEDSYN BEGIN
	//actual selected syn
	vector<string> selectedSyn = parsedQuery.getSelectedSyn();
	//expected selected syn
	vector<string> expectedSelectedSyn;
	expectedSelectedSyn.push_back("a");
	//assert selected syn
	for(int i=0;i<(int)expectedSelectedSyn.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedSelectedSyn[i],selectedSyn[i]);
	}
	//SELECTEDSYN END

	//SYNTABLE BEGIN
	//actual syn table
	unordered_map<string, TypeTable::SynType> synTable = parsedQuery.getSynTable();
	unordered_map<string, TypeTable::SynType>::iterator iter;
	iter = synTable.begin();
	//expected syn table
	unordered_map<string, TypeTable::SynType> expectedSynTable;
	expectedSynTable.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
	expectedSynTable.insert(make_pair("a", TypeTable::ASSIGN));
	expectedSynTable.insert(make_pair("a1", TypeTable::ASSIGN));
	unordered_map<string, TypeTable::SynType>::iterator expectedIter;
	expectedIter= expectedSynTable.begin();
	//assert syn table
	for(int i=0;i<expectedSynTable.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedIter->first,iter->first);
		CPPUNIT_ASSERT_EQUAL(expectedIter->second,iter->second);
		iter++;
		expectedIter++;
	}
	//SYNTABLE END

	//RELATIONSHIP BEGIN
	//actual relationship
	vector<Relationship> relVect = parsedQuery.getRelVect();
	//expected relationship
	vector<Relationship> expectedRelVect;
	expectedRelVect.push_back(Relationship("Modifies","a",Relationship::SYNONYM,"\"x\"",Relationship::IDENTIFIER));
	expectedRelVect.push_back(Relationship("pattern","a1","_",Relationship::UNDERSCORE,"_",Relationship::UNDERSCORE));
	//assert relationship
	for(int i=0;i<(int)expectedRelVect.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getRelType(),relVect[i].getRelType());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getPatternSyn(),relVect[i].getPatternSyn());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1(),relVect[i].getToken1());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1Type(),relVect[i].getToken1Type());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2(),relVect[i].getToken2());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2Type(),relVect[i].getToken2Type());
	}
	//RELATIONSHIP END
	return;
}

void QueryParserTest::testQueryComplex1(){
	//INIT BEGIN
	string query = " assign a  ;  stmt s; variable v; assign a1; variable v2; Select a such that Uses (s,v) pattern a1  (v2,  _\"asd\"_  )  ";
	QueryParser qp;
	bool isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	bool expectedIsValid = true;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	//INIT END
	
	//SELECTEDSYN BEGIN
	//actual selected syn
	vector<string> selectedSyn = parsedQuery.getSelectedSyn();
	//expected selected syn
	vector<string> expectedSelectedSyn;
	expectedSelectedSyn.push_back("a");
	//assert selected syn
	for(int i=0;i<(int)expectedSelectedSyn.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedSelectedSyn[i],selectedSyn[i]);
	}
	//SELECTEDSYN END

	//SYNTABLE BEGIN
	//actual syn table
	unordered_map<string, TypeTable::SynType> synTable = parsedQuery.getSynTable();
	unordered_map<string, TypeTable::SynType>::iterator iter;
	iter = synTable.begin();
	//expected syn table
	unordered_map<string, TypeTable::SynType> expectedSynTable;
	expectedSynTable.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
	expectedSynTable.insert(make_pair("a", TypeTable::ASSIGN));
	expectedSynTable.insert(make_pair("s", TypeTable::STMT));
	expectedSynTable.insert(make_pair("v", TypeTable::VARIABLE));
	expectedSynTable.insert(make_pair("a1", TypeTable::ASSIGN));
	expectedSynTable.insert(make_pair("v2", TypeTable::VARIABLE));
	unordered_map<string, TypeTable::SynType>::iterator expectedIter;
	expectedIter= expectedSynTable.begin();
	//assert syn table
	for(int i=0;i<expectedSynTable.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedIter->first,iter->first);
		CPPUNIT_ASSERT_EQUAL(expectedIter->second,iter->second);
		iter++;
		expectedIter++;
	}
	//SYNTABLE END

	//RELATIONSHIP BEGIN
	//actual relationship
	vector<Relationship> relVect = parsedQuery.getRelVect();
	//expected relationship
	vector<Relationship> expectedRelVect;
	expectedRelVect.push_back(Relationship("Uses","s",Relationship::SYNONYM,"v",Relationship::SYNONYM));
	expectedRelVect.push_back(Relationship("pattern","a1","v2",Relationship::SYNONYM,"_\"asd\"_",Relationship::UNDERSCOREEXPR));
	//assert relationship
	for(int i=0;i<(int)expectedRelVect.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getRelType(),relVect[i].getRelType());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getPatternSyn(),relVect[i].getPatternSyn());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1(),relVect[i].getToken1());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1Type(),relVect[i].getToken1Type());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2(),relVect[i].getToken2());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2Type(),relVect[i].getToken2Type());
	}
	//RELATIONSHIP END
	return;
}

void QueryParserTest::testQueryFollows1(){
	//INIT BEGIN
	string query = " assign a; while w; Select a such that Follows(w, a)";
	QueryParser qp;
	bool isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	bool expectedIsValid = true;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	//INIT END
	
	//SELECTEDSYN BEGIN
	//actual selected syn
	vector<string> selectedSyn = parsedQuery.getSelectedSyn();
	//expected selected syn
	vector<string> expectedSelectedSyn;
	expectedSelectedSyn.push_back("a");
	//assert selected syn
	for(int i=0;i<(int)expectedSelectedSyn.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedSelectedSyn[i],selectedSyn[i]);
	}
	//SELECTEDSYN END

	//SYNTABLE BEGIN
	//actual syn table
	unordered_map<string, TypeTable::SynType> synTable = parsedQuery.getSynTable();
	unordered_map<string, TypeTable::SynType>::iterator iter;
	iter = synTable.begin();
	//expected syn table
	unordered_map<string, TypeTable::SynType> expectedSynTable;
	expectedSynTable.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
	expectedSynTable.insert(make_pair("a", TypeTable::ASSIGN));
	expectedSynTable.insert(make_pair("w", TypeTable::WHILE));
	unordered_map<string, TypeTable::SynType>::iterator expectedIter;
	expectedIter= expectedSynTable.begin();
	//assert syn table
	for(int i=0;i<expectedSynTable.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedIter->first,iter->first);
		CPPUNIT_ASSERT_EQUAL(expectedIter->second,iter->second);
		iter++;
		expectedIter++;
	}
	//SYNTABLE END

	//RELATIONSHIP BEGIN
	//actual relationship
	vector<Relationship> relVect = parsedQuery.getRelVect();
	//expected relationship
	vector<Relationship> expectedRelVect;
	expectedRelVect.push_back(Relationship("Follows","w",Relationship::SYNONYM,"a",Relationship::SYNONYM));
	//assert relationship
	for(int i=0;i<(int)expectedRelVect.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getRelType(),relVect[i].getRelType());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getPatternSyn(),relVect[i].getPatternSyn());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1(),relVect[i].getToken1());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1Type(),relVect[i].getToken1Type());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2(),relVect[i].getToken2());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2Type(),relVect[i].getToken2Type());
	}
	//RELATIONSHIP END
	return;
}

void QueryParserTest::testQueryModifies1(){
	//INIT BEGIN
	string query = "variable v; assign a; Select v such that Modifies(a, v)";
	QueryParser qp;
	bool isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	bool expectedIsValid = true;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	//INIT END
	
	//SELECTEDSYN BEGIN
	//actual selected syn
	vector<string> selectedSyn = parsedQuery.getSelectedSyn();
	//expected selected syn
	vector<string> expectedSelectedSyn;
	expectedSelectedSyn.push_back("v");
	//assert selected syn
	for(int i=0;i<(int)expectedSelectedSyn.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedSelectedSyn[i],selectedSyn[i]);
	}
	//SELECTEDSYN END

	//SYNTABLE BEGIN
	//actual syn table
	unordered_map<string, TypeTable::SynType> synTable = parsedQuery.getSynTable();
	unordered_map<string, TypeTable::SynType>::iterator iter;
	iter = synTable.begin();
	//expected syn table
	unordered_map<string, TypeTable::SynType> expectedSynTable;
	expectedSynTable.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
	expectedSynTable.insert(make_pair("v", TypeTable::VARIABLE));
	expectedSynTable.insert(make_pair("a", TypeTable::ASSIGN));
	unordered_map<string, TypeTable::SynType>::iterator expectedIter;
	expectedIter= expectedSynTable.begin();
	//assert syn table
	for(int i=0;i<expectedSynTable.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedIter->first,iter->first);
		CPPUNIT_ASSERT_EQUAL(expectedIter->second,iter->second);
		iter++;
		expectedIter++;
	}
	//SYNTABLE END

	//RELATIONSHIP BEGIN
	//actual relationship
	vector<Relationship> relVect = parsedQuery.getRelVect();
	//expected relationship
	vector<Relationship> expectedRelVect;
	expectedRelVect.push_back(Relationship("Modifies","a",Relationship::SYNONYM,"v",Relationship::SYNONYM));
	//assert relationship
	for(int i=0;i<(int)expectedRelVect.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getRelType(),relVect[i].getRelType());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getPatternSyn(),relVect[i].getPatternSyn());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1(),relVect[i].getToken1());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1Type(),relVect[i].getToken1Type());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2(),relVect[i].getToken2());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2Type(),relVect[i].getToken2Type());
	}
	//RELATIONSHIP END
	return;
}

void QueryParserTest::testQueryModifies2(){
	//INIT BEGIN
	string query = "assign a, a1; variable v; Select a such that Modifies(a,v)";
	QueryParser qp;
	bool isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	bool expectedIsValid = true;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	//INIT END
	
	//SELECTEDSYN BEGIN
	//actual selected syn
	vector<string> selectedSyn = parsedQuery.getSelectedSyn();
	//expected selected syn
	vector<string> expectedSelectedSyn;
	expectedSelectedSyn.push_back("a");
	//assert selected syn
	for(int i=0;i<(int)expectedSelectedSyn.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedSelectedSyn[i],selectedSyn[i]);
	}
	//SELECTEDSYN END

	//SYNTABLE BEGIN
	//actual syn table
	unordered_map<string, TypeTable::SynType> synTable = parsedQuery.getSynTable();
	unordered_map<string, TypeTable::SynType>::iterator iter;
	iter = synTable.begin();
	//expected syn table
	unordered_map<string, TypeTable::SynType> expectedSynTable;
	expectedSynTable.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
	expectedSynTable.insert(make_pair("a", TypeTable::ASSIGN));
	expectedSynTable.insert(make_pair("a1", TypeTable::ASSIGN));
	expectedSynTable.insert(make_pair("v", TypeTable::VARIABLE));
	unordered_map<string, TypeTable::SynType>::iterator expectedIter;
	expectedIter= expectedSynTable.begin();
	//assert syn table
	for(int i=0;i<expectedSynTable.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedIter->first,iter->first);
		CPPUNIT_ASSERT_EQUAL(expectedIter->second,iter->second);
		iter++;
		expectedIter++;
	}
	//SYNTABLE END

	//RELATIONSHIP BEGIN
	//actual relationship
	vector<Relationship> relVect = parsedQuery.getRelVect();
	//expected relationship
	vector<Relationship> expectedRelVect;
	expectedRelVect.push_back(Relationship("Modifies","a",Relationship::SYNONYM,"v",Relationship::SYNONYM));
	//assert relationship
	for(int i=0;i<(int)expectedRelVect.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getRelType(),relVect[i].getRelType());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getPatternSyn(),relVect[i].getPatternSyn());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1(),relVect[i].getToken1());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1Type(),relVect[i].getToken1Type());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2(),relVect[i].getToken2());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2Type(),relVect[i].getToken2Type());
	}
	//RELATIONSHIP END

	return;
}

void QueryParserTest::testQueryCallStar1(){
	//INIT BEGIN
	string query = "procedure p; Select p such that Calls* (p, \"Tulip\")";
	QueryParser qp;
	bool isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	bool expectedIsValid = true;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	//INIT END
	
	//SELECTEDSYN BEGIN
	//actual selected syn
	vector<string> selectedSyn = parsedQuery.getSelectedSyn();
	//expected selected syn
	vector<string> expectedSelectedSyn;
	expectedSelectedSyn.push_back("p");
	//assert selected syn
	for(int i=0;i<(int)expectedSelectedSyn.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedSelectedSyn[i],selectedSyn[i]);
	}
	//SELECTEDSYN END

	//SYNTABLE BEGIN
	//actual syn table
	unordered_map<string, TypeTable::SynType> synTable = parsedQuery.getSynTable();
	unordered_map<string, TypeTable::SynType>::iterator iter;
	iter = synTable.begin();
	//expected syn table
	unordered_map<string, TypeTable::SynType> expectedSynTable;
	expectedSynTable.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
	expectedSynTable.insert(make_pair("p", TypeTable::PROCEDURE));
	unordered_map<string, TypeTable::SynType>::iterator expectedIter;
	expectedIter= expectedSynTable.begin();
	//assert syn table
	for(int i=0;i<expectedSynTable.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedIter->first,iter->first);
		CPPUNIT_ASSERT_EQUAL(expectedIter->second,iter->second);
		iter++;
		expectedIter++;
	}
	//SYNTABLE END

	//RELATIONSHIP BEGIN
	//actual relationship
	vector<Relationship> relVect = parsedQuery.getRelVect();
	//expected relationship
	vector<Relationship> expectedRelVect;
	expectedRelVect.push_back(Relationship("Calls*","p",Relationship::SYNONYM,"\"Tulip\"",Relationship::IDENTIFIER));
	//assert relationship
	for(int i=0;i<(int)expectedRelVect.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getRelType(),relVect[i].getRelType());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getPatternSyn(),relVect[i].getPatternSyn());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1(),relVect[i].getToken1());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1Type(),relVect[i].getToken1Type());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2(),relVect[i].getToken2());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2Type(),relVect[i].getToken2Type());
	}
	//RELATIONSHIP END

	return;
}

void QueryParserTest::testQueryPattern1(){
	//INIT BEGIN
	string query = "assign a; Select a pattern a(a,_)";
	QueryParser qp;
	bool isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	bool expectedIsValid = true;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	//INIT END
	
	//SELECTEDSYN BEGIN
	//actual selected syn
	vector<string> selectedSyn = parsedQuery.getSelectedSyn();
	//expected selected syn
	vector<string> expectedSelectedSyn;
	expectedSelectedSyn.push_back("a");
	//assert selected syn
	for(int i=0;i<(int)expectedSelectedSyn.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedSelectedSyn[i],selectedSyn[i]);
	}
	//SELECTEDSYN END

	//SYNTABLE BEGIN
	//actual syn table
	unordered_map<string, TypeTable::SynType> synTable = parsedQuery.getSynTable();
	unordered_map<string, TypeTable::SynType>::iterator iter;
	iter = synTable.begin();
	//expected syn table
	unordered_map<string, TypeTable::SynType> expectedSynTable;
	expectedSynTable.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
	expectedSynTable.insert(make_pair("a", TypeTable::ASSIGN));
	unordered_map<string, TypeTable::SynType>::iterator expectedIter;
	expectedIter= expectedSynTable.begin();
	//assert syn table
	for(int i=0;i<expectedSynTable.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedIter->first,iter->first);
		CPPUNIT_ASSERT_EQUAL(expectedIter->second,iter->second);
		iter++;
		expectedIter++;
	}
	//SYNTABLE END

	//RELATIONSHIP BEGIN
	//actual relationship
	vector<Relationship> relVect = parsedQuery.getRelVect();
	//expected relationship
	vector<Relationship> expectedRelVect;
	expectedRelVect.push_back(Relationship("pattern","a","a",Relationship::SYNONYM,"_",Relationship::UNDERSCORE));
	//assert relationship
	for(int i=0;i<(int)expectedRelVect.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getRelType(),relVect[i].getRelType());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getPatternSyn(),relVect[i].getPatternSyn());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1(),relVect[i].getToken1());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1Type(),relVect[i].getToken1Type());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2(),relVect[i].getToken2());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2Type(),relVect[i].getToken2Type());
	}
	//RELATIONSHIP END

	return;
}


void QueryParserTest::testQueryPattern2(){
	//INIT BEGIN
	string query = "assign a; Select a pattern a (\"y\", \" 2 * x \")";
	QueryParser qp;
	bool isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	bool expectedIsValid = true;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	//INIT END
	
	//SELECTEDSYN BEGIN
	//actual selected syn
	vector<string> selectedSyn = parsedQuery.getSelectedSyn();
	//expected selected syn
	vector<string> expectedSelectedSyn;
	expectedSelectedSyn.push_back("a");
	//assert selected syn
	for(int i=0;i<(int)expectedSelectedSyn.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedSelectedSyn[i],selectedSyn[i]);
	}
	//SELECTEDSYN END

	//SYNTABLE BEGIN
	//actual syn table
	unordered_map<string, TypeTable::SynType> synTable = parsedQuery.getSynTable();
	unordered_map<string, TypeTable::SynType>::iterator iter;
	iter = synTable.begin();
	//expected syn table
	unordered_map<string, TypeTable::SynType> expectedSynTable;
	expectedSynTable.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
	expectedSynTable.insert(make_pair("a", TypeTable::ASSIGN));
	unordered_map<string, TypeTable::SynType>::iterator expectedIter;
	expectedIter= expectedSynTable.begin();
	//assert syn table
	for(int i=0;i<expectedSynTable.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedIter->first,iter->first);
		CPPUNIT_ASSERT_EQUAL(expectedIter->second,iter->second);
		iter++;
		expectedIter++;
	}
	//SYNTABLE END

	//RELATIONSHIP BEGIN
	//actual relationship
	vector<Relationship> relVect = parsedQuery.getRelVect();
	//expected relationship
	vector<Relationship> expectedRelVect;
	expectedRelVect.push_back(Relationship("pattern","a","\"y\"",Relationship::IDENTIFIER,"\" 2 * x \"",Relationship::EXPR));
	//assert relationship
	for(int i=0;i<(int)expectedRelVect.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getRelType(),relVect[i].getRelType());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getPatternSyn(),relVect[i].getPatternSyn());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1(),relVect[i].getToken1());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1Type(),relVect[i].getToken1Type());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2(),relVect[i].getToken2());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2Type(),relVect[i].getToken2Type());
	}
	//RELATIONSHIP END

	return;
}

void QueryParserTest::testQueryWith1(){
	//INIT BEGIN
	string query = "variable v; procedure p; Select p with p.procName = v.varName ";
	QueryParser qp;
	bool isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	bool expectedIsValid = true;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	//INIT END
	
	//SELECTEDSYN BEGIN
	//actual selected syn
	vector<string> selectedSyn = parsedQuery.getSelectedSyn();
	//expected selected syn
	vector<string> expectedSelectedSyn;
	expectedSelectedSyn.push_back("p");
	//assert selected syn
	for(int i=0;i<(int)expectedSelectedSyn.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedSelectedSyn[i],selectedSyn[i]);
	}
	//SELECTEDSYN END

	//SYNTABLE BEGIN
	//actual syn table
	unordered_map<string, TypeTable::SynType> synTable = parsedQuery.getSynTable();
	unordered_map<string, TypeTable::SynType>::iterator iter;
	iter = synTable.begin();
	//expected syn table
	unordered_map<string, TypeTable::SynType> expectedSynTable;
	expectedSynTable.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
	expectedSynTable.insert(make_pair("v", TypeTable::VARIABLE));
	expectedSynTable.insert(make_pair("p", TypeTable::PROCEDURE));
	unordered_map<string, TypeTable::SynType>::iterator expectedIter;
	expectedIter= expectedSynTable.begin();
	//assert syn table
	for(int i=0;i<expectedSynTable.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedIter->first,iter->first);
		CPPUNIT_ASSERT_EQUAL(expectedIter->second,iter->second);
		iter++;
		expectedIter++;
	}
	//SYNTABLE END

	//RELATIONSHIP BEGIN
	//actual relationship
	vector<Relationship> relVect = parsedQuery.getRelVect();
	//expected relationship
	vector<Relationship> expectedRelVect;
	expectedRelVect.push_back(Relationship("with","p",Relationship::SYNONYM,"v",Relationship::SYNONYM));
	//assert relationship
	for(int i=0;i<(int)expectedRelVect.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getRelType(),relVect[i].getRelType());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getPatternSyn(),relVect[i].getPatternSyn());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1(),relVect[i].getToken1());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1Type(),relVect[i].getToken1Type());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2(),relVect[i].getToken2());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2Type(),relVect[i].getToken2Type());
	}
	//RELATIONSHIP END
	return;
}

void QueryParserTest::testQueryWith2(){
	//INIT BEGIN
	string query = "stmt s; constant c; Select s with s.stmt#=c.value ";
	QueryParser qp;
	bool isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	bool expectedIsValid = true;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	//INIT END
	
	//SELECTEDSYN BEGIN
	//actual selected syn
	vector<string> selectedSyn = parsedQuery.getSelectedSyn();
	//expected selected syn
	vector<string> expectedSelectedSyn;
	expectedSelectedSyn.push_back("s");
	//assert selected syn
	for(int i=0;i<(int)expectedSelectedSyn.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedSelectedSyn[i],selectedSyn[i]);
	}
	//SELECTEDSYN END

	//SYNTABLE BEGIN
	//actual syn table
	unordered_map<string, TypeTable::SynType> synTable = parsedQuery.getSynTable();
	unordered_map<string, TypeTable::SynType>::iterator iter;
	iter = synTable.begin();
	//expected syn table
	unordered_map<string, TypeTable::SynType> expectedSynTable;
	expectedSynTable.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
	expectedSynTable.insert(make_pair("s", TypeTable::STMT));
	expectedSynTable.insert(make_pair("c", TypeTable::CONSTANT));
	unordered_map<string, TypeTable::SynType>::iterator expectedIter;
	expectedIter= expectedSynTable.begin();
	//assert syn table
	for(int i=0;i<expectedSynTable.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedIter->first,iter->first);
		CPPUNIT_ASSERT_EQUAL(expectedIter->second,iter->second);
		iter++;
		expectedIter++;
	}
	//SYNTABLE END

	//RELATIONSHIP BEGIN
	//actual relationship
	vector<Relationship> relVect = parsedQuery.getRelVect();
	//expected relationship
	vector<Relationship> expectedRelVect;
	expectedRelVect.push_back(Relationship("with","s",Relationship::SYNONYM,"c",Relationship::SYNONYM));
	//assert relationship
	for(int i=0;i<(int)expectedRelVect.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getRelType(),relVect[i].getRelType());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getPatternSyn(),relVect[i].getPatternSyn());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1(),relVect[i].getToken1());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1Type(),relVect[i].getToken1Type());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2(),relVect[i].getToken2());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2Type(),relVect[i].getToken2Type());
	}
	//RELATIONSHIP END

	return;
}

void QueryParserTest::testQueryWith3(){
	//INIT BEGIN
	string query = "prog_line n; stmt s; Select s such that Follows*(n,s) with n=10";
	QueryParser qp;
	bool isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	bool expectedIsValid = true;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	//INIT END
	
	//SELECTEDSYN BEGIN
	//actual selected syn
	vector<string> selectedSyn = parsedQuery.getSelectedSyn();
	//expected selected syn
	vector<string> expectedSelectedSyn;
	expectedSelectedSyn.push_back("s");
	//assert selected syn
	for(int i=0;i<(int)expectedSelectedSyn.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedSelectedSyn[i],selectedSyn[i]);
	}
	//SELECTEDSYN END

	//SYNTABLE BEGIN
	//actual syn table
	unordered_map<string, TypeTable::SynType> synTable = parsedQuery.getSynTable();
	unordered_map<string, TypeTable::SynType>::iterator iter;
	iter = synTable.begin();
	//expected syn table
	unordered_map<string, TypeTable::SynType> expectedSynTable;
	expectedSynTable.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
	expectedSynTable.insert(make_pair("n", TypeTable::PROGLINE));
	expectedSynTable.insert(make_pair("s", TypeTable::STMT));
	unordered_map<string, TypeTable::SynType>::iterator expectedIter;
	expectedIter= expectedSynTable.begin();
	//assert syn table
	for(int i=0;i<expectedSynTable.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedIter->first,iter->first);
		CPPUNIT_ASSERT_EQUAL(expectedIter->second,iter->second);
		iter++;
		expectedIter++;
	}
	//SYNTABLE END

	//RELATIONSHIP BEGIN
	//actual relationship
	vector<Relationship> relVect = parsedQuery.getRelVect();
	//expected relationship
	vector<Relationship> expectedRelVect;
	expectedRelVect.push_back(Relationship("Follows*","n",Relationship::SYNONYM,"s",Relationship::SYNONYM));
	expectedRelVect.push_back(Relationship("with","n",Relationship::SYNONYM,"10",Relationship::INTEGER));
	//assert relationship
	for(int i=0;i<(int)expectedRelVect.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getRelType(),relVect[i].getRelType());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getPatternSyn(),relVect[i].getPatternSyn());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1(),relVect[i].getToken1());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1Type(),relVect[i].getToken1Type());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2(),relVect[i].getToken2());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2Type(),relVect[i].getToken2Type());
	}
	//RELATIONSHIP END

	return;
}

void QueryParserTest::testQueryMultipleSuchThat(){
	//INIT BEGIN
	string query = "prog_line n; stmt s; Select s such that Follows*(n,s) and Follows(n,s) and Uses(n,\"x\")";
	QueryParser qp;
	bool isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	bool expectedIsValid = true;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	//INIT END
	
	//SELECTEDSYN BEGIN
	//actual selected syn
	vector<string> selectedSyn = parsedQuery.getSelectedSyn();
	//expected selected syn
	vector<string> expectedSelectedSyn;
	expectedSelectedSyn.push_back("s");
	//assert selected syn
	for(int i=0;i<(int)expectedSelectedSyn.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedSelectedSyn[i],selectedSyn[i]);
	}
	//SELECTEDSYN END

	//SYNTABLE BEGIN
	//actual syn table
	unordered_map<string, TypeTable::SynType> synTable = parsedQuery.getSynTable();
	unordered_map<string, TypeTable::SynType>::iterator iter;
	iter = synTable.begin();
	//expected syn table
	unordered_map<string, TypeTable::SynType> expectedSynTable;
	expectedSynTable.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
	expectedSynTable.insert(make_pair("n", TypeTable::PROGLINE));
	expectedSynTable.insert(make_pair("s", TypeTable::STMT));
	unordered_map<string, TypeTable::SynType>::iterator expectedIter;
	expectedIter= expectedSynTable.begin();
	//assert syn table
	for(int i=0;i<expectedSynTable.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedIter->first,iter->first);
		CPPUNIT_ASSERT_EQUAL(expectedIter->second,iter->second);
		iter++;
		expectedIter++;
	}
	//SYNTABLE END

	//RELATIONSHIP BEGIN
	//actual relationship
	vector<Relationship> relVect = parsedQuery.getRelVect();
	//expected relationship
	vector<Relationship> expectedRelVect;
	expectedRelVect.push_back(Relationship("Follows*","n",Relationship::SYNONYM,"s",Relationship::SYNONYM));
	expectedRelVect.push_back(Relationship("Follows","n",Relationship::SYNONYM,"s",Relationship::SYNONYM));
	expectedRelVect.push_back(Relationship("Uses","n",Relationship::SYNONYM,"\"x\"",Relationship::IDENTIFIER));
	//assert relationship

	for(int i=0;i<(int)expectedRelVect.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getRelType(),relVect[i].getRelType());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getPatternSyn(),relVect[i].getPatternSyn());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1(),relVect[i].getToken1());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1Type(),relVect[i].getToken1Type());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2(),relVect[i].getToken2());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2Type(),relVect[i].getToken2Type());
	}
	//RELATIONSHIP END

	return;
}

void QueryParserTest::testQueryMultipleWith(){
	//INIT BEGIN
	string query = "prog_line n; stmt s; Select s such that Follows*(n,s) with n=10 and s.stmt#=9 and s.stmt#=11 with n=12";
	QueryParser qp;
	bool isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	bool expectedIsValid = true;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	//INIT END
	
	//SELECTEDSYN BEGIN
	//actual selected syn
	vector<string> selectedSyn = parsedQuery.getSelectedSyn();
	//expected selected syn
	vector<string> expectedSelectedSyn;
	expectedSelectedSyn.push_back("s");
	//assert selected syn
	for(int i=0;i<(int)expectedSelectedSyn.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedSelectedSyn[i],selectedSyn[i]);
	}
	//SELECTEDSYN END

	//SYNTABLE BEGIN
	//actual syn table
	unordered_map<string, TypeTable::SynType> synTable = parsedQuery.getSynTable();
	unordered_map<string, TypeTable::SynType>::iterator iter;
	iter = synTable.begin();
	//expected syn table
	unordered_map<string, TypeTable::SynType> expectedSynTable;
	expectedSynTable.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
	expectedSynTable.insert(make_pair("n", TypeTable::PROGLINE));
	expectedSynTable.insert(make_pair("s", TypeTable::STMT));
	unordered_map<string, TypeTable::SynType>::iterator expectedIter;
	expectedIter= expectedSynTable.begin();
	//assert syn table
	for(int i=0;i<expectedSynTable.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedIter->first,iter->first);
		CPPUNIT_ASSERT_EQUAL(expectedIter->second,iter->second);
		iter++;
		expectedIter++;
	}
	//SYNTABLE END

	//RELATIONSHIP BEGIN
	//actual relationship
	vector<Relationship> relVect = parsedQuery.getRelVect();
	//expected relationship
	vector<Relationship> expectedRelVect;
	expectedRelVect.push_back(Relationship("Follows*","n",Relationship::SYNONYM,"s",Relationship::SYNONYM));
	expectedRelVect.push_back(Relationship("with","n",Relationship::SYNONYM,"10",Relationship::INTEGER));
	expectedRelVect.push_back(Relationship("with","s",Relationship::SYNONYM,"9",Relationship::INTEGER));
	expectedRelVect.push_back(Relationship("with","s",Relationship::SYNONYM,"11",Relationship::INTEGER));
	expectedRelVect.push_back(Relationship("with","n",Relationship::SYNONYM,"12",Relationship::INTEGER));
	//assert relationship

	for(int i=0;i<(int)expectedRelVect.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getRelType(),relVect[i].getRelType());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getPatternSyn(),relVect[i].getPatternSyn());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1(),relVect[i].getToken1());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1Type(),relVect[i].getToken1Type());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2(),relVect[i].getToken2());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2Type(),relVect[i].getToken2Type());
	}
	//RELATIONSHIP END

	return;
}

void QueryParserTest::testQueryMultiplePattern(){
	//INIT BEGIN
	string query = "prog_line n; stmt s; Select s such that Follows*(n,s) pattern s(_,_) and s(_,_\"x+y\"_) and s(_,_\"x+z\"_)";
	QueryParser qp;
	bool isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	bool expectedIsValid = true;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	//INIT END
	
	//SELECTEDSYN BEGIN
	//actual selected syn
	vector<string> selectedSyn = parsedQuery.getSelectedSyn();
	//expected selected syn
	vector<string> expectedSelectedSyn;
	expectedSelectedSyn.push_back("s");
	//assert selected syn
	for(int i=0;i<(int)expectedSelectedSyn.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedSelectedSyn[i],selectedSyn[i]);
	}
	//SELECTEDSYN END

	//SYNTABLE BEGIN
	//actual syn table
	unordered_map<string, TypeTable::SynType> synTable = parsedQuery.getSynTable();
	unordered_map<string, TypeTable::SynType>::iterator iter;
	iter = synTable.begin();
	//expected syn table
	unordered_map<string, TypeTable::SynType> expectedSynTable;
	expectedSynTable.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
	expectedSynTable.insert(make_pair("n", TypeTable::PROGLINE));
	expectedSynTable.insert(make_pair("s", TypeTable::STMT));
	unordered_map<string, TypeTable::SynType>::iterator expectedIter;
	expectedIter= expectedSynTable.begin();
	//assert syn table
	for(int i=0;i<expectedSynTable.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedIter->first,iter->first);
		CPPUNIT_ASSERT_EQUAL(expectedIter->second,iter->second);
		iter++;
		expectedIter++;
	}
	//SYNTABLE END

	//RELATIONSHIP BEGIN
	//actual relationship
	vector<Relationship> relVect = parsedQuery.getRelVect();
	//expected relationship
	vector<Relationship> expectedRelVect;
	expectedRelVect.push_back(Relationship("Follows*","n",Relationship::SYNONYM,"s",Relationship::SYNONYM));
	expectedRelVect.push_back(Relationship("pattern","s", "_",Relationship::UNDERSCORE,"_",Relationship::UNDERSCORE));
	expectedRelVect.push_back(Relationship("pattern","s", "_",Relationship::UNDERSCORE,"_\"x+y\"_",Relationship::UNDERSCOREEXPR));
	expectedRelVect.push_back(Relationship("pattern","s", "_",Relationship::UNDERSCORE,"_\"x+z\"_",Relationship::UNDERSCOREEXPR));
	//assert relationship

	for(int i=0;i<(int)expectedRelVect.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getRelType(),relVect[i].getRelType());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getPatternSyn(),relVect[i].getPatternSyn());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1(),relVect[i].getToken1());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1Type(),relVect[i].getToken1Type());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2(),relVect[i].getToken2());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2Type(),relVect[i].getToken2Type());
	}
	//RELATIONSHIP END

	return;
}

void QueryParserTest::testQueryMultiplePatternAndWith(){
	//INIT BEGIN
	string query = "prog_line n; stmt s; Select s such that Follows*(n,s) pattern s(_,_) and s(_,_\"x+y\"_) and s(_,_\"x+z\"_) with n=10 and s.stmt#=9 and s.stmt#=11 with n=12 pattern s(s,\"x\") and s(_,_\"z+y\"_)";
	QueryParser qp;
	bool isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	bool expectedIsValid = true;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	//INIT END
	
	//SELECTEDSYN BEGIN
	//actual selected syn
	vector<string> selectedSyn = parsedQuery.getSelectedSyn();
	//expected selected syn
	vector<string> expectedSelectedSyn;
	expectedSelectedSyn.push_back("s");
	//assert selected syn
	for(int i=0;i<(int)expectedSelectedSyn.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedSelectedSyn[i],selectedSyn[i]);
	}
	//SELECTEDSYN END

	//SYNTABLE BEGIN
	//actual syn table
	unordered_map<string, TypeTable::SynType> synTable = parsedQuery.getSynTable();
	unordered_map<string, TypeTable::SynType>::iterator iter;
	iter = synTable.begin();
	//expected syn table
	unordered_map<string, TypeTable::SynType> expectedSynTable;
	expectedSynTable.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
	expectedSynTable.insert(make_pair("n", TypeTable::PROGLINE));
	expectedSynTable.insert(make_pair("s", TypeTable::STMT));
	unordered_map<string, TypeTable::SynType>::iterator expectedIter;
	expectedIter= expectedSynTable.begin();
	//assert syn table
	for(int i=0;i<expectedSynTable.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedIter->first,iter->first);
		CPPUNIT_ASSERT_EQUAL(expectedIter->second,iter->second);
		iter++;
		expectedIter++;
	}
	//SYNTABLE END

	//RELATIONSHIP BEGIN
	//actual relationship
	vector<Relationship> relVect = parsedQuery.getRelVect();
	//expected relationship
	vector<Relationship> expectedRelVect;
	expectedRelVect.push_back(Relationship("Follows*","n",Relationship::SYNONYM,"s",Relationship::SYNONYM));
	expectedRelVect.push_back(Relationship("pattern","s", "_",Relationship::UNDERSCORE,"_",Relationship::UNDERSCORE));
	expectedRelVect.push_back(Relationship("pattern","s", "_",Relationship::UNDERSCORE,"_\"x+y\"_",Relationship::UNDERSCOREEXPR));
	expectedRelVect.push_back(Relationship("pattern","s", "_",Relationship::UNDERSCORE,"_\"x+z\"_",Relationship::UNDERSCOREEXPR));
	expectedRelVect.push_back(Relationship("with","n",Relationship::SYNONYM,"10",Relationship::INTEGER));
	expectedRelVect.push_back(Relationship("with","s",Relationship::SYNONYM,"9",Relationship::INTEGER));
	expectedRelVect.push_back(Relationship("with","s",Relationship::SYNONYM,"11",Relationship::INTEGER));
	expectedRelVect.push_back(Relationship("with","n",Relationship::SYNONYM,"12",Relationship::INTEGER));
	expectedRelVect.push_back(Relationship("pattern","s", "s",Relationship::SYNONYM,"\"x\"",Relationship::IDENTIFIER));
	expectedRelVect.push_back(Relationship("pattern","s", "_",Relationship::UNDERSCORE,"_\"z+y\"_",Relationship::UNDERSCOREEXPR));
	//assert relationship

	for(int i=0;i<(int)expectedRelVect.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getRelType(),relVect[i].getRelType());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getPatternSyn(),relVect[i].getPatternSyn());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1(),relVect[i].getToken1());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1Type(),relVect[i].getToken1Type());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2(),relVect[i].getToken2());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2Type(),relVect[i].getToken2Type());
	}
	//RELATIONSHIP END

	return;
}

void QueryParserTest::testQueryMultipleSuchThatAndPatternAndWith(){
	//INIT BEGIN
	string query = "prog_line n; stmt s; Select s such that Follows*(n,s) and Follows(n,s) and Uses(n,\"x\") pattern s(_,_) and s(_,_\"x+y\"_) and s(_,_\"x+z\"_) with n=10 and s.stmt#=9 and s.stmt#=11 with n=12 pattern s(s,\"x\") and s(_,_\"z+y\"_) such that Follows*(n,s) and Follows(n,s) and Uses(n,\"x\")";
	QueryParser qp;
	bool isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	bool expectedIsValid = true;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	//INIT END
	
	//SELECTEDSYN BEGIN
	//actual selected syn
	vector<string> selectedSyn = parsedQuery.getSelectedSyn();
	//expected selected syn
	vector<string> expectedSelectedSyn;
	expectedSelectedSyn.push_back("s");
	//assert selected syn
	for(int i=0;i<(int)expectedSelectedSyn.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedSelectedSyn[i],selectedSyn[i]);
	}
	//SELECTEDSYN END

	//SYNTABLE BEGIN
	//actual syn table
	unordered_map<string, TypeTable::SynType> synTable = parsedQuery.getSynTable();
	unordered_map<string, TypeTable::SynType>::iterator iter;
	iter = synTable.begin();
	//expected syn table
	unordered_map<string, TypeTable::SynType> expectedSynTable;
	expectedSynTable.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
	expectedSynTable.insert(make_pair("n", TypeTable::PROGLINE));
	expectedSynTable.insert(make_pair("s", TypeTable::STMT));
	unordered_map<string, TypeTable::SynType>::iterator expectedIter;
	expectedIter= expectedSynTable.begin();
	//assert syn table
	for(int i=0;i<expectedSynTable.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedIter->first,iter->first);
		CPPUNIT_ASSERT_EQUAL(expectedIter->second,iter->second);
		iter++;
		expectedIter++;
	}
	//SYNTABLE END

	//RELATIONSHIP BEGIN
	//actual relationship
	vector<Relationship> relVect = parsedQuery.getRelVect();
	//expected relationship
	vector<Relationship> expectedRelVect;
	expectedRelVect.push_back(Relationship("Follows*","n",Relationship::SYNONYM,"s",Relationship::SYNONYM));
	expectedRelVect.push_back(Relationship("Follows","n",Relationship::SYNONYM,"s",Relationship::SYNONYM));
	expectedRelVect.push_back(Relationship("Uses","n",Relationship::SYNONYM,"\"x\"",Relationship::IDENTIFIER));
	expectedRelVect.push_back(Relationship("pattern","s", "_",Relationship::UNDERSCORE,"_",Relationship::UNDERSCORE));
	expectedRelVect.push_back(Relationship("pattern","s", "_",Relationship::UNDERSCORE,"_\"x+y\"_",Relationship::UNDERSCOREEXPR));
	expectedRelVect.push_back(Relationship("pattern","s", "_",Relationship::UNDERSCORE,"_\"x+z\"_",Relationship::UNDERSCOREEXPR));
	expectedRelVect.push_back(Relationship("with","n",Relationship::SYNONYM,"10",Relationship::INTEGER));
	expectedRelVect.push_back(Relationship("with","s",Relationship::SYNONYM,"9",Relationship::INTEGER));
	expectedRelVect.push_back(Relationship("with","s",Relationship::SYNONYM,"11",Relationship::INTEGER));
	expectedRelVect.push_back(Relationship("with","n",Relationship::SYNONYM,"12",Relationship::INTEGER));
	expectedRelVect.push_back(Relationship("pattern","s", "s",Relationship::SYNONYM,"\"x\"",Relationship::IDENTIFIER));
	expectedRelVect.push_back(Relationship("pattern","s", "_",Relationship::UNDERSCORE,"_\"z+y\"_",Relationship::UNDERSCOREEXPR));
	expectedRelVect.push_back(Relationship("Follows*","n",Relationship::SYNONYM,"s",Relationship::SYNONYM));
	expectedRelVect.push_back(Relationship("Follows","n",Relationship::SYNONYM,"s",Relationship::SYNONYM));
	expectedRelVect.push_back(Relationship("Uses","n",Relationship::SYNONYM,"\"x\"",Relationship::IDENTIFIER));
	//assert relationship

	for(int i=0;i<(int)expectedRelVect.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getRelType(),relVect[i].getRelType());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getPatternSyn(),relVect[i].getPatternSyn());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1(),relVect[i].getToken1());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1Type(),relVect[i].getToken1Type());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2(),relVect[i].getToken2());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2Type(),relVect[i].getToken2Type());
	}
	//RELATIONSHIP END

	return;
}

void QueryParserTest::testQueryTupleModifies(){
	//INIT BEGIN
	string query = "prog_line n; stmt s1,s2,s3,s4; Select <s1,s2,s3,s4>  such that Modifies(s1,\"v\")";
	QueryParser qp;
	bool isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	bool expectedIsValid = true;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	//INIT END
	
	//SELECTEDSYN BEGIN
	//actual selected syn
	vector<string> selectedSyn = parsedQuery.getSelectedSyn();
	//expected selected syn
	vector<string> expectedSelectedSyn;
	expectedSelectedSyn.push_back("s1");
	expectedSelectedSyn.push_back("s2");
	expectedSelectedSyn.push_back("s3");
	expectedSelectedSyn.push_back("s4");
	//assert selected syn
	for(int i=0;i<(int)expectedSelectedSyn.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedSelectedSyn[i],selectedSyn[i]);
	}
	//SELECTEDSYN END

	//SYNTABLE BEGIN
	//actual syn table
	unordered_map<string, TypeTable::SynType> synTable = parsedQuery.getSynTable();
	unordered_map<string, TypeTable::SynType>::iterator iter;
	iter = synTable.begin();
	//expected syn table
	unordered_map<string, TypeTable::SynType> expectedSynTable;
	expectedSynTable.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
	expectedSynTable.insert(make_pair("n", TypeTable::PROGLINE));
	expectedSynTable.insert(make_pair("s1", TypeTable::STMT));
	expectedSynTable.insert(make_pair("s2", TypeTable::STMT));
	expectedSynTable.insert(make_pair("s3", TypeTable::STMT));
	expectedSynTable.insert(make_pair("s4", TypeTable::STMT));
	unordered_map<string, TypeTable::SynType>::iterator expectedIter;
	expectedIter= expectedSynTable.begin();
	//assert syn table
	for(int i=0;i<expectedSynTable.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedIter->first,iter->first);
		CPPUNIT_ASSERT_EQUAL(expectedIter->second,iter->second);
		iter++;
		expectedIter++;
	}
	//SYNTABLE END

	//RELATIONSHIP BEGIN
	//actual relationship
	vector<Relationship> relVect = parsedQuery.getRelVect();
	//expected relationship
	vector<Relationship> expectedRelVect;
	expectedRelVect.push_back(Relationship("Modifies","s1",Relationship::SYNONYM,"\"v\"",Relationship::IDENTIFIER));
	//assert relationship

	for(int i=0;i<(int)expectedRelVect.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getRelType(),relVect[i].getRelType());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getPatternSyn(),relVect[i].getPatternSyn());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1(),relVect[i].getToken1());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1Type(),relVect[i].getToken1Type());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2(),relVect[i].getToken2());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2Type(),relVect[i].getToken2Type());
	}
	//RELATIONSHIP END

	return;
}

void QueryParserTest::testQueryTupleUses(){
	//INIT BEGIN
	string query = "prog_line n; stmt s1,s2,s3,s4; Select <  s1,   s2    ,s3   ,s4   >  such that Uses(s1,\"v\")";
	QueryParser qp;
	bool isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	bool expectedIsValid = true;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	//INIT END
	
	//SELECTEDSYN BEGIN
	//actual selected syn
	vector<string> selectedSyn = parsedQuery.getSelectedSyn();
	//expected selected syn
	vector<string> expectedSelectedSyn;
	expectedSelectedSyn.push_back("s1");
	expectedSelectedSyn.push_back("s2");
	expectedSelectedSyn.push_back("s3");
	expectedSelectedSyn.push_back("s4");
	//assert selected syn
	for(int i=0;i<(int)expectedSelectedSyn.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedSelectedSyn[i],selectedSyn[i]);
	}
	//SELECTEDSYN END

	//SYNTABLE BEGIN
	//actual syn table
	unordered_map<string, TypeTable::SynType> synTable = parsedQuery.getSynTable();
	unordered_map<string, TypeTable::SynType>::iterator iter;
	iter = synTable.begin();
	//expected syn table
	unordered_map<string, TypeTable::SynType> expectedSynTable;
	expectedSynTable.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
	expectedSynTable.insert(make_pair("n", TypeTable::PROGLINE));
	expectedSynTable.insert(make_pair("s1", TypeTable::STMT));
	expectedSynTable.insert(make_pair("s2", TypeTable::STMT));
	expectedSynTable.insert(make_pair("s3", TypeTable::STMT));
	expectedSynTable.insert(make_pair("s4", TypeTable::STMT));
	unordered_map<string, TypeTable::SynType>::iterator expectedIter;
	expectedIter= expectedSynTable.begin();
	//assert syn table
	for(int i=0;i<expectedSynTable.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedIter->first,iter->first);
		CPPUNIT_ASSERT_EQUAL(expectedIter->second,iter->second);
		iter++;
		expectedIter++;
	}
	//SYNTABLE END

	//RELATIONSHIP BEGIN
	//actual relationship
	vector<Relationship> relVect = parsedQuery.getRelVect();
	//expected relationship
	vector<Relationship> expectedRelVect;
	expectedRelVect.push_back(Relationship("Uses","s1",Relationship::SYNONYM,"\"v\"",Relationship::IDENTIFIER));
	//assert relationship

	for(int i=0;i<(int)expectedRelVect.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getRelType(),relVect[i].getRelType());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getPatternSyn(),relVect[i].getPatternSyn());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1(),relVect[i].getToken1());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1Type(),relVect[i].getToken1Type());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2(),relVect[i].getToken2());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2Type(),relVect[i].getToken2Type());
	}
	//RELATIONSHIP END

	return;
}

void QueryParserTest::testQueryValidationTuple(){
	string query = "assign a1; Select <a1,a2, a3> such that Modifies(a1, \"v\")";
	QueryParser qp;
	bool isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	bool expectedIsValid = false;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
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
	string query = "assign a; Select b such that Modifies(b, \"v\")";
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
	string query = "variable v; procedure z; Select p with p.procName= v.varName  ";
	QueryParser qp;
	bool isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	bool expectedIsValid = false;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	return;
}

void QueryParserTest::testQueryValidationWith2(){
	string query = "procedure p; constant c; Select p with p.procName= c.value  ";
	QueryParser qp;
	bool isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	bool expectedIsValid = false;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	return;
}

void QueryParserTest::testQueryValidationWith3(){
	string query = "procedure p; constant c; Select c with p.procName=10  ";
	QueryParser qp;
	bool isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	bool expectedIsValid = false;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	return;
}

void QueryParserTest::testQuerySemanticSelect(){
	//TEST INVALID
	string query = "procedure p; constant c; Select c such that Modifies (c,p)  ";
	QueryParser qp2;
	bool isValid = true;
	Query parsedQuery2 = qp2.queryParse(query,isValid);

	bool expectedIsValid = false;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//TEST INVALID
	query = "variable   s,s1,s2;procedure p;constant c ;   Select  <  s ,       s1.value,s2  ,p.procName,   c.varName     > such  that Modifies (p,s)  ";
	QueryParser qp3;
	isValid = true;
	Query parsedQuery3 = qp3.queryParse(query,isValid);

	expectedIsValid = false;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//TEST VALID

	//INIT BEGIN
	query = "variable   s,s1,s2;procedure p;constant c ;   Select  <  s ,       s1.varName,s2  ,p.procName,   c.value     > such  that Modifies (p,s)  ";
	QueryParser qp;
	isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	expectedIsValid = true;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	//INIT END
	
	//SELECTEDSYN BEGIN
	//actual selected syn
	vector<string> selectedSyn = parsedQuery.getSelectedSyn();
	//expected selected syn
	vector<string> expectedSelectedSyn;
	expectedSelectedSyn.push_back("s");
	expectedSelectedSyn.push_back("s1");
	expectedSelectedSyn.push_back("s2");
	expectedSelectedSyn.push_back("p");
	expectedSelectedSyn.push_back("c");
	//assert selected syn
	for(int i=0;i<(int)selectedSyn.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedSelectedSyn[i],selectedSyn[i]);
	}
	//SELECTEDSYN END

	//SYNTABLE BEGIN
	//actual syn table
	unordered_map<string, TypeTable::SynType> synTable = parsedQuery.getSynTable();
	unordered_map<string, TypeTable::SynType>::iterator iter;
	iter = synTable.begin();
	//expected syn table
	unordered_map<string, TypeTable::SynType> expectedSynTable;
	expectedSynTable.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
	expectedSynTable.insert(make_pair("s", TypeTable::VARIABLE));
	expectedSynTable.insert(make_pair("s1", TypeTable::VARIABLE));
	expectedSynTable.insert(make_pair("s2", TypeTable::VARIABLE));
	expectedSynTable.insert(make_pair("p", TypeTable::PROCEDURE));
	expectedSynTable.insert(make_pair("c", TypeTable::CONSTANT));
	unordered_map<string, TypeTable::SynType>::iterator expectedIter;
	expectedIter= expectedSynTable.begin();
	//assert syn table
	for(int i=0;i<expectedSynTable.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedIter->first,iter->first);
		CPPUNIT_ASSERT_EQUAL(expectedIter->second,iter->second);
		iter++;
		expectedIter++;
	}
	//SYNTABLE END

	//RELATIONSHIP BEGIN
	//actual relationship
	vector<Relationship> relVect = parsedQuery.getRelVect();
	//expected relationship
	vector<Relationship> expectedRelVect;
	expectedRelVect.push_back(Relationship("Modifies","p",Relationship::SYNONYM,"s",Relationship::SYNONYM));
	//assert relationship
	for(int i=0;i<(int)expectedRelVect.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getRelType(),relVect[i].getRelType());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getPatternSyn(),relVect[i].getPatternSyn());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1(),relVect[i].getToken1());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1Type(),relVect[i].getToken1Type());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2(),relVect[i].getToken2());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2Type(),relVect[i].getToken2Type());
	}
	//RELATIONSHIP END
	return;

}

void QueryParserTest::testQuerySemanticModifies(){
	//TEST INVALID
	string query = "procedure p; constant c; Select c such that Modifies (c,p)  ";
	QueryParser qp2;
	bool isValid = true;
	Query parsedQuery2 = qp2.queryParse(query,isValid);

	bool expectedIsValid = false;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//TEST VALID

	//INIT BEGIN
	query = "variable   s ;   Select   s  such  that Modifies (1,s)  ";
	QueryParser qp;
	isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	expectedIsValid = true;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	//INIT END
	
	//SELECTEDSYN BEGIN
	//actual selected syn
	vector<string> selectedSyn = parsedQuery.getSelectedSyn();
	//expected selected syn
	vector<string> expectedSelectedSyn;
	expectedSelectedSyn.push_back("s");
	//assert selected syn
	for(int i=0;i<(int)expectedSelectedSyn.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedSelectedSyn[i],selectedSyn[i]);
	}
	//SELECTEDSYN END

	//SYNTABLE BEGIN
	//actual syn table
	unordered_map<string, TypeTable::SynType> synTable = parsedQuery.getSynTable();
	unordered_map<string, TypeTable::SynType>::iterator iter;
	iter = synTable.begin();
	//expected syn table
	unordered_map<string, TypeTable::SynType> expectedSynTable;
	expectedSynTable.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
	expectedSynTable.insert(make_pair("s", TypeTable::VARIABLE));
	unordered_map<string, TypeTable::SynType>::iterator expectedIter;
	expectedIter= expectedSynTable.begin();
	//assert syn table
	for(int i=0;i<expectedSynTable.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedIter->first,iter->first);
		CPPUNIT_ASSERT_EQUAL(expectedIter->second,iter->second);
		iter++;
		expectedIter++;
	}
	//SYNTABLE END

	//RELATIONSHIP BEGIN
	//actual relationship
	vector<Relationship> relVect = parsedQuery.getRelVect();
	//expected relationship
	vector<Relationship> expectedRelVect;
	expectedRelVect.push_back(Relationship("Modifies","1",Relationship::INTEGER,"s",Relationship::SYNONYM));
	//assert relationship
	for(int i=0;i<(int)expectedRelVect.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getRelType(),relVect[i].getRelType());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getPatternSyn(),relVect[i].getPatternSyn());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1(),relVect[i].getToken1());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1Type(),relVect[i].getToken1Type());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2(),relVect[i].getToken2());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2Type(),relVect[i].getToken2Type());
	}
	//RELATIONSHIP END
	return;

}

void QueryParserTest::testQuerySemanticUses(){
	//TEST INVALID
	string query = "procedure p; constant c; Select c such that Uses (c,p)  ";
	QueryParser qp2;
	bool isValid = true;
	Query parsedQuery2 = qp2.queryParse(query,isValid);

	bool expectedIsValid = false;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//TEST VALID

	//INIT BEGIN
	query = "variable   s ;   Select   s  such  that Uses (1,s)  ";
	QueryParser qp;
	isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	expectedIsValid = true;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	//INIT END
	
	//SELECTEDSYN BEGIN
	//actual selected syn
	vector<string> selectedSyn = parsedQuery.getSelectedSyn();
	//expected selected syn
	vector<string> expectedSelectedSyn;
	expectedSelectedSyn.push_back("s");
	//assert selected syn
	for(int i=0;i<(int)expectedSelectedSyn.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedSelectedSyn[i],selectedSyn[i]);
	}
	//SELECTEDSYN END

	//SYNTABLE BEGIN
	//actual syn table
	unordered_map<string, TypeTable::SynType> synTable = parsedQuery.getSynTable();
	unordered_map<string, TypeTable::SynType>::iterator iter;
	iter = synTable.begin();
	//expected syn table
	unordered_map<string, TypeTable::SynType> expectedSynTable;
	expectedSynTable.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
	expectedSynTable.insert(make_pair("s", TypeTable::VARIABLE));
	unordered_map<string, TypeTable::SynType>::iterator expectedIter;
	expectedIter= expectedSynTable.begin();
	//assert syn table
	for(int i=0;i<expectedSynTable.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedIter->first,iter->first);
		CPPUNIT_ASSERT_EQUAL(expectedIter->second,iter->second);
		iter++;
		expectedIter++;
	}
	//SYNTABLE END

	//RELATIONSHIP BEGIN
	//actual relationship
	vector<Relationship> relVect = parsedQuery.getRelVect();
	//expected relationship
	vector<Relationship> expectedRelVect;
	expectedRelVect.push_back(Relationship("Uses","1",Relationship::INTEGER,"s",Relationship::SYNONYM));
	//assert relationship
	for(int i=0;i<(int)expectedRelVect.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getRelType(),relVect[i].getRelType());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getPatternSyn(),relVect[i].getPatternSyn());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1(),relVect[i].getToken1());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1Type(),relVect[i].getToken1Type());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2(),relVect[i].getToken2());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2Type(),relVect[i].getToken2Type());
	}
	//RELATIONSHIP END
	return;
}

void QueryParserTest::testQuerySemanticCalls(){
	//TEST INVALID
	string query = "procedure p; constant c; Select c such that Calls (c,p)  ";
	QueryParser qp2;
	bool isValid = true;
	Query parsedQuery2 = qp2.queryParse(query,isValid);

	bool expectedIsValid = false;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//TEST VALID

	//INIT BEGIN
	query = "procedure   s,a;   Select   s  such  that Calls (a,s)  ";
	QueryParser qp;
	isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	expectedIsValid = true;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	//INIT END
	
	//SELECTEDSYN BEGIN
	//actual selected syn
	vector<string> selectedSyn = parsedQuery.getSelectedSyn();
	//expected selected syn
	vector<string> expectedSelectedSyn;
	expectedSelectedSyn.push_back("s");
	//assert selected syn
	for(int i=0;i<(int)expectedSelectedSyn.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedSelectedSyn[i],selectedSyn[i]);
	}
	//SELECTEDSYN END

	//SYNTABLE BEGIN
	//actual syn table
	unordered_map<string, TypeTable::SynType> synTable = parsedQuery.getSynTable();
	unordered_map<string, TypeTable::SynType>::iterator iter;
	iter = synTable.begin();
	//expected syn table
	unordered_map<string, TypeTable::SynType> expectedSynTable;
	expectedSynTable.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
	expectedSynTable.insert(make_pair("s", TypeTable::PROCEDURE));
	expectedSynTable.insert(make_pair("a", TypeTable::PROCEDURE));
	unordered_map<string, TypeTable::SynType>::iterator expectedIter;
	expectedIter= expectedSynTable.begin();
	//assert syn table
	for(int i=0;i<expectedSynTable.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedIter->first,iter->first);
		CPPUNIT_ASSERT_EQUAL(expectedIter->second,iter->second);
		iter++;
		expectedIter++;
	}
	//SYNTABLE END

	//RELATIONSHIP BEGIN
	//actual relationship
	vector<Relationship> relVect = parsedQuery.getRelVect();
	//expected relationship
	vector<Relationship> expectedRelVect;
	expectedRelVect.push_back(Relationship("Calls","a",Relationship::SYNONYM,"s",Relationship::SYNONYM));
	//assert relationship
	for(int i=0;i<(int)expectedRelVect.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getRelType(),relVect[i].getRelType());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getPatternSyn(),relVect[i].getPatternSyn());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1(),relVect[i].getToken1());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1Type(),relVect[i].getToken1Type());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2(),relVect[i].getToken2());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2Type(),relVect[i].getToken2Type());
	}
	//RELATIONSHIP END
	return;
}

void QueryParserTest::testQuerySemanticCallsStar(){
	//TEST INVALID
	string query = "procedure p; constant c; Select c such that Calls* (c,p)  ";
	QueryParser qp2;
	bool isValid = true;
	Query parsedQuery2 = qp2.queryParse(query,isValid);

	bool expectedIsValid = false;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	
	//TEST VALID

	//INIT BEGIN
	query = "procedure   s,a;   Select   s  such  that Calls* (a,s)  ";
	QueryParser qp;
	isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	expectedIsValid = true;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	//INIT END
	
	//SELECTEDSYN BEGIN
	//actual selected syn
	vector<string> selectedSyn = parsedQuery.getSelectedSyn();
	//expected selected syn
	vector<string> expectedSelectedSyn;
	expectedSelectedSyn.push_back("s");
	//assert selected syn
	for(int i=0;i<(int)expectedSelectedSyn.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedSelectedSyn[i],selectedSyn[i]);
	}
	//SELECTEDSYN END

	//SYNTABLE BEGIN
	//actual syn table
	unordered_map<string, TypeTable::SynType> synTable = parsedQuery.getSynTable();
	unordered_map<string, TypeTable::SynType>::iterator iter;
	iter = synTable.begin();
	//expected syn table
	unordered_map<string, TypeTable::SynType> expectedSynTable;
	expectedSynTable.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
	expectedSynTable.insert(make_pair("s", TypeTable::PROCEDURE));
	expectedSynTable.insert(make_pair("a", TypeTable::PROCEDURE));
	unordered_map<string, TypeTable::SynType>::iterator expectedIter;
	expectedIter= expectedSynTable.begin();
	//assert syn table
	for(int i=0;i<expectedSynTable.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedIter->first,iter->first);
		CPPUNIT_ASSERT_EQUAL(expectedIter->second,iter->second);
		iter++;
		expectedIter++;
	}
	//SYNTABLE END

	//RELATIONSHIP BEGIN
	//actual relationship
	vector<Relationship> relVect = parsedQuery.getRelVect();
	//expected relationship
	vector<Relationship> expectedRelVect;
	expectedRelVect.push_back(Relationship("Calls*","a",Relationship::SYNONYM,"s",Relationship::SYNONYM));
	//assert relationship
	for(int i=0;i<(int)expectedRelVect.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getRelType(),relVect[i].getRelType());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getPatternSyn(),relVect[i].getPatternSyn());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1(),relVect[i].getToken1());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1Type(),relVect[i].getToken1Type());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2(),relVect[i].getToken2());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2Type(),relVect[i].getToken2Type());
	}
	//RELATIONSHIP END
	return;
}

void QueryParserTest::testQuerySemanticParent(){
	//TEST INVALID
	string query = "variable p; constant c; Select c such that Parent (c,p)  ";
	QueryParser qp2;
	bool isValid = true;
	Query parsedQuery2 = qp2.queryParse(query,isValid);

	bool expectedIsValid = false;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	
	//TEST VALID

	//INIT BEGIN
	query = "while   s,a;   Select   s  such  that Parent (a,s)  ";
	QueryParser qp;
	isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	expectedIsValid = true;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	//INIT END
	
	//SELECTEDSYN BEGIN
	//actual selected syn
	vector<string> selectedSyn = parsedQuery.getSelectedSyn();
	//expected selected syn
	vector<string> expectedSelectedSyn;
	expectedSelectedSyn.push_back("s");
	//assert selected syn
	for(int i=0;i<(int)expectedSelectedSyn.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedSelectedSyn[i],selectedSyn[i]);
	}
	//SELECTEDSYN END

	//SYNTABLE BEGIN
	//actual syn table
	unordered_map<string, TypeTable::SynType> synTable = parsedQuery.getSynTable();
	unordered_map<string, TypeTable::SynType>::iterator iter;
	iter = synTable.begin();
	//expected syn table
	unordered_map<string, TypeTable::SynType> expectedSynTable;
	expectedSynTable.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
	expectedSynTable.insert(make_pair("s", TypeTable::WHILE));
	expectedSynTable.insert(make_pair("a", TypeTable::WHILE));
	unordered_map<string, TypeTable::SynType>::iterator expectedIter;
	expectedIter= expectedSynTable.begin();
	//assert syn table
	for(int i=0;i<expectedSynTable.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedIter->first,iter->first);
		CPPUNIT_ASSERT_EQUAL(expectedIter->second,iter->second);
		iter++;
		expectedIter++;
	}
	//SYNTABLE END

	//RELATIONSHIP BEGIN
	//actual relationship
	vector<Relationship> relVect = parsedQuery.getRelVect();
	//expected relationship
	vector<Relationship> expectedRelVect;
	expectedRelVect.push_back(Relationship("Parent","a",Relationship::SYNONYM,"s",Relationship::SYNONYM));
	//assert relationship
	for(int i=0;i<(int)expectedRelVect.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getRelType(),relVect[i].getRelType());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getPatternSyn(),relVect[i].getPatternSyn());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1(),relVect[i].getToken1());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1Type(),relVect[i].getToken1Type());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2(),relVect[i].getToken2());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2Type(),relVect[i].getToken2Type());
	}
	//RELATIONSHIP END
	return;
}

void QueryParserTest::testQuerySemanticParentStar(){
	//TEST INVALID
	string query = "procedure p; constant c; Select c such that Parent* (c,p)  ";
	QueryParser qp2;
	bool isValid = true;
	Query parsedQuery2 = qp2.queryParse(query,isValid);

	bool expectedIsValid = false;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	
	//TEST VALID

	//INIT BEGIN
	query = "while   s,a;   Select   s  such  that Parent* (a,s)  ";
	QueryParser qp;
	isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	expectedIsValid = true;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	//INIT END
	
	//SELECTEDSYN BEGIN
	//actual selected syn
	vector<string> selectedSyn = parsedQuery.getSelectedSyn();
	//expected selected syn
	vector<string> expectedSelectedSyn;
	expectedSelectedSyn.push_back("s");
	//assert selected syn
	for(int i=0;i<(int)expectedSelectedSyn.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedSelectedSyn[i],selectedSyn[i]);
	}
	//SELECTEDSYN END

	//SYNTABLE BEGIN
	//actual syn table
	unordered_map<string, TypeTable::SynType> synTable = parsedQuery.getSynTable();
	unordered_map<string, TypeTable::SynType>::iterator iter;
	iter = synTable.begin();
	//expected syn table
	unordered_map<string, TypeTable::SynType> expectedSynTable;
	expectedSynTable.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
	expectedSynTable.insert(make_pair("s", TypeTable::WHILE));
	expectedSynTable.insert(make_pair("a", TypeTable::WHILE));
	unordered_map<string, TypeTable::SynType>::iterator expectedIter;
	expectedIter= expectedSynTable.begin();
	//assert syn table
	for(int i=0;i<expectedSynTable.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedIter->first,iter->first);
		CPPUNIT_ASSERT_EQUAL(expectedIter->second,iter->second);
		iter++;
		expectedIter++;
	}
	//SYNTABLE END

	//RELATIONSHIP BEGIN
	//actual relationship
	vector<Relationship> relVect = parsedQuery.getRelVect();
	//expected relationship
	vector<Relationship> expectedRelVect;
	expectedRelVect.push_back(Relationship("Parent*","a",Relationship::SYNONYM,"s",Relationship::SYNONYM));
	//assert relationship
	for(int i=0;i<(int)expectedRelVect.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getRelType(),relVect[i].getRelType());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getPatternSyn(),relVect[i].getPatternSyn());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1(),relVect[i].getToken1());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1Type(),relVect[i].getToken1Type());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2(),relVect[i].getToken2());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2Type(),relVect[i].getToken2Type());
	}
	//RELATIONSHIP END
	return;
}

void QueryParserTest::testQuerySemanticNext(){
	//TEST INVALID
	string query = "variable p; constant c; Select c such that Next(c,p)  ";
	QueryParser qp2;
	bool isValid = true;
	Query parsedQuery2 = qp2.queryParse(query,isValid);

	bool expectedIsValid = false;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	
	//TEST VALID

	//INIT BEGIN
	query = "prog_line   s,a;   Select   s  such  that Next (a,s)  ";
	QueryParser qp;
	isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	expectedIsValid = true;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	//INIT END
	
	//SELECTEDSYN BEGIN
	//actual selected syn
	vector<string> selectedSyn = parsedQuery.getSelectedSyn();
	//expected selected syn
	vector<string> expectedSelectedSyn;
	expectedSelectedSyn.push_back("s");
	//assert selected syn
	for(int i=0;i<(int)expectedSelectedSyn.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedSelectedSyn[i],selectedSyn[i]);
	}
	//SELECTEDSYN END

	//SYNTABLE BEGIN
	//actual syn table
	unordered_map<string, TypeTable::SynType> synTable = parsedQuery.getSynTable();
	unordered_map<string, TypeTable::SynType>::iterator iter;
	iter = synTable.begin();
	//expected syn table
	unordered_map<string, TypeTable::SynType> expectedSynTable;
	expectedSynTable.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
	expectedSynTable.insert(make_pair("s", TypeTable::PROGLINE));
	expectedSynTable.insert(make_pair("a", TypeTable::PROGLINE));
	unordered_map<string, TypeTable::SynType>::iterator expectedIter;
	expectedIter= expectedSynTable.begin();
	//assert syn table
	for(int i=0;i<expectedSynTable.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedIter->first,iter->first);
		CPPUNIT_ASSERT_EQUAL(expectedIter->second,iter->second);
		iter++;
		expectedIter++;
	}
	//SYNTABLE END

	//RELATIONSHIP BEGIN
	//actual relationship
	vector<Relationship> relVect = parsedQuery.getRelVect();
	//expected relationship
	vector<Relationship> expectedRelVect;
	expectedRelVect.push_back(Relationship("Next","a",Relationship::SYNONYM,"s",Relationship::SYNONYM));
	//assert relationship
	for(int i=0;i<(int)expectedRelVect.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getRelType(),relVect[i].getRelType());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getPatternSyn(),relVect[i].getPatternSyn());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1(),relVect[i].getToken1());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1Type(),relVect[i].getToken1Type());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2(),relVect[i].getToken2());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2Type(),relVect[i].getToken2Type());
	}
	//RELATIONSHIP END
	return;
}

void QueryParserTest::testQuerySemanticNextStar(){
	//TEST INVALID
	string query = "procedure p; constant c; Select c such that Next*(c,p)  ";
	QueryParser qp2;
	bool isValid = true;
	Query parsedQuery2 = qp2.queryParse(query,isValid);

	bool expectedIsValid = false;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	
	//TEST VALID

	//INIT BEGIN
	query = "prog_line   s,a;   Select   s  such  that Next* (a,s)  ";
	QueryParser qp;
	isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	expectedIsValid = true;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	//INIT END
	
	//SELECTEDSYN BEGIN
	//actual selected syn
	vector<string> selectedSyn = parsedQuery.getSelectedSyn();
	//expected selected syn
	vector<string> expectedSelectedSyn;
	expectedSelectedSyn.push_back("s");
	//assert selected syn
	for(int i=0;i<(int)expectedSelectedSyn.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedSelectedSyn[i],selectedSyn[i]);
	}
	//SELECTEDSYN END

	//SYNTABLE BEGIN
	//actual syn table
	unordered_map<string, TypeTable::SynType> synTable = parsedQuery.getSynTable();
	unordered_map<string, TypeTable::SynType>::iterator iter;
	iter = synTable.begin();
	//expected syn table
	unordered_map<string, TypeTable::SynType> expectedSynTable;
	expectedSynTable.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
	expectedSynTable.insert(make_pair("s", TypeTable::PROGLINE));
	expectedSynTable.insert(make_pair("a", TypeTable::PROGLINE));
	unordered_map<string, TypeTable::SynType>::iterator expectedIter;
	expectedIter= expectedSynTable.begin();
	//assert syn table
	for(int i=0;i<expectedSynTable.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedIter->first,iter->first);
		CPPUNIT_ASSERT_EQUAL(expectedIter->second,iter->second);
		iter++;
		expectedIter++;
	}
	//SYNTABLE END

	//RELATIONSHIP BEGIN
	//actual relationship
	vector<Relationship> relVect = parsedQuery.getRelVect();
	//expected relationship
	vector<Relationship> expectedRelVect;
	expectedRelVect.push_back(Relationship("Next*","a",Relationship::SYNONYM,"s",Relationship::SYNONYM));
	//assert relationship
	for(int i=0;i<(int)expectedRelVect.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getRelType(),relVect[i].getRelType());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getPatternSyn(),relVect[i].getPatternSyn());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1(),relVect[i].getToken1());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1Type(),relVect[i].getToken1Type());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2(),relVect[i].getToken2());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2Type(),relVect[i].getToken2Type());
	}
	//RELATIONSHIP END
	return;
}

void QueryParserTest::testQuerySemanticAffects(){
	//TEST INVALID
	string query = "variable p; constant c; Select c such that Affects (c,p)  ";
	QueryParser qp2;
	bool isValid = true;
	Query parsedQuery2 = qp2.queryParse(query,isValid);

	bool expectedIsValid = false;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	
	//TEST VALID

	//INIT BEGIN
	query = "assign   s,a;   Select   s  such  that Affects (a,s)  ";
	QueryParser qp;
	isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	expectedIsValid = true;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	//INIT END
	
	//SELECTEDSYN BEGIN
	//actual selected syn
	vector<string> selectedSyn = parsedQuery.getSelectedSyn();
	//expected selected syn
	vector<string> expectedSelectedSyn;
	expectedSelectedSyn.push_back("s");
	//assert selected syn
	for(int i=0;i<(int)expectedSelectedSyn.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedSelectedSyn[i],selectedSyn[i]);
	}
	//SELECTEDSYN END

	//SYNTABLE BEGIN
	//actual syn table
	unordered_map<string, TypeTable::SynType> synTable = parsedQuery.getSynTable();
	unordered_map<string, TypeTable::SynType>::iterator iter;
	iter = synTable.begin();
	//expected syn table
	unordered_map<string, TypeTable::SynType> expectedSynTable;
	expectedSynTable.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
	expectedSynTable.insert(make_pair("s", TypeTable::ASSIGN));
	expectedSynTable.insert(make_pair("a", TypeTable::ASSIGN));
	unordered_map<string, TypeTable::SynType>::iterator expectedIter;
	expectedIter= expectedSynTable.begin();
	//assert syn table
	for(int i=0;i<expectedSynTable.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedIter->first,iter->first);
		CPPUNIT_ASSERT_EQUAL(expectedIter->second,iter->second);
		iter++;
		expectedIter++;
	}
	//SYNTABLE END

	//RELATIONSHIP BEGIN
	//actual relationship
	vector<Relationship> relVect = parsedQuery.getRelVect();
	//expected relationship
	vector<Relationship> expectedRelVect;
	expectedRelVect.push_back(Relationship("Affects","a",Relationship::SYNONYM,"s",Relationship::SYNONYM));
	//assert relationship
	for(int i=0;i<(int)expectedRelVect.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getRelType(),relVect[i].getRelType());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getPatternSyn(),relVect[i].getPatternSyn());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1(),relVect[i].getToken1());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1Type(),relVect[i].getToken1Type());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2(),relVect[i].getToken2());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2Type(),relVect[i].getToken2Type());
	}
	//RELATIONSHIP END
	return;
}

void QueryParserTest::testQuerySemanticAffectsStar(){
	//TEST INVALID
	string query = "procedure p; constant c; Select c such that Affects* (c,p)  ";
	QueryParser qp2;
	bool isValid = true;
	Query parsedQuery2 = qp2.queryParse(query,isValid);

	bool expectedIsValid = false;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	
	//TEST VALID

	//INIT BEGIN
	query = "assign   s,a;   Select   s  such  that Affects* (a,s)  ";
	QueryParser qp;
	isValid = true;
	Query parsedQuery = qp.queryParse(query,isValid);

	expectedIsValid = true;
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);
	//INIT END
	
	//SELECTEDSYN BEGIN
	//actual selected syn
	vector<string> selectedSyn = parsedQuery.getSelectedSyn();
	//expected selected syn
	vector<string> expectedSelectedSyn;
	expectedSelectedSyn.push_back("s");
	//assert selected syn
	for(int i=0;i<(int)expectedSelectedSyn.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedSelectedSyn[i],selectedSyn[i]);
	}
	//SELECTEDSYN END

	//SYNTABLE BEGIN
	//actual syn table
	unordered_map<string, TypeTable::SynType> synTable = parsedQuery.getSynTable();
	unordered_map<string, TypeTable::SynType>::iterator iter;
	iter = synTable.begin();
	//expected syn table
	unordered_map<string, TypeTable::SynType> expectedSynTable;
	expectedSynTable.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
	expectedSynTable.insert(make_pair("s", TypeTable::ASSIGN));
	expectedSynTable.insert(make_pair("a", TypeTable::ASSIGN));
	unordered_map<string, TypeTable::SynType>::iterator expectedIter;
	expectedIter= expectedSynTable.begin();
	//assert syn table
	for(int i=0;i<expectedSynTable.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedIter->first,iter->first);
		CPPUNIT_ASSERT_EQUAL(expectedIter->second,iter->second);
		iter++;
		expectedIter++;
	}
	//SYNTABLE END

	//RELATIONSHIP BEGIN
	//actual relationship
	vector<Relationship> relVect = parsedQuery.getRelVect();
	//expected relationship
	vector<Relationship> expectedRelVect;
	expectedRelVect.push_back(Relationship("Affects*","a",Relationship::SYNONYM,"s",Relationship::SYNONYM));
	//assert relationship
	for(int i=0;i<(int)expectedRelVect.size();i++){
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getRelType(),relVect[i].getRelType());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getPatternSyn(),relVect[i].getPatternSyn());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1(),relVect[i].getToken1());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken1Type(),relVect[i].getToken1Type());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2(),relVect[i].getToken2());
		CPPUNIT_ASSERT_EQUAL(expectedRelVect[i].getToken2Type(),relVect[i].getToken2Type());
	}
	//RELATIONSHIP END
	return;
}

void QueryParserTest::testQBasic1F_invalid_queries(){
	QueryParser* qp;
	Query parsedQuery;
	string query;
	bool isValid = true;
	bool expectedIsValid = false;

	//1
	isValid = true;
	qp = new QueryParser();
	query = "prog_line pl; variable v; Select pl with pl.prog_line# = v.varName";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//2
	isValid = true;
	qp = new QueryParser();
	query = "prog_line pl; variable v;Select v with pl.prog_line# = v.varName ";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//3
	isValid = true;
	qp = new QueryParser();
	query = "prog_line pl; procedure p;Select pl with pl.prog_line# = p.procName ";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//4
	isValid = true;
	qp = new QueryParser();
	query = "prog_line pl; procedure p;Select p with pl.prog_line# = p.procName";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//5
	isValid = true;
	qp = new QueryParser();
	query = "constant c; variable v;Select c with c.value = v.varName";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//6
	isValid = true;
	qp = new QueryParser();
	query = "constant c; procedure p;Select c with c.value = p.procName";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//7
	isValid = true;
	qp = new QueryParser();
	query = "constant c; variable v;Select v with c.value = v.varName";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//8
	isValid = true;
	qp = new QueryParser();
	query = "constant c; procedure p; Select p with c.value = p.procName";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//17
	isValid = true;
	qp = new QueryParser();
	query = "prog_line pl; procedure p; Select pl with pl.procName = \"wrong\"";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//18
	isValid = true;
	qp = new QueryParser();
	query = "prog_line pl; procedure p;Select p with p.prog_line# = 34";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//19
	isValid = true;
	qp = new QueryParser();
	query = "prog_line pl; procedure p;Select pl with pl.varName = \"stillwrong\"";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//20
	isValid = true;
	qp = new QueryParser();
	query = "prog_line pl; Select pl with pl.value = 56";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//21
	isValid = true;
	qp = new QueryParser();
	query = "prog_line pl;Select pl with pl.stmt# = 999";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//22
	isValid = true;
	qp = new QueryParser();
	query = "procedure p; Select p with p.varName = \"wrong\"";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//23
	isValid = true;
	qp = new QueryParser();
	query = "procedure p; Select p with p.value = 23";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//24
	isValid = true;
	qp = new QueryParser();
	query = "variable v; Select v with v.procName = \"fantastic\"";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//25
	isValid = true;
	qp = new QueryParser();
	query = "variable v; Select v with v.value = 888";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//26
	isValid = true;
	qp = new QueryParser();
	query = "variable v; Select v with v.prog_line# = 89797";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//27
	isValid = true;
	qp = new QueryParser();
	query = "stmt s; Select s with s.procName = \"somthing\"";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//28
	isValid = true;
	qp = new QueryParser();
	query = "stmt s; Select s with s.varName = \"somthing\"";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//29
	isValid = true;
	qp = new QueryParser();
	query = "stmt s;Select s with s.value = 90000";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//30
	isValid = true;
	qp = new QueryParser();
	query = "stmt s;Select s with s.prog_line# = 999";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//31
	isValid = true;
	qp = new QueryParser();
	query = "while s; Select s with s.procName = \"somthing\"";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//32
	isValid = true;
	qp = new QueryParser();
	query = "while s; Select s with s.varName = \"somthing\"";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//33
	isValid = true;
	qp = new QueryParser();
	query = "while s;Select s with s.value = 90000";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//34
	isValid = true;
	qp = new QueryParser();
	query = "while s; Select s with s.prog_line# = 999";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//35
	isValid = true;
	qp = new QueryParser();
	query = "if s; Select s with s.procName = \"somthing\"";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//36
	isValid = true;
	qp = new QueryParser();
	query = "if s;Select s with s.varName = \"somthing\"";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//37
	isValid = true;
	qp = new QueryParser();
	query = "if s; Select s with s.value = 90000";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//38
	isValid = true;
	qp = new QueryParser();
	query = "if s; Select s with s.prog_line# = 999";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//39
	isValid = true;
	qp = new QueryParser();
	query = "assign s; Select s with s.procName = \"somthing\"";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//40
	isValid = true;
	qp = new QueryParser();
	query = "assign s; Select s with s.varName = \"somthing\"";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//41
	isValid = true;
	qp = new QueryParser();
	query = "assign s; Select s with s.value = 90000";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//42
	isValid = true;
	qp = new QueryParser();
	query = "assign s; Select s with s.prog_line# = 999";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//43
	isValid = true;
	qp = new QueryParser();
	query = "constant c;Select c with c.procName = \"wrong\"";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//44
	isValid = true;
	qp = new QueryParser();
	query = "constant c; Select c with c.stmt# = 78";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//45
	isValid = true;
	qp = new QueryParser();
	query = "constant c;Select c with c.varName = \"wrong\"";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//46
	isValid = true;
	qp = new QueryParser();
	query = "constant c; Select c with c.prog_line# = 89";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//47
	isValid = true;
	qp = new QueryParser();
	query = "procedure p; Select p with p.procName = 89";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//48
	isValid = true;
	qp = new QueryParser();
	query = "stmt s; Select s with s.stmt# = \"number\"";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//49
	isValid = true;
	qp = new QueryParser();
	query = "assign a; Select a with a.stmt# = \"number\"";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//50
	isValid = true;
	qp = new QueryParser();
	query = "while w; Select w with w.stmt# = \"number\"";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//51
	isValid = true;
	qp = new QueryParser();
	query = "if i; Select i with i.stmt# = \"number\"";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//52
	isValid = true;
	qp = new QueryParser();
	query = "variable v; Select v with v.varName = 000";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//53
	isValid = true;
	qp = new QueryParser();
	query = "constant c; Select c with c.value = somenum";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//54
	isValid = true;
	qp = new QueryParser();
	query = "constant c; Select c with c.value = \"somenum\"";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//55
	isValid = true;
	qp = new QueryParser();
	query = "prog_line pl; Select pl with pl.prog_line# = somenum";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//56
	isValid = true;
	qp = new QueryParser();
	query = "prog_line pl; Select pl with pl.prog_line# = \"somenum\"";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//57
	//isValid = true;
	//qp = new QueryParser();
	//query = "constant c; Select c with c.value = 0098";
	//parsedQuery = qp->queryParse(query,isValid);
	//CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//58
	//isValid = true;
	//qp = new QueryParser();
	//query = "stmt s; Select s with s.stmt# = 009";
	//parsedQuery = qp->queryParse(query,isValid);
	//CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//59
	isValid = true;
	qp = new QueryParser();
	query = "stmt s; Select s with s.stmt# = number";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//60
	isValid = true;
	qp = new QueryParser();
	query = "assign a; Select a with a.stmt# = number";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//61
	isValid = true;
	qp = new QueryParser();
	query = "while w; Select w with w.stmt# = number";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//62
	isValid = true;
	qp = new QueryParser();
	query = "if i; Select i with i.stmt# = number";
	parsedQuery = qp->queryParse(query,isValid);
	CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//63
	//isValid = true;
	//qp = new QueryParser();
	//query = "stmt s1, s2; Select BOOLEAN such that Calls (s1, s2);";
	//parsedQuery = qp->queryParse(query,isValid);
	//CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//64
	//isValid = true;
	//qp = new QueryParser();
	//query = "stmt s1, s2; procedure p; Select p such that Calls (s1, s2);";
	//parsedQuery = qp->queryParse(query,isValid);
	//CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//65
	//isValid = true;
	//qp = new QueryParser();
	//query = "stmt s1, s2; procedure p; Select p such that Calls (p, s1);";
	//parsedQuery = qp->queryParse(query,isValid);
	//CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//66
	//isValid = true;
	//qp = new QueryParser();
	//query = "stmt s1; procedure p; Select BOOLEAN such that Calls (p, s1);";
	//parsedQuery = qp->queryParse(query,isValid);
	//CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//67
	//isValid = true;
	//qp = new QueryParser();
	//query = "stmt s1, s2; procedure p; Select p such that Calls (s1, p);";
	//parsedQuery = qp->queryParse(query,isValid);
	//CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//68
	//isValid = true;
	//qp = new QueryParser();
	//query = "stmt s1, s2; procedure p; Select BOOLEAN such that Calls (s1, p)";
	//parsedQuery = qp->queryParse(query,isValid);
	//CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//69
	//isValid = true;
	//qp = new QueryParser();
	//query = "stmt s1, s2; constant c; procedure p; Select BOOLEAN such that Calls* (p, c);";
	//parsedQuery = qp->queryParse(query,isValid);
	//CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	//70
	//isValid = true;
	//qp = new QueryParser();
	//query = "stmt s1, s2; procedure p; constant c; Select p such that Calls* (c, p);";
	//parsedQuery = qp->queryParse(query,isValid);
	//CPPUNIT_ASSERT_EQUAL(expectedIsValid,isValid);

	return;
}
