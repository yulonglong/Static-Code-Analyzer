#ifndef TestSibling_h
#define TestSibling_h
#include "PKB.h"
#include "Sibling.h"

// Note 1
#include <cppunit/extensions/HelperMacros.h>

class SiblingTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE( SiblingTest ); // Note 3 
	CPPUNIT_TEST( testSiblingStmtNumStmtNum );
	CPPUNIT_TEST( testSiblingVarIndexVarIndex );
	CPPUNIT_TEST( testSiblingVarIndexConstant );
	CPPUNIT_TEST( testSiblingConstantConstant );
	CPPUNIT_TEST( testSiblingVarIndexMathOp );
	CPPUNIT_TEST( testSiblingConstantMathOp );
	CPPUNIT_TEST( testSiblingMathOpMathOp );
	CPPUNIT_TEST( testSiblingProcIndexProcIndex );
	CPPUNIT_TEST( testSiblingVarIndexStmtList );
	CPPUNIT_TEST( testSiblingStmtListStmtList );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testSiblingStmtNumStmtNum();
	void testSiblingVarIndexVarIndex();
	void testSiblingVarIndexConstant();
	void testSiblingConstantConstant();
	void testSiblingVarIndexMathOp();
	void testSiblingConstantMathOp();
	void testSiblingMathOpMathOp();
	void testSiblingProcIndexProcIndex();
	void testSiblingVarIndexStmtList();
	void testSiblingStmtListStmtList();
};
#endif
    