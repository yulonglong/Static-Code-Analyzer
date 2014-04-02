#pragma once
#ifndef QUERYEVALUATOR_H
#define QUERYEVALUATOR_H

#include <iostream>
#include "Relationship.h"
#include "Query.h"
#include "TypeTable.h"
#include "Follows.h"
#include <vector>


class QueryEvaluator{ 
private:
	std::vector<int> evaluateFollows(Relationship, std::unordered_map<std::string, Query::SynType>, std::string);
	std::vector<int> evaluateFollowsStar(Relationship, std::unordered_map<std::string, Query::SynType>, std::string);
	std::vector<int> evaluateParent(Relationship, std::unordered_map<std::string, Query::SynType>, std::string);
	std::vector<int> evaluateParentStar(Relationship);
	bool evaluateFollowsBoolean(Relationship, std::unordered_map<std::string, Query::SynType>);
	bool evaluateFollowsStarBoolean(Relationship);
	bool evaluateParentBoolean(Relationship, std::unordered_map<std::string, Query::SynType>);
	bool evaluateParentStarBoolean(Relationship);
	std::vector<int> intersectAnswers(std::vector<std::vector<int> >);
public:
	QueryEvaluator();
	std::vector<int> evaluateQuery(Query, Follows);
	bool evaluateQueryBoolean(Query);
};
#endif