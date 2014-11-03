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
	
	set<int> v;
	//pkb->printNextTable();

	string expected = "2 "; 
	v = pkb->getNext(1);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "3 "; 
	v = pkb->getNext(2);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "4 "; 
	v = pkb->getNext(3);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "5 "; 
	v = pkb->getNext(4);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "7 "; 
	v = pkb->getNext(6);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "8 "; 
	v = pkb->getNext(7);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "9 "; 
	v = pkb->getNext(8);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "10 "; 
	v = pkb->getNext(9);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "11 "; 
	v = pkb->getNext(10);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "12 "; 
	v = pkb->getNext(11);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "13 "; 
	v = pkb->getNext(12);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = ""; // returns nothing if not in Next table?
	v = pkb->getNext(13);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "15 "; 
	v = pkb->getNext(14);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "17 "; 
	v = pkb->getNext(16);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "19 "; 
	v = pkb->getNext(18);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "20 "; 
	v = pkb->getNext(19);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
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

	set<int> v;
	//pkb->printNextTable();

	string expected = "2 4 "; 
	v = pkb->getNext(1);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "3 "; 
	v = pkb->getNext(2);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "1 "; 
	v = pkb->getNext(3);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "6 25 "; 
	v = pkb->getNext(5);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));

	expected = "7 23 "; 
	v = pkb->getNext(6);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));

	expected = "8 "; 
	v = pkb->getNext(7);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));

	expected = "9 "; 
	v = pkb->getNext(8);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));

	expected = "10 11 "; 
	v = pkb->getNext(9);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));

	expected = "9 "; 
	v = pkb->getNext(10);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));

	expected = "12 22 "; 
	v = pkb->getNext(11);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));

	expected = "13 "; 
	v = pkb->getNext(12);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));

	expected = "14 21 "; 
	v = pkb->getNext(13);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));

	expected = "15 18 "; 
	v = pkb->getNext(14);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));

	expected = "16 "; 
	v = pkb->getNext(15);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));

	expected = "17 "; 
	v = pkb->getNext(16);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));

	expected = "14 "; 
	v = pkb->getNext(17);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));

	expected = "19 20 "; 
	v = pkb->getNext(18);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));

	expected = "18 "; 
	v = pkb->getNext(19);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));

	expected = "13 "; 
	v = pkb->getNext(20);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));

	expected = "11 "; 
	v = pkb->getNext(21);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));

	expected = "6 "; 
	v = pkb->getNext(22);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));

	expected = "24 "; 
	v = pkb->getNext(23);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));

	expected = "5 "; 
	v = pkb->getNext(24);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));

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
	
	set<int> v;
	//pkb->printNextTable();

	string expected = "2 "; 
	v = pkb->getNext(1);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "3 7 "; 
	v = pkb->getNext(2);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "4 5 "; 
	v = pkb->getNext(3);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "6 "; 
	v = pkb->getNext(4);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "6 "; 
	v = pkb->getNext(5);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "12 "; 
	v = pkb->getNext(6);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "8 "; 
	v = pkb->getNext(7);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "9 10 "; 
	v = pkb->getNext(8);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "11 "; 
	v = pkb->getNext(9);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "11 "; 
	v = pkb->getNext(10);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "12 "; 
	v = pkb->getNext(11);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = ""; 
	v = pkb->getNext(12);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "14 "; 
	v = pkb->getNext(13);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = ""; 
	v = pkb->getNext(14);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));

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
	set<int> v;
	//nextTable->printNextTable();
	
	string expected = "2 "; 
	v = pkb->getNext(1);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "3 "; 
	v = pkb->getNext(2);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "4 "; 
	v = pkb->getNext(3);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "5 7 "; 
	v = pkb->getNext(4);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "6 "; 
	v = pkb->getNext(5);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "9 "; 
	v = pkb->getNext(6);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "8 "; 
	v = pkb->getNext(7);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "9 "; 
	v = pkb->getNext(8);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "10 16 "; 
	v = pkb->getNext(9);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "11 "; 
	v = pkb->getNext(10);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "12 13 "; 
	v = pkb->getNext(11);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "36 "; 
	v = pkb->getNext(12);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "14 15 "; 
	v = pkb->getNext(13);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "36 "; 
	v = pkb->getNext(14);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));

	expected = "36 "; 
	v = pkb->getNext(15);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "17 18 "; 
	v = pkb->getNext(16);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "31 "; 
	v = pkb->getNext(17);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "19 26 "; 
	v = pkb->getNext(18);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "19 26 "; 
	v = pkb->getNext(18);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "20 21 "; 
	v = pkb->getNext(19);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "31 "; 
	v = pkb->getNext(20);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "22 25 "; 
	v = pkb->getNext(21);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "23 24 "; 
	v = pkb->getNext(22);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "31 "; 
	v = pkb->getNext(23);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));

	expected = "31 "; 
	v = pkb->getNext(24);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "31 "; 
	v = pkb->getNext(25);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "27 28 "; 
	v = pkb->getNext(26);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "31 "; 
	v = pkb->getNext(27);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "29 30 "; 
	v = pkb->getNext(28);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "31 "; 
	v = pkb->getNext(29);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "31 "; 
	v = pkb->getNext(30);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "32 "; 
	v = pkb->getNext(31);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "33 34 "; 
	v = pkb->getNext(32);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "35 "; 
	v = pkb->getNext(33);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "35 "; 
	v = pkb->getNext(34);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "36 "; 
	v = pkb->getNext(35);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "37 "; 
	v = pkb->getNext(36);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "38 39 "; 
	v = pkb->getNext(37);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = ""; 
	v = pkb->getNext(38);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = ""; 
	v = pkb->getNext(39);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
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

	set<int> v;
	//pkb->printNextTable();

	string expected = "7 21 "; 
	v = pkb->getNext(6);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));

	expected = "11 17 "; 
	v = pkb->getNext(10);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "14 16 "; 
	v = pkb->getNext(13);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "10 "; 
	v = pkb->getNext(16);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "6 18 "; 
	v = pkb->getNext(17);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "22 "; 
	v = pkb->getNext(21);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "26 29 "; 
	v = pkb->getNext(28);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	expected = "28 "; 
	v = pkb->getNext(30);
	CPPUNIT_ASSERT_EQUAL(expected, print(v));
	
	pkb->~PKB();
}

