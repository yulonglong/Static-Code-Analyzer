#ifndef TestParser_h
#define TestParser_h

// Note 1
#include <cppunit/extensions/HelperMacros.h>

class QueryParserTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE( QueryParserTest ); // Note 3 
	CPPUNIT_TEST( testModifyTable );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	// method to test the constructor
	void testModifyTable();
};
#endif
    