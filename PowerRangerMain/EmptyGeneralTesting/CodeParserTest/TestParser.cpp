#include <cppunit/config/SourcePrefix.h>
#include "Node.h"
#include "CodeParser.h"
#include "TestParser.h"

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void 
ParserTest::setUp()
{
}

void 
ParserTest::tearDown()
{
}

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( ParserTest ); // Note 4 

// method to test the constructor
void ParserTest::testModifyTable()
{  // Note 5
	
	PKB pkb;
	parserDriver("CodeParserTestIn.txt",pkb);

	VarTable varTable = pkb.getVarTable();
	ProcTable procTable = pkb.getProcTable();;
	Follows follows = pkb.getFollows();
	Parent parent = pkb.getParent();
	TypeTable typeTable = pkb.getTypeTable();
	Modifies modifies = pkb.getModifies();
	Uses uses = pkb.getUses();
	Node* root = pkb.getASTRoot();

	string expected = "x";
	CPPUNIT_ASSERT_EQUAL(expected, varTable.getVarName(0));
	expected = "z";
	CPPUNIT_ASSERT_EQUAL(expected, varTable.getVarName(1));
	expected = "i";
	CPPUNIT_ASSERT_EQUAL(expected, varTable.getVarName(2));
	expected = "y";
	CPPUNIT_ASSERT_EQUAL(expected, varTable.getVarName(3));
	expected = "v";
	CPPUNIT_ASSERT_EQUAL(expected, varTable.getVarName(4));

	expected = "First";
	CPPUNIT_ASSERT_EQUAL(expected, procTable.getProcName(0));
	expected = "Second";
	CPPUNIT_ASSERT_EQUAL(expected, procTable.getProcName(1));
	expected = "Third";
	CPPUNIT_ASSERT_EQUAL(expected, procTable.getProcName(2));

	CPPUNIT_ASSERT_EQUAL(false,parent.isParent(1,2));
	CPPUNIT_ASSERT_EQUAL(false,parent.isParent(3,2));
	CPPUNIT_ASSERT_EQUAL(true,parent.isParent(6,7));
	CPPUNIT_ASSERT_EQUAL(true,parent.isParent(6,8));
	CPPUNIT_ASSERT_EQUAL(true,parent.isParent(6,9));
	CPPUNIT_ASSERT_EQUAL(true,parent.isParent(10,11));
	CPPUNIT_ASSERT_EQUAL(true,parent.isParent(10,12));
	CPPUNIT_ASSERT_EQUAL(false,parent.isParent(11,12));

	CPPUNIT_ASSERT_EQUAL(true,follows.isFollows(1,2));
	CPPUNIT_ASSERT_EQUAL(true,follows.isFollows(2,3));
	CPPUNIT_ASSERT_EQUAL(false,follows.isFollows(1,3));
	CPPUNIT_ASSERT_EQUAL(true,follows.isFollows(4,5));
	CPPUNIT_ASSERT_EQUAL(true,follows.isFollows(5,6));
	CPPUNIT_ASSERT_EQUAL(false,follows.isFollows(6,7));

	CPPUNIT_ASSERT_EQUAL(TypeTable::ASSIGN,typeTable.getType(1));
	CPPUNIT_ASSERT_EQUAL(TypeTable::ASSIGN,typeTable.getType(2));
	CPPUNIT_ASSERT_EQUAL(TypeTable::CALL,typeTable.getType(3));
	CPPUNIT_ASSERT_EQUAL(TypeTable::WHILE,typeTable.getType(6));
	CPPUNIT_ASSERT_EQUAL(TypeTable::CALL,typeTable.getType(8));
	CPPUNIT_ASSERT_EQUAL(TypeTable::IF,typeTable.getType(10));
	CPPUNIT_ASSERT_EQUAL(TypeTable::ASSIGN,typeTable.getType(11));

	/*
	CPPUNIT_ASSERT_EQUAL(false,modifies.isModifies(2,"x"));
	CPPUNIT_ASSERT_EQUAL(false,modifies.isModifies(3,"x"));
	CPPUNIT_ASSERT_EQUAL(true,modifies.isModifies(1,"x"));
	CPPUNIT_ASSERT_EQUAL(true,modifies.isModifies(4,"x"));
	CPPUNIT_ASSERT_EQUAL(true,modifies.isModifies(5,"i"));
	CPPUNIT_ASSERT_EQUAL(true,modifies.isModifies(13,"z"));
	CPPUNIT_ASSERT_EQUAL(true,modifies.isModifies(16,"z"));
	CPPUNIT_ASSERT_EQUAL(false,modifies.isModifies(21,"v"));
	*/
	
	/*
	CPPUNIT_ASSERT_EQUAL(false,uses.isUses(1,"x"));
	CPPUNIT_ASSERT_EQUAL(true,uses.isUses(6,"i"));
	CPPUNIT_ASSERT_EQUAL(true,uses.isUses(7,"x"));
	CPPUNIT_ASSERT_EQUAL(true,uses.isUses(7,"y"));
	CPPUNIT_ASSERT_EQUAL(true,uses.isUses(1,"z"));
	CPPUNIT_ASSERT_EQUAL(true,uses.isUses(2,"y"));
	*/
	return;
}

