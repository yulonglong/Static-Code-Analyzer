//@author Steven Kester Yuwono
//TestQueryParser.h

#ifndef TestQueryParser_h
#define TestQueryParser_h

// Note 1
#include <cppunit/extensions/HelperMacros.h>

class QueryParserTest : public CPPUNIT_NS::TestFixture{ 
	CPPUNIT_TEST_SUITE( QueryParserTest );
	CPPUNIT_TEST(testQuerySelectOnly);
	CPPUNIT_TEST(testQuerySelectOnly2);
	CPPUNIT_TEST(testQuerySelectOnly3);
	CPPUNIT_TEST(testQueryAssignSelectModifies);
	CPPUNIT_TEST(testQueryAssignVariableSelectModifies);
	CPPUNIT_TEST(testQueryStmtSelectUses);
	CPPUNIT_TEST(testQueryStmtSelectParentStar);
	CPPUNIT_TEST(testQueryAssignSelectModifiesPattern);
	CPPUNIT_TEST(testQueryComplex1);
	CPPUNIT_TEST(testQueryFollows1);
	CPPUNIT_TEST(testQueryModifies1);
	CPPUNIT_TEST(testQueryModifies2);
	CPPUNIT_TEST(testQueryParent1);
	CPPUNIT_TEST(testQueryCallStar1);
	CPPUNIT_TEST(testQueryPattern1);
	CPPUNIT_TEST(testQueryPattern2);
	CPPUNIT_TEST(testQueryPatternWhile1);
	CPPUNIT_TEST(testQueryPatternIf1);
	CPPUNIT_TEST(testQueryWith1);
	CPPUNIT_TEST(testQueryWith2);
	CPPUNIT_TEST(testQueryWith3);
	CPPUNIT_TEST(testQueryWith4);
	CPPUNIT_TEST(testQueryWith5);
	CPPUNIT_TEST(testQueryWith6);
	CPPUNIT_TEST(testQueryMultipleSuchThat);
	CPPUNIT_TEST(testQueryMultipleWith);
	CPPUNIT_TEST(testQueryMultipleWith2);
	CPPUNIT_TEST(testQueryMultiplePattern);
	CPPUNIT_TEST(testQueryMultiplePatternAndWith);
	CPPUNIT_TEST(testQueryMultipleSuchThatAndPatternAndWith);
	CPPUNIT_TEST(testQueryTupleModifies);
	CPPUNIT_TEST(testQueryTupleUses);
	CPPUNIT_TEST(testQueryValidationTuple);
	CPPUNIT_TEST(testQueryValidationModifies1);
	CPPUNIT_TEST(testQueryValidationModifies2);
	CPPUNIT_TEST(testQueryValidationModifies3);
	CPPUNIT_TEST(testQueryValidationPattern1);
	CPPUNIT_TEST(testQueryValidationPattern2);
	CPPUNIT_TEST(testQueryValidationPattern3);
	CPPUNIT_TEST(testQueryValidationPatternWhile1);
	CPPUNIT_TEST(testQueryValidationPatternIf1);
	CPPUNIT_TEST(testQueryValidationPatternIf2);
	CPPUNIT_TEST(testQueryValidationWith1);
	CPPUNIT_TEST(testQueryValidationWith2);
	CPPUNIT_TEST(testQueryValidationWith3);
	CPPUNIT_TEST(testQueryValidationWith4);
	CPPUNIT_TEST(testQuerySemanticSelect);
	CPPUNIT_TEST(testQuerySemanticModifies);
	CPPUNIT_TEST(testQuerySemanticUses);
	CPPUNIT_TEST(testQuerySemanticCalls);
	CPPUNIT_TEST(testQuerySemanticCallsStar);
	CPPUNIT_TEST(testQuerySemanticParent);
	CPPUNIT_TEST(testQuerySemanticParentStar);
	CPPUNIT_TEST(testQuerySemanticNext);
	CPPUNIT_TEST(testQuerySemanticNextStar);
	CPPUNIT_TEST(testQuerySemanticAffects);
	CPPUNIT_TEST(testQuerySemanticAffectsStar);
	CPPUNIT_TEST(testQBasic1F_invalid_queries);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testQuerySelectOnly();
	void testQuerySelectOnly2();
	void testQuerySelectOnly3();
	void testQueryAssignSelectModifies();
	void testQueryAssignVariableSelectModifies();
	void testQueryStmtSelectUses();
	void testQueryStmtSelectParentStar();
	void testQueryAssignSelectModifiesPattern();
	void testQueryComplex1();
	void testQueryFollows1();
	void testQueryModifies1();
	void testQueryModifies2();
	void testQueryParent1();
	void testQueryCallStar1();
	void testQueryPattern1();
	void testQueryPattern2();
	void testQueryPatternWhile1();
	void testQueryPatternIf1();
	void testQueryWith1();
	void testQueryWith2();
	void testQueryWith3();
	void testQueryWith4();
	void testQueryWith5();
	void testQueryWith6();
	void testQueryMultipleSuchThat();
	void testQueryMultipleWith();
	void testQueryMultipleWith2();
	void testQueryMultiplePattern();
	void testQueryMultiplePatternAndWith();
	void testQueryMultipleSuchThatAndPatternAndWith();
	void testQueryTupleModifies();
	void testQueryTupleUses();
	void testQueryValidationTuple();
	void testQueryValidationModifies1();
	void testQueryValidationModifies2();
	void testQueryValidationModifies3();
	void testQueryValidationPattern1();
	void testQueryValidationPattern2();
	void testQueryValidationPattern3();
	void testQueryValidationPatternWhile1();
	void testQueryValidationPatternIf1();
	void testQueryValidationPatternIf2();
	void testQueryValidationWith1();
	void testQueryValidationWith2();
	void testQueryValidationWith3();
	void testQueryValidationWith4();
	void testQuerySemanticSelect();
	void testQuerySemanticModifies();
	void testQuerySemanticUses();
	void testQuerySemanticCalls();
	void testQuerySemanticCallsStar();
	void testQuerySemanticParent();
	void testQuerySemanticParentStar();
	void testQuerySemanticNext();
	void testQuerySemanticNextStar();
	void testQuerySemanticAffects();
	void testQuerySemanticAffectsStar();
	void testQBasic1F_invalid_queries();
};
#endif
    