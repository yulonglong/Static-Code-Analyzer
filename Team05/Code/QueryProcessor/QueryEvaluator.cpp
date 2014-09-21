//#include <iostream>
#include <string>
#include <algorithm>
#include "QueryEvaluator.h"
#include <ctype.h>
#include <set>
#include <stack>
#include <iostream>
#include <sstream>

using namespace std;



QueryEvaluator::QueryEvaluator(PKB* p){
	pkb = p;
	unordered_map<string, vector<int>> linkages;
	unordered_map<int, vector<Pair>> relAns;

}

QueryEvaluator::~QueryEvaluator(){
}

//function that orders the relationship vector for efficiency and faster running time
vector<Relationship> QueryEvaluator::orderRelationship(vector<Relationship> r){
	vector<Relationship> reorderedRelations;
	Relationship *rw;

	for(vector<Relationship>::iterator it = r.begin(); it!=r.end(); it++){
		//Swap pattern and relationships with non-alpha parameters to the front for first evaluation
		if(it->getRelType()==Relationship::PATTERN || !isalpha(it->getToken1()[0]) || !isalpha(it->getToken2()[0])){
			r.insert(r.begin(), *it);
			it = r.erase(it);
		}

		//evaluate with last
		else if(it->getRelType()==Relationship::WITH){
			Relationship relWith = *it;
			rw = &relWith;
			it = r.erase(it);
		}

	}

	reorderedRelations.push_back(*rw);

	return reorderedRelations;
}

unordered_map<string, vector<int>> QueryEvaluator::evaluateQuery(Query q){

	vector<Relationship> relations = q.getRelVect();
	relations = orderRelationship(relations);
	unordered_map<string, TypeTable::SynType> m = q.getSynTable();
	int relIndex = 0;
	for(vector<Relationship>::iterator it = relations.begin(); it!=relations.end(); it++){
		switch(it->getRelType()){
		case Relationship::FOLLOWS:
			evaluateFollows(*it, m,relIndex); break;

		case Relationship::FOLLOWSSTAR:
			evaluateFollowsStar(*it, m, relIndex); break;

		case Relationship::PARENT:
			evaluateParent(*it, m, relIndex); break;

		case Relationship::PARENTSTAR:
			evaluateParentStar(*it, m, q.getSelectedSyn().at(0)); break;//review

		case Relationship::CALLS:
			evaluateCalls(*it, relIndex); break;

		case Relationship::CALLSSTAR:
			evaluateCallsStar(*it, m, relIndex); break;

		case Relationship::MODIFIES:
			evaluateModifies(*it, m, relIndex); break;

		case Relationship::USES:
			evaluateUses(*it, m, relIndex); break;

		case Relationship::PATTERN:	
			vector<int> proxy = evaluatePattern(q, it->getToken1(), it->getToken2()); //review
		}

		relIndex++;
	}

	vector<string> selectedSyn = q.getSelectedSyn();
	unordered_map<string, vector<int>> answers;

	for(vector<string>::iterator it = selectedSyn.begin(); it!=selectedSyn.end(); it++){
		int index = (linkages.find(*it)->second).at(0);
		vector<Pair> p = relAns.at(index);
		vector<int> synAns;
		for(vector<Pair>::iterator it2 = p.begin(); it2!=p.end(); it2++){
			if(*it==it2->token1){
				synAns.push_back(it2->ans1);
			}
			else {
				synAns.push_back(it2->ans2);
			}
		}
	}

	return answers;
	/*
	//order the relationship vector
	vector<Relationship> relations = orderRelationship(q.getRelVect());
	vecOfRelations = relations;

	//declaring all table pointers
	TypeTable *t = pkb->getTypeTable();
	Follows *f = pkb->getFollows();
	VarTable *var = pkb->getVarTable();

	//retrieving synTable
	unordered_map<string, TypeTable::SynType> m = q.getSynTable();

	for(vector<Relationship>::iterator it = relations.begin(); it!=relations.end(); it++){

		string token1 = it->getToken1();
		string token2 = it->getToken2();

		if(token1==token2 && token1!="_"){
			answers.clear();
			break;
		}

		vector<string> selectedSyn = q.getSelectedSyn();
		
		unordered_map<string, TypeTable::SynType>::iterator i = m.find(selectedSyn);

		if(selectedSyn.at(0)!=(i->first)){
			answers.clear();
			break;
		}

		if((it->getRelType())!=Relationship::CALLS){
		if(token1=="_"){
			it->setToken1("s1");
			m.insert(make_pair<string, TypeTable::SynType>("s1", TypeTable::STMT));
			q.setSynTable(m);
		}

		if(token2=="_" && ((it->getRelType())!=Relationship::MODIFIES) && ((it->getRelType())!=Relationship::USES)){
			it->setToken2("s2");
			m.insert(make_pair<string, TypeTable::SynType>("s2", TypeTable::STMT));
			q.setSynTable(m);
		}

		if(token2=="_" && (((it->getRelType())==Relationship::MODIFIES) || ((it->getRelType())==Relationship::USES))){
			it->setToken2("v");
			m.insert(make_pair<string, TypeTable::SynType>("v", TypeTable::VARIABLE));
			q.setSynTable(m);
		}
		}

		switch(it->getRelType()){
		case Relationship::FOLLOWS: {	
			if((isdigit(token1[0]) && isdigit(token2[0])) || (selectedSyn!=token1 && selectedSyn!=token2)) { //if first char is a digit, then the token must be a number
				if(evaluateFollowsBoolean(*it, m)){
					answers.push_back(t->getAllStmts(i->second));
				}
			}
			else {
				answers.push_back(evaluateFollows(*it, m, q.getSelectedSyn()));
			}
			break;
									}
		case Relationship::FOLLOWSSTAR:
			{	

			if((isdigit(token1[0]) && isdigit(token2[0])) || (selectedSyn!=token1 && selectedSyn!=token2)) { //if first char is a digit, then the token must be a number
				if(evaluateFollowsStarBoolean(*it, m)){
					answers.push_back(t->getAllStmts(i->second));
				}
			}
			else {
				answers.push_back(evaluateFollowsStar(*it, m, q.getSelectedSyn()));
			}
			break;
									}

		case Relationship::CALLS:
			{
				

			}

		case Relationship::CALLSSTAR:
			{

			}

		case Relationship::PARENT:
			{
				if((isdigit(token1[0]) && isdigit(token2[0])) || (selectedSyn!=token1 && selectedSyn!=token2)) { //if first char is a digit, then the token must be a number
					if(evaluateParentBoolean(*it, m)){
						answers.push_back(t->getAllStmts(i->second));
					}
				}
				else {
					answers.push_back(evaluateParent(*it, m, q.getSelectedSyn()));
				}

				break;
			}
		case Relationship::PARENTSTAR:
			{	

			if((isdigit(token1[0]) && isdigit(token2[0])) || (selectedSyn!=token1 && selectedSyn!=token2)) { //if first char is a digit, then the token must be a number
				if(evaluateParentStarBoolean(*it, m)){
					answers.push_back(t->getAllStmts(i->second));
				}
			}
			else {
				answers.push_back(evaluateParentStar(*it, m, q.getSelectedSyn()));
			}
			break;
									}

		case Relationship::MODIFIES:
			{

			if(selectedSyn!=token1 && selectedSyn!=token2) { //if first char is a digit, then the token must be a number
				cout<<"Calling evaluateModifiesBoolean"<<endl;
				if(evaluateModifiesBoolean(*it, m)){
					switch(i->second){
					case TypeTable::VARIABLE:{
						answers.push_back(var->getAllVarIndex());
						break;
											 }
					default: {
						answers.push_back(t->getAllStmts(i->second));
						break;
							 }
					}
				}
			}
			else {
				cout<<"Calling evaluateModifies"<<endl;
				answers.push_back(evaluateModifies(*it, m, q.getSelectedSyn()));
			}
			break;
									}

		case Relationship::USES:
			{	

			if(selectedSyn!=token1 && selectedSyn!=token2) { //if first char is a digit, then the token must be a number
				cout<<"Calling evaluate uses boolean"<<endl;
				if(evaluateUsesBoolean(*it, m)){
					cout<<"called evaluate uses boolean"<<endl;
					switch(i->second){
					case TypeTable::VARIABLE:{
						cout<<"pushing back"<<endl;
						answers.push_back(var->getAllVarIndex());
						break;
											 }
					default: {
						answers.push_back(t->getAllStmts(i->second));
						break;
							 }
					}
				}
			}
			else {
				answers.push_back(evaluateUses(*it, m, q.getSelectedSyn()));
			}
			break;
									}
		case Relationship::PATTERN:
			{	
				if (q.getSelectedSyn().compare(q.getPatternSyn()) == 0)
					answers.push_back(evaluatePattern(q, token1, token2));
				else {
					vector<int> proxy = evaluatePattern(q, token1, token2);
					if(proxy.size()==0)
						answers.push_back(proxy);
				}
			}
		}
	}

	//If there are no relationships in Query
	if(relations.empty()){
		string sel = q.getSelectedSyn();
		unordered_map<string, TypeTable::SynType>::iterator iterate = q.getSynTable().find(sel);
		switch(iterate->second){
		case TypeTable::VARIABLE:{
			answers.push_back(var->getAllVarIndex());		
			break;
								 }
		case TypeTable::PROGLINE:{
			answers.push_back(t->getAllStmts(TypeTable::STMT));
			break;
								 }
		case TypeTable::CONSTANT:{
			ConstTable *c = pkb->getConstTable();
			answers.push_back(c->getAllConstIndex());
			break;
								 }
		default: {
			answers.push_back(t->getAllStmts(iterate->second));
			break;
				 }
		}
	}
	return intersectAnswers(answers);	*/
}

