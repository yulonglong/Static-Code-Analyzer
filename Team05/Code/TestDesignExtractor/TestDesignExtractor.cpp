//@author Ipsita Mohapatra
//TestParser.cpp

#include <cppunit/config/SourcePrefix.h>
#include "Node.h"
#include "DesignExtractor.h"
#include "TestDesignExtractor.h"
#include "CodeParser.h"
#include "PKB.h"

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void DesignExtractorTest::setUp()
{
}

void DesignExtractorTest::tearDown()
{
}

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( DesignExtractorTest ); // Note 4 

void DesignExtractorTest::testExtractRelationshipsModifiesProcedure() {
	PKB *pkb;
	pkb = PKB::getInstance();
	parserDriver("SourceDE1.txt",pkb);

	Node* ASTRoot = pkb->getASTRoot();
	Modifies* modifies = pkb->getModifies();
	Uses* uses = pkb->getUses();
	ProcTable* procTable = pkb->getProcTable();
	VarTable* varTable = pkb->getVarTable();
	
	unordered_map<PROCINDEX, vector<CALLSPAIR>> callsTable; 
	callsTable = pkb->getCallsTable();

	extractRelationships(*ASTRoot, callsTable, *procTable, *modifies, *uses);

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

void DesignExtractorTest::testExtractRelationshipsUsesProcedure() {
	PKB *pkb;
	pkb = PKB::getInstance();
	parserDriver("SourceDE1.txt",pkb);

	Node* ASTRoot = pkb->getASTRoot();
	Modifies* modifies = pkb->getModifies();
	Uses* uses = pkb->getUses();
	ProcTable* procTable = pkb->getProcTable();
	VarTable* varTable = pkb->getVarTable();
	
	unordered_map<PROCINDEX, vector<CALLSPAIR>> callsTable; 
	callsTable = pkb->getCallsTable();

	extractRelationships(*ASTRoot, callsTable, *procTable, *modifies, *uses);

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

void DesignExtractorTest::testExtractRelationshipsModifiesStatement() {
	PKB *pkb;
	pkb = PKB::getInstance();
	parserDriver("SourceDE1.txt",pkb);

	Node* ASTRoot = pkb->getASTRoot();
	Modifies* modifies = pkb->getModifies();
	Uses* uses = pkb->getUses();
	ProcTable* procTable = pkb->getProcTable();
	VarTable* varTable = pkb->getVarTable();
	
	unordered_map<PROCINDEX, vector<CALLSPAIR>> callsTable; 
	callsTable = pkb->getCallsTable();

	extractRelationships(*ASTRoot, callsTable, *procTable, *modifies, *uses);
	
	vector<VARINDEX> v;
	v =	modifies->getModifies(3);
	string expected = "x z y i b d e f ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *varTable));
	v =	modifies->getModifies(5);
	expected = "e f w a ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *varTable));
	v =	modifies->getModifies(6);
	expected = "b d x i ";
	// CPPUNIT_ASSERT_EQUAL(expected, print(v, *varTable));
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
	//CPPUNIT_ASSERT_EQUAL(expected, print(v, *varTable));
	
	v =	modifies->getModifies(23);
	expected = "a ";
	//CPPUNIT_ASSERT_EQUAL(expected, print(v, *varTable));
	
}

void DesignExtractorTest::testExtractRelationshipsUsesStatement() {
	PKB *pkb;
	pkb = PKB::getInstance();
	parserDriver("SourceDE1.txt",pkb);

	Node* ASTRoot = pkb->getASTRoot();
	Modifies* modifies = pkb->getModifies();
	Uses* uses = pkb->getUses();
	ProcTable* procTable = pkb->getProcTable();
	VarTable* varTable = pkb->getVarTable();
	
	unordered_map<PROCINDEX, vector<CALLSPAIR>> callsTable; 
	callsTable = pkb->getCallsTable();

	extractRelationships(*ASTRoot, callsTable, *procTable, *modifies, *uses);
	
	vector<VARINDEX> v;
	v =	uses->getUses(3);
	string expected = "x z y i c g ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *varTable));
	v =	uses->getUses(5);
	expected = "g w ";
	CPPUNIT_ASSERT_EQUAL(expected, print(v, *varTable));
	v =	uses->getUses(6);
	expected = "i x y c  ";
	// CPPUNIT_ASSERT_EQUAL(expected, print(v, *varTable));
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
	// CPPUNIT_ASSERT_EQUAL(expected, print(v, *varTable));
	
	v =	uses->getUses(23);
	expected = "w ";
	//CPPUNIT_ASSERT_EQUAL(expected, print(v, *varTable));
	
}

// Given a vector of VARINDEX and the corresponding varTable, returns a String of the VARNAMEs
string DesignExtractorTest::print(vector<VARINDEX> v, VarTable varTable) {
	string s = "";
	for (int i=0; i<v.size(); i++) {
		s += varTable.getVarName(v[i]);
		s += " ";
	}
	return s; 
}



void DesignExtractorTest::testFullDesignExtractor() {
	PKB *pkb;
	pkb = PKB::getInstance();
	parserDriver("SourceDE.txt",pkb);
	
	extractorDriver(pkb);
}
/*
void DesignExtractorTest::testFullDETestIn()
{  // Note 5

	PKB *pkb;
	pkb = PKB::getInstance();
	parserDriver("CodeParserTestIn.txt",pkb);

	// Node* ASTRoot = pkb->getASTRoot();
	extractorDriver(pkb);
	Node* CFGRoot = pkb->getCFGRoot();
	cout << "Built CFG." << endl;

	string resultFullTree;
	CFGRoot->stringPreOrderExpressionTree(CFGRoot, resultFullTree);
	cout << resultFullTree; 	

	
	ifstream infile;
	// infile.open("expectedSource2.txt",ios::in);
	if(infile.fail()){
		// cout << "expectedSource2.txt does not exist"<< endl;
	}
	else{
		string word;
		string expectedFullTree;
		while(getline(infile,word)){
			expectedFullTree = expectedFullTree + word +"\n";
		}
		string resultFullTree;
		CFGRoot->stringPreOrderExpressionTree(CFGRoot, resultFullTree);
	
		CPPUNIT_ASSERT_EQUAL(expectedFullTree, resultFullTree);
	}
	

	return;
}
*/

/*
void ParserTest::testCompleteParser()
{
	// create a node
	PKB* pkb;
	pkb = PKB::getInstance();
	parserDriver("CodeParserTestIn.txt",pkb);

	
	VarTable* varTable = pkb->getVarTable();
	ProcTable* procTable = pkb->getProcTable();;
	Follows* follows = pkb->getFollows();
	Parent* parent = pkb->getParent();
	TypeTable* typeTable = pkb->getTypeTable();
	Node* root = pkb->getASTRoot();
		
	Node* curr = root;
	curr = root->getChild()[0];
	curr = curr->getChild()[0];
	curr = curr->getChild()[0];

	string expected = "=";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getData());
	expected = "assign";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getType());

	curr = curr->getChild()[0];

	expected = "x";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getData());
	expected = "variable";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getType());
	
	// verify that the assignment is correct - Note 7
	

	return;
}
*/

/*
void ParserTest::testParserSource1()
{
	PKB* pkb;
	pkb = PKB::getInstance();
	parserDriver("Source1.txt",pkb);

	VarTable* varTable = pkb->getVarTable();
	ProcTable* procTable = pkb->getProcTable();;
	Follows* follows = pkb->getFollows();
	Parent* parent = pkb->getParent();
	TypeTable* typeTable = pkb->getTypeTable();
	Node* root = pkb->getASTRoot();

	Node* curr = root;
	
	string expected = "root";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getData());
	expected = "program";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getType());

	curr = curr->getChild()[0];
	expected = "Mini";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getData());
	expected = "procedure";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getType());

	curr = curr->getChild()[0];
    expected = "Mini";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getData());
	expected = "stmtLst";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getType());

	curr = curr->getChild()[0];
    expected = "=";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getData());
	expected = "assign";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getType());

	curr = curr->getChild()[0];
	expected = "A1";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getData());
	expected = "variable";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getType());

    curr = root;

	curr = curr->getChild()[1];
	expected = "mini";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getData());
	expected = "procedure";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getType());

	curr = curr->getChild()[0];
    expected = "mini";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getData());
	expected = "stmtLst";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getType());

	curr = curr->getChild()[1];
    expected = "=";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getData());
	expected = "assign";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getType());

	curr = curr->getChild()[1];
	expected = "A1";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getData());
	expected = "variable";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getType());

	return;
}
*/

/*
void ParserTest::testParserSource2()
{
	PKB* pkb;
	pkb = PKB::getInstance();
	parserDriver("Source2.txt",pkb);

	VarTable* varTable = pkb->getVarTable();
	ProcTable* procTable = pkb->getProcTable();;
	Follows* follows = pkb->getFollows();
	Parent* parent = pkb->getParent();
	TypeTable* typeTable = pkb->getTypeTable();
	Node* root = pkb->getASTRoot();

	Node* curr = root;
	
	string expected = "root";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getData());
	expected = "program";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getType());

	curr = curr->getChild()[0];
	expected = "ABC";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getData());
	expected = "procedure";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getType());

	curr = curr->getChild()[0];
    expected = "ABC";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getData());
	expected = "stmtLst";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getType());

	curr = curr->getChild()[3];
    expected = "4";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getData());
	CPPUNIT_ASSERT_EQUAL(4, curr->getProgLine());
	expected = "while";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getType());

	return;
}
*/


