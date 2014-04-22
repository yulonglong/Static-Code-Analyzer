#include <cppunit/config/SourcePrefix.h>

#include "TestTypeTable.h"


#include <iostream>
#include <string>
#include <vector>

void 
TypeTableTest::setUp()
{
}

void 
TypeTableTest::tearDown()
{
}

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( TypeTableTest ); // Note 4 

void TypeTableTest::testConstructor()
{  // Note 5
	// create a student object
	TypeTable typeTable;
	return;
}

void TypeTableTest::testTableSet()
{
	TypeTable typeTable;

	typeTable.insertStmtNumAndType(0, TypeTable::WHILE);
	typeTable.insertStmtNumAndType(4, TypeTable::IF);
	typeTable.insertStmtNumAndType(15, TypeTable::WHILE);
	typeTable.insertStmtNumAndType(21, TypeTable::ASSIGN);

	vector<STMTNUM> expected;
	vector<STMTNUM> result;
	expected.push_back(4);
	result = typeTable.getAllStmts(TypeTable::IF);
	// verify that the assignment is correct - Note 7
	CPPUNIT_ASSERT_EQUAL(expected[0], result[0]);

	expected.clear();
	result.clear();
	expected.push_back(15);
	result = typeTable.getAllStmts(TypeTable::WHILE);
	CPPUNIT_ASSERT_EQUAL(expected[0], result[0]);
	CPPUNIT_ASSERT_EQUAL(expected[1], result[1]);

	expected.clear();
	result.clear();
	expected.push_back(21);
	result = typeTable.getAllStmts(TypeTable::ASSIGN);
	CPPUNIT_ASSERT_EQUAL(expected[0],result[0]);

	TypeTable::SynType expectedType;
	expectedType = TypeTable::WHILE;
	CPPUNIT_ASSERT_EQUAL(expectedType, typeTable.getType(0));
	expectedType = TypeTable::IF;
	CPPUNIT_ASSERT_EQUAL(expectedType, typeTable.getType(4));
	expectedType = TypeTable::WHILE;
	CPPUNIT_ASSERT_EQUAL(expectedType, typeTable.getType(15));
	expectedType = TypeTable::ASSIGN;
	CPPUNIT_ASSERT_EQUAL(expectedType, typeTable.getType(21));

	expected.clear();
	result.clear();
	result =  typeTable.getAllStmts(TypeTable::CALL);
	CPPUNIT_ASSERT_EQUAL(expected.size(), result.size());

	return;
}