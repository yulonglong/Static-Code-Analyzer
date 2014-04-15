//#include <iostream>
#include <string>
#include <algorithm>
#include "QueryEvaluator.h"
#include <ctype.h>
#include <set>
#include <stack>


using namespace std;
QueryEvaluator::QueryEvaluator(PKB* p){
	pkb = p;
}

QueryEvaluator::~QueryEvaluator(){
}

vector<int> QueryEvaluator::evaluateQuery(Query q){
	cout<<"In evaluateQuery"<<endl;
	vector<Relationship> relations = q.getRelVect();
	vector<vector<int>> answers;
	TypeTable *t = pkb->getTypeTable();
	Follows *f = pkb->getFollows();
	cout<<"Before for loop"<<endl;
	for(vector<Relationship>::iterator it = relations.begin(); it!=relations.end(); it++){

		string token1 = it->getToken1();
		string token2 = it->getToken2();

		if(token1==token2 && token1!="_"){
			answers.clear();
			break;
		}

		string selectedSyn = q.getSelectedSyn();
		unordered_map<string, TypeTable::SynType> m = q.getSynTable();
		unordered_map<string, TypeTable::SynType>::iterator i = m.find(selectedSyn);

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

		cout<<"just before switch"<<endl;
		switch(it->getRelType()){
		case Relationship::FOLLOWS: {	
			cout<<"In Follows"<<endl;
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
		case Relationship::PARENT:
			{
				cout<<"In evaluateQuery case PARENT"<<endl;
				if((isdigit(token1[0]) && isdigit(token2[0])) || (selectedSyn!=token1 && selectedSyn!=token2)) { //if first char is a digit, then the token must be a number
					if(evaluateParentBoolean(*it, m)){
						cout<<"Called evaluateParentBoolean"<<endl;
						answers.push_back(t->getAllStmts(i->second));
					}
				}
				else {
					cout<<"Called evaluateParent"<<endl;
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
				cout<<"Calling evaluateParentStar"<<endl;
				answers.push_back(evaluateParentStar(*it, m, q.getSelectedSyn()));
			}
			break;
									}

		case Relationship::MODIFIES:
			{	

			if((isdigit(token1[0]) && isdigit(token2[0])) || (selectedSyn!=token1 && selectedSyn!=token2)) { //if first char is a digit, then the token must be a number
				cout<<"Calling evaluateModifiesBoolean"<<endl;
				if(evaluateModifiesBoolean(*it, m)){
					cout<<"type is"<<func(i->second)<<endl;
					cout<<"i->first = "<< i->first<<endl;
					answers.push_back(t->getAllStmts(i->second));
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

			if((isdigit(token1[0]) && isdigit(token2[0])) || (selectedSyn!=token1 && selectedSyn!=token2)) { //if first char is a digit, then the token must be a number
				if(evaluateUsesBoolean(*it, m)){
					answers.push_back(t->getAllStmts(i->second));
				}
			}
			else {
				answers.push_back(evaluateUses(*it, m, q.getSelectedSyn()));
			}
			break;
									}
		case Relationship::PATTERN:
			{	
				//
				//if(q.getSelectedSyn().compare(q.getPatternSyn()) == 0)
					answers.push_back(evaluatePattern(token1, token2));
				//else {
				//	vector<int> proxy = evaluatePattern(token1, token2);
				//	if(proxy.size()==0)
				//		answers.push_back(proxy);
			}
		}
	}

	if(relations.empty()){
		string selectedSyn = q.getSelectedSyn();
		unordered_map<string, TypeTable::SynType> m = q.getSynTable();
		unordered_map<string, TypeTable::SynType>::iterator i = m.find(selectedSyn);
		if(i->second!=TypeTable::VARIABLE){
			answers.push_back(t->getAllStmts(i->second));
		}
		else if(i->second==TypeTable::PROGLINE){
			answers.push_back(t->getAllStmts(TypeTable::STMT));
		}
		else{
			VarTable *v = pkb->getVarTable();
			answers.push_back(v->getAllVarIndex());
		}
	}
	cout<<"here2"<<endl;
	return intersectAnswers(answers);	
}

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
		}
	}
	return answers;
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
}

vector<int> QueryEvaluator::evaluateFollows(Relationship r, unordered_map<string, TypeTable::SynType> m, string selectedSyn){
	string tk1 = r.getToken1();
	string tk2 = r.getToken2();
	Follows *f = pkb->getFollows();
	vector<int> answer;
	unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(tk1);
	unordered_map<string, TypeTable::SynType>::iterator i2 = m.find(tk2);

	if(isalpha(tk1[0]) && isalpha(tk2[0]) && selectedSyn==tk1){
		cout<<"Calling getFollowedBy(TYPE, TYPE)"<<endl;
		return f->getFollowedBy(i1->second, i2->second);
	}
	else if(isalpha(tk1[0]) && isalpha(tk2[0]) && selectedSyn==tk2){
		cout<<"Calling getFollows(TYPE, TYPE)"<<endl;
		return f->getFollows(i1->second, i2->second);
	}
	else if(selectedSyn==tk1){
		cout<<"Calling getFollowedBy(TYPE, STMTNUM)"<<endl;
		int temp;
		try{
			temp = f->getFollowedBy(i1->second, atoi(tk2.c_str()));
		}catch(...){
		}
		answer.push_back(temp);
		return answer;
	}
	else {
		cout<<"Calling getFollows(TYPE, STMTNUM)"<<endl;
		answer.push_back(f->getFollows(i2->second, atoi(tk1.c_str())));
		return answer;
	}
}

