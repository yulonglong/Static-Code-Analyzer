#ifndef TestParent_h
#define TestParent_h
#include "PKB.h"
#include "Parent.h"

// Note 1
#include <cppunit/extensions/HelperMacros.h>

class ParentTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE( ParentTest ); // Note 3 
	CPPUNIT_TEST( testParentIsParent );
	CPPUNIT_TEST( testParentGetAllChildrenParent );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testParentIsParent();
	void testParentGetAllChildrenParent();
};
#endif
    