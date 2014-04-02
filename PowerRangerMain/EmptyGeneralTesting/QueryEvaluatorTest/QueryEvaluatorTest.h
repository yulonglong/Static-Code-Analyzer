#ifndef TestQueryEvaluator_h
#define TestQueryEvaluator_h

#include <cppunit/extensions/HelperMacros.h>

class QueryEvaluatorTest: public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( QueryEvaluatorTest );
	CPPUNIT_TEST( testEvaluateFollows );
	CPPUNIT_TEST( testEvaluateFollowsBoolean );
	CPPUNIT_TEST( testEvaluateParent );
	CPPUNIT_TEST( testEvaluateParentBoolean );
	CPPUNIT_TEST( testIntersectAnswers );
	CPPUNIT_TEST( testEvaluateQueryBoolean );
	CPPUNIT_TEST( testEvaluateQuery );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testEvaluateFollows();
	void testEvaluateFollowsBoolean();
	void testEvaluateParent();
	void testEvaluateParentBoolean();
	void testIntersectAnswers();
	void testEvaluateQueryBoolean();
	void testEvaluateQuery();

};
#endif