string QueryEvaluator::func(TypeTable::SynType t){
	switch(t){
	case TypeTable::ASSIGN:
		return "assign";
	case TypeTable::WHILE:
		return "while";
	}
	return "hi";
}

vector<int> QueryEvaluator::evaluateFollowsStar(Relationship r, unordered_map<string, TypeTable::SynType> m, string selectedSyn){
	string tk1=r.getToken1();
	string tk2=r.getToken2();
	Follows *f = pkb->getFollows();
	TypeTable *t = pkb->getTypeTable();
	set<int> answer;
	vector<int> selected;
	vector<int> vectorAnswer;
	int stmtNumber = 0;
	unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(tk1);
	unordered_map<string, TypeTable::SynType>::iterator i2 = m.find(tk2);

	//Select w such that Follows*(w, a)
	if(isalpha(tk1[0]) && isalpha(tk2[0]) && selectedSyn==tk1){
		cout<<"Handling Follows*(type, type) with first token selected"<<endl;
		selected = t->getAllStmts(i1->second);	//get all while statements

		for(vector<int>::iterator it = selected.begin(); it!=selected.end(); it++){
			cout<<"Calling getFollows(type, stmtnum)"<<endl;
			stmtNumber = f->getFollows(TypeTable::STMT, *it);
			do{			
				if(stmtNumber!=-1){
					if(t->isType(i2->second,stmtNumber)){
						answer.insert(*it);
						break;
					}
				}
				else{
					break;
				}
				cout<<"Calling getFollows(type, stmtnum)"<<endl;
				stmtNumber = f->getFollows(TypeTable::STMT, stmtNumber);
			}while(true);
		}
	}

	//Select a such that Follows*(w, a)
	else if(isalpha(tk1[0]) && isalpha(tk2[0]) && selectedSyn==tk2){
		cout<<"Handling Follows*(type, type) with second token selected"<<endl;
		selected = t->getAllStmts(i1->second);

		for(vector<int>::iterator it = selected.begin(); it!=selected.end(); it++){
			cout<<"Calling getFollows(type, stmtnum)"<<endl;
			stmtNumber = f->getFollows(TypeTable::STMT, *it);
			do{			
				if(stmtNumber!=-1){
					cout<<"Calling TypeTable->isType"<<endl;
					if(t->isType(i2->second, stmtNumber)){
						answer.insert(stmtNumber);
					}
				}
				else{
					break;
				}
				cout<<"Calling getFollows(type, stmtnum)"<<endl;
				stmtNumber = f->getFollows(TypeTable::STMT, stmtNumber);
			}while(true);
		}
	}

	//Select a such that Follows*(a, 13)
	else if(selectedSyn==tk1){
		cout<<"Handling Follows*(type, stmtnum)"<<endl;
		stmtNumber = atoi(tk2.c_str());
		do{			
			cout<<"Calling getFollowedBy(type, stmtnum)"<<endl;
			stmtNumber = f->getFollowedBy(TypeTable::STMT, stmtNumber);
			if(stmtNumber!=-1){
				cout<<"Calling TypeTable::isType"<<endl;
				if(t->isType(i1->second, stmtNumber)){
					answer.insert(stmtNumber);
				}
			}
			else{
				break;
			}
			
		}while(true);
	}

	//Select a such that Follows*(3, a)
	else {
		cout<<"Handling Follows*(stmtnum, type)"<<endl;
		stmtNumber = atoi(tk1.c_str());
		do{			
			cout<<"Calling getFollows(type, stmtnum)"<<endl;
			stmtNumber = f->getFollows(TypeTable::STMT, stmtNumber);
			if(stmtNumber!=-1){
				if(t->isType(i2->second, stmtNumber)){
					answer.insert(stmtNumber);
				}
			}
			else{
				break;
			}
			
		}while(true);
	}

	copy(answer.begin(), answer.end(), back_inserter(vectorAnswer));

	return vectorAnswer;
}

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
}

