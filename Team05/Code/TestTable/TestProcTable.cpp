#include <cppunit/config/SourcePrefix.h>

#include "TestProcTable.h"

#include <iostream>
#include <string>

ProcTable* procTable;

void ProcTableTest::setUp()
{
	procTable = procTable->getInstance();
}

void ProcTableTest::tearDown()
{
	procTable->~ProcTable();
	procTable = procTable->getInstance();
}

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( ProcTableTest ); // Note 4 

// method to test the assigning and retrieval of grades
void ProcTableTest::testTableSet()
{

	// assign a few grades to this student
	procTable->insertProc("First");
	procTable->insertProc("Second");
	procTable->insertProc("Third");

	// verify that the assignment is correct - Note 7
	CPPUNIT_ASSERT_EQUAL(1, procTable->getProcIndex("First"));
	CPPUNIT_ASSERT_EQUAL(2, procTable->getProcIndex("Second"));
	CPPUNIT_ASSERT_EQUAL(3, procTable->getProcIndex("Third"));

	// attempt to retrieve a course that does not exist
	CPPUNIT_ASSERT_EQUAL(-1, procTable->getProcIndex("Fourth"));

	CPPUNIT_ASSERT("First" == procTable->getProcName(1));
	CPPUNIT_ASSERT("Second" == procTable->getProcName(2));
	CPPUNIT_ASSERT("Third" == procTable->getProcName(3));
	CPPUNIT_ASSERT("" == procTable->getProcName(4));
	CPPUNIT_ASSERT("" == procTable->getProcName(-1));

	CPPUNIT_ASSERT(3 == procTable->getNumProcedures());

	set<int> ans;
	ans.insert(1);
	ans.insert(2);
	ans.insert(3);
	CPPUNIT_ASSERT(ans == procTable->getAllProcIndexes());
	return;
}