//@author Ipsita Mohapatra
//TestFullDesignExtractor.cpp

#include <cppunit/config/SourcePrefix.h>
#include "Node.h"
#include "DesignExtractor.h"
#include "TestFullDesignExtractor.h"
#include "CodeParser.h"
#include "PKB.h"
#include "Next.h"

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


void FullDesignExtractorTest::setUp() {
}

void FullDesignExtractorTest::tearDown() {
}

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( FullDesignExtractorTest ); // Note 4 

void FullDesignExtractorTest::testIter2SimpleSource() {
	PKB *pkb;
	Node* ASTRoot;
	CFGNode* CFGRoot;
	Modifies* modifies;
	Uses* uses;
	VarTable* varTable;
	unordered_map<PROCINDEX, vector<CALLSPAIR>> callsTable; 

	pkb = PKB::getInstance();
	CodeParser::parserDriver("TestIter2SIMPLEsource.txt",pkb);
	
	ASTRoot = pkb->getASTRoot();
	CFGRoot = pkb->getCFGRoot();

	if (CFGRoot == NULL && ASTRoot != NULL) {
		cout << "CFGRoot is null and ASTRoot is not null" << endl;
	} 
	if (CFGRoot != NULL) {
		cout << "CFGRoot is NOT NULL!!" << endl;
	} 
	if (ASTRoot == NULL) {
		cout << "ASTRoot is null!!!" << endl;
	}

	// CALLS DE
	DesignExtractor::extractorDriver(pkb);
	// after this, PKB Next, Modifies, Uses and CFGRoot should be filled in
	CFGRoot = pkb->getCFGRoot();

	if (CFGRoot == NULL) {
		cout << "CFGRoot is STILL NULL!!" << endl;
	}

	modifies = pkb->getModifies();
	uses = pkb->getUses();
	vector<int> v;
	varTable = pkb->getVarTable();

	v =	uses->getUses(5);
	string expected = "y x z v t idx ";
	CPPUNIT_ASSERT_EQUAL(expected, printVariables(v, *varTable));
	
	v =	modifies->getModifies(5);
	expected = "y x ";
	CPPUNIT_ASSERT_EQUAL(expected, printVariables(v, *varTable));
	
	v =	uses->getUses(7);
	expected = "y x v ";
	CPPUNIT_ASSERT_EQUAL(expected, printVariables(v, *varTable));
	
	v =	modifies->getModifies(7);
	expected = "y x ";
	CPPUNIT_ASSERT_EQUAL(expected, printVariables(v, *varTable));
	
	v =	uses->getUses(9);
	expected = "y x z v idx ";
	CPPUNIT_ASSERT_EQUAL(expected, printVariables(v, *varTable));
	
	v =	modifies->getModifies(9);
	expected = "y x z t idx ";
	CPPUNIT_ASSERT_EQUAL(expected, printVariables(v, *varTable));
	
	v =	uses->getUses(11);
	expected = "y x z v idx ";
	CPPUNIT_ASSERT_EQUAL(expected, printVariables(v, *varTable));
	
	v =	modifies->getModifies(11);
	expected = "y x z idx ";
	CPPUNIT_ASSERT_EQUAL(expected, printVariables(v, *varTable));
	
	v =	uses->getUses(15);
	expected = "y x v ";
	CPPUNIT_ASSERT_EQUAL(expected, printVariables(v, *varTable));
	
	v =	modifies->getModifies(15);
	expected = "y x ";
	CPPUNIT_ASSERT_EQUAL(expected, printVariables(v, *varTable));
	
	v =	uses->getUses(18);
	expected = "y x z v t idx ";
	CPPUNIT_ASSERT_EQUAL(expected, printVariables(v, *varTable));
	
	v =	modifies->getModifies(18);
	expected = "y x z idx ";
	CPPUNIT_ASSERT_EQUAL(expected, printVariables(v, *varTable));
	
	v =	uses->getUses(19);
	expected = "y x z v t idx ";
	CPPUNIT_ASSERT_EQUAL(expected, printVariables(v, *varTable));
	
	v =	modifies->getModifies(19);
	expected = "y x idx ";
	CPPUNIT_ASSERT_EQUAL(expected, printVariables(v, *varTable));
	
	v =	uses->getUses(21);
	expected = "y x z v t idx ";
	CPPUNIT_ASSERT_EQUAL(expected, printVariables(v, *varTable));
	
	v =	modifies->getModifies(21);
	expected = "y x ";
	CPPUNIT_ASSERT_EQUAL(expected, printVariables(v, *varTable));
	
	v =	uses->getUses(27);
	expected = "y x z v t idx ";
	CPPUNIT_ASSERT_EQUAL(expected, printVariables(v, *varTable));
	
	v =	modifies->getModifies(27);
	expected = "y x ";
	CPPUNIT_ASSERT_EQUAL(expected, printVariables(v, *varTable));

	Next* nextTable; 
	nextTable = pkb->getNext();
	//nextTable->printNextTable();

	expected = "10 18 "; 
	v = nextTable->getNext(9);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));

	expected = "12 14 "; 
	v = nextTable->getNext(11);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "17 "; 
	v = nextTable->getNext(13);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "17 "; 
	v = nextTable->getNext(16);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "9 "; 
	v = nextTable->getNext(17);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = ""; 
	v = nextTable->getNext(18);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "20 23 "; 
	v = nextTable->getNext(19);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "19 "; 
	v = nextTable->getNext(22);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = ""; 
	v = nextTable->getNext(23);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "25 26 "; 
	v = nextTable->getNext(24);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "24 "; 
	v = nextTable->getNext(25);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = ""; 
	v = nextTable->getNext(26);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "28 "; 
	v = nextTable->getNext(27);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "27 "; 
	v = nextTable->getNext(29);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "31 32 "; 
	v = nextTable->getNext(30);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "27 "; 
	v = nextTable->getNext(31);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "27 "; 
	v = nextTable->getNext(32);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	pkb->~PKB();
}

// Given a vector of int, returns a String of the ints
string FullDesignExtractorTest::print(vector<int> v) {
	string s = "";
	for (unsigned int i=0; i<v.size(); i++) {
		int j = v[i];
		std::string str;
		std::stringstream out;
		out << j;
		str = out.str();
		s += ( str + " ");
	}
	return s; 
}

// Given a vector of VARINDEX and the corresponding varTable, returns a String of the VARNAMEs
string FullDesignExtractorTest::printVariables(vector<VARINDEX> v, VarTable varTable) {
	string s = "";
	for (int i=0; i<v.size(); i++) {
		s += varTable.getVarName(v[i]);
		s += " ";
	}
	return s; 
}