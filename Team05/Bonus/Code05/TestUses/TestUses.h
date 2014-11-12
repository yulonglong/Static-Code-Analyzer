#ifndef TestUses_h
#define TestUses_h
#include "Uses.h"
#include "PKB.h"
#include "TypeTable.h"

// Note 1
#include <cppunit/extensions/HelperMacros.h>

class UsesTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE( UsesTest ); // Note 3 
	CPPUNIT_TEST( testSetAndIsUses );
	CPPUNIT_TEST( testGetUses );
	CPPUNIT_TEST( testSetAndIsUsesProc );
	CPPUNIT_TEST( testGetUsesProc );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testSetAndIsUses();
	void testGetUses();
	void testSetAndIsUsesProc();
	void testGetUsesProc();
};
#endif
    