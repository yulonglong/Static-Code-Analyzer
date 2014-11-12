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


	CPPUNIT_ASSERT(sibling->isSiblingVarIndexVarIndex(one, two) == true);
	CPPUNIT_ASSERT(sibling->isSiblingVarIndexVarIndex(five, six) == true);
	CPPUNIT_ASSERT(sibling->isSiblingVarIndexVarIndex(one, five) == false);
	CPPUNIT_ASSERT(sibling->isSiblingVarIndexVarIndex(one, -1) == false);
	CPPUNIT_ASSERT(sibling->isSiblingVarIndexVarIndex(one, 10) == false);
	CPPUNIT_ASSERT(sibling->isSiblingVarIndexVarIndex(-1, one) == false);
	CPPUNIT_ASSERT(sibling->isSiblingVarIndexVarIndex(90,100) == false);

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


	CPPUNIT_ASSERT(sibling->isSiblingVarIndexConstant(one, dua) == true);
	CPPUNIT_ASSERT(sibling->isSiblingVarIndexConstant(five, enam) == true);
	CPPUNIT_ASSERT(sibling->isSiblingVarIndexConstant(one, lima) == false);
	CPPUNIT_ASSERT(sibling->isSiblingVarIndexConstant(one, delapan) == false);
	CPPUNIT_ASSERT(sibling->isSiblingVarIndexConstant(one, -1) == false);
	CPPUNIT_ASSERT(sibling->isSiblingVarIndexConstant(-1, satu) == false);

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


	CPPUNIT_ASSERT(sibling->isSiblingConstantConstant(satu, dua) == true);
	CPPUNIT_ASSERT(sibling->isSiblingConstantConstant(lima, enam) == true);
	CPPUNIT_ASSERT(sibling->isSiblingConstantConstant(satu, lima) == false);
	CPPUNIT_ASSERT(sibling->isSiblingConstantConstant(satu, 9) == false);
	CPPUNIT_ASSERT(sibling->isSiblingConstantConstant(satu, delapan) == false);
	CPPUNIT_ASSERT(sibling->isSiblingConstantConstant(satu, -1) == false);
	CPPUNIT_ASSERT(sibling->isSiblingConstantConstant(10, satu) == false);
	CPPUNIT_ASSERT(sibling->isSiblingConstantConstant(15,17) == false);

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


	CPPUNIT_ASSERT(sibling->isSiblingVarIndexMathOp(one, TypeTable::PLUS) == true);
	CPPUNIT_ASSERT(sibling->isSiblingVarIndexMathOp(five, TypeTable::MINUS) == true);
	CPPUNIT_ASSERT(sibling->isSiblingVarIndexMathOp(one, TypeTable::ASSIGN) == false);
	CPPUNIT_ASSERT(sibling->isSiblingVarIndexMathOp(one, TypeTable::INVALID) == false);
	CPPUNIT_ASSERT(sibling->isSiblingVarIndexMathOp(five, TypeTable::TIMES) == false);
	CPPUNIT_ASSERT(sibling->isSiblingVarIndexMathOp(two, TypeTable::PLUS) == false);
	CPPUNIT_ASSERT(sibling->isSiblingVarIndexMathOp(-1, TypeTable::MINUS) == false);
	CPPUNIT_ASSERT(sibling->isSiblingVarIndexMathOp(99,TypeTable::MINUS) == false);

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
	CPPUNIT_ASSERT(sibling->getSiblingVarIndexWithMathOp(TypeTable::ASSIGN) == ans);
	CPPUNIT_ASSERT(sibling->getSiblingVarIndexWithMathOp(TypeTable::INVALID) == ans);
	CPPUNIT_ASSERT(sibling->getSiblingMathOpWithVarIndex(six) == ans2);
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

