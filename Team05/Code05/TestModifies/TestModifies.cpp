#include <cppunit/config/SourcePrefix.h>
#include "TestModifies.h"

#include <iostream>
#include <set>

Modifies* modifies; 
PKB* pkb;
TypeTable* typeTable;
VarTable* varTable;
ProcTable* procTable;


void ModifiesTest::setUp() {
	pkb = PKB::getInstance();
	typeTable = pkb->getTypeTable();
	varTable = pkb->getVarTable();
	procTable = pkb->getProcTable();
	modifies = Modifies::getInstance(varTable,procTable);

	varTable->insertVar("a");
	varTable->insertVar("b");
	varTable->insertVar("c");
	
	modifies->setModifies(1, "a");
	modifies->setModifies(1, "b");
	modifies->setModifies(1, "c");
	modifies->setModifies(2, "b");
	modifies->setModifies(4, "c");
	modifies->setModifies(1500, "a");

	for(int i=0;i<200;i++){
		string str = to_string((long long)i);
		varTable->insertVar(str);
	}
	modifies->setModifies(4, "100");

	set<int> variableTemp;
	variableTemp.insert(1);
	variableTemp.insert(2);
	variableTemp.insert(3);
	modifies->setModifiesProc(1, variableTemp);
	variableTemp.clear();
	variableTemp.insert(2);
	modifies->setModifiesProc(2, variableTemp);
	variableTemp.clear();
	variableTemp.insert(3);
	modifies->setModifiesProc(4, variableTemp);
	variableTemp.clear();
	variableTemp.insert(1);
	modifies->setModifiesProc(1500, variableTemp);
}

void ModifiesTest::tearDown() {
	pkb->~PKB();
	pkb = PKB::getInstance();
	typeTable = pkb->getTypeTable();
	varTable = pkb->getVarTable();
	procTable = pkb->getProcTable();
	modifies = Modifies::getInstance(varTable,procTable);
}
	
// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( ModifiesTest ); // Note 4 

void ModifiesTest::testSetAndIsModifies() {
	modifies->printModifiesTable();
	CPPUNIT_ASSERT(modifies->isModifies(1,1)==true);
	CPPUNIT_ASSERT(modifies->isModifies(1,2)==true);
	CPPUNIT_ASSERT(modifies->isModifies(1,3)==true);
	CPPUNIT_ASSERT(modifies->isModifies(1,62)==false);
	CPPUNIT_ASSERT(modifies->isModifies(1,63)==false);
	CPPUNIT_ASSERT(modifies->isModifies(1,64)==false);
	CPPUNIT_ASSERT(modifies->isModifies(1,65)==false);
	CPPUNIT_ASSERT(modifies->isModifies(1,66)==false);
	CPPUNIT_ASSERT(modifies->isModifies(2,2)==true);
	CPPUNIT_ASSERT(modifies->isModifies(1500,1)==true);
	CPPUNIT_ASSERT(modifies->isModifies(1500,2)==false);
	CPPUNIT_ASSERT(modifies->isModifies(1501,1)==false);
	CPPUNIT_ASSERT(modifies->isModifies(1549,1)==false);
	CPPUNIT_ASSERT(modifies->isModifies(-1,1)==false);
}

void ModifiesTest::testGetModifies() {
	set<int> ans;
	ans.insert(1);
	ans.insert(2);
	ans.insert(3);
	CPPUNIT_ASSERT(modifies->getModified(1)==ans);

	ans.clear();
	ans.insert(1);
	CPPUNIT_ASSERT(modifies->getModified(1500)==ans);
	ans.clear();
	CPPUNIT_ASSERT(modifies->getModified(1499)==ans);
	CPPUNIT_ASSERT(modifies->getModified(0)==ans);
	CPPUNIT_ASSERT(modifies->getModified(-1)==ans);

	ans.clear();
	ans.insert(1);
	ans.insert(1500);
	CPPUNIT_ASSERT(modifies->getModifies(1)==ans);
	ans.clear();
	CPPUNIT_ASSERT(modifies->getModifies(0)==ans);
	CPPUNIT_ASSERT(modifies->getModifies(-1)==ans);
	CPPUNIT_ASSERT(modifies->getModifies(4)==ans);

	ans.insert(1);
	ans.insert(2);
	ans.insert(4);
	ans.insert(1500);
	CPPUNIT_ASSERT(modifies->getAllModifies()==ans);

	ans.clear();
	ans.insert(1);
	ans.insert(2);
	ans.insert(3);
	ans.insert(104);
	CPPUNIT_ASSERT(modifies->getAllModified()==ans);
}

void ModifiesTest::testSetAndIsModifiesProc() {
	CPPUNIT_ASSERT(modifies->isModifiesProc(1,1)==true);
	CPPUNIT_ASSERT(modifies->isModifiesProc(1,2)==true);
	CPPUNIT_ASSERT(modifies->isModifiesProc(1,3)==true);
	CPPUNIT_ASSERT(modifies->isModifiesProc(1,62)==false);
	CPPUNIT_ASSERT(modifies->isModifiesProc(1,63)==false);
	CPPUNIT_ASSERT(modifies->isModifiesProc(1,64)==false);
	CPPUNIT_ASSERT(modifies->isModifiesProc(1,65)==false);
	CPPUNIT_ASSERT(modifies->isModifiesProc(1,66)==false);
	CPPUNIT_ASSERT(modifies->isModifiesProc(2,2)==true);
	CPPUNIT_ASSERT(modifies->isModifiesProc(1500,1)==true);
	CPPUNIT_ASSERT(modifies->isModifiesProc(1500,2)==false);
	CPPUNIT_ASSERT(modifies->isModifiesProc(1501,1)==false);
	CPPUNIT_ASSERT(modifies->isModifiesProc(1549,1)==false);
	CPPUNIT_ASSERT(modifies->isModifiesProc(-1,1)==false);
}

void ModifiesTest::testGetModifiesProc() {
	set<int> ans;
	ans.insert(1);
	ans.insert(2);
	ans.insert(3);
	CPPUNIT_ASSERT(modifies->getModifiedProc(1)==ans);

	ans.clear();
	ans.insert(1);
	CPPUNIT_ASSERT(modifies->getModifiedProc(1500)==ans);
	ans.clear();
	CPPUNIT_ASSERT(modifies->getModifiedProc(1499)==ans);
	CPPUNIT_ASSERT(modifies->getModifiedProc(0)==ans);
	CPPUNIT_ASSERT(modifies->getModifiedProc(-1)==ans);

	ans.clear();
	ans.insert(1);
	ans.insert(1500);
	CPPUNIT_ASSERT(modifies->getModifiesProc(1)==ans);
	ans.clear();
	CPPUNIT_ASSERT(modifies->getModifiesProc(0)==ans);
	CPPUNIT_ASSERT(modifies->getModifiesProc(-1)==ans);
	CPPUNIT_ASSERT(modifies->getModifiesProc(4)==ans);

	ans.insert(1);
	ans.insert(2);
	ans.insert(4);
	ans.insert(1500);
	CPPUNIT_ASSERT(modifies->getAllModifiesProc()==ans);

	ans.clear();
	ans.insert(1);
	ans.insert(2);
	ans.insert(3);
	CPPUNIT_ASSERT(modifies->getAllModifiedProc()==ans);
}
