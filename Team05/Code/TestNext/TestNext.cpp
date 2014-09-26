#include <cppunit/config/SourcePrefix.h>
#include "TestNext.h"

#include <iostream>
#include <string>

Next* next1;
PKB* pkb;
TypeTable* typeTable;

void NextTest::setUp() {
	pkb = PKB::getInstance();
	next1 = pkb->getNext();
	typeTable = TypeTable::getInstance();
	next1 = Next::getInstance(typeTable);
}

void NextTest::tearDown() {
	pkb->~PKB();
	pkb = new PKB();
	typeTable = TypeTable::getInstance();
	next1 = Next::getInstance(typeTable);
}

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( NextTest ); // Note 4 

void NextTest::testSetAndGetNext() {
	next1->setNext(1,2);
	next1->setNext(1,3);
	next1->setNext(1,4);
	next1->setNext(4,5);

	next1->printNextTable();
	next1->printNextTableForTesting();

	vector<STMTNUM> ans (1,2);
	ans.push_back(3);
	ans.push_back(4);

	CPPUNIT_ASSERT(next1->getNext(1) == ans);
	ans.clear();
	ans.push_back(5);
	CPPUNIT_ASSERT(next1->getNext(4) == ans);
	ans.clear();
	CPPUNIT_ASSERT(next1->getNext(999) == ans);
	CPPUNIT_ASSERT(next1->getNext(5) == ans);

	CPPUNIT_ASSERT(next1->getPrevious(3) == 1);
	CPPUNIT_ASSERT(next1->getPrevious(5) == 4);

	CPPUNIT_ASSERT(next1->getPrevious(1) == -1);
	CPPUNIT_ASSERT(next1->getPrevious(999) == -1);
	return;
}