void SiblingTest::testSiblingConstantMathOp() { 
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

	sibling->setToSiblingConstantMathOp("satu", TypeTable::PLUS);
	sibling->setToSiblingConstantMathOp("satu", TypeTable::MINUS);
	sibling->setToSiblingConstantMathOp("satu", TypeTable::TIMES);
	sibling->setToSiblingConstantMathOp("lima", TypeTable::PLUS);
	sibling->setToSiblingConstantMathOp("lima", TypeTable::MINUS);


	CPPUNIT_ASSERT(sibling->isSiblingConstantMathOp(satu, TypeTable::PLUS) == true);
	CPPUNIT_ASSERT(sibling->isSiblingConstantMathOp(lima, TypeTable::MINUS) == true);
	CPPUNIT_ASSERT(sibling->isSiblingConstantMathOp(satu, TypeTable::ASSIGN) == false);
	CPPUNIT_ASSERT(sibling->isSiblingConstantMathOp(satu, TypeTable::INVALID) == false);
	CPPUNIT_ASSERT(sibling->isSiblingConstantMathOp(lima, TypeTable::TIMES) == false);
	CPPUNIT_ASSERT(sibling->isSiblingConstantMathOp(dua, TypeTable::PLUS) == false);
	CPPUNIT_ASSERT(sibling->isSiblingConstantMathOp(-1, TypeTable::MINUS) == false);
	CPPUNIT_ASSERT(sibling->isSiblingConstantMathOp(-1,TypeTable::MINUS) == false);

	set<int> ans;
	set<TypeTable::SynType> ans2;
	ans2.insert(TypeTable::PLUS);
	ans2.insert(TypeTable::MINUS);
	ans2.insert(TypeTable::TIMES);
	CPPUNIT_ASSERT(sibling->getSiblingMathOpWithConstant(satu) == ans2);

	ans2.clear();
	ans2.insert(TypeTable::MINUS);
	ans2.insert(TypeTable::PLUS);
	CPPUNIT_ASSERT(sibling->getSiblingMathOpWithConstant(lima) == ans2);

	ans.clear();
	ans.insert(satu);
	CPPUNIT_ASSERT(sibling->getSiblingConstantWithMathOp(TypeTable::TIMES) == ans);

	ans.clear();
	ans.insert(satu);
	ans.insert(lima);
	CPPUNIT_ASSERT(sibling->getSiblingConstantWithMathOp(TypeTable::PLUS) == ans);

	ans.clear();
	ans2.clear();
	CPPUNIT_ASSERT(sibling->getSiblingConstantWithMathOp(TypeTable::ASSIGN) == ans);
	CPPUNIT_ASSERT(sibling->getSiblingConstantWithMathOp(TypeTable::INVALID) == ans);
	CPPUNIT_ASSERT(sibling->getSiblingMathOpWithConstant(enam) == ans2);
	CPPUNIT_ASSERT(sibling->getSiblingMathOpWithConstant(dua) == ans2);

	ans.clear();
	ans.insert(satu);
	ans.insert(lima);
	CPPUNIT_ASSERT(sibling->getAllSiblingConstantWithMathOp() == ans);

	ans2.clear();
	ans2.insert(TypeTable::PLUS);
	ans2.insert(TypeTable::MINUS);
	ans2.insert(TypeTable::TIMES);
	CPPUNIT_ASSERT(sibling->getAllSiblingMathOpWithConstant() == ans2);
	return;
}

void SiblingTest::testSiblingProcIndexProcIndex() { 
	procTable->insertProc("first");
	procTable->insertProc("second");
	procTable->insertProc("third");
	procTable->insertProc("fourth");
	procTable->insertProc("fifth");
	procTable->insertProc("sixth");
	procTable->insertProc("seventh");
	procTable->insertProc("eighth");

	int one = procTable->getProcIndex("first");
	int two = procTable->getProcIndex("second");
	int three = procTable->getProcIndex("third");
	int four = procTable->getProcIndex("fourth");
	int five = procTable->getProcIndex("fifth");
	int six = procTable->getProcIndex("sixth");
	int seven = procTable->getProcIndex("seventh");
	int eight = procTable->getProcIndex("eighth");

	sibling->setToSiblingProcNameProcName("first", "second");
	sibling->setToSiblingProcNameProcName("first", "third");
	sibling->setToSiblingProcNameProcName("first", "fourth");
	sibling->setToSiblingProcNameProcName("fifth", "sixth");
	sibling->setToSiblingProcNameProcName("fifth", "seventh");


	CPPUNIT_ASSERT(sibling->isSiblingProcIndexProcIndex(one, two) == true);
	CPPUNIT_ASSERT(sibling->isSiblingProcIndexProcIndex(five, six) == true);
	CPPUNIT_ASSERT(sibling->isSiblingProcIndexProcIndex(one, five) == false);
	CPPUNIT_ASSERT(sibling->isSiblingProcIndexProcIndex(one, -1) == false);
	CPPUNIT_ASSERT(sibling->isSiblingProcIndexProcIndex(one, 10) == false);
	CPPUNIT_ASSERT(sibling->isSiblingProcIndexProcIndex(-1, one) == false);
	CPPUNIT_ASSERT(sibling->isSiblingProcIndexProcIndex(40,-2) == false);

	set<int> ans;
	ans.insert(two);
	ans.insert(three);
	ans.insert(four);
	CPPUNIT_ASSERT(sibling->getSiblingProcIndexWithProcIndex(one) == ans);

	ans.clear();
	ans.insert(one);
	ans.insert(three);
	ans.insert(four);
	CPPUNIT_ASSERT(sibling->getSiblingProcIndexWithProcIndex(two) == ans);

	ans.clear();
	ans.insert(five);
	ans.insert(seven);
	CPPUNIT_ASSERT(sibling->getSiblingProcIndexWithProcIndex(six) == ans);

	ans.clear();
	ans.insert(one);
	ans.insert(two);
	ans.insert(three);
	ans.insert(four);
	ans.insert(five);
	ans.insert(six);
	ans.insert(seven);
	CPPUNIT_ASSERT(sibling->getAllSiblingProcIndexWithProcIndex() == ans);
	return;
}

