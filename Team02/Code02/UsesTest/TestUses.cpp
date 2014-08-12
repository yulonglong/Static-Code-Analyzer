#include <cppunit/config/SourcePrefix.h>
#include "TestUses.h"

#include <iostream>
#include <string>
using namespace std;

Uses* uses; 
PKB* pkb;
TypeTable* typeTable;
VarTable* varTable;

void UsesTest::setUp() {
	pkb = PKB::getInstance();
	uses = pkb->getUses();
	typeTable = pkb->getTypeTable();
	varTable = pkb->getVarTable();
}

void UsesTest::tearDown() {
	pkb->~PKB();
	pkb = new PKB();
	uses = Uses::getInstance();
	typeTable = TypeTable::getInstance();
	varTable = VarTable::getInstance();
}

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( UsesTest ); // Note 4 

void UsesTest::testUsesUsingStmtNum() {  // Note 5
	varTable->insertVar("x");
	varTable->insertVar("y");
	varTable->insertVar("z");
	varTable->insertVar("xy");

	uses->setUses(2, "x");
	uses->setUses(2, "y");
	uses->setUses(4, "x");
	uses->setUses(5, "z");
	uses->setUses(10, "xy");

	CPPUNIT_ASSERT(uses->isUses(2, "x") == true);
	CPPUNIT_ASSERT(uses->isUses(2, "y") == true);
	CPPUNIT_ASSERT(uses->isUses(2, "z") == false);
	CPPUNIT_ASSERT(uses->isUses(4, "x") == true);
	CPPUNIT_ASSERT(uses->isUses(5, "x") == false);
	CPPUNIT_ASSERT(uses->isUses(10, "x") == false);
	CPPUNIT_ASSERT(uses->isUses(111, "ashfwnelw") == false);
	CPPUNIT_ASSERT(uses->isUses(-150, "ashfwnelw") == false);
	return;
}

void UsesTest::testUsesUsingStmtType() {
	varTable->insertVar("x");
	varTable->insertVar("y");
	varTable->insertVar("z");
	varTable->insertVar("xy");
	typeTable->insertStmtNumAndType(2, TypeTable::ASSIGN);
	typeTable->insertStmtNumAndType(4, TypeTable::ASSIGN);
	typeTable->insertStmtNumAndType(5, TypeTable::IF);
	typeTable->insertStmtNumAndType(10, TypeTable::ASSIGN);
	typeTable->insertStmtNumAndType(12, TypeTable::ASSIGN);
	uses->setUses(2, "x");
	uses->setUses(2, "y");
	uses->setUses(4, "x");
	uses->setUses(5, "z");
	uses->setUses(10, "xy");

	
	CPPUNIT_ASSERT(uses->getUses(TypeTable::IF, "z") == vector<int> (1,5));
	vector<int> ans (1,2);
	ans.push_back(4);
	CPPUNIT_ASSERT(uses->getUses(TypeTable::ASSIGN, "x") == ans);
	CPPUNIT_ASSERT(uses->getUses(TypeTable::WHILE, "y") == vector<int> (1,-1));
	CPPUNIT_ASSERT(uses->getUses(TypeTable::WHILE, "asdfasdqwre") == vector<int> (1,-1));

	ans.clear();
	ans.push_back(varTable->getVarIndex("x"));
	CPPUNIT_ASSERT(uses->getUses(4) == ans);
	ans.push_back(varTable->getVarIndex("y"));
	CPPUNIT_ASSERT(uses->getUses(2) == ans);
	ans.clear();
	CPPUNIT_ASSERT(uses->getUses(3) == ans);
	CPPUNIT_ASSERT(uses->getUses(150) == ans);
	CPPUNIT_ASSERT(uses->getUses(-150) == ans);

	CPPUNIT_ASSERT(uses->getUses(TypeTable::WHILE)== ans);
	ans.push_back(2);
	ans.push_back(4);
	ans.push_back(10);
	CPPUNIT_ASSERT(uses->getUses(TypeTable::ASSIGN) ==ans);
	ans.clear();
	ans.push_back(5);
	CPPUNIT_ASSERT(uses->getUses(TypeTable::IF) ==ans);
	return;
}

void UsesTest::testChildrenUsingStmtType() {
	return;
}
