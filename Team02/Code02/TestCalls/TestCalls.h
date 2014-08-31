#ifndef TestCalls_h
#define TestCalls_h

#include "Calls.h"
#include "ProcTable.h"
#include "PKB.h"

// Note 1
#include <cppunit/extensions/HelperMacros.h>

class CallsTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE( CallsTest ); // Note 3 
	CPPUNIT_TEST( testSetCalls );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testSetCalls();
};
#endif
    