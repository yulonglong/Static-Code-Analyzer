//@author Ipsita Mohapatra
//TestExtractSibling.cpp

#include <cppunit/config/SourcePrefix.h>
#include "Node.h"
#include "DesignExtractor.h"
#include "TestExtractSibling.h"
#include "CodeParser.h"
#include "PKB.h"

#include <utility>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


void ExtractSiblingTest::setUp() {
}

void ExtractSiblingTest::tearDown() {
}

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( ExtractSiblingTest ); // Note 4 

void ExtractSiblingTest::testSource1B() {
	PKB *pkb;
	Node* ASTRoot;
	
	pkb = PKB::getInstance();
	CodeParser::parserDriver("Source1B.txt",pkb);
	
	ASTRoot = pkb->getASTRoot();
	if (ASTRoot == NULL) {
		cout << "ASTRoot is null!!!" << endl;
	}

	// CALLS DE
	DesignExtractor::extractSiblingRelationshipDriver(*ASTRoot, *pkb);
	


	pkb->~PKB();	
}
