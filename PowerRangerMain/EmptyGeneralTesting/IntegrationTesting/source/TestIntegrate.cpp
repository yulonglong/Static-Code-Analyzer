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

void IntegrateTest::testModifyTable()
{  // Note 5
	
	PKB *pkb;
	pkb = PKB::getInstance();
	parserDriver("CodeParserTestIn.txt",pkb);

	VarTable* varTable = pkb->getVarTable();
	ProcTable* procTable = pkb->getProcTable();;
	Follows* follows = pkb->getFollows();
	Parent* parent = pkb->getParent();
	TypeTable* typeTable = pkb->getTypeTable();
	Modifies* modifies = pkb->getModifies();
	Uses* uses = pkb->getUses();
	Node* root = pkb->getASTRoot();

	string expected = "x";
	CPPUNIT_ASSERT_EQUAL(expected, varTable->getVarName(0));
	expected = "z";
	CPPUNIT_ASSERT_EQUAL(expected, varTable->getVarName(1));
	expected = "i";
	CPPUNIT_ASSERT_EQUAL(expected, varTable->getVarName(2));
	expected = "y";
	CPPUNIT_ASSERT_EQUAL(expected, varTable->getVarName(3));
	expected = "v";
	CPPUNIT_ASSERT_EQUAL(expected, varTable->getVarName(4));

	expected = "First";
	CPPUNIT_ASSERT_EQUAL(expected, procTable->getProcName(0));
	expected = "Second";
	CPPUNIT_ASSERT_EQUAL(expected, procTable->getProcName(1));
	expected = "Third";
	CPPUNIT_ASSERT_EQUAL(expected, procTable->getProcName(2));

	CPPUNIT_ASSERT_EQUAL(false,parent->isParent(1,2));
	CPPUNIT_ASSERT_EQUAL(false,parent->isParent(3,2));
	CPPUNIT_ASSERT_EQUAL(true,parent->isParent(6,7));
	CPPUNIT_ASSERT_EQUAL(true,parent->isParent(6,8));
	CPPUNIT_ASSERT_EQUAL(true,parent->isParent(6,9));
	CPPUNIT_ASSERT_EQUAL(true,parent->isParent(10,11));
	CPPUNIT_ASSERT_EQUAL(true,parent->isParent(10,12));
	CPPUNIT_ASSERT_EQUAL(false,parent->isParent(11,12));

	CPPUNIT_ASSERT_EQUAL(true,follows->isFollows(1,2));
	CPPUNIT_ASSERT_EQUAL(true,follows->isFollows(2,3));
	CPPUNIT_ASSERT_EQUAL(false,follows->isFollows(1,3));
	CPPUNIT_ASSERT_EQUAL(true,follows->isFollows(4,5));
	CPPUNIT_ASSERT_EQUAL(true,follows->isFollows(5,6));
	CPPUNIT_ASSERT_EQUAL(false,follows->isFollows(6,7));

	CPPUNIT_ASSERT_EQUAL(TypeTable::ASSIGN,typeTable->getType(1));
	CPPUNIT_ASSERT_EQUAL(TypeTable::ASSIGN,typeTable->getType(2));
	CPPUNIT_ASSERT_EQUAL(TypeTable::CALL,typeTable->getType(3));
	CPPUNIT_ASSERT_EQUAL(TypeTable::WHILE,typeTable->getType(6));
	CPPUNIT_ASSERT_EQUAL(TypeTable::CALL,typeTable->getType(8));
	CPPUNIT_ASSERT_EQUAL(TypeTable::IF,typeTable->getType(10));
	CPPUNIT_ASSERT_EQUAL(TypeTable::ASSIGN,typeTable->getType(11));

	
	CPPUNIT_ASSERT_EQUAL(false,modifies->isModifies(2,"x"));
	CPPUNIT_ASSERT_EQUAL(false,modifies->isModifies(3,"x"));
	CPPUNIT_ASSERT_EQUAL(true,modifies->isModifies(1,"x"));
	CPPUNIT_ASSERT_EQUAL(true,modifies->isModifies(4,"x"));
	CPPUNIT_ASSERT_EQUAL(true,modifies->isModifies(5,"i"));
	CPPUNIT_ASSERT_EQUAL(true,modifies->isModifies(13,"z"));
	CPPUNIT_ASSERT_EQUAL(true,modifies->isModifies(16,"z"));
	CPPUNIT_ASSERT_EQUAL(false,modifies->isModifies(21,"v"));
	
	CPPUNIT_ASSERT_EQUAL(false,uses->isUses(1,"x"));
	CPPUNIT_ASSERT_EQUAL(true,uses->isUses(6,"i"));
	CPPUNIT_ASSERT_EQUAL(true,uses->isUses(7,"x"));
	CPPUNIT_ASSERT_EQUAL(true,uses->isUses(7,"y"));
	CPPUNIT_ASSERT_EQUAL(false,uses->isUses(1,"z"));
	CPPUNIT_ASSERT_EQUAL(false,uses->isUses(2,"z"));
	
	return;
}

void IntegrateTest::testCompleteParser()
{
	// create a node
	PKB* pkb;
	pkb = PKB::getInstance();
	parserDriver("CodeParserTestIn.txt",pkb);

	
	VarTable* varTable = pkb->getVarTable();
	ProcTable* procTable = pkb->getProcTable();;
	Follows* follows = pkb->getFollows();
	Parent* parent = pkb->getParent();
	TypeTable* typeTable = pkb->getTypeTable();
	Node* root = pkb->getASTRoot();
		
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
	

	return;
}


void IntegrateTest::testParserSource1()
{
	PKB* pkb;
	pkb = PKB::getInstance();
	parserDriver("Source1.txt",pkb);

	VarTable* varTable = pkb->getVarTable();
	ProcTable* procTable = pkb->getProcTable();;
	Follows* follows = pkb->getFollows();
	Parent* parent = pkb->getParent();
	TypeTable* typeTable = pkb->getTypeTable();
	Node* root = pkb->getASTRoot();

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

	return;
}

void IntegrateTest::testParserSource2()
{
	PKB* pkb;
	pkb = PKB::getInstance();
	parserDriver("Source2.txt",pkb);

	VarTable* varTable = pkb->getVarTable();
	ProcTable* procTable = pkb->getProcTable();;
	Follows* follows = pkb->getFollows();
	Parent* parent = pkb->getParent();
	TypeTable* typeTable = pkb->getTypeTable();
	Node* root = pkb->getASTRoot();

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

	return;
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
	Follows* f = qe.pkb->getFollows();
	TypeTable* t = qe.pkb->getTypeTable();

	//Query 1
	qp.validate(s1);
	Query q1 = qp.parse();
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

	f->setFollows(1,2);
	t->insertStmtNumAndType(1, TypeTable::ASSIGN);
	t->insertStmtNumAndType(2, TypeTable::ASSIGN);
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

 */