/*
vector<int> QueryEvaluator::intersectAnswers(vector<vector<int>> ans){

	cout<<"Intersecting Answers"<<endl;
	if(!ans.empty()){
		vector<int> first = ans[0];
		vector<int> queryAnswers;
		for(vector<int>::iterator it3 = first.begin(); it3!=first.end(); it3++){
			cout<<"In 1st for loop"<<endl;
			bool insert = true;
			for(vector<vector<int>>::iterator it1 = ans.begin()+1; it1!=ans.end(); it1++){
				bool change = true;
				cout<<"In 2nd for loop"<<endl;
				for(vector<int>::iterator it2 = it1->begin(); it2!=it1->end(); it2++){
					if(*it3==*it2)
						change = false;
				}
				if(change) {
					insert = false;
					break;
				}
			}
			if(insert){
				queryAnswers.push_back(*it3);
			}
		}
		return queryAnswers;
	}
	vector<int> emptyVec;
	return emptyVec;
}

bool QueryEvaluator::evaluateQueryBoolean(Query q){
	vector<Relationship> relations = q.getRelVect();
	bool answers = true;
	Follows *f = pkb->getFollows();
	for(vector<Relationship>::iterator it = relations.begin(); it!=relations.end(); it++){
		switch(it->getRelType()){
		case Relationship::FOLLOWS: 
			answers = answers && evaluateFollowsBoolean(*it, q.getSynTable());
			break;
		case Relationship::FOLLOWSSTAR:
			answers = answers && evaluateFollowsStarBoolean(*it, q.getSynTable());
			break;
		case Relationship::PARENT:
			answers = answers && evaluateParentBoolean(*it, q.getSynTable());
			break;
		case Relationship::PARENTSTAR:
			answers = answers && evaluateParentStarBoolean(*it, q.getSynTable());
			break;
		case Relationship::MODIFIES:
			answers = answers && evaluateModifiesBoolean(*it, q.getSynTable());
			break;
		case Relationship::USES:
			answers = answers && evaluateUsesBoolean(*it, q.getSynTable());
		}
	}
	return answers;
}


bool QueryEvaluator::evaluateCallsBoolean(Relationship r){
	Calls *call = pkb->getCalls();
	string tk1 = r.getToken1();
	string tk2 = r.getToken2();
	vector<int> ans; 

	//Calls(p, q)
	if((isalpha(tk1[0]) && isalpha(tk2[0])) || (tk1=="_" && tk2=="_")){
		ans = call->getCalls();
		if(!ans.empty())
			return true;
	}

	//Calls(p, "Second")
	else if(isalpha(tk1[0]) || tk1=="_"){
		ans = call->getCalls(tk2.substr(1,tk2.length()-2));
		if(!ans.empty())
			return true;
	}

	//Calls("First", q)
	else if(isalpha(tk2[0]) || tk2=="_"){
		ans = call->getCalled(tk2.substr(1,tk2.length()-2));
		if(!ans.empty())
			return true;
	}

	//Calls("First", "Second")
	else {
		return call->isCalls(tk1, tk2);
	}

	return false;
}

bool QueryEvaluator::evaluateParentBoolean(Relationship r, unordered_map<string, TypeTable::SynType> m){
	string tk1 = r.getToken1();
	string tk2 = r.getToken2();
	Parent *p = pkb->getParent();
	if(isdigit(tk1[0]) && isdigit(tk2[0])){
		return p->isParent(atoi(tk1.c_str()), atoi(tk2.c_str()));
	}
	else if(isalpha(tk1[0]) && isalpha(tk2[0])){
		unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(tk1);
		unordered_map<string, TypeTable::SynType>::iterator i2 = m.find(tk2);
		cout<<"Calling isParent(TYPE, TYPE)"<<endl;
		return p->isParent(i1->second, i2->second);
	}
	else if(isalpha(tk1[0])){
		unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(tk1);
		cout<<"Calling isParent(TYPE, STMTNUM)"<<endl;
		return p->isParent(i1->second, atoi(tk2.c_str()));
	}
	else {
		unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(tk2);
		cout<<"Calling isChildren(TYPE, STMTNUM)"<<endl;
		return p->isChildren(i1->second, atoi(tk1.c_str()));
	}
}

bool QueryEvaluator::evaluateFollowsBoolean(Relationship r, unordered_map<string, TypeTable::SynType> m){
	string tk1 = r.getToken1();
	string tk2 = r.getToken2();
	Follows *f = pkb->getFollows();

	if(isdigit(tk1[0]) && isdigit(tk2[0])){
		cout<<"Calling isFollows(STMTNUM, STMTNUM)"<<endl;
		return f->isFollows(atoi(tk1.c_str()), atoi(tk2.c_str()));
	}
	else if(isalpha(tk1[0]) && isalpha(tk2[0])){
		unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(tk1);
		unordered_map<string, TypeTable::SynType>::iterator i2 = m.find(tk2);
		cout<<"Calling isFollows(TYPE, TYPE)"<<endl;
		return f->isFollows(i1->second, i2->second);
	}
	else if(isalpha(tk1[0])){
		unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(tk1);
		cout<<"Calling getFollows(TYPE, STMTNUM)"<<endl;
		return (f->getFollows(i1->second, atoi(tk2.c_str()))==-1)?false:true;
	}
	else {
		unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(tk2);
		cout<<"Calling getFollowedBy(TYPE, STMTNUM)"<<endl;
		bool temp;
		try{
			temp = f->getFollowedBy(i1->second, atoi(tk1.c_str()))==-1?false:true;
		}catch(...){
		}
		return temp;
	}
}*/

void QueryEvaluator::evaluateCalls(Relationship r, int relIndex){
	Calls *call = pkb->getCalls();
	ProcTable *proc = pkb->getProcTable();
	string tk1 = r.getToken1();
	string tk2 = r.getToken2();
	vector<int> ans;
	vector<int> called;
	vector<Pair> callAns;

	//Calls(p, q) OR Calls(p, _) OR Calls(_,q)
	if((isalpha(tk1[0]) && isalpha(tk2[0])) || (isalpha(tk1[0])&&tk2=="_") || (tk1=="_"&&isalpha(tk2[0]))){
		ans = proc->getAllProcIndexes();
		for(vector<int>::iterator it=ans.begin(); it!=ans.end(); it++){
			string procName = proc->getProcName(*it);
			called = call->getCalled(procName);

			for(vector<int>::iterator it2=called.begin(); it2!=called.end(); it2++){
				callAns.push_back(Pair (*it, *it2, tk1, tk2));
			}
		}

	}

	//Select p Calls(p, "Second") 
	else if(isalpha(tk1[0])){
		ans = call->getCalls(tk2.substr(1,tk2.length()-2));
		int procIndex = proc->getProcIndex(tk2.substr(1,tk2.length()-2));

		for(vector<int>::iterator it=ans.begin(); it!=ans.end(); it++){
			callAns.push_back(Pair (*it, procIndex, tk1, tk2));
		}
	}

	//Select q Calls("First", q)
	else if(isalpha(tk2[0])){
		ans = call->getCalled(tk1.substr(1,tk1.length()-2));

		int procIndex = proc->getProcIndex(tk1.substr(1,tk1.length()-2));

		for(vector<int>::iterator it=ans.begin(); it!=ans.end(); it++){
			callAns.push_back(Pair (procIndex, *it, tk1, tk2));
		}
	}

	//Calls(_,_)
	else if(tk1=="_" && tk2=="_"){
		ans = call->getCalls();
		if(!ans.empty()){
			callAns.push_back(Pair (1, 1, "true", "true"));
		}else{
			callAns.push_back(Pair (0, 0, "false", "false"));
		}
	}

	//Calls("Third", "Fourth")
	else {
		if(call->isCalls(tk1.substr(1, tk1.length()-2), tk2.substr(1,tk2.length()-2))){
			callAns.push_back(Pair (1, 1, "true", "true"));
		}else{
			callAns.push_back(Pair (0, 0, "false", "false"));
		}
	}

//If both a and b exist in linkages
	if(isExistInLinkages(tk1) && isExistInLinkages(tk2)){

		removePairsFromRelAns(&callAns, tk1, 1);
		removePairsFromRelAns(&callAns, tk2, 2);
		removePairs(callAns, tk1);
		removePairs(callAns, tk2);
		insertLinks(tk1, relIndex);
		insertLinks(tk2, relIndex);
	}

	//If only a exist
	else if(isExistInLinkages(tk1)){
		removePairsFromRelAns(&callAns, tk1, 1);
		removePairs(callAns, tk1);
		insertLinks(tk1, relIndex);
	}

	//If only b exist
	else if(isExistInLinkages(tk2)){
		removePairsFromRelAns(&callAns, tk2, 2);
		removePairs(callAns, tk2);
		insertLinks(tk2, relIndex);
	}

	else {

	}

	relAns.insert(make_pair(relIndex, callAns));


}

