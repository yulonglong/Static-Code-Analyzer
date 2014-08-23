//@author Steven Kester Yuwono
//TestIntegrate.h

#ifndef TestIntegrate_h
#define TestIntegrate_h

// Note 1
#include <cppunit/extensions/HelperMacros.h>

class IntegrateTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE( IntegrateTest ); // Note 3 
	CPPUNIT_TEST( testParserSource2 );
	CPPUNIT_TEST( testSource2q1 );
	CPPUNIT_TEST( testSource2q2 );
	CPPUNIT_TEST( testSource2q3 );
	CPPUNIT_TEST( testSource2q4 );
	CPPUNIT_TEST( testSource2q5 );
	CPPUNIT_TEST( testSource2q6 );
	CPPUNIT_TEST( testSource2q7 );
	CPPUNIT_TEST( testSource2q8 );
	CPPUNIT_TEST( testSource2q9 );
	CPPUNIT_TEST( testSource2q10 );
	CPPUNIT_TEST( testSource2q11 );
	CPPUNIT_TEST( testSource2q12 );
	CPPUNIT_TEST( testSource2q13 );
	CPPUNIT_TEST( testSource2q14 );
	CPPUNIT_TEST( testSource2q15 );
	CPPUNIT_TEST( testSource2q16 );
	CPPUNIT_TEST( testSource2q17 );
	CPPUNIT_TEST( testSource2q18 );
	CPPUNIT_TEST( testSource2q19 );
	CPPUNIT_TEST( testSource2q20 );
	CPPUNIT_TEST( testSource2q21 );
	CPPUNIT_TEST( testSource2q22 );
	CPPUNIT_TEST( testSource2q23 );
	CPPUNIT_TEST( testSource2q24 );
	CPPUNIT_TEST( testSource2q25 );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	// method to test the assigning and retrieval of grades
	void testParserSource2();
	void testSource2q1();
	void testSource2q2();
	void testSource2q3();
	void testSource2q4();
	void testSource2q5();
	void testSource2q6();
	void testSource2q7();
	void testSource2q8();
	void testSource2q9();
	void testSource2q10();
	void testSource2q11();
	void testSource2q12();
	void testSource2q13();
	void testSource2q14();
	void testSource2q15();
	void testSource2q16();
	void testSource2q17();
	void testSource2q18();
	void testSource2q19();
	void testSource2q20();
	void testSource2q21();
	void testSource2q22();
	void testSource2q23();
	void testSource2q24();
	void testSource2q25();
};
#endif
    