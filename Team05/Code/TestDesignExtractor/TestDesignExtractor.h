//@author Ipsita Mohapatra
//TestDesignExtractor.h

#ifndef TestDesignExtractor_h
#define TestDesignExtractor_h

// Note 1
#include <cppunit/extensions/HelperMacros.h>

class DesignExtractorTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE( DesignExtractorTest ); // Note 3 
	CPPUNIT_TEST( testExtractRelationshipsSourceDE1 );
	// CPPUNIT_TEST( testExtractRelationshipsSourceDE2 );
	// CPPUNIT_TEST( testFullDesignExtractor );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testExtractRelationshipsSourceDE1(); 
	void testExtractRelationshipsSourceDE2(); 
	void testFullDesignExtractor();
};
#endif
    