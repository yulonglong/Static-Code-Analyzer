#include <cppunit/config/SourcePrefix.h>
#include "QueryEvaluator.h"
#include "QueryEvaluatorTest.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class QueryEvaluator;
PKB* pkb;

void QueryEvaluatorTest::setUp(){
	pkb = PKB::getInstance();
}

void QueryEvaluatorTest::tearDown(){

}

CPPUNIT_TEST_SUITE_REGISTRATION( QueryEvaluatorTest );

void QueryEvaluatorTest::testEvaluateFollows(){
	QueryEvaluator qe(pkb);
	//Query 1 assign a; Select a such that Follows(a, 2);
	Query q;
	Relationship r("Follows", "a", "2");
	q.addRelationship(r);
	unordered_map<string,TypeTable::SynType> m;
	m.insert(make_pair<string, TypeTable::SynType>("a", TypeTable::ASSIGN));
	q.setSelectedSyn("a");
	q.setSynTable(m);

	Follows *f = Follows::getInstance();
	TypeTable *t = TypeTable::getInstance();

	//follows(1,2)
	f->setFollows(1, 2);
	t->insertStmtNumAndType(1, TypeTable::ASSIGN);

	vector<int> vec = qe.evaluateQuery(q);
	cout<<vec.empty()<<endl;
	cout<<vec[0]<<endl;
	CPPUNIT_ASSERT_EQUAL(1, vec[0]);

	
	//Query 2 assign a; Select a such that Follows(1, a);
	Query q2;
	Relationship r2("Follows", "1", "a");
	q2.addRelationship(r2);
	unordered_map<string,TypeTable::SynType> m2;
	m2.insert(make_pair<string, TypeTable::SynType>("a", TypeTable::ASSIGN));
	q2.setSelectedSyn("a");
	q2.setSynTable(m2);

	t->insertStmtNumAndType(2, TypeTable::ASSIGN);
	vec = qe.evaluateQuery(q2);
	cout<<vec.empty()<<endl;
	cout<<vec[0]<<endl;
	CPPUNIT_ASSERT_EQUAL(2, vec[0]);

	//Query 3 assign a; Select a such that Follows(w, a);
	Query q3;
	Relationship r3("Follows", "w", "a");
	q3.addRelationship(r3);
	unordered_map<string,TypeTable::SynType> m3;
	m3.insert(make_pair<string, TypeTable::SynType>("a", TypeTable::ASSIGN));
	m3.insert(make_pair<string, TypeTable::SynType>("w", TypeTable::WHILE));
	q3.setSelectedSyn("a");
	q3.setSynTable(m3);

	//Follows(2,3)
	f->setFollows(2, 3);
	//Follows(3, 7)
	f->setFollows(3, 7);
	t->insertStmtNumAndType(3, TypeTable::WHILE);
	t->insertStmtNumAndType(7, TypeTable::ASSIGN);
	vec = qe.evaluateQuery(q3);
	cout<<vec.empty()<<endl;
	cout<<vec[0]<<endl;
	CPPUNIT_ASSERT_EQUAL(7, vec[0]);

	//Query 4 while w; Select w such that Follows(w, a);
	Query q4;
	Relationship r4("Follows", "w", "a");
	q4.addRelationship(r4);
	unordered_map<string,TypeTable::SynType> m4;
	m4.insert(make_pair<string, TypeTable::SynType>("a", TypeTable::ASSIGN));
	m4.insert(make_pair<string, TypeTable::SynType>("w", TypeTable::WHILE));
	q4.setSelectedSyn("w");
	q4.setSynTable(m4);

	vec = qe.evaluateQuery(q4);
	cout<<vec.empty()<<endl;
	cout<<vec[0]<<endl;
	CPPUNIT_ASSERT_EQUAL(3, vec[0]);

	//Query 5 while w; Select w such that Follows(1, 2);
	Query q5;
	Relationship r5("Follows", "1", "2");
	q5.addRelationship(r5);
	unordered_map<string,TypeTable::SynType> m5;
	m5.insert(make_pair<string, TypeTable::SynType>("w", TypeTable::WHILE));
	q5.setSelectedSyn("w");
	q5.setSynTable(m5);

	vec = qe.evaluateQuery(q5);
	cout<<vec.empty()<<endl;
	cout<<vec[0]<<endl;
	CPPUNIT_ASSERT_EQUAL(3, vec[0]);

	//Query 6 Select BOOLEAN such that Follows(1, 2);
	Query q6;
	Relationship r6("Follows", "1", "2");
	q6.addRelationship(r6);
	unordered_map<string,TypeTable::SynType> m6;
	q6.setSelectedSyn("BOOLEAN");
	q6.setSynTable(m6);

	bool flag = qe.evaluateQueryBoolean(q6);
	CPPUNIT_ASSERT_EQUAL(true, flag);

	//Query 7 Select BOOLEAN such that Follows*(1, 3);
	Query q7;
	Relationship r7("Follows*", "1", "3");
	q7.addRelationship(r7);
	unordered_map<string,TypeTable::SynType> m7;
	q7.setSelectedSyn("BOOLEAN");
	q7.setSynTable(m7);

	flag = qe.evaluateQueryBoolean(q7);
	CPPUNIT_ASSERT_EQUAL(true, flag);

	//Query 8 assign a; Select a such that Follows*(a, 3);
	Query q8;
	Relationship r8("Follows*", "a", "3");
	q8.addRelationship(r8);
	unordered_map<string,TypeTable::SynType> m8;
	m8.insert(make_pair<string, TypeTable::SynType>("a", TypeTable::ASSIGN));
	q8.setSelectedSyn("a");
	q8.setSynTable(m8);

	vec = qe.evaluateQuery(q8);
	//cout<<"VECTOR IS "<<vec.empty()<<endl;
	cout<<vec[0]<<endl;
	CPPUNIT_ASSERT_EQUAL(1, vec[0]);

	//Query 9 while w; Select w such that Follows*(1, w);
	Query q9;
	Relationship r9("Follows*", "1", "w");
	q9.addRelationship(r9);
	unordered_map<string,TypeTable::SynType> m9;
	m9.insert(make_pair<string, TypeTable::SynType>("w", TypeTable::WHILE));
	q9.setSelectedSyn("w");
	q9.setSynTable(m9);

	vec = qe.evaluateQuery(q9);
	//cout<<"VECTOR IS "<<vec.empty()<<endl;
	cout<<vec[0]<<endl;
	CPPUNIT_ASSERT_EQUAL(3, vec[0]);

	//Query 10 assign a; while w; Select w such that Follows*(a, w);
	Query q10;
	Relationship r10("Follows*", "a", "w");
	q10.addRelationship(r10);
	unordered_map<string,TypeTable::SynType> m10;
	m10.insert(make_pair<string, TypeTable::SynType>("w", TypeTable::WHILE));
	m10.insert(make_pair<string, TypeTable::SynType>("a", TypeTable::ASSIGN));
	q10.setSelectedSyn("w");
	q10.setSynTable(m10);

	vec = qe.evaluateQuery(q10);
	//cout<<"VECTOR IS "<<vec.empty()<<endl;
	cout<<vec[0]<<endl;
	CPPUNIT_ASSERT_EQUAL(3, vec[0]);
	
	return;
}

