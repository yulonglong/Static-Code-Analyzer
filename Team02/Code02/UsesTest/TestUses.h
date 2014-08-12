#ifndef TestUses_h
#define TestUses_h
#include "Uses.h"
#include "TypeTable.h"
#include "PKB.h"

// Note 1
#include <cppunit/extensions/HelperMacros.h>

class UsesTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE( UsesTest ); // Note 3 
	CPPUNIT_TEST( testUsesUsingStmtNum );
	CPPUNIT_TEST( testUsesUsingStmtType );
	CPPUNIT_TEST( testChildrenUsingStmtType );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testUsesUsingStmtNum();
	void testUsesUsingStmtType();
	void testChildrenUsingStmtType();
};
#endif
    