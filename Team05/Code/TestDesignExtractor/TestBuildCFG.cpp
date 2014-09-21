//@author Ipsita Mohapatra
//TestBuildCFG.cpp

#include <cppunit/config/SourcePrefix.h>
#include "Node.h"
#include "DesignExtractor.h"
#include "TestBuildCFG.h"
#include "CodeParser.h"
#include "PKB.h"

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
	Node* CFGRoot;
	
	pkb = PKB::getInstance();
	parserDriver("SourceDE3.txt",pkb);

	ASTRoot = pkb->getASTRoot();
	CFGRoot = pkb->getCFGRoot();
	if (CFGRoot == NULL && ASTRoot != NULL) {
		cout << "CFGRoot is null and ASTRoot is not null" << endl;
	} else {
		cout << "CFGRoot is NOT NULL!! or ASTRoot is null" << endl;
	}
	buildCFGDriver(*pkb, *ASTRoot, *CFGRoot);
	
	/*
	CFGNode* node = getCFGNode(12);
	if (node != NULL) {
		cout << "FOUND LINE NUMBER: " << node->getProgLine() << endl;
	} else {
		cout << "NOT FOUND" << endl;
	}
	*/

	/*
	string resultFullCFG = "";
	CFGRoot->stringPreOrderExpressionGraph(CFGRoot, resultFullCFG);
	string expectedFullCFG = "";
	cout << resultFullCFG << endl;
	cout << "End of CFG" << endl;
	*/

	// CPPUNIT_ASSERT_EQUAL(expectedFullCFG, resultFullCFG);
	pkb->~PKB();

}

void BuildCFGTest::testBuildCFGForWhileStmts() {
	PKB *pkb;
	Node* ASTRoot;
	Node* CFGRoot;
	
	pkb = PKB::getInstance();
	parserDriver("SourceDE2.txt",pkb);

	ASTRoot = pkb->getASTRoot();
	CFGRoot = pkb->getCFGRoot();
	if (CFGRoot == NULL && ASTRoot != NULL) {
		cout << "CFGRoot is null and ASTRoot is not null" << endl;
	} else {
		cout << "CFGRoot is NOT NULL!! or ASTRoot is null" << endl;
	}
	buildCFGDriver(*pkb, *ASTRoot, *CFGRoot);
	
	/*
	string resultFullCFG = "";
	CFGRoot->stringPreOrderExpressionGraph(CFGRoot, resultFullCFG);
	string expectedFullCFG = "";
	cout << resultFullCFG << endl;
	cout << "End of CFG" << endl;
	*/

	// CPPUNIT_ASSERT_EQUAL(expectedFullCFG, resultFullCFG);
	pkb->~PKB();

}