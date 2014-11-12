//@author Ipsita Mohapatra
//TestFullDesignExtractor_h

#ifndef TestFullDesignExtractor_h
#define TestFullDesignExtractor_h

// Note 1
#include <cppunit/extensions/HelperMacros.h>

class FullDesignExtractorTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE( FullDesignExtractorTest ); // Note 3 

	//CPPUNIT_TEST( testIter2SimpleSource );
	//CPPUNIT_TEST( testSource1B );
	//CPPUNIT_TEST( testAnySource );

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testIter2SimpleSource(); 
	void testSource1B(); 
	void testAnySource(); 

private:
	string print(set<int>); 
	string printVariables(set<VARINDEX>, PKB &pkb);

};
#endif
    