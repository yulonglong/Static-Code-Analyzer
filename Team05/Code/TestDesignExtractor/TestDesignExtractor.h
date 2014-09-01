//@author Ipsita Mohapatra
//TestDesignExtractor.h

#ifndef TestDesignExtractor_h
#define TestDesignExtractor_h

// Note 1
#include <cppunit/extensions/HelperMacros.h>

class DesignExtractorTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE( DesignExtractorTest ); // Note 3 
	CPPUNIT_TEST( testFullDETestIn );
	// CPPUNIT_TEST( testCompleteParser );
	// CPPUNIT_TEST( testParserSource1 );
	// CPPUNIT_TEST( testParserSource2 );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testFullDETestIn();
	// void testFullDESource1();
	// void testFullDESource2();
	// void testFullDESourec3();
};
#endif
    