//Returns true if token already exists in linkages
bool QueryEvaluator::isExistInLinkages(string token){
	if(linkages.find(token)!=linkages.end()){
		return true;	
	}

	return false;
}

vector<int> * QueryEvaluator::findAnswerVectorFromToken(string token){

	vector<int> *point = &linkages.find(token)->second;

	return point;
}

/*
//Returns true if tk1 and tk2 are linked
bool QueryEvaluator::isLinked(string tk1, string tk2){

	for(vector<vector<string>>::iterator it = linkages.begin(); it!=linkages.end(); it++){
		if(find(it->begin(), it->end(), tk1)!=it->end() && find(it->begin(), it->end(), tk2)!=it->end()){
			return true;
		}
	}

	return false;
}

vector<string> QueryEvaluator::findLinks(string token){
	for(vector<vector<string>>::iterator it = linkages.begin(); it!=linkages.end(); it++){
		if(find(it->begin(), it->end(), token)!=it->end()){
			return *it;
		}
	}
}*/

//return set of int answers for a particular syn
set<int> QueryEvaluator::retrieveTokenEvaluatedAnswers(string tk){
	vector<int> listOfRel = linkages.find(tk)->second;

	vector<Pair> ans = relAns.find(listOfRel.at(0))->second;
	set<int> setAns;
	if(ans.at(0).token1==tk){
		for(vector<Pair>::iterator it = ans.begin(); it!=ans.end(); it++){
			setAns.insert(it->ans1);
		}
	}else{
		for(vector<Pair>::iterator it = ans.begin(); it!=ans.end(); it++){
			setAns.insert(it->ans2);
		}
	}

	return setAns;
}

void QueryEvaluator::removePairs(vector<Pair> p, string token){
	int pairIndex;
	vector<int> listOfRel = linkages.find(token)->second;
	vector<int> list;
	if(p.at(0).token1==token){
		for(vector<Pair>::iterator iter=p.begin(); iter!=p.end(); iter++){
			list.push_back(iter->ans1);
		}
	}
	else{
		for(vector<Pair>::iterator iter=p.begin(); iter!=p.end(); iter++){
			list.push_back(iter->ans2);
		}
	}

	//iterate through all the relations that evaluated the token
	for(vector<int>::iterator it=listOfRel.begin(); it!=listOfRel.end(); it++){
		unordered_map<int, vector<Pair>>::iterator i = relAns.find(*it);
		vector<Pair> *pr = &i->second;

		//find out whether the token is the first or second argument of the relationship
		if(pr->at(0).token1==token){
			pairIndex=1;
		}
		else{
			pairIndex=2;
		}

		//iterate through the relationship pairs
		for(vector<Pair>::iterator it2=pr->begin(); it2!=pr->end(); it2++){

			//remove all pairs that are eliminated
			if(pairIndex==1){
				if(find(list.begin(),list.end(),it2->ans1)==list.end()){
					it2 = pr->erase(it2);
				}
			}else{
				if(find(list.begin(),list.end(),it2->ans2)==list.end()){
					it2 = pr->erase(it2);
				}
			}
		}
	}
}

void QueryEvaluator::evaluateWith(Relationship r, unordered_map<string, TypeTable::SynType> m, int relIndex){

	//Retrieve the two with syns
	string tk1 = r.getToken1();
	string tk2 = r.getToken2();
	vector<Pair> withAns;
	VarTable * v = pkb->getVarTable(); 
	ProcTable * p = pkb->getProcTable();
	ConstTable * c = pkb->getConstTable();


	unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(tk1);
	unordered_map<string, TypeTable::SynType>::iterator i2 = m.find(tk2);
	

	//with v1.varName = p.procName with c.value = s.stmt#
	if(isalpha(tk1[0]) && isalpha(tk2[0])){
		//if both exist in links then remove all unnecessary tuples. push relans true
		if(isExistInLinkages(tk1) && isExistInLinkages(tk2)){
			
			//if both tokens are of the same type e.g v1 v2
			if(i1->second == i2->second){
				//pop all relIndexes that have links to tk1 and tk2
				int dummyRel1 = (linkages.find(tk1)->second).at(0);
				int dummyRel2 = (linkages.find(tk2)->second).at(0);
				vector<Pair> dummyPairs1 = relAns.find(dummyRel1)->second;
				vector<Pair> dummyPairs2 = relAns.find(dummyRel2)->second;
				dummyPairs1.at(0).token1 = tk2;
				dummyPairs2.at(0).token1 = tk1;

				//intersect
				removePairs(dummyPairs2, tk1);
				removePairs(dummyPairs1, tk2);

			}

			//else if they are different type
			else {
				//get list of rel that link to v1
				set<int> ans1 = retrieveTokenEvaluatedAnswers(tk1);
				set<string> ans1string;
				if(i1->second==TypeTable::PROCEDURE || i1->second==TypeTable::VARIABLE){
					
					if(i1->second==TypeTable::PROCEDURE){
						for(set<int>::iterator it = ans1.begin(); it!=ans1.end(); it++){
							ans1string.insert(p->getProcName(*it));
						}
					}

					else{
						for(set<int>::iterator it = ans1.begin(); it!=ans1.end(); it++){
							ans1string.insert(v->getVarName(*it));
						}
					}
				}
				//get list of rel that link to p
				set<int> ans2 = retrieveTokenEvaluatedAnswers(tk2);
				set<string> ans2string;
				if(i2->second==TypeTable::PROCEDURE || i2->second==TypeTable::VARIABLE){
					
					if(i2->second==TypeTable::PROCEDURE){
						for(set<int>::iterator it = ans2.begin(); it!=ans2.end(); it++){
							ans2string.insert(p->getProcName(*it));
						}
					}

					else{
						for(set<int>::iterator it = ans2.begin(); it!=ans2.end(); it++){
							ans2string.insert(v->getVarName(*it));
						}
					}
				}

				set<int> ans3;
				

				if(!ans1string.empty()){
					vector<Pair> ans3stringVar;
					vector<Pair> ans3stringProc;
					set<string> ans3string;

					//std::set_intersection(ans1string.begin(), ans1string.end(), ans2string.begin(), ans2string.end(),ans3string.begin());

					for(set<string>::iterator it = ans3string.begin(); it!=ans3string.end(); it++){
						ans3stringVar.push_back(Pair (v->getVarIndex(*it), v->getVarIndex(*it), tk1, tk2));
						ans3stringProc.push_back(Pair (p->getProcIndex(*it), p->getProcIndex(*it), tk1, tk2));
					}

					if(i1->second==TypeTable::VARIABLE){
						removePairs(ans3stringVar, tk1);
						removePairs(ans3stringProc, tk2);
					}
					else{
						removePairs(ans3stringProc, tk1);
						removePairs(ans3stringVar, tk2);
					}
				}
				else{
					//std::set_intersection(ans1.begin(), ans1.end(), ans2.begin(), ans2.end(), ans3.begin());
					vector<Pair> finalAns;

					for(set<int>::iterator it = ans3.begin(); it!=ans3.end(); it++){
						finalAns.push_back(Pair(*it, *it, tk1, tk2));
					}

					removePairs(finalAns, tk1);
					removePairs(finalAns, tk2);
				}
			}
		}

		//else if only one exist and the other does not. get all from the one that does not exist and remove unnecessary tuples. push relans true
		else if(isExistInLinkages(tk1)){
			set<int> ans = retrieveTokenEvaluatedAnswers(tk1);
			vector<Pair> finalAns;
			if(i1->second==TypeTable::PROCEDURE){
				for(set<int>::iterator it = ans.begin(); it!=ans.end(); it++){
					if(v->getVarName(*it)!="-1"){
						finalAns.push_back(Pair (*it, 1, tk1, tk2));
					}
				}
			}

			else if(i1->second == TypeTable::VARIABLE){
				for(set<int>::iterator it = ans.begin(); it!=ans.end(); it++){
					if(p->getProcName(*it)!="-1"){
						finalAns.push_back(Pair (*it, 1, tk1, tk2));
					}
				}
			}

			else {
				if(i2->second==TypeTable::CONSTANT){
					for(set<int>::iterator it=ans.begin(); it!=ans.end(); it++){
						stringstream s;
						s << *it;					
						if(c->getConstIndex(s.str())!=-1){
							finalAns.push_back(Pair (*it, 1, tk1, tk2));
						}
					}
				}
				else if(i2->second==TypeTable::STMT){
					//request for stmt range
				}
				else{//PROGLINE
					//request for progline range
				}

				removePairs(finalAns, tk1);
			}
		}

		else if(isExistInLinkages(tk2)){
			set<int> ans = retrieveTokenEvaluatedAnswers(tk2);
			vector<Pair> finalAns;
			if(i2->second==TypeTable::PROCEDURE){
				for(set<int>::iterator it = ans.begin(); it!=ans.end(); it++){
					if(v->getVarName(*it)!="-1"){
						finalAns.push_back(Pair (1, *it, tk1, tk2));
					}
				}
			}

			else if(i2->second == TypeTable::VARIABLE){
				for(set<int>::iterator it = ans.begin(); it!=ans.end(); it++){
					if(p->getProcName(*it)!="-1"){
						finalAns.push_back(Pair (1, *it, tk1, tk2));
					}
				}
			}

			else {
				if(i1->second==TypeTable::CONSTANT){
					for(set<int>::iterator it=ans.begin(); it!=ans.end(); it++){
						stringstream s;
						s << *it;					
						if(c->getConstIndex(s.str())!=-1){
							finalAns.push_back(Pair (1, *it, tk1, tk2));
						}
					}
				}
				else if(i1->second==TypeTable::STMT){
					//request for stmt range
				}
				else{//PROGLINE
					//request for progline range
				}

				removePairs(finalAns, tk2);
			}
		}

		//else (both does not exist) evaluate true or false
		else {
			if(i1->second == TypeTable::PROCEDURE || i1->second == TypeTable::VARIABLE){

			}
		}

	}
	//with v.varName = "x" with p.procName = "Third"
	else {
		//if exist in links then delete all unnecessary tuples then push into relAns true
		if(!isdigit(tk2[0])){ //if the query is with c.value = 3 then we do not have to remove the quotation marks
			tk2 = tk2.substr(1,tk2.length()-2);
		}
		if(isExistInLinkages(tk1)){
			int index;
		
			if(i2->second==TypeTable::VARIABLE){
				index = v->getVarIndex(tk2);
			}else if(i2->second==TypeTable::PROCEDURE){
				index = p->getProcIndex(tk2);
			} else{
				index = atoi(tk2.c_str());
			}

			//push in a dummy value for removal purposes
			withAns.push_back(Pair (1, index, tk1, tk2));
			removePairs(withAns, tk1);
		}

		//else evaluate true or false
		else {
			withAns.push_back(Pair (1, 1, "true", "true"));
		}
	}
}

