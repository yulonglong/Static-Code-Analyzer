#include <cppunit/config/SourcePrefix.h>
#include "PKB.h"
#include "TestFollows.h"

#include <iostream>
#include <string>
using namespace std;

class Follows;
TypeTable *typeTable;
Follows *follows; 
PKB *pkb;

void FollowsTest::setUp() {
	pkb = PKB::getInstance();
	follows = Follows::getInstance();
	typeTable = TypeTable::getInstance();
}

void FollowsTest::tearDown() {
	pkb->~PKB();
	pkb = new PKB();
	follows = Follows::getInstance();
	typeTable = TypeTable::getInstance();
}
	
// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( FollowsTest ); // Note 4 

void FollowsTest::testIsFollowsUsingStmtNum() {  // Note 5
	follows->setFollows(1, 2);
	follows->setFollows(2, 3);
	follows->setFollows(4, 5);
	follows->setFollows(5, 6);
	follows->setFollows(6, 10);
	follows->setFollows(10, 12);
	
	CPPUNIT_ASSERT(follows->isFollows(5, 6) == true);
	CPPUNIT_ASSERT(follows->isFollows(6, 7) == false);
	CPPUNIT_ASSERT(follows->isFollows(6, 10) == true);
	CPPUNIT_ASSERT(follows->isFollows(10, 11) == false);
	
	return;
}

void FollowsTest::testFollowsDestructor() {
	CPPUNIT_ASSERT(follows->isFollows(5, 6) == false);
}

void FollowsTest::testFollowsUsingStmtType() {
	follows->setFollows(1, 2);
	follows->setFollows(2, 3);
	follows->setFollows(4, 5);
	follows->setFollows(5, 6);
	follows->setFollows(7, 8);
	follows->setFollows(8, 9);
	follows->setFollows(6, 10);
	follows->setFollows(10, 13);
	follows->setFollows(13, 14);
	follows->setFollows(14, 15);
	follows->setFollows(16, 17);
	
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
	typeTable->insertStmtNumAndType(13, TypeTable::ASSIGN);
	typeTable->insertStmtNumAndType(14, TypeTable::ASSIGN);
	typeTable->insertStmtNumAndType(15, TypeTable::ASSIGN);
	typeTable->insertStmtNumAndType(16, TypeTable::ASSIGN);
	typeTable->insertStmtNumAndType(17, TypeTable::ASSIGN);

	CPPUNIT_ASSERT(follows->isFollows(TypeTable::WHILE, 5) == true);
	CPPUNIT_ASSERT(follows->isFollows(TypeTable::IF, 6) == true);
	CPPUNIT_ASSERT(follows->isFollows(TypeTable::ASSIGN, 1) == true);
	CPPUNIT_ASSERT(follows->isFollows(TypeTable::CALL, 2) == true);
	CPPUNIT_ASSERT(follows->isFollows(TypeTable::IF, 5) == false);
	CPPUNIT_ASSERT(follows->isFollows(TypeTable::WHILE, 10) == false);
	CPPUNIT_ASSERT(follows->isFollows(TypeTable::WHILE, 99) == false);

	CPPUNIT_ASSERT(follows->isFollowedBy(TypeTable::ASSIGN, 6) == true);
	CPPUNIT_ASSERT(follows->isFollowedBy(TypeTable::WHILE, 10) == true);
	CPPUNIT_ASSERT(follows->isFollowedBy(TypeTable::ASSIGN, 12) == false); 
	CPPUNIT_ASSERT(follows->isFollowedBy(TypeTable::IF, 13) == true);
	CPPUNIT_ASSERT(follows->isFollowedBy(TypeTable::WHILE, 987) == false);

	CPPUNIT_ASSERT(follows->isFollows(TypeTable::ASSIGN, TypeTable::ASSIGN) == true);
	CPPUNIT_ASSERT(follows->isFollows(TypeTable::ASSIGN, TypeTable::WHILE) == true);
	CPPUNIT_ASSERT(follows->isFollows(TypeTable::WHILE, TypeTable::ASSIGN) == false);
	CPPUNIT_ASSERT(follows->isFollows(TypeTable::WHILE, TypeTable::STMT) == true);
	CPPUNIT_ASSERT(follows->isFollows(TypeTable::STMT, TypeTable::STMT) == true);
	CPPUNIT_ASSERT(follows->isFollows(TypeTable::STMT, TypeTable::IF) == true);
	CPPUNIT_ASSERT(follows->isFollows(TypeTable::ASSIGN, TypeTable::STMT) == true);
	CPPUNIT_ASSERT(follows->isFollows(TypeTable::WHILE, TypeTable::WHILE) == false);

	return;
}


