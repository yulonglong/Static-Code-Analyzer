#include <cppunit/config/SourcePrefix.h>
#include "TestModifies.h"

#include <iostream>

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
	modifies = Modifies::getInstance(typeTable,varTable,procTable);

	/*varTable->insertVar("z");
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
	modifies->setModifies(12, "z");*/
	
}

void ModifiesTest::tearDown() {
	pkb->~PKB();
	pkb = PKB::getInstance();
	typeTable = pkb->getTypeTable();
	varTable = pkb->getVarTable();
	procTable = pkb->getProcTable();
	modifies = Modifies::getInstance(typeTable,varTable,procTable);
}
	
// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( ModifiesTest ); // Note 4 

void ModifiesTest::test1() {
	varTable->insertVar("a");
	varTable->insertVar("b");
	varTable->insertVar("c");
	
	modifies->setModifies(1, "a");
	modifies->setModifies(1, "b");
	modifies->setModifies(1, "c");
	modifies->setModifies(2, "b");
	modifies->setModifies(4, "c");
	modifies->setModifies(1500, "a");

	CPPUNIT_ASSERT(modifies->isModifies(1,"a")==true);
	CPPUNIT_ASSERT(modifies->isModifies(1,"b")==true);
	CPPUNIT_ASSERT(modifies->isModifies(1,"c")==true);
	CPPUNIT_ASSERT(modifies->isModifies(2,"b")==true);
	CPPUNIT_ASSERT(modifies->isModifies(1500,"a")==true);
	CPPUNIT_ASSERT(modifies->isModifies(1500,"b")==false);
	CPPUNIT_ASSERT(modifies->isModifies(1501,"a")==false);
	CPPUNIT_ASSERT(modifies->isModifies(1549,"a")==false);
	CPPUNIT_ASSERT(modifies->isModifies(-1,"a")==false);

	vector<int> ans;
	ans.push_back(1);
	ans.push_back(2);
	ans.push_back(3);
	CPPUNIT_ASSERT(modifies->getModified(1)==ans);

	ans.clear();
	ans.push_back(1);
	CPPUNIT_ASSERT(modifies->getModified(1500)==ans);
	ans.clear();
	CPPUNIT_ASSERT(modifies->getModified(1499)==ans);

	ans.clear();
	ans.push_back(1);
	ans.push_back(1500);
	cout<<"size of ans ="<<modifies->getModifies(1).size();
	CPPUNIT_ASSERT(modifies->getModifies(1)==ans);
	ans.clear();
	CPPUNIT_ASSERT(modifies->getModifies(0)==ans);
	CPPUNIT_ASSERT(modifies->getModifies(4)==ans);

}



void ModifiesTest::testGetModifies() {
	modifies->printModifiesTable();
	vector<VARINDEX> v = modifies->getModifies(6); 
	CPPUNIT_ASSERT(varTable->getVarName(v.at(0)) == "x");
	CPPUNIT_ASSERT(varTable->getVarName(v.at(1)) == "i");

	v = modifies->getModifies(1); 
	CPPUNIT_ASSERT(varTable->getVarName(v.at(0)) == "x");
	
	v = modifies->getModifies(3); 
	CPPUNIT_ASSERT(v.empty() == true);

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
	CPPUNIT_ASSERT(list.empty() == true);

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

void ModifiesTest::testSetProcModifies() {
	vector<VARINDEX> temp (1,2);
	temp.push_back(3);
	temp.push_back(5);

	modifies->setModifiesProc(2,temp);
	vector<VARINDEX> temp1 (1,5);
	temp1.push_back(7);

	modifies->setModifiesProc(2,temp1);
	CPPUNIT_ASSERT(modifies->getModifiesProc(2).at(3) == 7);


	varTable->insertVar("x");
	modifies->setModifies(1,"x");
	cout<<modifies->getModifies(1).size()<<endl;
	modifies->setModifies(1,"x");
	cout<<modifies->getModifies(1).size()<<endl;
	modifies->setModifies(1,"x");
	cout<<modifies->getModifies(1).size()<<endl;
	return;
}