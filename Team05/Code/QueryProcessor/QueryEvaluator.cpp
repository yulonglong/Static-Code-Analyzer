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

unordered_map<string, vector<int>> QueryEvaluator::linkages;
unordered_map<int, vector<Pair>> QueryEvaluator::relAns;
unordered_map<int, vector<std::string>> QueryEvaluator::relParameters;

QueryEvaluator::QueryEvaluator(PKB* p){
	pkb = p;
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

	//Get relationships and order them
	vector<Relationship> relations = q.getRelVect();
	relations = orderRelationship(relations);

	unordered_map<string, TypeTable::SynType> m = q.getSynTable();
	vector<string> selectedSyn = q.getSelectedSyn();
	unordered_map<string, vector<int>> answers;
	TypeTable *t = pkb->getTypeTable();

	//If relations is empty
	if(relations.empty()){
		for(vector<string>::iterator it = selectedSyn.begin(); it!=selectedSyn.end(); it++){
			vector<int> synAns = t->getAllStmts(m.find(*it)->second);
			answers.insert(make_pair<string, vector<int>>(*it, synAns));
		}

		return answers;
	}

	//If relations are not empty
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
			evaluateParentStar(*it, m, relIndex); break;//review

		case Relationship::CALLS:
			evaluateCalls(*it, relIndex); break;

		case Relationship::CALLSSTAR:
			evaluateCallsStar(*it, relIndex); break;

		case Relationship::MODIFIES:
			evaluateModifies(*it, m, relIndex); break;

		case Relationship::USES:
			evaluateUses(*it, m, relIndex); break;

		case Relationship::PATTERN:	
			vector<int> proxy = evaluatePattern(q, it->getToken1(), it->getToken2()); //review
		}

		vector<string> parametersVec;
		parametersVec.push_back(it->getToken1());
		parametersVec.push_back(it->getToken2());

		QueryEvaluator::relParameters.insert(make_pair<int, vector<string>>(relIndex, parametersVec));
		relIndex++;
	}

	//If one of the relations are evaluated to false or empty
	for(int i=0; i<relations.size(); i++){
		vector<Pair> v = relAns.find(i)->second;
		if(v.empty() || v.at(0).ans1==-2){
			return answers;
		}
	}


	for(vector<string>::iterator it = selectedSyn.begin(); it!=selectedSyn.end(); it++){
		int index = (linkages.find(*it)->second).at(0);
		vector<string> param = relParameters.find(index)->second;

		vector<Pair> p = relAns.at(index);
		set<int> synAns;
		vector<int> synAnsVec;

		if(*it==param.at(0)){
			for(vector<Pair>::iterator it2 = p.begin(); it2!=p.end(); it2++){
				synAns.insert(it2->ans1);
			}

		}else {
			for(vector<Pair>::iterator it2 = p.begin(); it2!=p.end(); it2++){
				synAns.insert(it2->ans2);
			}
		}

		for(set<int>::iterator it3 = synAns.begin(); it3!=synAns.end(); it3++){
			synAnsVec.push_back(*it3);
		}

		answers.insert(make_pair<string, vector<int>>(*it, synAnsVec));
	}

	return answers;
}

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
				callAns.push_back(Pair (*it, *it2));
				cout<<"it = "<<*it<<" "<<"it2 = "<<*it2<<endl;
			}
		}

	}

	//Select p Calls(p, "Second") Calls(_, "Second")
	else if(isalpha(tk1[0]) || (tk1=="_" && tk2!="_")){
		ans = call->getCalls(tk2.substr(1,tk2.length()-2));
		if(tk1=="_"){
			if(!ans.empty()){
				callAns.push_back(Pair(-1,-1));
			}else{
				callAns.push_back(Pair(-2,-2));
			}
		}
		else{
			int procIndex = proc->getProcIndex(tk2.substr(1,tk2.length()-2));

			for(vector<int>::iterator it=ans.begin(); it!=ans.end(); it++){
				callAns.push_back(Pair (*it, procIndex));
			}
		}
	}

	//Select q Calls("First", q)
	else if(isalpha(tk2[0]) || (tk1!="_" && tk2=="_")){
		ans = call->getCalled(tk1.substr(1,tk1.length()-2));

		if(tk2=="_"){
			if(!ans.empty()){
				callAns.push_back(Pair(-1,-1));
			}else{
				callAns.push_back(Pair(-2,-2));
			}
		}
		else{
			int procIndex = proc->getProcIndex(tk1.substr(1,tk1.length()-2));

			for(vector<int>::iterator it=ans.begin(); it!=ans.end(); it++){
				callAns.push_back(Pair (procIndex, *it));
			}
		}
	}

	//Calls(_,_)
	else if(tk1=="_" && tk2=="_"){
		ans = call->getCalls();
		if(!ans.empty()){
			callAns.push_back(Pair (-1, -1));
		}else{
			callAns.push_back(Pair (-2, -2));
		}
	}

	//Calls("Third", "Fourth")
	else {
		cout<<"supposed"<<endl;
		call->setCalls("\"first\"", "\"second\"", 4);
		cout<<tk1.substr(1, tk1.length()-2)<<tk2.substr(1,tk2.length()-2)<<endl;
		if(call->isCalls(tk1.substr(1, tk1.length()-2), tk2.substr(1,tk2.length()-2))){
			callAns.push_back(Pair (-1, -1));
		}else{
			callAns.push_back(Pair (-2, -2));
		}
	}

	intersectPairs(tk1,tk2,&callAns, relIndex);

	relAns.insert(make_pair(relIndex, callAns));


}

//Returns true if token already exists in QueryEvaluator::linkages
bool QueryEvaluator::isExistInLinkages(string token){
	if(QueryEvaluator::linkages.find(token)!=QueryEvaluator::linkages.end()){
		return true;	
	}

	return false;
}

vector<int> * QueryEvaluator::findAnswerVectorFromToken(string token){

	vector<int> *point = &QueryEvaluator::linkages.find(token)->second;

	return point;
}

//return set of int answers for a particular syn
set<int> QueryEvaluator::retrieveTokenEvaluatedAnswers(string tk){
	vector<int> listOfRel = QueryEvaluator::linkages.find(tk)->second;

	vector<Pair> ans = QueryEvaluator::relAns.find(listOfRel.at(0))->second;
	cout<<"Retrieving Token Evaluated Answers with first relationship index = "<<listOfRel.at(0)<<endl;
	string relTk1 = QueryEvaluator::relParameters.find(listOfRel.at(0))->second.at(0);
	cout<<"RelTk1 = "<<relTk1<<" "<<"tk = "<<tk<<endl;
	set<int> setAns;
	if(relTk1==tk){
		for(vector<Pair>::iterator it = ans.begin(); it!=ans.end(); it++){
			setAns.insert(it->ans1);
		}
	}else{
		for(vector<Pair>::iterator it = ans.begin(); it!=ans.end(); it++){
			setAns.insert(it->ans2);
		}
	}

	cout<<"PRINTING ELEMENTS OF RETRIEVED TOKEN: "<<endl;
	for(set<int>::iterator it = setAns.begin(); it!=setAns.end(); it++){
		cout<<*it<<endl;
	}
	cout<<"End retrieving token"<<endl;
	return setAns;
}


