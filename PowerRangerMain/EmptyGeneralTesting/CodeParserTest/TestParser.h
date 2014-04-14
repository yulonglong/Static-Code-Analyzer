#ifndef TestParser_h
#define TestParser_h

// Note 1
#include <cppunit/extensions/HelperMacros.h>

class ParserTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE( ParserTest ); // Note 3 
	CPPUNIT_TEST( testModifyTable );
	CPPUNIT_TEST( testCompleteParser );
	CPPUNIT_TEST( testParserSource1 );
	CPPUNIT_TEST( testParserSource2 );
	CPPUNIT_TEST( testFullParserOwnSource );
	CPPUNIT_TEST( testFullParserSource1 );
	CPPUNIT_TEST( testFullParserSource2 );
	CPPUNIT_TEST( testFullParserSource2messy );
	CPPUNIT_TEST( testFullParserSource3 );
	CPPUNIT_TEST( testFullParserSource4 );
	CPPUNIT_TEST( testFullParserSource5 );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	// method to test the constructor
	void testModifyTable();

	void testCompleteParser();
	void testParserSource1();
	void testParserSource2();
	void testFullParserOwnSource();
	void testFullParserSource1();
	void testFullParserSource2();
	void testFullParserSource2messy();
	void testFullParserSource3();
	void testFullParserSource4();
	void testFullParserSource5();
};
#endif
    