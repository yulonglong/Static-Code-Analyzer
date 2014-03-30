#include <iostream>
#include <string>
#include "QueryEvaluator.h"
#include <ctype.h>
#include "Follows.h"


using namespace std;

vector<int> QueryEvaluator::evaluateQuery(Query q){
	vector<Relationship> relations = q.getRelVect();
	vector<vector<int>> answers;
	Follows f;
	for(vector<Relationship>::iterator it = relations.begin(); it!=relations.end(); it++){
		switch(it->getRelType()){
		case Relationship::FOLLOWS: {
			string token1 = it->getToken1();
			string token2 = it->getToken2();
			string selectedSyn = q.getSelectedSyn();
			unordered_map<string, STYPE> m = q.getSynTable();
			std::unordered_map<string, STYPE>::iterator i = q.getSynTable().find(selectedSyn);

			if((!isdigit(token1[0]) && !isdigit(token2[0])) || (selectedSyn!=token1 && selectedSyn!=token2)) { //if first char is a digit, then the token must be a number
				if(evaluateFollowsBoolean(*it, m)){
					answers.push_back( f.getAll(i->second));
				}
				else {
					answers.push_back(evaluateFollows(*it, m, q.getSelectedSyn()));
				}
			}
			break;
									}
		case Relationship::FOLLOWSSTAR:
			answers.push_back(evaluateFollowsStar(*it));
			break;
		case Relationship::PARENT:
			answers.push_back(evaluateParent(*it));
			break;
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
			answers = answers && evaluateParentBoolean(*it);
		case Relationship::PARENTSTAR:
			answers = answers && evaluateParentStarBoolean(*it);
		}
	}
	//WHAT IS THIS RETURN VALUEEE. YOHANES RETURN FALSE AS DEFAULT HERE
	return false;
}

bool evaluateFollowsBoolean(Relationship r, unordered_map<string, STYPE> m){
	string tk1 = r.getToken1();
	string tk2 = r.getToken2();
	Follows f;
	if(isdigit(tk1[0]) && isdigit(tk2[0])){
		return f.isFollows(atoi(tk1.c_str()), atoi(tk2.c_str()));
	}
	else if(isalpha(tk1[0]) && isalpha(tk2[0])){
		unordered_map<string, STYPE>::iterator i1 = m.find(tk1);
		unordered_map<string, STYPE>::iterator i2 = m.find(tk2);
		return f.isFollows(i1->second, i2->second);
	}
	else if(isalpha(tk1[0])){
		unordered_map<string, STYPE>::iterator i1 = m.find(tk1);
		return f.isFollows(i1->second, atoi(tk2.c_str()));
	}
	else {
		unordered_map<string, STYPE>::iterator i1 = m.find(tk2);
		return f.isFollowedBy(i1->second, atoi(tk1.c_str()));
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

vector<int> QueryEvaluator::evaluateFollows(Relationship r, unordered_map<string, STYPE> m, string selectedSyn){
	string tk1 = r.getToken1();
	string tk2 = r.getToken2();
	Follows f;
	vector<int> answer;
	unordered_map<string, STYPE>::iterator i1 = m.find(tk1);
	unordered_map<string, STYPE>::iterator i2 = m.find(tk2);
	unordered_map<string, STYPE>::iterator i3 = m.find(selectedSyn);
	if(isalpha(tk1[0]) && isalpha(tk2[0]) && selectedSyn==tk1){
		return f.getFollows(i3->second, i2->second, i1->second);
	}
	else if(isalpha(tk1[0]) && isalpha(tk2[0]) && selectedSyn==tk2){
		return f.getFollowedBy(i3->second, i2->second, i1->second);
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