void QueryEvaluator::evaluateNext(Relationship r, unordered_map<string, TypeTable::SynType> m, int relIndex){
	string tk1 = r.getToken1();
	string tk2 = r.getToken2();

}

void QueryEvaluator::recursiveCall(int rootProcIndex, int currentIndex, vector<Pair> * ans, string tk1, string tk2){
	Calls *c = pkb->getCalls();
	ProcTable *p = pkb->getProcTable();
	vector<int> called = c->getCalled(p->getProcName(currentIndex));

	for(vector<int>::iterator i=called.begin(); i!=called.end(); i++){
		ans->push_back(Pair (rootProcIndex, *i, tk1, tk2));
		recursiveCall(rootProcIndex, *i, ans, tk1, tk2);
	}
}

void QueryEvaluator::recursiveCallBoolean(int rootProcIndex, int currentIndex, int targetIndex, vector<Pair> * ans, string tk1, string tk2){
	Calls *c = pkb->getCalls();
	ProcTable *p = pkb->getProcTable();
	vector<int> called = c->getCalled(p->getProcName(currentIndex));

	for(vector<int>::iterator i=called.begin(); i!=called.end(); i++){
		if(currentIndex==targetIndex){
			ans->push_back(Pair (1,1,"true","true"));
			break;
		}
		recursiveCallBoolean(rootProcIndex, *i, targetIndex, ans, tk1, tk2);
	}
}

void QueryEvaluator::recursiveInverseCall(int leafIndex, int currentIndex, vector<Pair> * ans, string tk1, string tk2){
	Calls *c = pkb->getCalls();
	ProcTable *p = pkb->getProcTable();
	vector<int> calls = c->getCalls(p->getProcName(currentIndex));

	for(vector<int>::iterator i=calls.begin(); i!=calls.end(); i++){
		ans->push_back(Pair (*i, leafIndex, tk1, tk2));
		recursiveInverseCall(leafIndex, *i, ans, tk1, tk2);
	}
}

void QueryEvaluator::evaluateCallsStar(Relationship r, unordered_map<string, TypeTable::SynType> m, int relIndex){
	string tk1 = r.getToken1();
	string tk2 = r.getToken2();
	Calls *c = pkb->getCalls();
	ProcTable *p = pkb->getProcTable();
	unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(tk1);
	unordered_map<string, TypeTable::SynType>::iterator i2 = m.find(tk2);

	vector<Pair> callsStarAns;

	//Calls*(a,b) 
	if(isalpha(tk1[0]) && isalpha(tk2[0])){
		vector<int> allProc = p->getAllProcIndexes();

		for(vector<int>::iterator it = allProc.begin(); it!=allProc.end(); it++){
			recursiveCall(*it, *it, &callsStarAns, tk1, tk2);
		}
	}

	//Calls*(a,_)
	else if(isalpha(tk1[0]) && tk2=="_"){
			vector<int> allProc = p->getAllProcIndexes();

			for(vector<int>::iterator it=allProc.begin(); it!=allProc.end(); it++){
				if(!c->getCalled(p->getProcName(*it)).empty()){
					callsStarAns.push_back(Pair (*it, -1, tk1, tk2));
				}
			}
	}

	//Calls*(a, "second")
	else if(isalpha(tk1[0])) {
		int index = p->getProcIndex(tk2.substr(1,tk2.length()-2));

		recursiveInverseCall(index, index, &callsStarAns, tk1, tk2);

	}

	//Calls*(_,b)
	else if(isalpha(tk2[0]) && tk1=="_"){

		vector<int> allProc = p->getAllProcIndexes();

		for(vector<int>::iterator it = allProc.begin(); it!=allProc.end(); it++){
			if(!c->getCalls(p->getProcName(*it)).empty()){
				callsStarAns.push_back(Pair(-1, *it, tk1, tk2));
			}
		}

	}

	//Calls*("first", b)
	else if(isalpha(tk2[0])){
		int index = p->getProcIndex(tk1.substr(1, tk1.length()-2));

		recursiveCall(index, index, &callsStarAns, tk1, tk2);
	}

	//Calls*("first", "second")
	else {
		int index1 = p->getProcIndex(tk1.substr(1, tk1.length()-2));
		int index2 = p->getProcIndex(tk2.substr(1, tk1.length()-2));

		recursiveCallBoolean(index1, index1, index2, &callsStarAns, tk1, tk2);

		if(callsStarAns.empty()){
			callsStarAns.push_back(Pair (0, 0, "false", "false"));
		}
	}

	//If both a and b exist in linkages
	if(isExistInLinkages(tk1) && isExistInLinkages(tk2)){

		removePairsFromRelAns(&callsStarAns, tk1, 1);
		removePairsFromRelAns(&callsStarAns, tk2, 2);
		removePairs(callsStarAns, tk1);
		removePairs(callsStarAns, tk2);
		insertLinks(tk1, relIndex);
		insertLinks(tk2, relIndex);
	}

	//If only a exist
	else if(isExistInLinkages(tk1)){
		removePairsFromRelAns(&callsStarAns, tk1, 1);
		removePairs(callsStarAns, tk1);
		insertLinks(tk1, relIndex);
	}

	//If only b exist
	else if(isExistInLinkages(tk2)){
		removePairsFromRelAns(&callsStarAns, tk2, 2);
		removePairs(callsStarAns, tk2);
		insertLinks(tk2, relIndex);
	}

	else {

	}

	relAns.insert(make_pair(relIndex, callsStarAns));

}

