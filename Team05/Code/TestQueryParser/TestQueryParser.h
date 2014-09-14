//@author Steven Kester Yuwono
//TestQueryParser.h

#ifndef TestQueryParser_h
#define TestQueryParser_h

// Note 1
#include <cppunit/extensions/HelperMacros.h>

class QueryParserTest : public CPPUNIT_NS::TestFixture{ 
	CPPUNIT_TEST_SUITE( QueryParserTest );
	CPPUNIT_TEST(testQuerySelectOnly);
	CPPUNIT_TEST(testQueryAssignSelectModifies);
	CPPUNIT_TEST(testQueryAssignVariableSelectModifies);
	CPPUNIT_TEST(testQueryStmtSelectUses);
	CPPUNIT_TEST(testQueryStmtSelectParentStar);
	CPPUNIT_TEST(testQueryAssignSelectModifiesPattern);
	CPPUNIT_TEST(testQueryComplex1);
	CPPUNIT_TEST(testQueryFollows1);
	CPPUNIT_TEST(testQueryModifies1);
	CPPUNIT_TEST(testQueryModifies2);
	CPPUNIT_TEST(testQueryPattern1);
	CPPUNIT_TEST(testQueryWith1);
	CPPUNIT_TEST(testQueryWith2);
	CPPUNIT_TEST(testQueryWith3);
	CPPUNIT_TEST(testQueryValidationModifies1);
	CPPUNIT_TEST(testQueryValidationModifies2);
	CPPUNIT_TEST(testQueryValidationModifies3);
	CPPUNIT_TEST(testQueryValidationPattern1);
	CPPUNIT_TEST(testQueryValidationPattern2);
	CPPUNIT_TEST(testQueryValidationPattern3);
	CPPUNIT_TEST(testQueryValidationWith1);
	CPPUNIT_TEST(testQueryValidationWith2);
	CPPUNIT_TEST(testQueryValidationWith3);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testQuerySelectOnly();
	void testQueryAssignSelectModifies();
	void testQueryAssignVariableSelectModifies();
	void testQueryStmtSelectUses();
	void testQueryStmtSelectParentStar();
	void testQueryAssignSelectModifiesPattern();
	void testQueryComplex1();
	void testQueryFollows1();
	void testQueryModifies1();
	void testQueryModifies2();
	void testQueryPattern1();
	void testQueryWith1();
	void testQueryWith2();
	void testQueryWith3();
	void testQueryValidationModifies1();
	void testQueryValidationModifies2();
	void testQueryValidationModifies3();
	void testQueryValidationPattern1();
	void testQueryValidationPattern2();
	void testQueryValidationPattern3();
	void testQueryValidationWith1();
	void testQueryValidationWith2();
	void testQueryValidationWith3();
};
#endif
    