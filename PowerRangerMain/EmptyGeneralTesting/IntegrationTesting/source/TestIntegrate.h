#ifndef TestIntegrate_h
#define TestIntegrate_h

// Note 1
#include <cppunit/extensions/HelperMacros.h>

class IntegrateTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE( IntegrateTest ); // Note 3 
	CPPUNIT_TEST( testModifyTable );
	CPPUNIT_TEST( testCompleteParser );
	CPPUNIT_TEST( testParserSource1 );
	CPPUNIT_TEST( testParserSource2 );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	// method to test the constructor
	void testModifyTable();

	// method to test the assigning and retrieval of grades
	void testCompleteParser();
	void testParserSource1();
	void testParserSource2();
};
#endif
    