void QueryEvaluator::evaluateFollows(Relationship r, unordered_map<string, TypeTable::SynType> m, int relIndex){
	string tk1 = r.getToken1();
	string tk2 = r.getToken2();
	Follows *f = pkb->getFollows();
	unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(tk1);
	unordered_map<string, TypeTable::SynType>::iterator i2 = m.find(tk2);

	vector<Pair> followsAns;

	//Follows(a,b)
	if(isalpha(tk1[0]) && isalpha(tk2[0])){

		//If both tokens are already previously evaluated
		if(isExistInLinkages(tk1) && isExistInLinkages(tk2)){

			//get the set of answers that are previously evaluated by other relations
			set<int> sa = retrieveTokenEvaluatedAnswers(tk1);
			set<int> sb = retrieveTokenEvaluatedAnswers(tk2);

			//try all combinations in set A and set B
			for(set<int>::iterator it = sa.begin(); it!=sa.end(); it++){
				for(set<int>::iterator it2 = sb.begin(); it2!=sb.end(); it++){
					if(f->isFollows(*it, *it2)){
						followsAns.push_back(Pair (*it, *it2, tk1, tk2));
					}
				}
			}

			//From the new followsAns, delete all Pairs that are eliminated from other relations
			removePairs(followsAns,tk1);
			removePairs(followsAns,tk2);

			//Add the relationship into linkages
			insertLinks(tk1, relIndex);
			insertLinks(tk2, relIndex);
		}

		//If only a exists
		else if(isExistInLinkages(tk1)){

			//get the set of answers that are previously evaluated by other relations
			set<int> sa = retrieveTokenEvaluatedAnswers(tk1);

			for(set<int>::iterator it=sa.begin(); it!=sa.end(); it++){
				int follows = f->getFollows(i2->second, *it);
				if(follows!=-1){
					followsAns.push_back(Pair (*it, follows, tk1, tk2));
				}
			}

			//Delete the redundant pairs
			removePairs(followsAns,tk1);

			//Add the relationship into linkages
			insertLinks(tk1, relIndex);
		}


		//If only b exists
		else if(isExistInLinkages(tk2)){

			//get the set of answers that are previously evaluated by other relations
			set<int> sb = retrieveTokenEvaluatedAnswers(tk2);

			for(set<int>::iterator it=sb.begin(); it!=sb.end(); it++){
				int followedBy = f->getFollowedBy(i1->second, *it);
				if(followedBy!=-1){
					followsAns.push_back(Pair (*it, followedBy, tk1, tk2));
				}
			}

			//Delete the redundant pairs
			removePairs(followsAns,tk2);

			//Add the relationship into linkages
			insertLinks(tk2, relIndex);

		}

		//If both do not exist
		else {

			//Retrieve both a and b from PKB
			vector<int> first = f->getFollowedBy(i1->second, i2->second);
			vector<int> second = f->getFollows(i1->second, i2->second);

			for(int i=0; i<first.size(); i++){
				followsAns.push_back(Pair (first.at(i), second.at(i), tk1, tk2));
			}

		}
		

	}

	//Follows(a,1)
	else if(isalpha(tk1[0])){
		if(isExistInLinkages(tk1)){

			//get the set of answers that are previously evaluated by other relations
			set<int> sa = retrieveTokenEvaluatedAnswers(tk1);

			for(set<int>::iterator it=sa.begin(); it!=sa.end(); it++){
				if(f->isFollows(*it, atoi(tk2.c_str()))){
					followsAns.push_back(Pair (*it, atoi(tk2.c_str()), tk1, tk2));
				}
			}

			//Delete the redundant pairs
			removePairs(followsAns,tk1);

			//Add the relationship into linkages
			vector<int> *pt = &linkages.find(tk1)->second;
			pt->push_back(relIndex);
		}
		
		//If it does not exist
		else {

			//Retrieve a from PKB and push it into the answer vector
			int first = f->getFollowedBy(i1->second, atoi(tk2.c_str()));

			followsAns.push_back(Pair (first, atoi(tk2.c_str()), tk1, tk2));

		}
	}

	//Follows(1,b)
	else if(isalpha(tk2[0])){
		if(isExistInLinkages(tk2)){

			//get the set of answers that are previously evaluated by other relations
			set<int> sa = retrieveTokenEvaluatedAnswers(tk2);

			for(set<int>::iterator it=sa.begin(); it!=sa.end(); it++){
				if(f->isFollows(atoi(tk1.c_str()), *it)){
					followsAns.push_back(Pair (atoi(tk1.c_str()), *it, tk1, tk2));
				}
			}

			//Delete the redundant pairs
			removePairs(followsAns,tk2);

			//Add the relationship into linkages
			vector<int> *pt = &linkages.find(tk2)->second;
			pt->push_back(relIndex);
		}
		
		//If it does not exist
		else {

			//Retrieve a from PKB and push it into the answer vector
			int second = f->getFollows(i2->second, atoi(tk1.c_str()));

			followsAns.push_back(Pair (atoi(tk1.c_str()), second, tk1, tk2));

		}
	}

	//Follows(1,2)
	else {
		//if Follows(1,2) is verified as false, clear all answers
		if(!f->isFollows(atoi(tk1.c_str()), atoi(tk2.c_str()))){
			followsAns.push_back(Pair (0,0,"false","false"));
		}
		else{
			followsAns.push_back(Pair (1,1,"true","true"));
		}
	}

	relAns.insert(make_pair(relIndex, followsAns));
}

string QueryEvaluator::convertEnumToString(TypeTable::SynType t){
	switch(t){
	case TypeTable::ASSIGN:
		return "assign";
	case TypeTable::WHILE:
		return "while";
	case TypeTable::PROGLINE:
		return "progline";
	case TypeTable::CONSTANT:
		return "constant";
	}
	return "null";
}



void QueryEvaluator::evaluateFollowsStar(Relationship r, unordered_map<string, TypeTable::SynType> m, int relIndex){
	/*Pair p1;
	Pair p2;

	set<Pair> p;
	p.insert(Pair (1,1,"d","d"));
	p.insert(Pair (1,1,"d","d"));
	*/
	string tk1=r.getToken1();
	string tk2=r.getToken2();
	Follows *f = pkb->getFollows();
	TypeTable *t = pkb->getTypeTable();
	set<int> answer;
	vector<int> selected;
	set<Pair> followsStarAnsSet;//REMEMBER TO INSERT SELF DEFINED COMPARATOR
	vector<Pair> followsStarAns;

	
	int stmtNumber = 0;
	unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(tk1);
	unordered_map<string, TypeTable::SynType>::iterator i2 = m.find(tk2);
	
	//Select w such that Follows*(w, a)
	if(isalpha(tk1[0]) && isalpha(tk2[0])){

		selected = t->getAllStmts(i1->second);	//get all while statements

		for(vector<int>::iterator it = selected.begin(); it!=selected.end(); it++){

			stmtNumber = f->getFollows(TypeTable::STMT, *it);
			do{			
				if(stmtNumber!=-1){
					if(t->isType(i2->second,stmtNumber)){
						followsStarAnsSet.insert(Pair (*it, stmtNumber, tk1, tk2));
					}
				}
				else{
					break;
				}

				stmtNumber = f->getFollows(TypeTable::STMT, stmtNumber);
			}while(true);
		}
	}
	
	//Select a such that Follows*(a, 13)
	else if(isalpha(tk1[0])){
		cout<<"Handling Follows*(type, stmtnum)"<<endl;
		stmtNumber = atoi(tk2.c_str());
		do{			
			cout<<"Calling getFollowedBy(type, stmtnum)"<<endl;
			stmtNumber = f->getFollowedBy(TypeTable::STMT, stmtNumber);
			if(stmtNumber!=-1){
				cout<<"Calling TypeTable::isType"<<endl;
				if(t->isType(i1->second, stmtNumber)){
					followsStarAnsSet.insert(Pair (stmtNumber, atoi(tk2.c_str()), tk1, tk2));
				}
			}
			else{
				break;
			}
			
		}while(true);
	}

	//Select a such that Follows*(3, a)
	else if(isalpha(tk2[0])){
		cout<<"Handling Follows*(stmtnum, type)"<<endl;
		stmtNumber = atoi(tk1.c_str());
		do{			
			cout<<"Calling getFollows(type, stmtnum)"<<endl;
			stmtNumber = f->getFollows(TypeTable::STMT, stmtNumber);
			if(stmtNumber!=-1){
				if(t->isType(i2->second, stmtNumber)){
					followsStarAnsSet.insert(Pair (atoi(tk1.c_str()), stmtNumber, tk1, tk2));
				}
			}
			else{
				break;
			}
			
		}while(true);
	}

	//Follows*(1,2)
	else {
		stmtNumber = atoi(tk1.c_str());
		while(stmtNumber!=-1){
			cout<<"STMTNUM is "<<stmtNumber<<endl;
			stmtNumber = f->getFollows(TypeTable::STMT, stmtNumber);
			if(stmtNumber==atoi(tk2.c_str()))
				followsStarAnsSet.insert(Pair (1,1,"true","true"));
			if(stmtNumber>atoi(tk2.c_str()))
				followsStarAnsSet.insert(Pair (0,0,"false","false"));
				break;
		}
	}
	
	//copy set into vector
	//copy(followsStarAnsSet.begin(), followsStarAnsSet.end(),followsStarAns);
	for(set<Pair>::iterator it=followsStarAnsSet.begin(); it!=followsStarAnsSet.end(); it++){
		followsStarAns.push_back(*it);
	}

	
	//If both a and b exist in linkages
	if(isExistInLinkages(tk1) && isExistInLinkages(tk2)){

		removePairsFromRelAns(&followsStarAns, tk1, 1);
		removePairsFromRelAns(&followsStarAns, tk2, 2);
		removePairs(followsStarAns, tk1);
		removePairs(followsStarAns, tk2);
		insertLinks(tk1, relIndex);
		insertLinks(tk2, relIndex);
	}

	//If only a exist
	else if(isExistInLinkages(tk1)){
		removePairsFromRelAns(&followsStarAns, tk1, 1);
		removePairs(followsStarAns, tk1);
		insertLinks(tk1, relIndex);
	}

	//If only b exist
	else if(isExistInLinkages(tk2)){
		removePairsFromRelAns(&followsStarAns, tk2, 2);
		removePairs(followsStarAns, tk2);
		insertLinks(tk2, relIndex);
	}

	else {

	}

	relAns.insert(make_pair(relIndex, followsStarAns));
	
}

