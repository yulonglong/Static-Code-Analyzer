#include <cppunit/config/SourcePrefix.h>

#include "TestVarTable.h"

#include <iostream>
#include <string>

void 
VarTableTest::setUp()
{
}

void 
VarTableTest::tearDown()
{
}

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( VarTableTest ); // Note 4 

// method to test the constructor
void VarTableTest::testConstructor()
{  // Note 5
	// create a student object
	VarTable varTable;
	return;
}

// method to test the assigning and retrieval of grades
void VarTableTest::testTableSet()
{
	// create a student
	VarTable varTable;

	// assign a few grades to this student
	varTable.insertVar("x");
	varTable.insertVar("y");
	varTable.insertVar("z");

	// verify that the assignment is correct - Note 7
	CPPUNIT_ASSERT_EQUAL(0, varTable.getVarIndex("x"));
	CPPUNIT_ASSERT_EQUAL(1, varTable.getVarIndex("y"));
	CPPUNIT_ASSERT_EQUAL(2, varTable.getVarIndex("z"));

	// attempt to retrieve a course that does not exist
	CPPUNIT_ASSERT_EQUAL(-1, varTable.getVarIndex("a"));

	return;
}