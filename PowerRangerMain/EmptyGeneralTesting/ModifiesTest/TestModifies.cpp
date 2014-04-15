#include <cppunit/config/SourcePrefix.h>
#include "TestModifies.h"

#include <iostream>

Modifies* modifies; 
PKB* pkb;
TypeTable* typeTable;
VarTable* varTable;


void ModifiesTest::setUp() {
	pkb = PKB::getInstance();
	modifies = pkb->getModifies();
	typeTable = pkb->getTypeTable();
	varTable = pkb->getVarTable();

	varTable->insertVar("z");
	varTable->insertVar("x");
	varTable->insertVar("i");
	
	typeTable->insertStmtNumAndType(1, TypeTable::ASSIGN);
	typeTable->insertStmtNumAndType(2, TypeTable::ASSIGN);
	typeTable->insertStmtNumAndType(3, TypeTable::CALL);
	typeTable->insertStmtNumAndType(4, TypeTable::ASSIGN);
	typeTable->insertStmtNumAndType(5, TypeTable::ASSIGN);
	typeTable->insertStmtNumAndType(6, TypeTable::WHILE);
	typeTable->insertStmtNumAndType(7, TypeTable::ASSIGN);
	typeTable->insertStmtNumAndType(8, TypeTable::CALL);
	typeTable->insertStmtNumAndType(9, TypeTable::ASSIGN);
	typeTable->insertStmtNumAndType(10, TypeTable::IF);
	typeTable->insertStmtNumAndType(11, TypeTable::ASSIGN);
	typeTable->insertStmtNumAndType(12, TypeTable::ASSIGN);
	
	modifies->setModifies(1, "x");
	modifies->setModifies(2, "z");
	modifies->setModifies(4, "x");
	modifies->setModifies(5, "i");
	modifies->setModifies(6, "x");
	modifies->setModifies(6, "i");
	modifies->setModifies(7, "x");
	modifies->setModifies(9, "i");
	modifies->setModifies(10, "x");
	modifies->setModifies(10, "z");
	modifies->setModifies(11, "x");
	modifies->setModifies(12, "z");
	
}

void ModifiesTest::tearDown() {
	pkb->~PKB();
	pkb = new PKB();
	modifies = Modifies::getInstance();
	typeTable = TypeTable::getInstance();
	varTable = VarTable::getInstance();
}
	
// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( ModifiesTest ); // Note 4 

void ModifiesTest::testSetModifies() {  // Note 5
	map<STMTNUM, vector<VARINDEX>> map = modifies->getModifiesTable();
	CPPUNIT_ASSERT(map.at(1).size() == 1);
	CPPUNIT_ASSERT(varTable->getVarName(map.at(1).at(0)) == "x");

	CPPUNIT_ASSERT(map.at(6).size() == 2);
	CPPUNIT_ASSERT(varTable->getVarName(map.at(6).at(0)) == "x");
	CPPUNIT_ASSERT(varTable->getVarName(map.at(6).at(1)) == "i");
	return;
}

void ModifiesTest::testGetModifies() {
	vector<VARINDEX> v = modifies->getModifies(6); 
	CPPUNIT_ASSERT(varTable->getVarName(v.at(0)) == "x");
	CPPUNIT_ASSERT(varTable->getVarName(v.at(1)) == "i");

	v = modifies->getModifies(1); 
	CPPUNIT_ASSERT(varTable->getVarName(v.at(0)) == "x");
	
	v = modifies->getModifies(3); 
	CPPUNIT_ASSERT(v.size() == 0);

	vector<int> list = modifies->getModifies(TypeTable::ASSIGN, "x");
	CPPUNIT_ASSERT(list.size() == 4);
	CPPUNIT_ASSERT(list.at(0) == 1);
	CPPUNIT_ASSERT(list.at(1) == 4);
	CPPUNIT_ASSERT(list.at(2) == 7);
	CPPUNIT_ASSERT(list.at(3) == 11);

	list = modifies->getModifies(TypeTable::WHILE, "i");
	CPPUNIT_ASSERT(list.size() == 1);
	CPPUNIT_ASSERT(list.at(0) == 6);
		
	list = modifies->getModifies(TypeTable::WHILE, "z");
	CPPUNIT_ASSERT(list.size() == 1);
	CPPUNIT_ASSERT(list.at(0) == -1);

}

void ModifiesTest::testIsModifies() {
	CPPUNIT_ASSERT(modifies->isModifies(1, "x") == true);
	CPPUNIT_ASSERT(modifies->isModifies(2, "y") == false);
	CPPUNIT_ASSERT(modifies->isModifies(2, "z") == true);
	CPPUNIT_ASSERT(modifies->isModifies(3, "x") == false);
	CPPUNIT_ASSERT(modifies->isModifies(4, "x") == true);
	CPPUNIT_ASSERT(modifies->isModifies(5, "x") == false);
	CPPUNIT_ASSERT(modifies->isModifies(111, "ashfwnelw") == false);
	CPPUNIT_ASSERT(modifies->isModifies(-150, "ashfwnelw") == false);

}