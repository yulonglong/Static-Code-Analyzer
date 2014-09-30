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

	DesignExtractor::extractorDriver(pkb);
	CFGRoot = pkb->getCFGRoot();

	if (CFGRoot == NULL) {
		cout << "CFGRoot is STILL NULL!!" << endl;
	}













	Next* nextTable; 
	nextTable = pkb->getNext();
	vector<int> v;
	nextTable->printNextTable();

	/*
	string expected = "10 18 "; 
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
	
	expected = "27 "; 
	v = nextTable->getNext(30);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	*/
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
