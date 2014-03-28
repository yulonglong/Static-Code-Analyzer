#ifndef TestFollows_h
#define TestFollows_h

// Note 1
#include <cppunit/extensions/HelperMacros.h>

class FollowsTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE( FollowsTest ); // Note 3 
	CPPUNIT_TEST( testConstructor );
	CPPUNIT_TEST( testType );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	// method to test the constructor
	void testConstructor();

	// method to test the assigning and retrieval of grades
	void testType();
};
#endif
    