void BuildCFGTest::testBuildCFGWithNextPairRelationship() {
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
	vector<pair<STMTNUM,STMTNUM>> v;
	//nextTable->printNextTable();
	
	string expected = "";
	
	expected = "[ (38, 38) (39, 39) ]";
	v = pkb->getNextPair(37);
	CPPUNIT_ASSERT(v.size() == 2);
	//CPPUNIT_ASSERT_EQUAL(expected, printVectorOfNextPairs(v));

	v = pkb->getNextPair(38);
	CPPUNIT_ASSERT(v.size() == 0);

	v = pkb->getNextPair(39);
	CPPUNIT_ASSERT(v.size() == 0);

	pkb->~PKB();
}


void BuildCFGTest::testBuildCFGS5() {
	PKB *pkb;
	Node* ASTRoot;
	CFGNode* CFGRoot;

	pkb = PKB::getInstance();
	CodeParser::parserDriver("S5-basicTests.txt",pkb);

	ASTRoot = pkb->getASTRoot();
	CFGRoot = pkb->getCFGRoot();
	if (CFGRoot == NULL && ASTRoot != NULL) {
		cout << "CFGRoot is null and ASTRoot is not null" << endl;
	} else {
		cout << "CFGRoot is NOT NULL!! or ASTRoot is null" << endl;
	}
	DesignExtractor::buildCFGDriver(*pkb, *ASTRoot, *CFGRoot);
	
	set<int> v;
	//pkb->printNextTable();
	
	pkb->~PKB();

}


// Given a set of int, returns a String of the ints
string BuildCFGTest::print(set<int> v) {
	string s = "";
	/*for (unsigned int i=0; i<v.size(); i++) {
		int j = v[i];
		std::string str;
		std::stringstream out;
		out << j;
		str = out.str();
		s += ( str + " ");
	}*/
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

//
//string BuildCFGTest::printVectorOfNextPairs(vector<pair<STMTNUM,STMTNUM>> v) {
//	string s = "[ ";
//	vector<std::pair<int,int>> it;
//	for (it = v.begin(); it != v.end(); ++it) {
//		std::pair<int, int> j = *it; 
//		std::string str;
//		std::stringstream out;
//		out << j.first; 
//		str = out.str();
//		//s += ( "(" + str + ", ");
//		out << j.second; 
//		str = out.str();
//		//s += ( str + " )");
//	}
//	s += " ]"; 
//	return s; 
//}