#include <cppunit/config/SourcePrefix.h>

#include "TestVarTable.h"

#include <iostream>
#include <string>

VarTable* varTable;

void VarTableTest::setUp(){
	varTable = varTable->getInstance();
}

void VarTableTest::tearDown(){
	varTable->~VarTable();
	varTable = varTable->getInstance();
}

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( VarTableTest ); // Note 4 

// method to test the assigning and retrieval of grades
void VarTableTest::testTableSet(){

	// assign a few grades to this student
	varTable->insertVar("x");
	varTable->insertVar("y");
	varTable->insertVar("z");

	// verify that the assignment is correct - Note 7
	CPPUNIT_ASSERT_EQUAL(1, varTable->getVarIndex("x"));
	CPPUNIT_ASSERT_EQUAL(2, varTable->getVarIndex("y"));
	CPPUNIT_ASSERT_EQUAL(3, varTable->getVarIndex("z"));

	// attempt to retrieve a course that does not exist
	CPPUNIT_ASSERT_EQUAL(-1, varTable->getVarIndex("a"));

	CPPUNIT_ASSERT("x" == varTable->getVarName(1));
	CPPUNIT_ASSERT("y" == varTable->getVarName(2));
	CPPUNIT_ASSERT("z" == varTable->getVarName(3));
	CPPUNIT_ASSERT("" == varTable->getVarName(4));
	CPPUNIT_ASSERT("" == varTable->getVarName(-1));
	CPPUNIT_ASSERT(3 == varTable->getNumVar());

	set<int> ans;
	ans.insert(1);
	ans.insert(2);
	ans.insert(3);
	CPPUNIT_ASSERT(ans == varTable->getAllVarIndex());
	return;
}