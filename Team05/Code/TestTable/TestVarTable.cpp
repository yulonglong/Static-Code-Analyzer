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

	CPPUNIT_ASSERT("x" == varTable.getVarName(0));
	CPPUNIT_ASSERT("y" == varTable.getVarName(1));
	CPPUNIT_ASSERT("z" == varTable.getVarName(2));
	CPPUNIT_ASSERT("" == varTable.getVarName(3));
	CPPUNIT_ASSERT("" == varTable.getVarName(-1));

	CPPUNIT_ASSERT(3 == varTable.getNumVar());

	vector<int> ans;
	ans.emplace_back(0);
	ans.emplace_back(1);
	ans.emplace_back(2);
	CPPUNIT_ASSERT(ans == varTable.getAllVarIndex());
	return;
}