void QueryEvaluator::insertLinks(string tk, int relIndex){
	//Add the relationship into linkages
	vector<int> *pt = &linkages.find(tk)->second;
	pt->push_back(relIndex);
}

void QueryEvaluator::removePairsFromRelAns(vector<Pair> * relationsAns, string tk, int pairIndex){
	
	//Retrieve the set of int of the token that was evaluated
	set<int> s = retrieveTokenEvaluatedAnswers(tk);

	//Delete it from the ans pairs made
	for(vector<Pair>::iterator it = relationsAns->begin(); it!=relationsAns->end(); it++){
		if(pairIndex==1){

			//if ans from relationsAns is not found in the set, remove it
			if(s.find(it->ans1)==s.end()){
				relationsAns->erase(it);
			}
		}
		else {

			if(s.find(it->ans2)==s.end()){
				relationsAns->erase(it);
			}
		}
	}
}

/*
bool QueryEvaluator::evaluateFollowsStarBoolean(Relationship r, std::unordered_map<std::string, TypeTable::SynType> m){
	string tk1=r.getToken1();
	string tk2=r.getToken2();
	Follows *f = pkb->getFollows();
	int stmtnum=0;
	vector<int> temp;

	bool flag = false;

	if(isdigit(tk1[0]) && isdigit(tk2[0])){
		stmtnum = atoi(tk1.c_str());
		while(stmtnum!=-1){
			cout<<"STMTNUM is "<<stmtnum<<endl;
			stmtnum = f->getFollows(TypeTable::STMT, stmtnum);
			if(stmtnum==atoi(tk2.c_str()))
				flag = true;
			if(stmtnum>atoi(tk2.c_str()))
				break;
		}
	}
	else if((isalpha(tk1[0]) && isalpha(tk2[0])) || isdigit(tk2[0])){
		temp = evaluateFollowsStar(r, m, tk1);
	}
	else{
		temp = evaluateFollowsStar(r, m, tk2);
	}

	if(!temp.empty())
		flag = true;

	return flag;
}*/

void QueryEvaluator::evaluateParent(Relationship r, unordered_map<string, TypeTable::SynType> m, int relIndex){
	string tk1 = r.getToken1();
	string tk2 = r.getToken2();

	Parent *p = pkb->getParent();
	TypeTable *t = pkb->getTypeTable();

	vector<int> answer;
	vector<Pair> parentAns;
	unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(tk1);
	unordered_map<string, TypeTable::SynType>::iterator i2 = m.find(tk2);

	//Parent(a,b)
	if(isalpha(tk1[0]) && isalpha(tk2[0])){

		answer = t->getAllStmts(i1->second);
		
		for(vector<int>::iterator it=answer.begin(); it!=answer.end(); it++){
			vector<int> children = p->getChildren(i1->second, *it);
			for(vector<int>::iterator it2=children.begin(); it2!=children.end(); it2++){
				parentAns.push_back(Pair(*it, *it2, tk1, tk2));
			}
		}
	}


	//Parent(a,3)
	else if(isalpha(tk1[0])){
		cout<<"Calling getParent(TYPE, STMTNUM)"<<endl;
		int parent = p->getParent(i1->second, atoi(tk2.c_str()));
		parentAns.push_back(Pair(parent, atoi(tk2.c_str()), tk1, tk2));
	}

	//Parent(3,a)
	else if(isalpha(tk2[0])){
		vector<int> children = p->getChildren(i2->second, atoi(tk1.c_str()));
		for(vector<int>::iterator it=children.begin(); it!=children.end(); it++){
			parentAns.push_back(Pair(atoi(tk1.c_str()), *it, tk1, tk2));
		}
	}

	//Parent(1,5)
	else{
		 if(p->isParent(atoi(tk1.c_str()), atoi(tk2.c_str()))){
			 parentAns.push_back(Pair (1,1,"true","true"));
		 }else{
			 parentAns.push_back(Pair (0,0,"false","false"));
		 }
	}

		//If both a and b exist in linkages
	if(isExistInLinkages(tk1) && isExistInLinkages(tk2)){

		removePairsFromRelAns(&parentAns, tk1, 1);
		removePairsFromRelAns(&parentAns, tk2, 2);
		removePairs(parentAns, tk1);
		removePairs(parentAns, tk2);
		insertLinks(tk1, relIndex);
		insertLinks(tk2, relIndex);
	}

	//If only a exist
	else if(isExistInLinkages(tk1)){
		removePairsFromRelAns(&parentAns, tk1, 1);
		removePairs(parentAns, tk1);
		insertLinks(tk1, relIndex);
	}

	//If only b exist
	else if(isExistInLinkages(tk2)){
		removePairsFromRelAns(&parentAns, tk2, 2);
		removePairs(parentAns, tk2);
		insertLinks(tk2, relIndex);
	}

	else {

	}

	relAns.insert(make_pair(relIndex, parentAns));
}



vector<int> QueryEvaluator::evaluateParentStar(Relationship r, unordered_map<string, TypeTable::SynType> m, string selectedSyn){
	string tk1=r.getToken1();
	string tk2=r.getToken2();
	Parent *p = pkb->getParent();
	TypeTable *t = pkb->getTypeTable();
	set<int> answer;
	vector<int> selected;
	vector<int> vectorAnswer;
	int stmtNumber = 0;
	unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(tk1);
	unordered_map<string, TypeTable::SynType>::iterator i2 = m.find(tk2);

	//Select w such that Parent*(w, a)
	if(isalpha(tk1[0]) && isalpha(tk2[0]) && selectedSyn==tk1){
		selected = t->getAllStmts(i2->second);	//get all assign statements

		for(vector<int>::iterator it = selected.begin(); it!=selected.end(); it++){
			stmtNumber = p->getParent(*it);
			answer.insert(stmtNumber);
			stmtNumber = p->getParent(stmtNumber);
			while(stmtNumber!=-1){
				answer.insert(stmtNumber);
				stmtNumber = p->getParent(stmtNumber);
			}
		}
	}

	//Select a such that Parent*(w, a)
	else if(isalpha(tk1[0]) && isalpha(tk2[0]) && selectedSyn==tk2){
		cout<<"In supposed area"<<endl;
		selected = t->getAllStmts(i2->second);	//get all assign statements

		for(vector<int>::iterator it = selected.begin(); it!=selected.end(); it++){
			stmtNumber = p->getParent(*it);
			if(stmtNumber!=-1)
				answer.insert(*it);
		}
	}

	//Select w such that Parent*(w, 13)
	else if(selectedSyn==tk1){

		stmtNumber = atoi(tk2.c_str());
		stmtNumber = p->getParent(stmtNumber);

		while(stmtNumber!=-1){
			answer.insert(stmtNumber);
			stmtNumber = p->getParent(stmtNumber);
		}
	}

	//Select a such that Parent*(3, a)
	else {
		
		selected = t->getAllStmts(i2->second);
		
		for(vector<int>::iterator it = selected.begin(); it!=selected.end(); it++){			
			stmtNumber = p->getParent(*it);
			while(stmtNumber!=-1){
				if(stmtNumber == atoi(tk1.c_str())){
					answer.insert(*it);	
					break;
				}
				stmtNumber = p->getParent(stmtNumber);
			}
			
		}
	}

	copy(answer.begin(), answer.end(), back_inserter(vectorAnswer));

	return vectorAnswer;
}

