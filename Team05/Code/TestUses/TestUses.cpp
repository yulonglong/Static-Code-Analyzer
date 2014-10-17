#include <cppunit/config/SourcePrefix.h>
#include "TestUses.h"

#include <iostream>
#include <string>
using namespace std;

Uses* uses; 
PKB* pkb;
VarTable* varTable;

void UsesTest::setUp() {
	pkb = PKB::getInstance();
	varTable = pkb->getVarTable();
	uses = Uses::getInstance(varTable);
	
	varTable->insertVar("a");
	varTable->insertVar("b");
	varTable->insertVar("c");
	
	uses->setUses(1, "a");
	uses->setUses(1, "b");
	uses->setUses(1, "c");
	uses->setUses(2, "b");
	uses->setUses(4, "c");
	uses->setUses(1500, "a");

	for(int i=0;i<200;i++){
		string str = to_string((long long)i);
		varTable->insertVar(str);
	}
	uses->setUses(4, "100");

	set<int> variableTemp;
	variableTemp.insert(1);
	variableTemp.insert(2);
	variableTemp.insert(3);
	uses->setUsesProc(1, variableTemp);
	variableTemp.clear();
	variableTemp.insert(2);
	uses->setUsesProc(2, variableTemp);
	variableTemp.clear();
	variableTemp.insert(3);
	uses->setUsesProc(4, variableTemp);
	variableTemp.clear();
	variableTemp.insert(1);
	uses->setUsesProc(1500, variableTemp);
}

void UsesTest::tearDown() {
	pkb->~PKB();
	pkb = PKB::getInstance();
	varTable = pkb->getVarTable();
	uses = Uses::getInstance(varTable);
}
	
// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( UsesTest ); // Note 4 

void UsesTest::testSetAndIsUses() {
	uses->printUsesTable();
	CPPUNIT_ASSERT(uses->isUses(1,1)==true);
	CPPUNIT_ASSERT(uses->isUses(1,2)==true);
	CPPUNIT_ASSERT(uses->isUses(1,3)==true);
	CPPUNIT_ASSERT(uses->isUses(1,62)==false);
	CPPUNIT_ASSERT(uses->isUses(1,63)==false);
	CPPUNIT_ASSERT(uses->isUses(1,64)==false);
	CPPUNIT_ASSERT(uses->isUses(1,65)==false);
	CPPUNIT_ASSERT(uses->isUses(1,66)==false);
	CPPUNIT_ASSERT(uses->isUses(2,2)==true);
	CPPUNIT_ASSERT(uses->isUses(1500,1)==true);
	CPPUNIT_ASSERT(uses->isUses(1500,2)==false);
	CPPUNIT_ASSERT(uses->isUses(1501,1)==false);
	CPPUNIT_ASSERT(uses->isUses(1549,1)==false);
	CPPUNIT_ASSERT(uses->isUses(-1,1)==false);
}

void UsesTest::testGetUses() {
	set<int> ans;
	ans.insert(1);
	ans.insert(2);
	ans.insert(3);
	CPPUNIT_ASSERT(uses->getUsed(1)==ans);

	ans.clear();
	ans.insert(1);
	CPPUNIT_ASSERT(uses->getUsed(1500)==ans);
	ans.clear();
	CPPUNIT_ASSERT(uses->getUsed(1499)==ans);
	CPPUNIT_ASSERT(uses->getUsed(0)==ans);
	CPPUNIT_ASSERT(uses->getUsed(-1)==ans);

	ans.clear();
	ans.insert(1);
	ans.insert(1500);
	CPPUNIT_ASSERT(uses->getUses(1)==ans);
	ans.clear();
	CPPUNIT_ASSERT(uses->getUses(0)==ans);
	CPPUNIT_ASSERT(uses->getUses(-1)==ans);
	CPPUNIT_ASSERT(uses->getUses(4)==ans);

	ans.insert(1);
	ans.insert(2);
	ans.insert(4);
	ans.insert(1500);
	CPPUNIT_ASSERT(uses->getAllUses()==ans);
	ans.clear();
	ans.insert(1);
	ans.insert(2);
	ans.insert(3);
	ans.insert(104);
	CPPUNIT_ASSERT(uses->getAllUsed()==ans);
}

void UsesTest::testSetAndIsUsesProc() {
	CPPUNIT_ASSERT(uses->isUsesProc(1,1)==true);
	CPPUNIT_ASSERT(uses->isUsesProc(1,2)==true);
	CPPUNIT_ASSERT(uses->isUsesProc(1,3)==true);
	CPPUNIT_ASSERT(uses->isUsesProc(1,62)==false);
	CPPUNIT_ASSERT(uses->isUsesProc(1,63)==false);
	CPPUNIT_ASSERT(uses->isUsesProc(1,64)==false);
	CPPUNIT_ASSERT(uses->isUsesProc(1,65)==false);
	CPPUNIT_ASSERT(uses->isUsesProc(1,66)==false);
	CPPUNIT_ASSERT(uses->isUsesProc(2,2)==true);
	CPPUNIT_ASSERT(uses->isUsesProc(1500,1)==true);
	CPPUNIT_ASSERT(uses->isUsesProc(1500,2)==false);
	CPPUNIT_ASSERT(uses->isUsesProc(1501,1)==false);
	CPPUNIT_ASSERT(uses->isUsesProc(1549,1)==false);
	CPPUNIT_ASSERT(uses->isUsesProc(-1,1)==false);
}

void UsesTest::testGetUsesProc() {
	set<int> ans;
	ans.insert(1);
	ans.insert(2);
	ans.insert(3);
	CPPUNIT_ASSERT(uses->getUsedProc(1)==ans);

	ans.clear();
	ans.insert(1);
	CPPUNIT_ASSERT(uses->getUsedProc(1500)==ans);
	ans.clear();
	CPPUNIT_ASSERT(uses->getUsedProc(1499)==ans);
	CPPUNIT_ASSERT(uses->getUsedProc(0)==ans);
	CPPUNIT_ASSERT(uses->getUsedProc(-1)==ans);

	ans.clear();
	ans.insert(1);
	ans.insert(1500);
	CPPUNIT_ASSERT(uses->getUsesProc(1)==ans);
	ans.clear();
	CPPUNIT_ASSERT(uses->getUsesProc(0)==ans);
	CPPUNIT_ASSERT(uses->getUsesProc(-1)==ans);
	CPPUNIT_ASSERT(uses->getUsesProc(4)==ans);

	ans.insert(1);
	ans.insert(2);
	ans.insert(4);
	ans.insert(1500);
	CPPUNIT_ASSERT(uses->getAllUsesProc()==ans);

	ans.clear();
	ans.insert(1);
	ans.insert(2);
	ans.insert(3);
	CPPUNIT_ASSERT(uses->getAllUsedProc()==ans);
}