void FollowsTest::testGetFollowsUsingStmtType() {
	follows->setFollows(1, 2);
	follows->setFollows(2, 3);
	follows->setFollows(4, 5);
	follows->setFollows(5, 6);
	follows->setFollows(7, 8);
	follows->setFollows(8, 9);
	follows->setFollows(6, 10);
	follows->setFollows(10, 13);
	follows->setFollows(13, 14);
	follows->setFollows(14, 15);
	follows->setFollows(16, 17);
	
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
	typeTable->insertStmtNumAndType(13, TypeTable::ASSIGN);
	typeTable->insertStmtNumAndType(14, TypeTable::ASSIGN);
	typeTable->insertStmtNumAndType(15, TypeTable::ASSIGN);
	typeTable->insertStmtNumAndType(16, TypeTable::ASSIGN);
	typeTable->insertStmtNumAndType(17, TypeTable::ASSIGN);

	CPPUNIT_ASSERT(follows->getFollows(TypeTable::WHILE, 5) == 6);
	CPPUNIT_ASSERT(follows->getFollows(TypeTable::IF, 6) == 10);
	CPPUNIT_ASSERT(follows->getFollows(TypeTable::ASSIGN, 1) == 2);
	CPPUNIT_ASSERT(follows->getFollows(TypeTable::CALL, 2) == 3);
	CPPUNIT_ASSERT(follows->getFollows(TypeTable::ASSIGN, 6) == -1);
	CPPUNIT_ASSERT(follows->getFollows(TypeTable::ASSIGN, 99) == -1);
	
	CPPUNIT_ASSERT(follows->getFollowedBy(TypeTable::ASSIGN, 6) == 5);
	CPPUNIT_ASSERT(follows->getFollowedBy(TypeTable::WHILE, 10) == 6);
	CPPUNIT_ASSERT(follows->getFollowedBy(TypeTable::ASSIGN, 12) == -1);
	CPPUNIT_ASSERT(follows->getFollowedBy(TypeTable::IF, 13) == 10);
	CPPUNIT_ASSERT(follows->getFollowedBy(TypeTable::ASSIGN, 99) == -1);
	
	vector<STMTNUM> list = follows->getFollows(TypeTable::WHILE, TypeTable::IF); 
	CPPUNIT_ASSERT(list.size() == 1);	
	CPPUNIT_ASSERT(list.at(0) == 10);	
	
	list = follows->getFollowedBy(TypeTable::WHILE, TypeTable::IF); 
	CPPUNIT_ASSERT(list.size() == 1);	
	CPPUNIT_ASSERT(list.at(0) == 6);	
	

	list = follows->getFollows(TypeTable::ASSIGN, TypeTable::WHILE); 
	CPPUNIT_ASSERT(list.size() == 1);	
	CPPUNIT_ASSERT(list.at(0) == 6);	

	list = follows->getFollowedBy(TypeTable::ASSIGN, TypeTable::WHILE); 
	CPPUNIT_ASSERT(list.size() == 1);	
	CPPUNIT_ASSERT(list.at(0) == 5);	
	
	return;
}