void QueryEvaluatorTest::testEvaluateParent(){
	QueryEvaluator qe(pkb);

	//Query 1 assign a; Select a such that Parent(1, a);
	Query q;
	Relationship r("Parent", "1", "a");
	q.addRelationship(r);
	unordered_map<string,TypeTable::SynType> m;
	m.insert(make_pair<string, TypeTable::SynType>("a", TypeTable::ASSIGN));
	q.setSelectedSyn("a");
	q.setSynTable(m);

	Parent *p = Parent::getInstance();
	TypeTable *t = TypeTable::getInstance();

	//parent(1,2)
	p->setParent(1, 2);
	t->insertStmtNumAndType(1, TypeTable::WHILE);
	t->insertStmtNumAndType(2, TypeTable::ASSIGN);

	vector<int> vec = qe.evaluateQuery(q);
	cout<<vec.empty()<<endl;
	cout<<vec[0]<<endl;
	CPPUNIT_ASSERT_EQUAL(2, vec[0]);

	
	//Query 2 while w; Select w such that Parent(w, 2);
	Query q2;
	Relationship r2("Parent", "w", "2");
	q2.addRelationship(r2);
	unordered_map<string,TypeTable::SynType> m2;
	m2.insert(make_pair<string, TypeTable::SynType>("w", TypeTable::WHILE));
	q2.setSelectedSyn("w");
	q2.setSynTable(m2);

	t->insertStmtNumAndType(2, TypeTable::ASSIGN);
	vec = qe.evaluateQuery(q2);
	cout<<vec.empty()<<endl;
	cout<<vec[0]<<endl;
	CPPUNIT_ASSERT_EQUAL(1, vec[0]);

	//Query 3 assign a; Select a such that Parent(w, a);
	Query q3;
	Relationship r3("Parent", "w", "a");
	q3.addRelationship(r3);
	unordered_map<string,TypeTable::SynType> m3;
	m3.insert(make_pair<string, TypeTable::SynType>("a", TypeTable::ASSIGN));
	m3.insert(make_pair<string, TypeTable::SynType>("w", TypeTable::WHILE));
	q3.setSelectedSyn("a");
	q3.setSynTable(m3);

	vec = qe.evaluateQuery(q3);
	cout<<vec.empty()<<endl;
	cout<<vec[0]<<endl;
	CPPUNIT_ASSERT_EQUAL(2, vec[0]);

	//Query 4 while w; Select w such that Parent(w, a);
	Query q4;
	Relationship r4("Parent", "w", "a");
	q4.addRelationship(r4);
	unordered_map<string,TypeTable::SynType> m4;
	m4.insert(make_pair<string, TypeTable::SynType>("a", TypeTable::ASSIGN));
	m4.insert(make_pair<string, TypeTable::SynType>("w", TypeTable::WHILE));
	q4.setSelectedSyn("w");
	q4.setSynTable(m4);

	vec = qe.evaluateQuery(q4);
	cout<<vec.empty()<<endl;
	cout<<vec[0]<<endl;
	CPPUNIT_ASSERT_EQUAL(1, vec[0]);

	//Query 5 while w; Select w such that Parent(1, 2);
	Query q5;
	Relationship r5("Parent", "1", "2");
	q5.addRelationship(r5);
	unordered_map<string,TypeTable::SynType> m5;
	m5.insert(make_pair<string, TypeTable::SynType>("w", TypeTable::WHILE));
	q5.setSelectedSyn("w");
	q5.setSynTable(m5);

	vec = qe.evaluateQuery(q5);
	cout<<vec.empty()<<endl;
	cout<<vec[0]<<endl;
	CPPUNIT_ASSERT_EQUAL(1, vec[0]);

	//Query 6 Select BOOLEAN such that Parent(1, 2);
	Query q6;
	Relationship r6("Parent", "1", "2");
	q6.addRelationship(r6);
	unordered_map<string,TypeTable::SynType> m6;
	q6.setSelectedSyn("BOOLEAN");
	q6.setSynTable(m6);

	bool flag = qe.evaluateQueryBoolean(q6);
	CPPUNIT_ASSERT_EQUAL(true, flag);

	//Query 7 Select BOOLEAN such that Parent*(1, 4);
	//parent(1,3)
	p->setParent(1,3);
	//parent(3,4)
	p->setParent(3,4);
	t->insertStmtNumAndType(3, TypeTable::WHILE);
	t->insertStmtNumAndType(4, TypeTable::ASSIGN);
	Query q7;
	Relationship r7("Parent*", "1", "4");
	q7.addRelationship(r7);
	unordered_map<string,TypeTable::SynType> m7;
	q7.setSelectedSyn("BOOLEAN");
	q7.setSynTable(m7);

	flag = qe.evaluateQueryBoolean(q7);
	CPPUNIT_ASSERT_EQUAL(true, flag);

	//Query 8 while w; Select w such that Parent*(w, 4);
	Query q8;
	Relationship r8("Parent*", "w", "4");
	q8.addRelationship(r8);
	unordered_map<string,TypeTable::SynType> m8;
	m8.insert(make_pair<string, TypeTable::SynType>("w", TypeTable::WHILE));
	q8.setSelectedSyn("w");
	q8.setSynTable(m8);

	vec = qe.evaluateQuery(q8);
	CPPUNIT_ASSERT_EQUAL(1, vec[0]);
	CPPUNIT_ASSERT_EQUAL(3, vec[1]);

	//Query 9 assign a; Select a such that Parent*(1, a);
	Query q9;
	Relationship r9("Parent*", "1", "a");
	q9.addRelationship(r9);
	unordered_map<string,TypeTable::SynType> m9;
	m9.insert(make_pair<string, TypeTable::SynType>("a", TypeTable::ASSIGN));
	q9.setSelectedSyn("a");
	q9.setSynTable(m9);

	vec = qe.evaluateQuery(q9);
	CPPUNIT_ASSERT_EQUAL(2, vec[0]);
	CPPUNIT_ASSERT_EQUAL(4, vec[1]);

	//Query 10 assign a; Select a such that Parent*(w, a);
	Query q10;
	Relationship r10("Parent*", "w", "a");
	q10.addRelationship(r10);
	unordered_map<string,TypeTable::SynType> m10;
	m10.insert(make_pair<string, TypeTable::SynType>("w", TypeTable::WHILE));
	m10.insert(make_pair<string, TypeTable::SynType>("a", TypeTable::ASSIGN));
	q10.setSelectedSyn("a");
	q10.setSynTable(m10);

	vec = qe.evaluateQuery(q10);
	for(vector<int>::iterator i = vec.begin(); i!=vec.end(); i++){
		cout<<*i<<endl;
	}
	CPPUNIT_ASSERT_EQUAL(2, vec[0]);
	CPPUNIT_ASSERT_EQUAL(4, vec[1]);
}

