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
	int sorted = 0;
	Relationship temp;
	//Relationship with;
	//bool flag = false;
	cout<<"In orderRelationships"<<endl;

	for(unsigned int i=0; i<r.size(); i++){
		if((r.at(i).getRelType()==Relationship::PATTERN || !isalpha(r.at(i).getToken1()[0]) || !isalpha(r.at(i).getToken2()[0])) && r.at(i).getRelType()!=Relationship::WITH){
			cout<<"pattern or relationships with only one alpha token found"<<endl;
			temp = r.at(sorted);
			r.at(sorted) = r.at(i);
			r.at(i) = temp;
			sorted++;
		} else if(r.at(i).getRelType() == Relationship::WITH){
			cout<<"with relationship found"<<endl;
			/*
			with = r.at(i);
			flag = true;
			r.erase(r.begin()+i);
			*/
			temp = r.at(r.size()-1);
			r.at(r.size()-1) = r.at(i);
			r.at(i) = temp;
		}
	}
	/*
	if(flag){
		r.push_back(with);
	}*/

	cout<<"After Ordering Relations, r.size = "<<r.size()<<endl;
	return r;
}

unordered_map<string, vector<int>> QueryEvaluator::evaluateQuery(Query q){

	//Get relationships and order them
	vector<Relationship> relations = q.getRelVect();
	linkages.clear();
	relAns.clear();
	relParameters.clear();


	cout<<"Ordering Relationships"<<endl;
	relations = orderRelationship(relations);

	cout<<"Initializing Variables"<<endl;
	unordered_map<string, TypeTable::SynType> m = q.getSynTable();
	vector<string> selectedSyn = q.getSelectedSyn();
	unordered_map<string, vector<int>> answers;

	//If relations is empty
	if(relations.empty()){
		cout<<"Relations found empty"<<endl;
		for(vector<string>::iterator it = selectedSyn.begin(); it!=selectedSyn.end(); it++){
			set<int> synAns = pkb->getAllStmts(m.find(*it)->second);
			vector<int> pairAns;
			copy(synAns.begin(), synAns.end(), back_inserter(pairAns));
			answers.insert(make_pair<string, vector<int>>(*it, pairAns));
		}

		return answers;
	}

	//If relations are not empty
	int relIndex = 0;
	for(vector<Relationship>::iterator it = relations.begin(); it!=relations.end(); it++){
		cout<<" "<<endl;
		cout<<it->getRelName()<<"("<<it->getToken1()<<", "<< it->getToken2()<<")"<<endl;
		switch(it->getRelType()){
		case Relationship::FOLLOWS:
			cout<<"\n EVALUATING FOLLOWS ("<<it->getToken1()<<" "<<it->getToken2()<<")"<<endl;
			evaluateFollows(*it, m,relIndex); break;

		case Relationship::FOLLOWSSTAR:
			cout<<"\n EVALUATING FOLLOWS* ("<<it->getToken1()<<" "<<it->getToken2()<<")"<<endl;
			evaluateFollowsStar(*it, m, relIndex); break;

		case Relationship::PARENT:
			cout<<"\n EVALUATING PARENT ("<<it->getToken1()<<" "<<it->getToken2()<<")"<<endl;
			evaluateParent(*it, m, relIndex); break;

		case Relationship::PARENTSTAR:
			cout<<"\n EVALUATING PARENT* ("<<it->getToken1()<<" "<<it->getToken2()<<")"<<endl;
			evaluateParentStar(*it, m, relIndex); break;//review

		case Relationship::CALLS:
			cout<<"\n EVALUATING CALLS ("<<it->getToken1()<<" "<<it->getToken2()<<")"<<endl;
			evaluateCalls(*it, relIndex); break;

		case Relationship::CALLSSTAR:
			cout<<"\n EVALUATING CALLS* ("<<it->getToken1()<<" "<<it->getToken2()<<")"<<endl;
			evaluateCallsStar(*it, relIndex); break;

		case Relationship::MODIFIES:
			cout<<"\n EVALUATING MODIFIES ("<<it->getToken1()<<" "<<it->getToken2()<<")"<<endl;
			evaluateModifies(*it, m, relIndex); break;

		case Relationship::USES:
			cout<<"\n EVALUATING USES ("<<it->getToken1()<<" "<<it->getToken2()<<")"<<endl;
			evaluateUses(*it, m, relIndex); break;

		case Relationship::NEXT:
			cout<<"\n EVALUATING NEXT ("<<it->getToken1()<<" "<<it->getToken2()<<")"<<endl;
			evaluateNext(*it, m, relIndex); break;

		case Relationship::NEXTSTAR:
			cout<<"\n EVALUATING NEXT* ("<<it->getToken1()<<" "<<it->getToken2()<<")"<<endl;
			evaluateNextStar(*it, m, relIndex); break;

		case Relationship::WITH:
			cout<<"\n EVALUATING WITH ("<<it->getToken1()<<" "<<it->getToken2()<<")"<<endl;
			evaluateWith(*it, m, relIndex); break;

		case Relationship::PATTERN:	
			cout<<"\n EVALUATING PATTERN"<<endl;
			evaluatePattern(*it, m, relIndex); break;

		case Relationship::AFFECTS:
			cout<<"\n EVALUATING AFFECTS"<<endl;
			evaluateAffects(*it, m, relIndex); break;

		case Relationship::AFFECTSSTAR:
			cout<<"\n EVALUATING AFFECTSSTAR"<<endl;
			evaluateAffectsStar(*it, m , relIndex); break;
		}

		vector<string> parametersVec;
		parametersVec.clear();
		if(it->getRelType()==Relationship::PATTERN){
			parametersVec.push_back(it->getPatternSyn());
			parametersVec.push_back(it->getPatternSyn());
		}
		else{
			parametersVec.push_back(it->getToken1());
			parametersVec.push_back(it->getToken2());
		}

		cout<<"Inserting tokens into relParameters"<<endl;
		relParameters.insert(make_pair<int, vector<string>>(relIndex, parametersVec));
		relIndex++;
	}

	//If one of the relations are evaluated to false or empty
	for(unsigned int i=0; i<relations.size(); i++){
		vector<Pair> v = relAns.find(i)->second;
		if(v.empty() || v.at(0).ans1==-2){
			cout<<"Found Relations to be False or Empty"<<endl;
			return answers;
		}
	}


	for(vector<string>::iterator it = selectedSyn.begin(); it!=selectedSyn.end(); it++){
		cout<<"Iterating Selected Syn"<<endl;

		set<int> synAns;
		vector<int> synAnsVec;
		if(linkages.find(*it)!=linkages.end()){
			int index;
			vector<string> param;
			index = (linkages.find(*it)->second).at(0);
			param = relParameters.find(index)->second;

			vector<Pair> p = relAns.at(index);
		
			cout<<"token in selectedSyn = "<<*it<<" p.size = "<<p.size()<<endl;
			cout<<"FIRST PARAM = "<<param.at(0)<<endl;
			if(*it==param.at(0)){
				for(vector<Pair>::iterator it2 = p.begin(); it2!=p.end(); it2++){
					synAns.insert(it2->ans1);
					cout<<"it2->ans1 = "<<it2->ans1<<endl;
				}

			}else {
				cout<<"SECOND PARAM = "<<param.at(1)<<endl;
				for(vector<Pair>::iterator it2 = p.begin(); it2!=p.end(); it2++){
					synAns.insert(it2->ans2);
					cout<<"it2->ans2 = "<<it2->ans2<<endl;
				}
			}

		}

		//If selectedSyn is not found in linkages or is BOOLEAN
		else{
			synAns = pkb->getAllStmts(m.find(*it)->second);
		}

		for(set<int>::iterator it3 = synAns.begin(); it3!=synAns.end(); it3++){
			synAnsVec.push_back(*it3);
		}

		answers.insert(make_pair<string, vector<int>>(*it, synAnsVec));
	}

	cout<<"RETURNING FINAL ANSWERS"<<endl;
	return answers;
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
	cout<<"In retrieveTokenEvaluatedAnswers Finding tk = "<<tk<<endl;
	vector<int> listOfRel = linkages.find(tk)->second;
	vector<Pair> ans = QueryEvaluator::relAns.find(listOfRel.at(0))->second;
	cout<<"Retrieving Token Evaluated Answers with first relationship index = "<<listOfRel.at(0)<<endl;
	string relTk1 = QueryEvaluator::relParameters.find(listOfRel.at(0))->second.at(0);
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

void QueryEvaluator::intersectPairs(string tk1, string tk2, vector<Pair> *ans, int relIndex){
		//If both a and b exist in QueryEvaluator::linkages
	if(isExistInLinkages(tk1) && isExistInLinkages(tk2)){
		cout<<"Both tk1 and tk2 Exists tk1 = "<<tk1<<" tk2 = " <<tk2<<endl;
		removePairsFromRelAns(ans, tk1, 1);
		removePairsFromRelAns(ans, tk2, 2);
		removePairs(*ans, tk1, 1);
		removePairs(*ans, tk2, 2);
	}

	//If only a exist
	else if(isExistInLinkages(tk1)){
		cout<<"IntersectPairs tk1 Exists tk1 = "<<tk1<<endl;
		removePairsFromRelAns(ans, tk1, 1);
		removePairs(*ans, tk1, 1);
		//insertLinks(tk1, relIndex);
	}

	//If only b exist
	else if(isExistInLinkages(tk2)){
		cout<<"IntersectPairs tk2 Exists tk2 = "<<tk2<<endl;
		removePairsFromRelAns(ans, tk2, 2);
		removePairs(*ans, tk2, 2);
	}

	else {
		cout<<"In intersect Pairs: both do not exist"<<endl;
	}

	
	if(isalpha(tk1[0])){
		cout<<"Insert links for tk1 =" <<tk1<<endl;
		insertLinks(tk1, relIndex);
	}
	
	if(isalpha(tk2[0])){
		cout<<"Insert links for tk2 = "<<tk2<<endl;
		insertLinks(tk2, relIndex);
	}
}

void QueryEvaluator::insertLinks(string tk, int relIndex){
	//Add the relationship into QueryEvaluator::linkages
	cout<<"IN INSERT LINKS INSERTING TOKEN = "<<tk<<endl;
	//if tk exists
	if(linkages.find(tk) != linkages.end()){
		cout<<tk<<" Found in Linkages"<<endl;
		vector<int> *pt = &QueryEvaluator::linkages.find(tk)->second;
		pt->push_back(relIndex);
	}
	else {
		cout<<tk<<" Not Found in Linkages and relIndex = "<<relIndex<<endl;
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

void QueryEvaluator::removePairs(vector<Pair> p, string token, int i){
	cout<<"\n---START REMOVE PAIRS METHOD---"<<endl;
	int pairIndex;
	vector<int> listOfRel = linkages.find(token)->second;
	vector<int> list;
	if(i==1){
		for(vector<Pair>::iterator iter=p.begin(); iter!=p.end(); iter++){
			list.push_back(iter->ans1);
			cout<<"Inserting "<<iter->ans1<<endl;
		}
	}
	else{
		for(vector<Pair>::iterator iter=p.begin(); iter!=p.end(); iter++){
			list.push_back(iter->ans2);
			cout<<"Inserting "<<iter->ans2<<endl;
		}
	}

	//iterate through all the relations that evaluated the token
	for(vector<int>::iterator it=listOfRel.begin(); it!=listOfRel.end(); it++){
		cout<<"RelIndex of clause with contents being removed: "<<*it<<endl;
		unordered_map<int, vector<Pair>>::iterator i = relAns.find(*it);
		vector<Pair> *pr = &i->second;
		int index = QueryEvaluator::relAns.find(*it)->first;

		//find out whether the token is the first or second argument of the relationship
		if(relParameters.find(index)->second.at(0)==token){
			cout<<"PairIndex: 1"<<endl;
			pairIndex=1;
		}
		else{
			cout<<"PairIndex: 2"<<endl;
			pairIndex=2;
		}

		//iterate through the relationship pairs
		for(vector<Pair>::iterator it2=pr->begin(); it2!=pr->end();){

			//remove all pairs that are eliminated
			if(pairIndex==1){
				if(find(list.begin(),list.end(),it2->ans1)==list.end()){
					cout<<"Erasing element "<<it2->ans2<<endl;
					it2 = pr->erase(it2);
				} else{
					++it2;
				}
			}else{
				if(find(list.begin(),list.end(),it2->ans2)==list.end()){
					cout<<"Erasing element "<<it2->ans2<<endl;
					it2 = pr->erase(it2);
				} else{
					++it2;
				}
			}
		}
		/*
		for(vector<Pair>::iterator ii = pr->begin(); ii!=pr->end(); ii++){
			cout<<"Left element "<<ii->ans1<<endl;
		}*/
	}
}

void QueryEvaluator::evaluateWith(Relationship r, unordered_map<string, TypeTable::SynType> m, int relIndex){
	cout<<"\n---START EVALUATE WITH METHOD---"<<endl;
	cout<<"Relationship Index: "<<relIndex<<endl;
	//Retrieve the two with syns
	string tk1 = r.getToken1();
	string tk2 = r.getToken2();

	cout<<"r.tk1: "<<tk1<<endl;
	cout<<"r.tk2: "<<tk2<<endl;
	vector<Pair> withAns;

	unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(tk1);
	unordered_map<string, TypeTable::SynType>::iterator i2 = m.find(tk2);
	

	//with v1.varName = p.procName with c.value = s.stmt# = pr.progline
	if(isalpha(tk1[0]) && isalpha(tk2[0])){
		set<int> a;
		set<int> b;
		if(isExistInLinkages(tk1)){
			a = retrieveTokenEvaluatedAnswers(tk1);
		}else {
			if(i1->second==TypeTable::PROCEDURE){
				a = pkb->getAllProcIndexes();
			}else if(i1->second == TypeTable::VARIABLE){
				a = pkb->getAllVarIndex();
			}else if(i1->second == TypeTable::CONSTANT){
				a = pkb->getAllConstIndex();
			}else {
				a = pkb->getAllStmts(i1->second);
			}
		}

		if(isExistInLinkages(tk2)){
			b = retrieveTokenEvaluatedAnswers(tk2);
		}else{
			if(i2->second==TypeTable::PROCEDURE){
				b = pkb->getAllProcIndexes();
			}else if(i2->second == TypeTable::VARIABLE){
				b = pkb->getAllVarIndex();
			}else if(i2->second == TypeTable::CONSTANT){
				b = pkb->getAllConstIndex();
			}else {
				b = pkb->getAllStmts(i2->second);
			}
		}
		//if the two tokens are of the same type
		if(i1->second == i2->second){

			set<int> intersect;
			set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::inserter(intersect, intersect.begin()));

			for(set<int>::iterator iter = intersect.begin(); iter!=intersect.end(); iter++){
				withAns.push_back(Pair (*iter, *iter));
			}

			if(isExistInLinkages(tk1)){
				removePairs(withAns, tk1, 1);
			}

			if(isExistInLinkages(tk2)){
				removePairs(withAns, tk2, 1);
			}

			if(!intersect.empty()){
				withAns.clear();
				withAns.push_back(Pair (-1,-1));
			}
		}

		else {
			if(i1->second == TypeTable::PROCEDURE || i1->second == TypeTable::VARIABLE){
				vector<string> procNames;
				vector<string> varNames;
				if(i1->second == TypeTable::PROCEDURE){
					for(set<int>::iterator it = a.begin(); it!=a.end(); it++){
						procNames.push_back(pkb->getProcName(*it));
					}
					for(set<int>::iterator it2 = b.begin(); it2!=b.end(); it2++){
						varNames.push_back(pkb->getVarName(*it2));
					}
				}else if(i1->second == TypeTable::VARIABLE){
					for(set<int>::iterator it = a.begin(); it!=a.end(); it++){
						procNames.push_back(pkb->getProcName(*it));
					}
					for(set<int>::iterator it2 = b.begin(); it2!=b.end(); it2++){
						varNames.push_back(pkb->getVarName(*it2));
					}
				}

				set<string> intersect;
				set_intersection(procNames.begin(), procNames.end(), varNames.begin(), varNames.end(), std::inserter(intersect, intersect.begin()));
				vector<Pair> ansProc;
				vector<Pair> ansVar;
				for(set<string>::iterator it = intersect.begin(); it!=intersect.end(); it++){
					if(i1->second == TypeTable::VARIABLE){
						withAns.push_back(Pair (pkb->getVarIndex(*it), pkb->getProcIndex(*it)));
					}else {
						withAns.push_back(Pair (pkb->getProcIndex(*it), pkb->getVarIndex(*it)));
					}
					/*
					ansProc.push_back(Pair (pkb->getProcIndex(*it), pkb->getProcIndex(*it)));
					ansVar.push_back(Pair (pkb->getVarIndex(*it), pkb->getVarIndex(*it)));*/
				}
				/*
				if(i1->second ==TypeTable::VARIABLE){
					removePairs(ansVar, tk1, 1);
					removePairs(ansProc, tk2, 2);
				}
				else {
					removePairs(ansProc, tk1, 1);
					removePairs(ansVar, tk2, 2);
				}*/

			}

			//if constant = progline = stmt
			

		}
		/*
		//if both exist in links then remove all unnecessary tuples. push QueryEvaluator::relAns true
		if(isExistInLinkages(tk1) && isExistInLinkages(tk2)){
			cout<<"Both tokens exist in linkages"<<endl;
			//if both tokens are of the same type e.g v1 v2
			if(i1->second == i2->second){
				set<int> tk1Set = retrieveTokenEvaluatedAnswers(tk1);
				set<int> tk2Set = retrieveTokenEvaluatedAnswers(tk2);

				set<int> intersect;
				set_intersection(tk1Set.begin(), tk1Set.end(), tk2Set.begin(), tk2Set.end(), std::inserter(intersect, intersect.begin()));

				vector<Pair> withAns;
				for(set<int>::iterator it = intersect.begin(); it!=intersect.end(); it++){
					withAns.push_back(Pair (*it, *it));
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
							ans1string.insert(pkb->getProcName(*it));
						}
					}

					else{
						for(set<int>::iterator it = ans1.begin(); it!=ans1.end(); it++){
							ans1string.insert(pkb->getVarName(*it));
						}
					}
				}
				//get list of rel that link to p
				set<int> ans2 = retrieveTokenEvaluatedAnswers(tk2);
				set<string> ans2string;
				if(i2->second==TypeTable::PROCEDURE || i2->second==TypeTable::VARIABLE){
					
					if(i2->second==TypeTable::PROCEDURE){
						for(set<int>::iterator it = ans2.begin(); it!=ans2.end(); it++){
							ans2string.insert(pkb->getProcName(*it));
						}
					}

					else{
						for(set<int>::iterator it = ans2.begin(); it!=ans2.end(); it++){
							ans2string.insert(pkb->getVarName(*it));
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
						ans3stringVar.push_back(Pair (pkb->getVarIndex(*it), pkb->getVarIndex(*it)));
						ans3stringProc.push_back(Pair (pkb->getProcIndex(*it), pkb->getProcIndex(*it)));
					}

					if(i1->second==TypeTable::VARIABLE){
						removePairs(ans3stringVar, tk1,1);
						removePairs(ans3stringProc, tk2,1);
					}
					else{
						removePairs(ans3stringProc, tk1,1);
						removePairs(ans3stringVar, tk2,1);
					}

					withAns.push_back(Pair (-1,-1));
					relAns.insert(make_pair<int, vector<Pair>>(relIndex, withAns));
				}
				else{
					std::set_intersection(ans1.begin(), ans1.end(), ans2.begin(), ans2.end(), inserter(ans3, ans3.begin()));
					vector<Pair> finalAns;

					for(set<int>::iterator it = ans3.begin(); it!=ans3.end(); it++){
						finalAns.push_back(Pair(*it, *it));
					}

					removePairs(finalAns, tk1, 1);
					removePairs(finalAns, tk2, 1);

					withAns.push_back(Pair (-1,-1));
					relAns.insert(make_pair<int, vector<Pair>>(relIndex, withAns));
				}
			}
		}

		//else if both tokens do not exist or only 1 exists
		else {
			cout<<"Only 1 exist or None exist in linkages"<<endl;
			vector<Pair> withAns;
			//if is constant = stmt or constant = prog
			if((i1->second==TypeTable::CONSTANT && i2->second==TypeTable::STMT) || (i1->second==TypeTable::STMT && i2->second==TypeTable::CONSTANT) || (i1->second==TypeTable::CONSTANT && i2->second==TypeTable::PROGLINE) || (i1->second==TypeTable::PROGLINE && i2->second==TypeTable::CONSTANT)){
				set<int> allConst = pkb->getAllConstIndex();
				int stmtRange = pkb->getStmtRange();

				for(set<int>::iterator it = allConst.begin(); it!=allConst.end(); it++){
					if(atoi((pkb->getConstValue(*it)).c_str())<=stmtRange){
						withAns.push_back(Pair(*it, *it));
					}
				}		
			}

			//if is stmt = prog
			else if((i1->second==TypeTable::STMT && i2->second==TypeTable::PROGLINE) || (i1->second==TypeTable::PROGLINE && i2->second==TypeTable::STMT)){
				int higher = pkb->getStmtRange();
				for(int i=1; i<=higher; i++){
					withAns.push_back(Pair (i, i));
				}
			}

			//if is var = proc
			else{
				set<int> retrieved;
				if(isExistInLinkages(tk1)){
					retrieved = retrieveTokenEvaluatedAnswers(tk1);
					if(i1->second == TypeTable::VARIABLE){
						
					}
				}
				else if(isExistInLinkages(tk2)){
					retrieved = retrieveTokenEvaluatedAnswers(tk2);
				}
				else {

				}

			}

			if(isExistInLinkages(tk1)){
				removePairs(withAns, tk1, 1);
			} else if(isExistInLinkages(tk2)){
				removePairs(withAns, tk2, 2);
			}else {

			}

			if(withAns.empty()){
				withAns.push_back(Pair (-2, -2));
		
			}

			relAns.insert(make_pair<int, vector<Pair>>(relIndex, withAns));
		}
		*/
	}
	//with v.varName = "x" with p.procName = "Third"
	else {
		//if exist in links then delete all unnecessary tuples then push into QueryEvaluator::relAns true
		if(!isdigit(tk2[0])){ //if the query is with c.value = 3 then we do not have to remove the quotation marks
			tk2 = tk2.substr(1,tk2.length()-2);
		}
		if(isExistInLinkages(tk1)){
			cout<<"Tk1 exist in linkages"<<endl;
			int index;
		
			if(i1->second==TypeTable::VARIABLE){
				cout<<"First token VARIABLE"<<endl;
				index = pkb->getVarIndex(tk2);
			}else if(i1->second==TypeTable::PROCEDURE){
				cout<<"First token PROCEDURE"<<endl;
				index = pkb->getProcIndex(tk2);
			} else{
				cout<<"First token NEITHER VAR NOR PROC"<<endl;
				index = atoi(tk2.c_str());
				cout<<"Index: "<<index<<endl;
			}

			//push in a dummy value for removal purposes
			withAns.push_back(Pair (index, index));
			removePairs(withAns, tk1, 2);
			relAns.insert(make_pair<int, vector<Pair>>(relIndex, withAns));
		}

		//else evaluate true or false
		else {
			if(i1->second == TypeTable::VARIABLE){
				int varI = pkb->getVarIndex(tk2);
				if(varI!=-1){
					withAns.push_back(Pair (varI, varI));
				}
			}
			else if(i1->second == TypeTable::PROCEDURE){
				int procI = pkb->getProcIndex(tk2);
				if(procI!=-1){
					withAns.push_back(Pair (procI, procI));
				}
			}

			else if(i1->second == TypeTable::CONSTANT){
				int constI = pkb->getConstIndex(tk2);
				if(constI!=-1){
					withAns.push_back(Pair (constI, constI));
				}
			}


			else if(i1->second == TypeTable::STMT || i1->second == TypeTable::PROGLINE){
				int stmtRange = pkb->getStmtRange();
				int chosenStmt = atoi(tk2.c_str());
				if(chosenStmt<=stmtRange){
					withAns.push_back(Pair (chosenStmt, chosenStmt));
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
	cout<<"---END EVALUATE WITH METHOD---\n"<<endl;
}

void QueryEvaluator::evaluateNext(Relationship r, unordered_map<string, TypeTable::SynType> m, int relIndex){
	string tk1 = r.getToken1();
	string tk2 = r.getToken2();
	unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(tk1);
	unordered_map<string, TypeTable::SynType>::iterator i2 = m.find(tk2);

	vector<Pair> nextAns;

	//if token 1 and token 2 is alpha
	//Next(s, a)
	if(isalpha(tk1[0]) && isalpha(tk2[0])){
		cout<<"Both Tokens are Alpha"<<endl;
		//If s and a exists, retrieve s and a answers, then isNext
		if(isExistInLinkages(tk1) && isExistInLinkages(tk2)){
			cout<<"Both Tokens Exist in Linkages"<<endl;
			set<int> firstSet = retrieveTokenEvaluatedAnswers(tk1);
			set<int> secondSet = retrieveTokenEvaluatedAnswers(tk2);

			for(set<int>::iterator it = firstSet.begin(); it!=firstSet.end(); it++){
				for(set<int>::iterator it2 = secondSet.begin(); it2!=secondSet.end(); it2++){
					if(pkb->isNext(*it, *it2)){ 
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
			set<int> tk2Ans;

			for(set<int>::iterator it = firstSet.begin(); it!=firstSet.end(); it++){
				tk2Ans = pkb->getNext(*it);
				for(set<int>::iterator it1 = tk2Ans.begin(); it1!=tk2Ans.end(); it1++){
					if(pkb->isSynType(i2->second, *it1)){
						nextAns.push_back(Pair (*it, *it1));
					}
				}
			}

			removePairs(nextAns, tk1, 1);
		}

		//If a exists, retrieve a, get previous check type
		if(isExistInLinkages(tk2)){
			set<int> secondSet = retrieveTokenEvaluatedAnswers(tk2);
			set<int> tk1Ans;

			for(set<int>::iterator it = secondSet.begin(); it!=secondSet.end(); it++){
				tk1Ans = pkb->getPrevious(*it);
				for(set<int>::iterator it2 = tk1Ans.begin(); it2!=tk1Ans.end(); it2++){
					if(pkb->isSynType(i1->second, *it2)){
						nextAns.push_back(Pair (*it2, *it));
					}
				}
			}

			removePairs(nextAns, tk2, 2);
		}

		//If both doesn't exist, then getNext(type, type)
		else {
			set<int> allTk1 = pkb->getAllStmts(i2->second);
			set<int> tk1Ans;
			for(set<int>::iterator it= allTk1.begin(); it!=allTk1.end(); it++){
				tk1Ans = pkb->getPrevious(*it);
				for(set<int>::iterator it2 = tk1Ans.begin(); it2!=tk1Ans.end(); it2++){
					if(pkb->isSynType(i1->second,*it2)){
						nextAns.push_back(Pair (*it2, *it));
					}
				}
			}
		}

		insertLinks(tk1, relIndex);
		insertLinks(tk2, relIndex);
	}

	//Next(n, _)
	else if(isalpha(tk1[0]) && tk2=="_"){
		if(isExistInLinkages(tk1)){
			set<int> sa = retrieveTokenEvaluatedAnswers(tk1);

			for(set<int>::iterator it = sa.begin(); it!=sa.end(); it++){
				if(!pkb->getNext(*it).empty()){
					nextAns.push_back(Pair (*it, *pkb->getNext(*it).begin()));
				}
			}

			removePairs(nextAns, tk1, 1);
		} else {
			cout<<"First Token does not Exist"<<endl;
			set<int> va = pkb->getAllStmts(i1->second);

			for(set<int>::iterator it = va.begin(); it!=va.end(); it++){
				cout<<"Before retrieving getNext it = "<<*it<<endl;
				if(!pkb->getNext(*it).empty()){
					nextAns.push_back(Pair (*it, *pkb->getNext(*it).begin()));
					cout<<"Pushing in it = "<<*it<<endl;
				}
			}
		}

		insertLinks(tk1, relIndex);
	}

	//Next(_, n)
	else if(tk1=="_"){
		if(isExistInLinkages(tk2)){
			set<int> sa = retrieveTokenEvaluatedAnswers(tk2);

			for(set<int>::iterator it = sa.begin(); it!=sa.end(); it++){
				if(!pkb->getPrevious(*it).empty()){
					nextAns.push_back(Pair (*pkb->getPrevious(*it).begin(), *it));
				}
			}
			
			removePairs(nextAns, tk2, 2);
		} else {
			set<int> va = pkb->getAllStmts(i2->second);

			for(set<int>::iterator it = va.begin(); it!=va.end(); it++){
				if(!pkb->getPrevious(*it).empty()){
					nextAns.push_back(Pair (*pkb->getPrevious(*it).begin(), *it));
				}
			}
		}

		insertLinks(tk2, relIndex);
	}

	//Next(n, 4)
	else if(isalpha(tk1[0])){
		int tk2Int = atoi(tk2.c_str());
		set<int> tk1Vec = pkb->getPrevious(tk2Int);
		for(set<int>::iterator it= tk1Vec.begin(); it!=tk1Vec.end(); it++){
			if(pkb->isSynType(i1->second, *it)){
				nextAns.push_back(Pair (*it, tk2Int));
			}
		}
		
		if(isExistInLinkages(tk1)){
			removePairsFromRelAns(&nextAns, tk1, 1);
			removePairs(nextAns, tk1, 1);
		}

		insertLinks(tk1, relIndex);
	}

	//Next(3, n)
	else if(isalpha(tk2[0])){
		cout<<"Second Token is Alpha"<<endl;
		int tk1Int = atoi(tk1.c_str());
		set<int> tk1Vec = pkb->getNext(tk1Int);

		for(set<int>::iterator it = tk1Vec.begin(); it!=tk1Vec.end(); it++){
			cout<<"Iterating through the vector of GETNEXT(TOKEN1)"<<endl;
			if(pkb->isSynType(i2->second, *it)){
				cout<<"Pushing into Answer "<<*it<<endl;
				nextAns.push_back(Pair (tk1Int, *it));
			}
		}

		if(isExistInLinkages(tk2)){
			removePairsFromRelAns(&nextAns, tk2, 2);
			removePairs(nextAns, tk2, 2);
		}

		insertLinks(tk2, relIndex);
	}

	//Next(_, 3)
	else if(tk1=="_" && isdigit(tk2[0])){
		int tk2Int = atoi(tk2.c_str());
		if(pkb->getPrevious(tk2Int).empty()){
			nextAns.push_back(Pair (-2,-2));
		}
		else{
			nextAns.push_back(Pair (-1,-1));
		}
	}

	//Next(3, _)
	else if(isdigit(tk1[0]) && tk2=="_"){
		int tk1Int = atoi(tk1.c_str());
		if(pkb->getNext(tk1Int).empty()){
			nextAns.push_back(Pair (-2,-2));
		}
		else{
			nextAns.push_back(Pair (-1,-1));
		}
	}

	//Next(3,4)
	else {
		if(pkb->isNext(atoi(tk1.c_str()), atoi(tk2.c_str()))){
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

	unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(tk1);
	unordered_map<string, TypeTable::SynType>::iterator i2 = m.find(tk2);

	vector<int> traverseTable;
	set<Pair> nextStarAns;
	vector<Pair> nextStarAnsVec;
	//Next*(n,b) //Next*(m, _) //Next*(_,b)
	if((isalpha(tk1[0]) && isalpha(tk2[0])) || (tk1=="_" && isalpha(tk2[0])) || (isalpha(tk1[0]) && tk2=="_")){
		set<int> tk1List;
		if(tk1=="_"){
			tk1List = pkb->getAllStmts(TypeTable::STMT);
		}else{
			tk1List = pkb->getAllStmts(i1->second);
		}

		if(tk2=="_"){
			for(set<int>::iterator it = tk1List.begin(); it!=tk1List.end(); it++){
				traverseTable.clear();
				recursiveNext(*it, *it, &nextStarAns, i2->second, &traverseTable);
			}
		}
		//Next*(n, n)
		else if(tk1==tk2){
			cout<<"Token1 and Token2 are equal"<<endl;
			for(set<int>::iterator it = tk1List.begin(); it!=tk1List.end(); it++){
				traverseTable.clear();
				recursiveNextTarget(*it, *it, *it, &nextStarAns, &traverseTable);
			}
		}
		else{
			for(set<int>::iterator it = tk1List.begin(); it!=tk1List.end(); it++){
				traverseTable.clear();
				recursiveNext(*it, *it, &nextStarAns, TypeTable::STMT, &traverseTable);
			}
		}

		for(set<Pair>::iterator it = nextStarAns.begin(); it!=nextStarAns.end(); it++){
			nextStarAnsVec.push_back(*it);
		}
	}

	else if(tk1=="_" && tk2=="_"){
		set<int> x = pkb->getAllNext();
		if(x.empty()){
			nextStarAnsVec.push_back(Pair (-2,-2));
		}else {
			nextStarAnsVec.push_back(Pair (-1, -1));
		}
	}

	//Next*(n, 3) //Next*(_, 3)
	else if(isalpha(tk1[0]) || tk1=="_"){
		int tk2Int = atoi(tk2.c_str());
		if(tk1=="_"){
			recursiveNextReverse(tk2Int, tk2Int, &nextStarAns, TypeTable::STMT, &traverseTable);
			if(nextStarAns.empty()){
				nextStarAnsVec.push_back(Pair(-2,-2));
			}else{
				nextStarAnsVec.push_back(Pair(-1,-1));
			}
		}
		else{
			cout<<"In Next*(token, digit)"<<endl;
			recursiveNextReverse(tk2Int, tk2Int, &nextStarAns, i1->second, &traverseTable);
			for(set<Pair>::iterator it = nextStarAns.begin(); it!=nextStarAns.end(); it++){
				cout<<"Pushing into answer the pair "<<it->ans1<<"and"<<it->ans2<<endl;
				nextStarAnsVec.push_back(*it);
			}
		}
	}

	//Next*(3, n) Next*(3, _)
	else if(isalpha(tk2[0])){
		if(tk2=="_"){
			recursiveNext(atoi(tk1.c_str()), atoi(tk1.c_str()), &nextStarAns, TypeTable::STMT, &traverseTable);
			if(nextStarAns.empty()){
				nextStarAnsVec.push_back(Pair(-2,-2));
			}else{
				nextStarAnsVec.push_back(Pair(-1,-1));
			}
		}else{
			recursiveNext(atoi(tk1.c_str()), atoi(tk1.c_str()), &nextStarAns, i2->second, &traverseTable);

			for(set<Pair>::iterator it = nextStarAns.begin(); it!=nextStarAns.end(); it++){
				nextStarAnsVec.push_back(*it);
			}
		}
	}

	//Next*(1,7)
	else {
		int tk2Int = atoi(tk2.c_str());
		int tk1Int = atoi(tk1.c_str());

		cout<<"tk1Int = "<<tk1Int<<" tk2Int = "<<tk2Int<<endl;
		recursiveNextTarget(tk1Int, tk1Int, tk2Int, &nextStarAns, &traverseTable);
		
		if(nextStarAns.empty()){
			nextStarAnsVec.push_back(Pair (-2, -2));
		}else{
			nextStarAnsVec.push_back(Pair (-1, -1));
		}

	}

	intersectPairs(tk1,tk2,&nextStarAnsVec, relIndex);
	relAns.insert(make_pair<int, vector<Pair>>(relIndex, nextStarAnsVec));
}

//find Next*(1, s2)
void QueryEvaluator::recursiveNext(int rootIndex, int currentIndex, set<Pair> * ans, TypeTable::SynType type, vector<int> *traverseTable){
	set<int> next = pkb->getNext(currentIndex);

	for(set<int>::iterator it = next.begin(); it!=next.end(); it++){
		if(find(traverseTable->begin(), traverseTable->end(), *it)!=traverseTable->end()){
			it++;
			if(it==next.end()){
				break;
			}
		}else{
			traverseTable->push_back(*it);
		}
		if(pkb->isSynType(type,*it)){
			ans->insert(Pair (rootIndex, *it));
		}
		recursiveNext(rootIndex, *it, ans, type, traverseTable);
	}
}

void QueryEvaluator::recursiveNextTarget(int rootIndex, int currentIndex, int targetIndex, set<Pair> * ans, vector<int> *traverseTable){
	cout<<"In recursiveNextTarget where rootIndex = "<<rootIndex <<" and currentIndex = "<<currentIndex<<" and targetIndex = "<<targetIndex<<endl;
	set<int> next = pkb->getNext(currentIndex);
	for(set<int>::iterator it = next.begin(); it!=next.end(); it++){
		//int flag = (find(traverseTable->begin(), traverseTable->end(), *it)!=traverseTable->end());
		//cout<<"FLAG IS "<<flag<<endl;
		if(find(traverseTable->begin(), traverseTable->end(), *it)!=traverseTable->end()){
			cout<<*it<<" is traversed before. Moving on to the next node"<<endl;
			it++;
			if(it==next.end()){
				cout<<"Reached the end "<<endl;
				break;
			}
		}else{
			cout<<*it<<" is not traversed before. Inserting stmtnum "<<*it<<" into traverseTable"<<endl;
			traverseTable->push_back(*it);
		}
		if(*it == targetIndex){
			cout<<"TargetIndex found"<<endl;
			ans->insert(Pair (rootIndex, targetIndex));
			break;
		}
		recursiveNextTarget(rootIndex, *it, targetIndex, ans, traverseTable);
	}
}

void QueryEvaluator::recursiveNextReverse(int rootIndex, int currentIndex, set<Pair> * ans, TypeTable::SynType type, vector<int>* traverseTable){
	set<int> prev = pkb->getPrevious(currentIndex);

	for(set<int>::iterator it = prev.begin(); it!=prev.end(); it++){
		cout<<"Traversing "<<*it<<endl;
		cout<<"Type is "<<convertEnumToString(type)<<endl;
		if(find(traverseTable->begin(), traverseTable->end(), *it)!=traverseTable->end()){
			cout<<"Node traversed before. Moving on to next node"<<endl;
			it++;
			if(it==prev.end()){
				break;
			}
		}else{
			cout<<"Node not traversed before"<<endl;
			traverseTable->push_back(*it);
		}
		if(pkb->isSynType(type,*it)){
			cout<<"SynType match, inserting pair"<<endl;
			ans->insert(Pair (*it, rootIndex));
		}
		recursiveNextReverse(rootIndex, *it, ans, type, traverseTable);
	}
}

void QueryEvaluator::evaluateCalls(Relationship r, int relIndex){
	string tk1 = r.getToken1();
	string tk2 = r.getToken2();
	set<int> ans;
	set<int> called;
	vector<Pair> callAns;

	//Calls(p, q) OR Calls(p, _) OR Calls(_,q)
	if((isalpha(tk1[0]) && isalpha(tk2[0])) || (isalpha(tk1[0])&&tk2=="_") || (tk1=="_"&&isalpha(tk2[0]))){
		set<int> procIndexes = pkb->getAllProcIndexes();
		for(set<int>::iterator it=procIndexes.begin(); it!=procIndexes.end(); it++){
			called = pkb->getCalled(*it);

			for(set<int>::iterator it2=called.begin(); it2!=called.end(); it2++){
				callAns.push_back(Pair (*it, *it2));
				cout<<"it = "<<*it<<" "<<"it2 = "<<*it2<<endl;
			}
		}

	}

	//Select p Calls(p, "Second") Calls(_, "Second")
	else if(isalpha(tk1[0]) || (tk1=="_" && tk2!="_")){
		int procIndex = pkb->getProcIndex(tk2.substr(1,tk2.length()-2));
		ans = pkb->getCalls(procIndex);

		//Calls(_, "Second")
		if(tk1=="_"){
			if(!ans.empty()){
				callAns.push_back(Pair(-1,-1));
			}else{
				callAns.push_back(Pair(-2,-2));
			}
		}

		//Calls(p, "Second")
		else{
			for(set<int>::iterator it=ans.begin(); it!=ans.end(); it++){
				callAns.push_back(Pair (*it, procIndex));
			}
		}
	}

	//Select q Calls("First", q) Calls("First", _)
	else if(isalpha(tk2[0]) || (tk1!="_" && tk2=="_")){

		int procIndex = pkb->getProcIndex(tk1.substr(1,tk1.length()-2));
		ans = pkb->getCalled(procIndex);

		//Calls("First", _)
		if(tk2=="_"){
			if(!ans.empty()){
				callAns.push_back(Pair(-1,-1));
			}else{
				callAns.push_back(Pair(-2,-2));
			}
		}

		//Calls("First", q)
		else{
			for(set<int>::iterator it=ans.begin(); it!=ans.end(); it++){
				callAns.push_back(Pair (procIndex, *it));
			}
		}
	}

	//Calls(_,_)
	else if(tk1=="_" && tk2=="_"){
		ans = pkb->getAllCalls();
		if(!ans.empty()){
			callAns.push_back(Pair (-1, -1));
		}else{
			callAns.push_back(Pair (-2, -2));
		}
	}

	//Calls("Third", "Fourth")
	else {
		cout<<"supposed"<<endl;
		cout<<tk1.substr(1, tk1.length()-2)<<tk2.substr(1,tk2.length()-2)<<endl;
		int procIndex1 = pkb->getProcIndex(tk1.substr(1, tk1.length()-2));
		int procIndex2 = pkb->getProcIndex(tk2.substr(1,tk2.length()-2));
		if(pkb->isCalls(procIndex1, procIndex2)){
			callAns.push_back(Pair (-1, -1));
		}else{
			callAns.push_back(Pair (-2, -2));
		}
	}

	intersectPairs(tk1,tk2,&callAns, relIndex);

	relAns.insert(make_pair(relIndex, callAns));


}

void QueryEvaluator::evaluateCallsStar(Relationship r, int relIndex){
	string tk1 = r.getToken1();
	string tk2 = r.getToken2();

	vector<Pair> callsStarAns;

	//Calls*(a,b) 
	if(isalpha(tk1[0]) && isalpha(tk2[0])){
		set<int> allProc = pkb->getAllProcIndexes();

		for(set<int>::iterator it = allProc.begin(); it!=allProc.end(); it++){
			recursiveCall(*it, *it, &callsStarAns);
		}
	}

	//Calls*(a,_)
	else if(isalpha(tk1[0]) && tk2=="_"){
			set<int> allProc = pkb->getAllProcIndexes();

			for(set<int>::iterator it=allProc.begin(); it!=allProc.end(); it++){
				if(!pkb->getCalled(*it).empty()){
					callsStarAns.push_back(Pair (*it, -1));
				}
			}
	}

	//Calls*(a, "second")
	else if(isalpha(tk1[0])) {
		int index = pkb->getProcIndex(tk2.substr(1,tk2.length()-2));

		recursiveInverseCall(index, index, &callsStarAns);

	}

	//Calls*(_,b)
	else if(isalpha(tk2[0]) && tk1=="_"){

		set<int> allProc = pkb->getAllProcIndexes();

		for(set<int>::iterator it = allProc.begin(); it!=allProc.end(); it++){
			if(!pkb->getCalls(*it).empty()){
				callsStarAns.push_back(Pair(-1, *it));
			}
		}

	}

	//Calls*("first", b)
	else if(isalpha(tk2[0])){
		int index = pkb->getProcIndex(tk1.substr(1, tk1.length()-2));

		recursiveCall(index, index, &callsStarAns);
	}

	//Calls*(_,"Second")
	else if(tk1=="_" && tk2[0]=='\"'){
		set<int> p = pkb->getCalls(pkb->getProcIndex(tk2.substr(1, tk2.length()-2)));
		if(p.empty()){
			callsStarAns.push_back(Pair (-2,-2));
		}else{
			callsStarAns.push_back(Pair (-1,-1));
		}
	}

	//Calls*("First", _)
	else if(tk1[0]=='\"' && tk2=="_"){
		set<int> p = pkb->getCalled(pkb->getProcIndex(tk1.substr(1, tk1.length()-2)));
		if(p.empty()){
			callsStarAns.push_back(Pair (-2,-2));
		}else{
			callsStarAns.push_back(Pair (-1,-1));
		}
	}

	//Calls*("first", "second")
	else {
		int index1 = pkb->getProcIndex(tk1.substr(1, tk1.length()-2));
		int index2 = pkb->getProcIndex(tk2.substr(1, tk1.length()-2));

		recursiveCallBoolean(index1, index1, index2, &callsStarAns);

		if(callsStarAns.empty()){
			callsStarAns.push_back(Pair (-2, -2));
		}
	}

	//If both a and b exist in QueryEvaluator::linkages
	intersectPairs(tk1,tk2,&callsStarAns,relIndex);

	QueryEvaluator::relAns.insert(make_pair(relIndex, callsStarAns));

}

void QueryEvaluator::recursiveCall(int rootProcIndex, int currentIndex, vector<Pair> * ans){
	set<int> called = pkb->getCalled(currentIndex);

	for(set<int>::iterator i=called.begin(); i!=called.end(); i++){
		ans->push_back(Pair (rootProcIndex, *i));
		recursiveCall(rootProcIndex, *i, ans);
	}
}

void QueryEvaluator::recursiveCallBoolean(int rootProcIndex, int currentIndex, int targetIndex, vector<Pair> * ans){
	set<int> called = pkb->getCalled(currentIndex);

	for(set<int>::iterator i=called.begin(); i!=called.end(); i++){
		cout<<"Iterating throught called vector. *i = "<<*i <<endl;
		if(*i==targetIndex){
			cout<<"recursiveCallBoolean returns TRUE"<<endl;
			ans->push_back(Pair (-1,-1));
			break;
		}
		recursiveCallBoolean(rootProcIndex, *i, targetIndex, ans);
	}
}

void QueryEvaluator::recursiveInverseCall(int leafIndex, int currentIndex, vector<Pair> * ans){
	set<int> calls = pkb->getCalls(currentIndex);

	for(set<int>::iterator i=calls.begin(); i!=calls.end(); i++){
		ans->push_back(Pair (*i, leafIndex));
		recursiveInverseCall(leafIndex, *i, ans);
	}
}

void QueryEvaluator::evaluateFollows(Relationship r, unordered_map<string, TypeTable::SynType> m, int relIndex){
	string tk1 = r.getToken1();
	string tk2 = r.getToken2();
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
					if(pkb->isFollows(*it, *it2)){
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
				cout<<"in for loop"<<endl;
				int follows = pkb->getFollows(*it);
				cout<<"follows: "<<convertEnumToString(i2->second)<<" "<<follows<<endl;
				if(follows!=-1 && pkb->isSynType(i2->second,follows)){
					followsAns.push_back(Pair (*it, follows));
					cout<<"Pushing back "<<*it<<endl;
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
				int followedBy = pkb->getFollowedBy(*it);
				if(followedBy!=-1 && pkb->isSynType(i1->second,followedBy)){
					followsAns.push_back(Pair (followedBy, *it));
				}
			}
			//Delete the redundant pairs
			removePairs(followsAns,tk2,2);

		}

		//If both do not exist
		else {
			cout<<"Both tokens are alpha and do not exist in linkages"<<endl;
			//Retrieve both a and b from PKB
			set<int> first = pkb->getAllStmts(i1->second);
			set<int> second = pkb->getAllStmts(i2->second);
			cout<<"trying is follows"<<pkb->isFollows(2,3)<<endl;
			for(set<int>::iterator iter1 = first.begin(); iter1!=first.end(); iter1++){
				for(set<int>::iterator iter2 = second.begin(); iter2!=second.end(); iter2++){
					if(pkb->isFollows(*iter1, *iter2)){
						followsAns.push_back(Pair (*iter1, *iter2));
						cout<<"first.at(i) = "<<*iter1<<"second.at(i) = "<<*iter2<<endl;
					}
				}
			}

		}
		
		//Add the relationship into QueryEvaluator::linkages
		insertLinks(tk1, relIndex);
		insertLinks(tk2, relIndex);

	}

	//Follows(_,_) if both tokens are wildcards just evaluate true or false
	else if(tk1=="_" && tk2=="_"){
		set<int> ans = pkb->getAllFollows();
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
					if(pkb->isFollows(*it, atoi(tk2.c_str()))){
						followsAns.push_back(Pair (*it, atoi(tk2.c_str())));
					}
				}
			} 
			//Follows(a, _)
			else {
				for(set<int>::iterator it=sa.begin(); it!=sa.end(); it++){
					if(pkb->getFollows(*it)!=-1){
						followsAns.push_back(Pair (*it, pkb->getFollows(*it)));
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
				int first = pkb->getFollowedBy(atoi(tk2.c_str()));
				if(pkb->isSynType(i1->second,first))
					followsAns.push_back(Pair (first, atoi(tk2.c_str())));
			}

			//Follows(a, _)
			else {
				set<int> a = pkb->getAllFollowedBy();
				for(set<int>::iterator it = a.begin(); it!=a.end(); it++){
					if(pkb->isSynType(i1->second, *it))
						followsAns.push_back(Pair (*it, pkb->getFollows(*it)));
				}
			}
		}

		insertLinks(tk1, relIndex);
	}

	//Follows(1,b)
	else if(isalpha(tk2[0])){
		if(isExistInLinkages(tk2)){
			cout<<tk2<<" Found to Exist in Linkages"<<endl;
			//get the set of answers that are previously evaluated by other relations
			set<int> sa = retrieveTokenEvaluatedAnswers(tk2);

			if(isdigit(tk1[0])){
				for(set<int>::iterator it=sa.begin(); it!=sa.end(); it++){
					if(pkb->isFollows(atoi(tk1.c_str()), *it)){
						followsAns.push_back(Pair (atoi(tk1.c_str()), *it));
					}
				}
			}

			//Follows(_,b)
			else {
				for(set<int>::iterator it=sa.begin(); it!=sa.end(); it++){
					if(pkb->getFollowedBy(*it)!=-1){
						followsAns.push_back(Pair (pkb->getFollowedBy(*it),*it));
					}
				}
			}
			//Delete the redundant pairs
			removePairs(followsAns,tk2,2);
			
		}
		
		//If it does not exist
		else {
			//Retrieve a from PKB and push it into the answer vector
			cout<<"Second token is alpha and it does not exist in linkages"<<endl;
			if(isdigit(tk1[0])){
				cout<<"First token is digit"<<endl;
				int second = pkb->getFollows(atoi(tk1.c_str()));
				cout<<"Answer is = "<<second<<endl;
				if(second!=-1 && pkb->isSynType(i2->second, second)){
					followsAns.push_back(Pair (atoi(tk1.c_str()), second));
				}
				cout<<"followsAns.size = "<<followsAns.size()<<endl;
			}

			//Follows(_,b)
			else {
				set<int> a = pkb->getAllFollows();
				for(set<int>::iterator it = a.begin(); it!=a.end(); it++){
					followsAns.push_back(Pair (pkb->getFollowedBy(*it), *it));
				}
			}

		}

		insertLinks(tk2, relIndex);
	}

	//Follows(1,2)
	else {
		//if Follows(1,2) is verified as false, clear all answers
		if(isdigit(tk1[0]) && isdigit(tk2[0])){
			if(!pkb->isFollows(atoi(tk1.c_str()), atoi(tk2.c_str()))){
				followsAns.push_back(Pair (-2,-2));
			}
			else{
				followsAns.push_back(Pair (-1,-1));
			}
		}

		//Follows(1, _)
		else if(isdigit(tk1[0])){
			if(pkb->getFollows(atoi(tk1.c_str()))==-1){
				followsAns.push_back(Pair (-2,-2));
			}
			else{
				followsAns.push_back(Pair (-1,-1));
			}
		}

		//Follows(_, 2)
		else {
			if(pkb->getFollows(atoi(tk2.c_str()))==-1){
				followsAns.push_back(Pair (-2,-2));
			}
			else{
				followsAns.push_back(Pair (-1,-1));
			}
		}
	}

	QueryEvaluator::relAns.insert(make_pair(relIndex, followsAns));
}


void QueryEvaluator::evaluateFollowsStar(Relationship r, unordered_map<string, TypeTable::SynType> m, int relIndex){
	string tk1=r.getToken1();
	string tk2=r.getToken2();
	set<int> answer;
	set<int> selected;
	set<Pair> followsStarAnsSet;//REMEMBER TO INSERT SELF DEFINED COMPARATOR
	vector<Pair> followsStarAns;
	
	int stmtNumber = 0;
	unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(tk1);
	unordered_map<string, TypeTable::SynType>::iterator i2 = m.find(tk2);
	
	//Select w such that Follows*(w, a) OR Follows*(_, a) OR Follows*(w, _)
	if((isalpha(tk1[0]) && isalpha(tk2[0])) || (tk1=="_" && isalpha(tk2[0])) || (tk2=="_" && isalpha(tk1[0]))){

		if(tk1=="_"){
			selected = pkb->getAllStmts(TypeTable::STMT);
		}

		else{
			selected = pkb->getAllStmts(i1->second);	//get all while statements
		}

		for(set<int>::iterator it = selected.begin(); it!=selected.end(); it++){
			stmtNumber = pkb->getFollows(*it);
			if(tk2!="_"){
				if(!pkb->isSynType(i2->second, stmtNumber)){
					stmtNumber = -1;
				}
			}
			do{			
				if(stmtNumber!=-1){
					followsStarAnsSet.insert(Pair (*it, stmtNumber));
				}
				else{
					break;
				}
				stmtNumber = pkb->getFollows(stmtNumber);
				if(tk2!="_"){
					if(!pkb->isSynType(i2->second, stmtNumber)){
						stmtNumber = -1;
					}
				}
			}while(true);
		}
	}
	
	//Select a such that Follows*(a, 13)
	else if(isalpha(tk1[0])){
		cout<<"Handling Follows*(type, stmtnum) with tk2 = " << atoi(tk2.c_str())<<endl;
		stmtNumber = atoi(tk2.c_str());
		do{			
			cout<<"Calling getFollowedBy(type, stmtnum)"<<endl;
			stmtNumber = pkb->getFollowedBy(stmtNumber);
			if(stmtNumber!=-1){
				cout<<"Evaluated StmtNumber = "<<stmtNumber<<endl;
				if(pkb->isSynType(i1->second, stmtNumber)){
					cout<<"Inserting StmtNumber "<<stmtNumber<<" into the answer set"<<endl;
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
			stmtNumber = pkb->getFollows(stmtNumber);
			if(stmtNumber!=-1){
				if(pkb->isSynType(i2->second, stmtNumber)){
					followsStarAnsSet.insert(Pair (atoi(tk1.c_str()), stmtNumber));
				}
			}
			else{
				break;
			}
			
		}while(true);
	}

	else if(tk1=="_" && tk2=="_"){
		bool flag = false;
		set<int> dummy = pkb->getAllStmts(TypeTable::STMT);
		for(set<int>::iterator it=dummy.begin(); it!=dummy.end(); it++){
			if(pkb->getFollows(*it)!=-1){
				flag = true;
				break;
			}
		}

		if(flag){
			followsStarAnsSet.insert(Pair (-1,-1));
		}else{
			followsStarAnsSet.insert(Pair (-2,-2));
		}
	}

	//Follows*(1,2) OR Follows*(1, _)
	else if((isdigit(tk1[0]) && isdigit(tk2[0]))|| tk2=="_"){
		stmtNumber = atoi(tk1.c_str());
		while(stmtNumber!=-1){	
			stmtNumber = pkb->getFollows(stmtNumber);
			cout<<"STMTNUM is "<<stmtNumber<<endl;
			if(stmtNumber==atoi(tk2.c_str()) || (tk2=="_" && stmtNumber!=-1)){
				followsStarAnsSet.insert(Pair (-1,-1));
				break;
			}
			if(stmtNumber>atoi(tk2.c_str())){
				followsStarAnsSet.insert(Pair (-2,-2));
				break;
			}
		}
	}

	//Follows(_,2)
	else{
		stmtNumber = pkb->getFollowedBy(atoi(tk2.c_str()));
		if(stmtNumber==-1){
			followsStarAnsSet.insert(Pair(-2,-2));
		}
		else {
			followsStarAnsSet.insert(Pair(-1,-1));
		}
	}
	
	//copy set into vector
	//copy(followsStarAnsSet.begin(), followsStarAnsSet.end(),followsStarAns);
	for(set<Pair>::iterator it=followsStarAnsSet.begin(); it!=followsStarAnsSet.end(); it++){
		followsStarAns.push_back(*it);
	}

	
	intersectPairs(tk1,tk2,&followsStarAns,relIndex);

	cout<<"Inserting into RelAns RelIndex = "<<relIndex<<endl;
	relAns.insert(make_pair(relIndex, followsStarAns));
	
}

void QueryEvaluator::evaluateParent(Relationship r, unordered_map<string, TypeTable::SynType> m, int relIndex){
	string tk1 = r.getToken1();
	string tk2 = r.getToken2();

	set<int> answer;
	vector<Pair> parentAns;
	unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(tk1);
	unordered_map<string, TypeTable::SynType>::iterator i2 = m.find(tk2);

	//Parent(a,b)
	if((isalpha(tk1[0]) && isalpha(tk2[0])) || (tk1=="_" && isalpha(tk2[0]))|| (tk2=="_" && isalpha(tk1[0])) ){

		if(isExistInLinkages(tk1))
			answer = retrieveTokenEvaluatedAnswers(tk1);
		else
			answer = pkb->getAllStmts(i1->second);

		//Parent(_, b)
		if(tk1=="_"){
			answer = pkb->getAllStmts(TypeTable::STMT);
		}
		
		for(set<int>::iterator it=answer.begin(); it!=answer.end(); it++){
			cout<<"answer = "<<*it<<endl;
			set<int> children;
			if(tk2=="_"){	//Parent(a,_)
				children = pkb->getChildren(*it);
			}else{
				children = pkb->getChildren(*it);
			}
			for(set<int>::iterator it2=children.begin(); it2!=children.end(); it2++){
				if(pkb->isSynType(i2->second, *it2)){
					parentAns.push_back(Pair(*it, *it2));
					cout<<"it" << *it << "it2"<<*it2<<endl;
				}
			}
		}
	}
	//Parent(a,3)
	else if(isalpha(tk1[0]) || tk1=="_"){

		cout<<"Calling getParent(TYPE, STMTNUM)"<<endl;
		int parent;
		//Parent(_,3)
		if(tk1=="_"){
			parent = pkb->getParent(atoi(tk2.c_str()));
			if(parent!=-1){
				parentAns.push_back(Pair(-1,-1));
			}
			else {
				parentAns.push_back(Pair(-2,-2));
			}
		}
		else {
			parent = pkb->getParent(atoi(tk2.c_str()));
			if(!pkb->isSynType(i1->second, parent)){
				parent = -1;
			}
			if(parent!=-1){
				parentAns.push_back(Pair(parent, atoi(tk2.c_str())));
			}
		}
	}

	//Parent(3,a)
	else if(isalpha(tk2[0]) || tk2=="_"){
		cout<<"Parent(STMTNUM, TYPE)"<<endl;
		if(tk2!="_"){
			set<int> children = pkb->getChildren(atoi(tk1.c_str()));
			for(set<int>::iterator it=children.begin(); it!=children.end(); it++){
				if(pkb->isSynType(i2->second, *it)){
					parentAns.push_back(Pair(atoi(tk1.c_str()), *it));
					cout<<"in for loop"<<endl;
				}
			}
		} else {
			set<int> children = pkb->getChildren(atoi(tk1.c_str()));
			if(!children.empty()){
				parentAns.push_back(Pair(-1,-1));
			}else {
				parentAns.push_back(Pair(-2,-2));
			}
		}
	}

	//Parent(_,_)
	else if(tk1=="_" && tk2 == "_"){
		set<int> ans = pkb->getAllParent();
		if(!ans.empty()){
			parentAns.push_back(Pair(-1,-1));
		}else {
			parentAns.push_back(Pair(-2,-2));
		}
	}

	//Parent(1,5)
	else{
		 if(pkb->isParent(atoi(tk1.c_str()), atoi(tk2.c_str()))){
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

void QueryEvaluator::evaluateParentStar(Relationship r, unordered_map<string, TypeTable::SynType> m, int relIndex){
	cout<<"Initialzing all Parent* variables"<<endl;
	string tk1=r.getToken1();
	string tk2=r.getToken2();

	vector<Pair> answer;
	set<Pair> parentStarAnsSet;
	int stmtNumber = 0;
	unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(tk1);
	unordered_map<string, TypeTable::SynType>::iterator i2 = m.find(tk2);

	//Parent*(w, a) Parent(_,a) Parent(w,_)
	if((isalpha(tk1[0]) && isalpha(tk2[0]))|| (isalpha(tk1[0])&& tk2=="_") || (tk1=="_" && isalpha(tk2[0]))){
		cout<<"If both tokens are alpha or one of them is a wildcard"<<endl;
		set<int> sa;
		set<int> sb;
		if(isExistInLinkages(tk1)){
			sa = retrieveTokenEvaluatedAnswers(tk1);
		}
		if(isExistInLinkages(tk2)){
			sb = retrieveTokenEvaluatedAnswers(tk2);
		}


		int stmt;

		if(!isExistInLinkages(tk2)){
			cout<<"Token2 does not Exist in Linkages"<<endl;
			sb.clear();
			if(tk2=="_"){
				sb = pkb->getAllStmts(TypeTable::STMT);
			}else{
				sb = pkb->getAllStmts(i2->second);
			}

		}

		cout<<"sb is Empty: "<<sb.empty()<<endl;
		for(set<int>::iterator it = sb.begin(); it!=sb.end(); it++){
			cout<<"Iterating token 2 set Sb"<<endl;
			stmt = pkb->getParent(*it);
			while(stmt!=-1){
				if(isExistInLinkages(tk1)){
					if(pkb->isSynType(i1->second,stmt) && sa.find(stmt)!=sa.end()){
						parentStarAnsSet.insert(Pair (stmt, *it));
					}
				}
				else{
					if(tk1=="_"){
						cout<<"Token = _ and Parent = "<<stmt<<endl;
						parentStarAnsSet.insert(Pair (stmt, *it));
					}else{
						if(pkb->isSynType(i1->second,stmt)){
							parentStarAnsSet.insert(Pair (stmt, *it));
						}
					}
				}
				stmt = pkb->getParent(stmt);
			}
		}

		if(isalpha(tk1[0])){
			insertLinks(tk1, relIndex);
		}

		if(isalpha(tk2[0])){
			insertLinks(tk2, relIndex);
		}
	}


	//Parent*(w, 4)
	else if(isalpha(tk1[0])){
		int tk2Int = atoi(tk2.c_str());
		cout<<"tk2 is Integer "<<tk2Int<<endl;
		set<int> sa;
		int stmt;

		if(isExistInLinkages(tk1)){
			cout<<"TOKEN1 FOUND TO EXIST IN LINKAGES"<<endl;
			sa = retrieveTokenEvaluatedAnswers(tk1);
		}else {
			cout<<"TOKEN1 FOUND NOT TO EXIST IN LINKAGES"<<endl;
			sa = pkb->getAllStmts(i1->second);
		}
		
		cout<<"Set is Empty: "<<sa.empty()<<endl;
		stmt = pkb->getParent(tk2Int);
		while(stmt!=-1){
			//cout<<"Parent StmtNumber = "<<stmt<<endl;
			if(sa.find(stmt)!=sa.end()){
				cout<<"Insert stmtNum = "<<stmt<<" into set"<<endl;
				parentStarAnsSet.insert(Pair (stmt, tk2Int));
			}
		stmt = pkb->getParent(stmt);
		}

		insertLinks(tk1, relIndex);
	}

	//Parent*(3, a)
	else if(isalpha(tk2[0])){
		int tk1Int = atoi(tk1.c_str());
		set<int> sb;
		int stmt;

		if(isExistInLinkages(tk2)){
			sb = retrieveTokenEvaluatedAnswers(tk2);
		}else {
			sb = pkb->getAllStmts(i2->second);
		}
		
		for(set<int>::iterator it = sb.begin(); it!=sb.end(); it++){
		stmt = pkb->getParent(*it);
			while(stmt!=-1){
				if(stmt == tk1Int){
					parentStarAnsSet.insert(Pair (tk1Int, *it));
					break;
				}
			stmt = pkb->getParent(stmt);
			}
		}

		insertLinks(tk2, relIndex);
	}

	else if(tk1=="_" && tk2=="_"){
		set<int> dummy = pkb->getAllParent();
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
			if(pkb->getChildren(atoi(tk1.c_str())).empty()){
				answer.push_back(Pair(-2,-2));
			}else{
				answer.push_back(Pair(-1,-1));
			}
			relAns.insert(make_pair<int, vector<Pair>>(relIndex, answer));
			return;
		}

		//Parent*(_,3)
		if(tk1=="_"){
			if(pkb->getParent(atoi(tk2.c_str()))==-1){
				answer.push_back(Pair(-2,-2));
			}else{
				answer.push_back(Pair(-1,-1));
			}
			relAns.insert(make_pair<int, vector<Pair>>(relIndex, answer));
			return;
		}

		int tk1Int = atoi(tk1.c_str());
		int tk2Int = atoi(tk2.c_str());

		int stmt = pkb->getParent(tk2Int);
		while(stmt!=-1){
			if(stmt == tk1Int){
				answer.push_back(Pair(-1,-1));
				relAns.insert(make_pair<int, vector<Pair>>(relIndex, answer));
				return;
			}

			stmt = pkb->getParent(stmt);
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

	set<int> selected;
	vector<Pair> modAns;
	set<int> answer;
	unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(tk1);
	unordered_map<string, TypeTable::SynType>::iterator i2 = m.find(tk2);

	//Modifies(a,v) Modifies(_,v) Modifies(a,_)
	if((isalpha(tk1[0]) && isalpha(tk2[0])) || (tk1=="_" && isalpha(tk2[0])) || (isalpha(tk1[0])&& tk2=="_")){

		//If first token is of procedure type
		//Modifies(p, v)
		if(i1->second==TypeTable::PROCEDURE || tk1=="_"){

			selected = pkb->getAllProcIndexes();

			//iterate through all procedures
			for(set<int>::iterator it=selected.begin(); it!=selected.end(); it++){
				answer = pkb->getModifiedProc(*it);
				for(set<int>::iterator it2=answer.begin(); it2!=answer.end(); it2++){
					modAns.push_back(Pair (*it, *it2));
				}
			}
		} 
		

		//Otherwise
		else {
			selected = pkb->getAllStmts(i1->second);
			for(set<int>::iterator it=selected.begin(); it!=selected.end(); it++){
				answer = pkb->getModified(*it);
				for(set<int>::iterator it2=answer.begin(); it2!=answer.end(); it2++){
					modAns.push_back(Pair (*it, *it2));
				}
			}
		}
	}

	//Modifies(a, "x")
	else if(isalpha(tk1[0])){
		string varName = tk2.substr(1,tk2.length()-2);
		int varIndex = pkb->getVarIndex(varName);

		//If first token is of type procedure
		//Modifies(p, "x")
		if(i1->second==TypeTable::PROCEDURE){
			cout<<"In Modifies(p, \"var\")"<<endl;
			answer = pkb->getModifiesProc(varIndex);
			for(set<int>::iterator it=answer.begin(); it!=answer.end(); it++){
				modAns.push_back(Pair (*it, varIndex));
			}
		}

		//otherwise
		else {
			answer = pkb->getModifies(varIndex);
			cout<<varIndex<<endl;
			cout<<"answer is empty: "<<answer.empty()<<endl;
			for(set<int>::iterator it=answer.begin(); it!=answer.end(); it++){
				cout<<"modifiesAnswer"<<*it<<" "<<varIndex<<endl;
				if(pkb->isSynType(i1->second, *it)){
					modAns.push_back(Pair (*it, varIndex));
				}
				
			}
		}

	}

	//Select v such that Modifies(1, v);
	else if(isalpha(tk2[0])){
		if(isdigit(tk1[0])){
			selected = pkb->getModified(atoi(tk1.c_str()));
			for(set<int>::iterator it=selected.begin(); it!=selected.end(); it++){
				modAns.push_back(Pair (atoi(tk1.c_str()), *it));
			}
		}

		//Modifies("First", v)
		else {
			int procIndex = pkb->getProcIndex(tk1.substr(1,tk1.length()-2));
			set<int> vars = pkb->getModifiedProc(procIndex);

			for(set<int>::iterator it = vars.begin(); it!=vars.end(); it++){
				modAns.push_back(Pair(procIndex, *it));
			}
		}
	}

	//Modifies("Third", "x")
	else if(tk1[0]=='\"'){
		if(tk2!="_"){
			cout<<"Modifies(\"Procname\", \"VarName\")"<<endl;
			string procName = tk1.substr(1,tk1.length()-2);
			int procIndex = pkb->getProcIndex(procName);
			string varName = tk2.substr(1,tk2.length()-2);
			int varIndex = pkb->getVarIndex(varName);
			if(pkb->isModifiesProc(procIndex, varIndex)){
				modAns.push_back(Pair (-1,-1));
			}else {
				modAns.push_back(Pair (-2,-2));
			}
		} 
		
		//Modifies("Third", _)
		else {
			int index = pkb->getProcIndex(tk1.substr(1, tk1.length()-2));
			set<int> allVariablesModifiedByProc = pkb->getModifiedProc(index);
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
		set<int> allProcIndexes = pkb->getAllProcIndexes();
		bool flag = false;
		for(set<int>::iterator it = allProcIndexes.begin(); it!=allProcIndexes.end(); it++){
			if(!pkb->getModifiedProc(*it).empty()){
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
			if(!pkb->getModifiesProc(pkb->getVarIndex(tk2.substr(1, tk2.length()-2))).empty()){
				modAns.push_back(Pair (-1,-1));
			}
			else {
				modAns.push_back(Pair (-2, -2));
			}
		}

		else {
		cout<<"supposed"<<endl;
		string varName = tk2.substr(1,tk2.length()-2);
		int varIndex = pkb->getVarIndex(varName);
		cout<<atoi(tk1.c_str())<<varName<<endl;
		if(pkb->isModifies(atoi(tk1.c_str()), varIndex)){
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

void QueryEvaluator::evaluateUses(Relationship r, std::unordered_map<std::string, TypeTable::SynType> m, int relIndex) {
	string tk1=r.getToken1();
	string tk2=r.getToken2();
	set<int> selected;
	set<int> answer;
	vector<Pair> usesAns;
	unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(tk1);
	unordered_map<string, TypeTable::SynType>::iterator i2 = m.find(tk2);

	//Uses(a,v)
	if((isalpha(tk1[0]) && isalpha(tk2[0])) || (tk1=="_" && isalpha(tk2[0])) || (isalpha(tk1[0])&& tk2=="_")){

		//If first token is of procedure type
		if(i1->second==TypeTable::PROCEDURE || tk1=="_"){

			selected = pkb->getAllProcIndexes();

			//iterate through all procedures
			for(set<int>::iterator it=selected.begin(); it!=selected.end(); it++){
				answer = pkb->getUsedProc(*it);
				for(set<int>::iterator it2=answer.begin(); it2!=answer.end(); it2++){
					usesAns.push_back(Pair (*it, *it2));
				}
			}
		} 
		

		//Otherwise
		else {
			selected = pkb->getAllStmts(i1->second);
			for(set<int>::iterator it=selected.begin(); it!=selected.end(); it++){
				answer = pkb->getUsed(*it);
				for(set<int>::iterator it2=answer.begin(); it2!=answer.end(); it2++){
					usesAns.push_back(Pair (*it, *it2));
				}
			}
		}
	}

	//Select a Uses(a, "x")
	else if(isalpha(tk1[0])){
		string varName = tk2.substr(1,tk2.length()-2);
		int varIndex = pkb->getVarIndex(varName);

		//If first token is of type procedure
		if(i1->second==TypeTable::PROCEDURE){

			answer = pkb->getUsesProc(varIndex);
			for(set<int>::iterator it=answer.begin(); it!=answer.end(); it++){
				usesAns.push_back(Pair (*it, varIndex));
			}
		}

		//otherwise
		else {
			answer = pkb->getUses(varIndex);

			for(set<int>::iterator it=answer.begin(); it!=answer.end(); it++){
				if(pkb->isSynType(i1->second, *it)){
					usesAns.push_back(Pair (*it, varIndex));
				}
			}
		}

	}


	//Select v such that Uses(1, v);
	else if(isalpha(tk2[0])){

		if(isdigit(tk1[0])){
			selected = pkb->getUsed(atoi(tk1.c_str()));
			for(set<int>::iterator it=selected.begin(); it!=selected.end(); it++){
				usesAns.push_back(Pair (atoi(tk1.c_str()), *it));
			}
		}

		//Uses("First", v)
		else {
			int procIndex = pkb->getProcIndex(tk1.substr(1,tk1.length()-2));
			set<int> vars = pkb->getUsedProc(procIndex);

			for(set<int>::iterator it = vars.begin(); it!=vars.end(); it++){
				usesAns.push_back(Pair(procIndex, *it));
			}
		}
	}

	//Uses("Third", "x")
	else if(tk1[0]=='\"'){
		if(tk2!="_"){
			string procName = tk1.substr(1,tk1.length()-2);
			int procIndex = pkb->getProcIndex(procName);
			string varName = tk2.substr(1,tk2.length()-2);
			int varIndex = pkb->getVarIndex(varName);
			if(pkb->isUsesProc(procIndex, varIndex)){
				usesAns.push_back(Pair (-1,-1));
			}else {
				usesAns.push_back(Pair (-2,-2));
			}
		}

		//Uses("Third", _)
		else {
			int index = pkb->getProcIndex(tk1.substr(1, tk1.length()-2));
			set<int> allVariablesUsedByProc = pkb->getUsedProc(index);
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
		set<int> allProcIndexes = pkb->getAllProcIndexes();
		bool flag = false;
		for(set<int>::iterator it = allProcIndexes.begin(); it!=allProcIndexes.end(); it++){
			if(!pkb->getUsedProc(*it).empty()){
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
		string varName = tk2.substr(1,tk2.length()-2);
		int varIndex = pkb->getVarIndex(varName);
		//Uses(_, "x")
		if(tk1=="_"){
			if(!pkb->getUsesProc(varIndex).empty()){
				usesAns.push_back(Pair (-1,-1));
			}
			else {
				usesAns.push_back(Pair (-2, -2));
			}
		}

		else{

			if(pkb->isUses(atoi(tk1.c_str()), varIndex)){
				 usesAns.push_back(Pair (-1,-1));
			 }else{
				 usesAns.push_back(Pair (-2,-2));
			 }
		}
	}

	intersectPairs(tk1,tk2,&usesAns,relIndex);

	QueryEvaluator::relAns.insert(make_pair(relIndex, usesAns));
}

void QueryEvaluator::evaluatePattern(Relationship r, std::unordered_map<std::string, TypeTable::SynType> m, int relIndex) {
	string lhs = r.getToken1();
	string rhs = r.getToken2();
	string syn = r.getPatternSyn();
	TypeTable::SynType synType = m.at(syn);
	vector<Pair> patternAns;
	Node* root = pkb->getASTRoot();

	insertLinks(syn, relIndex);
	cout<<"token 1 = "<<lhs<<"token 2 = "<<rhs<<endl;
	switch(synType){
		case TypeTable::ASSIGN:
			patternAns = findAssign(*root, lhs, rhs);
			break;

		case TypeTable::IF:
			break;

		case TypeTable::WHILE:
			break;

	}

	//Printing patternAns
	cout<<"PRINTING PATTERNANS"<<endl;
	for(vector<Pair>::iterator it = patternAns.begin(); it!=patternAns.end(); it++){
		cout<<"ans1 = "<<it->ans1<< " ans2 = "<<it->ans2<<endl;
	}

	QueryEvaluator::relAns.insert(make_pair(relIndex, patternAns));
}

void QueryEvaluator::evaluateAffects(Relationship r, std::unordered_map<std::string, TypeTable::SynType> m, int relIndex) {
}

void QueryEvaluator::evaluateAffectsStar(Relationship r, std::unordered_map<std::string, TypeTable::SynType> m, int relIndex) {
}

vector<Pair> QueryEvaluator::findAssign(Node startNode, string lhs, string rhs) {
	vector<Pair> ans;
	stack<Node> st;
	st.push(startNode);
	
	while(!st.empty()) {
		Node n = st.top();
		st.pop();
		if(n.getType().compare("assign") == 0) {
			if(matchPattern(n, lhs, rhs)) {
				ans.push_back(Pair(n.getProgLine(), n.getProgLine()));
			}
		}
		else {
			vector<Node*> children = n.getChild();
			for(int i=0; i<children.size(); i++)
				st.push(*children.at(i));
		}
	}

	return ans;
}

bool QueryEvaluator::matchPattern(Node n, string lhs, string rhs) {
	lhs.erase(std::remove(lhs.begin(), lhs.end(), '\"'), lhs.end());
	rhs.erase(std::remove(rhs.begin(), rhs.end(), '\"'), rhs.end());

	bool leftMatch=false, rightMatch=false;
	vector<Node*> children = n.getChild();
	Node left = *children.at(0);
	Node right = *children.at(1);

	//Check if lhs matches pattern
	if(lhs.compare("_") == 0 || lhs.compare(left.getData()) == 0) {
		leftMatch = true;
	}

	//Check if rhs matches pattern
	bool underscore = false;
	if(rhs.front() == '_') {
		if(rhs.size() == 1)
			rightMatch = true;
		else
			underscore = true;
	}

	rhs.erase(std::remove(rhs.begin(), rhs.end(), '_'), rhs.end());

	if(!rightMatch) {
		vector<string> tokens;
		tokenizeTokens(rhs, tokens);
		vector<string> postfix = getPostfix(tokens);
		Node* treeRoot = constructExpressionTree(postfix);

		if(underscore) {
			stack<Node> st;
			st.push(right);
			while(!rightMatch && !st.empty()) {
				Node n = st.top();
				st.pop();
				rightMatch = matchTree(n, *treeRoot);
				children = n.getChild();
				for(int i=0; i<children.size(); i++)
					st.push(*children.at(i));
			}
		}
		else
			rightMatch = matchTree(right, *treeRoot);
	}


	return leftMatch && rightMatch;
}

bool QueryEvaluator::matchTree(Node a, Node b) {
	vector<Node*> children1 = a.getChild();
	vector<Node*> children2 = b.getChild();

	if(children1.size() != children2.size())
		return false;

	if(a.getData().compare(b.getData()) != 0)
		return false;

	if(a.getData().compare(b.getData()) == 0 && children1.size() == 0)
		return true;

	Node childA1 = *children1.at(0);
	Node childA2 = *children1.at(1);
	Node childB1 = *children2.at(0);
	Node childB2 = *children2.at(1);

	return matchTree(childA1, childB1) && matchTree(childA2, childB2);
}

Node* QueryEvaluator::constructExpressionTree(vector<string> tokens){
	stack<Node*> st;
	int length = tokens.size();
	
	for(int i=0;i<length;i++){
		if((tokens[i]=="+")||(tokens[i]=="-")||(tokens[i]=="*")||(tokens[i]=="/")){
			Node* right = st.top();
			st.pop();
			Node* left = st.top();
			st.pop();
			Node* curr = new Node(left,right,tokens[i],"operator",-1);
			left->setParent(curr);
			right->setParent(curr);
			st.push(curr);
		}
		else{
			string type;
			if(isAllDigit(tokens[i]))
				type="constant";
			else
				type="variable";

			Node* curr = new Node(tokens[i],type,-1);
			st.push(curr);
		}
	}
	Node* root = st.top();
	st.pop();
	return root;
}

vector<string> QueryEvaluator::getPostfix(vector<string> tokens){
	vector<string> ans;
	stack<string> st;
	int size = tokens.size();
	for(int i=0;i<size;i++){
		if(tokens[i]=="("){
			st.push(tokens[i]);
		}
		else if(tokens[i]==")"){
			if(!st.empty()){
				ans.clear();
				ans.push_back("invalid");
				return ans;
			}
			string tempToken = st.top();
			st.pop();
			while(tempToken!="("){
				if(!st.empty()){
					ans.push_back(tempToken);
					tempToken=st.top();
					st.pop();
				}
				else{
					ans.clear();
					ans.push_back("invalid");
					return ans;
				}
			}
		}
		else if(tokens[i]=="+") {
			if(st.empty()){
				st.push("+");
				continue;
			}
			else{
				string tempToken = st.top();
				while((tempToken=="+")||(tempToken=="-")||(tempToken=="*")||(tempToken=="/")){
					ans.push_back(tempToken);
					st.pop();
					if(!st.empty()){
						tempToken=st.top();
					}
					else{
						break;
					}
				}
				st.push("+");
			}
		}
		else if(tokens[i]=="-") {
			if(st.empty()){
				st.push("-");
				continue;
			}
			else{
				string tempToken = st.top();
				while((tempToken=="+")||(tempToken=="-")||(tempToken=="*")||(tempToken=="/")){
					ans.push_back(tempToken);
					st.pop();
					if(!st.empty()){
						tempToken=st.top();
					}
					else{
						break;
					}
				}
				st.push("-");
			}
		}
		else if(tokens[i]=="*") {
			if(st.empty()){
				st.push("*");
				continue;
			}
			else{
				string tempToken = st.top();
				while((tempToken=="*")||(tempToken=="/")){
					ans.push_back(tempToken);
					st.pop();
					if(!st.empty()){
						tempToken=st.top();
					}
					else{
						break;
					}
				}
				st.push("*");
			}
		}
		else if(tokens[i]=="/") {
			if(st.empty()){
				st.push("/");
				continue;
			}
			else{
				string tempToken = st.top();
				while((tempToken=="*")||(tempToken=="/")){
					ans.push_back(tempToken);
					st.pop();
					if(!st.empty()){
						tempToken=st.top();
					}
					else{
						break;
					}
				}
				st.push("/");
			}
		}
		else {
			ans.push_back(tokens[i]);
		}
	}
	
	while(!st.empty()){
		ans.push_back(st.top());
		st.pop();
	}
	return ans;
}

void QueryEvaluator::tokenizeTokens(string word, vector<string> &storage){
	string token ="";
	for(int i=0;i<(int) word.length();i++){
		if((word[i]=='+')||(word[i]=='-')||(word[i]=='/')||(word[i]=='*')||(word[i]=='=')){
			if(token.length()>0){
				storage.push_back(token);
			}
			token = word[i];
			storage.push_back(token);
			token ="";
		}
		else{
			token = token + word[i];
		}
	}
	if(token.length()>0){
		storage.push_back(token);
	}
	return;
}

bool QueryEvaluator::isAllDigit(string input){
	for(int i=0;i<(int)input.length();i++){
		if(!isdigit(input[i])){
			return false;
		}
	}
	return true;
}


	