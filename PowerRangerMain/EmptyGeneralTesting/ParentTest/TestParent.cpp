#include <cppunit/config/SourcePrefix.h>
#include "TestParent.h"

#include <iostream>
#include <string>
using namespace std;

class Parent;
Parent* parentTable; 

void ParentTest::setUp() {
	parentTable = new Parent();
}

void ParentTest::tearDown() {
	parentTable->~Parent(); 
}

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( ParentTest ); // Note 4 

void ParentTest::testParentUsingStmtNum() {  // Note 5
	parentTable->setParent(6, 7);
	parentTable->setParent(6, 8);
	parentTable->setParent(6, 9);
	parentTable->setParent(10, 11);
	parentTable->setParent(10, 12);

	CPPUNIT_ASSERT(parentTable->isParent(6, 7) == true);
	CPPUNIT_ASSERT(parentTable->isParent(10, 11) == true);
	CPPUNIT_ASSERT(parentTable->isParent(5, 6) == false);
	CPPUNIT_ASSERT(parentTable->isParent(6, 10) == false);
	return;
}

void ParentTest::testParentUsingStmtType() {
	parentTable->setParent(6, 7);
	parentTable->setParent(6, 8);
	parentTable->setParent(6, 9);
	parentTable->setParent(10, 11);
	parentTable->setParent(10, 12);
	parentTable->table.insertStmtNumAndType(6, WHILE);
	parentTable->table.insertStmtNumAndType(7, ASSIGN);
	parentTable->table.insertStmtNumAndType(8, CALL);
	parentTable->table.insertStmtNumAndType(9, ASSIGN);
	parentTable->table.insertStmtNumAndType(10, IF);
	parentTable->table.insertStmtNumAndType(11, ASSIGN);
	parentTable->table.insertStmtNumAndType(12, ASSIGN);
	
	CPPUNIT_ASSERT(parentTable->isParent(WHILE, 9) == true);
	// CPPUNIT_ASSERT(parentTable->isParent(10, 11) == true);
	// CPPUNIT_ASSERT(parentTable->isParent(5, 6) == false);
	// CPPUNIT_ASSERT(parentTable->isParent(6, 10) == false);
	

	return;
}

void ParentTest::testChildrenUsingStmtType() {
	return;
}
