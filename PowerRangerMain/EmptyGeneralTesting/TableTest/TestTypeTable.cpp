#include <cppunit/config/SourcePrefix.h>
#include "TypeTable.h"
#include "TestTypeTable.h"

#include <iostream>
#include <string>

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

	typeTable.insertStmtNumAndType(0, WHILE);
	typeTable.insertStmtNumAndType(4, IF);
	typeTable.insertStmtNumAndType(15, WHILE);
	typeTable.insertStmtNumAndType(21, ASSIGN);

	LIST expected;
	LIST result;
	expected.push_back(4);
	result = typeTable.getStmtNum(IF);
	// verify that the assignment is correct - Note 7
	CPPUNIT_ASSERT_EQUAL(expected[0], result[0]);

	expected.clear();
	result.clear();
	expected.push_back(0);
	expected.push_back(15);
	result = typeTable.getStmtNum(WHILE);
	CPPUNIT_ASSERT_EQUAL(expected[0], result[0]);
	CPPUNIT_ASSERT_EQUAL(expected[1], result[1]);

	expected.clear();
	result.clear();
	expected.push_back(21);
	result = typeTable.getStmtNum(ASSIGN);
	CPPUNIT_ASSERT_EQUAL(expected[0],result[0]);

	STYPE expectedType;
	expectedType = WHILE;
	CPPUNIT_ASSERT_EQUAL(expectedType, typeTable.getType(0));
	expectedType = IF;
	CPPUNIT_ASSERT_EQUAL(expectedType, typeTable.getType(4));
	expectedType = WHILE;
	CPPUNIT_ASSERT_EQUAL(expectedType, typeTable.getType(15));
	expectedType = ASSIGN;
	CPPUNIT_ASSERT_EQUAL(expectedType, typeTable.getType(21));

	expected.clear();
	result.clear();
	result =  typeTable.getStmtNum(CALL);
	CPPUNIT_ASSERT_EQUAL(expected.size(), result.size());

	return;
}