void QueryEvaluatorTest::testEvaluateModifies(){
	QueryEvaluator qe(pkb);

	//Query 1 assign a; Select a such that Modifies(a, "x");
	Query q;
	Relationship r("Modifies", "a", "\"x\"");
	q.addRelationship(r);
	unordered_map<string,TypeTable::SynType> map;
	map.insert(make_pair<string, TypeTable::SynType>("a", TypeTable::ASSIGN));
	q.setSelectedSyn("a");
	q.setSynTable(map);

	Modifies *m = Modifies::getInstance();
	TypeTable *t = TypeTable::getInstance();
	VarTable *v = pkb->getVarTable();

	//modifies(1, "x")
	v->insertVar("x");
	m->setModifies(1, "x");
	t->insertStmtNumAndType(1, TypeTable::ASSIGN);

	vector<int> vec = qe.evaluateQuery(q);
	cout<<vec.empty()<<endl;
	cout<<vec[0]<<endl;
	CPPUNIT_ASSERT_EQUAL(1, vec[0]);

	//Query 2 variable v; Select v such that Modifies(1, v);
	Query q2;
	Relationship r2("Modifies", "1", "v");
	q2.addRelationship(r2);
	unordered_map<string,TypeTable::SynType> map2;
	map2.insert(make_pair<string, TypeTable::SynType>("v", TypeTable::VARIABLE));
	q2.setSelectedSyn("v");
	q2.setSynTable(map2);

	vec = qe.evaluateQuery(q2);
	cout<<vec.empty()<<endl;
	cout<<vec[0]<<endl;
	string expected = "x";
	CPPUNIT_ASSERT_EQUAL(expected, v->getVarName(vec[0]));

	//Query 3 variable v; Select v such that Modifies(a, v);
	Query q3;
	Relationship r3("Modifies", "a", "v");
	q3.addRelationship(r3);
	unordered_map<string,TypeTable::SynType> map3;
	map3.insert(make_pair<string, TypeTable::SynType>("v", TypeTable::VARIABLE));
	map3.insert(make_pair<string, TypeTable::SynType>("a", TypeTable::ASSIGN));
	q3.setSelectedSyn("v");
	q3.setSynTable(map3);

	vec = qe.evaluateQuery(q3);
	cout<<vec.empty()<<endl;
	cout<<vec[0]<<endl;
	expected = "x";
	CPPUNIT_ASSERT_EQUAL(expected, v->getVarName(vec[0]));

	//Query 4 assign a; Select a such that Modifies(a, v);
	Query q4;
	Relationship r4("Modifies", "a", "v");
	q4.addRelationship(r4);
	unordered_map<string,TypeTable::SynType> map4;
	map4.insert(make_pair<string, TypeTable::SynType>("v", TypeTable::VARIABLE));
	map4.insert(make_pair<string, TypeTable::SynType>("a", TypeTable::ASSIGN));
	q4.setSelectedSyn("a");
	q4.setSynTable(map4);

	vec = qe.evaluateQuery(q4);
	cout<<vec.empty()<<endl;
	cout<<vec[0]<<endl;
	CPPUNIT_ASSERT_EQUAL(1, vec[0]);

	//Query 5 Select BOOLEAN such that Modifies(1, "x");
	Query q5;
	Relationship r5("Modifies", "1", "\"x\"");
	q5.addRelationship(r5);
	unordered_map<string,TypeTable::SynType> map5;
	q5.setSelectedSyn("BOOLEAN");
	q5.setSynTable(map5);

	bool flag = qe.evaluateQueryBoolean(q5);
	CPPUNIT_ASSERT_EQUAL(true, flag);

	//Query 6 stmt s; assign a; Select s such that Modifies(a, "x");
	Query q6;
	Relationship r6("Modifies", "a", "\"x\"");
	q6.addRelationship(r6);
	unordered_map<string,TypeTable::SynType> map6;
	map6.insert(make_pair<string, TypeTable::SynType>("s", TypeTable::STMT));
	map6.insert(make_pair<string, TypeTable::SynType>("a", TypeTable::ASSIGN));
	q6.setSelectedSyn("s");
	q6.setSynTable(map6);

	vec = qe.evaluateQuery(q6);
	/*for(vector<int>::iterator i = vec.begin(); i!=vec.end(); i++){
		cout<<*i<<endl;
	}*/
	CPPUNIT_ASSERT_EQUAL(1, vec[0]);
	CPPUNIT_ASSERT_EQUAL(2, vec[1]);
	CPPUNIT_ASSERT_EQUAL(3, vec[2]);
	CPPUNIT_ASSERT_EQUAL(4, vec[3]);
	CPPUNIT_ASSERT_EQUAL(5, vec[4]);

}

