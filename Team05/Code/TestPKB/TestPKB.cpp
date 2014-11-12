#include <cppunit/config/SourcePrefix.h>
#include "TestPKB.h"

#include <iostream>
#include <vector>


PKB* pkb;
Parent* parent;
TypeTable* typeTable;
VarTable* varTable;


void PKBTest::setUp() {
	/*pkb = PKB::getInstance();
	typeTable = pkb->getTypeTable();
	varTable = pkb->getVarTable();*/
}

void PKBTest::tearDown() {
	/*pkb->~PKB();
	pkb = new PKB();
	typeTable = TypeTable::getInstance();
	varTable = VarTable::getInstance();*/
}
	
// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( PKBTest ); // Note 4 

void PKBTest::testDestructor() {
}