void QueryEvaluator::removePairs(vector<Pair> p, string token, int i){
	int pairIndex;
	vector<int> listOfRel = QueryEvaluator::linkages.find(token)->second;
	vector<int> list;
	if(i==1){
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
		unordered_map<int, vector<Pair>>::iterator i = QueryEvaluator::relAns.find(*it);
		vector<Pair> *pr = &i->second;
		int index = QueryEvaluator::relAns.find(*it)->first;

		//find out whether the token is the first or second argument of the relationship
		if(QueryEvaluator::relParameters.find(index)->second.at(0)==token){
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
	TypeTable * t = pkb->getTypeTable();


	unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(tk1);
	unordered_map<string, TypeTable::SynType>::iterator i2 = m.find(tk2);
	

	//with v1.varName = p.procName with c.value = s.stmt#
	if(isalpha(tk1[0]) && isalpha(tk2[0])){
		//if both exist in links then remove all unnecessary tuples. push QueryEvaluator::relAns true
		if(isExistInLinkages(tk1) && isExistInLinkages(tk2)){
			
			//if both tokens are of the same type e.g v1 v2
			if(i1->second == i2->second){
				set<int> tk1Set = retrieveTokenEvaluatedAnswers(tk1);
				set<int> tk2Set = retrieveTokenEvaluatedAnswers(tk2);

				set<int> intersect;
				set_intersection(tk1Set.begin(), tk1Set.end(), tk2Set.begin(), tk2Set.end(), std::inserter(intersect, intersect.begin()));

				vector<Pair> withAns;
				for(set<int>::iterator it = intersect.begin(); it!=intersect.end(); it++){
					withAns.push_back(Pair (*it, 0));
				}

				removePairs(withAns, tk1, 1);
				removePairs(withAns, tk2, 1);
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

					set_intersection(ans1string.begin(), ans1string.end(), ans2string.begin(), ans2string.end(), inserter(ans3string,ans3string.begin()));

					for(set<string>::iterator it = ans3string.begin(); it!=ans3string.end(); it++){
						ans3stringVar.push_back(Pair (v->getVarIndex(*it), v->getVarIndex(*it)));
						ans3stringProc.push_back(Pair (p->getProcIndex(*it), p->getProcIndex(*it)));
					}

					if(i1->second==TypeTable::VARIABLE){
						removePairs(ans3stringVar, tk1,1);
						removePairs(ans3stringProc, tk2,1);
					}
					else{
						removePairs(ans3stringProc, tk1,1);
						removePairs(ans3stringVar, tk2,1);
					}
				}
				else{
					std::set_intersection(ans1.begin(), ans1.end(), ans2.begin(), ans2.end(), inserter(ans3, ans3.begin()));
					vector<Pair> finalAns;

					for(set<int>::iterator it = ans3.begin(); it!=ans3.end(); it++){
						finalAns.push_back(Pair(*it, *it));
					}

					removePairs(finalAns, tk1, 1);
					removePairs(finalAns, tk2, 1);
				}
			}
		}

		else {
			vector<Pair> withAns;
			if((i1->second==TypeTable::CONSTANT && i2->second==TypeTable::STMT) || (i1->second==TypeTable::STMT && i2->second==TypeTable::CONSTANT) || (i1->second==TypeTable::CONSTANT && i2->second==TypeTable::PROGLINE) || (i1->second==TypeTable::PROGLINE && i2->second==TypeTable::CONSTANT)){
				vector<int> allConst = c->getAllConstValue();
				int stmtRange = t->getStmtRange();

				for(vector<int>::iterator it = allConst.begin(); it!=allConst.end(); it++){
					if(*it<=stmtRange){
						withAns.push_back(Pair(*it, *it));
					}
				}		
			}

			else if((i1->second==TypeTable::STMT && i2->second==TypeTable::PROGLINE) || (i1->second==TypeTable::PROGLINE && i2->second==TypeTable::STMT)){
				int higher = t->getStmtRange();
				for(int i=1; i<=higher; i++){
					withAns.push_back(Pair (i, i));
				}
			}

			else{

			}

			if(isExistInLinkages(tk1)){
				removePairs(withAns, tk1, 1);
			} else if(isExistInLinkages(tk2)){
				removePairs(withAns, tk2, 2);
			}else {

			}

			if(withAns.empty()){
				withAns.push_back(Pair (-2, -2));
				relAns.insert(make_pair<int, vector<Pair>>(relIndex, withAns));
			}
		}
	}
	//with v.varName = "x" with p.procName = "Third"
	else {
		//if exist in links then delete all unnecessary tuples then push into QueryEvaluator::relAns true
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
			withAns.push_back(Pair (index, index));
			removePairs(withAns, tk1, 2);
		}

		//else evaluate true or false
		else {
			if((i1->second == TypeTable::VARIABLE && v->getVarIndex(tk2)!=-1) || (i1->second == TypeTable::PROCEDURE && p->getProcIndex(tk2)!=-1)
				|| (i1->second == TypeTable::CONSTANT && c->getConstIndex(tk2)!=-1)){
				withAns.push_back(Pair (-1, -1));
			}

			else if(i1->second == TypeTable::STMT || i1->second == TypeTable::PROGLINE){
				int stmtRange = t->getStmtRange();
				if(atoi(tk2.c_str())<=stmtRange){
					withAns.push_back(Pair (-1, -1));
				}else {
					withAns.push_back(Pair (-2, -2));
				}
			}

			else{
				withAns.push_back(Pair (-2, -2));
			}
			relAns.insert(make_pair<int, vector<Pair>>(relIndex, withAns));
		}
	}
	
}