void QueryEvaluatorTest::testEvaluateUses(){
	QueryEvaluator qe(pkb);

	//Query 1 assign a; Select a such that Uses(a, "x");
	Query q;
	Relationship r("Uses", "a", "\"x\"");
	q.addRelationship(r);
	unordered_map<string,TypeTable::SynType> map;
	map.insert(make_pair<string, TypeTable::SynType>("a", TypeTable::ASSIGN));
	q.setSelectedSyn("a");
	q.setSynTable(map);

	Uses *u = Uses::getInstance();
	TypeTable *t = TypeTable::getInstance();
	VarTable *v = pkb->getVarTable();

	//uses(1, "x")
	v->insertVar("x");
	u->setUses(1, "x");
	t->insertStmtNumAndType(1, TypeTable::ASSIGN);

	vector<int> vec = qe.evaluateQuery(q);
	cout<<vec.empty()<<endl;
	cout<<vec[0]<<endl;
	CPPUNIT_ASSERT_EQUAL(1, vec[0]);

	
	//Query 2 variable v; Select v such that Modifies(1, v);
	Query q2;
	Relationship r2("Uses", "1", "v");
	q2.addRelationship(r2);
	unordered_map<string,TypeTable::SynType> map2;
	map2.insert(make_pair<string, TypeTable::SynType>("v", TypeTable::VARIABLE));
	q2.setSelectedSyn("v");
	q2.setSynTable(map2);

	vec = qe.evaluateQuery(q2);
	cout<<vec.empty()<<endl;
	cout<<vec[0]<<endl;
	string expected = "x";
	CPPUNIT_ASSERT_EQUAL(expected, v->getVarName(vec[0]));
	
	//Query 3 variable v; Select v such that Modifies(a, v);
	Query q3;
	Relationship r3("Uses", "a", "v");
	q3.addRelationship(r3);
	unordered_map<string,TypeTable::SynType> map3;
	map3.insert(make_pair<string, TypeTable::SynType>("v", TypeTable::VARIABLE));
	map3.insert(make_pair<string, TypeTable::SynType>("a", TypeTable::ASSIGN));
	q3.setSelectedSyn("v");
	q3.setSynTable(map3);

	vec = qe.evaluateQuery(q3);
	cout<<vec.empty()<<endl;
	cout<<vec[0]<<endl;
	expected = "x";
	CPPUNIT_ASSERT_EQUAL(expected, v->getVarName(vec[0]));
	
	//Query 4 assign a; Select a such that Modifies(a, v);
	Query q4;
	Relationship r4("Uses", "a", "v");
	q4.addRelationship(r4);
	unordered_map<string,TypeTable::SynType> map4;
	map4.insert(make_pair<string, TypeTable::SynType>("v", TypeTable::VARIABLE));
	map4.insert(make_pair<string, TypeTable::SynType>("a", TypeTable::ASSIGN));
	q4.setSelectedSyn("a");
	q4.setSynTable(map4);

	vec = qe.evaluateQuery(q4);
	cout<<vec.empty()<<endl;
	cout<<vec[0]<<endl;
	CPPUNIT_ASSERT_EQUAL(1, vec[0]);
	
	//Query 5 Select BOOLEAN such that Modifies(1, "x");
	Query q5;
	Relationship r5("Uses", "1", "\"x\"");
	q5.addRelationship(r5);
	unordered_map<string,TypeTable::SynType> map5;
	q5.setSelectedSyn("BOOLEAN");
	q5.setSynTable(map5);

	bool flag = qe.evaluateQueryBoolean(q5);
	CPPUNIT_ASSERT_EQUAL(true, flag);

	//Query 6 stmt s; assign a; Select s such that Modifies(a, "x");
	Query q6;
	Relationship r6("Uses", "a", "\"x\"");
	q6.addRelationship(r6);
	unordered_map<string,TypeTable::SynType> map6;
	map6.insert(make_pair<string, TypeTable::SynType>("s", TypeTable::STMT));
	map6.insert(make_pair<string, TypeTable::SynType>("a", TypeTable::ASSIGN));
	q6.setSelectedSyn("s");
	q6.setSynTable(map6);

	vec = qe.evaluateQuery(q6);
	/*for(vector<int>::iterator i = vec.begin(); i!=vec.end(); i++){
		cout<<*i<<endl;
	}*/
	CPPUNIT_ASSERT_EQUAL(1, vec[0]);
	CPPUNIT_ASSERT_EQUAL(2, vec[1]);
	CPPUNIT_ASSERT_EQUAL(3, vec[2]);
	CPPUNIT_ASSERT_EQUAL(4, vec[3]);
	CPPUNIT_ASSERT_EQUAL(5, vec[4]);
	
}
