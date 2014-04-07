#include <cppunit/config/SourcePrefix.h>
#include "Node.h"
#include "CodeParser.h"
#include "Testintegrate.h"
#include "QueryParser.h"
#include "QueryEvaluator.h"
#include "PKB.h"


#include <iostream>
#include <string>
using namespace std;

void 
IntegrateTest::setUp()
{
}

void IntegrateTest::tearDown()
{
}

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( IntegrateTest ); // Note 4 

// method to test the constructor
void IntegrateTest::testModifyTable()
{  // Note 5
	// create a node
	/*
	PKB pkb;
	parserDriver("CodeParserTestIn.txt",pkb);

	VarTable varTable = pkb.getVarTable();
	ProcTable procTable = pkb.getProcTable();;
	Follows follows = pkb.getFollows();
	Parent parent = pkb.getParent();
	TypeTable typeTable = pkb.getTypeTable();
	Node* root = pkb.getASTRoot();

	string expected = "x";
	CPPUNIT_ASSERT_EQUAL(expected, varTable.getVarName(0));
	expected = "z";
	CPPUNIT_ASSERT_EQUAL(expected, varTable.getVarName(1));
	expected = "i";
	CPPUNIT_ASSERT_EQUAL(expected, varTable.getVarName(2));
	expected = "y";
	CPPUNIT_ASSERT_EQUAL(expected, varTable.getVarName(3));
	expected = "v";
	CPPUNIT_ASSERT_EQUAL(expected, varTable.getVarName(4));


	expected = "First";
	CPPUNIT_ASSERT_EQUAL(expected, procTable.getProcName(0));
	expected = "Second";
	CPPUNIT_ASSERT_EQUAL(expected, procTable.getProcName(1));
	expected = "Third";
	CPPUNIT_ASSERT_EQUAL(expected, procTable.getProcName(2));
	return;*/
}

// method to test the assigning and retrieval of grades
void IntegrateTest::testCompleteParser()
{
/*	// create a node
	PKB pkb;
	parserDriver("CodeParserTestIn.txt",pkb);

	VarTable varTable = pkb.getVarTable();
	ProcTable procTable = pkb.getProcTable();;
	Follows follows = pkb.getFollows();
	Parent parent = pkb.getParent();
	TypeTable typeTable = pkb.getTypeTable();
	Node* root = pkb.getASTRoot();
	// assign
	Node* curr = root;
	curr = root->getChild()[0];
	curr = curr->getChild()[0];
	curr = curr->getChild()[0];

	string expected = "=";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getData());
	expected = "assign";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getType());

	curr = curr->getChild()[0];

	expected = "x";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getData());
	expected = "variable";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getType());

	// verify that the assignment is correct - Note 7
	

	return;*/
}

void IntegrateTest::testParserSource1()
{
	/*// create a node
	PKB pkb;
	parserDriver("Source1.txt",pkb);

	VarTable varTable = pkb.getVarTable();
	ProcTable procTable = pkb.getProcTable();;
	Follows follows = pkb.getFollows();
	Parent parent = pkb.getParent();
	TypeTable typeTable = pkb.getTypeTable();
	Node* root = pkb.getASTRoot();

	Node* curr = root;
	
	string expected = "root";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getData());
	expected = "program";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getType());

	curr = curr->getChild()[0];
	expected = "Mini";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getData());
	expected = "procedure";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getType());

	curr = curr->getChild()[0];
    expected = "Mini";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getData());
	expected = "stmtLst";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getType());

	curr = curr->getChild()[0];
    expected = "=";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getData());
	expected = "assign";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getType());

	curr = curr->getChild()[0];
	expected = "A1";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getData());
	expected = "variable";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getType());

    curr = root;

	curr = curr->getChild()[1];
	expected = "mini";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getData());
	expected = "procedure";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getType());

	curr = curr->getChild()[0];
    expected = "mini";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getData());
	expected = "stmtLst";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getType());

	curr = curr->getChild()[1];
    expected = "=";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getData());
	expected = "assign";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getType());

	curr = curr->getChild()[1];
	expected = "A1";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getData());
	expected = "variable";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getType());

	return;*/
}

