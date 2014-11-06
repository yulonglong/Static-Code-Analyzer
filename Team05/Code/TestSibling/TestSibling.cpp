#include <cppunit/config/SourcePrefix.h>
#include "TestSibling.h"

#include <iostream>
#include <string>
using namespace std;

class Sibling;
Sibling *sibling; 
PKB *pkb;

void SiblingTest::setUp() {
	pkb = PKB::getInstance();
	sibling = Sibling::getInstance();

	sibling->setSibling(6, 7);
	sibling->setSibling(6, 8);
	sibling->setSibling(6, 9);
	sibling->setSibling(10, 11);
	sibling->setSibling(10, 12);
	sibling->setSibling(500, 502);
	sibling->setSibling(500, 600);
	sibling->setSibling(500, 1500);
}

void SiblingTest::tearDown() {
	pkb->~PKB();
	pkb = PKB::getInstance();
	sibling = Sibling::getInstance();
}

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( SiblingTest ); // Note 4 

void SiblingTest::testSiblingIsSibling() {  // Note 5

	sibling->printSiblingTable();

	CPPUNIT_ASSERT(sibling->isSibling(6, 7) == true);
	CPPUNIT_ASSERT(sibling->isSibling(10, 11) == true);
	CPPUNIT_ASSERT(sibling->isSibling(5, 6) == false);
	CPPUNIT_ASSERT(sibling->isSibling(6, 10) == false);
	CPPUNIT_ASSERT(sibling->isSibling(500, 502) == true);
	CPPUNIT_ASSERT(sibling->isSibling(500, 600) == true);
	CPPUNIT_ASSERT(sibling->isSibling(500, 1500) == true);
	CPPUNIT_ASSERT(sibling->isSibling(500, 505) == false);
	CPPUNIT_ASSERT(sibling->isSibling(500, 1499) == false);
	CPPUNIT_ASSERT(sibling->isSibling(500, 1501) == false);
	CPPUNIT_ASSERT(sibling->isSibling(500, -1) == false);
	CPPUNIT_ASSERT(sibling->isSibling(-1,500) == false);
	return;
}

void SiblingTest::testSiblingGetSibling() {  
	set<int> ans;
	ans.insert(7);
	ans.insert(8);
	ans.insert(9);
	CPPUNIT_ASSERT(sibling->getSibling(6) == ans);

	ans.clear();
	ans.insert(502);
	ans.insert(600);
	ans.insert(1500);
	CPPUNIT_ASSERT(sibling->getSibling(500) == ans);

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
	CPPUNIT_ASSERT(sibling->getAllSibling() == ans);

	return;
}