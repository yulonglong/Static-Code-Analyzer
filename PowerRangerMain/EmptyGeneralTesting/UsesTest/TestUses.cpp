#include <cppunit/config/SourcePrefix.h>
#include "TestUses.h"

#include <iostream>
#include <string>
using namespace std;

class Parent;
Uses* usesTable; 

void UsesTest::setUp() {
	usesTable = new Uses();
}

void UsesTest::tearDown() {
	usesTable->~Uses(); 
}

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( UsesTest ); // Note 4 

void UsesTest::testUsesUsingStmtNum() {  // Note 5
	usesTable->setUses(2, "x");
	usesTable->setUses(2, "y");
	usesTable->setUses(4, "x");
	usesTable->setUses(5, "z");
	usesTable->setUses(10, "xy");

	CPPUNIT_ASSERT(usesTable->isUses(2, "x") == true);
	CPPUNIT_ASSERT(usesTable->isUses(2, "y") == true);
	CPPUNIT_ASSERT(usesTable->isUses(2, "z") == false);
	CPPUNIT_ASSERT(usesTable->isUses(4, "x") == true);
	CPPUNIT_ASSERT(usesTable->isUses(5, "x") == false);
	CPPUNIT_ASSERT(usesTable->isUses(10, "x") == false);
	return;
}

void UsesTest::testUsesUsingStmtType() {
	usesTable->setUses(2, "x");
	usesTable->setUses(2, "y");
	usesTable->setUses(4, "x");
	usesTable->setUses(5, "z");
	usesTable->setUses(10, "xy");
	usesTable->typeTable.insertStmtNumAndType(2, TypeTable::ASSIGN);
	usesTable->typeTable.insertStmtNumAndType(4, TypeTable::ASSIGN);
	usesTable->typeTable.insertStmtNumAndType(5, TypeTable::IF);
	usesTable->typeTable.insertStmtNumAndType(10, TypeTable::ASSIGN);
	usesTable->typeTable.insertStmtNumAndType(12, TypeTable::ASSIGN);
	
	vector<int> ans (1,2);
	ans.push_back(4);
	CPPUNIT_ASSERT(usesTable->getUses(TypeTable::IF, "z") == vector<int> (1,5) );
	CPPUNIT_ASSERT(usesTable->getUses(TypeTable::WHILE, "y") == vector<int> (1,-1));
	
	return;
}

void UsesTest::testChildrenUsingStmtType() {
	return;
}
