//#include <iostream>
#include <string>
#include "QueryEvaluator.h"
#include <ctype.h>
#include <set>


using namespace std;
QueryEvaluator::QueryEvaluator(PKB p){
	pkb = &p;
}

vector<int> QueryEvaluator::evaluateQuery(Query q){
	vector<Relationship> relations = q.getRelVect();
	vector<vector<int>> answers;

	TypeTable t = pkb->getTypeTable();
	Follows f = pkb->getFollows();
	unordered_map<string, TypeTable::SynType> m = q.getSynTable();

	for(vector<Relationship>::iterator it = relations.begin(); it!=relations.end(); it++){
		switch(it->getRelType()){
		case Relationship::FOLLOWS: {
			string token1 = it->getToken1();
			string token2 = it->getToken2();
			string selectedSyn = q.getSelectedSyn();
			
			std::unordered_map<string, TypeTable::SynType>::iterator i = q.getSynTable().find(selectedSyn);
			if((!isdigit(token1[0]) && !isdigit(token2[0])) || (selectedSyn!=token1 && selectedSyn!=token2)) { //if first char is a digit, then the token must be a number
				if(evaluateFollowsBoolean(*it, m)){
					answers.push_back(t.getAllStmts(i->second));
				}
			}
			else {
				answers.push_back(evaluateFollows(*it, m, q.getSelectedSyn()));
			}
			break;
									}
		case Relationship::FOLLOWSSTAR:
			answers.push_back(evaluateFollowsStar(*it, m, q.getSelectedSyn()));
			break;
		case Relationship::PARENT:
			{
			string token1 = it->getToken1();
			string token2 = it->getToken2();
			string selectedSyn = q.getSelectedSyn();
			unordered_map<string, TypeTable::SynType> m = q.getSynTable();
			std::unordered_map<string, TypeTable::SynType>::iterator i = q.getSynTable().find(selectedSyn);

			if((!isdigit(token1[0]) && !isdigit(token2[0])) || (selectedSyn!=token1 && selectedSyn!=token2)) { //if first char is a digit, then the token must be a number
				if(evaluateParentBoolean(*it, m)){
					answers.push_back(t.getAllStmts(i->second));
				}
				else {
					answers.push_back(evaluateParent(*it, m, q.getSelectedSyn()));
				}
			}
			break;
									}
		case Relationship::PARENTSTAR:
			//answers.push_back(evaluateParentStar(*it));
			break;
		}
	}

	return intersectAnswers(answers);	
}

bool QueryEvaluator::evaluateQueryBoolean(Query q){
	vector<Relationship> relations = q.getRelVect();
	bool answers = true;
	Follows f = pkb->getFollows();
	for(vector<Relationship>::iterator it = relations.begin(); it!=relations.end(); it++){
		switch(it->getRelType()){
		case Relationship::FOLLOWS: 
			answers = answers && evaluateFollowsBoolean(*it, q.getSynTable());
			break;
		case Relationship::FOLLOWSSTAR:
			//answers = answers && evaluateFollowsStarBoolean(*it);
			break;
		case Relationship::PARENT:
			answers = answers && evaluateParentBoolean(*it, q.getSynTable());
			break;
		case Relationship::PARENTSTAR:
			//answers = answers && evaluateParentStarBoolean(*it);
			break;
		}
	}
	return answers;
}

bool QueryEvaluator::evaluateParentBoolean(Relationship r, unordered_map<string, TypeTable::SynType> m){
	string tk1 = r.getToken1();
	string tk2 = r.getToken2();
	Parent p = pkb->getParent();
	if(isdigit(tk1[0]) && isdigit(tk2[0])){
		return p.isParent(atoi(tk1.c_str()), atoi(tk2.c_str()));
	}
	else if(isalpha(tk1[0]) && isalpha(tk2[0])){
		unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(tk1);
		unordered_map<string, TypeTable::SynType>::iterator i2 = m.find(tk2);
		return p.isParent(i1->second, i2->second);
	}
	else if(isalpha(tk1[0])){
		unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(tk1);
		return p.isParent(i1->second, atoi(tk2.c_str()));
	}
	else {
		unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(tk2);
		return p.isChildren(i1->second, atoi(tk1.c_str()));
	}
}