vector<int> QueryEvaluator::evaluateParent(Relationship r, unordered_map<string, TypeTable::SynType> m, string selectedSyn){
	string tk1 = r.getToken1();
	string tk2 = r.getToken2();
	Parent *p = pkb->getParent();
	vector<int> answer;
	unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(tk1);
	unordered_map<string, TypeTable::SynType>::iterator i2 = m.find(tk2);
	unordered_map<string, TypeTable::SynType>::iterator i3 = m.find(selectedSyn);
	if(isalpha(tk1[0]) && isalpha(tk2[0]) && selectedSyn==tk1){
		cout<<"Calling getParent(TYPE, TYPE)"<<endl;
		return p->getParent(i1->second, i2->second);
	}
	else if(isalpha(tk1[0]) && isalpha(tk2[0]) && selectedSyn==tk2){
		cout<<"Calling getChildren(TYPE, TYPE)"<<endl;
		return p->getChildren(i1->second, i2->second);
	}
	else if(selectedSyn==tk1){
		cout<<"Calling getParent(TYPE, STMTNUM)"<<endl;
		answer.push_back( p->getParent(i1->second, atoi(tk2.c_str())));
		return answer;
	}
	else {
		cout<<"Calling getChildren(TYPE, STMTNUM)"<<endl;
		return p->getChildren(i2->second, atoi(tk1.c_str()));
	}
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
}

vector<int> QueryEvaluator::evaluateModifies(Relationship r, std::unordered_map<std::string, TypeTable::SynType> m, string selectedSyn) {
	string tk1=r.getToken1();
	string tk2=r.getToken2();
	Modifies *mod = pkb->getModifies();
	TypeTable *t = pkb->getTypeTable();
	vector<int> selected;
	set<int> answer;
	unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(tk1);
	unordered_map<string, TypeTable::SynType>::iterator i2 = m.find(tk2);

	//Select a Modifies(a,v)
	if(isalpha(tk1[0]) && isalpha(tk2[0]) && selectedSyn==tk1){
		cout<<"Calling getModifies(TYPE)"<<endl;
		selected = mod->getModifies(i1->second);
		return selected;
	}

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
	}

	//Modifies(a, "x")
	else if(isalpha(tk1[0])){
		string varName = tk2.substr(1,tk2.length()-2);
		cout<<"Calling getModifies(TYPE, varName)"<<endl;
		return mod->getModifies(i1->second, varName);
	}

	//Select v such that Modifies(1, v);
	else {
		cout<<"Calling getModifies(STMTNUM)"<<endl;
		return mod->getModifies(atoi(tk1.c_str()));
	}
}

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

	//Modifies(1, "x")
	else{
		return mod->isModifies(atoi(tk1.c_str()), tk2.substr(1, tk2.length()-2));
	}

	return false;
}

vector<int> QueryEvaluator::evaluateUses(Relationship r, std::unordered_map<std::string, TypeTable::SynType> m, string selectedSyn) {
	string tk1=r.getToken1();
	string tk2=r.getToken2();
	Uses *use = pkb->getUses();
	TypeTable *t = pkb->getTypeTable();
	vector<int> selected;
	set<int> answer;
	unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(tk1);
	unordered_map<string, TypeTable::SynType>::iterator i2 = m.find(tk2);

	//Select a Uses(a,v)
	if(isalpha(tk1[0]) && isalpha(tk2[0]) && selectedSyn==tk1){
		cout<<"Calling getUses(TYPE)"<<endl;
		selected = use->getUses(i1->second);
		return selected;
	}

	//Select v Uses(a,v)
	else if(isalpha(tk1[0]) && isalpha(tk2[0]) && selectedSyn==tk2){
		selected = t->getAllStmts(TypeTable::ASSIGN);
		vector<int> usedVar;
		for(vector<int>::iterator it = selected.begin(); it!=selected.end(); it++){
			cout<<"Calling getUses(STMTNUM)"<<endl;
			usedVar = use->getUses(*it);
			answer.insert(usedVar.begin(), usedVar.end());
		}
		selected.clear();
		copy(answer.begin(), answer.end(), back_inserter(selected));
		return selected;
	}

	//Select a Uses(a, "x")
	else if(isalpha(tk1[0])){
		string varName = tk2.substr(1,tk2.length()-2);
		cout<<"Calling getUses(TYPE, VARNAME)"<<endl;
		return use->getUses(i1->second, varName);
	}

	//Select v such that Uses(1, v);
	else {
		cout<<"Calling getUses(STMTNUM)"<<endl;
		return use->getUses(atoi(tk1.c_str()));
	}
}

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

	//Modifies(1, "x")
	else{
		return use->isUses(atoi(tk1.c_str()), tk2.substr(1, tk2.length()-2));
	}

	return false;
}

vector<int> QueryEvaluator::evaluatePattern(string leftHandSide, std::string rightHandSide) {
	vector<int> answers;
	VarTable* varTable = pkb->getVarTable();

	leftHandSide.erase(std::remove(leftHandSide.begin(), leftHandSide.end(), '\"'), leftHandSide.end());
	rightHandSide.erase(std::remove(rightHandSide.begin(), rightHandSide.end(), '\"'), rightHandSide.end());
	
	if(leftHandSide.compare("v")==0) {
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
				for(int i=0; i<children.size(); i++) {
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
				if(childOne.getData().compare(right)==0 && childTwo.getData().compare(left)==0)
					return true;
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
	return false;
}