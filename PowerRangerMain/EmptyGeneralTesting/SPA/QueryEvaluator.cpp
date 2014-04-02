#include <iostream>
#include <string>
#include "QueryEvaluator.h"
#include <ctype.h>
#include "Follows.h"
#include "Parent.h"
#include <set>


using namespace std;

vector<int> QueryEvaluator::evaluateQuery(Query q){
	vector<Relationship> relations = q.getRelVect();
	vector<vector<int>> answers;
	Follows f;
	TypeTable t;
	unordered_map<string, Query::SynType> m = q.getSynTable();
	for(vector<Relationship>::iterator it = relations.begin(); it!=relations.end(); it++){
		switch(it->getRelType()){
		case Relationship::FOLLOWS: {
			string token1 = it->getToken1();
			string token2 = it->getToken2();
			string selectedSyn = q.getSelectedSyn();
			
			std::unordered_map<string, Query::SynType>::iterator i = q.getSynTable().find(selectedSyn);

			if((!isdigit(token1[0]) && !isdigit(token2[0])) || (selectedSyn!=token1 && selectedSyn!=token2)) { //if first char is a digit, then the token must be a number
				if(evaluateFollowsBoolean(*it, m)){
					answers.push_back( t.getAllStmts(i->second));
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
			unordered_map<string, Query::SynType> m = q.getSynTable();
			std::unordered_map<string, Query::SynType>::iterator i = q.getSynTable().find(selectedSyn);

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
			answers.push_back(evaluateParentStar(*it));
			break;
		}
	}

	return intersectAnswers(answers);	
}

bool QueryEvaluator::evaluateQueryBoolean(Query q){
	vector<Relationship> relations = q.getRelVect();
	bool answers = true;
	Follows f;
	for(vector<Relationship>::iterator it = relations.begin(); it!=relations.end(); it++){
		switch(it->getRelType()){
		case Relationship::FOLLOWS: 
			answers = answers && evaluateFollowsBoolean(*it, q.getSynTable());
			break;
		case Relationship::FOLLOWSSTAR:
			answers = answers && evaluateFollowsStarBoolean(*it);
			break;
		case Relationship::PARENT:
			answers = answers && evaluateParentBoolean(*it, q.getSynTable());
		case Relationship::PARENTSTAR:
			answers = answers && evaluateParentStarBoolean(*it);
		}
	}
	return answers;
}

bool QueryEvaluator::evaluateParentBoolean(Relationship r, unordered_map<string, Query::SynType> m){
	string tk1 = r.getToken1();
	string tk2 = r.getToken2();
	Parent p;
	if(isdigit(tk1[0]) && isdigit(tk2[0])){
		return p.isParent(atoi(tk1.c_str()), atoi(tk2.c_str()));
	}
	else if(isalpha(tk1[0]) && isalpha(tk2[0])){
		unordered_map<string, Query::SynType>::iterator i1 = m.find(tk1);
		unordered_map<string, Query::SynType>::iterator i2 = m.find(tk2);
		return p.isParent(i1->second, i2->second);
	}
	else if(isalpha(tk1[0])){
		unordered_map<string, Query::SynType>::iterator i1 = m.find(tk1);
		return p.isParent(i1->second, atoi(tk2.c_str()));
	}
	else {
		unordered_map<string, Query::SynType>::iterator i1 = m.find(tk2);
		return p.isChildren(i1->second, atoi(tk1.c_str()));
	}
}

bool QueryEvaluator::evaluateFollowsBoolean(Relationship r, unordered_map<string, Query::SynType> m){
	string tk1 = r.getToken1();
	string tk2 = r.getToken2();
	Follows f;
	if(isdigit(tk1[0]) && isdigit(tk2[0])){
		return f.isFollows(atoi(tk1.c_str()), atoi(tk2.c_str()));
	}
	else if(isalpha(tk1[0]) && isalpha(tk2[0])){
		unordered_map<string, Query::SynType>::iterator i1 = m.find(tk1);
		unordered_map<string, Query::SynType>::iterator i2 = m.find(tk2);
		return f.isFollows(i1->second, i2->second);
	}
	else if(isalpha(tk1[0])){
		unordered_map<string, Query::SynType>::iterator i1 = m.find(tk1);
		return (f.getFollows(i1->second, atoi(tk2.c_str()))==-1)?false:true;
	}
	else {
		unordered_map<string, Query::SynType>::iterator i1 = m.find(tk2);
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

vector<int> QueryEvaluator::evaluateFollows(Relationship r, unordered_map<string, Query::SynType> m, string selectedSyn){
	string tk1 = r.getToken1();
	string tk2 = r.getToken2();
	Follows f;
	vector<int> answer;
	unordered_map<string, Query::SynType>::iterator i1 = m.find(tk1);
	unordered_map<string, Query::SynType>::iterator i2 = m.find(tk2);
	if(isalpha(tk1[0]) && isalpha(tk2[0]) && selectedSyn==tk1){
		return f.getFollows(i1->second, i2->second);
	}
	else if(isalpha(tk1[0]) && isalpha(tk2[0]) && selectedSyn==tk2){
		return f.getFollowedBy(i1->second, i2->second);
	}
	else if(selectedSyn==tk1){
		answer.push_back(f.getFollows(i1->second, atoi(tk2.c_str())));
		return answer;
	}
	else {
		answer.push_back(f.getFollows(i2->second, atoi(tk1.c_str())));
		return answer;
	}
}

vector<int> QueryEvaluator::evaluateFollowsStar(Relationship r, unordered_map<string, Query::SynType> m, string selectedSyn){
	string tk1=r.getToken1();
	string tk2=r.getToken2();
	Follows f;
	TypeTable t;
	set<int> answer;
	vector<int> selected;
	int stmtNumber = 0;
	unordered_map<string, Query::SynType>::iterator i1 = m.find(tk1);
	unordered_map<string, Query::SynType>::iterator i2 = m.find(tk2);

	if(isalpha(tk1[0]) && isalpha(tk2[0]) && selectedSyn==tk1){
		selected = t.getAllStmts(i2->second);

		for(vector<int>::iterator it = selected.begin(); it!=selected.end(); ++it){
			while(stmtNumber!=-1){

			}
		}
	}
	return selected;
}

bool QueryEvaluator::evaluateFollowsStarBoolean(Relationship r){
	bool v;
	return v;
}

vector<int> QueryEvaluator::evaluateParent(Relationship r, unordered_map<string, Query::SynType> m, string selectedSyn){
	string tk1 = r.getToken1();
	string tk2 = r.getToken2();
	Parent p;
	vector<int> answer;
	unordered_map<string, Query::SynType>::iterator i1 = m.find(tk1);
	unordered_map<string, Query::SynType>::iterator i2 = m.find(tk2);
	unordered_map<string, Query::SynType>::iterator i3 = m.find(selectedSyn);
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

vector<int> QueryEvaluator::evaluateParentStar(Relationship r){
	vector<int> v;
	return v;
}

bool QueryEvaluator::evaluateParentStarBoolean(Relationship r){
	bool v;
	return v;
}

