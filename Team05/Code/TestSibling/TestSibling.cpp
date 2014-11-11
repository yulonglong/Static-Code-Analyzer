#include <cppunit/config/SourcePrefix.h>
#include "TestSibling.h"
#include "TypeTable.h"
#include "VarTable.h"
#include "ProcTable.h"
#include "ConstTable.h"

#include <iostream>
#include <string>
using namespace std;

class Sibling;
Sibling *sibling; 
PKB *pkb;
VarTable *varTable;
ProcTable *procTable;
ConstTable *constTable;
TypeTable *typeTable;

void SiblingTest::setUp() {
	pkb = PKB::getInstance();
	typeTable = pkb->getTypeTable();
	varTable = pkb->getVarTable();
	procTable = pkb->getProcTable();
	constTable = pkb->getConstTable();
	sibling = Sibling::getInstance(varTable,procTable,constTable,typeTable);
}

void SiblingTest::tearDown() {
	pkb->~PKB();
	pkb = PKB::getInstance();
	typeTable = pkb->getTypeTable();
	varTable = pkb->getVarTable();
	procTable = pkb->getProcTable();
	constTable = pkb->getConstTable();
	sibling = Sibling::getInstance(varTable,procTable,constTable,typeTable);
}

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( SiblingTest ); // Note 4 

void SiblingTest::testSiblingStmtNumStmtNum() {  // Note 5
	
	sibling->setToSiblingStmtNumStmtNum(6, 7);
	sibling->setToSiblingStmtNumStmtNum(6, 8);
	sibling->setToSiblingStmtNumStmtNum(6, 9);
	sibling->setToSiblingStmtNumStmtNum(10, 11);
	sibling->setToSiblingStmtNumStmtNum(10, 12);
	sibling->setToSiblingStmtNumStmtNum(500, 502);
	sibling->setToSiblingStmtNumStmtNum(500, 600);
	sibling->setToSiblingStmtNumStmtNum(500, 1500);


	sibling->printSiblingTable();

	CPPUNIT_ASSERT(sibling->isSiblingStmtNumStmtNum(6, 7) == true);
	CPPUNIT_ASSERT(sibling->isSiblingStmtNumStmtNum(7, 6) == true);
	CPPUNIT_ASSERT(sibling->isSiblingStmtNumStmtNum(7, 9) == true);
	CPPUNIT_ASSERT(sibling->isSiblingStmtNumStmtNum(10, 11) == true);
	CPPUNIT_ASSERT(sibling->isSiblingStmtNumStmtNum(12, 11) == true);
	CPPUNIT_ASSERT(sibling->isSiblingStmtNumStmtNum(5, 6) == false);
	CPPUNIT_ASSERT(sibling->isSiblingStmtNumStmtNum(6, 10) == false);
	CPPUNIT_ASSERT(sibling->isSiblingStmtNumStmtNum(500, 502) == true);
	CPPUNIT_ASSERT(sibling->isSiblingStmtNumStmtNum(500, 600) == true);
	CPPUNIT_ASSERT(sibling->isSiblingStmtNumStmtNum(500, 1500) == true);
	CPPUNIT_ASSERT(sibling->isSiblingStmtNumStmtNum(500, 505) == false);
	CPPUNIT_ASSERT(sibling->isSiblingStmtNumStmtNum(500, 1499) == false);
	CPPUNIT_ASSERT(sibling->isSiblingStmtNumStmtNum(500, 1501) == false);
	CPPUNIT_ASSERT(sibling->isSiblingStmtNumStmtNum(500, -1) == false);
	CPPUNIT_ASSERT(sibling->isSiblingStmtNumStmtNum(-1,500) == false);

	set<int> ans;
	ans.insert(7);
	ans.insert(8);
	ans.insert(9);
	CPPUNIT_ASSERT(sibling->getSiblingStmtNumWithStmtNum(6) == ans);

	ans.clear();
	ans.insert(502);
	ans.insert(600);
	ans.insert(1500);
	CPPUNIT_ASSERT(sibling->getSiblingStmtNumWithStmtNum(500) == ans);

	ans.clear();
	ans.insert(6);
	ans.insert(10);
	ans.insert(500);
	ans.insert(7);
	ans.insert(8);
	ans.insert(9);
	ans.insert(11);
	ans.insert(12);
	ans.insert(502);
	ans.insert(600);
	ans.insert(1500);
	CPPUNIT_ASSERT(sibling->getAllSiblingStmtNumWithStmtNum() == ans);
	return;
}

