//@author Ipsita Mohapatra
//TestBuildCFG.h

#ifndef TestBuildCFG_h
#define TestBuildCFG_h

// Note 1
#include <cppunit/extensions/HelperMacros.h>

class BuildCFGTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE( BuildCFGTest ); // Note 3 
	//CPPUNIT_TEST( testBuildCFGForAssignAndCallStmts );
	//CPPUNIT_TEST( testBuildCFGForWhileStmts );
	CPPUNIT_TEST( testBuildCFGForIfStmts );
	//CPPUNIT_TEST( testBuildCFGForNestedIfStmts ); 
	//CPPUNIT_TEST( testBuildCFGForNestedWhileStmts );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testBuildCFGForAssignAndCallStmts(); 
	void testBuildCFGForWhileStmts(); 
	void testBuildCFGForIfStmts(); 
	void testBuildCFGForNestedIfStmts(); 
	void testBuildCFGForNestedWhileStmts(); 
private:
	string print(vector<int>); 

};
#endif
    