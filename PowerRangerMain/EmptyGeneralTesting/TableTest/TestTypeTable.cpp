#include <cppunit/config/SourcePrefix.h>
#include "TypeTable.h"
#include "TestTypeTable.h"

#include <iostream>
#include <string>

void 
TypeTableTest::setUp()
{
}

void 
TypeTableTest::tearDown()
{
}

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( TypeTableTest ); // Note 4 

// method to test the constructor
void TypeTableTest::testConstructor()
{  // Note 5
	// create a student object
	TypeTable typeTable;
	return;
}

// method to test the assigning and retrieval of grades
void TypeTableTest::testTableSet()
{
	// create a student
	TypeTable typeTable;

	// assign a few grades to this student
	typeTable.insertStmtNumAndType(0,"while");
	typeTable.insertStmtNumAndType(4,"if");
	typeTable.insertStmtNumAndType(15,"while");
	typeTable.insertStmtNumAndType(21,"assign");


	LIST expected;
	LIST result;
	expected.push_back(4);
	result = typeTable.getStmtNum("if");
	// verify that the assignment is correct - Note 7
	CPPUNIT_ASSERT_EQUAL(expected[0], result[0]);

	expected.clear();
	result.clear();
	expected.push_back(0);
	expected.push_back(15);
	result = typeTable.getStmtNum("while");
	CPPUNIT_ASSERT_EQUAL(expected[0], result[0]);
	CPPUNIT_ASSERT_EQUAL(expected[1], result[1]);

	expected.clear();
	result.clear();
	expected.push_back(21);
	result = typeTable.getStmtNum("assign");
	CPPUNIT_ASSERT_EQUAL(expected[0],result[0]);

	SType expectedType;
	expectedType = "while";
	CPPUNIT_ASSERT_EQUAL(expectedType, typeTable.getType(0));
	expectedType = "if";
	CPPUNIT_ASSERT_EQUAL(expectedType, typeTable.getType(4));
	expectedType = "while";
	CPPUNIT_ASSERT_EQUAL(expectedType, typeTable.getType(15));
	expectedType = "assign";
	CPPUNIT_ASSERT_EQUAL(expectedType, typeTable.getType(21));

	// attempt to retrieve a course that does not exist
	expected.clear();
	result.clear();
	result =  typeTable.getStmtNum("call");
	CPPUNIT_ASSERT_EQUAL(expected.size(),result.size());

	return;
}