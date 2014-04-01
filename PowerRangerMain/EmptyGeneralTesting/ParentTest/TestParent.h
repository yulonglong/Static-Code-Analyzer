#ifndef TestParent_h
#define TestParent_h
#include "Parent.h"
#include "TypeTable.h"

// Note 1
#include <cppunit/extensions/HelperMacros.h>

class ParentTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE( ParentTest ); // Note 3 
	CPPUNIT_TEST( testParentUsingStmtNum );
	CPPUNIT_TEST( testParentUsingStmtType );
	CPPUNIT_TEST( testChildrenUsingStmtType );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testParentUsingStmtNum();
	void testParentUsingStmtType();
	void testChildrenUsingStmtType();
};
#endif
    