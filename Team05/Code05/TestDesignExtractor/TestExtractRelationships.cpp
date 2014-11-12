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

	set<VARINDEX> v;
	v =	pkb->getModifiedProc(1);
	string expected = "x z y i b d e f w a ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	v =	pkb->getModifiedProc(2);
	expected = "x z y i b d e f ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	v =	pkb->getModifiedProc(3);
	expected = "b d ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	v =	pkb->getModifiedProc(4);
	expected = "e f ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	v =	pkb->getModifiedProc(5);
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

	set<VARINDEX> v;
	v =	pkb->getUsedProc(1);
	string expected = "x z y i c g w ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	v = pkb->getUsedProc(2);
	expected = "x z y i c g ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	v = pkb->getUsedProc(3);
	expected = "c ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	v = pkb->getUsedProc(4);
	expected = "g ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	v = pkb->getUsedProc(5);
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

	set<VARINDEX> v;
	v =	pkb->getModified(3);
	string expected = "x z y i b d e f ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	v =	pkb->getModified(5);
	expected = "e f w a ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	v =	pkb->getModified(6);
	expected = "x i b d ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	v =	pkb->getModified(8);
	expected = "b d ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	v =	pkb->getModified(10);
	expected = "e f ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	v =	pkb->getModified(21);
	expected = "e f ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	
	v =	pkb->getModified(22);
	expected = "w ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	
	v =	pkb->getModified(23);
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

	set<VARINDEX> v;
	v =	pkb->getUsed(3);
	string expected = "x z y i c g ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	v =	pkb->getUsed(5);
	expected = "g w ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	v =	pkb->getUsed(6);
	expected = "x y i c ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	v =	pkb->getUsed(8);
	expected = "c ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	v =	pkb->getUsed(10);
	expected = "g ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	v =	pkb->getUsed(21);
	expected = "g ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	
	v =	pkb->getUsed(22);
	expected = "";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	
	v =	pkb->getUsed(23);
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

	set<VARINDEX> v;
	v =	pkb->getUsed(1);
	string expected = "a beta tmp I k j1k chArlie x left right Romeo c delta l width w may june ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	
	v =	pkb->getUsed(2);
	expected = "beta tmp I k j1k chArlie x left right Romeo c delta l width may june ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	
	v =	pkb->getUsed(4);
	expected = "june ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	
	v =	pkb->getUsed(12);
	expected = "may ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	
	v =	pkb->getModified(1);
	expected = "a oSCar x Romeo c w may june ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));

	v =	pkb->getModified(2);
	expected = "a oSCar x Romeo c may june ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));

	v =	pkb->getModified(4);
	expected = "a june ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	
	v =	pkb->getModified(12);
	expected = "a may ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *pkb));
	pkb->~PKB();
}

// Given a set of VARINDEX and the corresponding varTable, returns a String of the VARNAMEs
string ExtractRelationshipsTest::print(set<VARINDEX> v, PKB &pkb) {
	string s = "";
	/*for (int i=0; i<v.size(); i++) {
		s += pkb.getVarName(v[i]);
		s += " ";
	}*/
	set<int>::iterator it;
	for (it = v.begin(); it != v.end(); ++it) {
		s += pkb.getVarName(*it);
		s += " ";
	}
	return s; 
}


