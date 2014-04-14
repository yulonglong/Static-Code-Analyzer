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
	//assign a; Select a such that Follows(a, 2);
	Query q;
	Relationship r("a", "a", "2");
	q.addRelationship(r);
	unordered_map<string,TypeTable::SynType> m;
	m.insert(make_pair<string, TypeTable::SynType>("a", TypeTable::ASSIGN));
	q.setSelectedSyn("a");
	q.setSynTable(m);

	Follows *f = pkb->getFollows();
	TypeTable *t = pkb->getTypeTable();
	f->setFollows(1, 2);
	cout<<"After setFollows"<<endl;
	t->insertStmtNumAndType(1, TypeTable::ASSIGN);
	cout<<"After inserting into table"<<endl;

	
	vector<int> vec = qe.evaluateQuery(q);
	cout<<"After evaluateQuery"<<endl;
	cout<<vec.empty()<<endl;
	//cout<<vec[0]<<endl;
	//CPPUNIT_ASSERT_EQUAL(1, vec[0]);
	
	return;
}

void QueryEvaluatorTest::testEvaluateFollowsBoolean(){
	cout<<"Test follows boolean"<<endl;
}

void QueryEvaluatorTest::testEvaluateParent(){

}
void QueryEvaluatorTest::testEvaluateParentBoolean(){

}
