#ifndef TestModifies_h
#define TestModifies_h
#include "Modifies.h"
#include "TypeTable.h"
#include "VarTable.h"
#include "PKB.h"

// Note 1
#include <cppunit/extensions/HelperMacros.h>

class ModifiesTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE( ModifiesTest ); // Note 3 
	CPPUNIT_TEST( testSetModifies );
	CPPUNIT_TEST( testGetModifies );
	CPPUNIT_TEST( testIsModifies );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testSetModifies();
	void testGetModifies();
	void testIsModifies();
};

#endif
    