void IntegrateTest::testParserSource2()
{
/*	// create a node
	PKB pkb;
	parserDriver("Source2.txt",pkb);

	VarTable varTable = pkb.getVarTable();
	ProcTable procTable = pkb.getProcTable();;
	Follows follows = pkb.getFollows();
	Parent parent = pkb.getParent();
	TypeTable typeTable = pkb.getTypeTable();
	Node* root = pkb.getASTRoot();

	Node* curr = root;
	
	string expected = "root";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getData());
	expected = "program";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getType());

	curr = curr->getChild()[0];
	expected = "ABC";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getData());
	expected = "procedure";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getType());

	curr = curr->getChild()[0];
    expected = "ABC";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getData());
	expected = "stmtLst";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getType());

	curr = curr->getChild()[3];
    expected = "4";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getData());
	CPPUNIT_ASSERT_EQUAL(4, curr->getProgLine());
	expected = "while";
	CPPUNIT_ASSERT_EQUAL(expected, curr->getType());

	return;*/
}

 void IntegrateTest::testPQLSource1() {
	string expected="";
	vector<Relationship> v;
	

	string s1 = "assign a; Select a such that Follows(1, 2)";
	string s2 = "assign a; Select a such that Follows(1, a)";
	string s3 = "stmt s; Select s such that Follows(4, s)";
	string s4 = "Select BOOLEAN such that Follows(6, 7)";
	string s5 = "Select BOOLEAN such that Follows(5, 6)";

	string s6 = "while w; Select w such that Follows(3, w)";
	string s7 = "while w; Select w such that Follows(4, w)";
	string s8 = "stmt s; Select s such that Follows(s, 19)";
	string s9 = "Select BOOLEAN such that Follows(15, 16)";
	string s10 = "stmt s; Select s such that Parent(s, 9)";
	string s11 = "while w; Select w such that Parent(w, 11)";
	string s12 = "assign a; Select a such that Parent(a, 3)";
	// string s13 = "while w; assign a; Select w such that Parent(w, a)";
	string s13 = "while w, assign a; Select w such that Parent(w, a)";
	string s14 = "Select BOOLEAN such that Parent(4, 9)";
	string s15 = "while w; Select BOOLEAN such that Parent(4, w)";
	string s16 = "assign a; Select a such that Parent(11, a)";

	// TODO: run query parser;
	QueryParser qp;
	PKB pkb;
	QueryEvaluator qe(pkb);
	Follows f = qe.pkb->getFollows();
	TypeTable t = qe.pkb->getTypeTable();

	//Query 1
	Query q1 = qp.parse(s1);
	v = q1.getRelVect();
	expected = "a";
	Relationship r = v[0];
	unordered_map<string, TypeTable::SynType> m = q1.getSynTable();
	
	CPPUNIT_ASSERT_EQUAL(Relationship::FOLLOWS, r.getRelType());
	CPPUNIT_ASSERT_EQUAL(expected, q1.getSelectedSyn());
	expected = "1";
	CPPUNIT_ASSERT_EQUAL(expected, r.getToken1());
	expected = "2";
	CPPUNIT_ASSERT_EQUAL(expected, r.getToken2());

	f.setFollows(1,2);
	t.insertStmtNumAndType(1, TypeTable::ASSIGN);
	t.insertStmtNumAndType(2, TypeTable::ASSIGN);
	qe.pkb->setFollows(f);
	qe.pkb->setTypeTable(t);
	CPPUNIT_ASSERT(qe.evaluateFollowsBoolean(r,m)==true);
	/*

	//Query 2
	Query q2 = qp.parse(s2);
	v = q2.getRelVect();
	r = v[0];
	m = q2.getSynTable();

	unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(r.getToken1());
	unordered_map<string, TypeTable::SynType>::iterator i2 = m.find(r.getToken2());

	

	CPPUNIT_ASSERT_EQUAL(Relationship::FOLLOWS, r.getRelType());
	expected = "a";
	CPPUNIT_ASSERT_EQUAL(expected, q2.getSelectedSyn());
	expected = "1";
	CPPUNIT_ASSERT_EQUAL(expected, r.getToken1());
	expected = "a";
	CPPUNIT_ASSERT_EQUAL(expected, r.getToken2()); 
	
	vector<int> vec = qe.evaluateFollows(r, m, q2.getSelectedSyn());
	//cout<<vec[0]<<endl;
	*/
	
	Query q3 = qp.parse(s3);
	Query q4 = qp.parse(s4);
	Query q5 = qp.parse(s5);
	Query q6 = qp.parse(s6);
	Query q7 = qp.parse(s7);
	Query q8 = qp.parse(s8);
	Query q9 = qp.parse(s9);
	Query q10 = qp.parse(s10);
	Query q11 = qp.parse(s11);
	Query q12 = qp.parse(s12);
	Query q13 = qp.parse(s13);
	Query q14 = qp.parse(s14);
	Query q15 = qp.parse(s15);
	Query q16 = qp.parse(s16);

	// TODO: run evaluate on query

	// TODO: compare result with expected result
 }