// method to test the assigning and retrieval of grades
void ParserTest::testCompleteParser()
{
	// create a node
	PKB pkb;
	parserDriver("CodeParserTestIn.txt",pkb);

	VarTable varTable = pkb.getVarTable();
	ProcTable procTable = pkb.getProcTable();;
	Follows follows = pkb.getFollows();
	Parent parent = pkb.getParent();
	TypeTable typeTable = pkb.getTypeTable();
	Node* root = pkb.getASTRoot();

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

void ParserTest::testParserSource1()
{
	PKB pkb;
	parserDriver("Source1.txt",pkb);

	VarTable varTable = pkb.getVarTable();
	ProcTable procTable = pkb.getProcTable();;
	Follows follows = pkb.getFollows();
	Parent parent = pkb.getParent();
	TypeTable typeTable = pkb.getTypeTable();
	Node* root = pkb.getASTRoot();

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

void ParserTest::testParserSource2()
{
	PKB pkb;
	parserDriver("Source2.txt",pkb);

	VarTable varTable = pkb.getVarTable();
	ProcTable procTable = pkb.getProcTable();;
	Follows follows = pkb.getFollows();
	Parent parent = pkb.getParent();
	TypeTable typeTable = pkb.getTypeTable();
	Node* root = pkb.getASTRoot();

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


void ParserTest::testFullParserOwnSource()
{
	// create a node
	PKB pkb;
	parserDriver("CodeParserTestIn.txt",pkb);

	VarTable varTable = pkb.getVarTable();
	ProcTable procTable = pkb.getProcTable();;
	Follows follows = pkb.getFollows();
	Parent parent = pkb.getParent();
	TypeTable typeTable = pkb.getTypeTable();
	Node* root = pkb.getASTRoot();

	ifstream infile;
	infile.open("expectedCodeParserTestIn.txt",ios::in);
	if(infile.fail()){
		cout << "expectedCodeParserTestIn.txt does not exists"<< endl;
	}
	else{
		string word;
		string expectedFullTree;
		while(getline(infile,word)){
			expectedFullTree = expectedFullTree + word +"\n";
		}
		string resultFullTree;
		root->stringPreOrderExpressionTree(root, resultFullTree);

		CPPUNIT_ASSERT_EQUAL(expectedFullTree, resultFullTree);
	}
}


void ParserTest::testFullParserSource1()
{
	// create a node
	PKB pkb;
	parserDriver("Source1.txt",pkb);

	VarTable varTable = pkb.getVarTable();
	ProcTable procTable = pkb.getProcTable();;
	Follows follows = pkb.getFollows();
	Parent parent = pkb.getParent();
	TypeTable typeTable = pkb.getTypeTable();
	Node* root = pkb.getASTRoot();

	ifstream infile;
	infile.open("expectedSource1.txt",ios::in);
	if(infile.fail()){
		cout << "expectedSource1.txt does not exists"<< endl;
	}
	else{
		string word;
		string expectedFullTree;
		while(getline(infile,word)){
			expectedFullTree = expectedFullTree + word +"\n";
		}
		string resultFullTree;
		root->stringPreOrderExpressionTree(root, resultFullTree);

		CPPUNIT_ASSERT_EQUAL(expectedFullTree, resultFullTree);
	}
}


void ParserTest::testFullParserSource2()
{
	PKB pkb;
	parserDriver("Source2.txt",pkb);

	VarTable varTable = pkb.getVarTable();
	ProcTable procTable = pkb.getProcTable();;
	Follows follows = pkb.getFollows();
	Parent parent = pkb.getParent();
	TypeTable typeTable = pkb.getTypeTable();
	Node* root = pkb.getASTRoot();

		ifstream infile;
	infile.open("expectedSource2.txt",ios::in);
	if(infile.fail()){
		cout << "expectedSource2.txt does not exists"<< endl;
	}
	else{
		string word;
		string expectedFullTree;
		while(getline(infile,word)){
			expectedFullTree = expectedFullTree + word +"\n";
		}
		string resultFullTree;
		root->stringPreOrderExpressionTree(root, resultFullTree);

		CPPUNIT_ASSERT_EQUAL(expectedFullTree, resultFullTree);
	}
}

void ParserTest::testFullParserSource2messy()
{
	PKB pkb;
	parserDriver("Source2messy.txt",pkb);

	VarTable varTable = pkb.getVarTable();
	ProcTable procTable = pkb.getProcTable();;
	Follows follows = pkb.getFollows();
	Parent parent = pkb.getParent();
	TypeTable typeTable = pkb.getTypeTable();
	Node* root = pkb.getASTRoot();

		ifstream infile;
	infile.open("expectedSource2.txt",ios::in);
	if(infile.fail()){
		cout << "expectedSource2.txt does not exists"<< endl;
	}
	else{
		string word;
		string expectedFullTree;
		while(getline(infile,word)){
			expectedFullTree = expectedFullTree + word +"\n";
		}
		string resultFullTree;
		root->stringPreOrderExpressionTree(root, resultFullTree);
	
		CPPUNIT_ASSERT_EQUAL(expectedFullTree, resultFullTree);

	
	}
}