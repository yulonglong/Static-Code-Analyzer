#ifndef TestSibling_h
#define TestSibling_h
#include "PKB.h"
#include "Sibling.h"

// Note 1
#include <cppunit/extensions/HelperMacros.h>

class SiblingTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE( SiblingTest ); // Note 3 
	CPPUNIT_TEST( testSiblingIsSibling );
	CPPUNIT_TEST( testSiblingGetSibling );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testSiblingIsSibling();
	void testSiblingGetSibling();
};
#endif
    