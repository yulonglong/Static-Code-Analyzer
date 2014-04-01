#include <cppunit/config/SourcePrefix.h>

#include "TestTypeTable.h"
#include "TypeTable.h"

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

	typeTable.insertStmtNumAndType(0, Query::WHILE);
	typeTable.insertStmtNumAndType(4, Query::IF);
	typeTable.insertStmtNumAndType(15, Query::WHILE);
	typeTable.insertStmtNumAndType(21, Query::ASSIGN);

	vector<STMTNUM> expected;
	vector<STMTNUM> result;
	expected.push_back(4);
	result = typeTable.getAllStmts(Query::IF);
	// verify that the assignment is correct - Note 7
	CPPUNIT_ASSERT_EQUAL(expected[0], result[0]);

	expected.clear();
	result.clear();
	expected.push_back(0);
	expected.push_back(15);
	result = typeTable.getAllStmts(Query::WHILE);
	CPPUNIT_ASSERT_EQUAL(expected[0], result[0]);
	CPPUNIT_ASSERT_EQUAL(expected[1], result[1]);

	expected.clear();
	result.clear();
	expected.push_back(21);
	result = typeTable.getAllStmts(Query::ASSIGN);
	CPPUNIT_ASSERT_EQUAL(expected[0],result[0]);

	Query::SynType expectedType;
	expectedType = Query::WHILE;
	CPPUNIT_ASSERT_EQUAL(expectedType, typeTable.getType(0));
	expectedType = Query::IF;
	CPPUNIT_ASSERT_EQUAL(expectedType, typeTable.getType(4));
	expectedType = Query::WHILE;
	CPPUNIT_ASSERT_EQUAL(expectedType, typeTable.getType(15));
	expectedType = Query::ASSIGN;
	CPPUNIT_ASSERT_EQUAL(expectedType, typeTable.getType(21));

	expected.clear();
	result.clear();
	result =  typeTable.getAllStmts(Query::CALL);
	CPPUNIT_ASSERT_EQUAL(expected.size(), result.size());

	return;
}