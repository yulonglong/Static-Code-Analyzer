#ifndef TestFollows_h
#define TestFollows_h

// Note 1
#include <cppunit/extensions/HelperMacros.h>

class FollowsTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE( FollowsTest ); // Note 3 
	CPPUNIT_TEST( testIsFollowsUsingStmtNum );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testIsFollowsUsingStmtNum();
	void testIsFollowsUsingStmtType();
	void testIsfollowedByUsingStmtType();
	void testGetFollowsUsingStmtType();
	void testGetfollowedByUsingStmtType();
	void testGetAll();
};
#endif
    