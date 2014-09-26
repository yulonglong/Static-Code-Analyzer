//@author Ipsita Mohapatra
//TestBuildCFG.cpp

#include <cppunit/config/SourcePrefix.h>
#include "Node.h"
#include "DesignExtractor.h"
#include "TestBuildCFG.h"
#include "CodeParser.h"
#include "PKB.h"
#include "Next.h"

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


void BuildCFGTest::setUp() {
}

void BuildCFGTest::tearDown() {
}

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( BuildCFGTest ); // Note 4 

void BuildCFGTest::testBuildCFGForAssignAndCallStmts() {
	PKB *pkb;
	Node* ASTRoot;
	CFGNode* CFGRoot;

	pkb = PKB::getInstance();
	CodeParser::parserDriver("SourceDE3.txt",pkb);

	ASTRoot = pkb->getASTRoot();
	CFGRoot = pkb->getCFGRoot();
	if (CFGRoot == NULL && ASTRoot != NULL) {
		cout << "CFGRoot is null and ASTRoot is not null" << endl;
	} else {
		cout << "CFGRoot is NOT NULL!! or ASTRoot is null" << endl;
	}
	DesignExtractor::buildCFGDriver(*pkb, *ASTRoot, *CFGRoot);
	
	Next* nextTable; 
	nextTable = pkb->getNext();
	vector<int> v;
	string expected = "1 6 14 16 18 "; 
	v = nextTable->getNext(0);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));

	expected = "2 "; 
	v = nextTable->getNext(1);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "3 "; 
	v = nextTable->getNext(2);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "4 "; 
	v = nextTable->getNext(3);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "5 "; 
	v = nextTable->getNext(4);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "7 "; 
	v = nextTable->getNext(6);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "8 "; 
	v = nextTable->getNext(7);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "9 "; 
	v = nextTable->getNext(8);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "10 "; 
	v = nextTable->getNext(9);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "11 "; 
	v = nextTable->getNext(10);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "12 "; 
	v = nextTable->getNext(11);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "13 "; 
	v = nextTable->getNext(12);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = ""; // returns nothing if not in Next table?
	v = nextTable->getNext(13);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "15 "; 
	v = nextTable->getNext(14);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "17 "; 
	v = nextTable->getNext(16);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "19 "; 
	v = nextTable->getNext(18);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "20 "; 
	v = nextTable->getNext(19);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	//nextTable->printNextTable();

	pkb->~PKB();

}

void BuildCFGTest::testBuildCFGForWhileStmts() {
	PKB *pkb;
	Node* ASTRoot;
	CFGNode* CFGRoot;
	
	pkb = PKB::getInstance();
	CodeParser::parserDriver("SourceDE5.txt",pkb);

	ASTRoot = pkb->getASTRoot();
	CFGRoot = pkb->getCFGRoot();
	if (CFGRoot == NULL && ASTRoot != NULL) {
		cout << "CFGRoot is null and ASTRoot is not null" << endl;
	} else {
		cout << "CFGRoot is NOT NULL!! or ASTRoot is null" << endl;
	}
	DesignExtractor::buildCFGDriver(*pkb, *ASTRoot, *CFGRoot);

	Next* nextTable; 
	nextTable = pkb->getNext();
	vector<int> v;
	string expected = "1 5 "; 
	v = nextTable->getNext(0);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "2 4 "; 
	v = nextTable->getNext(1);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "3 "; 
	v = nextTable->getNext(2);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "1 "; 
	v = nextTable->getNext(3);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "6 25 "; 
	v = nextTable->getNext(5);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));

	expected = "7 23 "; 
	v = nextTable->getNext(6);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));

	expected = "8 "; 
	v = nextTable->getNext(7);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));

	expected = "9 "; 
	v = nextTable->getNext(8);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));

	expected = "10 11 "; 
	v = nextTable->getNext(9);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));

	expected = "9 "; 
	v = nextTable->getNext(10);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));

	expected = "12 22 "; 
	v = nextTable->getNext(11);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));

	expected = "13 "; 
	v = nextTable->getNext(12);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));

	expected = "14 21 "; 
	v = nextTable->getNext(13);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));

	expected = "15 18 "; 
	v = nextTable->getNext(14);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));

	expected = "16 "; 
	v = nextTable->getNext(15);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));

	expected = "17 "; 
	v = nextTable->getNext(16);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));

	expected = "14 "; 
	v = nextTable->getNext(17);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));

	expected = "19 20 "; 
	v = nextTable->getNext(18);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));

	expected = "18 "; 
	v = nextTable->getNext(19);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));

	expected = "13 "; 
	v = nextTable->getNext(20);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));

	expected = "11 "; 
	v = nextTable->getNext(21);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));

	expected = "6 "; 
	v = nextTable->getNext(22);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));

	expected = "24 "; 
	v = nextTable->getNext(23);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));

	expected = "5 "; 
	v = nextTable->getNext(24);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));

	//nextTable->printNextTable();

	pkb->~PKB();

}

void BuildCFGTest::testBuildCFGForIfStmts() {
	PKB *pkb;
	Node* ASTRoot;
	CFGNode* CFGRoot;
	
	pkb = PKB::getInstance();
	CodeParser::parserDriver("SourceDE4.txt",pkb);
	
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

	DesignExtractor::buildCFGDriver(*pkb, *ASTRoot, *CFGRoot);
	CFGRoot = pkb->getCFGRoot();

	if (CFGRoot == NULL) {
		cout << "CFGRoot is STILL NULL!!" << endl;
	}
	
	Next* nextTable; 
	nextTable = pkb->getNext();

	nextTable->printNextTable();

	
	pkb->~PKB();
}

void BuildCFGTest::testBuildCFGForNestedIfStmts() {
	PKB *pkb;
	Node* ASTRoot;
	CFGNode* CFGRoot;
	
	pkb = PKB::getInstance();
	CodeParser::parserDriver("source-if.txt",pkb);
	
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

	DesignExtractor::buildCFGDriver(*pkb, *ASTRoot, *CFGRoot);
	CFGRoot = pkb->getCFGRoot();

	if (CFGRoot == NULL) {
		cout << "CFGRoot is STILL NULL!!" << endl;
	}

	Next* nextTable; 
	nextTable = pkb->getNext();
	
	nextTable->printNextTable();

	pkb->~PKB();
}

void BuildCFGTest::testBuildCFGForNestedWhileStmts() {
	PKB *pkb;
	Node* ASTRoot;
	CFGNode* CFGRoot;
	
	pkb = PKB::getInstance();
	CodeParser::parserDriver("source-while.txt",pkb);
	
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

	DesignExtractor::buildCFGDriver(*pkb, *ASTRoot, *CFGRoot);
	CFGRoot = pkb->getCFGRoot();

	if (CFGRoot == NULL) {
		cout << "CFGRoot is STILL NULL!!" << endl;
	}

	Next* nextTable; 
	nextTable = pkb->getNext();
	vector<int> v;
	string expected = "7 21 "; 
	v = nextTable->getNext(6);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));

	expected = "11 17 "; 
	v = nextTable->getNext(10);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "14 16 "; 
	v = nextTable->getNext(13);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "10 "; 
	v = nextTable->getNext(16);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "18 6 "; 
	v = nextTable->getNext(17);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "22 "; 
	v = nextTable->getNext(21);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "29 26 "; 
	v = nextTable->getNext(28);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "28 "; 
	v = nextTable->getNext(30);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	//nextTable->printNextTable();

	pkb->~PKB();
}

// Given a vector of int, returns a String of the ints
string BuildCFGTest::print(vector<int> v) {
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
