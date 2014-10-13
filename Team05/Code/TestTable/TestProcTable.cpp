#include <cppunit/config/SourcePrefix.h>

#include "TestProcTable.h"

#include <iostream>
#include <string>

void 
ProcTableTest::setUp()
{
}

void 
ProcTableTest::tearDown()
{
}

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( ProcTableTest ); // Note 4 

// method to test the constructor
void ProcTableTest::testConstructor()
{  // Note 5
	// create a student object
	ProcTable procTable;
	return;
}

// method to test the assigning and retrieval of grades
void ProcTableTest::testTableSet()
{
	// create a student
	ProcTable procTable;

	// assign a few grades to this student
	procTable.insertProc("First");
	procTable.insertProc("Second");
	procTable.insertProc("Third");

	// verify that the assignment is correct - Note 7
	CPPUNIT_ASSERT_EQUAL(0, procTable.getProcIndex("First"));
	CPPUNIT_ASSERT_EQUAL(1, procTable.getProcIndex("Second"));
	CPPUNIT_ASSERT_EQUAL(2, procTable.getProcIndex("Third"));

	// attempt to retrieve a course that does not exist
	CPPUNIT_ASSERT_EQUAL(-1, procTable.getProcIndex("Fourth"));

	CPPUNIT_ASSERT("First" == procTable.getProcName(0));
	CPPUNIT_ASSERT("Second" == procTable.getProcName(1));
	CPPUNIT_ASSERT("Third" == procTable.getProcName(2));
	CPPUNIT_ASSERT("" == procTable.getProcName(3));
	CPPUNIT_ASSERT("" == procTable.getProcName(-1));

	CPPUNIT_ASSERT(3 == procTable.getNumProcedures());

	vector<int> ans;
	ans.emplace_back(0);
	ans.emplace_back(1);
	ans.emplace_back(2);
	CPPUNIT_ASSERT(ans == procTable.getAllProcIndexes());
	return;
}