void QueryEvaluator::evaluateNext(Relationship r, unordered_map<string, TypeTable::SynType> m, int relIndex){
	string tk1 = r.getToken1();
	string tk2 = r.getToken2();
	Next* n = pkb->getNext();
	TypeTable *t = pkb->getTypeTable();
	unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(tk1);
	unordered_map<string, TypeTable::SynType>::iterator i2 = m.find(tk2);

	vector<Pair> nextAns;

	//if token 1 and token 2 is alpha
	//Next(s, a)
	if(isalpha(tk1[0]) && isalpha(tk2[0])){

		//If s and a exists, retrieve s and a answers, then isNext
		if(isExistInLinkages(tk1) && isExistInLinkages(tk2)){
			set<int> firstSet = retrieveTokenEvaluatedAnswers(tk1);
			set<int> secondSet = retrieveTokenEvaluatedAnswers(tk2);

			for(set<int>::iterator it = firstSet.begin(); it!=firstSet.end(); it++){
				for(set<int>::iterator it2 = secondSet.begin(); it2!=secondSet.end(); it2++){
					if(n->isNext(*it, *it2)){ 
						nextAns.push_back(Pair (*it, *it2));
					}
				}
			}

			removePairs(nextAns, tk1, 1);
			removePairs(nextAns, tk2, 2);
		}

		//If s exists, retrieve s then getNext check type
		if(isExistInLinkages(tk1)){
			set<int> firstSet = retrieveTokenEvaluatedAnswers(tk1);
			vector<int> tk2Ans;

			for(set<int>::iterator it = firstSet.begin(); it!=firstSet.end(); it++){
				tk2Ans = n->getNext(*it);
				for(vector<int>::iterator it1 = tk2Ans.begin(); it1!=tk2Ans.end(); it1++){
					if(t->getType(*it1)==i2->second){
						nextAns.push_back(Pair (*it, *it1));
					}
				}
			}

			removePairs(nextAns, tk1, 1);
		}

		//If a exists, retrieve a, get previous check type
		if(isExistInLinkages(tk2)){
			set<int> secondSet = retrieveTokenEvaluatedAnswers(tk2);
			int tk1Ans;

			for(set<int>::iterator it = secondSet.begin(); it!=secondSet.end(); it++){
				tk1Ans = n->getPrevious(*it);
				if(t->getType(tk1Ans) == i1->second){
					nextAns.push_back(Pair (tk1Ans, *it));
				}
			}

			removePairs(nextAns, tk2, 2);
		}

		//If both doesn't exist, then getNext(type, type)
		else {
			vector<int> allTk1 = t->getAllStmts(i2->second);
			int tk1Ans;
			for(vector<int>::iterator it= allTk1.begin(); it!=allTk1.end(); it++){
				tk1Ans = n->getPrevious(*it);
				if(t->getType(tk1Ans)==i1->second){
					nextAns.push_back(Pair (tk1Ans, *it));
				}
			}
		}

		insertLinks(tk1, relIndex);
		insertLinks(tk2, relIndex);
	}

	//Next(n, 4)
	else if(isalpha(tk1[0])){
		int tk2Int = atoi(tk2.c_str());

		if(t->getType(n->getPrevious(tk2Int))==i1->second){
			nextAns.push_back(Pair (n->getPrevious(tk2Int), tk2Int));
		}
		
		if(isExistInLinkages(tk1)){
			removePairsFromRelAns(&nextAns, tk1, 1);
			removePairs(nextAns, tk1, 1);
		}

		insertLinks(tk1, relIndex);
	}

	//Next(3, n)
	else if(isalpha(tk2[0])){
		int tk1Int = atoi(tk1.c_str());
		vector<int> tk1Vec = n->getNext(tk1Int);

		for(vector<int>::iterator it = tk1Vec.begin(); it!=tk1Vec.end(); it++){
			if(t->getType(*it)==i2->second){
				nextAns.push_back(Pair (tk1Int, *it));
			}
		}

		if(isExistInLinkages(tk2)){
			removePairsFromRelAns(&nextAns, tk2, 2);
			removePairs(nextAns, tk2, 2);
		}

		insertLinks(tk2, relIndex);
	}

	//Next(3,4)
	else {
		if(n->isNext(atoi(tk1.c_str()), atoi(tk2.c_str()))){
			nextAns.push_back(Pair (-1,-1));
		}else{
			nextAns.push_back(Pair (-2, -2));
		}
	}

	relAns.insert(make_pair<int, vector<Pair>>(relIndex, nextAns));
}

void QueryEvaluator::evaluateNextStar(Relationship r, unordered_map<string, TypeTable::SynType> m, int relIndex){
	string tk1 = r.getToken1();
	string tk2 = r.getToken2();
	Next *n = pkb->getNext();
	TypeTable *t = pkb->getTypeTable();
	unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(tk1);
	unordered_map<string, TypeTable::SynType>::iterator i2 = m.find(tk2);

	set<Pair> nextStarAns;
	vector<Pair> nextStarAnsVec;
	//Next*(n,b)
	if(isalpha(tk1[0]) && isalpha(tk2[0])){

		//if b exists
		if(isExistInLinkages(tk2)){
			set<int> sb = retrieveTokenEvaluatedAnswers(tk2);
			
			int stmt = -1;

			for(set<int>::iterator it = sb.begin(); it!=sb.end(); it++){
				stmt = n->getPrevious(*it);
				while(stmt!=-1){
					if(i1->second==t->getType(stmt)){
						nextStarAns.insert(Pair (stmt, *it));
					}
					stmt = n->getPrevious(stmt);
				}
			}
			for(set<Pair>::iterator it = nextStarAns.begin(); it!=nextStarAns.end(); it++){
					nextStarAnsVec.push_back(*it);
				}
			if(isExistInLinkages(tk1)){
				removePairsFromRelAns(&nextStarAnsVec,tk1,1);
				removePairs(nextStarAnsVec, tk1, 1);
			}

			removePairs(nextStarAnsVec, tk2, 2);
		}

		else if(isExistInLinkages(tk1)){
			set<int> sa = retrieveTokenEvaluatedAnswers(tk1);
			vector<int> nextOfStmt;
			for(set<int>::iterator it = sa.begin(); it!=sa.end(); it++){
				recursiveNext(*it, *it, &nextStarAns, i2->second);
			}

			for(set<Pair>::iterator it = nextStarAns.begin(); it!=nextStarAns.end(); it++){
				nextStarAnsVec.push_back(*it);
			}

			removePairs(nextStarAnsVec, tk1, 1);
		}

		else {
			vector<int> allB = t->getAllStmts(i2->second);
			int stmt = -1;
			for(vector<int>::iterator it = allB.begin(); it!=allB.end(); it++){
				stmt = n->getPrevious(*it);
				while(stmt!=-1){
					if(t->getType(stmt) == i1->second){
						nextStarAns.insert(Pair (stmt, *it));
					}
					stmt = n->getPrevious(stmt);
				}
			}
		}

		insertLinks(tk1, relIndex);
		insertLinks(tk2, relIndex);
	}

	//Next*(n, 3)
	else if(isalpha(tk1[0])){
		int tk2Int = atoi(tk2.c_str());
		int stmt = n->getPrevious(tk2Int);

		while(stmt!=-1){
			if(t->getType(stmt)==i1->second){
				nextStarAnsVec.push_back(Pair (stmt, tk2Int));
			}
			stmt = n->getPrevious(tk2Int);
		}
		
		insertLinks(tk1, relIndex);
	}

	//Next*(3, n)
	else if(isalpha(tk2[0])){
		recursiveNext(atoi(tk1.c_str()), atoi(tk1.c_str()), &nextStarAns, i2->second);

		for(set<Pair>::iterator it = nextStarAns.begin(); it!=nextStarAns.end(); it++){
			nextStarAnsVec.push_back(*it);
		}

		insertLinks(tk2, relIndex);
	}

	//Next*(1,7)
	else {
		int tk2Int = atoi(tk2.c_str());
		int tk1Int = atoi(tk1.c_str());
		int stmt = n->getPrevious(tk2Int);

		while(stmt!=-1){
			if(stmt == tk1Int){
				nextStarAnsVec.push_back(Pair (-1, -1));
			}
			stmt = n->getPrevious(tk2Int);
		}
		
		if(nextStarAnsVec.empty()){
			nextStarAnsVec.push_back(Pair (-2, -2));
		}

	}

	relAns.insert(make_pair<int, vector<Pair>>(relIndex, nextStarAnsVec));
}
void QueryEvaluator::recursiveNext(int rootIndex, int currentIndex, set<Pair> * ans, TypeTable::SynType type){
	Next * n = pkb->getNext();
	TypeTable *t = pkb->getTypeTable();
	vector<int> next = n->getNext(currentIndex);

	for(vector<int>::iterator it = next.begin(); it!=next.end(); it++){
		if(t->getType(*it) == type){
			ans->insert(Pair (rootIndex, *it));
		}
		recursiveNext(rootIndex, *it, ans, type);
	}
}
void QueryEvaluator::recursiveCall(int rootProcIndex, int currentIndex, vector<Pair> * ans){
	Calls *c = pkb->getCalls();
	ProcTable *p = pkb->getProcTable();
	vector<int> called = c->getCalled(p->getProcName(currentIndex));

	for(vector<int>::iterator i=called.begin(); i!=called.end(); i++){
		ans->push_back(Pair (rootProcIndex, *i));
		recursiveCall(rootProcIndex, *i, ans);
	}
}

