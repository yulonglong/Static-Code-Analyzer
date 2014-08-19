#ifndef TestQueryParser_h
#define TestQueryParser_h

// Note 1
#include <cppunit/extensions/HelperMacros.h>

class QueryParserTest : public CPPUNIT_NS::TestFixture{ 
	CPPUNIT_TEST_SUITE( QueryParserTest );
	CPPUNIT_TEST(testQueryAssignSelectModifies);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testQueryAssignSelectModifies();
};
#endif
    