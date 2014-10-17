#include <cppunit/config/SourcePrefix.h>
#include "TestParent.h"

#include <iostream>
#include <string>
using namespace std;

class Parent;
Parent *parent; 
PKB *pkb;

void ParentTest::setUp() {
	pkb = PKB::getInstance();
	parent = Parent::getInstance();

	parent->setParent(6, 7);
	parent->setParent(6, 8);
	parent->setParent(6, 9);
	parent->setParent(10, 11);
	parent->setParent(10, 12);
	parent->setParent(500, 502);
	parent->setParent(500, 600);
	parent->setParent(500, 1500);
}

void ParentTest::tearDown() {
	pkb->~PKB();
	pkb = PKB::getInstance();
	parent = Parent::getInstance();
}

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( ParentTest ); // Note 4 

void ParentTest::testParentIsParent() {  // Note 5

	parent->printParentTable();

	CPPUNIT_ASSERT(parent->isParent(6, 7) == true);
	CPPUNIT_ASSERT(parent->isParent(10, 11) == true);
	CPPUNIT_ASSERT(parent->isParent(5, 6) == false);
	CPPUNIT_ASSERT(parent->isParent(6, 10) == false);
	CPPUNIT_ASSERT(parent->isParent(500, 502) == true);
	CPPUNIT_ASSERT(parent->isParent(500, 600) == true);
	CPPUNIT_ASSERT(parent->isParent(500, 1500) == true);
	CPPUNIT_ASSERT(parent->isParent(500, 505) == false);
	CPPUNIT_ASSERT(parent->isParent(500, 1499) == false);
	CPPUNIT_ASSERT(parent->isParent(500, 1501) == false);
	CPPUNIT_ASSERT(parent->isParent(500, -1) == false);
	CPPUNIT_ASSERT(parent->isParent(-1,500) == false);
	return;
}

void ParentTest::testParentGetAllChildrenParent() {  
	set<int> ans;
	ans.insert(7);
	ans.insert(8);
	ans.insert(9);
	CPPUNIT_ASSERT(parent->getChildren(6) == ans);

	ans.clear();
	ans.insert(502);
	ans.insert(600);
	ans.insert(1500);
	CPPUNIT_ASSERT(parent->getChildren(500) == ans);

	ans.clear();
	ans.insert(6);
	ans.insert(10);
	ans.insert(500);
	CPPUNIT_ASSERT(parent->getAllParent() == ans);

	ans.clear();
	ans.insert(7);
	ans.insert(8);
	ans.insert(9);
	ans.insert(11);
	ans.insert(12);
	ans.insert(502);
	ans.insert(600);
	ans.insert(1500);
	CPPUNIT_ASSERT(parent->getAllChildren() == ans);
	return;
}