void QueryEvaluator::recursiveCallBoolean(int rootProcIndex, int currentIndex, int targetIndex, vector<Pair> * ans){
	Calls *c = pkb->getCalls();
	ProcTable *p = pkb->getProcTable();
	vector<int> called = c->getCalled(p->getProcName(currentIndex));

	for(vector<int>::iterator i=called.begin(); i!=called.end(); i++){
		if(currentIndex==targetIndex){
			ans->push_back(Pair (-1,-1));
			break;
		}
		recursiveCallBoolean(rootProcIndex, *i, targetIndex, ans);
	}
}

void QueryEvaluator::recursiveInverseCall(int leafIndex, int currentIndex, vector<Pair> * ans){
	Calls *c = pkb->getCalls();
	ProcTable *p = pkb->getProcTable();
	vector<int> calls = c->getCalls(p->getProcName(currentIndex));

	for(vector<int>::iterator i=calls.begin(); i!=calls.end(); i++){
		ans->push_back(Pair (*i, leafIndex));
		recursiveInverseCall(leafIndex, *i, ans);
	}
}

void QueryEvaluator::evaluateCallsStar(Relationship r, int relIndex){
	string tk1 = r.getToken1();
	string tk2 = r.getToken2();
	Calls *c = pkb->getCalls();
	ProcTable *p = pkb->getProcTable();

	vector<Pair> callsStarAns;

	//Calls*(a,b) 
	if(isalpha(tk1[0]) && isalpha(tk2[0])){
		vector<int> allProc = p->getAllProcIndexes();

		for(vector<int>::iterator it = allProc.begin(); it!=allProc.end(); it++){
			recursiveCall(*it, *it, &callsStarAns);
		}
	}

	//Calls*(a,_)
	else if(isalpha(tk1[0]) && tk2=="_"){
			vector<int> allProc = p->getAllProcIndexes();

			for(vector<int>::iterator it=allProc.begin(); it!=allProc.end(); it++){
				if(!c->getCalled(p->getProcName(*it)).empty()){
					callsStarAns.push_back(Pair (*it, -1));
				}
			}
	}

	//Calls*(a, "second")
	else if(isalpha(tk1[0])) {
		int index = p->getProcIndex(tk2.substr(1,tk2.length()-2));

		recursiveInverseCall(index, index, &callsStarAns);

	}

	//Calls*(_,b)
	else if(isalpha(tk2[0]) && tk1=="_"){

		vector<int> allProc = p->getAllProcIndexes();

		for(vector<int>::iterator it = allProc.begin(); it!=allProc.end(); it++){
			if(!c->getCalls(p->getProcName(*it)).empty()){
				callsStarAns.push_back(Pair(-1, *it));
			}
		}

	}

	//Calls*("first", b)
	else if(isalpha(tk2[0])){
		int index = p->getProcIndex(tk1.substr(1, tk1.length()-2));

		recursiveCall(index, index, &callsStarAns);
	}

	//Calls*("first", "second")
	else {
		int index1 = p->getProcIndex(tk1.substr(1, tk1.length()-2));
		int index2 = p->getProcIndex(tk2.substr(1, tk1.length()-2));

		recursiveCallBoolean(index1, index1, index2, &callsStarAns);

		if(callsStarAns.empty()){
			callsStarAns.push_back(Pair (-2, -2));
		}
	}

	//If both a and b exist in QueryEvaluator::linkages
	intersectPairs(tk1,tk2,&callsStarAns,relIndex);

	QueryEvaluator::relAns.insert(make_pair(relIndex, callsStarAns));

}

