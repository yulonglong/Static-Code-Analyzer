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

	string s6 = "while w; Select w such that Follows*(3, w)";
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
	PKB* pkb = PKB::getInstance();
	QueryEvaluator qe(pkb);
	Follows* f = qe.pkb->getFollows();
	TypeTable* t = qe.pkb->getTypeTable();

	//Query 1 assign a; Select a such that Follows(1, 2)
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

	/*f->setFollows(1,2);
	t->insertStmtNumAndType(1, TypeTable::ASSIGN);
	t->insertStmtNumAndType(2, TypeTable::ASSIGN);*/
	CPPUNIT_ASSERT(qe.evaluateQueryBoolean(q1)==true);
	
	
	//Query 2 assign a; Select a such that Follows(1, a)
	qp.validate(s2);
	Query q2 = qp.parse();
	v = q2.getRelVect();
	Relationship r2 = v[0];
	unordered_map<string, TypeTable::SynType> m2 = q2.getSynTable();
	
	/*
	Query q2;
	q2.setSelectedSyn("a");
	Relationship r2("Follows", "1", "a");
	q2.addRelationship(r2);
	unordered_map<string,TypeTable::SynType> m2;
	m2.insert(make_pair<string, TypeTable::SynType>("a", TypeTable::ASSIGN));
	q2.setSynTable(m2);

	unordered_map<string, TypeTable::SynType>::iterator i1 = m2.find(r.getToken1());
	unordered_map<string, TypeTable::SynType>::iterator i2 = m2.find(r.getToken2());*/

	CPPUNIT_ASSERT_EQUAL(Relationship::FOLLOWS, r2.getRelType());
	expected = "a";
	CPPUNIT_ASSERT_EQUAL(expected, q2.getSelectedSyn());
	expected = "1";
	CPPUNIT_ASSERT_EQUAL(expected, r2.getToken1());
	expected = "a";
	CPPUNIT_ASSERT_EQUAL(expected, r2.getToken2()); 
	
	vector<int> vec = qe.evaluateQuery(q2);
	CPPUNIT_ASSERT_EQUAL(2, vec[0]);

	//Query 3 stmt s; Select s such that Follows(4, s)
	qp.validate(s3);
	Query q3 = qp.parse();
	v = q3.getRelVect();
	Relationship r3 = v[0];
	unordered_map<string, TypeTable::SynType> m3 = q3.getSynTable();

	CPPUNIT_ASSERT_EQUAL(Relationship::FOLLOWS, r3.getRelType());
	expected = "s";
	CPPUNIT_ASSERT_EQUAL(expected, q3.getSelectedSyn());
	expected = "4";
	CPPUNIT_ASSERT_EQUAL(expected, r3.getToken1());
	expected = "s";
	CPPUNIT_ASSERT_EQUAL(expected, r3.getToken2()); 
	/*
	Query q3;
	q3.setSelectedSyn("s");
	Relationship r3("Follows", "4", "s");
	q3.addRelationship(r3);
	unordered_map<string,TypeTable::SynType> m3;
	m3.insert(make_pair<string, TypeTable::SynType>("s", TypeTable::STMT));
	q2.setSynTable(m3);*/
	
	vec.clear();
	vec = qe.evaluateQuery(q3);
	CPPUNIT_ASSERT_EQUAL(23, vec[0]);

	//Query 4 Select BOOLEAN such that Follows(6, 7)
	qp.validate(s4);
	Query q4 = qp.parse();
	v = q4.getRelVect();
	Relationship r4 = v[0];
	unordered_map<string, TypeTable::SynType> m4 = q4.getSynTable();

	CPPUNIT_ASSERT_EQUAL(Relationship::FOLLOWS, r4.getRelType());
	expected = "BOOLEAN";
	CPPUNIT_ASSERT_EQUAL(expected, q4.getSelectedSyn());
	expected = "6";
	CPPUNIT_ASSERT_EQUAL(expected, r4.getToken1());
	expected = "7";
	CPPUNIT_ASSERT_EQUAL(expected, r4.getToken2()); 

	CPPUNIT_ASSERT_EQUAL(true, qe.evaluateQueryBoolean(q4));

	//Query 5 Select BOOLEAN such that Follows(5, 6)
	qp.validate(s5);
	Query q5 = qp.parse();
	v = q5.getRelVect();
	Relationship r5 = v[0];
	unordered_map<string, TypeTable::SynType> m5 = q5.getSynTable();

	CPPUNIT_ASSERT_EQUAL(Relationship::FOLLOWS, r5.getRelType());
	expected = "BOOLEAN";
	CPPUNIT_ASSERT_EQUAL(expected, q5.getSelectedSyn());
	expected = "5";
	CPPUNIT_ASSERT_EQUAL(expected, r5.getToken1());
	expected = "6";
	CPPUNIT_ASSERT_EQUAL(expected, r5.getToken2()); 

	CPPUNIT_ASSERT_EQUAL(false, qe.evaluateQueryBoolean(q5));
	
	//Query 6 while w; Select w such that Follows*(3, w)
	qp.validate(s6);
	Query q6 = qp.parse();
	v = q6.getRelVect();
	Relationship r6 = v[0];
	unordered_map<string, TypeTable::SynType> m6 = q6.getSynTable();

	CPPUNIT_ASSERT_EQUAL(Relationship::FOLLOWSSTAR, r6.getRelType());
	expected = "w";
	CPPUNIT_ASSERT_EQUAL(expected, q6.getSelectedSyn());
	expected = "3";
	CPPUNIT_ASSERT_EQUAL(expected, r6.getToken1());
	expected = "w";
	CPPUNIT_ASSERT_EQUAL(expected, r6.getToken2()); 
	
	
	vec.clear();
	vec = qe.evaluateQuery(q6);
	CPPUNIT_ASSERT_EQUAL(4, vec[0]);
	/*
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
 */
 }

 