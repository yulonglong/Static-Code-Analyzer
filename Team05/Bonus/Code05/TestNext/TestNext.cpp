#include <cppunit/config/SourcePrefix.h>
#include "TestNext.h"

#include <iostream>
#include <string>

Next* next1;
PKB* pkb;
TypeTable* typeTable;

void NextTest::setUp() {
	pkb = PKB::getInstance();
	next1 = Next::getInstance();
}

void NextTest::tearDown() {
	pkb->~PKB();
	pkb = new PKB();
	next1 = Next::getInstance();
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

	
	next1->setNextPair(1,make_pair(2,3));
	next1->setNextPair(1,make_pair(4,5));
	next1->setNextPair(5,make_pair(6,0));
	next1->setNextPair(7,make_pair(8,11));

	next1->printNextPairTableForTesting();

	set<STMTNUM> ans;
	ans.insert(2);
	ans.insert(3);
	ans.insert(4);

	CPPUNIT_ASSERT(next1->getNext(1) == ans);
	ans.clear();
	ans.insert(5);
	CPPUNIT_ASSERT(next1->getNext(4) == ans);
	ans.clear();
	CPPUNIT_ASSERT(next1->getNext(999) == ans);
	CPPUNIT_ASSERT(next1->getNext(5) == ans);
	ans.clear();
	ans.insert(1);
	CPPUNIT_ASSERT(next1->getPrevious(3) == ans);
	ans.clear();
	ans.insert(4);
	CPPUNIT_ASSERT(next1->getPrevious(5) == ans);
	ans.clear();
	CPPUNIT_ASSERT(next1->getPrevious(1) == ans);
	CPPUNIT_ASSERT(next1->getPrevious(999) == ans);

	ans.clear();
	ans.insert(1);
	ans.insert(4);
	CPPUNIT_ASSERT(next1->getAllNext() == ans);
	ans.clear();
	ans.insert(2);
	ans.insert(3);
	ans.insert(4);
	ans.insert(5);
	CPPUNIT_ASSERT(next1->getAllPrevious() == ans);

	vector<pair<STMTNUM,STMTNUM>> ans2;
	pair<STMTNUM,STMTNUM> p1 = make_pair(2,3);
	pair<STMTNUM,STMTNUM> p2 = make_pair(4,5);
	ans2.push_back(p1);
	ans2.push_back(p2);

	CPPUNIT_ASSERT(next1->getNextPair(1) == ans2);
	ans2.clear();
	p1 = make_pair(6,0);
	ans2.push_back(p1);
	CPPUNIT_ASSERT(next1->getNextPair(5) == ans2);
	ans2.clear();
	CPPUNIT_ASSERT(next1->getNextPair(-1) == ans2);
	CPPUNIT_ASSERT(next1->getNextPair(100) == ans2);
	return;
}