void QueryEvaluator::evaluateFollows(Relationship r, unordered_map<string, TypeTable::SynType> m, int relIndex){
	string tk1 = r.getToken1();
	string tk2 = r.getToken2();
	Follows *f = pkb->getFollows();
	unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(tk1);
	unordered_map<string, TypeTable::SynType>::iterator i2 = m.find(tk2);

	vector<Pair> followsAns;

	//Follows(a,b)
	if((isalpha(tk1[0]) && isalpha(tk2[0]))){

		//If both tokens are already previously evaluated
		if(isExistInLinkages(tk1) && isExistInLinkages(tk2)){
			//get the set of answers that are previously evaluated by other relations
			set<int> sa = retrieveTokenEvaluatedAnswers(tk1);
			set<int> sb = retrieveTokenEvaluatedAnswers(tk2);
			
			for(set<int>::iterator x=sb.begin(); x!=sb.end(); x++){
				cout<<*x<<endl;
			}
			//try all combinations in set A and set B
			for(set<int>::iterator it = sa.begin(); it!=sa.end(); it++){
				for(set<int>::iterator it2 = sb.begin(); it2!=sb.end(); it2++){
					if(f->isFollows(*it, *it2)){
						followsAns.push_back(Pair (*it, *it2));
					}
				}			
			}

			//From the new followsAns, delete all Pairs that are eliminated from other relations
			removePairs(followsAns,tk1,1);
			removePairs(followsAns,tk2,2);

		}

		//If only a exists
		else if(isExistInLinkages(tk1)){

			//get the set of answers that are previously evaluated by other relations
			set<int> sa = retrieveTokenEvaluatedAnswers(tk1);

			for(set<int>::iterator it=sa.begin(); it!=sa.end(); it++){
				int follows = f->getFollows(i2->second, *it);
				if(follows!=-1){
					followsAns.push_back(Pair (*it, follows));
				}
			}

			//Delete the redundant pairs
			removePairs(followsAns,tk1,1);
		}


		//If only b exists
		else if(isExistInLinkages(tk2)){
			
			//get the set of answers that are previously evaluated by other relations
			set<int> sb = retrieveTokenEvaluatedAnswers(tk2);
			cout<<sb.empty()<<endl;				
			for(set<int>::iterator it = sb.begin(); it!=sb.end(); it++){

			}

			for(set<int>::iterator it=sb.begin(); it!=sb.end(); it++){
				int followedBy = f->getFollowedBy(i1->second, *it);
				if(followedBy!=-1){
					followsAns.push_back(Pair (followedBy, *it));
				}
			}
			//Delete the redundant pairs
			removePairs(followsAns,tk2,2);

		}

		//If both do not exist
		else {

			//Retrieve both a and b from PKB
			vector<int> first = f->getFollowedBy(i1->second, i2->second);
			vector<int> second = f->getFollows(i1->second, i2->second);

			for(int i=0; i<first.size(); i++){
				followsAns.push_back(Pair (first.at(i), second.at(i)));
			}

		}
		
		//Add the relationship into QueryEvaluator::linkages
		insertLinks(tk1, relIndex);
		insertLinks(tk2, relIndex);

	}

	//Follows(_,_) if both tokens are wildcards just evaluate true or false
	else if(tk1=="_" && tk2=="_"){
		vector<int> ans = f->getFollows(TypeTable::STMT, TypeTable::STMT);
		if(!ans.empty()){
			followsAns.push_back(Pair (-1,-1));
		}else {
			followsAns.push_back(Pair (-2,-2));
		}
	}

	//Follows(a,1)
	else if(isalpha(tk1[0])){
		if(isExistInLinkages(tk1)){
			//get the set of answers that are previously evaluated by other relations
			set<int> sa = retrieveTokenEvaluatedAnswers(tk1);

			if(isdigit(tk2[0])){
				for(set<int>::iterator it=sa.begin(); it!=sa.end(); it++){
					if(f->isFollows(*it, atoi(tk2.c_str()))){
						followsAns.push_back(Pair (*it, atoi(tk2.c_str())));
					}
				}
			} 
			//Follows(a, _)
			else {
				for(set<int>::iterator it=sa.begin(); it!=sa.end(); it++){
					if(f->getFollows(TypeTable::STMT, *it)!=-1){
						followsAns.push_back(Pair (*it, f->getFollows(TypeTable::STMT, *it)));
					}
				}
			}

			//Delete the redundant pairs
			removePairs(followsAns,tk1,1);

		}
		
		//If it does not exist
		else {

			//Retrieve a from PKB and push it into the answer vector
			if(isdigit(tk2[0])){
				int first = f->getFollowedBy(i1->second, atoi(tk2.c_str()));
				followsAns.push_back(Pair (first, atoi(tk2.c_str())));
			}

			//Follows(a, _)
			else {
				vector<int> a = f->getFollowedBy(i1->second, TypeTable::STMT);
				cout<<a.at(0)<<endl;
				for(vector<int>::iterator it = a.begin(); it!=a.end(); it++){
					followsAns.push_back(Pair (*it, f->getFollows(TypeTable::STMT,*it)));
				}
			}
		}

		insertLinks(tk1, relIndex);
	}

	//Follows(1,b)
	else if(isalpha(tk2[0])){
		if(isExistInLinkages(tk2)){
			
			//get the set of answers that are previously evaluated by other relations
			set<int> sa = retrieveTokenEvaluatedAnswers(tk2);

			if(isdigit(tk2[0])){
				for(set<int>::iterator it=sa.begin(); it!=sa.end(); it++){
					if(f->isFollows(atoi(tk1.c_str()), *it)){
						followsAns.push_back(Pair (atoi(tk1.c_str()), *it));
					}
				}
			}

			//Follows(_,b)
			else {
				for(set<int>::iterator it=sa.begin(); it!=sa.end(); it++){
					if(f->getFollowedBy(TypeTable::STMT, *it)!=-1){
						followsAns.push_back(Pair (f->getFollowedBy(TypeTable::STMT, *it),*it));
					}
				}
			}
			//Delete the redundant pairs
			removePairs(followsAns,tk2,2);
			
		}
		
		//If it does not exist
		else {
			//Retrieve a from PKB and push it into the answer vector

			if(isdigit(tk1[0])){
				int second = f->getFollows(i2->second, atoi(tk1.c_str()));

				followsAns.push_back(Pair (atoi(tk1.c_str()), second));
			}

			//Follows(_,b)
			else {
				vector<int> a = f->getFollows(TypeTable::STMT, i2->second);
				for(vector<int>::iterator it = a.begin(); it!=a.end(); it++){
					followsAns.push_back(Pair (f->getFollowedBy(TypeTable::STMT,*it), *it));
				}
			}

		}

		insertLinks(tk2, relIndex);
	}

	//Follows(1,2)
	else {
		//if Follows(1,2) is verified as false, clear all answers
		if(isdigit(tk1[0]) && isdigit(tk2[0])){
			if(!f->isFollows(atoi(tk1.c_str()), atoi(tk2.c_str()))){
				followsAns.push_back(Pair (-2,-2));
			}
			else{
				followsAns.push_back(Pair (-1,-1));
			}
		}

		//Follows(1, _)
		else if(isdigit(tk1[0])){
			if(f->getFollows(TypeTable::STMT, atoi(tk1.c_str()))==-1){
				followsAns.push_back(Pair (-2,-2));
			}
			else{
				followsAns.push_back(Pair (-1,-1));
			}
		}

		//Follows(_, 2)
		else {
			if(f->getFollows(TypeTable::STMT, atoi(tk2.c_str()))==-1){
				followsAns.push_back(Pair (-2,-2));
			}
			else{
				followsAns.push_back(Pair (-1,-1));
			}
		}
	}

	QueryEvaluator::relAns.insert(make_pair(relIndex, followsAns));
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
						followsStarAnsSet.insert(Pair (*it, stmtNumber));
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
					followsStarAnsSet.insert(Pair (stmtNumber, atoi(tk2.c_str())));
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
					followsStarAnsSet.insert(Pair (atoi(tk1.c_str()), stmtNumber));
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
				followsStarAnsSet.insert(Pair (-1,-1));
			if(stmtNumber>atoi(tk2.c_str()))
				followsStarAnsSet.insert(Pair (-2,-2));
				break;
		}
	}
	
	//copy set into vector
	//copy(followsStarAnsSet.begin(), followsStarAnsSet.end(),followsStarAns);
	for(set<Pair>::iterator it=followsStarAnsSet.begin(); it!=followsStarAnsSet.end(); it++){
		followsStarAns.push_back(*it);
	}

	
	intersectPairs(tk1,tk2,&followsStarAns,relIndex);

	QueryEvaluator::relAns.insert(make_pair(relIndex, followsStarAns));
	
}

void QueryEvaluator::insertLinks(string tk, int relIndex){
	//Add the relationship into QueryEvaluator::linkages

	//if tk exists
	if(linkages.find(tk) != linkages.end()){
		vector<int> *pt = &QueryEvaluator::linkages.find(tk)->second;
		pt->push_back(relIndex);
	}
	else {
		vector<int> relIndexes;
		relIndexes.push_back(relIndex);
		linkages.insert(make_pair(tk, relIndexes));
	}
}

