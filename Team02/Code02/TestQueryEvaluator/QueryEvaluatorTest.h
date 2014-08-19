#ifndef TestQueryEvaluator_h
#define TestQueryEvaluator_h

#include <cppunit/extensions/HelperMacros.h>

class QueryEvaluatorTest: public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( QueryEvaluatorTest );
	CPPUNIT_TEST( testEvaluateFollows );
	CPPUNIT_TEST( testEvaluateParent );
	CPPUNIT_TEST( testEvaluateModifies );
	CPPUNIT_TEST( testEvaluateUses );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testEvaluateFollows();
	void testEvaluateParent();
	void testEvaluateModifies();
	void testEvaluateUses();

};

#endif