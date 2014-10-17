#include <cppunit/config/SourcePrefix.h>

#include "TestFollows.h"

#include <iostream>
#include <string>
using namespace std;

Follows* follows; 
PKB* pkb;

void FollowsTest::setUp() {
	pkb = PKB::getInstance();
	follows = Follows::getInstance();

	follows->setFollows(1, 2);
	follows->setFollows(2, 3);
	follows->setFollows(4, 5);
	follows->setFollows(5, 6);
	follows->setFollows(6, 10);
	follows->setFollows(10, 12);
}

void FollowsTest::tearDown() {
	pkb->~PKB();
	pkb = PKB::getInstance();
	follows = Follows::getInstance();
}
	
// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( FollowsTest ); // Note 4 

void FollowsTest::testIsFollows() {  // Note 5
	follows->printFollowsTable();
	
	CPPUNIT_ASSERT(follows->isFollows(5, 6) == true);
	CPPUNIT_ASSERT(follows->isFollows(6, 7) == false);
	CPPUNIT_ASSERT(follows->isFollows(6, 10) == true);
	CPPUNIT_ASSERT(follows->isFollows(10, 11) == false);
	CPPUNIT_ASSERT(follows->isFollows(10, 25) == false);
	CPPUNIT_ASSERT(follows->isFollows(102, 113) == false);
	CPPUNIT_ASSERT(follows->isFollows(-1, -1) == false);
	return;
}

void FollowsTest::testGetFollows() {
	CPPUNIT_ASSERT(follows->getFollows(0) == -1);
	CPPUNIT_ASSERT(follows->getFollows(1) == 2);
	CPPUNIT_ASSERT(follows->getFollows(2) == 3);
	CPPUNIT_ASSERT(follows->getFollows(12) == -1);
	CPPUNIT_ASSERT(follows->getFollows(15) == -1);

	CPPUNIT_ASSERT(follows->getFollowedBy(0) == -1);
	CPPUNIT_ASSERT(follows->getFollowedBy(1) == -1);
	CPPUNIT_ASSERT(follows->getFollowedBy(3) == 2);
	CPPUNIT_ASSERT(follows->getFollowedBy(5) == 4);
	CPPUNIT_ASSERT(follows->getFollowedBy(12) == 10);
	CPPUNIT_ASSERT(follows->getFollowedBy(13) == -1);

	set<int> ans;
	ans.insert(1);
	ans.insert(2);
	ans.insert(4);
	ans.insert(5);
	ans.insert(6);
	ans.insert(10);
	CPPUNIT_ASSERT(follows->getAllFollows() == ans);

	ans.clear();
	ans.insert(2);
	ans.insert(3);
	ans.insert(5);
	ans.insert(6);
	ans.insert(10);
	ans.insert(12);
	CPPUNIT_ASSERT(follows->getAllFollowedBy() == ans);
}