void QueryEvaluator::removePairsFromRelAns(vector<Pair> * relationsAns, string tk, int pairIndex){
	cout<<"removePairsfrom RELANS"<<endl;
	//Retrieve the set of int of the token that was evaluated
	set<int> s = retrieveTokenEvaluatedAnswers(tk);
	//Delete it from the ans pairs made
	/*
	for(vector<Pair>::iterator it = relationsAns->begin(); it!=relationsAns->end(); it++){
		cout<<it->ans2<<endl;
	}*/

	for(vector<Pair>::iterator it = relationsAns->begin(); it!=relationsAns->end();){
		cout<<"in for loop"<<endl;
		if(pairIndex==1){
			cout<<"pair index is 1"<< it->ans1<<endl;
			//if ans from relationsAns is not found in the set, remove it
			if(s.find(it->ans1)==s.end()){
				it = relationsAns->erase(it);
			}
			else{
				++it;
			}
		}
		else {
			cout<<"in else"<<endl;
			if(s.find(it->ans2)==s.end()){
				it = relationsAns->erase(it);
			}
			else{
				++it;
			}
		}
	}

	cout<<"end of RemovePairsFromRelAns"<<endl;
}

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
	if((isalpha(tk1[0]) && isalpha(tk2[0])) || (tk1=="_" && isalpha(tk2[0]))|| (tk2=="_" && isalpha(tk1[0])) ){

		answer = t->getAllStmts(i1->second);

		//Parent(_, b)
		if(tk1=="_"){
			answer = t->getAllStmts(TypeTable::STMT);
		}
		
		for(vector<int>::iterator it=answer.begin(); it!=answer.end(); it++){
			
			vector<int> children;
			if(tk2=="_"){
				children = p->getChildren(TypeTable::STMT, *it);
			}else{
				children = p->getChildren(i2->second, *it);
			}
			for(vector<int>::iterator it2=children.begin(); it2!=children.end(); it2++){
				parentAns.push_back(Pair(*it, *it2));
				cout<<"it" << *it << "it2"<<*it2<<endl;
			}
		}
	}
	//Parent(a,3)
	else if(isalpha(tk1[0]) || tk1=="_"){

		cout<<"Calling getParent(TYPE, STMTNUM)"<<endl;
		int parent;
		//Parent(_,3)
		if(tk1=="_"){
			parent = p->getParent(TypeTable::STMT, atoi(tk2.c_str()));
			if(parent!=-1){
				parentAns.push_back(Pair(-1,-1));
			}
			else {
				parentAns.push_back(Pair(-2,-2));
			}
		}
		else {
			parent = p->getParent(i1->second, atoi(tk2.c_str()));
			if(parent!=-1){
				parentAns.push_back(Pair(parent, atoi(tk2.c_str())));
			}
		}
	}

	//Parent(3,a)
	else if(isalpha(tk2[0]) || tk2=="_"){
		cout<<"Parent(STMTNUM, TYPE)"<<endl;
		if(tk2!="_"){
			vector<int> children = p->getChildren(i2->second, atoi(tk1.c_str()));
			for(vector<int>::iterator it=children.begin(); it!=children.end(); it++){
				parentAns.push_back(Pair(atoi(tk1.c_str()), *it));
				cout<<"in for loop"<<endl;
			}
		} else {
			vector<int> children = p->getChildren(TypeTable::STMT, atoi(tk1.c_str()));
			if(!children.empty()){
				parentAns.push_back(Pair(-1,-1));
			}else {
				parentAns.push_back(Pair(-2,-2));
			}
		}
	}

	//Parent(_,_)
	else if(tk1=="_" && tk2 == "_"){
		vector<int> ans = p->getParent(TypeTable::STMT, TypeTable::STMT);
		if(!ans.empty()){
			parentAns.push_back(Pair(-1,-1));
		}else {
			parentAns.push_back(Pair(-2,-2));
		}
	}

	//Parent(1,5)
	else{
		 if(p->isParent(atoi(tk1.c_str()), atoi(tk2.c_str()))){
			 cout<<"istrue"<<endl;
			 parentAns.push_back(Pair (-1,-1));
		 }else{
			 cout<<"isfalse"<<atoi(tk1.c_str())<<atoi(tk2.c_str())<<endl;
			 parentAns.push_back(Pair (-2,-2));
		 }
	}
	

	cout<<"before intersect pairs"<<endl;
	intersectPairs(tk1,tk2,&parentAns,relIndex);
	cout<<"after intersect pairs"<<endl;
	QueryEvaluator::relAns.insert(make_pair(relIndex, parentAns));
}

/*
void QueryEvaluator::recursiveParent(int rootIndex, int currentIndex){
	vector<int> 

}*/


