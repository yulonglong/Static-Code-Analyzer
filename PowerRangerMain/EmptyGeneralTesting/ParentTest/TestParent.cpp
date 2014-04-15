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
	pkb->~PKB();
	pkb = new PKB();
	parent = Parent::getInstance();
	typeTable = TypeTable::getInstance();
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
	parent->setParent(6, 7);
	parent->setParent(6, 8);
	parent->setParent(6, 9);
	parent->setParent(10, 11);
	parent->setParent(10, 12);
	typeTable->insertStmtNumAndType(6, TypeTable::WHILE);
	typeTable->insertStmtNumAndType(7, TypeTable::ASSIGN);
	typeTable->insertStmtNumAndType(8, TypeTable::CALL);
	typeTable->insertStmtNumAndType(9, TypeTable::ASSIGN);
	typeTable->insertStmtNumAndType(10, TypeTable::IF);
	typeTable->insertStmtNumAndType(11, TypeTable::ASSIGN);
	typeTable->insertStmtNumAndType(12, TypeTable::ASSIGN);
	
	CPPUNIT_ASSERT(parent->isParent(TypeTable::WHILE, 9) == true);
	CPPUNIT_ASSERT(parent->isParent(TypeTable::IF, 12) == true);
	CPPUNIT_ASSERT(parent->isParent(TypeTable::WHILE, 5) == false);
	CPPUNIT_ASSERT(parent->isParent(TypeTable::CALL, 55) == false);
	return;
}

void ParentTest::testAllBoolean() {
	parent->setParent(6, 7);
	parent->setParent(6, 8);
	parent->setParent(6, 9);
	parent->setParent(10, 11);
	parent->setParent(10, 12);
	typeTable->insertStmtNumAndType(6, TypeTable::WHILE);
	typeTable->insertStmtNumAndType(7, TypeTable::ASSIGN);
	typeTable->insertStmtNumAndType(8, TypeTable::CALL);
	typeTable->insertStmtNumAndType(9, TypeTable::ASSIGN);
	typeTable->insertStmtNumAndType(10, TypeTable::IF);
	typeTable->insertStmtNumAndType(11, TypeTable::ASSIGN);
	typeTable->insertStmtNumAndType(12, TypeTable::ASSIGN);

	CPPUNIT_ASSERT(parent->isParent(TypeTable::WHILE, TypeTable::ASSIGN) == true);
	CPPUNIT_ASSERT(parent->isParent(TypeTable::WHILE, TypeTable::CALL) == true);
	CPPUNIT_ASSERT(parent->isParent(TypeTable::IF, TypeTable::ASSIGN) == true);
	CPPUNIT_ASSERT(parent->isParent(TypeTable::IF, TypeTable::CALL) == false);

	CPPUNIT_ASSERT(parent->isChildren(TypeTable::CALL, 6) == true);
	CPPUNIT_ASSERT(parent->isChildren(TypeTable::IF, 6) == false);
	CPPUNIT_ASSERT(parent->isChildren(TypeTable::ASSIGN, 10) == true);
	CPPUNIT_ASSERT(parent->isChildren(TypeTable::CALL, 10) == false);
	CPPUNIT_ASSERT(parent->isChildren(TypeTable::CALL, 55) == false);
	return;
}

void ParentTest::testGetParent() {
	parent->setParent(6, 7);
	parent->setParent(6, 8);
	parent->setParent(6, 9);
	parent->setParent(10, 11);
	parent->setParent(10, 12);
	typeTable->insertStmtNumAndType(6, TypeTable::WHILE);
	typeTable->insertStmtNumAndType(7, TypeTable::ASSIGN);
	typeTable->insertStmtNumAndType(8, TypeTable::CALL);
	typeTable->insertStmtNumAndType(9, TypeTable::ASSIGN);
	typeTable->insertStmtNumAndType(10, TypeTable::IF);
	typeTable->insertStmtNumAndType(11, TypeTable::ASSIGN);
	typeTable->insertStmtNumAndType(12, TypeTable::ASSIGN);

	CPPUNIT_ASSERT(parent->getParent(7) == 6);
	CPPUNIT_ASSERT(parent->getParent(12) == 10);
	CPPUNIT_ASSERT(parent->getParent(10) == -1);

	CPPUNIT_ASSERT(parent->getParent(TypeTable::WHILE,7) == 6);
	CPPUNIT_ASSERT(parent->getParent(TypeTable::IF,12) == 10);
	CPPUNIT_ASSERT(parent->getParent(TypeTable::WHILE,12) == -1);

	vector<int> ans (1,6);
	CPPUNIT_ASSERT(parent->getParent(TypeTable::WHILE,TypeTable::ASSIGN) == ans);
	ans.clear();
	ans.push_back(10);
	CPPUNIT_ASSERT(parent->getParent(TypeTable::IF,TypeTable::ASSIGN) == ans);
	ans.clear();
	ans.push_back(-1);
	CPPUNIT_ASSERT(parent->getParent(TypeTable::WHILE,TypeTable::WHILE) == ans);

	ans.clear();
	ans.push_back(6);
	CPPUNIT_ASSERT(parent->getParent(TypeTable::WHILE,TypeTable::WHILE,7) == ans);
	ans.clear();
	ans.push_back(7);
	ans.push_back(9);
	ans.push_back(11);
	ans.push_back(12);
	CPPUNIT_ASSERT(parent->getParent(TypeTable::ASSIGN,TypeTable::WHILE,7) == ans);
	ans.clear();
	ans.push_back(8);
	CPPUNIT_ASSERT(parent->getParent(TypeTable::CALL,TypeTable::IF,11) == ans);
	ans.clear();
	ans.push_back(-1);
	CPPUNIT_ASSERT(parent->getParent(TypeTable::WHILE,TypeTable::WHILE,12) == ans);
	CPPUNIT_ASSERT(parent->getParent(TypeTable::WHILE,TypeTable::WHILE,100) == ans);
	return;
}

