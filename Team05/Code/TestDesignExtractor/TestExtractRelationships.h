//@author Ipsita Mohapatra
//TestExtractRelationships.h

#ifndef TestExtractRelationships_h
#define TestExtractRelationships_h

// Note 1
#include <cppunit/extensions/HelperMacros.h>

class ExtractRelationshipsTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE( ExtractRelationshipsTest ); // Note 3 

	CPPUNIT_TEST( testModifiesProcedure );
	CPPUNIT_TEST( testUsesProcedure );
	CPPUNIT_TEST( testModifiesStatement );
	CPPUNIT_TEST( testUsesStatement );
	CPPUNIT_TEST( testFullSourceDE2 );

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testModifiesProcedure(); 
	void testUsesProcedure(); 
	void testModifiesStatement(); 
	void testUsesStatement(); 
	void testFullSourceDE2();

private:
	string print(vector<VARINDEX>, VarTable);

};
#endif
    