//PARENTSTAR
void QueryEvaluator::evaluateParentStar(Relationship r, unordered_map<string, TypeTable::SynType> m, int relIndex){
	string tk1=r.getToken1();
	string tk2=r.getToken2();
	Parent *p = pkb->getParent();
	TypeTable *t = pkb->getTypeTable();
	vector<Pair> answer;
	set<Pair> parentStarAnsSet;
	int stmtNumber = 0;
	unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(tk1);
	unordered_map<string, TypeTable::SynType>::iterator i2 = m.find(tk2);

	//Parent*(w, a)
	if((isalpha(tk1[0]) && isalpha(tk2[0]))|| (isalpha(tk1[0])&& tk2=="_") || (tk1=="_" && isalpha(tk2[0]))){
		set<int> sa = retrieveTokenEvaluatedAnswers(tk1);
		set<int> sb = retrieveTokenEvaluatedAnswers(tk2);

		int stmt;

		if(!isExistInLinkages(tk2)){
			vector<int> vb;
			if(tk2=="_"){
				vb = t->getAllStmts(TypeTable::STMT);
			}else{
				vb = t->getAllStmts(i2->second);
			}
			sb.clear();
			copy(vb.begin(), vb.end(), inserter(sb, sb.begin()));
		}

		for(set<int>::iterator it = sb.begin(); it!=sb.end(); it++){
			stmt = p->getParent(*it);
			while(stmt!=-1){
				if(isExistInLinkages(tk1)){
					if(t->getType(stmt) == i1->second && sa.find(stmt)!=sa.end()){
						parentStarAnsSet.insert(Pair (stmt, *it));
					}
				}
				else{
					if(tk1=="_"){
						parentStarAnsSet.insert(Pair (stmt, *it));
					}else{
						if(t->getType(stmt) == i1->second){
							parentStarAnsSet.insert(Pair (stmt, *it));
						}
					}
				}
				stmt = p->getParent(stmt);
			}
		}

		if(isExistInLinkages(tk1)){
			insertLinks(tk1, relIndex);
		}

		if(isExistInLinkages(tk2)){
			insertLinks(tk2, relIndex);
		}
	}


	//Parent*(w, 4)
	else if(isalpha(tk1[0])){
		int tk2Int = atoi(tk2.c_str());
		set<int> sa;
		int stmt;

		if(isExistInLinkages(tk1)){
			sa = retrieveTokenEvaluatedAnswers(tk1);
			insertLinks(tk1, relIndex);
		}else {
			vector<int> va = t->getAllStmts(i1->second);
			copy(va.begin(), va.end(), inserter(sa, sa.begin()));
		}
		
		stmt = p->getParent(tk2Int);
		while(stmt!=-1){
			if(sa.find(stmt)!=sa.end()){
				parentStarAnsSet.insert(Pair (stmt, tk2Int));
			}
		stmt = p->getParent(stmt);
		}
	}

	//Parent*(3, a)
	else if(isalpha(tk2[0])){
		int tk1Int = atoi(tk1.c_str());
		set<int> sb;
		int stmt;

		if(isExistInLinkages(tk2)){
			sb = retrieveTokenEvaluatedAnswers(tk2);
			insertLinks(tk2, relIndex);
		}else {
			vector<int> va = t->getAllStmts(i2->second);
			copy(va.begin(), va.end(), inserter(sb, sb.begin()));
		}
		
		for(set<int>::iterator it = sb.begin(); it!=sb.end(); it++){
		stmt = p->getParent(*it);
			while(stmt!=-1){
				if(stmt == tk1Int){
					parentStarAnsSet.insert(Pair (tk1Int, *it));
					break;
				}
			stmt = p->getParent(stmt);
			}
		}
	}

	else if(tk1=="_" && tk2=="_"){
		vector<int> dummy = p->getParent(TypeTable::STMT, TypeTable::STMT);
		if(dummy.empty()){
			parentStarAnsSet.insert(Pair(-2,-2));
		}else {
			parentStarAnsSet.insert(Pair(-1,-1));
		}
	}

	//Parent*(3,4)
	else {

		//Parent*(3, _)
		if(tk2=="_"){
			if(p->getChildren(atoi(tk1.c_str())).empty()){
				answer.push_back(Pair(-2,-2));
			}else{
				answer.push_back(Pair(-1,-1));
			}
			relAns.insert(make_pair<int, vector<Pair>>(relIndex, answer));
			return;
		}

		//Parent*(_,3)
		if(tk1=="_"){
			if(p->getParent(atoi(tk2.c_str()))==-1){
				answer.push_back(Pair(-2,-2));
			}else{
				answer.push_back(Pair(-1,-1));
			}
			relAns.insert(make_pair<int, vector<Pair>>(relIndex, answer));
			return;
		}

		int tk1Int = atoi(tk1.c_str());
		int tk2Int = atoi(tk2.c_str());

		int stmt = p->getParent(tk2Int);
		while(stmt!=-1){
			if(stmt == tk1Int){
				answer.push_back(Pair(-1,-1));
				relAns.insert(make_pair<int, vector<Pair>>(relIndex, answer));
				return;
			}

			stmt = p->getParent(stmt);
		}

		parentStarAnsSet.insert(Pair(-2,-2));

	}

	copy(parentStarAnsSet.begin(), parentStarAnsSet.end(), back_inserter(answer));
	relAns.insert(make_pair<int, vector<Pair>>(relIndex, answer));
	/*
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

	copy(answer.begin(), answer.end(), back_inserter(vectorAnswer));*/
}

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

	//Modifies(a,v) Modifies(_,v) Modifies(a,_)
	if((isalpha(tk1[0]) && isalpha(tk2[0])) || (tk1=="_" && isalpha(tk2[0])) || (isalpha(tk1[0])&& tk2=="_")){

		//If first token is of procedure type
		//Modifies(p, v)
		if(i1->second==TypeTable::PROCEDURE || tk1=="_"){

			selected = proc->getAllProcIndexes();

			//iterate through all procedures
			for(vector<int>::iterator it=selected.begin(); it!=selected.end(); it++){
				answer = mod->getModifiesProc(*it);
				for(vector<int>::iterator it2=answer.begin(); it2!=answer.end(); it2++){
					modAns.push_back(Pair (*it, *it2));
				}
			}
		} 
		

		//Otherwise
		else {
			selected = t->getAllStmts(i1->second);
			for(vector<int>::iterator it=selected.begin(); it!=selected.end(); it++){
				answer = mod->getModifies(*it);
				for(vector<int>::iterator it2=answer.begin(); it2!=answer.end(); it2++){
					modAns.push_back(Pair (*it, *it2));
				}
			}
		}
	}

	//Modifies(a, "x")
	else if(isalpha(tk1[0])){
		string varName = tk2.substr(1,tk2.length()-2);

		//If first token is of type procedure
		//Modifies(p, "x")
		if(i1->second==TypeTable::PROCEDURE){
			cout<<"In Modifies(p, \"var\")"<<endl;
			answer = mod->getModifiesProcVar(varName);
			for(vector<int>::iterator it=answer.begin(); it!=answer.end(); it++){
				modAns.push_back(Pair (*it, varTab->getVarIndex(varName)));
			}
		}

		//otherwise
		else {
			cout<<"hihihihi"<<endl;
			answer = mod->getModifies(i1->second,varName);
			cout<<"answer is empty: "<<answer.empty()<<endl;
			for(vector<int>::iterator it=answer.begin(); it!=answer.end(); it++){
				cout<<"modifiesAnswer"<<*it<<" "<<varTab->getVarIndex(varName)<<endl;
				modAns.push_back(Pair (*it, varTab->getVarIndex(varName)));
				
			}
		}

	}

	//Select v such that Modifies(1, v);
	else if(isalpha(tk2[0])){
		if(isdigit(tk1[0])){
			selected = mod->getModifies(atoi(tk1.c_str()));
			for(vector<int>::iterator it=selected.begin(); it!=selected.end(); it++){
				modAns.push_back(Pair (atoi(tk1.c_str()), *it));
			}
		}

		//Modifies("First", v)
		else {
			int procIndex = proc->getProcIndex(tk1.substr(1,tk1.length()-2));
			vector<int> vars = mod->getModifiesProc(procIndex);

			for(vector<int>::iterator it = vars.begin(); it!=vars.end(); it++){
				modAns.push_back(Pair(procIndex, *it));
			}
		}
	}

	//Modifies("Third", "x")
	else if(tk1[0]=='\"'){
		if(tk2!="_"){
			cout<<"Modifies(\"Procname\", \"VarName\")"<<endl;
			string procName = tk1.substr(1,tk1.length()-2);
			string varName = tk2.substr(1,tk2.length()-2);
			if(mod->isModifiesProc(procName, varName)){
				modAns.push_back(Pair (-1,-1));
			}else {
				modAns.push_back(Pair (-2,-2));
			}
		} 
		
		//Modifies("Third", _)
		else {
			int index = proc->getProcIndex(tk1.substr(1, tk1.length()-2));
			vector<int> allVariablesModifiedByProc = mod->getModifiesProc(index);
			if(allVariablesModifiedByProc.empty()){
				modAns.push_back(Pair(-2,-2));
			}

			else {
				modAns.push_back(Pair(-1,-1));
			}
		}
	}

	//Modifies(_,_)
	else if(tk1=="_" && tk2=="_"){
		cout<<"Modifies(_,_)"<<endl;
		vector<int> allProcIndexes = proc->getAllProcIndexes();
		bool flag = false;
		for(vector<int>::iterator it = allProcIndexes.begin(); it!=allProcIndexes.end(); it++){
			if(!mod->getModifiesProc(*it).empty()){
				cout<<"flag is true"<<endl;
				flag = true;
				break;
			}
		}

		if(flag){
			modAns.push_back(Pair (-1,-1));
		}else{
			modAns.push_back(Pair (-2,-2));
		}
	}

	//Modifies(1, "x")
	else {

		//Modifies(_, "x")
		if(tk1=="_"){
			if(!mod->getModifiesProcVar(tk2.substr(1, tk2.length()-2)).empty()){
				modAns.push_back(Pair (-1,-1));
			}
			else {
				modAns.push_back(Pair (-2, -2));
			}
		}

		else {
		cout<<"supposed"<<endl;
		string varName = tk2.substr(1,tk2.length()-2);
		cout<<atoi(tk1.c_str())<<varName<<endl;
		mod->setModifies(1, "y");
		if(mod->isModifies(atoi(tk1.c_str()), varName)){
			cout<<"supposed2"<<endl;
			 modAns.push_back(Pair (-1,-1));
		 }else{
			 modAns.push_back(Pair (-2,-2));
		 }
		}
	}

	intersectPairs(tk1, tk2, &modAns, relIndex);

	QueryEvaluator::relAns.insert(make_pair(relIndex, modAns));
}

