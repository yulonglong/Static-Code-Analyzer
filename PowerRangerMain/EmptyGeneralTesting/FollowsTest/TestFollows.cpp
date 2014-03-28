#include <cppunit/config/SourcePrefix.h>
#include "Follows.h"
#include "TestFollows.h"

#include <iostream>
#include <string>
using namespace std;


class Follows;
Follows* followsTable; 

void FollowsTest::setUp()
{
	
	followsTable = new Follows();

}

void FollowsTest::tearDown()
{
	followsTable->~Follows(); 
}
	
// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( FollowsTest ); // Note 4 

void FollowsTest::testIsFollowsUsingStmtNum()
{  // Note 5
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

void FollowsTest::testIsFollowsUsingStmtType()
{
	
	return;
}