//@author Ipsita Mohapatra
//TestFullDesignExtractor.cpp

#include <cppunit/config/SourcePrefix.h>
#include "Node.h"
#include "DesignExtractor.h"
#include "TestFullDesignExtractor.h"
#include "CodeParser.h"
#include "PKB.h"
#include "Next.h"

#include <utility>
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

	set<int> v;

	v =	pkb->getUses(5);
	string expected = "y x z v t idx ";
	CPPUNIT_ASSERT_EQUAL(expected, printVariables(v, *pkb));
	
	v =	pkb->getModifies(5);
	expected = "y x ";
	CPPUNIT_ASSERT_EQUAL(expected, printVariables(v, *pkb));
	
	v =	pkb->getUses(7);
	expected = "y x v ";
	CPPUNIT_ASSERT_EQUAL(expected, printVariables(v, *pkb));
	
	v =	pkb->getModifies(7);
	expected = "y x ";
	CPPUNIT_ASSERT_EQUAL(expected, printVariables(v, *pkb));
	
	v =	pkb->getUses(9);
	expected = "y x z v idx ";
	CPPUNIT_ASSERT_EQUAL(expected, printVariables(v, *pkb));
	
	v =	pkb->getModifies(9);
	expected = "y x z t idx ";
	CPPUNIT_ASSERT_EQUAL(expected, printVariables(v, *pkb));
	
	v =	pkb->getUses(11);
	expected = "y x z v idx ";
	CPPUNIT_ASSERT_EQUAL(expected, printVariables(v, *pkb));
	
	v =	pkb->getModifies(11);
	expected = "y x z idx ";
	CPPUNIT_ASSERT_EQUAL(expected, printVariables(v, *pkb));
	
	v =	pkb->getUses(15);
	expected = "y x v ";
	CPPUNIT_ASSERT_EQUAL(expected, printVariables(v, *pkb));
	
	v =	pkb->getModifies(15);
	expected = "y x ";
	CPPUNIT_ASSERT_EQUAL(expected, printVariables(v, *pkb));
	
	v =	pkb->getUses(18);
	expected = "y x z v t idx ";
	CPPUNIT_ASSERT_EQUAL(expected, printVariables(v, *pkb));
	
	v =	pkb->getModifies(18);
	expected = "y x z idx ";
	CPPUNIT_ASSERT_EQUAL(expected, printVariables(v, *pkb));
	
	v =	pkb->getUses(19);
	expected = "y x z v t idx ";
	CPPUNIT_ASSERT_EQUAL(expected, printVariables(v, *pkb));
	
	v =	pkb->getModifies(19);
	expected = "y x idx ";
	CPPUNIT_ASSERT_EQUAL(expected, printVariables(v, *pkb));
	
	v =	pkb->getUses(21);
	expected = "y x z v t idx ";
	CPPUNIT_ASSERT_EQUAL(expected, printVariables(v, *pkb));
	
	v =	pkb->getModifies(21);
	expected = "y x ";
	CPPUNIT_ASSERT_EQUAL(expected, printVariables(v, *pkb));
	
	v =	pkb->getUses(27);
	expected = "y x z v t idx ";
	CPPUNIT_ASSERT_EQUAL(expected, printVariables(v, *pkb));
	
	v =	pkb->getModifies(27);
	expected = "y x ";
	CPPUNIT_ASSERT_EQUAL(expected, printVariables(v, *pkb));

	//pkb->printNextTable();

	expected = "10 18 "; 
	v = pkb->getNext(9);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));

	expected = "12 14 "; 
	v = pkb->getNext(11);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "17 "; 
	v = pkb->getNext(13);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "17 "; 
	v = pkb->getNext(16);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "9 "; 
	v = pkb->getNext(17);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = ""; 
	v = pkb->getNext(18);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "20 23 "; 
	v = pkb->getNext(19);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "19 "; 
	v = pkb->getNext(22);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = ""; 
	v = pkb->getNext(23);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "25 26 "; 
	v = pkb->getNext(24);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "24 "; 
	v = pkb->getNext(25);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = ""; 
	v = pkb->getNext(26);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "28 "; 
	v = pkb->getNext(27);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "27 "; 
	v = pkb->getNext(29);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "31 32 "; 
	v = pkb->getNext(30);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "27 "; 
	v = pkb->getNext(31);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "27 "; 
	v = pkb->getNext(32);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	pkb->~PKB();
}

// Given a set of int, returns a String of the ints
string FullDesignExtractorTest::print(set<int> v) {
	string s = "";
	set<int>::iterator it;
	for (it = v.begin(); it != v.end(); ++it) {
		int j = *it; 
		std::string str;
		std::stringstream out;
		out << j; 
		str = out.str();
		s += ( str + " ");
	}
	return s; 
}

// Given a set of VARINDEX and the corresponding varTable, returns a String of the VARNAMEs
string FullDesignExtractorTest::printVariables(set<VARINDEX> v, PKB &pkb) {
	string s = "";
	set<int>::iterator it;
	for (it = v.begin(); it != v.end(); ++it) {
		s += pkb.getVarName(*it);
		s += " ";
	}
	return s; 
}