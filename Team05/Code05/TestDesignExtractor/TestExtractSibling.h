//@author Ipsita Mohapatra
//TestExtractSibling_h

#ifndef TestExtractSibling_h
#define TestExtractSibling_h

// Note 1
#include <cppunit/extensions/HelperMacros.h>

class ExtractSiblingTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE( ExtractSiblingTest ); // Note 3 

	CPPUNIT_TEST( testSource1B );
	CPPUNIT_TEST( testSourceDE5 );
	CPPUNIT_TEST( testSourceSibling );

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testSource1B(); 
	void testSourceDE5();
	void testSourceSibling();
};
#endif
    