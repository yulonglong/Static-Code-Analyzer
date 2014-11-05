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
	procTable = ProcTable::getInstance();
	calls = Calls::getInstance(procTable);
}

void CallsTest::tearDown() {
	pkb->~PKB();
	pkb = PKB::getInstance();
	procTable = ProcTable::getInstance();
	calls = Calls::getInstance(procTable);
}

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( CallsTest ); // Note 4 

void CallsTest::testSetCalls() {  // Note 5
	procTable->insertProc("x");
	procTable->insertProc("y");
	procTable->insertProc("z");

	calls->setCalls("x", "y",2);
	calls->setCalls("x", "z",3);
	calls->setCalls("y", "z",4);

	calls->printCallsTable();
	calls->printCallsPairTable();

	CPPUNIT_ASSERT(calls->isCalls(1, 2) == true);
	CPPUNIT_ASSERT(calls->isCalls(2, 3) == true);
	CPPUNIT_ASSERT(calls->isCalls(3, 2) == false);
	return;
}

void CallsTest::testGetCalls() {  // Note 5
	procTable->insertProc("w");
	procTable->insertProc("x");
	procTable->insertProc("y");
	procTable->insertProc("z");
	
	calls->setCalls("w", "z",11);
	calls->setCalls("x", "y",22);
	calls->setCalls("x", "z",33);
	calls->setCalls("y", "z",44);
	
	cout<<"index of w = "<<procTable->getProcIndex("w")<<endl;
	cout<<"index of x = "<<procTable->getProcIndex("x")<<endl;
	cout<<"index of y = "<<procTable->getProcIndex("y")<<endl;
	cout<<"index of z = "<<procTable->getProcIndex("z")<<endl;
	
	set<PROCINDEX> temp;
	temp.insert(1);
	temp.insert(2);
	temp.insert(3);
	CPPUNIT_ASSERT(calls->getAllCalls() == temp);
	CPPUNIT_ASSERT(calls->getCalls(4) == temp);

	temp.clear();
	temp.insert(3);
	temp.insert(4);
	CPPUNIT_ASSERT(calls->getAllCalled() == temp);
	CPPUNIT_ASSERT(calls->getCalled(2) == temp);
	temp.clear();
	CPPUNIT_ASSERT(calls->getCalls(0) == temp);
	CPPUNIT_ASSERT(calls->getCalls(-1) == temp);
	CPPUNIT_ASSERT(calls->getCalls(10) == temp);
	CPPUNIT_ASSERT(calls->getCalled(10) == temp);
	CPPUNIT_ASSERT(calls->getCalled(-1) == temp);
	CPPUNIT_ASSERT(calls->getCalled(0) == temp);

	temp.clear();
	temp.insert(22);
	temp.insert(33);
	CPPUNIT_ASSERT(calls->getCallStmt(2) == temp);
	temp.clear();
	CPPUNIT_ASSERT(calls->getCallStmt(5) == temp);
	temp.insert(44);
	CPPUNIT_ASSERT(calls->getCallStmt(3) == temp);
	return;
}
