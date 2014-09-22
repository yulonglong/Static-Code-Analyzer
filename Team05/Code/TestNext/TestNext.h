#ifndef TestNext_h
#define TestNext_h

#include "PKB.h"
#include "TypeTable.h"
#include "Next.h"

// Note 1
#include <cppunit/extensions/HelperMacros.h>

class NextTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE( NextTest ); // Note 3
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testSetNext();
	void testGetNext();
};
#endif
    