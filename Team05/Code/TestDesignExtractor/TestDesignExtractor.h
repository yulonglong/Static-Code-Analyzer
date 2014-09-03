//@author Ipsita Mohapatra
//TestDesignExtractor.h

#ifndef TestDesignExtractor_h
#define TestDesignExtractor_h

// Note 1
#include <cppunit/extensions/HelperMacros.h>

class DesignExtractorTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE( DesignExtractorTest ); // Note 3 
	CPPUNIT_TEST( testExtractRelationshipsModifiesProcedure );
	CPPUNIT_TEST( testExtractRelationshipsUsesProcedure );
	CPPUNIT_TEST( testExtractRelationshipsModifiesStatement );
	CPPUNIT_TEST( testExtractRelationshipsUsesStatement );
	// CPPUNIT_TEST( testFullDesignExtractor );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testExtractRelationshipsModifiesProcedure(); 
	void testExtractRelationshipsUsesProcedure(); 
	void testExtractRelationshipsModifiesStatement(); 
	void testExtractRelationshipsUsesStatement(); 
	void testFullDesignExtractor();

private:
	string print(vector<VARINDEX>, VarTable);

};
#endif
    