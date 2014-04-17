#ifndef TestVarTable_h
#define TestVarTable_h

// Note 1
#include <cppunit/extensions/HelperMacros.h>
#include "VarTable.h"

class VarTableTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE( VarTableTest ); // Note 3 
	CPPUNIT_TEST( testConstructor );
	CPPUNIT_TEST( testTableSet );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	// method to test the constructor
	void testConstructor();

	// method to test the assigning and retrieval of grades
	void testTableSet();
};
#endif
    