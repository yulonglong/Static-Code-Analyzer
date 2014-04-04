#include <cppunit/config/SourcePrefix.h>
#include "PKB.h"
#include "TestFollows.h"

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
	
	followsTable->table.insertStmtNumAndType(1, TypeTable::ASSIGN);
	followsTable->table.insertStmtNumAndType(2, TypeTable::ASSIGN);
	followsTable->table.insertStmtNumAndType(3, TypeTable::CALL);
	followsTable->table.insertStmtNumAndType(5, TypeTable::ASSIGN);
	followsTable->table.insertStmtNumAndType(6, TypeTable::WHILE);
	followsTable->table.insertStmtNumAndType(10, TypeTable::IF);
	followsTable->table.insertStmtNumAndType(13, TypeTable::ASSIGN);

	CPPUNIT_ASSERT(followsTable->isFollows(TypeTable::WHILE, 5) == true);
	CPPUNIT_ASSERT(followsTable->isFollows(TypeTable::IF, 6) == true);
	CPPUNIT_ASSERT(followsTable->isFollows(TypeTable::ASSIGN, 1) == true);
	CPPUNIT_ASSERT(followsTable->isFollows(TypeTable::CALL, 2) == true);
	CPPUNIT_ASSERT(followsTable->isFollows(TypeTable::IF, 5) == false);
	CPPUNIT_ASSERT(followsTable->isFollows(TypeTable::WHILE, 10) == false);

	CPPUNIT_ASSERT(followsTable->isFollowedBy(TypeTable::ASSIGN, 6) == true);
	CPPUNIT_ASSERT(followsTable->isFollowedBy(TypeTable::WHILE, 10) == true);
	CPPUNIT_ASSERT(followsTable->isFollowedBy(TypeTable::ASSIGN, 12) == false); 
	CPPUNIT_ASSERT(followsTable->isFollowedBy(TypeTable::IF, 13) == true);
	
	CPPUNIT_ASSERT(followsTable->isFollows(TypeTable::ASSIGN, TypeTable::ASSIGN) == true);
	CPPUNIT_ASSERT(followsTable->isFollows(TypeTable::ASSIGN, TypeTable::WHILE) == true);
	CPPUNIT_ASSERT(followsTable->isFollows(TypeTable::WHILE, TypeTable::ASSIGN) == false);
	CPPUNIT_ASSERT(followsTable->isFollows(TypeTable::WHILE, TypeTable::STMT) == true);
	CPPUNIT_ASSERT(followsTable->isFollows(TypeTable::STMT, TypeTable::STMT) == true);
	CPPUNIT_ASSERT(followsTable->isFollows(TypeTable::STMT, TypeTable::IF) == true);
	CPPUNIT_ASSERT(followsTable->isFollows(TypeTable::ASSIGN, TypeTable::STMT) == true);

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
	
	followsTable->table.insertStmtNumAndType(1, TypeTable::ASSIGN);
	followsTable->table.insertStmtNumAndType(2, TypeTable::ASSIGN);
	followsTable->table.insertStmtNumAndType(3, TypeTable::CALL);
	followsTable->table.insertStmtNumAndType(5, TypeTable::ASSIGN);
	followsTable->table.insertStmtNumAndType(6, TypeTable::WHILE);
	followsTable->table.insertStmtNumAndType(10, TypeTable::IF);

	CPPUNIT_ASSERT(followsTable->getFollows(TypeTable::WHILE, 5) == 6);
	CPPUNIT_ASSERT(followsTable->getFollows(TypeTable::IF, 6) == 10);
	CPPUNIT_ASSERT(followsTable->getFollows(TypeTable::ASSIGN, 1) == 2);
	CPPUNIT_ASSERT(followsTable->getFollows(TypeTable::CALL, 2) == 3);
	CPPUNIT_ASSERT(followsTable->getFollows(TypeTable::ASSIGN, 6) == -1);

	CPPUNIT_ASSERT(followsTable->getFollowedBy(TypeTable::ASSIGN, 6) == 5);
	CPPUNIT_ASSERT(followsTable->getFollowedBy(TypeTable::WHILE, 10) == 6);
	CPPUNIT_ASSERT(followsTable->getFollowedBy(TypeTable::ASSIGN, 12) == -1);
	CPPUNIT_ASSERT(followsTable->getFollowedBy(TypeTable::IF, 13) == 10);	
	
	vector<STMTNUM> list = followsTable->getFollows(TypeTable::WHILE, TypeTable::IF); 
	CPPUNIT_ASSERT(list.size(), 1);	
	CPPUNIT_ASSERT(list.at(0), 6);	

	list = followsTable->getFollowedBy(TypeTable::WHILE, TypeTable::IF); 
	CPPUNIT_ASSERT(list.size() == 1);	
	CPPUNIT_ASSERT(list.at(0) == 10);	
	

	list = followsTable->getFollows(TypeTable::ASSIGN, TypeTable::WHILE); 
	CPPUNIT_ASSERT(list.size() == 1);	
	CPPUNIT_ASSERT(list.at(0) == 5);	

	list = followsTable->getFollowedBy(TypeTable::ASSIGN, TypeTable::WHILE); 
	CPPUNIT_ASSERT(list.size() == 1);	
	CPPUNIT_ASSERT(list.at(0) == 6);	
	
	/*
	cout << list.size() << endl;
	for (int i=0; i<list.size(); i++) {
		cout << list.at(i) << endl;
	}
	*/
	
	return;
}