bool QueryEvaluator::evaluateFollowsBoolean(Relationship r, unordered_map<string, TypeTable::SynType> m){
	string tk1 = r.getToken1();
	string tk2 = r.getToken2();
	Follows f = pkb->getFollows();

	if(isdigit(tk1[0]) && isdigit(tk2[0])){
		return f.isFollows(atoi(tk1.c_str()), atoi(tk2.c_str()));
	}
	else if(isalpha(tk1[0]) && isalpha(tk2[0])){
		unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(tk1);
		unordered_map<string, TypeTable::SynType>::iterator i2 = m.find(tk2);
		return f.isFollows(i1->second, i2->second);
	}
	else if(isalpha(tk1[0])){
		unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(tk1);
		return (f.getFollows(i1->second, atoi(tk2.c_str()))==-1)?false:true;
	}
	else {
		unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(tk2);
		return (f.getFollowedBy(i1->second, atoi(tk1.c_str()))==-1)?false:true;
	}
}

vector<int> QueryEvaluator::intersectAnswers(vector<vector<int>> ans){
	vector<int> first = ans[0];
	vector<int> queryAnswers;
	for(vector<int>::iterator it3 = first.begin(); it3!=first.end(); it3++){
		bool insert = true;
		for(vector<vector<int>>::iterator it1 = ans.begin()+1; it1!=ans.end(); it1++){
			bool change = true;
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

vector<int> QueryEvaluator::evaluateFollows(Relationship r, unordered_map<string, TypeTable::SynType> m, string selectedSyn){
	string tk1 = r.getToken1();
	string tk2 = r.getToken2();
	Follows f = pkb->getFollows();
	vector<int> answer;
	unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(tk1);
	unordered_map<string, TypeTable::SynType>::iterator i2 = m.find(tk2);

	if(isalpha(tk1[0]) && isalpha(tk2[0]) && selectedSyn==tk1){
		return f.getFollowedBy(i1->second, i2->second);
	}
	else if(isalpha(tk1[0]) && isalpha(tk2[0]) && selectedSyn==tk2){
		return f.getFollows(i1->second, i2->second);
	}
	else if(selectedSyn==tk1){
		answer.push_back(f.getFollowedBy(i1->second, atoi(tk2.c_str())));
		return answer;
	}
	else {
		answer.push_back(f.getFollows(i2->second, atoi(tk1.c_str())));
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
	Follows f = pkb->getFollows();
	TypeTable t = pkb->getTypeTable();
	set<int> answer;
	vector<int> selected;
	vector<int> vectorAnswer;
	int stmtNumber = 0;
	unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(tk1);
	unordered_map<string, TypeTable::SynType>::iterator i2 = m.find(tk2);

	//Select w such that Follows*(w, a)
	if(isalpha(tk1[0]) && isalpha(tk2[0]) && selectedSyn==tk1){
		selected = t.getAllStmts(i1->second);	//get all while statements

		for(vector<int>::iterator it = selected.begin(); it!=selected.end(); it++){
			stmtNumber = f.getFollows(TypeTable::STMT, *it);
			do{			
				if(stmtNumber!=1){
					if(t.getType(stmtNumber)==i2->second){
						answer.insert(*it);
						break;
					}
				}
				else{
					break;
				}
				stmtNumber = f.getFollows(TypeTable::STMT, stmtNumber);
			}while(true);
		}
	}

	//Select a such that Follows*(w, a)
	else if(isalpha(tk1[0]) && isalpha(tk2[0]) && selectedSyn==tk2){
		selected = t.getAllStmts(i1->second);

		for(vector<int>::iterator it = selected.begin(); it!=selected.end(); it++){
			stmtNumber = f.getFollows(TypeTable::STMT, *it);
			do{			
				if(stmtNumber!=1){
					if(t.getType(stmtNumber)==i2->second){
						answer.insert(stmtNumber);
					}
				}
				else{
					break;
				}
				stmtNumber = f.getFollows(TypeTable::STMT, stmtNumber);
			}while(true);
		}
	}

	//Select a such that Follows*(a, 13)
	else if(selectedSyn==tk1){
		stmtNumber = atoi(tk2.c_str());
		do{			
			stmtNumber = f.getFollowedBy(TypeTable::STMT, stmtNumber);
			if(stmtNumber!=1){
				if(t.getType(stmtNumber)==i1->second){
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
		stmtNumber = atoi(tk1.c_str());
		do{			
			stmtNumber = f.getFollows(TypeTable::STMT, stmtNumber);
			if(stmtNumber!=1){
				if(t.getType(stmtNumber)==i2->second){
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
	Follows f = pkb->getFollows();
	int stmtnum=0;
	vector<int> temp;

	bool flag = false;

	if(isdigit(tk1[0]) && isdigit(tk2[0])){
		stmtnum = atoi(tk1.c_str());
		while(stmtnum!=-1){
			stmtnum = f.getFollows(TypeTable::STMT, stmtnum);
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
	Parent p = pkb->getParent();
	vector<int> answer;
	unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(tk1);
	unordered_map<string, TypeTable::SynType>::iterator i2 = m.find(tk2);
	unordered_map<string, TypeTable::SynType>::iterator i3 = m.find(selectedSyn);
	if(isalpha(tk1[0]) && isalpha(tk2[0]) && selectedSyn==tk1){
		return p.getParent(i1->second, i2->second);
	}
	else if(isalpha(tk1[0]) && isalpha(tk2[0]) && selectedSyn==tk2){
		return p.getChildren(i1->second, i2->second);
	}
	else if(selectedSyn==tk1){
		answer.push_back( p.getParent(i1->second, atoi(tk2.c_str())));
		return answer;
	}
	else {
		return p.getChildren(i2->second, atoi(tk1.c_str()));
	}
}



vector<int> QueryEvaluator::evaluateParentStar(Relationship r, unordered_map<string, TypeTable::SynType> m, string selectedSyn){
	string tk1=r.getToken1();
	string tk2=r.getToken2();
	Parent p = pkb->getParent();
	TypeTable t = pkb->getTypeTable();
	set<int> answer;
	vector<int> selected;
	vector<int> vectorAnswer;
	int stmtNumber = 0;
	unordered_map<string, TypeTable::SynType>::iterator i1 = m.find(tk1);
	unordered_map<string, TypeTable::SynType>::iterator i2 = m.find(tk2);

	//Select w such that Parent*(w, a)
	if(isalpha(tk1[0]) && isalpha(tk2[0]) && selectedSyn==tk1){
		selected = t.getAllStmts(i2->second);	//get all assign statements

		for(vector<int>::iterator it = selected.begin(); it!=selected.end(); it++){
			stmtNumber = p.getParent(*it);
			answer.insert(stmtNumber);
			stmtNumber = p.getParent(stmtNumber);
			while(stmtNumber!=-1){
				answer.insert(stmtNumber);
				stmtNumber = p.getParent(stmtNumber);
			}
		}
	}

	//Select a such that Parent*(w, a)
	else if(isalpha(tk1[0]) && isalpha(tk2[0]) && selectedSyn==tk2){

		selected = t.getAllStmts(i2->second);	//get all assign statements

		for(vector<int>::iterator it = selected.begin(); it!=selected.end(); it++){
			stmtNumber = p.getParent(*it);
			if(stmtNumber!=-1)
				answer.insert(stmtNumber);
		}
	}

	//Select w such that Parent*(w, 13)
	else if(selectedSyn==tk1){

		stmtNumber = atoi(tk2.c_str());
		stmtNumber = p.getParent(stmtNumber);

		while(stmtNumber!=-1){
			answer.insert(stmtNumber);
			stmtNumber = p.getParent(stmtNumber);
		}
	}

	//Select a such that Parent*(3, a)
	else {
		
		selected = t.getAllStmts(i2->second);
		
		for(vector<int>::iterator it = selected.begin(); it!=selected.end(); it++){			
			stmtNumber = p.getParent(*it);
			while(stmtNumber!=-1){
				if(stmtNumber == atoi(tk1.c_str())){
					answer.insert(*it);	
					break;
				}
				stmtNumber = p.getParent(stmtNumber);
			}
			
		}
	}

	copy(answer.begin(), answer.end(), back_inserter(vectorAnswer));

	return vectorAnswer;
}

bool QueryEvaluator::evaluateParentStarBoolean(Relationship r, std::unordered_map<std::string, TypeTable::SynType> m){
	string tk1=r.getToken1();
	string tk2=r.getToken2();
	Parent p = pkb->getParent();
	int stmtnum=0;
	vector<int> temp;

	bool flag = false;

	//Parent*(1,8)
	if(isdigit(tk1[0]) && isdigit(tk2[0])){
		stmtnum = atoi(tk2.c_str());
		while(stmtnum!=-1){
			stmtnum = p.getParent(stmtnum);
			if(stmtnum==atoi(tk2.c_str()))
				flag = true;
			if(stmtnum<atoi(tk2.c_str()))
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

