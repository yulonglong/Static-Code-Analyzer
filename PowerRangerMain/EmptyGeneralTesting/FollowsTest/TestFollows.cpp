#include <cppunit/config/SourcePrefix.h>
#include "Follows.h"
#include "TestFollows.h"
#include "Query.h"

#include <iostream>
#include <string>
using namespace std;


class Follows;
Follows* followsTable; 

void FollowsTest::setUp() {
	followsTable = new Follows();

}

void FollowsTest::tearDown() {
	followsTable->~Follows(); 
}
	
// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( FollowsTest ); // Note 4 

void FollowsTest::testIsFollowsUsingStmtNum() {  // Note 5
	followsTable->setFollows(1, 2);
	followsTable->setFollows(2, 3);
	followsTable->setFollows(4, 5);
	followsTable->setFollows(5, 6);
	followsTable->setFollows(6, 10);
	followsTable->setFollows(10, 12);
	
	CPPUNIT_ASSERT(followsTable->isFollows(5, 6) == true);
	CPPUNIT_ASSERT(followsTable->isFollows(6, 7) == false);
	CPPUNIT_ASSERT(followsTable->isFollows(6, 10) == true);
	CPPUNIT_ASSERT(followsTable->isFollows(10, 11) == false);
	
	return;
}

void FollowsTest::testFollowsDestructor() {
	CPPUNIT_ASSERT(followsTable->isFollows(5, 6) == false);
}

void FollowsTest::testFollowsUsingStmtType() {
	followsTable->setFollows(1, 2);
	followsTable->setFollows(2, 3);
	followsTable->setFollows(4, 5);
	followsTable->setFollows(5, 6);
	followsTable->setFollows(7, 8);
	followsTable->setFollows(8, 9);
	followsTable->setFollows(6, 10);
	followsTable->setFollows(10, 13);
	followsTable->setFollows(13, 14);
	followsTable->setFollows(14, 15);
	followsTable->setFollows(16, 17);
	
	followsTable->table.insertStmtNumAndType(1, Query::ASSIGN);
	followsTable->table.insertStmtNumAndType(2, Query::ASSIGN);
	followsTable->table.insertStmtNumAndType(3, Query::CALL);
	followsTable->table.insertStmtNumAndType(5, Query::ASSIGN);
	followsTable->table.insertStmtNumAndType(6, Query::WHILE);
	followsTable->table.insertStmtNumAndType(10, Query::IF);

	CPPUNIT_ASSERT(followsTable->isFollows(Query::WHILE, 5) == true);
	CPPUNIT_ASSERT(followsTable->isFollows(Query::IF, 6) == true);
	CPPUNIT_ASSERT(followsTable->isFollows(Query::ASSIGN, 1) == true);
	CPPUNIT_ASSERT(followsTable->isFollows(Query::CALL, 2) == true);

	CPPUNIT_ASSERT(followsTable->isFollowedBy(Query::ASSIGN, 6) == true);
	CPPUNIT_ASSERT(followsTable->isFollowedBy(Query::WHILE, 10) == true);
	// need exception handling in getFollowedBy
	// CPPUNIT_ASSERT(followsTable->isFollowedBy(Query::ASSIGN, 12) == false);
	CPPUNIT_ASSERT(followsTable->isFollowedBy(Query::IF, 13) == true);

	return;
}


void FollowsTest::testGetFollowsUsingStmtType() {
	followsTable->setFollows(1, 2);
	followsTable->setFollows(2, 3);
	followsTable->setFollows(4, 5);
	followsTable->setFollows(5, 6);
	followsTable->setFollows(7, 8);
	followsTable->setFollows(8, 9);
	followsTable->setFollows(6, 10);
	followsTable->setFollows(10, 13);
	followsTable->setFollows(13, 14);
	followsTable->setFollows(14, 15);
	followsTable->setFollows(16, 17);
	
	followsTable->table.insertStmtNumAndType(1, Query::ASSIGN);
	followsTable->table.insertStmtNumAndType(2, Query::ASSIGN);
	followsTable->table.insertStmtNumAndType(3, Query::CALL);
	followsTable->table.insertStmtNumAndType(5, Query::ASSIGN);
	followsTable->table.insertStmtNumAndType(6, Query::WHILE);
	followsTable->table.insertStmtNumAndType(10, Query::IF);

	CPPUNIT_ASSERT(followsTable->getFollows(Query::WHILE, 5) == 6);
	CPPUNIT_ASSERT(followsTable->getFollows(Query::IF, 6) == 10);
	CPPUNIT_ASSERT(followsTable->getFollows(Query::ASSIGN, 1) == 2);
	CPPUNIT_ASSERT(followsTable->getFollows(Query::CALL, 2) == 3);
	CPPUNIT_ASSERT(followsTable->getFollows(Query::ASSIGN, 6) == -1);

	CPPUNIT_ASSERT(followsTable->getFollowedBy(Query::ASSIGN, 6) == 5);
	CPPUNIT_ASSERT(followsTable->getFollowedBy(Query::WHILE, 10) == 6);
	// need exception handling in getFollowedBy
	// CPPUNIT_ASSERT(followsTable->getFollowedBy(Query::ASSIGN, 12) == -1);
	CPPUNIT_ASSERT(followsTable->getFollowedBy(Query::IF, 13) == 10);	
	return;
}
