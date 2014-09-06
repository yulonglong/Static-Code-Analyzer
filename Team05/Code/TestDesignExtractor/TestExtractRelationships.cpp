//@author Ipsita Mohapatra
//TestExtractRelationships.cpp

#include <cppunit/config/SourcePrefix.h>
#include "Node.h"
#include "DesignExtractor.h"
#include "TestExtractRelationships.h"
#include "CodeParser.h"
#include "PKB.h"

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

PKB *pkb;
Node* ASTRoot;
Modifies* modifies;
Uses* uses;
Parent* parent;
ProcTable* procTable;
VarTable* varTable;
unordered_map<PROCINDEX, vector<CALLSPAIR>> callsTable; 

void ExtractRelationshipsTest::setUp() {
}

void ExtractRelationshipsTest::tearDown() {
}

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( ExtractRelationshipsTest ); // Note 4 

void ExtractRelationshipsTest::testModifiesProcedure() {
	pkb = PKB::getInstance();
	parserDriver("SourceDE1.txt",pkb);

	ASTRoot = pkb->getASTRoot();
	modifies = pkb->getModifies();
	uses = pkb->getUses();
	parent = pkb->getParent();
	procTable = pkb->getProcTable();
	varTable = pkb->getVarTable();
	callsTable = pkb->getCallsTable();
	extractRelationships(*ASTRoot, callsTable, *procTable, *modifies, *uses, *parent);

	vector<VARINDEX> v;
	v =	modifies->getModifiesProc(0);
	string expected = "x z y i b d e f w a ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *varTable));
	v =	modifies->getModifiesProc(1);
	expected = "x z y i b d e f ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *varTable));
	v =	modifies->getModifiesProc(2);
	expected = "b d ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *varTable));
	v =	modifies->getModifiesProc(3);
	expected = "e f ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *varTable));
	v =	modifies->getModifiesProc(4);
	expected = "e f w a ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *varTable));
}

void ExtractRelationshipsTest::testUsesProcedure() {
	vector<VARINDEX> v;
	v =	uses->getUsesProc(0);
	string expected = "x z y i c g w ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *varTable));
	v = uses->getUsesProc(1);
	expected = "x z y i c g ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *varTable));
	v = uses->getUsesProc(2);
	expected = "c ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *varTable));
	v = uses->getUsesProc(3);
	expected = "g ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *varTable));
	v = uses->getUsesProc(4);
	expected = "g w ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *varTable));
}

void ExtractRelationshipsTest::testModifiesStatement() {
	vector<VARINDEX> v;
	v =	modifies->getModifies(3);
	string expected = "x z y i b d e f ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *varTable));
	v =	modifies->getModifies(5);
	expected = "e f w a ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *varTable));
	v =	modifies->getModifies(6);
	expected = "x i b d ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *varTable));
	v =	modifies->getModifies(8);
	expected = "b d ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *varTable));
	v =	modifies->getModifies(10);
	expected = "e f ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *varTable));
	v =	modifies->getModifies(21);
	expected = "e f ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *varTable));
	
	v =	modifies->getModifies(22);
	expected = "w ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *varTable));
	
	v =	modifies->getModifies(23);
	expected = "a ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *varTable));
	
}

void ExtractRelationshipsTest::testUsesStatement() {
	vector<VARINDEX> v;
	v =	uses->getUses(3);
	string expected = "x z y i c g ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *varTable));
	v =	uses->getUses(5);
	expected = "g w ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *varTable));
	v =	uses->getUses(6);
	expected = "x y i c ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *varTable));
	v =	uses->getUses(8);
	expected = "c ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *varTable));
	v =	uses->getUses(10);
	expected = "g ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *varTable));
	v =	uses->getUses(21);
	expected = "g ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *varTable));
	
	v =	uses->getUses(22);
	expected = "";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *varTable));
	
	v =	uses->getUses(23);
	expected = "w ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *varTable));
	
}

// Given a vector of VARINDEX and the corresponding varTable, returns a String of the VARNAMEs
string ExtractRelationshipsTest::print(vector<VARINDEX> v, VarTable varTable) {
	string s = "";
	for (int i=0; i<v.size(); i++) {
		s += varTable.getVarName(v[i]);
		s += " ";
	}
	return s; 
}


