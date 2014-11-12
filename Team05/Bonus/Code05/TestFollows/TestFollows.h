#ifndef TestFollows_h
#define TestFollows_h

#include "Follows.h"
#include "PKB.h"

// Note 1
#include <cppunit/extensions/HelperMacros.h>

class FollowsTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE( FollowsTest ); // Note 3 
	CPPUNIT_TEST( testIsFollows );
	CPPUNIT_TEST( testGetFollows );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testIsFollows();
	void testGetFollows();
};
#endif
    