void SiblingTest::testSiblingVarIndexVarIndex() { 
	varTable->insertVar("first");
	varTable->insertVar("second");
	varTable->insertVar("third");
	varTable->insertVar("fourth");
	varTable->insertVar("fifth");
	varTable->insertVar("sixth");
	varTable->insertVar("seventh");
	varTable->insertVar("eighth");

	int one = varTable->getVarIndex("first");
	int two = varTable->getVarIndex("second");
	int three = varTable->getVarIndex("third");
	int four = varTable->getVarIndex("fourth");
	int five = varTable->getVarIndex("fifth");
	int six = varTable->getVarIndex("sixth");
	int seven = varTable->getVarIndex("seventh");
	int eight = varTable->getVarIndex("eighth");

	sibling->setToSiblingVarNameVarName("first", "second");
	sibling->setToSiblingVarNameVarName("first", "third");
	sibling->setToSiblingVarNameVarName("first", "fourth");
	sibling->setToSiblingVarNameVarName("fifth", "sixth");
	sibling->setToSiblingVarNameVarName("fifth", "seventh");


	CPPUNIT_ASSERT(sibling->isSiblingVarNameVarName("first", "second") == true);
	CPPUNIT_ASSERT(sibling->isSiblingVarNameVarName("fifth", "sixth") == true);
	CPPUNIT_ASSERT(sibling->isSiblingVarNameVarName("first", "fifth") == false);
	CPPUNIT_ASSERT(sibling->isSiblingVarNameVarName("first", "error") == false);
	CPPUNIT_ASSERT(sibling->isSiblingVarNameVarName("first", "eighth") == false);
	CPPUNIT_ASSERT(sibling->isSiblingVarNameVarName("error", "first") == false);
	CPPUNIT_ASSERT(sibling->isSiblingVarNameVarName("eroor1","error2") == false);

	set<int> ans;
	ans.insert(two);
	ans.insert(three);
	ans.insert(four);
	CPPUNIT_ASSERT(sibling->getSiblingVarIndexWithVarIndex(one) == ans);

	ans.clear();
	ans.insert(one);
	ans.insert(three);
	ans.insert(four);
	CPPUNIT_ASSERT(sibling->getSiblingVarIndexWithVarIndex(two) == ans);

	ans.clear();
	ans.insert(five);
	ans.insert(seven);
	CPPUNIT_ASSERT(sibling->getSiblingVarIndexWithVarIndex(six) == ans);

	ans.clear();
	ans.insert(one);
	ans.insert(two);
	ans.insert(three);
	ans.insert(four);
	ans.insert(five);
	ans.insert(six);
	ans.insert(seven);
	CPPUNIT_ASSERT(sibling->getAllSiblingVarIndexWithVarIndex() == ans);
	return;
}