void SiblingTest::testSiblingMathOpMathOp() { 
	sibling->setToSiblingMathOpMathOp(TypeTable::PLUS, TypeTable::MINUS);


	CPPUNIT_ASSERT(sibling->isSiblingMathOpMathOp(TypeTable::PLUS, TypeTable::MINUS) == true);
	CPPUNIT_ASSERT(sibling->isSiblingMathOpMathOp(TypeTable::MINUS, TypeTable::PLUS) == true);
	CPPUNIT_ASSERT(sibling->isSiblingMathOpMathOp(TypeTable::PLUS, TypeTable::TIMES) == false);
	CPPUNIT_ASSERT(sibling->isSiblingMathOpMathOp(TypeTable::PLUS, TypeTable::INVALID) == false);

	set<TypeTable::SynType> ans;
	ans.insert(TypeTable::PLUS);
	CPPUNIT_ASSERT(sibling->getSiblingMathOpWithMathOp(TypeTable::MINUS) == ans);
	ans.insert(TypeTable::MINUS);
	CPPUNIT_ASSERT(sibling->getAllSiblingMathOpWithMathOp() == ans);

	sibling->setToSiblingMathOpMathOp(TypeTable::PLUS, TypeTable::TIMES);

	ans.clear();
	ans.insert(TypeTable::PLUS);
	ans.insert(TypeTable::TIMES);
	CPPUNIT_ASSERT(sibling->getSiblingMathOpWithMathOp(TypeTable::MINUS) == ans);

	ans.insert(TypeTable::MINUS);
	CPPUNIT_ASSERT(sibling->getAllSiblingMathOpWithMathOp() == ans);
	return;
}