/*
bool QueryEvaluator::evaluateParentStarBoolean(Relationship r, std::unordered_map<std::string, TypeTable::SynType> m){
	string tk1=r.getToken1();
	string tk2=r.getToken2();
	Parent *p = pkb->getParent();
	int stmtnum=0;
	vector<int> temp;

	bool flag = false;

	//Parent*(1,8)
	if(isdigit(tk1[0]) && isdigit(tk2[0])){
		stmtnum = atoi(tk2.c_str());
		while(stmtnum!=-1){
			cout<<"STMTNUM IS "<<stmtnum<<endl;
			stmtnum = p->getParent(stmtnum);
			if(stmtnum==atoi(tk1.c_str()))
				flag = true;
			if(stmtnum<atoi(tk1.c_str()))
				break;
		}
	}

	//Parent*(w, a) Parent*(w, 3)
	else if((isalpha(tk1[0]) && isalpha(tk2[0])) || isdigit(tk2[0])){
		temp = evaluateParentStar(r, m, tk1);
	}

	//Parent*(3, a)
	else{
		temp = evaluateFollowsStar(r, m, tk2);
	}

	if(!temp.empty())
		flag = true;

	return flag;
}*/

void QueryEvaluator::evaluateModifies(Relationship r, std::unordered_map<std::string, TypeTable::SynType> m, int relIndex) {
	string tk1=r.getToken1();
	string tk2=r.getToken2();
	Modifies *mod = pkb->getModifies();
	TypeTable *t = pkb->getTypeTable();
	VarTable *varTab = pkb->getVarTable();
	ProcTable *proc = pkb->getProcTable();
	vector<int> selected;
	vector<Pair> modAns;
	vector<int> answer;
	unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(tk1);
	unordered_map<string, TypeTable::SynType>::iterator i2 = m.find(tk2);

	//Modifies(a,v)
	if(isalpha(tk1[0]) && isalpha(tk2[0])){

		//If first token is of procedure type
		if(t->getSynType(tk1)==TypeTable::PROCEDURE){

			selected = proc->getAllProcIndexes();

			//iterate through all procedures
			for(vector<int>::iterator it=selected.begin(); it!=selected.end(); it++){
				answer = mod->getModifiesProc(*it);
				for(vector<int>::iterator it2=answer.begin(); it2!=answer.end(); it2++){
					modAns.push_back(Pair (*it, *it2, tk1, tk2));
				}
			}
		} 
		

		//Otherwise
		else {
			selected = t->getAllStmts(i1->second);
			for(vector<int>::iterator it=selected.begin(); it!=selected.end(); it++){
				answer = mod->getModifies(*it);
				for(vector<int>::iterator it2=answer.begin(); it2!=answer.end(); it2++){
					modAns.push_back(Pair (*it, *it2, tk1, tk2));
				}
			}
		}
	}
	/*
	//Select v Modifies(a,v)
	else if(isalpha(tk1[0]) && isalpha(tk2[0]) && selectedSyn==tk2){
		selected = t->getAllStmts(TypeTable::ASSIGN);
		vector<int> modifiedVar;
		for(vector<int>::iterator it = selected.begin(); it!=selected.end(); it++){	
			cout<<"Calling getModifies(STMTNUM)"<<endl;
			modifiedVar = mod->getModifies(*it);
			answer.insert(modifiedVar.begin(), modifiedVar.end());
		}
		selected.clear();
		copy(answer.begin(), answer.end(), back_inserter(selected));
		return selected;
	}*/

	//Modifies(a, "x")
	else if(isalpha(tk1[0])){
		string varName = tk2.substr(1,tk2.length()-2);

		//If first token is of type procedure
		if(t->getSynType(tk1)==TypeTable::PROCEDURE){

			answer = mod->getModifiesProcVar(varName);
			for(vector<int>::iterator it=answer.begin(); it!=answer.end(); it++){
				modAns.push_back(Pair (*it, varTab->getVarIndex(varName), tk1, tk2));
			}
		}

		//otherwise
		else {
			answer = mod->getModifies(i1->second,varName);
			for(vector<int>::iterator it=answer.begin(); it!=answer.end(); it++){
				modAns.push_back(Pair (*it, varTab->getVarIndex(varName), tk1, tk2));
			}
		}

	}

	//Select v such that Modifies(1, v);
	else if(isalpha(tk2[0])){
		selected = mod->getModifies(atoi(tk1.c_str()));
		for(vector<int>::iterator it=selected.begin(); it!=selected.end(); it++){
			modAns.push_back(Pair (atoi(tk1.c_str()), *it, tk1, tk2));
		}
	}

	//Modifies("Third", "x")
	else if(tk1[0]=='\"'){
		string procName = tk1.substr(1,tk1.length()-2);
		string varName = tk2.substr(1,tk2.length()-2);
		if(mod->isModifiesProc(procName, varName)){
			modAns.push_back(Pair (1,1,"true","true"));
		}else {
			modAns.push_back(Pair (0,0,"false","false"));
		}
	}

	//Modifies(1, "x")
	else {
		string varName = tk2.substr(1,tk2.length()-2);
		if(mod->isModifies(atoi(tk1.c_str()), varName)){
			 modAns.push_back(Pair (1,1,"true","true"));
		 }else{
			 modAns.push_back(Pair (0,0,"false","false"));
		 }
	}

	//If both a and b exist in linkages
	if(isExistInLinkages(tk1) && isExistInLinkages(tk2)){

		removePairsFromRelAns(&modAns, tk1, 1);
		removePairsFromRelAns(&modAns, tk2, 2);
		removePairs(modAns, tk1);
		removePairs(modAns, tk2);
		insertLinks(tk1, relIndex);
		insertLinks(tk2, relIndex);
	}

	//If only a exist
	else if(isExistInLinkages(tk1)){
		removePairsFromRelAns(&modAns, tk1, 1);
		removePairs(modAns, tk1);
		insertLinks(tk1, relIndex);
	}

	//If only b exist
	else if(isExistInLinkages(tk2)){
		removePairsFromRelAns(&modAns, tk2, 2);
		removePairs(modAns, tk2);
		insertLinks(tk2, relIndex);
	}

	else {

	}

	relAns.insert(make_pair(relIndex, modAns));
}

/*
bool QueryEvaluator::evaluateModifiesBoolean(Relationship r, std::unordered_map<std::string, TypeTable::SynType> m){
	string tk1=r.getToken1();
	string tk2=r.getToken2();
	Modifies *mod = pkb->getModifies();
	TypeTable *t = pkb->getTypeTable();

	unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(tk1);
	unordered_map<string, TypeTable::SynType>::iterator i2 = m.find(tk2);

	//Modifies(a,v)
	if(isalpha(tk1[0]) && isalpha(tk2[0])){
		vector<int>ans = mod->getModifies(i1->second);
		if(!ans.empty()){
			return true;
		}
	}

	//Modifies(a, "x")
	else if(isalpha(tk1[0])){
		vector<int> ans = mod->getModifies(i1->second, tk2.substr(1,tk2.length()-2));
		if(!ans.empty())
			return true;
	}

	//Modifies(1, v)
	else if(isdigit(tk1[0]) && isalpha(tk2[0])){
		vector<int> ans = mod->getModifies(atoi(tk1.c_str()));
		if(!ans.empty())
			return true;
	}

	//Modifies(1, "x")
	else{
		return mod->isModifies(atoi(tk1.c_str()), tk2.substr(1, tk2.length()-2));
	}

	return false;
}*/

