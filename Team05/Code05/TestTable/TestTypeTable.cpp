#include <cppunit/config/SourcePrefix.h>

#include "TestTypeTable.h"


#include <iostream>
#include <string>
#include <vector>

TypeTable* typeTable;

void TypeTableTest::setUp(){
	typeTable = typeTable->getInstance();
}

void TypeTableTest::tearDown() {
	typeTable->~TypeTable();
	typeTable = typeTable->getInstance();
}

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( TypeTableTest ); // Note 4 

void TypeTableTest::testTableSet() {
	typeTable->insertStmtNumAndType(0, TypeTable::WHILE);
	typeTable->insertStmtNumAndType(4, TypeTable::IF);
	typeTable->insertStmtNumAndType(15, TypeTable::WHILE);
	typeTable->insertStmtNumAndType(21, TypeTable::ASSIGN);
	typeTable->insertStmtNumAndType(22, TypeTable::WHILE);

	set<STMTNUM> expected;
	set<STMTNUM> result;
	expected.insert(4);
	result = typeTable->getAllStmts(TypeTable::IF);
	// verify that the assignment is correct - Note 7
	CPPUNIT_ASSERT(expected==result);

	expected.clear();
	result.clear();
	expected.insert(15);
	expected.insert(22);
	result = typeTable->getAllStmts(TypeTable::WHILE);
	CPPUNIT_ASSERT(expected==result);

	expected.clear();
	result.clear();
	expected.insert(21);
	result = typeTable->getAllStmts(TypeTable::ASSIGN);
	CPPUNIT_ASSERT(expected==result);

	TypeTable::SynType expectedType;
	expectedType = TypeTable::WHILE;
	CPPUNIT_ASSERT_EQUAL(expectedType, typeTable->getType(0));
	expectedType = TypeTable::IF;
	CPPUNIT_ASSERT_EQUAL(expectedType, typeTable->getType(4));
	expectedType = TypeTable::WHILE;
	CPPUNIT_ASSERT_EQUAL(expectedType, typeTable->getType(15));
	expectedType = TypeTable::ASSIGN;
	CPPUNIT_ASSERT_EQUAL(expectedType, typeTable->getType(21));

	expected.clear();
	result.clear();
	result =  typeTable->getAllStmts(TypeTable::CALL);
	CPPUNIT_ASSERT(expected.size()== result.size());

	result =  typeTable->getAllStmts(TypeTable::WHILE);
	CPPUNIT_ASSERT(2== result.size());

	CPPUNIT_ASSERT(typeTable->getStmtRange()==22);

	return;
}