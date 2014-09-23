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

	CPPUNIT_ASSERT(calls->isCalls("x", "y") == true);
	CPPUNIT_ASSERT(calls->isCalls("y", "z") == true);
	CPPUNIT_ASSERT(calls->isCalls("z", "y") == false);
	return;
}

void CallsTest::testGetCalls() {  // Note 5
	procTable->insertProc("w");
	procTable->insertProc("x");
	procTable->insertProc("y");
	procTable->insertProc("z");
	
	calls->setCalls("w", "z",1);
	calls->setCalls("x", "y",2);
	calls->setCalls("x", "z",3);
	calls->setCalls("y", "z",4);
	
	cout<<"index of w = "<<procTable->getProcIndex("w")<<endl;
	cout<<"index of x = "<<procTable->getProcIndex("x")<<endl;
	cout<<"index of y = "<<procTable->getProcIndex("y")<<endl;
	cout<<"index of z = "<<procTable->getProcIndex("z")<<endl;
	
	vector<PROCINDEX> temp;
	temp.push_back(0);
	temp.push_back(1);
	temp.push_back(2);
	CPPUNIT_ASSERT(calls->getCalls() == temp);
	CPPUNIT_ASSERT(calls->getCalls("z") == temp);

	temp.clear();
	temp.push_back(2);
	temp.push_back(3);
	CPPUNIT_ASSERT(calls->getCalled() == temp);
	CPPUNIT_ASSERT(calls->getCalled("x") == temp);
	return;
}
