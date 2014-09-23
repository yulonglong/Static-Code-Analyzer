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
	typeTable = pkb->getTypeTable();
}

void NextTest::tearDown() {
	pkb->~PKB();
	pkb = new PKB();
	next1 = Next::getInstance();
	typeTable = TypeTable::getInstance();
}

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( NextTest ); // Note 4 