void SiblingTest::testSiblingVarIndexConstant() { 
	varTable->insertVar("first");
	varTable->insertVar("second");
	varTable->insertVar("third");
	varTable->insertVar("fourth");
	varTable->insertVar("fifth");
	varTable->insertVar("sixth");
	varTable->insertVar("seventh");
	varTable->insertVar("eighth");

	int one = varTable->getVarIndex("first");
	int two = varTable->getVarIndex("second");
	int three = varTable->getVarIndex("third");
	int four = varTable->getVarIndex("fourth");
	int five = varTable->getVarIndex("fifth");
	int six = varTable->getVarIndex("sixth");
	int seven = varTable->getVarIndex("seventh");
	int eight = varTable->getVarIndex("eighth");

	constTable->insertConst("satu");
	constTable->insertConst("dua");
	constTable->insertConst("tiga");
	constTable->insertConst("empat");
	constTable->insertConst("lima");
	constTable->insertConst("enam");
	constTable->insertConst("tujuh");
	constTable->insertConst("delapan");

	int satu = constTable->getConstIndex("satu");
	int dua = constTable->getConstIndex("dua");
	int tiga = constTable->getConstIndex("tiga");
	int empat = constTable->getConstIndex("empat");
	int lima = constTable->getConstIndex("lima");
	int enam = constTable->getConstIndex("enam");
	int tujuh = constTable->getConstIndex("tujuh");
	int delapan = constTable->getConstIndex("delapan");

	sibling->setToSiblingVarNameConstant("first", "dua");
	sibling->setToSiblingVarNameConstant("first", "tiga");
	sibling->setToSiblingVarNameConstant("first", "empat");
	sibling->setToSiblingVarNameConstant("fifth", "lima");
	sibling->setToSiblingVarNameConstant("fifth", "enam");


	CPPUNIT_ASSERT(sibling->isSiblingVarNameConstant("first", "dua") == true);
	CPPUNIT_ASSERT(sibling->isSiblingVarNameConstant("fifth", "enam") == true);
	CPPUNIT_ASSERT(sibling->isSiblingVarNameConstant("first", "lima") == false);
	CPPUNIT_ASSERT(sibling->isSiblingVarNameConstant("first", "error") == false);
	CPPUNIT_ASSERT(sibling->isSiblingVarNameConstant("first", "delapan") == false);
	CPPUNIT_ASSERT(sibling->isSiblingVarNameConstant("error", "first") == false);
	CPPUNIT_ASSERT(sibling->isSiblingVarNameConstant("error", "satu") == false);
	CPPUNIT_ASSERT(sibling->isSiblingVarNameConstant("eroor1","error2") == false);
	CPPUNIT_ASSERT(sibling->isSiblingVarNameConstant("","") == false);

	set<int> ans;
	ans.insert(dua);
	ans.insert(tiga);
	ans.insert(empat);
	CPPUNIT_ASSERT(sibling->getSiblingConstantWithVarIndex(one) == ans);

	ans.clear();
	ans.insert(lima);
	ans.insert(enam);
	CPPUNIT_ASSERT(sibling->getSiblingConstantWithVarIndex(five) == ans);

	ans.clear();
	ans.insert(one);
	CPPUNIT_ASSERT(sibling->getSiblingVarIndexWithConstant(dua) == ans);

	ans.clear();
	CPPUNIT_ASSERT(sibling->getSiblingVarIndexWithConstant(satu) == ans);
	CPPUNIT_ASSERT(sibling->getSiblingVarIndexWithConstant(delapan) == ans);
	CPPUNIT_ASSERT(sibling->getSiblingConstantWithVarIndex(six) == ans);
	CPPUNIT_ASSERT(sibling->getSiblingConstantWithVarIndex(two) == ans);

	ans.clear();
	ans.insert(one);
	ans.insert(five);
	CPPUNIT_ASSERT(sibling->getAllSiblingVarIndexWithConstant() == ans);

	ans.clear();
	ans.insert(dua);
	ans.insert(tiga);
	ans.insert(empat);
	ans.insert(lima);
	ans.insert(enam);
	CPPUNIT_ASSERT(sibling->getAllSiblingConstantWithVarIndex() == ans);
	return;
}

void SiblingTest::testSiblingConstantConstant() { 
	constTable->insertConst("satu");
	constTable->insertConst("dua");
	constTable->insertConst("tiga");
	constTable->insertConst("empat");
	constTable->insertConst("lima");
	constTable->insertConst("enam");
	constTable->insertConst("tujuh");
	constTable->insertConst("delapan");

	int satu = constTable->getConstIndex("satu");
	int dua = constTable->getConstIndex("dua");
	int tiga = constTable->getConstIndex("tiga");
	int empat = constTable->getConstIndex("empat");
	int lima = constTable->getConstIndex("lima");
	int enam = constTable->getConstIndex("enam");
	int tujuh = constTable->getConstIndex("tujuh");
	int delapan = constTable->getConstIndex("delapan");

	sibling->setToSiblingConstantConstant("satu", "dua");
	sibling->setToSiblingConstantConstant("satu", "tiga");
	sibling->setToSiblingConstantConstant("satu", "empat");
	sibling->setToSiblingConstantConstant("lima", "enam");
	sibling->setToSiblingConstantConstant("lima", "tujuh");


	CPPUNIT_ASSERT(sibling->isSiblingConstantConstant("satu", "dua") == true);
	CPPUNIT_ASSERT(sibling->isSiblingConstantConstant("lima", "enam") == true);
	CPPUNIT_ASSERT(sibling->isSiblingConstantConstant("satu", "lima") == false);
	CPPUNIT_ASSERT(sibling->isSiblingConstantConstant("satu", "error") == false);
	CPPUNIT_ASSERT(sibling->isSiblingConstantConstant("satu", "delapan") == false);
	CPPUNIT_ASSERT(sibling->isSiblingConstantConstant("error", "first") == false);
	CPPUNIT_ASSERT(sibling->isSiblingConstantConstant("eroor1","error2") == false);

	set<int> ans;
	ans.insert(dua);
	ans.insert(tiga);
	ans.insert(empat);
	CPPUNIT_ASSERT(sibling->getSiblingConstantWithConstant(satu) == ans);

	ans.clear();
	ans.insert(satu);
	ans.insert(tiga);
	ans.insert(empat);
	CPPUNIT_ASSERT(sibling->getSiblingConstantWithConstant(dua) == ans);

	ans.clear();
	ans.insert(lima);
	ans.insert(tujuh);
	CPPUNIT_ASSERT(sibling->getSiblingConstantWithConstant(enam) == ans);

	ans.clear();
	ans.insert(satu);
	ans.insert(dua);
	ans.insert(tiga);
	ans.insert(empat);
	ans.insert(lima);
	ans.insert(enam);
	ans.insert(tujuh);
	CPPUNIT_ASSERT(sibling->getAllSiblingConstantWithConstant() == ans);
	return;
}

