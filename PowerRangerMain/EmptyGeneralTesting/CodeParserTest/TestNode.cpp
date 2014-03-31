#include <cppunit/config/SourcePrefix.h>
#include "Node.h"
#include "TestNode.h"

#include <iostream>
#include <string>
using namespace std;

void 
NodeTest::setUp()
{
}

void 
NodeTest::tearDown()
{
}

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( NodeTest ); // Note 4 

// method to test the constructor
void NodeTest::testConstructor()
{  // Note 5
	Node* node= new Node("y","variable",15);
	string expected = "y";
	CPPUNIT_ASSERT_EQUAL(expected, node->getData());
	expected = "variable";
	CPPUNIT_ASSERT_EQUAL(expected, node->getType());
	Node* expectedNode = NULL;
	CPPUNIT_ASSERT_EQUAL(expectedNode, node->getParent());
	int expectedInt = 15;
	CPPUNIT_ASSERT_EQUAL(expectedInt, node->getProgLine());
	return;
}

// method to test the assigning and retrieval of grades
void NodeTest::testType()
{
	// create a node
	Node* parent = new Node();
	Node* child = new Node();
	// assign
	parent->setType("variable");
	parent->setData("x");
	child->setType("stmtLst");
	child->setParent(parent);
	parent->setChild(child);

	// verify that the assignment is correct - Note 7
	string expected = "variable";
	CPPUNIT_ASSERT_EQUAL(expected, parent->getType());
	expected = "x";
	CPPUNIT_ASSERT_EQUAL(expected, parent->getData());
	expected = "stmtLst";
	CPPUNIT_ASSERT_EQUAL(expected, child->getType());

	Node* expectedNode = parent->getChild()[0];

	expected = "stmtLst";
	CPPUNIT_ASSERT_EQUAL(expected, expectedNode->getType());

	expectedNode = child->getParent();
	expected = "x";
	CPPUNIT_ASSERT_EQUAL(expected, expectedNode->getData());
	expected = "variable";
	CPPUNIT_ASSERT_EQUAL(expected, expectedNode->getType());

	return;
}