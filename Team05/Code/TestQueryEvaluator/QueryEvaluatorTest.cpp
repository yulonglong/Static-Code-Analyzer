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
	
	//INITIALIZATION
	QueryEvaluator qe(pkb);
	
	TypeTable *t = pkb->getTypeTable();
	Follows* f = pkb->getFollows();
	Parent* p = pkb->getParent();
	Calls* c = pkb->getCalls();
	Modifies* m = pkb->getModifies();
	Uses * u = pkb->getUses();
	ProcTable * pt = pkb->getProcTable();
	VarTable* vt = pkb->getVarTable();
	Next* n = pkb->getNext();

	Query q;
	Relationship r;
	unordered_map<string,TypeTable::SynType> map;
	unordered_map<string, vector<int>> answer;
	vector<string> selectedSyn;

	//SETTINGS
	t->insertStmtNumAndType(1, TypeTable::WHILE);
	t->insertStmtNumAndType(2, TypeTable::ASSIGN);
	t->insertStmtNumAndType(3, TypeTable::CALL);
	t->insertStmtNumAndType(4, TypeTable::ASSIGN);
	t->insertStmtNumAndType(5, TypeTable::ASSIGN);
	t->insertStmtNumAndType(6, TypeTable::ASSIGN);
	t->insertStmtNumAndType(7, TypeTable::ASSIGN);

	t->insertStmtNumAndType(8, TypeTable::IF);
	t->insertStmtNumAndType(9, TypeTable::WHILE);
	t->insertStmtNumAndType(10, TypeTable::CALL);
	t->insertStmtNumAndType(11, TypeTable::ASSIGN);

	n->setNext(1,2);
	n->setNext(2,3);
	n->setNext(3,4);
	n->setNext(4,5);
	n->setNext(5,1);
	n->setNext(1,6);
	n->setNext(6,7);
	n->setNext(7,8);
	n->setNext(8,9);
	n->setNext(8,11);
	n->setNext(9,10);
	n->setNext(9,11);
	n->setNext(10,9);

	f->setFollows(2, 3);
	f->setFollows(3, 4);
	f->setFollows(4, 5);
	f->setFollows(1, 6);
	f->setFollows(6, 7);

	p->setParent(1, 2);
	p->setParent(1, 3);
	p->setParent(1, 4);
	p->setParent(1, 5);
	p->setParent(8, 9);
	p->setParent(9, 10);

	pt->insertProc("First");
	pt->insertProc("Second");
	pt->insertProc("Third");
	pt->insertProc("Fourth");

	vt->insertVar("x");
	vt->insertVar("y");
	vt->insertVar("z");
	
	m->setModifies(2, "x");
	m->setModifies(4, "y");
	m->setModifies(5, "z");
	m->setModifies(1, "x");
	m->setModifies(1, "y");
	m->setModifies(1, "z");

	vector<int> procedureFirstModifies;
	procedureFirstModifies.push_back(0);
	procedureFirstModifies.push_back(1);
	procedureFirstModifies.push_back(2);
	m->setModifiesProc(0, procedureFirstModifies);

	vector<int> procedureSecondModifies;
	procedureSecondModifies.push_back(1);
	procedureSecondModifies.push_back(2);
	m->setModifiesProc(1, procedureSecondModifies);

	c->setCalls("First", "Second", 3);
	c->setCalls("Second", "Third", 10);

	map.insert(make_pair<string, TypeTable::SynType>("a", TypeTable::ASSIGN));
	map.insert(make_pair<string, TypeTable::SynType>("a2", TypeTable::ASSIGN));	
	map.insert(make_pair<string, TypeTable::SynType>("a3", TypeTable::ASSIGN));	
	map.insert(make_pair<string, TypeTable::SynType>("c", TypeTable::CALL));
	map.insert(make_pair<string, TypeTable::SynType>("p", TypeTable::PROCEDURE));
	map.insert(make_pair<string, TypeTable::SynType>("p2", TypeTable::PROCEDURE));
	map.insert(make_pair<string, TypeTable::SynType>("q", TypeTable::PROCEDURE));
	map.insert(make_pair<string, TypeTable::SynType>("q2", TypeTable::PROCEDURE));
	map.insert(make_pair<string, TypeTable::SynType>("s", TypeTable::STMT));
	map.insert(make_pair<string, TypeTable::SynType>("s2", TypeTable::STMT));	
	map.insert(make_pair<string, TypeTable::SynType>("s3", TypeTable::STMT));
	map.insert(make_pair<string, TypeTable::SynType>("s4", TypeTable::STMT));	
	map.insert(make_pair<string, TypeTable::SynType>("s5", TypeTable::STMT));	
	map.insert(make_pair<string, TypeTable::SynType>("s6", TypeTable::STMT));
	map.insert(make_pair<string, TypeTable::SynType>("s7", TypeTable::STMT));
	map.insert(make_pair<string, TypeTable::SynType>("s8", TypeTable::STMT));
	map.insert(make_pair<string, TypeTable::SynType>("v", TypeTable::VARIABLE));
	map.insert(make_pair<string, TypeTable::SynType>("w", TypeTable::WHILE));
	map.insert(make_pair<string, TypeTable::SynType>("w2", TypeTable::WHILE));

	q.setSynTable(map);
	
	//Follows(a,s)	r1
	r = Relationship("Follows", "a", "s");
	q.addRelationship(r);
	selectedSyn.push_back("a");
	selectedSyn.push_back("s");

	//Follows(4, a2) r2
	r = Relationship("Follows", "4", "a2");
	q.addRelationship(r);
	selectedSyn.push_back("a2");

	//Follows(w, 6) r3
	r = Relationship("Follows", "w", "6");
	q.addRelationship(r);
	selectedSyn.push_back("w");

	
	//Follows*(s2, s3) r4
	r = Relationship("Follows*", "s2", "s3");
	q.addRelationship(r);
	selectedSyn.push_back("s2");
	selectedSyn.push_back("s3");
	
	//Follows*(a, 5) r5
	r = Relationship("Follows*", "a", "5");
	q.addRelationship(r);

	//Follows*(a, 3) r6
	r = Relationship("Follows*", "a", "3");
	q.addRelationship(r);

	//Follows*(1, 7) r7
	r = Relationship("Follows*", "1", "7");
	q.addRelationship(r);

	//Follows*(w, 7) r8
	r = Relationship("Follows*", "w", "7");
	q.addRelationship(r);

	//Follows*(_,_) r9
	r = Relationship("Follows", "_", "_");
	q.addRelationship(r);

	//Follows*(w, _) r10
	r = Relationship("Follows", "w", "_");
	q.addRelationship(r);

	//Follows*(_, s) r11
	r = Relationship("Follows", "_", "s");
	q.addRelationship(r);

	//Follows*(_, 5) r12
	r = Relationship("Follows", "_", "_");
	q.addRelationship(r);

	/*
	//Parent(w, a3) r13
	r = Relationship("Parent", "w", "a3");
	q.addRelationship(r);
	selectedSyn.push_back("a3");

	//Parent(s4, s5) r14
	r = Relationship("Parent", "s4", "s5");
	q.addRelationship(r);
	selectedSyn.push_back("s4");
	selectedSyn.push_back("s5");

	//Parent(s4, 10) r15
	r = Relationship("Parent", "s4", "10");
	q.addRelationship(r);

	//Parent*(8, 10) r16
	r = Relationship("Parent*", "8", "10");
	q.addRelationship(r);

	//Parent*(w2, 10) r17
	r = Relationship("Parent*", "w2", "10");
	q.addRelationship(r);
	selectedSyn.push_back("w2");

	//Parent*(8, s5) r18
	r = Relationship("Parent*", "8", "s5");
	q.addRelationship(r);

	//Parent*(_, s5) r19
	r = Relationship("Parent*", "_", "s5");
	q.addRelationship(r);

	//Parent*(_,_) r20
	r = Relationship("Parent*", "_", "_");
	q.addRelationship(r);

	//Parent*(1, _) r21
	r = Relationship("Parent*", "1", "_");
	q.addRelationship(r);

	//Parent*(_, 9) r22
	r = Relationship("Parent*", "_", "9");
	q.addRelationship(r);

	//Modifies(p, v) r23
	r = Relationship("Modifies", "p", "v");
	q.addRelationship(r);
	selectedSyn.push_back("p");
	selectedSyn.push_back("v");

	//Modifies(a, v) r24
	r = Relationship("Modifies", "a", "v");
	q.addRelationship(r);

	//Modifies(_, v) r25
	r = Relationship("Modifies", "_", "v");
	q.addRelationship(r);

	//Modifies(w, _) r26
	r = Relationship("Modifies", "w", "_");
	q.addRelationship(r);

	//Modifies(p2, "y") r27
	r = Relationship("Modifies", "p2", "\"y\"");
	q.addRelationship(r);
	selectedSyn.push_back("p2");

	//Modifies(_, "z") r28
	r = Relationship("Modifies", "_", "\"z\"");
	q.addRelationship(r);
	
	//Modifies("First", "z") r29
	r = Relationship("Modifies", "\"First\"", "\"z\"");
	q.addRelationship(r);

	//Modifies("First", v) r30
	r = Relationship("Modifies", "\"First\"", "v");
	q.addRelationship(r);

	//Modifies(a, "x") r31
	r = Relationship("Modifies", "a", "\"x\"");
	q.addRelationship(r);

	//Calls (p2, q) r32
	r = Relationship("Calls", "p2", "q");
	q.addRelationship(r);
	selectedSyn.push_back("q");

	//Calls* (p2, q) 
	r = Relationship("Calls*", "p2", "q");
	q.addRelationship(r);

	//Calls*("First", "Third")
	r = Relationship("Calls*", "\"First\"", "\"Third\"");
	q.addRelationship(r);

	//Calls*(p, "Second")
	r = Relationship("Calls*", "p", "\"Second\"");
	q.addRelationship(r);

	//Calls*("Second", q2)
	r = Relationship("Calls*", "\"Second\"", "q2");
	q.addRelationship(r);
	selectedSyn.push_back("q2");

	//Calls*(_, q2)
	r = Relationship("Calls*", "_", "q2");
	q.addRelationship(r);

	//Calls*(_, "Second")
	r = Relationship("Calls*", "_", "\"Second\"");
	q.addRelationship(r);

	//Calls*("Second", _)
	r = Relationship("Calls*", "\"Second\"", "_");
	q.addRelationship(r);

	//Next(a, c)
	r = Relationship("Next", "a", "c");
	q.addRelationship(r);
	selectedSyn.push_back("c");

	//Next(8, s6)
	r = Relationship("Next", "8", "s6");
	q.addRelationship(r);
	selectedSyn.push_back("s6");

	//Next(s7, 11)
	r = Relationship("Next", "s7", "11");
	q.addRelationship(r);
	selectedSyn.push_back("s7");

	//Next(7,8)
	r = Relationship("Next", "7", "8");
	q.addRelationship(r);

	//Next(s8, _)
	r = Relationship("Next", "s8", "_");
	q.addRelationship(r);
	selectedSyn.push_back("s8");

	//Next*(1, 5)
	r = Relationship("Next*", "1", "5");
	q.addRelationship(r);


	q.setSelectedSyn(selectedSyn);
	answer = qe.evaluateQuery(q);

	CPPUNIT_ASSERT_EQUAL(2, answer.find("a")->second.at(0));
	CPPUNIT_ASSERT_EQUAL(5, answer.find("a2")->second.at(0));
	CPPUNIT_ASSERT_EQUAL(2, answer.find("a3")->second.at(0));
	CPPUNIT_ASSERT_EQUAL(4, answer.find("a3")->second.at(1));
	CPPUNIT_ASSERT_EQUAL(5, answer.find("a3")->second.at(2));
	CPPUNIT_ASSERT_EQUAL(0, answer.find("p")->second.at(0));
	CPPUNIT_ASSERT_EQUAL(0, answer.find("p2")->second.at(0));
	CPPUNIT_ASSERT_EQUAL(1, answer.find("p2")->second.at(1));
	CPPUNIT_ASSERT_EQUAL(1, answer.find("q")->second.at(0));
	CPPUNIT_ASSERT_EQUAL(2, answer.find("q")->second.at(1));
	CPPUNIT_ASSERT_EQUAL(2, answer.find("q2")->second.at(0));
	CPPUNIT_ASSERT_EQUAL(3, answer.find("s")->second.at(0));
	CPPUNIT_ASSERT_EQUAL(1, answer.find("s2")->second.at(0));
	CPPUNIT_ASSERT_EQUAL(2, answer.find("s2")->second.at(1));
	CPPUNIT_ASSERT_EQUAL(3, answer.find("s2")->second.at(2));
	CPPUNIT_ASSERT_EQUAL(4, answer.find("s2")->second.at(3));
	CPPUNIT_ASSERT_EQUAL(3, answer.find("s3")->second.at(0));
	CPPUNIT_ASSERT_EQUAL(4, answer.find("s3")->second.at(1));
	CPPUNIT_ASSERT_EQUAL(5, answer.find("s3")->second.at(2));
	CPPUNIT_ASSERT_EQUAL(6, answer.find("s3")->second.at(3));
	CPPUNIT_ASSERT_EQUAL(9, answer.find("s4")->second.at(0));
	CPPUNIT_ASSERT_EQUAL(10, answer.find("s5")->second.at(0));

	CPPUNIT_ASSERT_EQUAL(9, answer.find("s6")->second.at(0));
	CPPUNIT_ASSERT_EQUAL(11, answer.find("s6")->second.at(1));
	CPPUNIT_ASSERT_EQUAL(8, answer.find("s7")->second.at(0));
	CPPUNIT_ASSERT_EQUAL(9, answer.find("s7")->second.at(1));
	CPPUNIT_ASSERT_EQUAL(0, answer.find("v")->second.at(0));
	CPPUNIT_ASSERT_EQUAL(1, answer.find("w")->second.at(0));
	CPPUNIT_ASSERT_EQUAL(9, answer.find("w2")->second.at(0));
	
	vector<int> k = answer.find("p2")->second;
	vector<int> j = answer.find("s8")->second;

	for(int i = 0; i<k.size(); i++){
		cout<<"parent ans1 = "<< k.at(i)<<endl;
	}
	for(int i=0; i<j.size(); i++){
		cout<<"parent ans2 = "<<j.at(i)<<endl;
	}

	n->printNextTable();

	/*
	//Query 1 assign a; Select a such that Follows(_ , _); r0
	Relationship r("Follows", "_", "_");
	unordered_map<string,TypeTable::SynType> m;
	m.insert(make_pair<string, TypeTable::SynType>("a", TypeTable::ASSIGN));
	m.insert(make_pair<string, TypeTable::SynType>("a1", TypeTable::ASSIGN));
	m.insert(make_pair<string, TypeTable::SynType>("a2", TypeTable::ASSIGN));
	m.insert(make_pair<string, TypeTable::SynType>("w", TypeTable::WHILE));
	m.insert(make_pair<string, TypeTable::SynType>("if", TypeTable::IF));
	m.insert(make_pair<string, TypeTable::SynType>("c", TypeTable::STMT));

	
	TypeTable *t = TypeTable::getInstance();
	Follows *f = Follows::getInstance(t);

	//setting follows(1,2)
	f->setFollows(1, 2);
	f->setFollows(2, 3);
	t->insertStmtNumAndType(1, TypeTable::WHILE);
	t->insertStmtNumAndType(3, TypeTable::ASSIGN);
	t->insertStmtNumAndType(2, TypeTable::ASSIGN);
	vector<Pair> ans;
	vector<string> tokens;

	qe.evaluateFollows(r, m, 0);
	ans = qe.relAns.find(0)->second;

	CPPUNIT_ASSERT_EQUAL(-1, ans.at(0).ans1);

	//Follows(a,3)  r1
	r = Relationship("Follows", "a", "3");
	qe.evaluateFollows(r, m, 1);
	ans = qe.relAns.find(1)->second;

	CPPUNIT_ASSERT_EQUAL(2, ans.at(0).ans1);
	tokens.push_back("_");
	tokens.push_back("_");
	qe.relParameters.insert(make_pair<int, vector<string>>(0, tokens));
	tokens.clear();
	tokens.push_back("a");
	tokens.push_back("3");
	qe.relParameters.insert(make_pair<int, vector<string>>(1, tokens));

	//Follows(_,c)
	r = Relationship("Follows", "_", "c");
	
	qe.evaluateFollows(r, m, 2);
	ans = qe.relAns.find(2)->second;

	CPPUNIT_ASSERT_EQUAL(2, ans.at(0).ans2);

	/*
	//Modifies(1 , "y")
	Calls* call = pkb->getCalls();
	call->setCalls("first", "second", 4);
	r = Relationship("Calls", "\"first\"", "\"second\"");

	qe.evaluateCalls(r,3);
	ans = qe.relAns.find(3)->second;
	CPPUNIT_ASSERT_EQUAL(-1, ans.at(0).ans2);*/

	/*
	//Parent(1,2) r3
	cout<<"r3"<<endl;
	Parent *p = Parent::getInstance(t);
	p->setParent(1, 2);
	r = Relationship("Parent", "1", "2");
	tokens.clear();
	tokens.push_back("1");
	tokens.push_back("2");
	qe.relParameters.insert(make_pair<int, vector<string>>(3, tokens));

	qe.evaluateParent(r, m, 3);
	ans = qe.relAns.find(3)->second;

	CPPUNIT_ASSERT_EQUAL(-1, ans.at(0).ans1);

	//Parent (w, 2) r4
	cout<<"r4"<<endl;
	r = Relationship("Parent", "w", "2");
	tokens.clear();
	tokens.push_back("w");
	tokens.push_back("2");
	qe.relParameters.insert(make_pair<int, vector<string>>(4, tokens));

	qe.evaluateParent(r, m, 4);
	ans = qe.relAns.find(4)->second;

	CPPUNIT_ASSERT_EQUAL(1, ans.at(0).ans1);

	//Parent (w,4) r5
	cout<<"r5"<<endl;
	r = Relationship("Parent", "w", "4");
	p->setParent(1, 4);
	tokens.clear();
	tokens.push_back("w");
	tokens.push_back("4");
	qe.relParameters.insert(make_pair<int, vector<string>>(5, tokens));

	qe.evaluateParent(r, m, 5);
	ans = qe.relAns.find(5)->second;

	//cout<<ans.empty()<<endl;
	CPPUNIT_ASSERT_EQUAL(1, ans.at(0).ans1);

	//Parent (5, a1) r6
	cout<<"r6"<<endl;
	r = Relationship("Parent", "5", "a1");
	p->setParent(5, 7);
	p->setParent(5, 6);
	t->insertStmtNumAndType(5, TypeTable::WHILE);
	t->insertStmtNumAndType(6, TypeTable::STMT);
	t->insertStmtNumAndType(7, TypeTable::ASSIGN);
	t->insertStmtNumAndType(4, TypeTable::ASSIGN);
	tokens.clear();
	tokens.push_back("5");
	tokens.push_back("a");
	qe.relParameters.insert(make_pair<int, vector<string>>(6, tokens));

	qe.evaluateParent(r, m, 6);
	ans = qe.relAns.find(6) ->second;

	CPPUNIT_ASSERT_EQUAL(7, ans.at(0).ans2);

	//Follows(6, a1) r7
	cout<<"r7"<<endl;
	f->setFollows(6, 7);
	r = Relationship("Follows", "6", "a1");
	tokens.clear();
	tokens.push_back("6");
	tokens.push_back("a1");
	qe.relParameters.insert(make_pair<int, vector<string>>(7, tokens));

	qe.evaluateFollows(r, m, 7);
	ans = qe.relAns.find(7) -> second;

	CPPUNIT_ASSERT_EQUAL(7, ans.at(0).ans2);
	
	
	//Parent(w, a2) r8
	r = Relationship("Parent", "w", "a2");
	cout<<"r8"<<endl;
	qe.evaluateParent(r, m, 8);
	ans = qe.relAns.find(8)->second;
	tokens.clear();
	tokens.push_back("w");
	tokens.push_back("a2");
	qe.relParameters.insert(make_pair<int, vector<string>>(8, tokens));

	
	CPPUNIT_ASSERT_EQUAL(1, ans.at(0).ans1);
	CPPUNIT_ASSERT_EQUAL(2, ans.at(0).ans2);
	CPPUNIT_ASSERT_EQUAL(1, ans.at(1).ans1);
	CPPUNIT_ASSERT_EQUAL(4, ans.at(1).ans2);

	
	//Parent(w, _) r9
	cout<<"r9"<<endl;
	r = Relationship("Parent", "w", "_");
	tokens.clear();
	tokens.push_back("w");
	tokens.push_back("_");
	qe.relParameters.insert(make_pair<int, vector<string>>(9, tokens));

	qe.evaluateParent(r, m, 9);
	ans = qe.relAns.find(9)->second;

	CPPUNIT_ASSERT_EQUAL(1, ans.at(0).ans1);
	//CPPUNIT_ASSERT_EQUAL(5, ans.at(2).ans1);

	
	//Parent(_ ,a) r10
	cout<<"r10"<<endl;
	r = Relationship("Parent", "_", "a");
	tokens.clear();
	tokens.push_back("_");
	tokens.push_back("a");
	qe.relParameters.insert(make_pair<int, vector<string>>(10, tokens));

	qe.evaluateParent(r, m, 10);
	ans = qe.relAns.find(10)->second;

	CPPUNIT_ASSERT_EQUAL(2, ans.at(0).ans2);

	//Modifies(a, "x") r11
	cout<<"r11"<<endl;
	Modifies* mod = pkb->getModifies();
	VarTable *varT = pkb->getVarTable();
	varT->insertVar("x");
	mod->setModifies(2, "x");
	r = Relationship("Modifies", "a", "\"x\"");
	tokens.clear();
	tokens.push_back("a");
	tokens.push_back("\"x\"");
	qe.relParameters.insert(make_pair<int, vector<string>>(11, tokens));

	qe.evaluateModifies(r, m, 11);
	ans = qe.relAns.find(11)->second;

	CPPUNIT_ASSERT_EQUAL(2, ans.at(0).ans1);

	//Modifies(a, v) r12
	cout<<"r12"<<endl;
	r = Relationship("Modifies", "a", "v");
	tokens.clear();
	tokens.push_back("a");
	tokens.push_back("v");
	qe.relParameters.insert(make_pair<int, vector<string>>(12, tokens));

	qe.evaluateModifies(r, m, 12);
	ans = qe.relAns.find(12)->second;

	CPPUNIT_ASSERT_EQUAL(0, ans.at(0).ans2);

	//Modifies(2, "x") r13
	r = Relationship("Modifies", "2", "\"x\"");
	ProcTable* proc = pkb->getProcTable();

	tokens.clear();
	tokens.push_back("a");
	tokens.push_back("v");
	qe.relParameters.insert(make_pair<int, vector<string>>(13, tokens));

	qe.evaluateModifies(r, m, 13);
	ans = qe.relAns.find(13)->second;

	CPPUNIT_ASSERT_EQUAL(-1, ans.at(0).ans1);

	//Modifies(2, v) r14
	r = Relationship("Modifies", "2", "v");
	tokens.push_back("2");
	tokens.push_back("v");
	qe.relParameters.insert(make_pair<int, vector<string>>(14, tokens));

	qe.evaluateModifies(r, m, 14);
	ans = qe.relAns.find(14)->second;

	CPPUNIT_ASSERT_EQUAL(0, ans.at(0).ans2);

	//Modifies(p, "x") r15
	cout<<"Evaluating Relationship 15"<<endl;
	r = Relationship("Modifies", "p", "\"x\"");
	tokens.push_back("p");
	tokens.push_back("\"x\"");
	qe.relParameters.insert(make_pair<int, vector<string>>(15, tokens));
	m.insert(make_pair<string, TypeTable::SynType>("p", TypeTable::PROCEDURE));
	proc->insertProc("First");
	vector<int> varIndexes;
	varIndexes.push_back(0);
	mod->setModifiesProc(proc->getProcIndex("First"),varIndexes);

	qe.evaluateModifies(r, m, 15);
	ans = qe.relAns.find(15)->second;

	CPPUNIT_ASSERT_EQUAL(0, ans.at(0).ans1);

	//Modifies("First", "x") r16
	r = Relationship("Modifies", "\"First\"", "\"x\"");
	tokens.push_back("\"First\"");
	tokens.push_back("\"x\"");
	qe.relParameters.insert(make_pair<int, vector<string>>(15, tokens));
	
	qe.evaluateModifies(r, m, 16);
	ans = qe.relAns.find(16)->second;

	CPPUNIT_ASSERT_EQUAL(-1, ans.at(0).ans1);

	//Modifies(p, v) r17
	r = Relationship("Modifies", "p", "v");
	m.insert(make_pair<string, TypeTable::SynType>("v", TypeTable::VARIABLE));
	tokens.push_back("p");
	tokens.push_back("v");
	qe.relParameters.insert(make_pair<int, vector<string>>(17, tokens));
	
	qe.evaluateModifies(r, m, 17);
	ans = qe.relAns.find(17)->second;

	CPPUNIT_ASSERT_EQUAL(0, ans.at(0).ans1);
	CPPUNIT_ASSERT_EQUAL(0, ans.at(0).ans2);
	
	//Modifies("First", v) r18
	r = Relationship("Modifies", "\"First\"", "v");
	tokens.push_back("\"First\"");
	tokens.push_back("v");
	qe.relParameters.insert(make_pair<int, vector<string>>(18, tokens));

	qe.evaluateModifies(r, m, 18);
	ans = qe.relAns.find(18)->second;

	CPPUNIT_ASSERT_EQUAL(0, ans.at(0).ans2);

	//Modifies(_,_) r19
	r = Relationship("Modifies", "_", "_");

	qe.evaluateModifies(r, m, 19);
	ans = qe.relAns.find(19)->second;

	CPPUNIT_ASSERT_EQUAL(-1, ans.at(0).ans1);

	//Modifies(_,"x") r20
	r = Relationship("Modifies", "_", "\"y\"");

	qe.evaluateModifies(r, m, 20);
	ans = qe.relAns.find(20)->second;

	CPPUNIT_ASSERT_EQUAL(-2, ans.at(0).ans1);

	//Modifies("First",_) r21
	r = Relationship("Modifies", "\"First\"", "_");

	qe.evaluateModifies(r, m, 21);
	ans = qe.relAns.find(21)->second;

	CPPUNIT_ASSERT_EQUAL(-1, ans.at(0).ans1);

	//Modifies(_,v) r22
	r = Relationship("Modifies", "_", "v");
	tokens.push_back("_");
	tokens.push_back("v");
	qe.relParameters.insert(make_pair<int, vector<string>>(22, tokens));

	qe.evaluateModifies(r, m, 22);
	ans = qe.relAns.find(22)->second;

	CPPUNIT_ASSERT_EQUAL(0, ans.at(0).ans2);

	//Modifies(p,_) r23
	r = Relationship("Modifies", "p", "_");
	tokens.push_back("p");
	tokens.push_back("_");
	qe.relParameters.insert(make_pair<int, vector<string>>(23, tokens));

	qe.evaluateModifies(r, m, 23);
	ans = qe.relAns.find(23)->second;

	CPPUNIT_ASSERT_EQUAL(0, ans.at(0).ans1);

	//Uses(p, v) r24
	Uses* use = pkb->getUses();
	use->setUses(2, "x");
	use->setUsesProc(0, varIndexes);

	r = Relationship("Uses", "p", "v");
	tokens.push_back("p");
	tokens.push_back("v");
	qe.relParameters.insert(make_pair<int, vector<string>>(24, tokens));
	qe.evaluateUses(r, m, 24); 
	ans = qe.relAns.find(24)->second;

	CPPUNIT_ASSERT_EQUAL(0, ans.at(0).ans1);
	
	//Calls(p, q) r25
	Calls* call = pkb->getCalls();
	proc->insertProc("Second");
	proc->insertProc("Third");
	proc->insertProc("Fourth");
	proc->insertProc("Fifth");

	call->setCalls("First", "Second",8);
	call->setCalls("Second", "Third", 9);
	call->setCalls("First", "Third", 10);

	r = Relationship("Calls", "p", "q");
	tokens.push_back("p");
	tokens.push_back("q");
	qe.relParameters.insert(make_pair<int, vector<string>>(25, tokens));
	m.insert(make_pair<string, TypeTable::SynType>("q", TypeTable::PROCEDURE));
	qe.evaluateCalls(r, 25);
	ans = qe.relAns.find(25)->second;

	CPPUNIT_ASSERT_EQUAL(1, ans.at(0).ans2);
	CPPUNIT_ASSERT_EQUAL(2, ans.at(1).ans2);
	for(vector<Pair>::iterator it = ans.begin(); it!=ans.end(); it++){
		cout<<"ans1 = "<<it->ans1<<endl;
		cout<<"ans2 = "<<it->ans2<<endl;
	}

	//Calls(p, "Third") 26
	r = Relationship("Calls", "p", "\"Third\"");
	qe.evaluateCalls(r, 26);
	ans = qe.relAns.find(26)->second;
	tokens.push_back("p");
	tokens.push_back("\"Third\"");
	qe.relParameters.insert(make_pair<int, vector<string>>(26, tokens));

	CPPUNIT_ASSERT_EQUAL(0, ans.at(0).ans1);
	for(vector<Pair>::iterator it = ans.begin(); it!=ans.end(); it++){
		cout<<"ans1 = "<<it->ans1<<endl;
		cout<<"ans2 = "<<it->ans2<<endl;
	}

	//Calls("Second", q) r27
	r = Relationship("Calls", "\"Second\"", "q");
	tokens.push_back("\"Second\"");
	tokens.push_back("q");
	qe.relParameters.insert(make_pair<int, vector<string>>(27, tokens));
	qe.evaluateCalls(r, 27);
	ans = qe.relAns.find(27)->second;

	CPPUNIT_ASSERT_EQUAL(2, ans.at(0).ans2);

	//Calls("Second", "Third") r28
	r = Relationship("Calls", "\"Second\"", "\"Third\"");
	qe.evaluateCalls(r, 28);
	ans = qe.relAns.find(28)->second;

	CPPUNIT_ASSERT_EQUAL(-1, ans.at(0).ans1);

	call->setCalls("Third", "Fourth", 11);
	//Calls*("First", "Fourth") r29
	r = Relationship("Calls*", "\"First\"", "\"Fourth\"");
	qe.evaluateCallsStar(r,29);
	ans = qe.relAns.find(29)->second;

	CPPUNIT_ASSERT_EQUAL(-1, ans.at(0).ans1);
	//evaluate
	/*
	qe.evaluateFollows(r,m,0);
	vector<Pair> ans = qe.relAns.find(0)->second;
	
	//inserting into relParameters
	
	tokens.push_back("2");
	tokens.push_back("a");
	qe.relParameters.insert(make_pair(0, tokens));

	CPPUNIT_ASSERT_EQUAL(3, ans.at(0).ans2);*/
	/*
	//Query 2 assign a; Select a such that Follows(b, 4);
	r = Relationship("Follows", "b", "4");

	//setting follows(3,4)
	f->setFollows(3, 4);
	m.insert(make_pair<string, TypeTable::SynType>("b", TypeTable::ASSIGN));
	t->insertStmtNumAndType(4, TypeTable::ASSIGN);

	qe.evaluateFollows(r,m,0);
	ans = qe.relAns.find(0)->second;

	//inserting into relParameters
	tokens.clear();
	tokens.push_back("b");
	tokens.push_back("4");
	qe.relParameters.insert(make_pair(0, tokens));

	CPPUNIT_ASSERT_EQUAL(3, ans.at(0).ans1);
	
	//Query 3 assign a; Select a such that Follows(a, b);
	r = Relationship("Follows", "a", "b");

	//setting follows(3,4)
	f->setFollows(3, 4);
	f->setFollows(1, 2);
	t->insertStmtNumAndType(1, TypeTable::ASSIGN);
	qe.evaluateFollows(r,m,1);
	ans = qe.relAns.find(1)->second;
	CPPUNIT_ASSERT_EQUAL(2, ans.at(0).ans1);
	CPPUNIT_ASSERT_EQUAL(3, ans.at(0).ans2);

	/*
	//Query 1.5 variable v; assign a; Select v such that Follows(a, 2);
	Query q1p5;
	Relationship r1p5("Follows", "a", "2");
	//q1p5.addRelationship(r1p5);
	unordered_map<string,TypeTable::SynType> m1p5;
	m1p5.insert(make_pair<string, TypeTable::SynType>("a", TypeTable::ASSIGN));
	m1p5.insert(make_pair<string, TypeTable::SynType>("v", TypeTable::VARIABLE));
	q1p5.setSelectedSyn("v");
	q1p5.setSynTable(m1p5);

	vec = qe.evaluateQuery(q1p5);
	string e = "x";
	CPPUNIT_ASSERT_EQUAL(e, v->getVarName(vec[0]));

	
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

	//Query 3 assign a; while w; Select a such that Follows(w, a);
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
	CPPUNIT_ASSERT_EQUAL(-1, vec[0]);

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
	*/

	return;
}

/*
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
	expected = "";
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
	
	//for(vector<int>::iterator i = vec.begin(); i!=vec.end(); i++){
	//	cout<<*i<<endl;
	//}
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
	//for(vector<int>::iterator i = vec.begin(); i!=vec.end(); i++){
	//	cout<<*i<<endl;
	//}
	CPPUNIT_ASSERT_EQUAL(1, vec[0]);
	CPPUNIT_ASSERT_EQUAL(2, vec[1]);
	CPPUNIT_ASSERT_EQUAL(3, vec[2]);
	CPPUNIT_ASSERT_EQUAL(4, vec[3]);
	CPPUNIT_ASSERT_EQUAL(5, vec[4]);
	
}
*/