void QueryEvaluator::evaluateUses(Relationship r, std::unordered_map<std::string, TypeTable::SynType> m, int relIndex) {
	string tk1=r.getToken1();
	string tk2=r.getToken2();
	Uses *use = pkb->getUses();
	TypeTable *t = pkb->getTypeTable();
	VarTable *varTab = pkb->getVarTable();
	ProcTable *proc = pkb->getProcTable();
	vector<int> selected;
	vector<int> answer;
	vector<Pair> usesAns;
	unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(tk1);
	unordered_map<string, TypeTable::SynType>::iterator i2 = m.find(tk2);

	//Uses(a,v)
	if(isalpha(tk1[0]) && isalpha(tk2[0])){

		//If first token is of procedure type
		if(t->getSynType(tk1)==TypeTable::PROCEDURE){

			selected = proc->getAllProcIndexes();

			//iterate through all procedures
			for(vector<int>::iterator it=selected.begin(); it!=selected.end(); it++){
				answer = use->getUsesProc(*it);
				for(vector<int>::iterator it2=answer.begin(); it2!=answer.end(); it2++){
					usesAns.push_back(Pair (*it, *it2, tk1, tk2));
				}
			}
		} 
		

		//Otherwise
		else {
			selected = t->getAllStmts(i1->second);
			for(vector<int>::iterator it=selected.begin(); it!=selected.end(); it++){
				answer = use->getUses(*it);
				for(vector<int>::iterator it2=answer.begin(); it2!=answer.end(); it2++){
					usesAns.push_back(Pair (*it, *it2, tk1, tk2));
				}
			}
		}
	}

	//Select a Uses(a, "x")
	else if(isalpha(tk1[0])){
		string varName = tk2.substr(1,tk2.length()-2);

		//If first token is of type procedure
		if(t->getSynType(tk1)==TypeTable::PROCEDURE){

			answer = use->getUsesProcVar(varName);
			for(vector<int>::iterator it=answer.begin(); it!=answer.end(); it++){
				usesAns.push_back(Pair (*it, varTab->getVarIndex(varName), tk1, tk2));
			}
		}

		//otherwise
		else {
			answer = use->getUses(i1->second,varName);
			for(vector<int>::iterator it=answer.begin(); it!=answer.end(); it++){
				usesAns.push_back(Pair (*it, varTab->getVarIndex(varName), tk1, tk2));
			}
		}

	}


	//Select v such that Uses(1, v);
	else if(isalpha(tk2[0])){
		selected = use->getUses(atoi(tk1.c_str()));
		for(vector<int>::iterator it=selected.begin(); it!=selected.end(); it++){
			usesAns.push_back(Pair (atoi(tk1.c_str()), *it, tk1, tk2));
		}
	}

	//Modifies("Third", "x")
	else if(tk1[0]=='\"'){
		string procName = tk1.substr(1,tk1.length()-2);
		string varName = tk2.substr(1,tk2.length()-2);
		if(use->isUsesProc(procName, varName)){
			usesAns.push_back(Pair (1,1,"true","true"));
		}else {
			usesAns.push_back(Pair (0,0,"false","false"));
		}
	}

	//Modifies(1, "x")
	else {
		string varName = tk2.substr(1,tk2.length()-2);
		if(use->isUses(atoi(tk1.c_str()), varName)){
			 usesAns.push_back(Pair (1,1,"true","true"));
		 }else{
			 usesAns.push_back(Pair (0,0,"false","false"));
		 }
	}

	//If both a and b exist in linkages
	if(isExistInLinkages(tk1) && isExistInLinkages(tk2)){

		removePairsFromRelAns(&usesAns, tk1, 1);
		removePairsFromRelAns(&usesAns, tk2, 2);
		removePairs(usesAns, tk1);
		removePairs(usesAns, tk2);
		insertLinks(tk1, relIndex);
		insertLinks(tk2, relIndex);
	}

	//If only a exist
	else if(isExistInLinkages(tk1)){
		removePairsFromRelAns(&usesAns, tk1, 1);
		removePairs(usesAns, tk1);
		insertLinks(tk1, relIndex);
	}

	//If only b exist
	else if(isExistInLinkages(tk2)){
		removePairsFromRelAns(&usesAns, tk2, 2);
		removePairs(usesAns, tk2);
		insertLinks(tk2, relIndex);
	}

	else {

	}

	relAns.insert(make_pair(relIndex, usesAns));
}

/*
bool QueryEvaluator::evaluateUsesBoolean(Relationship r, std::unordered_map<std::string, TypeTable::SynType> m){
	string tk1=r.getToken1();
	string tk2=r.getToken2();
	Uses *use = pkb->getUses();
	TypeTable *t = pkb->getTypeTable();

	unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(tk1);
	unordered_map<string, TypeTable::SynType>::iterator i2 = m.find(tk2);

	//Uses(a,v)
	if(isalpha(tk1[0]) && isalpha(tk2[0])){
		vector<int>ans = use->getUses(i1->second);
		if(!ans.empty()){
			return true;
		}
	}

	//Uses(a, "x")
	else if(isalpha(tk1[0])){
		vector<int> ans = use->getUses(i1->second, tk2.substr(1,tk2.length()-2));
		if(!ans.empty())
			return true;
	}

	//Uses(1, "x")
	else{
		return use->isUses(atoi(tk1.c_str()), tk2.substr(1, tk2.length()-2));
	}

	return false;
}*/

vector<int> QueryEvaluator::evaluatePattern(Query q, string leftHandSide, std::string rightHandSide) {
	vector<int> answers;
	VarTable* varTable = pkb->getVarTable();

	leftHandSide.erase(std::remove(leftHandSide.begin(), leftHandSide.end(), '\"'), leftHandSide.end());
	rightHandSide.erase(std::remove(rightHandSide.begin(), rightHandSide.end(), '\"'), rightHandSide.end());

	unordered_map<string, TypeTable::SynType>::iterator iterate = q.getSynTable().find(leftHandSide);
	
	if(iterate->second == 6) {
		vector<int> varIndexs = varTable->getAllVarIndex();
		for(int i=0; i<varIndexs.size(); i++) {
			leftHandSide = varTable->getVarName(varIndexs.at(i));
			Node* root = pkb->getASTRoot();
			stack<Node> st;
			st.push(*root);
			while(!st.empty()) {
				Node nd = st.top();
				st.pop();
				if(nd.getType().compare("assign")==0) {
					vector<Node*> children = nd.getChild();
					Node childOne = *children.at(0);
					Node childTwo = *children.at(1);
					if(evaluateLeftHandSide(leftHandSide, childOne) && evaluateRightHandSide(rightHandSide, childTwo))
						answers.push_back(nd.getProgLine());
				}
				else {
					vector<Node*> children = nd.getChild();
					for(int i=0; i<children.size(); i++) {
						Node child = *children.at(i);
						st.push(child);
					}
				}
			}
		}
	}
	else {
		Node* root = pkb->getASTRoot();
		stack<Node> st;
		st.push(*root);
		while(!st.empty()) {
			Node nd = st.top();
			st.pop();
			if(nd.getType().compare("assign")==0) {
				vector<Node*> children = nd.getChild();
				Node childOne = *children.at(0);
				Node childTwo = *children.at(1);
				if(evaluateLeftHandSide(leftHandSide, childOne) && evaluateRightHandSide(rightHandSide, childTwo))
					answers.push_back(nd.getProgLine());
			}
			else {
				vector<Node*> children = nd.getChild();
				for(int i=0; i<children.size(); i++) {
					Node child = *children.at(i);
					st.push(child);
				}
			}
		}
	}

	return answers;
}

bool QueryEvaluator::evaluateLeftHandSide(string IDENT, Node rightHand) {
	if(IDENT.compare("_") == 0)
		return true;
	else if(IDENT.compare(rightHand.getData()) == 0)
		return true;
	else 
		return false;
}

bool QueryEvaluator::evaluateRightHandSide(string pattern, Node leftHand) {
	if(pattern.compare("_") == 0)
		return true;
	else if(pattern.find("+") == string::npos){
		pattern = pattern.substr(1, pattern.length()-2);
		stack<Node> st;
		st.push(leftHand);
		while(!st.empty()) {
			Node nd = st.top();
			st.pop();
			if(nd.getData().compare(pattern) == 0)
				return true;
			else {
				vector<Node*> children = nd.getChild();
				for(int i=0; i< children.size(); i++) {
					Node child = *children.at(i);
					st.push(child);
				}
			}
		}
	}
	else {
		pattern = pattern.substr(1, pattern.length()-2);
		unsigned pos = pattern.find("+");
		string right = pattern.substr(0, pos);
		string left = pattern.substr(pos+1);

		stack<Node> st;
		st.push(leftHand);
		while(!st.empty()) {
			Node nd = st.top();
			st.pop();
			if(nd.getType().compare("operator")==0 && nd.getData().compare("+")==0) {
				vector<Node*> children = nd.getChild();
				Node childOne = *children.at(0);
				Node childTwo = *children.at(1);
				cout<<"currNode: "<< nd.getData()<< " " << nd.getProgLine() <<endl;
				cout<<"left, right: "<< childOne.getData() << " " << childTwo.getData()<< endl;
				if(childOne.getData().compare(right)==0 && childTwo.getData().compare(left)==0)
					return true;
				else {
					vector<Node*> children = nd.getChild();
					for(int i=0; i<  children.size(); i++) {
						Node child = *children.at(i);
						st.push(child);
					}
				}
			}
			else {
				vector<Node*> children = nd.getChild();
				for(int i=0; i<  children.size(); i++) {
					Node child = *children.at(i);
					st.push(child);
				}
			}

		}
	}
	return false;
}