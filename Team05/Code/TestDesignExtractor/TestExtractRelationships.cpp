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


void ExtractRelationshipsTest::setUp() {
}

void ExtractRelationshipsTest::tearDown() {
}

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( ExtractRelationshipsTest ); // Note 4 

void ExtractRelationshipsTest::testModifiesProcedure() {
	PKB *pkb;
	Node* ASTRoot;
	unordered_map<PROCINDEX, vector<CALLSPAIR>> callsTable; 

	pkb = PKB::getInstance();
	CodeParser::parserDriver("SourceDE1.txt",pkb);

	ASTRoot = pkb->getASTRoot();
	callsTable = pkb->getCallsTable();

	DesignExtractor::extractRelationships(*ASTRoot, callsTable, *pkb);

	vector<VARINDEX> v;
	v =	pkb->getModifiesProc(0);
	string expected = "x z y i b d e f w a ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	v =	pkb->getModifiesProc(1);
	expected = "x z y i b d e f ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	v =	pkb->getModifiesProc(2);
	expected = "b d ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	v =	pkb->getModifiesProc(3);
	expected = "e f ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	v =	pkb->getModifiesProc(4);
	expected = "e f w a ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	pkb->~PKB();
}

void ExtractRelationshipsTest::testUsesProcedure() {
	PKB *pkb;
	Node* ASTRoot;
	unordered_map<PROCINDEX, vector<CALLSPAIR>> callsTable; 

	pkb = PKB::getInstance();
	CodeParser::parserDriver("SourceDE1.txt",pkb);

	ASTRoot = pkb->getASTRoot();
	callsTable = pkb->getCallsTable();
	DesignExtractor::extractRelationships(*ASTRoot, callsTable, *pkb);

	vector<VARINDEX> v;
	v =	pkb->getUsesProc(0);
	string expected = "x z y i c g w ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	v = pkb->getUsesProc(1);
	expected = "x z y i c g ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	v = pkb->getUsesProc(2);
	expected = "c ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	v = pkb->getUsesProc(3);
	expected = "g ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	v = pkb->getUsesProc(4);
	expected = "g w ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	pkb->~PKB();

}

void ExtractRelationshipsTest::testModifiesStatement() {
	PKB *pkb;
	Node* ASTRoot;
	VarTable* varTable;
	unordered_map<PROCINDEX, vector<CALLSPAIR>> callsTable; 

	pkb = PKB::getInstance();
	CodeParser::parserDriver("SourceDE1.txt",pkb);

	ASTRoot = pkb->getASTRoot();
	varTable = pkb->getVarTable();
	callsTable = pkb->getCallsTable();
	DesignExtractor::extractRelationships(*ASTRoot, callsTable, *pkb);

	vector<VARINDEX> v;
	v =	pkb->getModifies(3);
	string expected = "x z y i b d e f ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	v =	pkb->getModifies(5);
	expected = "e f w a ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	v =	pkb->getModifies(6);
	expected = "x i b d ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	v =	pkb->getModifies(8);
	expected = "b d ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	v =	pkb->getModifies(10);
	expected = "e f ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	v =	pkb->getModifies(21);
	expected = "e f ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	
	v =	pkb->getModifies(22);
	expected = "w ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	
	v =	pkb->getModifies(23);
	expected = "a ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	pkb->~PKB();

}

void ExtractRelationshipsTest::testUsesStatement() {
	PKB *pkb;
	Node* ASTRoot;
	unordered_map<PROCINDEX, vector<CALLSPAIR>> callsTable; 

	pkb = PKB::getInstance();
	CodeParser::parserDriver("SourceDE1.txt",pkb);

	ASTRoot = pkb->getASTRoot();
	callsTable = pkb->getCallsTable();
	DesignExtractor::extractRelationships(*ASTRoot, callsTable, *pkb);

	vector<VARINDEX> v;
	v =	pkb->getUses(3);
	string expected = "x z y i c g ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	v =	pkb->getUses(5);
	expected = "g w ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	v =	pkb->getUses(6);
	expected = "x y i c ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	v =	pkb->getUses(8);
	expected = "c ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	v =	pkb->getUses(10);
	expected = "g ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	v =	pkb->getUses(21);
	expected = "g ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	
	v =	pkb->getUses(22);
	expected = "";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	
	v =	pkb->getUses(23);
	expected = "w ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	pkb->~PKB();
}

void ExtractRelationshipsTest::testFullSourceDE2() {
	PKB *pkb;
	Node* ASTRoot;
	unordered_map<PROCINDEX, vector<CALLSPAIR>> callsTable; 

	pkb = PKB::getInstance();
	CodeParser::parserDriver("SourceDE2.txt",pkb);

	ASTRoot = pkb->getASTRoot();
	callsTable = pkb->getCallsTable();
	DesignExtractor::extractRelationships(*ASTRoot, callsTable, *pkb);

	vector<VARINDEX> v;
	v =	pkb->getUses(1);
	string expected = "a beta tmp I k j1k chArlie x left right Romeo c delta l width w may june ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	
	v =	pkb->getUses(2);
	expected = "beta tmp I k j1k chArlie x left right Romeo c delta l width may june ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	
	v =	pkb->getUses(4);
	expected = "june ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	
	v =	pkb->getUses(12);
	expected = "may ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	
	v =	pkb->getModifies(1);
	expected = "a oSCar x Romeo c w may june ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));

	v =	pkb->getModifies(2);
	expected = "a oSCar x Romeo c may june ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));

	v =	pkb->getModifies(4);
	expected = "a june ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	
	v =	pkb->getModifies(12);
	expected = "a may ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	pkb->~PKB();
}

// Given a vector of VARINDEX and the corresponding varTable, returns a String of the VARNAMEs
string ExtractRelationshipsTest::print(vector<VARINDEX> v, PKB &pkb) {
	string s = "";
	for (int i=0; i<v.size(); i++) {
		s += pkb.getVarName(v[i]);
		s += " ";
	}
	return s; 
}


