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
unordered_map<int, set<int>> QueryEvaluator::nextStarTable;
unordered_map<int, bool> QueryEvaluator::affectsTable;
unordered_map<int, bool> QueryEvaluator::affectsStarTable;
unordered_map<int, set<int>> QueryEvaluator::nst;


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
	//weight
	float followsWeight = 10;
	float followsStarWeight = 20;
	float parentWeight = 10;
	float parentStarWeight = 20;
	float callsWeight = 10;
	float callStarWeight = 20;
	float modifiesWeight = 10;
	float usesWeight = 10;
	float nextWeight = 20;
	float nextStarWeight= 40;
	float withWeight = 20;
	float patternWeight = 20;
	float affectsWeight = 40;
	float affectsStarWeight = 80;
	float siblingWeight = 10;

	float twoTokenMultiplier = 1.5;

	float synonymMultiplier = 1.0;
	float identifierMultiplier = 1.0;
	float integerMultiplier = 0.3;
	float underscoreMultiplier = 2;
	float underscoreExpMultiplier = 1.5;
	float exprMultiplier = 1;


	// cout<<"In orderRelationships"<<endl;

	vector<float> weightArr (r.size(),0);

	for(unsigned int i=0; i<r.size(); i++){
		Relationship currentRel = r.at(i);
		//Give weight based on the relationship type
		switch(currentRel.getRelType()){
		case Relationship::FOLLOWS:
			weightArr[i]=followsWeight;

		case Relationship::FOLLOWSSTAR:
			weightArr[i]=followsStarWeight;

		case Relationship::PARENT:
			weightArr[i]=parentWeight;

		case Relationship::PARENTSTAR:
			weightArr[i]=parentStarWeight;

		case Relationship::CALLS:
			weightArr[i]=callsWeight;

		case Relationship::CALLSSTAR:
			weightArr[i]=callStarWeight;

		case Relationship::MODIFIES:
			weightArr[i]=modifiesWeight;

		case Relationship::USES:
			weightArr[i]=usesWeight;

		case Relationship::NEXT:
			weightArr[i]=nextWeight;

		case Relationship::NEXTSTAR:
			weightArr[i]=nextStarWeight;

		case Relationship::WITH:
			weightArr[i]=withWeight;

		case Relationship::PATTERN:	
			weightArr[i]=patternWeight;

		case Relationship::AFFECTS:
			weightArr[i]=affectsWeight;

		case Relationship::AFFECTSSTAR:
			weightArr[i]=affectsStarWeight;

		case Relationship::SIBLING:
			weightArr[i]=siblingWeight;
		}

		//multiply based on token
		switch(currentRel.getToken1Type()){
		case Relationship::SYNONYM:
			weightArr[i]*=synonymMultiplier;

		case Relationship::IDENTIFIER:
			weightArr[i]*=identifierMultiplier;

		case Relationship::INTEGER:
			weightArr[i]*=integerMultiplier;

		case Relationship::UNDERSCORE:
			weightArr[i]*=underscoreMultiplier;

		case Relationship::UNDERSCOREEXPR:
			weightArr[i]*=underscoreExpMultiplier;

		case Relationship::EXPR:
			weightArr[i]*=exprMultiplier;
		}

		switch(currentRel.getToken2Type()){
		case Relationship::SYNONYM:
			weightArr[i]*=synonymMultiplier;

		case Relationship::IDENTIFIER:
			weightArr[i]*=identifierMultiplier;

		case Relationship::INTEGER:
			weightArr[i]*=integerMultiplier;

		case Relationship::UNDERSCORE:
			weightArr[i]*=underscoreMultiplier;

		case Relationship::UNDERSCOREEXPR:
			weightArr[i]*=underscoreExpMultiplier;

		case Relationship::EXPR:
			weightArr[i]*=exprMultiplier;
		}
	}

	//order based on weight
	vector<Relationship> newOrder;
	while(r.size()>0){
		float minWeight = weightArr.at(0);
		int minWeightIndex = 0;
		for(int j =1; j<weightArr.size();j++){
			if(minWeight>weightArr.at(j)){
				minWeightIndex = j;
				minWeight = weightArr.at(j);
			}
		}
		newOrder.push_back(r.at(minWeightIndex));
		weightArr.erase(weightArr.begin()+minWeightIndex);
		r.erase(r.begin()+minWeightIndex);
	}
	r =newOrder;


	for(unsigned int i=0; i<r.size(); i++){
		if(r.at(i).getRelType()==Relationship::PATTERN){
			// cout<<"pattern found"<<endl;
			temp = r.at(sorted);
			r.at(sorted) = r.at(0);
			r.at(0) = temp;
			sorted++;
		}
		else if((!isalpha(r.at(i).getToken1()[0]) || !isalpha(r.at(i).getToken2()[0])) && r.at(i).getRelType()!=Relationship::WITH){
			// cout<<"relationships with only one alpha token found"<<endl;
			temp = r.at(sorted);
			r.at(sorted) = r.at(i);
			r.at(i) = temp;
			sorted++;
		} else if(r.at(i).getRelType() == Relationship::WITH){
			// cout<<"with relationship found"<<endl;
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

	// cout<<"After Ordering Relations, r.size = "<<r.size()<<endl;
	return r;
}

unordered_map<int, vector<Pair>> QueryEvaluator::evaluateQuery(Query q, vector<Relationship> *newRelations){
	cout<<"Start Query Evaluator"<<endl;
	//Get relationships and order them
	vector<Relationship> relations = q.getRelVect();
	linkages.clear();
	relAns.clear();
	relParameters.clear();
	nextStarTable.clear();

	// cout<<"Ordering Relationships"<<endl;
	relations = orderRelationship(relations);
	*newRelations = relations;

	// cout<<"Initializing Variables"<<endl;
	unordered_map<string, TypeTable::SynType> m = q.getSynTable();
	vector<string> selectedSyn = q.getSelectedSyn();
	unordered_map<string, vector<int>> answers;

	//If relations is empty
	if(relations.empty()){
		// cout<<"Relations found empty"<<endl;
		for(vector<string>::iterator it = selectedSyn.begin(); it!=selectedSyn.end(); it++){
			set<int> synAns;
			
			if(m.find(*it)->second==TypeTable::VARIABLE){
				synAns = pkb->getAllVarIndex();
			}else if(m.find(*it)->second==TypeTable::PROCEDURE){
				synAns = pkb->getAllProcIndexes();
			}else if(m.find(*it)->second== TypeTable::CONSTANT){
				synAns = pkb->getAllConstIndex();
			}else{
				synAns = pkb->getAllStmts(m.find(*it)->second);

			}
			vector<int> pairAns;
			copy(synAns.begin(), synAns.end(), back_inserter(pairAns));
			answers.insert(make_pair<string, vector<int>>(*it, pairAns));
		}

		//return answers;
	}

	//If relations are not empty
	int relIndex = 0;
	for(vector<Relationship>::iterator it = relations.begin(); it!=relations.end(); it++){
		if (AbstractWrapper::GlobalStop) {
			// cout<< "Timeout detected! Stopping QueryEvaluator!" << endl;
			affectsTable.clear();
			affectsStarTable.clear();
			nst.clear();
			return relAns;
		}

		// cout<<" "<<endl;
		// cout<<it->getRelName()<<"("<<it->getToken1()<<", "<< it->getToken2()<<")"<<endl;

		if(isalpha(it->getToken1()[0]) && isalpha(it->getToken2()[0]) && it->getToken1()==it->getToken2()){
			if(it->getRelType()!=Relationship::NEXT){
				answers.clear();
				//return answers;
			}
		}
		switch(it->getRelType()){
		case Relationship::FOLLOWS:
			// cout<<"\n EVALUATING FOLLOWS ("<<it->getToken1()<<" "<<it->getToken2()<<")"<<endl;
			evaluateFollows(*it, m,relIndex); break;

		case Relationship::FOLLOWSSTAR:
			// cout<<"\n EVALUATING FOLLOWS* ("<<it->getToken1()<<" "<<it->getToken2()<<")"<<endl;
			evaluateFollowsStar(*it, m, relIndex); break;

		case Relationship::PARENT:
			// cout<<"\n EVALUATING PARENT ("<<it->getToken1()<<" "<<it->getToken2()<<")"<<endl;
			evaluateParent(*it, m, relIndex); break;

		case Relationship::PARENTSTAR:
			// cout<<"\n EVALUATING PARENT* ("<<it->getToken1()<<" "<<it->getToken2()<<")"<<endl;
			evaluateParentStar(*it, m, relIndex); break;//review

		case Relationship::CALLS:
			// cout<<"\n EVALUATING CALLS ("<<it->getToken1()<<" "<<it->getToken2()<<")"<<endl;
			evaluateCalls(*it, relIndex); break;

		case Relationship::CALLSSTAR:
			// cout<<"\n EVALUATING CALLS* ("<<it->getToken1()<<" "<<it->getToken2()<<")"<<endl;
			evaluateCallsStar(*it, relIndex); break;

		case Relationship::MODIFIES:
			// cout<<"\n EVALUATING MODIFIES ("<<it->getToken1()<<" "<<it->getToken2()<<")"<<endl;
			evaluateModifies(*it, m, relIndex); break;

		case Relationship::USES:
			// cout<<"\n EVALUATING USES ("<<it->getToken1()<<" "<<it->getToken2()<<")"<<endl;
			evaluateUses(*it, m, relIndex); break;

		case Relationship::NEXT:
			// cout<<"\n EVALUATING NEXT ("<<it->getToken1()<<" "<<it->getToken2()<<")"<<endl;
			evaluateNext(*it, m, relIndex); break;

		case Relationship::NEXTSTAR:
			// cout<<"\n EVALUATING NEXT* ("<<it->getToken1()<<" "<<it->getToken2()<<")"<<endl;
			evaluateNextStar(*it, m, relIndex); break;

		case Relationship::WITH:
			// cout<<"\n EVALUATING WITH ("<<it->getToken1()<<" "<<it->getToken2()<<")"<<endl;
			evaluateWith(*it, m, relIndex); break;

		case Relationship::PATTERN:	
			// cout<<"\n EVALUATING PATTERN"<<endl;
			evaluatePattern(*it, m, relIndex); break;

		case Relationship::AFFECTS:
			// cout<<"\n EVALUATING AFFECTS"<<endl;
			evaluateAffects(*it, m, relIndex); break;

		case Relationship::AFFECTSSTAR:
			// cout<<"\n EVALUATING AFFECTSSTAR"<<endl;
			evaluateAffectsStar(*it, m , relIndex); break;
			
		case Relationship::SIBLING:
			// cout<<"\n EVALUATING SIBLING"<<endl;
			evaluateSibling(*it, m, relIndex); break;
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

		// cout<<"Inserting tokens into relParameters"<<endl;
		relParameters.insert(make_pair<int, vector<string>>(relIndex, parametersVec));
		relIndex++;
	}

	//If one of the relations are evaluated to false or empty
	for(unsigned int i=0; i<relations.size(); i++){
		vector<Pair> v = relAns.find(i)->second;
		if(v.empty() || v.at(0).ans1==-2){
			// cout<<"Found Relations to be False or Empty"<<endl;
			//return answers;
		}
	}

	for(vector<string>::iterator it = selectedSyn.begin(); it!=selectedSyn.end(); it++){
		// cout<<"Iterating Selected Syn"<<endl;

		set<int> synAns;
		vector<int> synAnsVec;
		if(linkages.find(*it)!=linkages.end()){
			int index;
			vector<string> param;
			index = (linkages.find(*it)->second).at(0);
			param = relParameters.find(index)->second;

			vector<Pair> p = relAns.at(index);
		
			// cout<<"token in selectedSyn = "<<*it<<" p.size = "<<p.size()<<endl;
			// cout<<"FIRST PARAM = "<<param.at(0)<<endl;
			if(*it==param.at(0)){
				for(vector<Pair>::iterator it2 = p.begin(); it2!=p.end(); it2++){
					synAns.insert(it2->ans1);
					// cout<<"it2->ans1 = "<<it2->ans1<<endl;
				}

			}else {
				// cout<<"SECOND PARAM = "<<param.at(1)<<endl;
				for(vector<Pair>::iterator it2 = p.begin(); it2!=p.end(); it2++){
					synAns.insert(it2->ans2);
					// cout<<"it2->ans2 = "<<it2->ans2<<endl;
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
	/*
	set<int> cc = retrieveTokenEvaluatedAnswers("p");
	// cout<<"IS SET EMPTY: "<<cc.empty()<<endl;
	for(set<int>::iterator xx = cc.begin(); xx!=cc.end(); xx++){
		// cout<<*xx<<endl;
	}*/

	affectsTable.clear();
	affectsStarTable.clear();
	nst.clear();


	// cout<<"RETURNING FINAL ANSWERS"<<endl;
	cout<<"End Query Evaluator"<<endl;
	return relAns;
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
	// cout<<"In retrieveTokenEvaluatedAnswers Finding tk = "<<tk<<endl;
	vector<int> listOfRel = linkages.find(tk)->second;
	vector<Pair> ans = QueryEvaluator::relAns.find(listOfRel.at(0))->second;
	// cout<<"Retrieving Token Evaluated Answers with first relationship index = "<<listOfRel.at(0)<<endl;
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

	// cout<<"PRINTING ELEMENTS OF RETRIEVED TOKEN: "<<endl;
	for(set<int>::iterator it = setAns.begin(); it!=setAns.end(); it++){
		// cout<<*it<<endl;
	}
	// cout<<"End retrieving token"<<endl;
	return setAns;
}

void QueryEvaluator::intersectPairs(string tk1, string tk2, vector<Pair> *ans, int relIndex){
		//If both a and b exist in QueryEvaluator::linkages
	if(isExistInLinkages(tk1) && isExistInLinkages(tk2)){
		// cout<<"Both tk1 and tk2 Exists tk1 = "<<tk1<<" tk2 = " <<tk2<<endl;
		removePairsFromRelAns(ans, tk1, 1);
		removePairsFromRelAns(ans, tk2, 2);
		removePairs(*ans, tk1, 1);
		removePairs(*ans, tk2, 2);
	}

	//If only a exist
	else if(isExistInLinkages(tk1)){
		// cout<<"IntersectPairs tk1 Exists tk1 = "<<tk1<<endl;
		removePairsFromRelAns(ans, tk1, 1);
		removePairs(*ans, tk1, 1);
		//insertLinks(tk1, relIndex);
	}

	//If only b exist
	else if(isExistInLinkages(tk2)){
		// cout<<"IntersectPairs tk2 Exists tk2 = "<<tk2<<endl;
		removePairsFromRelAns(ans, tk2, 2);
		removePairs(*ans, tk2, 2);
	}

	else {
		// cout<<"In intersect Pairs: both do not exist"<<endl;
	}

	
	if(isalpha(tk1[0])){
		// cout<<"Insert links for tk1 =" <<tk1<<endl;
		insertLinks(tk1, relIndex);
	}
	
	if(isalpha(tk2[0])){
		// cout<<"Insert links for tk2 = "<<tk2<<endl;
		insertLinks(tk2, relIndex);
	}
}

void QueryEvaluator::insertLinks(string tk, int relIndex){
	//Add the relationship into QueryEvaluator::linkages
	// cout<<"--INSERTING "<<tk<<"--"<<endl;
	//if tk exists
	if(linkages.find(tk) != linkages.end()){
		// cout<<tk<<" Found in Linkages"<<endl;
		vector<int> *pt = &QueryEvaluator::linkages.find(tk)->second;
		pt->push_back(relIndex);
	}
	else {
		// cout<<tk<<" Not Found in Linkages and relIndex = "<<relIndex<<endl;
		vector<int> relIndexes;
		relIndexes.push_back(relIndex);
		linkages.insert(make_pair(tk, relIndexes));
	}
	// cout<<"--END OF INSERT--"<<endl;
}

void QueryEvaluator::removePairsFromRelAns(vector<Pair> * relationsAns, string tk, int pairIndex){
	// cout<<"--REMOVE PAIRS FROM REL ANS START--"<<endl;
	//Retrieve the set of int of the token that was evaluated
	set<int> s = retrieveTokenEvaluatedAnswers(tk);
	//Delete it from the ans pairs made
	/*
	for(vector<Pair>::iterator it = relationsAns->begin(); it!=relationsAns->end(); it++){
		// cout<<it->ans2<<endl;
	}*/

	for(vector<Pair>::iterator it = relationsAns->begin(); it!=relationsAns->end();){
		if(pairIndex==1){
			//if ans from relationsAns is not found in the set, remove it
			if(s.find(it->ans1)==s.end()){
				it = relationsAns->erase(it);
			}
			else{
				++it;
			}
		}
		else {
			if(s.find(it->ans2)==s.end()){
				it = relationsAns->erase(it);
			}
			else{
				++it;
			}
		}
	}

	// cout<<"--REMOVE PAIRS FROM RELANS END--"<<endl;
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
	case TypeTable::PROCEDURE:
		return "procedure";
	case TypeTable::CALL:
		return "call";
	case TypeTable::VARIABLE:
		return "variable";
	case TypeTable::BOOLEAN:
		return "boolean";
	}
	return "null";
}

void QueryEvaluator::removePairs(vector<Pair> p, string token, int i){
	// cout<<"\n---START REMOVE PAIRS METHOD---"<<endl;
	int pairIndex;
	vector<int> listOfRel = linkages.find(token)->second;
	set<int> list;
	if(i==1){
		for(vector<Pair>::iterator iter=p.begin(); iter!=p.end(); iter++){
			list.insert(iter->ans1);
			//// cout<<"Inserting "<<iter->ans1<<endl;
		}
	}
	else{
		for(vector<Pair>::iterator iter=p.begin(); iter!=p.end(); iter++){
			list.insert(iter->ans2);
			//// cout<<"Inserting "<<iter->ans2<<endl;
		}
	}

	//iterate through all the relations that evaluated the token
	for(vector<int>::iterator it=listOfRel.begin(); it!=listOfRel.end(); it++){
		// cout<<"RelIndex of clause with contents being removed: "<<*it<<endl;
		unordered_map<int, vector<Pair>>::iterator i = relAns.find(*it);
		vector<Pair> *pr = &i->second;
		int index = relAns.find(*it)->first;

		//find out whether the token is the first or second argument of the relationship
		if(relParameters.find(index)->second.at(0)==token){
			// cout<<"PairIndex: 1"<<endl;
			pairIndex=1;
		}
		else{
			// cout<<"PairIndex: 2"<<endl;
			pairIndex=2;
		}

		//iterate through the relationship pairs
		for(vector<Pair>::iterator it2=pr->begin(); it2!=pr->end();){

			//remove all pairs that are eliminated
			if(pairIndex==1){
				if(find(list.begin(),list.end(),it2->ans1)==list.end()){
					// cout<<"Erasing element "<<it2->ans2<<endl;
					it2 = pr->erase(it2);
				} else{
					++it2;
				}
			}else{
				if(find(list.begin(),list.end(),it2->ans2)==list.end()){
					// cout<<"Erasing element "<<it2->ans2<<endl;
					it2 = pr->erase(it2);
				} else{
					++it2;
				}
			}
		}
		/*
		for(vector<Pair>::iterator ii = pr->begin(); ii!=pr->end(); ii++){
			// cout<<"Left element "<<ii->ans1<<endl;
		}*/
	}
}

bool QueryEvaluator::isStmtType(TypeTable::SynType t){
	if(t == TypeTable::STMT || t == TypeTable::ASSIGN || t == TypeTable::WHILE || t == TypeTable::IF || t == TypeTable::CALL)
		return true;
	else
		return false;
}

bool QueryEvaluator::isOperator(TypeTable::SynType t){
	if(t == TypeTable::PLUS || t == TypeTable::MINUS || t == TypeTable::TIMES){
		return true;
	}else{
		return false;
	}
}

bool QueryEvaluator::isConstOrVar(TypeTable::SynType t){
	if(t == TypeTable::CONSTANT || t == TypeTable::VARIABLE){
		return true;
	}else{
		return false;
	}
}
void QueryEvaluator::evaluateSibling(Relationship r, unordered_map<string, TypeTable::SynType> m, int relIndex){
	
	string tk1 = r.getToken1();
	string tk2 = r.getToken2();
	set<int> tk1List;
	set<int> tk2List;
	bool flag = false;
	unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(tk1);
	unordered_map<string, TypeTable::SynType>::iterator i2 = m.find(tk2);

	if(isExistInLinkages(tk1)){
		tk1List = retrieveTokenEvaluatedAnswers(tk1);
	}else {
		if(i1->second == TypeTable::PROCEDURE){
			tk1List = pkb->getAllProcIndexes();
		}else if(i1->second == TypeTable::CONSTANT){
			tk1List = pkb->getAllConstIndex();
		}else if(i1->second == TypeTable::VARIABLE){
			tk1List = pkb->getAllVarIndex();
		}else if(i1->second == TypeTable::PLUS || i1->second == TypeTable::MINUS || i1->second == TypeTable::TIMES){
			flag = true;
		}else {
			tk1List = pkb->getAllStmts(i1->second);
		}
	}

	if(isExistInLinkages(tk2)){
		tk2List = retrieveTokenEvaluatedAnswers(tk2);
	}else {
		if(i2->second == TypeTable::PROCEDURE){
			tk2List = pkb->getAllProcIndexes();
		}else if(i2->second == TypeTable::CONSTANT){
			tk2List = pkb->getAllConstIndex();
		}else if(i2->second == TypeTable::VARIABLE){
			tk2List = pkb->getAllVarIndex();
		}else if(i2->second == TypeTable::PLUS || i2->second == TypeTable::MINUS || i2->second == TypeTable::TIMES){
			flag = true;
		}else {
			tk2List = pkb->getAllStmts(i2->second);
		}
	}

	set<Pair> siblingAns;

	//Sibling(s1,s2)
	if(r.getToken1Type()==Relationship::SYNONYM && r.getToken2Type()==Relationship::SYNONYM){
		
		//Sibling(p1, p2)
		if(i1->second == TypeTable::PROCEDURE && i2->second == TypeTable::PROCEDURE){
			for(set<int>::iterator i = tk1List.begin(); i!=tk1List.end(); i++){
				for(set<int>::iterator i2 = tk2List.begin(); i2!=tk2List.end(); i2++){
					if(pkb->isSiblingProcIndexProcIndex(*i, *i2)){
						siblingAns.insert(Pair(*i, *i2));
					}
				}
			}
		}

		//Sibling(stmtlst, stmtlst)
		else if(i1->second == TypeTable::STMTLST && i2->second == TypeTable::STMTLST){
			for(set<int>::iterator i = tk1List.begin(); i!=tk1List.end(); i++){
				for(set<int>::iterator i2 = tk2List.begin(); i2!=tk2List.end(); i2++){
					if(pkb->isSiblingStmtListStmtList(*i, *i2)){
						siblingAns.insert(Pair(*i, *i2));
					}
				}
			}
		}

		//Sibling(stmt,stmt)
		else if(isStmtType(i1->second) && isStmtType(i2->second)){
			for(set<int>::iterator i = tk1List.begin(); i!=tk1List.end(); i++){
				for(set<int>::iterator i2 = tk2List.begin(); i2!=tk2List.end(); i2++){
					if(pkb->isSiblingStmtNumStmtNum(*i, *i2)){
						siblingAns.insert(Pair(*i, *i2));
					}
				}
			}
		}

		//Sibling(stmtlst, variable)
		else if((i1->second == TypeTable::STMTLST && i2->second == TypeTable::VARIABLE) || (i2->second == TypeTable::STMTLST && i1->second == TypeTable::VARIABLE)){
			if(i1->second == TypeTable::STMTLST){
				for(set<int>::iterator i = tk1List.begin(); i!=tk1List.end(); i++){
					for(set<int>::iterator i2 = tk2List.begin(); i2!=tk2List.end(); i2++){
						if(pkb->isSiblingVarIndexStmtList(*i2, *i)){
							siblingAns.insert(Pair(*i2, *i));
						}
					}
				}
			}else{
				for(set<int>::iterator i = tk1List.begin(); i!=tk1List.end(); i++){
					for(set<int>::iterator i2 = tk2List.begin(); i2!=tk2List.end(); i2++){
						if(pkb->isSiblingVarIndexStmtList(*i, *i2)){
							siblingAns.insert(Pair(*i, *i2));
						}
					}
				}
			}
		}

		//Sibling(op, op)
		else if(isOperator(i1->second) && isOperator(i2->second)){
			if(pkb->isSiblingMathOpMathOp(i1->second, i2->second)){
				siblingAns.insert(Pair(-1,-1));
			}
		}

		else if(isOperator(i1->second) && isConstOrVar(i2->second) || isOperator(i2->second) || isConstOrVar(i1->second)){
			if(isOperator(i1->second) && i2->second == TypeTable::VARIABLE){
				for(set<int>::iterator i = tk2List.begin(); i!=tk2List.end(); i++){
					if(pkb->isSiblingVarIndexMathOp(*i, i1->second)){
						siblingAns.insert(Pair(-1, *i)); //-1 cuz operator will nvr be selected
					}
				}
			}else if(isOperator(i2->second) && i1->second == TypeTable::VARIABLE){
				for(set<int>::iterator i = tk1List.begin(); i!=tk1List.end(); i++){
					if(pkb->isSiblingVarIndexMathOp(*i, i1->second)){
						siblingAns.insert(Pair(*i, -1)); //-1 cuz operator will nvr be selected
					}
				}
			}else if(isOperator(i1->second) && i2->second == TypeTable::CONSTANT){
				for(set<int>::iterator i = tk2List.begin(); i!=tk2List.end(); i++){
					if(pkb->isSiblingConstantMathOp(*i, i1->second)){
						siblingAns.insert(Pair(-1, *i)); //-1 cuz operator will nvr be selected
					}
				}
			}else{
				for(set<int>::iterator i = tk1List.begin(); i!=tk1List.end(); i++){
					if(pkb->isSiblingConstantMathOp(*i, i1->second)){
						siblingAns.insert(Pair(*i, -1)); //-1 cuz operator will nvr be selected
					}
				}
			}
		}

		else if(i1->second == TypeTable::CONSTANT && i2->second == TypeTable::CONSTANT){
			for(set<int>::iterator i = tk1List.begin(); i!=tk1List.end(); i++){
				for(set<int>::iterator i2 = tk2List.begin(); i2!=tk2List.end(); i2++){
					if(pkb->isSiblingConstantConstant(*i, *i2)){
						siblingAns.insert(Pair(*i, *i2));
					}
				}
			}
		}

		else if(i1->second == TypeTable::VARIABLE && i2->second == TypeTable::VARIABLE){
			for(set<int>::iterator i = tk1List.begin(); i!=tk1List.end(); i++){
				for(set<int>::iterator i2 = tk2List.begin(); i2!=tk2List.end(); i2++){
					if(pkb->isSiblingVarIndexVarIndex(*i, *i2)){
						siblingAns.insert(Pair(*i, *i2));
					}
				}
			}
		}

		else if(i1->second == TypeTable::VARIABLE && i2->second == TypeTable::CONSTANT){
			for(set<int>::iterator i = tk1List.begin(); i!=tk1List.end(); i++){
				for(set<int>::iterator i2 = tk2List.begin(); i2!=tk2List.end(); i2++){
					if(pkb->isSiblingVarIndexConstant(*i, *i2)){
						siblingAns.insert(Pair(*i, *i2));
					}
				}
			}
		}

		else if(i1->second == TypeTable::CONSTANT && i2->second == TypeTable::VARIABLE){
			for(set<int>::iterator i = tk1List.begin(); i!=tk1List.end(); i++){
				for(set<int>::iterator i2 = tk2List.begin(); i2!=tk2List.end(); i2++){
					if(pkb->isSiblingVarIndexConstant(*i, *i2)){
						siblingAns.insert(Pair(*i2, *i));
					}
				}
			}
		}

		else{

		}
	}

	//Sibling(alpha, _) Sibling(alpha, 4) Sibling(alpha, "x") Sibling(alpha, "proc")
	else if(r.getToken1Type()==Relationship::SYNONYM){

		//Sibling(alpha, "proc")
		if(i1->second==TypeTable::PROCEDURE){
			string procname = tk2.substr(1,tk2.length()-2);
			for(set<int>::iterator it = tk1List.begin(); it!=tk1List.end(); it++){
				if(pkb->isSiblingProcIndexProcIndex(*it, pkb->getProcIndex(tk2))){
					siblingAns.insert(Pair(*it, pkb->getProcIndex(tk2)));
				}
			}
		}

		else if(i1->second == TypeTable::STMTLST){
			//Sibling(stmtlst, 4)
			if(isdigit(tk2[0])){
				for(set<int>::iterator it = tk1List.begin(); it!=tk1List.end(); it++){
					if(pkb->isSiblingStmtListStmtList(*it, atoi(tk2.c_str()))){
						siblingAns.insert(Pair(*it, atoi(tk2.c_str())));
					}
				}
			}
			
			//Sibling(stmtlst, "x")
			else{
				string varname = tk2.substr(1,tk2.length()-2);
				for(set<int>::iterator it = tk1List.begin(); it!=tk1List.end(); it++){
					if(pkb->isSiblingVarIndexStmtList(pkb->getVarIndex(varname), *it)){
						siblingAns.insert(Pair(*it, pkb->getVarIndex(varname)));
					}
				}
			}
		}

		//Sibling(stmt, 5)
		else if(i1->second == TypeTable::STMT){
			if(isdigit(tk2[0])){
				for(set<int>::iterator it = tk1List.begin(); it!=tk1List.end(); it++){
					if(pkb->isSiblingStmtNumStmtNum(*it, atoi(tk2.c_str()))){
						siblingAns.insert(Pair(*it, atoi(tk2.c_str())));
					}
				}
			}else{

			}
		}
	}


}

void QueryEvaluator::evaluateWith(Relationship r, unordered_map<string, TypeTable::SynType> m, int relIndex){
	// cout<<"\n---START EVALUATE WITH METHOD---"<<endl;
	// cout<<"Relationship Index: "<<relIndex<<endl;
	//Retrieve the two with syns
	string tk1 = r.getToken1();
	string tk2 = r.getToken2();

	// cout<<"r.tk1: "<<tk1<<endl;
	// cout<<"r.tk2: "<<tk2<<endl;
	vector<Pair> withAns;

	unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(tk1);
	unordered_map<string, TypeTable::SynType>::iterator i2 = m.find(tk2);
	

	//with v1.varName = p.procName with c.value = s.stmt# = pr.progline
	if(isalpha(tk1[0]) && isalpha(tk2[0])){
		// cout<<"2 alpha tokens found"<<endl;
		set<int> a;
		set<int> b;
		if(isExistInLinkages(tk1)){
			// cout<<"tk1 exist in linkages"<<endl;
			a = retrieveTokenEvaluatedAnswers(tk1);
		}else {
			// cout<<"tk1 does not exist in linkages"<<endl;
			if(i1->second==TypeTable::PROCEDURE){
				// cout<<"getting all proc indexes"<<endl;
				a = pkb->getAllProcIndexes();
			}else if(i1->second == TypeTable::VARIABLE){
				// cout<<"getting all var indexes"<<endl;
				a = pkb->getAllVarIndex();
			}else if(i1->second == TypeTable::CONSTANT){
				set<int> c = pkb->getAllConstIndex();
				// cout<<"getting all constants"<<endl;
				for(set<int>::iterator iti = c.begin(); iti!=c.end(); iti++){
					a.insert(atoi((pkb->getConstValue(*iti)).c_str()));
				}
			}else if(i1->second == TypeTable::CALL){
				if(r.getCallSynType() == TypeTable::PROCEDURE){
					a = pkb->getAllCalled();
					// cout<<"getting all called procedures"<<endl;
				}else {
					// cout<<"getting all call stmts"<<endl;
					a = pkb->getAllCallStmt();
				}
			}else {
				// cout<<"getting all stmts"<<endl;
				a = pkb->getAllStmts(i1->second);
			}
		}

		if(isExistInLinkages(tk2)){
			// cout<<"tk2 exist in linkages"<<endl;
			b = retrieveTokenEvaluatedAnswers(tk2);
		}else{
			if(i2->second==TypeTable::PROCEDURE){
				// cout<<"getting all proc indexes"<<endl;
				b = pkb->getAllProcIndexes();
			}else if(i2->second == TypeTable::VARIABLE){
				// cout<<"getting all var indexes"<<endl;
				b = pkb->getAllVarIndex();
			}else if(i2->second == TypeTable::CONSTANT){
				set<int> c = pkb->getAllConstIndex();
				// cout<<"getting all constants"<<endl;
				for(set<int>::iterator iti = c.begin(); iti!=c.end(); iti++){
					b.insert(atoi((pkb->getConstValue(*iti)).c_str()));
				}
			}else if(i1->second == TypeTable::CALL){
				if(r.getCallSynType() == TypeTable::PROCEDURE){
					// cout<<"getting all called procedures"<<endl;
					b = pkb->getAllCalled();
				}else {
					// cout<<"getting all call stmts"<<endl;
					b = pkb->getAllCallStmt();
				}
			}else {
				// cout<<"getting all stmts"<<endl;
				b = pkb->getAllStmts(i2->second);
			}
		}

		//else if the two tokens are of different type and of proc and var
			//v.varName = p.procName OR p.procName = v.varName
		if((i1->second == TypeTable::PROCEDURE && i1->second!=i2->second && i1->second!=r.getCallSynType()) || (i1->second == TypeTable::VARIABLE && i1->second!=i2->second)|| (i1->second==TypeTable::CALL && r.getCallSynType()!=i2->second)){
			// cout<<"tk1 type != tk2 type and tk1 type =variable OR procedure"<<endl;
			set<string> procNames;
			set<string> varNames;

			//p.procName = v.varName
			if(i1->second == TypeTable::PROCEDURE || i1->second==TypeTable::CALL){
				for(set<int>::iterator it = a.begin(); it!=a.end(); it++){
					// cout<<"pushing back procName "<<pkb->getProcName(*it)<<endl;
					procNames.insert(pkb->getProcName(*it));
				}
				for(set<int>::iterator it2 = b.begin(); it2!=b.end(); it2++){
					// cout<<"pushing back varName "<<pkb->getVarName(*it2)<<endl;
					varNames.insert(pkb->getVarName(*it2));
				}
			}
			//v.varName = p.procName
			else if(i1->second == TypeTable::VARIABLE){
				for(set<int>::iterator it = a.begin(); it!=a.end(); it++){
					if(pkb->getVarName(*it)!="-1"){
						// cout<<"pushing back varName "<<*it<<endl;
						varNames.insert(pkb->getVarName(*it));
					}
				}
				for(set<int>::iterator it2 = b.begin(); it2!=b.end(); it2++){
					if(pkb->getProcName(*it2)!="-1"){
						// cout<<"pushing back procName "<<*it2<<endl;
						procNames.insert(pkb->getProcName(*it2));
					}
				}
			}

			vector<string> intersect;
			set_intersection(procNames.begin(), procNames.end(), varNames.begin(), varNames.end(), back_inserter(intersect));
			vector<Pair> ansProc;
			vector<Pair> ansVar;
			// cout<<"intersect is empty: "<<intersect.empty()<<endl;
			for(vector<string>::iterator it = intersect.begin(); it!=intersect.end(); it++){
				if(i1->second == TypeTable::VARIABLE){
					if(i2->second==TypeTable::CALL){
						set<int> stmts = pkb->getCallStmt(pkb->getProcIndex(*it));
						for(set<int>::iterator iter = stmts.begin(); iter!=stmts.end(); iter++){
							withAns.push_back(Pair (pkb->getVarIndex(*it), *iter));
						}
					}else{
						// cout<<"Pushing var and proc "<<*it <<endl;
						withAns.push_back(Pair (pkb->getVarIndex(*it), pkb->getProcIndex(*it)));
					}
				}else {
					if(i1->second==TypeTable::CALL){
						set<int> stmts = pkb->getCallStmt(pkb->getProcIndex(*it));
						for(set<int>::iterator iter = stmts.begin(); iter!=stmts.end(); iter++){
							withAns.push_back(Pair ( *iter, pkb->getVarIndex(*it)));
						}
					}else{
						// cout<<"Pushing var and proc  "<< *it <<endl;
						withAns.push_back(Pair (pkb->getProcIndex(*it), pkb->getVarIndex(*it)));
					}
					
				}
			}

		}

		//else	
		else{
			set<int> intersect;
			set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::inserter(intersect, intersect.begin()));

			for(set<int>::iterator iter = intersect.begin(); iter!=intersect.end(); iter++){
				withAns.push_back(Pair (*iter, *iter));
			}
		}

	}

	else if((isdigit(tk1[0]) && isdigit(tk2[0])) || (tk1[0]=='\"' && tk2[0]=='\"')){
		if(tk1==tk2){
			withAns.push_back(Pair(-1,-1));
		}else{
			//withAns.push_back(Pair(-2,-2));
		}
	}
	//with v.varName = "x" with p.procName = "Third"
	else {
		string dum;
		// cout<<"only 1 alpha token found"<<endl;
		//if exist in links then delete all unnecessary tuples then push into QueryEvaluator::relAns true
		if(!isdigit(tk2[0])){ //if the query is with c.value = 3 then we do not have to remove the quotation marks
			dum = tk2.substr(1,tk2.length()-2);
		}

		int index = -1;
		// cout<<convertEnumToString(i1->second)<<endl;
		// cout<<convertEnumToString(r.getCallSynType())<<endl;
		if(i1->second==TypeTable::VARIABLE){
			// cout<<"First token VARIABLE"<<endl;
			index = pkb->getVarIndex(dum);
			// cout<<"tk2 = "<<tk2<<" index = "<<index<<endl;
		}else if(i1->second==TypeTable::PROCEDURE || (i1->second==TypeTable::CALL && r.getCallSynType()==TypeTable::PROCEDURE)){
			if(i1->second==TypeTable::PROCEDURE){
				// cout<<"First token PROCEDURE"<<endl;
				index = pkb->getProcIndex(dum);
				// cout<<"tk2 = "<<tk2 <<" index = "<<index<<endl;
			} else{
				// cout<<"call.procName"<<endl;
				set<int> callstmts = pkb->getCallStmt(pkb->getProcIndex(dum));
				// cout<<"procedure name is "<<dum<<endl;
				// cout<<"procedure index is "<<pkb->getProcIndex(dum)<<endl;
				// cout<<"callstmts is empty: "<<callstmts.empty()<<endl;
				for(set<int>::iterator x = callstmts.begin(); x!=callstmts.end(); x++){
					withAns.push_back(Pair(*x, *x));
					// cout<<"Pushing back "<<*x<<endl;
				}
			}
		} else{
			// cout<<"First token NEITHER VAR NOR PROC"<<endl;
			index = atoi(tk2.c_str());
			// cout<<"Index: "<<index<<endl;
			if(i1->second==TypeTable::STMT){
				int range = pkb->getStmtRange();
				if(range<index){
					index = -1;
				}
			}
			else if(i1->second==TypeTable::CALL){
				if(!pkb->isSynType(TypeTable::CALL, index)){
					index=-1;
				}
			}
			else if(i1->second==TypeTable::CONSTANT){
				if(pkb->getConstIndex(tk2)==-1){
					index = -1;
				}
			}
			else{
				if(!pkb->isSynType(i1->second, index)){
					index = -1;
				}
			}
		}

		if(index!=-1)
			withAns.push_back(Pair (index, index));

	}
	intersectPairs(tk1,tk2,&withAns,relIndex);
	relAns.insert(make_pair<int, vector<Pair>>(relIndex, withAns));
	// cout<<"---END EVALUATE WITH METHOD---\n"<<endl;
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
		// cout<<"Both Tokens are Alpha"<<endl;
		//If s and a exists, retrieve s and a answers, then isNext
		if(isExistInLinkages(tk1) && isExistInLinkages(tk2)){
			// cout<<"Both Tokens Exist in Linkages"<<endl;
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
			pkb->printNextTable();
			for(set<int>::iterator it= allTk1.begin(); it!=allTk1.end(); it++){
				tk1Ans = pkb->getPrevious(*it);
				for(set<int>::iterator it2 = tk1Ans.begin(); it2!=tk1Ans.end(); it2++){
					if(pkb->isSynType(i1->second,*it2)){
						nextAns.push_back(Pair (*it2, *it));
						// cout<<"Pushing in pairs ("<<*it2<<" "<<*it<<")"<<endl;
					}
				}
			}
		}

		if(tk1==tk2){
			nextAns.clear();
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
			// cout<<"First Token does not Exist"<<endl;
			set<int> va = pkb->getAllStmts(i1->second);

			for(set<int>::iterator it = va.begin(); it!=va.end(); it++){
				// cout<<"Before retrieving getNext it = "<<*it<<endl;
				if(!pkb->getNext(*it).empty()){
					nextAns.push_back(Pair (*it, *pkb->getNext(*it).begin()));
					// cout<<"Pushing in it = "<<*it<<endl;
				}
			}
		}

		insertLinks(tk1, relIndex);
	}

	//Next(_,_)
	else if(tk1=="_" && tk2=="_"){
		set<int> s = pkb->getAllNext();
		if(!s.empty()){
			nextAns.push_back(Pair(-1,-1));
		}else{
		//	nextAns.push_back(Pair(-2,-2));
		}
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
		// cout<<"Second Token is Alpha"<<endl;
		int tk1Int = atoi(tk1.c_str());
		set<int> tk1Vec = pkb->getNext(tk1Int);

		for(set<int>::iterator it = tk1Vec.begin(); it!=tk1Vec.end(); it++){
			// cout<<"Iterating through the vector of GETNEXT(TOKEN1)"<<endl;
			if(pkb->isSynType(i2->second, *it)){
				// cout<<"Pushing into Answer "<<*it<<endl;
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
			//nextAns.push_back(Pair (-2,-2));
		}
		else{
			nextAns.push_back(Pair (-1,-1));
		}
	}

	//Next(3, _)
	else if(isdigit(tk1[0]) && tk2=="_"){
		int tk1Int = atoi(tk1.c_str());
		if(pkb->getNext(tk1Int).empty()){
			//nextAns.push_back(Pair (-2,-2));
		}
		else{
			nextAns.push_back(Pair (-1,-1));
		}
	}

	//Next(3,4)
	else {
		if(pkb->isNext(atoi(tk1.c_str()), atoi(tk2.c_str()))){
			// cout<<"is true"<<endl;
			nextAns.push_back(Pair (-1,-1));
		}else{
			// cout<<"is false"<<endl;
			//nextAns.push_back(Pair (-2, -2));
		}
	}
	pkb->printNextTable();
	relAns.insert(make_pair<int, vector<Pair>>(relIndex, nextAns));
}

void QueryEvaluator::evaluateNextStar(Relationship r, unordered_map<string, TypeTable::SynType> m, int relIndex){
	cout<<"Start Evaluate NextStar"<<endl;
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
		set<int> tk2List;

		if(isExistInLinkages(tk2)){
			tk2List = retrieveTokenEvaluatedAnswers(tk2);
		}else{
			tk2List = pkb->getAllStmts(i2->second);
		}

		if(isExistInLinkages(tk1)){
			tk1List = retrieveTokenEvaluatedAnswers(tk1);
		}else{
			tk1List = pkb->getAllStmts(i1->second);
		}

		//Next*(_, n)
		if(tk1=="_"){
			for(set<int>::iterator it = tk2List.begin(); it!=tk2List.end(); it++){
				if(!pkb->getPrevious(*it).empty()){
					nextStarAns.insert(Pair (-1, *it));
				}
			}
		}
		
		//Next*(n, _)
		else if(tk2=="_"){
			for(set<int>::iterator it = tk1List.begin(); it!=tk1List.end(); it++){
				if(!pkb->getNext(*it).empty()){
					nextStarAns.insert(Pair (*it, -1));
				}
			}
		}
		//Next*(n, n)
		else if(tk1==tk2){
			// cout<<"Token1 and Token2 are equal"<<endl;
			for(set<int>::iterator it = tk1List.begin(); it!=tk1List.end(); it++){
				traverseTable.clear();
				if(nextStarTable.find(*it)!=nextStarTable.end() && nextStarTable.find(*it)->second.find(*it)!=nextStarTable.find(*it)->second.end()){
					// cout<<"non recursive method"<<endl;
					nextStarAns.insert(Pair(*it, *it));
				}else {
					// cout<<"recursive method"<<endl;
					recursiveNextTarget(*it, *it, *it, &nextStarAns, &traverseTable, false);
				}

			}
		}
		//Next*(n1,n2)
		else{
			for(set<int>::iterator it = tk1List.begin(); it!=tk1List.end(); it++){
				for(set<int>::iterator it2 = tk2List.begin(); it2!=tk2List.end(); it2++){
					traverseTable.clear();
					cout<<"it1 " << *it << " it2 "<<*it2<<endl;
					if(nextStarTable.find(*it)!=nextStarTable.end() && nextStarTable.find(*it)->second.find(*it2)!=nextStarTable.find(*it)->second.end()){
						// cout<<"NEXTSTARTABLE("<<*it<<","<<*it2<<")"<<endl;
						nextStarAns.insert(Pair(*it, *it2));
					}else {
						recursiveNextTarget(*it, *it, *it2, &nextStarAns, &traverseTable, false);
					}
				}
			}
		}

		for(set<Pair>::iterator it = nextStarAns.begin(); it!=nextStarAns.end(); it++){
			nextStarAnsVec.push_back(*it);
		}
	}

	else if(tk1=="_" && tk2=="_"){
		set<int> x = pkb->getAllNext();
		if(x.empty()){
			//nextStarAnsVec.push_back(Pair (-2,-2));
		}else {
			nextStarAnsVec.push_back(Pair (-1, -1));
		}
	}

	//Next*(n, 3) //Next*(_, 3)
	else if(isalpha(tk1[0]) || tk1=="_"){
		int tk2Int = atoi(tk2.c_str());
		set<int> tk1List;

		if(isExistInLinkages(tk1)){
			tk1List = retrieveTokenEvaluatedAnswers(tk1);
		}else{
			tk1List = pkb->getAllStmts(i1->second);
		}

		//Next*(_,3)
		if(tk1=="_"){
			if(!pkb->getPrevious(tk2Int).empty()){
				nextStarAnsVec.push_back(Pair(-1,-1));
			}
		}

		//Next*(n, 3)
		else{

			// cout<<"In Next*(token, digit)"<<endl;

			for(set<int>::iterator it2 = tk1List.begin(); it2!=tk1List.end(); it2++){
				traverseTable.clear();
				if(nextStarTable.find(*it2)!=nextStarTable.end() && nextStarTable.find(*it2)->second.find(tk2Int)!=nextStarTable.find(*it2)->second.end()){
					nextStarAns.insert(Pair(*it2, tk2Int));
				}else {
					recursiveNextTarget(*it2, *it2, tk2Int, &nextStarAns, &traverseTable, false);
				}
			}

			for(set<Pair>::iterator it = nextStarAns.begin(); it!=nextStarAns.end(); it++){
				// cout<<"Pushing into answer the pair "<<it->ans1<<"and"<<it->ans2<<endl;
				nextStarAnsVec.push_back(*it);
			}
		}
	}

	//Next*(3, n) Next*(3, _)
	else if(isalpha(tk2[0]) || tk2=="_"){
		int tk1Int = atoi(tk1.c_str());
		set<int> tk2List;

		if(isExistInLinkages(tk2)){
			tk2List = retrieveTokenEvaluatedAnswers(tk2);
		}else{
			tk2List = pkb->getAllStmts(i2->second);
		}

		//Next*(3, _)
		if(tk2=="_"){
			if(!pkb->getNext(tk1Int).empty()){
				nextStarAnsVec.push_back(Pair(-1,-1));
			}
		}
		
		//Next*(3,n)
		else{
			for(set<int>::iterator it2 = tk2List.begin(); it2!=tk2List.end(); it2++){
				if(nextStarTable.find(tk1Int)!=nextStarTable.end() && nextStarTable.find(tk1Int)->second.find(*it2)!=nextStarTable.find(tk1Int)->second.end()){
					nextStarAns.insert(Pair(tk1Int, *it2));
				}else {
					traverseTable.clear();
					recursiveNextTarget(tk1Int, tk1Int, *it2, &nextStarAns, &traverseTable, false);
				}
			}

			for(set<Pair>::iterator it = nextStarAns.begin(); it!=nextStarAns.end(); it++){
				nextStarAnsVec.push_back(*it);
			}
		}
	}

	//Next*(1,7)
	else {
		int tk2Int = atoi(tk2.c_str());
		int tk1Int = atoi(tk1.c_str());

		// cout<<"tk1Int = "<<tk1Int<<" tk2Int = "<<tk2Int<<endl;
		recursiveNextTarget(tk1Int, tk1Int, tk2Int, &nextStarAns, &traverseTable, false);
		
		if(nextStarAns.empty()){
			//nextStarAnsVec.push_back(Pair (-2, -2));
		}else{
			nextStarAnsVec.push_back(Pair (-1, -1));
		}

	}

	intersectPairs(tk1,tk2,&nextStarAnsVec, relIndex);
	relAns.insert(make_pair<int, vector<Pair>>(relIndex, nextStarAnsVec));
	cout<<"End Evaluate Next Star"<<endl;
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

void QueryEvaluator::recursiveNextTarget(int rootIndex, int currentIndex, int targetIndex, set<Pair> * ans, vector<int> *traverseTable, bool flag){
	
	set<int> next = pkb->getNext(currentIndex);
	for(set<int>::iterator it = next.begin(); it!=next.end(); it++){
		if(nextStarTable.find(currentIndex)!=nextStarTable.end()){
			set<int> s = nextStarTable.find(currentIndex)->second;
			s.insert(*it);
			nextStarTable.at(currentIndex) = s;
			//// cout<<"NEXTSTARTABLE("<<currentIndex<<","<<*it<<")"<<endl;
		}else {
			set<int> s;
			s.insert(*it);
			nextStarTable.insert(make_pair<int, set<int>>(currentIndex, s));
			//// cout<<"NEXTSTARTABLE("<<currentIndex<<","<<*it<<")"<<endl;
		}

		if(nextStarTable.find(rootIndex)!=nextStarTable.end()){
			set<int> s = nextStarTable.find(rootIndex)->second;
			s.insert(*it);
			nextStarTable.at(rootIndex) = s;
			//// cout<<"NEXTSTARTABLE("<<rootIndex<<","<<*it<<")"<<endl;
		}else {
			set<int> s;
			s.insert(*it);
			nextStarTable.insert(make_pair<int, set<int>>(rootIndex, s));
			//// cout<<"NEXTSTARTABLE("<<rootIndex<<","<<*it<<")"<<endl;
		}

		if(find(traverseTable->begin(), traverseTable->end(), *it)!=traverseTable->end()){
			//// cout<<*it<<" is traversed"<<endl;
			it++;
			if(it==next.end()){
				//// cout<<"Reached the end "<<endl;
				break;
			}
		}else{
			traverseTable->push_back(*it);
		}
		if(*it == targetIndex){
			// cout<<"TargetIndex found"<<endl;
			ans->insert(Pair (rootIndex, targetIndex));
			flag = true;
			break;
		}
		recursiveNextTarget(rootIndex, *it, targetIndex, ans, traverseTable, flag);
		if(flag)
			return;
	}
}

void QueryEvaluator::recursiveNextReverse(int rootIndex, int currentIndex, set<Pair> * ans, TypeTable::SynType type, vector<int>* traverseTable){
	set<int> prev = pkb->getPrevious(currentIndex);

	for(set<int>::iterator it = prev.begin(); it!=prev.end(); it++){
		// cout<<"Traversing "<<*it<<endl;
		// cout<<"Type is "<<convertEnumToString(type)<<endl;
		if(find(traverseTable->begin(), traverseTable->end(), *it)!=traverseTable->end()){
			// cout<<"Node traversed before. Moving on to next node"<<endl;
			it++;
			if(it==prev.end()){
				break;
			}
		}else{
			// cout<<"Node not traversed before"<<endl;
			traverseTable->push_back(*it);
		}
		if(pkb->isSynType(type,*it)){
			// cout<<"SynType match, inserting pair"<<endl;
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
		if(tk1!=tk2){
			set<int> procIndexes = pkb->getAllProcIndexes();
			for(set<int>::iterator it=procIndexes.begin(); it!=procIndexes.end(); it++){
				called = pkb->getCalled(*it);

				for(set<int>::iterator it2=called.begin(); it2!=called.end(); it2++){
					callAns.push_back(Pair (*it, *it2));
					// cout<<"it = "<<*it<<" "<<"it2 = "<<*it2<<endl;
				}
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
				//callAns.push_back(Pair(-2,-2));
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
			//	callAns.push_back(Pair(-2,-2));
			}
		}

		//Calls("First", q)
		else{
			for(set<int>::iterator it=ans.begin(); it!=ans.end(); it++){
				callAns.push_back(Pair (procIndex, *it));
				// cout<<"Call - Pushing Pair ("<<procIndex<<" "<<*it<<")"<<endl;
			}
		}
	}

	//Calls(_,_)
	else if(tk1=="_" && tk2=="_"){
		ans = pkb->getAllCalls();
		if(!ans.empty()){
			callAns.push_back(Pair (-1, -1));
		}else{
			//callAns.push_back(Pair (-2, -2));
		}
	}

	//Calls("Third", "Fourth")
	else {
		// cout<<"supposed"<<endl;
		// cout<<tk1.substr(1, tk1.length()-2)<<tk2.substr(1,tk2.length()-2)<<endl;
		int procIndex1 = pkb->getProcIndex(tk1.substr(1, tk1.length()-2));
		int procIndex2 = pkb->getProcIndex(tk2.substr(1,tk2.length()-2));
		if(pkb->isCalls(procIndex1, procIndex2)){
			callAns.push_back(Pair (-1, -1));
		}else{
			//callAns.push_back(Pair (-2, -2));
		}
	}

	intersectPairs(tk1,tk2,&callAns, relIndex);

	relAns.insert(make_pair(relIndex, callAns));


}

void QueryEvaluator::evaluateCallsStar(Relationship r, int relIndex){
	string tk1 = r.getToken1();
	string tk2 = r.getToken2();
	// cout<<"---STARTING CALLS STAR---"<<endl;
	set<Pair> callsStarAns;
	vector<int> traverseTable;

	//Calls*(a,b) 
	if(isalpha(tk1[0]) && isalpha(tk2[0])){
		if(tk1==tk2){
			
		}else {
			// cout<<"tk1 = "<<tk1<<" and tk2 = "<<tk2<<endl;
			set<int> allProc = pkb->getAllProcIndexes();

			for(set<int>::iterator it = allProc.begin(); it!=allProc.end(); it++){
				recursiveCall(*it, *it, &callsStarAns, &traverseTable);
			}
		}
	}

	//Calls*(a,_)
	else if(isalpha(tk1[0]) && tk2=="_"){
			set<int> allProc = pkb->getAllProcIndexes();

			for(set<int>::iterator it=allProc.begin(); it!=allProc.end(); it++){
				if(!pkb->getCalled(*it).empty()){
					callsStarAns.insert(Pair (*it, -1));
				}
			}
	}

	//Calls*(a, "second")
	else if(isalpha(tk1[0])) {
		int index = pkb->getProcIndex(tk2.substr(1,tk2.length()-2));

		recursiveInverseCall(index, index, &callsStarAns, &traverseTable);

	}

	//Calls*(_,b)
	else if(isalpha(tk2[0]) && tk1=="_"){

		set<int> allProc = pkb->getAllProcIndexes();

		for(set<int>::iterator it = allProc.begin(); it!=allProc.end(); it++){
			if(!pkb->getCalls(*it).empty()){
				callsStarAns.insert(Pair(-1, *it));
			}
		}

	}

	//Calls*("first", b)
	else if(isalpha(tk2[0])){
		int index = pkb->getProcIndex(tk1.substr(1, tk1.length()-2));

		recursiveCall(index, index, &callsStarAns, &traverseTable);
	}

	//Calls*(_,"Second")
	else if(tk1=="_" && tk2[0]=='\"'){
		set<int> p = pkb->getCalls(pkb->getProcIndex(tk2.substr(1, tk2.length()-2)));
		if(p.empty()){
			//callsStarAns.insert(Pair (-2,-2));
		}else{
			callsStarAns.insert(Pair (-1,-1));
		}
	}

	//Calls*("First", _)
	else if(tk1[0]=='\"' && tk2=="_"){
		set<int> p = pkb->getCalled(pkb->getProcIndex(tk1.substr(1, tk1.length()-2)));
		if(p.empty()){
		//	callsStarAns.insert(Pair (-2,-2));
		}else{
			callsStarAns.insert(Pair (-1,-1));
		}
	}

	else if(tk1=="_" && tk2=="_"){
		// cout<<"tk1=_ and tk2=_"<<endl;
		if(pkb->getAllCalled().empty()){
			//callsStarAns.insert(Pair(-2,-2));
		}else{
			callsStarAns.insert(Pair(-1,-1));
		}
	}

	//Calls*("first", "second")
	else {
		int index1 = pkb->getProcIndex(tk1.substr(1, tk1.length()-2));
		int index2 = pkb->getProcIndex(tk2.substr(1, tk2.length()-2));

		recursiveCallBoolean(index1, index1, index2, &callsStarAns, &traverseTable);

		if(callsStarAns.empty()){
			//callsStarAns.insert(Pair (-2, -2));
		}
	}
	vector<Pair> callsStarAnsVector;
	for (set<Pair>::iterator x = callsStarAns.begin(); x!=callsStarAns.end(); x++){
		callsStarAnsVector.push_back(*x);
	}
	//If both a and b exist in QueryEvaluator::linkages
	intersectPairs(tk1,tk2,&callsStarAnsVector,relIndex);

	QueryEvaluator::relAns.insert(make_pair(relIndex, callsStarAnsVector));

	// cout<<"---END OF CALLS STAR---"<<endl;

}

void QueryEvaluator::recursiveCall(int rootProcIndex, int currentIndex, set<Pair> * ans, vector<int> *traverseTable){
	// cout<<"in recursive Call"<<endl;
	// cout<<"rootindex = "<<rootProcIndex<<" currentIndex= "<<currentIndex<<endl;
	set<int> called = pkb->getCalled(currentIndex);
	// cout<<"after getting called"<<endl;
	for(set<int>::iterator i=called.begin(); i!=called.end(); i++){
		ans->insert(Pair (rootProcIndex, *i));
		if(find(traverseTable->begin(), traverseTable->end(), *i)!=traverseTable->end()){
			i++;
			if(i==called.end()){
				break;
			}
			ans->insert(Pair (rootProcIndex, *i));
		}else{
			traverseTable->push_back(*i);
		}
		recursiveCall(rootProcIndex, *i, ans, traverseTable);
	}
}

void QueryEvaluator::recursiveCallBoolean(int rootProcIndex, int currentIndex, int targetIndex, set<Pair> * ans, vector<int> *traverseTable){
	set<int> called = pkb->getCalled(currentIndex);
	// cout<<"rootIndex = "<<rootProcIndex<<" currentIndex = "<<currentIndex<< " targetIndex = "<<targetIndex<<endl;
	for(set<int>::iterator i=called.begin(); i!=called.end(); i++){
		// cout<<"Iterating throught called vector. *i = "<<*i <<endl;
		if(*i==targetIndex){
			// cout<<"recursiveCallBoolean returns TRUE"<<endl;
			ans->insert(Pair (-1,-1));
			break;
		}
		if(find(traverseTable->begin(), traverseTable->end(), *i)!=traverseTable->end()){
			i++;
			if(i==called.end()){
				break;
			}
			if(*i==targetIndex){
			// cout<<"recursiveCallBoolean returns TRUE"<<endl;
			ans->insert(Pair (-1,-1));
			break;
		}
		}else{
			traverseTable->push_back(*i);
		}
		recursiveCallBoolean(rootProcIndex, *i, targetIndex, ans, traverseTable);
	}
}

void QueryEvaluator::recursiveInverseCall(int leafIndex, int currentIndex, set<Pair> * ans, vector<int> *traverseTable){
	set<int> calls = pkb->getCalls(currentIndex);
	// cout<<"in recursiveInverseCall currentIndex = "<<currentIndex<<endl;
	for(set<int>::iterator i=calls.begin(); i!=calls.end(); i++){
		// cout<<"inserting "<<*i<<endl;
		ans->insert(Pair (*i, leafIndex));
		if(find(traverseTable->begin(), traverseTable->end(), *i)!=traverseTable->end()){
			i++;
			if(i==calls.end()){
				break;
			}
			ans->insert(Pair (*i, leafIndex));
		}else{
			traverseTable->push_back(*i);
		}
		recursiveInverseCall(leafIndex, *i, ans,traverseTable);
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
		if(tk1==tk2){

		}
		//If both tokens are already previously evaluated
		else if(isExistInLinkages(tk1) && isExistInLinkages(tk2)){
			//get the set of answers that are previously evaluated by other relations
			set<int> sa = retrieveTokenEvaluatedAnswers(tk1);
			set<int> sb = retrieveTokenEvaluatedAnswers(tk2);
			
			for(set<int>::iterator x=sb.begin(); x!=sb.end(); x++){
				// cout<<*x<<endl;
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
				// cout<<"in for loop"<<endl;
				int follows = pkb->getFollows(*it);
				// cout<<"follows: "<<convertEnumToString(i2->second)<<" "<<follows<<endl;
				if(follows!=-1 && pkb->isSynType(i2->second,follows)){
					followsAns.push_back(Pair (*it, follows));
					// cout<<"Pushing back "<<*it<<endl;
				}
			}

			//Delete the redundant pairs
			removePairs(followsAns,tk1,1);
		}


		//If only b exists
		else if(isExistInLinkages(tk2)){
			
			//get the set of answers that are previously evaluated by other relations
			set<int> sb = retrieveTokenEvaluatedAnswers(tk2);
			// cout<<sb.empty()<<endl;				
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
			// cout<<"Both tokens are alpha and do not exist in linkages"<<endl;
			//Retrieve both a and b from PKB
			set<int> first = pkb->getAllStmts(i1->second);
			set<int> second = pkb->getAllStmts(i2->second);
			// cout<<"trying is follows"<<pkb->isFollows(2,3)<<endl;
			for(set<int>::iterator iter1 = first.begin(); iter1!=first.end(); iter1++){
				for(set<int>::iterator iter2 = second.begin(); iter2!=second.end(); iter2++){
					if(pkb->isFollows(*iter1, *iter2)){
						followsAns.push_back(Pair (*iter1, *iter2));
						// cout<<"first.at(i) = "<<*iter1<<"second.at(i) = "<<*iter2<<endl;
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
			//followsAns.push_back(Pair (-2,-2));
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
				if(pkb->isSynType(i1->second,first) && first!=-1)
					followsAns.push_back(Pair (first, atoi(tk2.c_str())));
			}

			//Follows(a, _)
			else {
				set<int> a = pkb->getAllStmts(i1->second);
				for(set<int>::iterator it = a.begin(); it!=a.end(); it++){
					if(pkb->getFollows(*it)!=-1)
						followsAns.push_back(Pair (*it, pkb->getFollows(*it)));
				}
			}
		}

		insertLinks(tk1, relIndex);
	}

	//Follows(1,b)
	else if(isalpha(tk2[0])){
		if(isExistInLinkages(tk2)){
			// cout<<tk2<<" Found to Exist in Linkages"<<endl;
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
			// cout<<"Second token is alpha and it does not exist in linkages"<<endl;
			if(isdigit(tk1[0])){
				// cout<<"First token is digit"<<endl;
				int second = pkb->getFollows(atoi(tk1.c_str()));
				// cout<<"Answer is = "<<second<<endl;
				if(second!=-1 && pkb->isSynType(i2->second, second)){
					followsAns.push_back(Pair (atoi(tk1.c_str()), second));
				}
				// cout<<"followsAns.size = "<<followsAns.size()<<endl;
			}

			//Follows(_,b)
			else {
				set<int> a = pkb->getAllStmts(i2->second);
				for(set<int>::iterator it = a.begin(); it!=a.end(); it++){
					if(pkb->getFollowedBy(*it)!=-1)
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
				//followsAns.push_back(Pair (-2,-2));
			}
			else{
				followsAns.push_back(Pair (-1,-1));
			}
		}

		//Follows(1, _)
		else if(isdigit(tk1[0])){
			if(pkb->getFollows(atoi(tk1.c_str()))==-1){
				//followsAns.push_back(Pair (-2,-2));
			}
			else{
				followsAns.push_back(Pair (-1,-1));
			}
		}

		//Follows(_, 2)
		else {
			if(pkb->getFollowedBy(atoi(tk2.c_str()))==-1){
				//followsAns.push_back(Pair (-2,-2));
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
	if(isalpha(tk1[0]) && isalpha(tk2[0]) &&tk1==tk2){

	}

	else if((isalpha(tk1[0]) && isalpha(tk2[0])) || (tk1=="_" && isalpha(tk2[0])) || (tk2=="_" && isalpha(tk1[0]))){

		if(tk1=="_"){
			selected = pkb->getAllStmts(TypeTable::STMT);
		}

		else{
			if(isExistInLinkages(tk1)){
				selected = retrieveTokenEvaluatedAnswers(tk1);
			}
			else{
				selected = pkb->getAllStmts(i1->second);	//get all while statements
			}
		}


		for(set<int>::iterator it = selected.begin(); it!=selected.end(); it++){
			stmtNumber = pkb->getFollows(*it);
			/*
			if(tk2!="_"){
				if(!pkb->isSynType(i2->second, stmtNumber)){
					stmtNumber = -1;
				}
			}*/
			do{			
				if(stmtNumber!=-1){
					if(tk2!="_"){
						if(pkb->isSynType(i2->second, stmtNumber)){
							followsStarAnsSet.insert(Pair (*it, stmtNumber));
						}
					}else{
						followsStarAnsSet.insert(Pair (*it, stmtNumber));
					}
				}
				else{
					break;
				}
				stmtNumber = pkb->getFollows(stmtNumber);
				/*
				if(tk2!="_"){
					if(!pkb->isSynType(i2->second, stmtNumber)){
						stmtNumber = -1;
					}
				}*/
			}while(true);
		}

	}
	
	//Select a such that Follows*(a, 13)
	else if(isalpha(tk1[0])){
		// cout<<"Handling Follows*(type, stmtnum) with tk2 = " << atoi(tk2.c_str())<<endl;
		stmtNumber = atoi(tk2.c_str());
		do{			
			// cout<<"Calling getFollowedBy(type, stmtnum)"<<endl;
			stmtNumber = pkb->getFollowedBy(stmtNumber);
			if(stmtNumber!=-1){
				// cout<<"Evaluated StmtNumber = "<<stmtNumber<<endl;
				if(pkb->isSynType(i1->second, stmtNumber)){
					// cout<<"Inserting StmtNumber "<<stmtNumber<<" into the answer set"<<endl;
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
		// cout<<"Handling Follows*(stmtnum, type)"<<endl;
		stmtNumber = atoi(tk1.c_str());
		do{			
			// cout<<"Calling getFollows(type, stmtnum)"<<endl;
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
			//followsStarAnsSet.insert(Pair (-2,-2));
		}
	}

	//Follows*(1,2) OR Follows*(1, _)
	else if((isdigit(tk1[0]) && isdigit(tk2[0]))|| tk2=="_"){
		stmtNumber = atoi(tk1.c_str());
		while(stmtNumber!=-1){	
			stmtNumber = pkb->getFollows(stmtNumber);
			// cout<<"STMTNUM is "<<stmtNumber<<endl;
			if(stmtNumber==atoi(tk2.c_str()) || (tk2=="_" && stmtNumber!=-1)){
				followsStarAnsSet.insert(Pair (-1,-1));
				break;
			}
			if(stmtNumber>atoi(tk2.c_str())){
				//followsStarAnsSet.insert(Pair (-2,-2));
				break;
			}
		}
	}

	//Follows*(_,2)
	else{
		stmtNumber = pkb->getFollowedBy(atoi(tk2.c_str()));
		if(stmtNumber==-1){
			//followsStarAnsSet.insert(Pair(-2,-2));
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

	// cout<<"Inserting into RelAns RelIndex = "<<relIndex<<endl;
	relAns.insert(make_pair(relIndex, followsStarAns));
	
}

void QueryEvaluator::evaluateParent(Relationship r, unordered_map<string, TypeTable::SynType> m, int relIndex){
	string tk1 = r.getToken1();
	string tk2 = r.getToken2();

	set<int> answer;
	vector<Pair> parentAns;
	unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(tk1);
	unordered_map<string, TypeTable::SynType>::iterator i2 = m.find(tk2);
	// cout<<"tk1 = "<<tk1<<" tk2 = "<<tk2<<endl;

	//Parent(a,b)
	if(isalpha(tk1[0]) && isalpha(tk2[0]) && tk1==tk2){

	}

	else if((isalpha(tk1[0]) && isalpha(tk2[0])) || (tk1=="_" && isalpha(tk2[0]))|| (tk2=="_" && isalpha(tk1[0])) ){

		if(isExistInLinkages(tk1))
			answer = retrieveTokenEvaluatedAnswers(tk1);
		
		//Parent(_, b)
		else if(tk1=="_"){
			answer = pkb->getAllStmts(TypeTable::STMT);
		}
		else
			answer = pkb->getAllStmts(i1->second);

		
		for(set<int>::iterator it=answer.begin(); it!=answer.end(); it++){
			set<int> children;
			if(tk2=="_"){	//Parent(a,_)
				children = pkb->getChildren(*it);
			}else{
				children = pkb->getChildren(*it);
			}
			for(set<int>::iterator it2=children.begin(); it2!=children.end(); it2++){
				if(pkb->isSynType(i2->second, *it2) || tk2=="_"){
					parentAns.push_back(Pair(*it, *it2));
				}
			}
		}
	}

		//Parent(_,_)
	else if(tk1=="_" && tk2 == "_"){
		set<int> ans = pkb->getAllParent();
		if(!ans.empty()){
			// cout<<"parent found to be not empty"<<endl;
			parentAns.push_back(Pair(-1,-1));
		}else {
			//parentAns.push_back(Pair(-2,-2));
			// cout<<"parent found to be empty"<<endl;
		}
	}
	//Parent(a,3)
	else if(isalpha(tk1[0]) || tk1=="_"){

		// cout<<"Calling getParent(TYPE, STMTNUM)"<<endl;
		int parent;
		//Parent(_,3)
		if(tk1=="_"){
			parent = pkb->getParent(atoi(tk2.c_str()));
			if(parent!=-1){
				parentAns.push_back(Pair(-1,-1));
			}
			else {
				//parentAns.push_back(Pair(-2,-2));
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
		// cout<<"Parent(STMTNUM, TYPE)"<<endl;
		if(tk2!="_"){
			set<int> children = pkb->getChildren(atoi(tk1.c_str()));
			for(set<int>::iterator it=children.begin(); it!=children.end(); it++){
				if(pkb->isSynType(i2->second, *it)){
					parentAns.push_back(Pair(atoi(tk1.c_str()), *it));
					// cout<<"in for loop"<<endl;
				}
			}
		} else {
			set<int> children = pkb->getChildren(atoi(tk1.c_str()));
			if(!children.empty()){
				parentAns.push_back(Pair(-1,-1));
			}else {
				//parentAns.push_back(Pair(-2,-2));
			}
		}
	}

	//Parent(1,5)
	else{
		 if(pkb->isParent(atoi(tk1.c_str()), atoi(tk2.c_str()))){
			 // cout<<"istrue"<<endl;
			 parentAns.push_back(Pair (-1,-1));
		 }else{
			 // cout<<"isfalse"<<atoi(tk1.c_str())<<atoi(tk2.c_str())<<endl;
			 //parentAns.push_back(Pair (-2,-2));
		 }
	}
	

	// cout<<"before intersect pairs"<<endl;
	intersectPairs(tk1,tk2,&parentAns,relIndex);
	// cout<<"after intersect pairs"<<endl;
	QueryEvaluator::relAns.insert(make_pair(relIndex, parentAns));
}

void QueryEvaluator::evaluateParentStar(Relationship r, unordered_map<string, TypeTable::SynType> m, int relIndex){
	// cout<<"Initialzing all Parent* variables"<<endl;
	string tk1=r.getToken1();
	string tk2=r.getToken2();

	vector<Pair> answer;
	set<Pair> parentStarAnsSet;
	int stmtNumber = 0;
	unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(tk1);
	unordered_map<string, TypeTable::SynType>::iterator i2 = m.find(tk2);

	//Parent*(w, a) Parent(_,a) Parent(w,_)
	if(isalpha(tk1[0]) && isalpha(tk2[0]) && tk1==tk2){

	}
	else if((isalpha(tk1[0]) && isalpha(tk2[0]))|| (isalpha(tk1[0])&& tk2=="_") || (tk1=="_" && isalpha(tk2[0]))){
		// cout<<"If both tokens are alpha or one of them is a wildcard"<<endl;
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
			// cout<<"Token2 does not Exist in Linkages"<<endl;
			sb.clear();
			if(tk2=="_"){
				sb = pkb->getAllStmts(TypeTable::STMT);
			}else{
				sb = pkb->getAllStmts(i2->second);
			}

		}

		// cout<<"sb is Empty: "<<sb.empty()<<endl;
		for(set<int>::iterator it = sb.begin(); it!=sb.end(); it++){
			// cout<<"Iterating token 2 set Sb"<<endl;
			stmt = pkb->getParent(*it);
			while(stmt!=-1){
				if(isExistInLinkages(tk1)){
					if(pkb->isSynType(i1->second,stmt) && sa.find(stmt)!=sa.end()){
						parentStarAnsSet.insert(Pair (stmt, *it));
					}
				}
				else{
					if(tk1=="_"){
						// cout<<"Token = _ and Parent = "<<stmt<<endl;
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
		// cout<<"tk2 is Integer "<<tk2Int<<endl;
		set<int> sa;
		int stmt;

		if(isExistInLinkages(tk1)){
			// cout<<"TOKEN1 FOUND TO EXIST IN LINKAGES"<<endl;
			sa = retrieveTokenEvaluatedAnswers(tk1);
		}else {
			// cout<<"TOKEN1 FOUND NOT TO EXIST IN LINKAGES"<<endl;
			sa = pkb->getAllStmts(i1->second);
		}
		
		// cout<<"Set is Empty: "<<sa.empty()<<endl;
		stmt = pkb->getParent(tk2Int);
		while(stmt!=-1){
			//// cout<<"Parent StmtNumber = "<<stmt<<endl;
			if(sa.find(stmt)!=sa.end()){
				// cout<<"Insert stmtNum = "<<stmt<<" into set"<<endl;
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
			//parentStarAnsSet.insert(Pair(-2,-2));
		}else {
			parentStarAnsSet.insert(Pair(-1,-1));
		}
	}

	//Parent*(3,4)
	else {

		//Parent*(3, _)
		if(tk2=="_"){
			if(pkb->getChildren(atoi(tk1.c_str())).empty()){
				//answer.push_back(Pair(-2,-2));
			}else{
				answer.push_back(Pair(-1,-1));
			}
			relAns.insert(make_pair<int, vector<Pair>>(relIndex, answer));
			return;
		}

		//Parent*(_,3)
		if(tk1=="_"){
			if(pkb->getParent(atoi(tk2.c_str()))==-1){
				//answer.push_back(Pair(-2,-2));
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

		//parentStarAnsSet.insert(Pair(-2,-2));

	}

	copy(parentStarAnsSet.begin(), parentStarAnsSet.end(), back_inserter(answer));
	relAns.insert(make_pair<int, vector<Pair>>(relIndex, answer));
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
			// cout<<"In Modifies(p, \"var\")"<<endl;
			answer = pkb->getModifiesProc(varIndex);
			for(set<int>::iterator it=answer.begin(); it!=answer.end(); it++){
				modAns.push_back(Pair (*it, varIndex));
			}
		}

		//otherwise
		else {
			answer = pkb->getModifies(varIndex);
			// cout<<varIndex<<endl;
			// cout<<"answer is empty: "<<answer.empty()<<endl;
			for(set<int>::iterator it=answer.begin(); it!=answer.end(); it++){
				// cout<<"modifiesAnswer"<<*it<<" "<<varIndex<<endl;
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

			//Modifies(1,_)
			if(tk2=="_"){
				if(selected.empty()){
					//modAns.push_back(Pair (-2,-2));
				}else{
					modAns.push_back(Pair(-1,-1));
				}
			}else{
				for(set<int>::iterator it=selected.begin(); it!=selected.end(); it++){
					modAns.push_back(Pair (atoi(tk1.c_str()), *it));
				}
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
			// cout<<"Modifies(\"Procname\", \"VarName\")"<<endl;
			string procName = tk1.substr(1,tk1.length()-2);
			int procIndex = pkb->getProcIndex(procName);
			string varName = tk2.substr(1,tk2.length()-2);
			int varIndex = pkb->getVarIndex(varName);
			if(pkb->isModifiesProc(procIndex, varIndex)){
				modAns.push_back(Pair (-1,-1));
			}else {
				//modAns.push_back(Pair (-2,-2));
			}
		} 
		
		//Modifies("Third", _)
		else {
			int index = pkb->getProcIndex(tk1.substr(1, tk1.length()-2));
			set<int> allVariablesModifiedByProc = pkb->getModifiedProc(index);
			if(allVariablesModifiedByProc.empty()){
				//modAns.push_back(Pair(-2,-2));
			}

			else {
				modAns.push_back(Pair(-1,-1));
			}
		}
	}

	//Modifies(_,_)
	else if(tk1=="_" && tk2=="_"){
		// cout<<"Modifies(_,_)"<<endl;
		set<int> allProcIndexes = pkb->getAllProcIndexes();
		bool flag = false;
		for(set<int>::iterator it = allProcIndexes.begin(); it!=allProcIndexes.end(); it++){
			if(!pkb->getModifiedProc(*it).empty()){
				// cout<<"flag is true"<<endl;
				flag = true;
				break;
			}
		}

		if(flag){
			modAns.push_back(Pair (-1,-1));
		}else{
			//modAns.push_back(Pair (-2,-2));
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
				//modAns.push_back(Pair (-2, -2));
			}
		}
		else if(tk2=="_"){
			selected = pkb->getUsed(atoi(tk1.c_str()));
			if(selected.empty()){
				//modAns.push_back(Pair(-2,-2));
			}else {
				modAns.push_back(Pair(-1,-1));
			}
		}
		else {
		string varName = tk2.substr(1,tk2.length()-2);
		int varIndex = pkb->getVarIndex(varName);
		// cout<<atoi(tk1.c_str())<<varName<<endl;
		if(pkb->isModifies(atoi(tk1.c_str()), varIndex)){
			 modAns.push_back(Pair (-1,-1));
		 }else{
			// modAns.push_back(Pair (-2,-2));
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
				//usesAns.push_back(Pair (-2,-2));
			}
		}

		//Uses("Third", _)
		else {
			int index = pkb->getProcIndex(tk1.substr(1, tk1.length()-2));
			set<int> allVariablesUsedByProc = pkb->getUsedProc(index);
			if(allVariablesUsedByProc.empty()){
				//usesAns.push_back(Pair(-2,-2));
			}

			else {
				usesAns.push_back(Pair(-1,-1));
			}
		}
	}

	//Uses(_,_)
	else if(tk1=="_" && tk2=="_"){
		// cout<<"Uses(_,_)"<<endl;
		set<int> allProcIndexes = pkb->getAllProcIndexes();
		bool flag = false;
		for(set<int>::iterator it = allProcIndexes.begin(); it!=allProcIndexes.end(); it++){
			if(!pkb->getUsedProc(*it).empty()){
				// cout<<"flag is true"<<endl;
				flag = true;
				break;
			}
		}

		if(flag){
			usesAns.push_back(Pair (-1,-1));
		}else{
			//usesAns.push_back(Pair (-2,-2));
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
				//usesAns.push_back(Pair (-2, -2));
			}
		}
		else if(tk2=="_"){
			selected = pkb->getUsed(atoi(tk1.c_str()));
			if(selected.empty()){
				//usesAns.push_back(Pair(-2,-2));
			}else {
				usesAns.push_back(Pair(-1,-1));
			}
		}

		else{

			if(pkb->isUses(atoi(tk1.c_str()), varIndex)){
				 usesAns.push_back(Pair (-1,-1));
			 }else{
				 //usesAns.push_back(Pair (-2,-2));
			 }
		}
	}

	intersectPairs(tk1,tk2,&usesAns,relIndex);

	QueryEvaluator::relAns.insert(make_pair(relIndex, usesAns));
}

void QueryEvaluator::evaluateAffects(Relationship r, std::unordered_map<std::string, TypeTable::SynType> m, int relIndex) {
	string tk1=r.getToken1();
	string tk2=r.getToken2();

	vector<Pair> affAns;

	unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(tk1);
	unordered_map<string, TypeTable::SynType>::iterator i2 = m.find(tk2);


	//Affects(a1, a2)
	if((isalpha(tk1[0]) && isalpha(tk2[0])) || (tk1=="_" && isalpha(tk2[0])) || (isalpha(tk1[0])&& tk2=="_")) {
		cout << "Case 1: Both are Synonyms" << endl;
		set<int> tk1List;
		set<int> tk2List;
		if(tk1==tk2) {
			if(tk1=="_")
				tk1List = pkb->getAllStmts(TypeTable::ASSIGN);
			else if(isExistInLinkages(tk1)) {
				tk1List = retrieveTokenEvaluatedAnswers(tk1);
				insertLinks(tk1, relIndex);
			}
			else {
				tk1List = pkb->getAllStmts(i1->second);
				insertLinks(tk1, relIndex);
			}

			tk2List = tk1List;
		}
		else {
			if(tk1=="_")
				tk1List = pkb->getAllStmts(TypeTable::ASSIGN);
			else if(isExistInLinkages(tk1)) {
				tk1List = retrieveTokenEvaluatedAnswers(tk1);
				insertLinks(tk1, relIndex);
			}
			else {
				tk1List = pkb->getAllStmts(i1->second);
				insertLinks(tk1, relIndex);
			}
		
			if(tk2=="_")
				tk2List = pkb->getAllStmts(TypeTable::ASSIGN);
			else if(isExistInLinkages(tk2)) {
				tk2List = retrieveTokenEvaluatedAnswers(tk2);
				insertLinks(tk2, relIndex);
			}
			else {
				tk2List = pkb->getAllStmts(i2->second);
				insertLinks(tk2, relIndex);
			}
		}

		for(set<int>::iterator itA = tk1List.begin(); itA!=tk1List.end(); itA++) {
			for(set<int>::iterator itB = tk2List.begin(); itB!=tk2List.end(); itB++) {
				if (AbstractWrapper::GlobalStop) {
					// cout<< "Timeout detected! Stopping Affects Evaluation!" << endl;
					QueryEvaluator::relAns.insert(make_pair(relIndex, affAns));
					return;
				}
				if(isAffects(*itA, *itB))
					affAns.push_back(Pair(*itA, *itB));
			}
		}
	}

	//Affects(a, "7")
	else if( (isalpha(tk1[0]) || tk1=="_") && tk2!="_" ) {
		cout << "Case 2: Left is Synonym" << endl;
		set<int> tk1List;
		if(tk1=="_")
			tk1List = pkb->getAllStmts(TypeTable::ASSIGN);
		else if(isExistInLinkages(tk1)) {
			tk1List = retrieveTokenEvaluatedAnswers(tk1);
			insertLinks(tk1, relIndex);
		}
		else {
			tk1List = pkb->getAllStmts(i1->second);
			insertLinks(tk1, relIndex);
		}

		for(set<int>::iterator it = tk1List.begin(); it!=tk1List.end(); it++) {
			if (AbstractWrapper::GlobalStop) {
				// cout<< "Timeout detected! Stopping Affects Evaluation!" << endl;
				QueryEvaluator::relAns.insert(make_pair(relIndex, affAns));
				return;
			}
			if(isAffects(*it, atoi(tk2.c_str()))) {
				if(tk1=="_") {
					affAns.push_back(Pair(-1, -1));
					break;
				}
				else {
					affAns.push_back(Pair(*it, atoi(tk2.c_str())));
				}
			}
		}
	}

	//Affects("1", a)
	else if( (isalpha(tk2[0]) || tk2=="_") && tk1!="_" ) {
		cout << "Case 3: Right is Synonym" << endl;
		set<int> tk2List;
		if(tk2=="_")
			tk2List = pkb->getAllStmts(TypeTable::ASSIGN);
		else if(isExistInLinkages(tk2)) {
			tk2List = retrieveTokenEvaluatedAnswers(tk2);
			insertLinks(tk2, relIndex);
		}
		else {
			tk2List = pkb->getAllStmts(i2->second);
			insertLinks(tk2, relIndex);
		}

		for(set<int>::iterator it = tk2List.begin(); it!=tk2List.end(); it++) {
			if (AbstractWrapper::GlobalStop) {
				cout<< "Timeout detected! Stopping Affects Evaluation!" << endl;
				QueryEvaluator::relAns.insert(make_pair(relIndex, affAns));
				return;
			}
			if(isAffects(atoi(tk1.c_str()), *it)) {
				if(tk2=="_"){
					affAns.push_back(Pair(-1,-1));
					break;
				}
				else {
					affAns.push_back(Pair(atoi(tk1.c_str()), *it));
				}
			}
		}

	}

	//Affects("1", "2")
	else if( tk1!="_" ) {
		cout << "Case 4: Both are Constants" << endl;
		if(isAffects(atoi(tk1.c_str()), atoi(tk2.c_str())))
			affAns.push_back(Pair(-1, -1));
	}

	//Affects(_,_)
	else {
		cout << "Case 5: Both are underscore" << endl;
		set<int> tk1List = pkb->getAllStmts(TypeTable::ASSIGN);
		set<int> tk2List = pkb->getAllStmts(TypeTable::ASSIGN);

		for(set<int>::iterator itA = tk1List.begin(); itA!=tk1List.end(); itA++) {
			for(set<int>::iterator itB = tk2List.begin(); itB!=tk2List.end(); itB++) {
				if (AbstractWrapper::GlobalStop) {
					// cout<< "Timeout detected! Stopping Affects Evaluation!" << endl;
					QueryEvaluator::relAns.insert(make_pair(relIndex, affAns));
					return;
				}
				if(isAffects(*itA, *itB)) {
					affAns.push_back(Pair(-1,-1));
					intersectPairs(tk1, tk2, &affAns, relIndex);
					QueryEvaluator::relAns.insert(make_pair(relIndex, affAns));
					return;
				}
			}
		}
	}

	//intersectPairs(tk1, tk2, &affAns, relIndex);
	QueryEvaluator::relAns.insert(make_pair(relIndex, affAns));
}

void QueryEvaluator::evaluateAffectsStar(Relationship r, std::unordered_map<std::string, TypeTable::SynType> m, int relIndex) {
	string tk1=r.getToken1();
	string tk2=r.getToken2();

	vector<Pair> affAns;
	unordered_map<Pair, bool> processed;
	vector<int> path;

	unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(tk1);
	unordered_map<string, TypeTable::SynType>::iterator i2 = m.find(tk2);

	//Affects*(a1, a2)
	if((isalpha(tk1[0]) && isalpha(tk2[0])) || (tk1=="_" && isalpha(tk2[0])) || (isalpha(tk1[0])&& tk2=="_")) {
		cout << "Case 1: Both are Synonyms" << endl;
		set<int> tk1List;
		set<int> tk2List;
		
		if(tk1==tk2) {
			if(tk1=="_")
				tk1List = pkb->getAllStmts(TypeTable::ASSIGN);
			else if(isExistInLinkages(tk1)) {
				tk1List = retrieveTokenEvaluatedAnswers(tk1);
				insertLinks(tk1, relIndex);
			}
			else {
				tk1List = pkb->getAllStmts(i1->second);
				insertLinks(tk1, relIndex);
			}

			tk2List = tk1List;
		}
		else {
			if(tk1=="_")
				tk1List = pkb->getAllStmts(TypeTable::ASSIGN);
			else if(isExistInLinkages(tk1)) {
				tk1List = retrieveTokenEvaluatedAnswers(tk1);
				insertLinks(tk1, relIndex);
			}
			else {
				tk1List = pkb->getAllStmts(i1->second);
				insertLinks(tk1, relIndex);
			}
		
			if(tk2=="_")
				tk2List = pkb->getAllStmts(TypeTable::ASSIGN);
			else if(isExistInLinkages(tk2)) {
				tk2List = retrieveTokenEvaluatedAnswers(tk2);
				insertLinks(tk2, relIndex);
			}
			else {
				tk2List = pkb->getAllStmts(i2->second);
				insertLinks(tk2, relIndex);
			}
		}

		for(set<int>::iterator itA = tk1List.begin(); itA!=tk1List.end(); itA++) {
			for(set<int>::iterator itB = tk2List.begin(); itB!=tk2List.end(); itB++) {
				if (AbstractWrapper::GlobalStop) {
					// cout<< "Timeout detected! Stopping Affects* Evaluation!" << endl;
					QueryEvaluator::relAns.insert(make_pair(relIndex, affAns));
					return;
				}
				if(isAffectsStar(*itA, *itB)) {
					// cout << "Affects*(" << *itA << "," << *itB << ") is true. Inserting into affAns." << endl;
					affAns.push_back(Pair(*itA, *itB));
				}
			}
		}
	}

	//Affects*(a, "7")
	else if( (isalpha(tk1[0]) || tk1=="_") && tk2!="_") {
		cout << "Case 2: Left is Synonym" << endl;
		set<int> tk1List;
		if(tk1=="_")
			tk1List = pkb->getAllStmts(TypeTable::ASSIGN);
		else if(isExistInLinkages(tk1)) {
			tk1List = retrieveTokenEvaluatedAnswers(tk1);
			insertLinks(tk1, relIndex);
		}
		else {
			tk1List = pkb->getAllStmts(i1->second);
			insertLinks(tk1, relIndex);
		}

		for(set<int>::iterator it = tk1List.begin(); it!=tk1List.end(); it++) {
			if (AbstractWrapper::GlobalStop) {
				// cout<< "Timeout detected! Stopping Affects* Evaluation!" << endl;
				QueryEvaluator::relAns.insert(make_pair(relIndex, affAns));
				return;
			}
			if(isAffectsStar(*it, atoi(tk2.c_str())))
			{	
				if(tk1=="_") {
					affAns.push_back(Pair(-1,-1));
					break;
				}
				else {
					affAns.push_back(Pair(*it, atoi(tk2.c_str())));
				}
			}
		}
	}

	//Affects*("1", a)
	else if( (isalpha(tk2[0]) || tk2=="_")  && tk1!="_") {
		cout << "Case 3: Right is Synonym" << endl;
		set<int> tk2List;
		if(tk2=="_")
			tk2List = pkb->getAllStmts(TypeTable::ASSIGN);
		else if(isExistInLinkages(tk2)) {
			tk2List = retrieveTokenEvaluatedAnswers(tk2);
			insertLinks(tk2, relIndex);
		}
		else {
			tk2List = pkb->getAllStmts(i2->second);
			insertLinks(tk2, relIndex);
		}

		for(set<int>::iterator it = tk2List.begin(); it!=tk2List.end(); it++) {
			if (AbstractWrapper::GlobalStop) {
				// cout<< "Timeout detected! Stopping Affects* Evaluation!" << endl;
				QueryEvaluator::relAns.insert(make_pair(relIndex, affAns));
				return;
			}
			if(isAffectsStar(atoi(tk1.c_str()), *it)) {
				if(tk2=="_") {
					affAns.push_back(Pair(-1,-1));
					break;
				}
				else {
					affAns.push_back(Pair(atoi(tk1.c_str()), *it));
				}
			}
		}
	}

	//Affects*("1", "2")
	else if( tk1!="_" ) {
		cout << "Case 4: Both are Constants" << endl;
		if(isAffectsStar(atoi(tk1.c_str()), atoi(tk2.c_str())))
			affAns.push_back(Pair(-1, -1));
	}

	//Affects*(_,_)
	else {
		cout << "Case 5: Both are underscore" << endl;
		set<int> tk1List = pkb->getAllStmts(TypeTable::ASSIGN);
		set<int> tk2List = pkb->getAllStmts(TypeTable::ASSIGN);

		for(set<int>::iterator itA = tk1List.begin(); itA!=tk1List.end(); itA++) {
			for(set<int>::iterator itB = tk2List.begin(); itB!=tk2List.end(); itB++) {
				if (AbstractWrapper::GlobalStop) {
					// cout<< "Timeout detected! Stopping Affects* Evaluation!" << endl;
					QueryEvaluator::relAns.insert(make_pair(relIndex, affAns));
					return;
				}
				if(isAffectsStar(*itA, *itB)) {
					affAns.push_back(Pair(-1,-1));
					//intersectPairs(tk1, tk2, &affAns, relIndex);
					QueryEvaluator::relAns.insert(make_pair(relIndex, affAns));
					return;
				}
			}
		}
	}

	// cout << "NUMBER OF ANSWERS OF AFFECTS*(" << tk1 << "," << tk2 << ") :" << affAns.size() << endl; 
	// cout << "ANSWERS FOR AFFECTS*(" << tk1 << "," << tk2 << ") :" << endl;
	for(int i=0; i<int(affAns.size()); i++) {
		// cout << "(" << affAns.at(i).ans1 << ", " << affAns.at(i).ans2 << ")" << endl;
	}

	//intersectPairs(tk1, tk2, &affAns, relIndex);
	QueryEvaluator::relAns.insert(make_pair(relIndex, affAns));
	cout << "End Affects* evaluation" << endl;
}

bool QueryEvaluator::findPath(int start, int target, set<int> modifies) {
	if(pkb->getSynType(target)!=TypeTable::ASSIGN)
		return false;

	stack<int> st;
	set<int> next = pkb->getNext(start);
	for(set<int>::iterator it = next.begin(); it!=next.end(); it++)
		st.push(*it);
	set<int> visited;

	while(!st.empty()) {
		int curr = st.top();
		st.pop();
		visited.insert(curr);

		if(modifies.count(curr)!=0 && (pkb->getSynType(curr)==TypeTable::ASSIGN || pkb->getSynType(curr)==TypeTable::CALL) && curr!=target) {
			continue;
		}

		if(curr==target)
			return true;

		set<int> next = pkb->getNext(curr);
		for(set<int>::iterator it = next.begin(); it!=next.end(); it++) {
			if(visited.count(*it)==0)
				st.push(*it);
		}

	}
	return false;
}

bool QueryEvaluator::isAffects(int token1, int token2) {
	if(affectsTable.count(hashPair(Pair(token1, token2)))!=0)
		return affectsTable.at(hashPair(Pair(token1, token2)));
	
	set<int> modified = pkb->getModified(token1);
	if( !(pkb->isUses(token2, *modified.begin())) )
		return false;
	set<int> modifies = pkb->getModifies(*modified.begin());

	bool ans = findPath(token1, token2, modifies);

	affectsTable.insert(make_pair(hashPair(Pair(token1, token2)), ans));

	return ans;
}

bool QueryEvaluator::isAffectsStar(int token1, int token2) {
	if(affectsStarTable.count(hashPair(Pair(token1, token2)))!=0)
		return affectsStarTable.at(hashPair(Pair(token1, token2)));
	
	set<int> next = getNextStar(token1);
	stack<Pair> st;
	set<pair<int, int>> visited;

	for(set<int>::iterator it = next.begin(); it!=next.end(); it++)
		st.push(Pair(token1, *it));

	while(!st.empty()) {
		Pair curr = st.top();
		st.pop();
		visited.insert(make_pair(curr.ans1, curr.ans2));

		if(isAffects(curr.ans1, curr.ans2)) {
			if(curr.ans2 == token2) {
				affectsStarTable.insert(make_pair(hashPair(Pair(token1, token2)), true));
				return true;
			}
			else {
				next = getNextStar(curr.ans2);
				for(set<int>::iterator it = next.begin(); it!=next.end(); it++) {			
					if(visited.count(make_pair(curr.ans2, *it)) == 0)
						st.push(Pair(curr.ans2, *it));
				}
			}
		}
	}

	affectsStarTable.insert(make_pair(hashPair(Pair(token1, token2)), false));
	return false;
}

set<int> QueryEvaluator::getNextStar(int start) {
	if(nst.count(start)!=0)
		return nst.at(start);

	stack<int> st;
	set<int> next = pkb->getNext(start);
	for(set<int>::iterator it = next.begin(); it!=next.end(); it++)
		st.push(*it);
	set<int> visited;

	while(!st.empty()) {
		int curr = st.top();
		st.pop();
		visited.insert(curr);

		next = pkb->getNext(curr);

		for(set<int>::iterator it = next.begin(); it!=next.end(); it++) {
			if(visited.count(*it)==0)
				st.push(*it);
		}
	}

	nst.insert(make_pair(start, visited));
	return visited;
}

int QueryEvaluator::hashPair(Pair p) {
	int tk1 = p.ans1;
	int tk2 = p.ans2;

	int range = pkb->getStmtRange()+1;

	return tk1 + tk2*range;
}

void QueryEvaluator::evaluatePattern(Relationship r, std::unordered_map<std::string, TypeTable::SynType> m, int relIndex) {
	string lhs = r.getToken1();
	string rhs = r.getToken2();
	string syn = r.getPatternSyn();
	TypeTable::SynType synType = m.at(syn);
	vector<Pair> patternAns;
	Node* root = pkb->getASTRoot();

	insertLinks(syn, relIndex);
	if(r.getToken1Type() == Relationship::SYNONYM)
		insertLinks(lhs, relIndex);

	switch(synType){
		case TypeTable::ASSIGN:
			patternAns = findAssign(*root, lhs, rhs, r);
			break;

		case TypeTable::IF:
			patternAns = findIf(*root, lhs, rhs, r);
			break;

		case TypeTable::WHILE:
			patternAns = findWhile(*root, lhs, rhs, r);
			break;

	}

	//Printing patternAns
	// cout<<"PRINTING PATTERNANS"<<endl;
	for(vector<Pair>::iterator it = patternAns.begin(); it!=patternAns.end(); it++){
		// cout<<"ans1 = "<<it->ans1<< " ans2 = "<<it->ans2<<endl;
	}

	QueryEvaluator::relAns.insert(make_pair(relIndex, patternAns));
}

vector<Pair> QueryEvaluator::findAssign(Node startNode, string lhs, string rhs, Relationship r) {
	vector<Pair> ans;
	stack<Node> st;
	st.push(startNode);
	
	while(!st.empty()) {
		Node n = st.top();
		st.pop();

		if(r.getToken1Type() == Relationship::SYNONYM) {
			if(n.getType().compare("assign") == 0) {
				if(matchPattern(n, lhs, rhs, true)) {
					vector<Node*> children = n.getChild();
					Node left = *children.at(0);
					ans.push_back(Pair(n.getProgLine(), pkb->getVarIndex(left.getData())));
				}
			}
			else {
				vector<Node*> children = n.getChild();
				for(int i=0; i<int(children.size()); i++)
					st.push(*children.at(i));
			}
		}
		else {
			if(n.getType().compare("assign") == 0) {
				if(matchPattern(n, lhs, rhs, false)) {
					ans.push_back(Pair(n.getProgLine(), n.getProgLine()));
				}
			}
			else {
				vector<Node*> children = n.getChild();
				for(int i=0; i<int(children.size()); i++)
					st.push(*children.at(i));
			}
		}
	}

	return ans;
}

vector<Pair> QueryEvaluator::findIf(Node startNode, string lhs, string rhs, Relationship r) {
	vector<Pair> ans;
	stack<Node> st;
	st.push(startNode);
	
	while(!st.empty()) {
		Node n = st.top();
		st.pop();
		if(r.getToken1Type() == Relationship::SYNONYM) {
			if(n.getType().compare("if") == 0) {
				if(matchPattern(n, lhs, rhs, true)) {
					vector<Node*> children = n.getChild();
					Node left = *children.at(0);
					ans.push_back(Pair(n.getProgLine(), pkb->getVarIndex(left.getData())));
				}
				vector<Node*> children = n.getChild();
				for(int i=0; i<int(children.size()); i++)
					st.push(*children.at(i));
			}
			else {
				vector<Node*> children = n.getChild();
				for(int i=0; i<int(children.size()); i++)
					st.push(*children.at(i));
			}
		}
		else {
			if(n.getType().compare("if") == 0) {
				if(matchPattern(n, lhs, rhs, false)) {
					ans.push_back(Pair(n.getProgLine(), n.getProgLine()));
				}
				vector<Node*> children = n.getChild();
				for(int i=0; i<int(children.size()); i++)
					st.push(*children.at(i));
			}
			else {
				vector<Node*> children = n.getChild();
				for(int i=0; i<int(children.size()); i++)
					st.push(*children.at(i));
			}
		}
	}

	return ans;
}

vector<Pair> QueryEvaluator::findWhile(Node startNode, string lhs, string rhs, Relationship r) {
	vector<Pair> ans;
	stack<Node> st;
	st.push(startNode);
	
	while(!st.empty()) {
		Node n = st.top();
		st.pop();
		if(r.getToken1Type() == Relationship::SYNONYM) {
			if(n.getType().compare("while") == 0) {
				if(matchPattern(n, lhs, rhs, true)) {
					vector<Node*> children = n.getChild();
					Node left = *children.at(0);
					ans.push_back(Pair(n.getProgLine(), pkb->getVarIndex(left.getData())));
				}
				vector<Node*> children = n.getChild();
				for(int i=0; i<int(children.size()); i++)
					st.push(*children.at(i));
			}
			else {
				vector<Node*> children = n.getChild();
				for(int i=0; i<int(children.size()); i++)
					st.push(*children.at(i));
			}
		}
		else {
			if(n.getType().compare("while") == 0) {
				if(matchPattern(n, lhs, rhs, false)) {
					ans.push_back(Pair(n.getProgLine(), n.getProgLine()));
				}
				vector<Node*> children = n.getChild();
				for(int i=0; i<int(children.size()); i++)
					st.push(*children.at(i));
			}
			else {
				vector<Node*> children = n.getChild();
				for(int i=0; i<int(children.size()); i++)
					st.push(*children.at(i));
			}
		}
	}

	return ans;
}

bool QueryEvaluator::matchPattern(Node n, string lhs, string rhs, bool leftIsSyn) {
	lhs.erase(std::remove(lhs.begin(), lhs.end(), '\"'), lhs.end());
	rhs.erase(std::remove(rhs.begin(), rhs.end(), '\"'), rhs.end());

	bool leftMatch=false, rightMatch=false;
	vector<Node*> children = n.getChild();
	Node left = *children.at(0);
	Node right = *children.at(1);

	//Check if lhs matches pattern
	if(lhs.compare("_") == 0 || lhs.compare(left.getData()) == 0 || leftIsSyn) {
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
				for(int i=0; i<int(children.size()); i++)
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

	string aData = a.getData();
	string bData = b.getData();
	
	aData.erase(std::remove(aData.begin(), aData.end(), ' '), aData.end());
	bData.erase(std::remove(bData.begin(), bData.end(), ' '), bData.end());
	//aData.erase(std::remove(aData.begin(), aData.end(), ')'), aData.end());
	//bData.erase(std::remove(bData.begin(), bData.end(), ')'), bData.end());
	if(children1.size() != children2.size()) {
		return false;
	}

	if(aData.compare(bData) != 0) {
		return false;
	}

	if(aData.compare(bData) == 0 && children1.size() == 0) {
		return true;
	}

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
			if(st.empty()){
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
		if((word[i]=='+')||(word[i]=='-')||(word[i]=='/')||(word[i]=='*')||(word[i]=='=')||(word[i]=='(')||(word[i]==')')){
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
