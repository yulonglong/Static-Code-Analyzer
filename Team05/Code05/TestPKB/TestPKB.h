#ifndef TestPKB_h
#define TestPKB_h

#include "TypeTable.h"
#include "VarTable.h"
#include "PKB.h"

// Note 1
#include <cppunit/extensions/HelperMacros.h>

class PKBTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE( PKBTest ); // Note 3
	CPPUNIT_TEST( testDestructor );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testDestructor();
};

#endif