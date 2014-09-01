#include <cppunit/config/SourcePrefix.h>
#include "TestCalls.h"

#include <iostream>
#include <string>
using namespace std;

Calls* calls; 
PKB* pkb;
ProcTable* procTable;

void CallsTest::setUp() {
	pkb = PKB::getInstance();
	calls = pkb->getCalls();
	procTable = pkb->getProcTable();
}

void CallsTest::tearDown() {
	pkb->~PKB();
	pkb = new PKB();
	calls = Calls::getInstance();
	procTable = ProcTable::getInstance();
}

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( CallsTest ); // Note 4 

void CallsTest::testSetCalls() {  // Note 5
	procTable->insertProc("x");
	procTable->insertProc("y");
	procTable->insertProc("z");

	calls->setCalls("x", "y");
	calls->setCalls("x", "z");
	calls->setCalls("y", "z");

	CPPUNIT_ASSERT(calls->isCalled("x", "y") == true);
	CPPUNIT_ASSERT(calls->isCalled("y", "z") == true);
	CPPUNIT_ASSERT(calls->isCalled("z", "y") == false);
	return;
}
