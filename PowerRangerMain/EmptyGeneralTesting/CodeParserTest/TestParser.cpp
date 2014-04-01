#include <cppunit/config/SourcePrefix.h>
#include "Node.h"
#include "CodeParser.h"
#include "TestParser.h"

#include <iostream>
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
	VarTable varTable;
	ProcTable procTable;
	Follows follows;
	Parent parent;
	Node* root = parseCode("CodeParserTestIn.txt",varTable,procTable,follows,parent);

	string expected = "i";
	CPPUNIT_ASSERT_EQUAL(expected, varTable.getVarName(0));
	expected = "x";
	CPPUNIT_ASSERT_EQUAL(expected, varTable.getVarName(1));
	expected = "y";
	CPPUNIT_ASSERT_EQUAL(expected, varTable.getVarName(2));
	expected = "z";
	CPPUNIT_ASSERT_EQUAL(expected, varTable.getVarName(3));

	expected = "First";
	CPPUNIT_ASSERT_EQUAL(expected, procTable.getProcName(0));
	expected = "Second";
	CPPUNIT_ASSERT_EQUAL(expected, procTable.getProcName(1));
	expected = "Third";
	CPPUNIT_ASSERT_EQUAL(expected, procTable.getProcName(2));
	return;
}

// method to test the assigning and retrieval of grades
void ParserTest::testCompleteParser()
{
	// create a node
	VarTable varTable;
	ProcTable procTable;
	Follows follows;
	Parent parent;
	Node* root = parseCode("CodeParserTestIn.txt",varTable,procTable,follows,parent);
	// assign
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
	VarTable varTable;
	ProcTable procTable;
	Follows follows;
	Parent parent;
	Node* root = parseCode("Source1.txt",varTable,procTable,follows,parent);

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
	VarTable varTable;
	ProcTable procTable;
	Follows follows;
	Parent parent;
	Node* root = parseCode("Source2.txt",varTable,procTable,follows,parent);

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