void ParentTest::testGetChildren() {
	parent->setParent(6, 7);
	parent->setParent(6, 8);
	parent->setParent(6, 9);
	parent->setParent(10, 11);
	parent->setParent(10, 12);
	typeTable->insertStmtNumAndType(6, TypeTable::WHILE);
	typeTable->insertStmtNumAndType(7, TypeTable::ASSIGN);
	typeTable->insertStmtNumAndType(8, TypeTable::CALL);
	typeTable->insertStmtNumAndType(9, TypeTable::ASSIGN);
	typeTable->insertStmtNumAndType(10, TypeTable::IF);
	typeTable->insertStmtNumAndType(11, TypeTable::ASSIGN);
	typeTable->insertStmtNumAndType(12, TypeTable::ASSIGN);

	vector<int> ans (1,7);
	ans.push_back(8);
	ans.push_back(9);
	CPPUNIT_ASSERT(parent->getChildren(6) == ans);
	ans.clear();
	ans.push_back(-1);
	CPPUNIT_ASSERT(parent->getChildren(11) == ans);
	CPPUNIT_ASSERT(parent->getChildren(13) == ans);

	ans.clear();
	ans.push_back(7);
	ans.push_back(9);
	CPPUNIT_ASSERT(parent->getChildren(TypeTable::ASSIGN,6) == ans);
	ans.clear();
	ans.push_back(-1);
	CPPUNIT_ASSERT(parent->getChildren(TypeTable::IF,10) == ans);
	ans.clear();
	ans.push_back(-1);
	CPPUNIT_ASSERT(parent->getChildren(TypeTable::WHILE,12) == ans);

	ans.clear();
	ans.push_back(8);
	CPPUNIT_ASSERT(parent->getChildren(TypeTable::WHILE,TypeTable::CALL) == ans);
	ans.clear();
	ans.push_back(11);
	ans.push_back(12);
	CPPUNIT_ASSERT(parent->getChildren(TypeTable::IF,TypeTable::ASSIGN) == ans);
	ans.clear();
	ans.push_back(-1);
	CPPUNIT_ASSERT(parent->getChildren(TypeTable::WHILE,TypeTable::WHILE) == ans);

	ans.clear();
	ans.push_back(6);
	CPPUNIT_ASSERT(parent->getChildren(TypeTable::WHILE,TypeTable::CALL,6) == ans);
	ans.clear();
	ans.push_back(8);
	CPPUNIT_ASSERT(parent->getChildren(TypeTable::CALL,TypeTable::ASSIGN,10) == ans);
	ans.clear();
	ans.push_back(-1);
	CPPUNIT_ASSERT(parent->getChildren(TypeTable::WHILE,TypeTable::WHILE,12) == ans);
	CPPUNIT_ASSERT(parent->getChildren(TypeTable::WHILE,TypeTable::WHILE,13) == ans);
	return;
}

void ParentTest::testNew() {
	parent->setParent(6, 7);
	parent->setParent(6, 20);
	parent->setParent(20, 21);
	parent->setParent(6, 8);
	parent->setParent(6, 9);
	parent->setParent(10, 11);
	parent->setParent(10, 12);
	typeTable->insertStmtNumAndType(6, TypeTable::WHILE);
	typeTable->insertStmtNumAndType(7, TypeTable::ASSIGN);
	typeTable->insertStmtNumAndType(8, TypeTable::CALL);
	typeTable->insertStmtNumAndType(9, TypeTable::ASSIGN);
	typeTable->insertStmtNumAndType(10, TypeTable::IF);
	typeTable->insertStmtNumAndType(11, TypeTable::ASSIGN);
	typeTable->insertStmtNumAndType(12, TypeTable::ASSIGN);
	typeTable->insertStmtNumAndType(20, TypeTable::WHILE);
	typeTable->insertStmtNumAndType(21, TypeTable::WHILE);
	
	vector<int> ans (1,6);
	ans.push_back(20);
	CPPUNIT_ASSERT(parent->getParent(TypeTable::WHILE,TypeTable::WHILE) == ans);
	return;
}