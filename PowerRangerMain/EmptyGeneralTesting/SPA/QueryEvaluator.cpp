#include <iostream>
#include <string>
#include "QueryEvaluator.h"

using namespace std;

vector<int> QueryEvaluator::evaluateQuery(Query q){
	vector<Relationship> relations = q.getRelVect();
	vector<vector<int>> answers;
	for(vector<Relationship>::iterator it = relations.begin(); it!=relations.end(); it++){
		switch(it->getRelType()){
		case Relationship::FOLLOWS:
			answers.push_back(evaluateFollows(*it));
			break;
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

vector<int> QueryEvaluator::evaluateFollows(Relationship r){
	
}