void SiblingTest::testSiblingVarIndexMathOp() { 
	varTable->insertVar("first");
	varTable->insertVar("second");
	varTable->insertVar("third");
	varTable->insertVar("fourth");
	varTable->insertVar("fifth");
	varTable->insertVar("sixth");
	varTable->insertVar("seventh");
	varTable->insertVar("eighth");

	int one = varTable->getVarIndex("first");
	int two = varTable->getVarIndex("second");
	int three = varTable->getVarIndex("third");
	int four = varTable->getVarIndex("fourth");
	int five = varTable->getVarIndex("fifth");
	int six = varTable->getVarIndex("sixth");
	int seven = varTable->getVarIndex("seventh");
	int eight = varTable->getVarIndex("eighth");

	sibling->setToSiblingVarNameMathOp("first", TypeTable::PLUS);
	sibling->setToSiblingVarNameMathOp("first", TypeTable::MINUS);
	sibling->setToSiblingVarNameMathOp("first", TypeTable::TIMES);
	sibling->setToSiblingVarNameMathOp("fifth", TypeTable::PLUS);
	sibling->setToSiblingVarNameMathOp("fifth", TypeTable::MINUS);


	CPPUNIT_ASSERT(sibling->isSiblingVarNameMathOp("first", TypeTable::PLUS) == true);
	CPPUNIT_ASSERT(sibling->isSiblingVarNameMathOp("fifth", TypeTable::MINUS) == true);
	CPPUNIT_ASSERT(sibling->isSiblingVarNameMathOp("first", TypeTable::ASSIGN) == false);
	CPPUNIT_ASSERT(sibling->isSiblingVarNameMathOp("first", TypeTable::INVALID) == false);
	CPPUNIT_ASSERT(sibling->isSiblingVarNameMathOp("fifth", TypeTable::TIMES) == false);
	CPPUNIT_ASSERT(sibling->isSiblingVarNameMathOp("second", TypeTable::PLUS) == false);
	CPPUNIT_ASSERT(sibling->isSiblingVarNameMathOp("eightg", TypeTable::MINUS) == false);
	CPPUNIT_ASSERT(sibling->isSiblingVarNameMathOp("",TypeTable::MINUS) == false);

	set<int> ans;
	set<TypeTable::SynType> ans2;
	ans2.insert(TypeTable::PLUS);
	ans2.insert(TypeTable::MINUS);
	ans2.insert(TypeTable::TIMES);
	CPPUNIT_ASSERT(sibling->getSiblingMathOpWithVarIndex(one) == ans2);

	ans2.clear();
	ans2.insert(TypeTable::MINUS);
	ans2.insert(TypeTable::PLUS);
	CPPUNIT_ASSERT(sibling->getSiblingMathOpWithVarIndex(five) == ans2);

	ans.clear();
	ans.insert(one);
	CPPUNIT_ASSERT(sibling->getSiblingVarIndexWithMathOp(TypeTable::TIMES) == ans);

	ans.clear();
	ans.insert(one);
	ans.insert(five);
	CPPUNIT_ASSERT(sibling->getSiblingVarIndexWithMathOp(TypeTable::PLUS) == ans);

	ans.clear();
	ans2.clear();
	cout<<"here5"<<endl;
	CPPUNIT_ASSERT(sibling->getSiblingVarIndexWithMathOp(TypeTable::ASSIGN) == ans);
	cout<<"here5"<<endl;
	CPPUNIT_ASSERT(sibling->getSiblingVarIndexWithMathOp(TypeTable::INVALID) == ans);
	cout<<"here5"<<endl;
	CPPUNIT_ASSERT(sibling->getSiblingMathOpWithVarIndex(six) == ans2);
	cout<<"here5"<<endl;
	CPPUNIT_ASSERT(sibling->getSiblingMathOpWithVarIndex(two) == ans2);

	ans.clear();
	ans.insert(one);
	ans.insert(five);
	CPPUNIT_ASSERT(sibling->getAllSiblingVarIndexWithMathOp() == ans);

	ans2.clear();
	ans2.insert(TypeTable::PLUS);
	ans2.insert(TypeTable::MINUS);
	ans2.insert(TypeTable::TIMES);
	CPPUNIT_ASSERT(sibling->getAllSiblingMathOpWithVarIndex() == ans2);
	return;
}