void QueryEvaluator::intersectPairs(string tk1, string tk2, vector<Pair> *ans, int relIndex){
		//If both a and b exist in QueryEvaluator::linkages
	if(isExistInLinkages(tk1) && isExistInLinkages(tk2)){
		removePairsFromRelAns(ans, tk1, 1);
		removePairsFromRelAns(ans, tk2, 2);
		removePairs(*ans, tk1, 1);
		removePairs(*ans, tk2, 2);
	}

	//If only a exist
	else if(isExistInLinkages(tk1)){
		cout<<"intersectPairs tk1Exists"<<endl;
		removePairsFromRelAns(ans, tk1, 1);
		removePairs(*ans, tk1, 1);
		//insertLinks(tk1, relIndex);
	}

	//If only b exist
	else if(isExistInLinkages(tk2)){
		removePairsFromRelAns(ans, tk2, 2);
		removePairs(*ans, tk2, 2);
	}

	else {
		cout<<"In intersect Pairs: both does not exist"<<endl;
	}

	
	if(isalpha(tk1[0])){
		cout<<"insert links for tk1 =" <<tk1<<endl;
		insertLinks(tk1, relIndex);
	}
	
	if(isalpha(tk2[0])){
	
		insertLinks(tk2, relIndex);
	}
}

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
	if((isalpha(tk1[0]) && isalpha(tk2[0])) || (tk1=="_" && isalpha(tk2[0])) || (isalpha(tk1[0])&& tk2=="_")){

		//If first token is of procedure type
		if(i1->second==TypeTable::PROCEDURE || tk1=="_"){

			selected = proc->getAllProcIndexes();

			//iterate through all procedures
			for(vector<int>::iterator it=selected.begin(); it!=selected.end(); it++){
				answer = use->getUsesProc(*it);
				for(vector<int>::iterator it2=answer.begin(); it2!=answer.end(); it2++){
					usesAns.push_back(Pair (*it, *it2));
				}
			}
		} 
		

		//Otherwise
		else {
			selected = t->getAllStmts(i1->second);
			for(vector<int>::iterator it=selected.begin(); it!=selected.end(); it++){
				answer = use->getUses(*it);
				for(vector<int>::iterator it2=answer.begin(); it2!=answer.end(); it2++){
					usesAns.push_back(Pair (*it, *it2));
				}
			}
		}
	}

	//Select a Uses(a, "x")
	else if(isalpha(tk1[0])){
		string varName = tk2.substr(1,tk2.length()-2);

		//If first token is of type procedure
		if(i1->second==TypeTable::PROCEDURE){

			answer = use->getUsesProcVar(varName);
			for(vector<int>::iterator it=answer.begin(); it!=answer.end(); it++){
				usesAns.push_back(Pair (*it, varTab->getVarIndex(varName)));
			}
		}

		//otherwise
		else {
			answer = use->getUses(i1->second,varName);
			for(vector<int>::iterator it=answer.begin(); it!=answer.end(); it++){
				usesAns.push_back(Pair (*it, varTab->getVarIndex(varName)));
			}
		}

	}


	//Select v such that Uses(1, v);
	else if(isalpha(tk2[0])){

		if(isdigit(tk1[0])){
			selected = use->getUses(atoi(tk1.c_str()));
			for(vector<int>::iterator it=selected.begin(); it!=selected.end(); it++){
				usesAns.push_back(Pair (atoi(tk1.c_str()), *it));
			}
		}

		//Uses("First", v)
		else {
			int procIndex = proc->getProcIndex(tk1.substr(1,tk1.length()-2));
			vector<int> vars = use->getUsesProc(procIndex);

			for(vector<int>::iterator it = vars.begin(); it!=vars.end(); it++){
				usesAns.push_back(Pair(procIndex, *it));
			}
		}
	}

	//Uses("Third", "x")
	else if(tk1[0]=='\"'){
		if(tk2!="_"){
			string procName = tk1.substr(1,tk1.length()-2);
			string varName = tk2.substr(1,tk2.length()-2);
			if(use->isUsesProc(procName, varName)){
				usesAns.push_back(Pair (-1,-1));
			}else {
				usesAns.push_back(Pair (-2,-2));
			}
		}

		//Uses("Third", _)
		else {
			int index = proc->getProcIndex(tk1.substr(1, tk1.length()-2));
			vector<int> allVariablesUsedByProc = use->getUsesProc(index);
			if(allVariablesUsedByProc.empty()){
				usesAns.push_back(Pair(-2,-2));
			}

			else {
				usesAns.push_back(Pair(-1,-1));
			}
		}
	}

	//Uses(_,_)
	else if(tk1=="_" && tk2=="_"){
		cout<<"Uses(_,_)"<<endl;
		vector<int> allProcIndexes = proc->getAllProcIndexes();
		bool flag = false;
		for(vector<int>::iterator it = allProcIndexes.begin(); it!=allProcIndexes.end(); it++){
			if(!use->getUsesProc(*it).empty()){
				cout<<"flag is true"<<endl;
				flag = true;
				break;
			}
		}

		if(flag){
			usesAns.push_back(Pair (-1,-1));
		}else{
			usesAns.push_back(Pair (-2,-2));
		}
	}

	//Uses(1, "x")
	else {

		//Uses(_, "x")
		if(tk1=="_"){
			if(!use->getUsesProcVar(tk2.substr(1, tk2.length()-2)).empty()){
				usesAns.push_back(Pair (-1,-1));
			}
			else {
				usesAns.push_back(Pair (-2, -2));
			}
		}

		else{
			string varName = tk2.substr(1,tk2.length()-2);
			if(use->isUses(atoi(tk1.c_str()), varName)){
				 usesAns.push_back(Pair (-1,-1));
			 }else{
				 usesAns.push_back(Pair (-2,-2));
			 }
		}
	}

	intersectPairs(tk1,tk2,&usesAns,relIndex);

	QueryEvaluator::relAns.insert(make_pair(relIndex, usesAns));
}

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