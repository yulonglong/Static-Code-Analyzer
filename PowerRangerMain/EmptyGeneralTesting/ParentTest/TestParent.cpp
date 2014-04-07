#include <cppunit/config/SourcePrefix.h>
#include "TestParent.h"

#include <iostream>
#include <string>
using namespace std;

class Parent;
TypeTable *typeTable;
Parent *parent; 
PKB *pkb;

void ParentTest::setUp() {
	pkb = PKB::getInstance();
	parent = Parent::getInstance();
	typeTable = TypeTable::getInstance();
}

void ParentTest::tearDown() {
	/*parent->~Parent(); */
}

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( ParentTest ); // Note 4 

void ParentTest::testParentUsingStmtNum() {  // Note 5
	parent->setParent(6, 7);
	parent->setParent(6, 8);
	parent->setParent(6, 9);
	parent->setParent(10, 11);
	parent->setParent(10, 12);

	CPPUNIT_ASSERT(parent->isParent(6, 7) == true);
	CPPUNIT_ASSERT(parent->isParent(10, 11) == true);
	CPPUNIT_ASSERT(parent->isParent(5, 6) == false);
	CPPUNIT_ASSERT(parent->isParent(6, 10) == false);
	return;
}

void ParentTest::testParentUsingStmtType() {
	/*parentTable->setParent(6, 7);
	parentTable->setParent(6, 8);
	parentTable->setParent(6, 9);
	parentTable->setParent(10, 11);
	parentTable->setParent(10, 12);
	typeTable->insertStmtNumAndType(6, TypeTable::WHILE);
	typeTable->insertStmtNumAndType(7, TypeTable::ASSIGN);
	typeTable->insertStmtNumAndType(8, TypeTable::CALL);
	typeTable->insertStmtNumAndType(9, TypeTable::ASSIGN);
	typeTable->insertStmtNumAndType(10, TypeTable::IF);
	typeTable->insertStmtNumAndType(11, TypeTable::ASSIGN);
	typeTable->insertStmtNumAndType(12, TypeTable::ASSIGN);
	
	CPPUNIT_ASSERT(parentTable->isParent(TypeTable::WHILE, 9) == true);
	CPPUNIT_ASSERT(parentTable->isParent(TypeTable::IF, 12) == true);
	CPPUNIT_ASSERT(parentTable->isParent(TypeTable::WHILE, 5) == false);*/
	
	return;
}

void ParentTest::testChildrenUsingStmtType() {
	return;
}
