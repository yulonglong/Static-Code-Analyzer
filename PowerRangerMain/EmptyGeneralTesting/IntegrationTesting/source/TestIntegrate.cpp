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
	string s7 = "assign a; Select a such that Follows*(13, a)";
	string s8 = "stmt s; Select s such that Follows*(s, 19)";
	string s9 = "Select BOOLEAN such that Follows*(1, 3)";
	string s10 = "stmt s; Select s such that Parent(s, 9)";
	string s11 = "while w; Select w such that Parent(w, 11)";
	string s12 = "assign a; Select a such that Parent(a, 3)";
	string s13 = "while w; assign a; Select w such that Parent(w, a)";
	string s14 = "Select BOOLEAN such that Parent(4, 9)";
	string s15 = "while w; Select w such that Parent(4, w)";
	string s16 = "assign a; Select a such that Parent*(11, a)";
	string s17 = "while w; Select w such that Parent*(w, 17)";

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

	//Query 7 assign a; Select a such that Follows*(13, a)
	qp.validate(s7);
	Query q7 = qp.parse();
	v = q7.getRelVect();
	Relationship r7 = v[0];
	unordered_map<string, TypeTable::SynType> m7 = q7.getSynTable();

	CPPUNIT_ASSERT_EQUAL(Relationship::FOLLOWSSTAR, r7.getRelType());
	expected = "a";
	CPPUNIT_ASSERT_EQUAL(expected, q7.getSelectedSyn());
	expected = "13";
	CPPUNIT_ASSERT_EQUAL(expected, r7.getToken1());
	expected = "a";
	CPPUNIT_ASSERT_EQUAL(expected, r7.getToken2()); 
	
	
	vec.clear();
	vec = qe.evaluateQuery(q7);
	CPPUNIT_ASSERT_EQUAL(14, vec[0]);
	CPPUNIT_ASSERT_EQUAL(15, vec[1]);

	//Query 8 stmt s; Select s such that Follows*(s, 19)
	qp.validate(s8);
	Query q8 = qp.parse();
	v = q8.getRelVect();
	Relationship r8 = v[0];
	unordered_map<string, TypeTable::SynType> m8 = q8.getSynTable();

	CPPUNIT_ASSERT_EQUAL(Relationship::FOLLOWSSTAR, r8.getRelType());
	expected = "19";
	CPPUNIT_ASSERT_EQUAL(expected, r8.getToken2()); 
	expected = "s";
	CPPUNIT_ASSERT_EQUAL(expected, q8.getSelectedSyn());
	expected = "s";
	CPPUNIT_ASSERT_EQUAL(expected, r8.getToken1());
	
	vec.clear();
	vec = qe.evaluateQuery(q8);

	CPPUNIT_ASSERT_EQUAL(10, vec[0]);
	CPPUNIT_ASSERT_EQUAL(11, vec[1]);

	//Query 9 Select BOOLEAN such that Follows*(1, 3)
	qp.validate(s9);
	Query q9 = qp.parse();
	v = q9.getRelVect();
	Relationship r9 = v[0];
	unordered_map<string, TypeTable::SynType> m9 = q9.getSynTable();

	CPPUNIT_ASSERT_EQUAL(Relationship::FOLLOWSSTAR, r9.getRelType());
	expected = "BOOLEAN";
	CPPUNIT_ASSERT_EQUAL(expected, q9.getSelectedSyn());
	expected = "1";
	CPPUNIT_ASSERT_EQUAL(expected, r9.getToken1());
	expected = "3";
	CPPUNIT_ASSERT_EQUAL(expected, r9.getToken2()); 

	CPPUNIT_ASSERT_EQUAL(true, qe.evaluateQueryBoolean(q9));

	//Query 10 stmt s; Select s such that Parent(s, 9)
	qp.validate(s10);
	Query q10 = qp.parse();
	v = q10.getRelVect();
	Relationship r10 = v[0];
	unordered_map<string, TypeTable::SynType> m10 = q10.getSynTable();

	CPPUNIT_ASSERT_EQUAL(Relationship::PARENT, r10.getRelType());
	expected = "s";
	CPPUNIT_ASSERT_EQUAL(expected, q10.getSelectedSyn());
	expected = "s";
	CPPUNIT_ASSERT_EQUAL(expected, r10.getToken1());
	expected = "9";
	CPPUNIT_ASSERT_EQUAL(expected, r10.getToken2()); 

	vec = qe.evaluateQuery(q10);
	CPPUNIT_ASSERT_EQUAL(5, vec[0]);

	
	//Query 11 while w; Select w such that Parent(w, 11)
	qp.validate(s11);
	Query q11 = qp.parse();
	v = q11.getRelVect();
	Relationship r11 = v[0];
	unordered_map<string, TypeTable::SynType> m11 = q11.getSynTable();

	CPPUNIT_ASSERT_EQUAL(Relationship::PARENT, r11.getRelType());
	expected = "w";
	CPPUNIT_ASSERT_EQUAL(expected, q11.getSelectedSyn());
	expected = "w";
	CPPUNIT_ASSERT_EQUAL(expected, r11.getToken1());
	expected = "11";
	CPPUNIT_ASSERT_EQUAL(expected, r11.getToken2()); 

	vec = qe.evaluateQuery(q11);
	CPPUNIT_ASSERT_EQUAL(9, vec[0]);

	//Query 12 assign a; Select a such that Parent(a, 3)
	qp.validate(s12);
	Query q12 = qp.parse();
	v = q12.getRelVect();
	Relationship r12 = v[0];
	unordered_map<string, TypeTable::SynType> m12 = q12.getSynTable();

	CPPUNIT_ASSERT_EQUAL(Relationship::PARENT, r12.getRelType());
	expected = "a";
	CPPUNIT_ASSERT_EQUAL(expected, q12.getSelectedSyn());
	expected = "a";
	CPPUNIT_ASSERT_EQUAL(expected, r12.getToken1());
	expected = "3";
	CPPUNIT_ASSERT_EQUAL(expected, r12.getToken2()); 

	vec = qe.evaluateQuery(q12);
	CPPUNIT_ASSERT_EQUAL(-1, vec[0]);
	
	//Query 13 while w; assign a; Select w such that Parent(w, a)
	qp.validate(s13);
	Query q13 = qp.parse();
	v = q13.getRelVect();
	Relationship r13 = v[0];
	unordered_map<string, TypeTable::SynType> m13 = q13.getSynTable();
	
	CPPUNIT_ASSERT_EQUAL(Relationship::PARENT, r13.getRelType());
	expected = "w";
	CPPUNIT_ASSERT_EQUAL(expected, q13.getSelectedSyn());
	expected = "w";
	CPPUNIT_ASSERT_EQUAL(expected, r13.getToken1());
	expected = "a";
	CPPUNIT_ASSERT_EQUAL(expected, r13.getToken2()); 

	vec = qe.evaluateQuery(q13);
	CPPUNIT_ASSERT_EQUAL(4, vec[0]);
	CPPUNIT_ASSERT_EQUAL(5, vec[1]);
	CPPUNIT_ASSERT_EQUAL(7, vec[2]);
	CPPUNIT_ASSERT_EQUAL(9, vec[3]);
	CPPUNIT_ASSERT_EQUAL(11, vec[4]);
	CPPUNIT_ASSERT_EQUAL(12, vec[5]);
	CPPUNIT_ASSERT_EQUAL(16, vec[6]);

	//Query 14 Select BOOLEAN such that Parent(4, 9)
	qp.validate(s14);
	Query q14 = qp.parse();
	v = q14.getRelVect();
	Relationship r14 = v[0];
	unordered_map<string, TypeTable::SynType> m14 = q14.getSynTable();

	CPPUNIT_ASSERT_EQUAL(Relationship::PARENT, r14.getRelType());
	expected = "BOOLEAN";
	CPPUNIT_ASSERT_EQUAL(expected, q14.getSelectedSyn());
	expected = "4";
	CPPUNIT_ASSERT_EQUAL(expected, r14.getToken1());
	expected = "9";
	CPPUNIT_ASSERT_EQUAL(expected, r14.getToken2()); 

	CPPUNIT_ASSERT_EQUAL(false, qe.evaluateQueryBoolean(q14));

	//Query 15 while w; Select w such that Parent(4, w)
	qp.validate(s15);
	Query q15 = qp.parse();
	v = q15.getRelVect();
	Relationship r15 = v[0];
	unordered_map<string, TypeTable::SynType> m15 = q15.getSynTable();

	CPPUNIT_ASSERT_EQUAL(Relationship::PARENT, r15.getRelType());
	expected = "w";
	CPPUNIT_ASSERT_EQUAL(expected, q15.getSelectedSyn());
	expected = "4";
	CPPUNIT_ASSERT_EQUAL(expected, r15.getToken1());
	expected = "w";
	CPPUNIT_ASSERT_EQUAL(expected, r15.getToken2()); 

	vec = qe.evaluateQuery(q15);
	CPPUNIT_ASSERT_EQUAL(5, vec[0]);

	//Query 16 assign a; Select a such that Parent*(11, a)
	qp.validate(s16);
	Query q16 = qp.parse();
	v = q16.getRelVect();
	Relationship r16 = v[0];
	unordered_map<string, TypeTable::SynType> m16 = q16.getSynTable();

	CPPUNIT_ASSERT_EQUAL(Relationship::PARENTSTAR, r16.getRelType());
	expected = "a";
	CPPUNIT_ASSERT_EQUAL(expected, q16.getSelectedSyn());
	expected = "11";
	CPPUNIT_ASSERT_EQUAL(expected, r16.getToken1());
	expected = "a";
	CPPUNIT_ASSERT_EQUAL(expected, r16.getToken2()); 

	vec = qe.evaluateQuery(q16);
	CPPUNIT_ASSERT_EQUAL(13, vec[0]);
	CPPUNIT_ASSERT_EQUAL(14, vec[1]);
	CPPUNIT_ASSERT_EQUAL(15, vec[2]);
	CPPUNIT_ASSERT_EQUAL(17, vec[3]);
	CPPUNIT_ASSERT_EQUAL(18, vec[4]);

	//Query 17 while w; Select w such that Parent*(w, 17)
	qp.validate(s17);
	Query q17 = qp.parse();
	v = q17.getRelVect();
	Relationship r17 = v[0];
	unordered_map<string, TypeTable::SynType> m17 = q17.getSynTable();

	CPPUNIT_ASSERT_EQUAL(Relationship::PARENTSTAR, r17.getRelType());
	expected = "w";
	CPPUNIT_ASSERT_EQUAL(expected, q17.getSelectedSyn());
	expected = "w";
	CPPUNIT_ASSERT_EQUAL(expected, r17.getToken1());
	expected = "17";
	CPPUNIT_ASSERT_EQUAL(expected, r17.getToken2()); 

	vec = qe.evaluateQuery(q17);

	CPPUNIT_ASSERT_EQUAL(4, vec[0]);
	CPPUNIT_ASSERT_EQUAL(5, vec[1]);
	CPPUNIT_ASSERT_EQUAL(9, vec[2]);
	CPPUNIT_ASSERT_EQUAL(11, vec[3]);
	CPPUNIT_ASSERT_EQUAL(16, vec[4]);


	//MODIFIES AND USES TESTS
	//Query 18
	string s18 = "assign a; Select a such that Modifies(a, \"x\")";
	qp.validate(s18);
	Query q18 = qp.parse();
	v = q18.getRelVect();
	Relationship r18 = v[0];
	unordered_map<string, TypeTable::SynType> m18 = q18.getSynTable();

	CPPUNIT_ASSERT_EQUAL(Relationship::MODIFIES, r18.getRelType());
	expected = "a";
	CPPUNIT_ASSERT_EQUAL(expected, q18.getSelectedSyn());
	expected = "a";
	CPPUNIT_ASSERT_EQUAL(expected, r18.getToken1());
	expected = "\"x\"";
	CPPUNIT_ASSERT_EQUAL(expected, r18.getToken2()); 
	
	vec = qe.evaluateQuery(q18);
	CPPUNIT_ASSERT_EQUAL(10, vec[0]);
	CPPUNIT_ASSERT_EQUAL(18, vec[1]);

	//Query 19
	string s19 = "stmt s; Select s such that Modifies(s, \"Romeo\")";
	qp.validate(s19);
	Query q19 = qp.parse();
	v = q19.getRelVect();
	Relationship r19 = v[0];
	unordered_map<string, TypeTable::SynType> m19 = q19.getSynTable();

	CPPUNIT_ASSERT_EQUAL(Relationship::MODIFIES, r19.getRelType());
	expected = "s";
	CPPUNIT_ASSERT_EQUAL(expected, q19.getSelectedSyn());
	expected = "s";
	CPPUNIT_ASSERT_EQUAL(expected, r19.getToken1());
	expected = "\"Romeo\"";
	CPPUNIT_ASSERT_EQUAL(expected, r19.getToken2()); 

	vec = qe.evaluateQuery(q19);
	/*for(vector<int>::iterator i = vec.begin(); i!=vec.end(); i++){
		cout<<*i<<endl;
	}*/
	CPPUNIT_ASSERT_EQUAL(4, vec[0]);
	CPPUNIT_ASSERT_EQUAL(5, vec[1]);
	CPPUNIT_ASSERT_EQUAL(9, vec[2]);
	CPPUNIT_ASSERT_EQUAL(11, vec[3]);
	CPPUNIT_ASSERT_EQUAL(12, vec[4]);
	CPPUNIT_ASSERT_EQUAL(13, vec[5]);

	//Query 20
	string s20 = "assign a; variable v; Select s such that Modifies(a, v)";
	qp.validate(s20);
	Query q20 = qp.parse();
	v = q20.getRelVect();
	Relationship r20 = v[0];
	unordered_map<string, TypeTable::SynType> m20 = q20.getSynTable();

	CPPUNIT_ASSERT_EQUAL(Relationship::MODIFIES, r20.getRelType());
	expected = "s";
	CPPUNIT_ASSERT_EQUAL(expected, q20.getSelectedSyn());
	expected = "a";
	CPPUNIT_ASSERT_EQUAL(expected, r20.getToken1());
	expected = "v";
	CPPUNIT_ASSERT_EQUAL(expected, r20.getToken2()); 

	vec = qe.evaluateQuery(q20);
	CPPUNIT_ASSERT_EQUAL(1, vec[0]);
	CPPUNIT_ASSERT_EQUAL(2, vec[1]);
	CPPUNIT_ASSERT_EQUAL(3, vec[2]);
	CPPUNIT_ASSERT_EQUAL(6, vec[3]);
	CPPUNIT_ASSERT_EQUAL(8, vec[4]);
	CPPUNIT_ASSERT_EQUAL(10, vec[5]);
	CPPUNIT_ASSERT_EQUAL(13, vec[6]);
	CPPUNIT_ASSERT_EQUAL(14, vec[7]);
	CPPUNIT_ASSERT_EQUAL(15, vec[8]);
	CPPUNIT_ASSERT_EQUAL(17, vec[9]);
	CPPUNIT_ASSERT_EQUAL(18, vec[10]);
	CPPUNIT_ASSERT_EQUAL(19, vec[11]);
	CPPUNIT_ASSERT_EQUAL(20, vec[12]);
	CPPUNIT_ASSERT_EQUAL(21, vec[13]);
	CPPUNIT_ASSERT_EQUAL(22, vec[14]);
	CPPUNIT_ASSERT_EQUAL(23, vec[15]);

	//Query 21
	string s21 = "while w; assign a; variable v; Select w such that Modifies(a, v)";
	qp.validate(s21);
	Query q21 = qp.parse();
	v = q21.getRelVect();
	Relationship r21 = v[0];
	unordered_map<string, TypeTable::SynType> m21 = q21.getSynTable();
	std::unordered_map<string, TypeTable::SynType>::iterator i = m21.find(q21.getSelectedSyn());
	expected = "w";
	CPPUNIT_ASSERT_EQUAL(expected, i->first);

	CPPUNIT_ASSERT_EQUAL(Relationship::MODIFIES, r21.getRelType());
	expected = "w";
	CPPUNIT_ASSERT_EQUAL(expected, q21.getSelectedSyn());
	expected = "a";
	CPPUNIT_ASSERT_EQUAL(expected, r21.getToken1());
	expected = "v";
	CPPUNIT_ASSERT_EQUAL(expected, r21.getToken2()); 

	vec = qe.evaluateQuery(q21);
	CPPUNIT_ASSERT_EQUAL(4, vec[0]);
	CPPUNIT_ASSERT_EQUAL(5, vec[1]);
	CPPUNIT_ASSERT_EQUAL(7, vec[2]);
	CPPUNIT_ASSERT_EQUAL(9, vec[3]);
	CPPUNIT_ASSERT_EQUAL(11, vec[4]);
	CPPUNIT_ASSERT_EQUAL(12, vec[5]);
	CPPUNIT_ASSERT_EQUAL(16, vec[6]);

	//Query 22
	string s22 = "while w; assign a; variable v; Select w such that Uses(a, v)";
	qp.validate(s22);
	Query q22 = qp.parse();
	v = q22.getRelVect();
	Relationship r22 = v[0];
	unordered_map<string, TypeTable::SynType> m22 = q22.getSynTable();

	CPPUNIT_ASSERT_EQUAL(Relationship::USES, r22.getRelType());
	expected = "w";
	CPPUNIT_ASSERT_EQUAL(expected, q22.getSelectedSyn());
	expected = "a";
	CPPUNIT_ASSERT_EQUAL(expected, r22.getToken1());
	expected = "v";
	CPPUNIT_ASSERT_EQUAL(expected, r22.getToken2()); 

	vec = qe.evaluateQuery(q22);
	for(vector<int>::iterator i = vec.begin(); i!=vec.end(); i++){
		cout<<*i<<endl;
	}
	CPPUNIT_ASSERT_EQUAL(4, vec[0]);
	CPPUNIT_ASSERT_EQUAL(5, vec[1]);
	CPPUNIT_ASSERT_EQUAL(7, vec[2]);
	CPPUNIT_ASSERT_EQUAL(9, vec[3]);
	CPPUNIT_ASSERT_EQUAL(11, vec[4]);
	CPPUNIT_ASSERT_EQUAL(12, vec[5]);
	CPPUNIT_ASSERT_EQUAL(16, vec[6]);

	//Query 23
	string s23 = "stmt s; Select s such that Uses(s, \"x\")";
	qp.validate(s23);
	Query q23 = qp.parse();
	v = q23.getRelVect();
	Relationship r23 = v[0];
	unordered_map<string, TypeTable::SynType> m23 = q23.getSynTable();

	CPPUNIT_ASSERT_EQUAL(Relationship::USES, r23.getRelType());
	expected = "s";
	CPPUNIT_ASSERT_EQUAL(expected, q23.getSelectedSyn());
	expected = "s";
	CPPUNIT_ASSERT_EQUAL(expected, r23.getToken1());
	expected = "\"x\"";
	CPPUNIT_ASSERT_EQUAL(expected, r23.getToken2()); 

	vec = qe.evaluateQuery(q23);
	for(vector<int>::iterator i = vec.begin(); i!=vec.end(); i++){
		cout<<*i<<endl;
	}
	//CPPUNIT_ASSERT_EQUAL(4, vec[0]);

 }