void SiblingTest::testSiblingVarIndexStmtList() { 
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

	sibling->setToSiblingVarNameStmtList("first", 2);
	sibling->setToSiblingVarNameStmtList("first", 3);
	sibling->setToSiblingVarNameStmtList("first", 4);
	sibling->setToSiblingVarNameStmtList("fifth", 5);
	sibling->setToSiblingVarNameStmtList("fifth", 6);


	CPPUNIT_ASSERT(sibling->isSiblingVarIndexStmtList(one, 2) == true);
	CPPUNIT_ASSERT(sibling->isSiblingVarIndexStmtList(five, 6) == true);
	CPPUNIT_ASSERT(sibling->isSiblingVarIndexStmtList(one, 5) == false);
	CPPUNIT_ASSERT(sibling->isSiblingVarIndexStmtList(one, -1) == false);
	CPPUNIT_ASSERT(sibling->isSiblingVarIndexStmtList(one, 1000) == false);
	CPPUNIT_ASSERT(sibling->isSiblingVarIndexStmtList(one, 8) == false);
	CPPUNIT_ASSERT(sibling->isSiblingVarIndexStmtList(-1, 1) == false);
	CPPUNIT_ASSERT(sibling->isSiblingVarIndexStmtList(120, 1) == false);
	CPPUNIT_ASSERT(sibling->isSiblingVarIndexStmtList(-2,-1) == false);
	CPPUNIT_ASSERT(sibling->isSiblingVarIndexStmtList(0,-1) == false);

	set<int> ans;
	ans.insert(2);
	ans.insert(3);
	ans.insert(4);
	CPPUNIT_ASSERT(sibling->getSiblingStmtListWithVarIndex(one) == ans);

	ans.clear();
	ans.insert(5);
	ans.insert(6);
	CPPUNIT_ASSERT(sibling->getSiblingStmtListWithVarIndex(five) == ans);

	ans.clear();
	ans.insert(one);
	CPPUNIT_ASSERT(sibling->getSiblingVarIndexWithStmtList(2) == ans);

	ans.clear();
	CPPUNIT_ASSERT(sibling->getSiblingVarIndexWithStmtList(1) == ans);
	CPPUNIT_ASSERT(sibling->getSiblingVarIndexWithStmtList(8) == ans);
	CPPUNIT_ASSERT(sibling->getSiblingStmtListWithVarIndex(six) == ans);
	CPPUNIT_ASSERT(sibling->getSiblingStmtListWithVarIndex(two) == ans);

	ans.clear();
	ans.insert(one);
	ans.insert(five);
	CPPUNIT_ASSERT(sibling->getAllSiblingVarIndexWithStmtList() == ans);

	ans.clear();
	ans.insert(2);
	ans.insert(3);
	ans.insert(4);
	ans.insert(5);
	ans.insert(6);
	CPPUNIT_ASSERT(sibling->getAllSiblingStmtListWithVarIndex() == ans);
	return;
}

void SiblingTest::testSiblingStmtListStmtList() {  // Note 5
	
	sibling->setToSiblingStmtListStmtList(6, 7);
	sibling->setToSiblingStmtListStmtList(6, 8);
	sibling->setToSiblingStmtListStmtList(6, 9);
	sibling->setToSiblingStmtListStmtList(10, 11);
	sibling->setToSiblingStmtListStmtList(10, 12);
	sibling->setToSiblingStmtListStmtList(500, 502);
	sibling->setToSiblingStmtListStmtList(500, 600);
	sibling->setToSiblingStmtListStmtList(500, 1500);


	sibling->printSiblingTable();

	CPPUNIT_ASSERT(sibling->isSiblingStmtListStmtList(6, 7) == true);
	CPPUNIT_ASSERT(sibling->isSiblingStmtListStmtList(7, 6) == true);
	CPPUNIT_ASSERT(sibling->isSiblingStmtListStmtList(7, 9) == true);
	CPPUNIT_ASSERT(sibling->isSiblingStmtListStmtList(10, 11) == true);
	CPPUNIT_ASSERT(sibling->isSiblingStmtListStmtList(12, 11) == true);
	CPPUNIT_ASSERT(sibling->isSiblingStmtListStmtList(5, 6) == false);
	CPPUNIT_ASSERT(sibling->isSiblingStmtListStmtList(6, 10) == false);
	CPPUNIT_ASSERT(sibling->isSiblingStmtListStmtList(500, 502) == true);
	CPPUNIT_ASSERT(sibling->isSiblingStmtListStmtList(500, 600) == true);
	CPPUNIT_ASSERT(sibling->isSiblingStmtListStmtList(500, 1500) == true);
	CPPUNIT_ASSERT(sibling->isSiblingStmtListStmtList(500, 505) == false);
	CPPUNIT_ASSERT(sibling->isSiblingStmtListStmtList(500, 1499) == false);
	CPPUNIT_ASSERT(sibling->isSiblingStmtListStmtList(500, 1501) == false);
	CPPUNIT_ASSERT(sibling->isSiblingStmtListStmtList(500, -1) == false);
	CPPUNIT_ASSERT(sibling->isSiblingStmtListStmtList(-1,500) == false);

	set<int> ans;
	ans.insert(7);
	ans.insert(8);
	ans.insert(9);
	CPPUNIT_ASSERT(sibling->getSiblingStmtListWithStmtList(6) == ans);

	ans.clear();
	ans.insert(502);
	ans.insert(600);
	ans.insert(1500);
	CPPUNIT_ASSERT(sibling->getSiblingStmtListWithStmtList(500) == ans);

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
	CPPUNIT_ASSERT(sibling->getAllSiblingStmtListWithStmtList() == ans);
	return;
}



