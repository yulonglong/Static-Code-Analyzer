#include <cppunit/config/SourcePrefix.h>
#include "Node.h"
#include "CodeParser.h"
#include "Testintegrate.h"
#include "QueryParser.h"


#include <iostream>
#include <string>
using namespace std;

void 
IntegrateTest::setUp()
{
}

void IntegrateTest::tearDown()
{
}

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( IntegrateTest ); // Note 4 

// method to test the constructor
void IntegrateTest::testModifyTable()
{  // Note 5
	VarTable varTable;
	ProcTable procTable;
	Node* root = parseCode("CodeParserTestIn.txt",varTable,procTable);

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
void IntegrateTest::testCompleteParser()
{
	// create a node
	VarTable varTable;
	ProcTable procTable;
	Node* root = parseCode("CodeParserTestIn.txt",varTable,procTable);
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

void IntegrateTest::testParserSource1()
{
	VarTable varTable;
	ProcTable procTable;
	Node* root = parseCode("Source1.txt",varTable,procTable);

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

void IntegrateTest::testParserSource2()
{
	VarTable varTable;
	ProcTable procTable;
	Node* root = parseCode("Source2.txt",varTable,procTable);

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

 void IntegrateTest::testPQLSource1() {

	string s1 = "assign a; Select a such that Follows(a, 7)";
	string s2 = "assign a; Select a such that Follows(3, a)";
	string s3 = "stmt s; Select s such that Follows(4, s)";
	string s4 = "Select BOOLEAN such that Follows(6, 7)";
	string s5 = "Select BOOLEAN such that Follows(5, 6)";

	string s6 = "while w; Select w such that Follows(3, w)";
	string s7 = "while w; Select w such that Follows(4, w)";
	string s8 = "stmt s; Select s such that Follows(s, 19)";
	string s9 = "Select BOOLEAN such that Follows(15, 16)";
	string s10 = "stmt s; Select s such that Parent(s, 9)";
	string s11 = "while w; Select w such that Parent(w, 11)";
	string s12 = "assign a; Select a such that Parent(a, 3)";
	string s13 = "while w; assign a; Select w such that Parent(w, a)";
	string s14 = "Select BOOLEAN such that Parent(4, 9)";
	string s15 = "while w; Select BOOLEAN such that Parent(4, w)";
	string s16 = "assign a; Select a such that Parent(11, a)";

	// TODO: run query parser;
	QueryParser qp;

	Query q1 = qp.parse(s1);
	Query q2 = qp.parse(s2);
	Query q3 = qp.parse(s3);
	Query q4 = qp.parse(s4);
	Query q5 = qp.parse(s5);
	Query q6 = qp.parse(s6);
	Query q7 = qp.parse(s7);
	Query q8 = qp.parse(s8);
	Query q9 = qp.parse(s9);
	Query q10 = qp.parse(s10);
	Query q11 = qp.parse(s11);
	Query q12 = qp.parse(s12);
	Query q13 = qp.parse(s13);
	Query q14 = qp.parse(s14);
	Query q15 = qp.parse(s15);
	Query q16 = qp.parse(s16);

	// TODO: run evaluate on query

	// TODO: compare result with expected result
 }
