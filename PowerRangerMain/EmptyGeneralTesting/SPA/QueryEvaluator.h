#pragma once
#ifndef QUERYEVALUATOR_H
#define QUERYEVALUATOR_H

#include <iostream>
#include "Relationship.h"
#include "Query.h"
#include "TypeTable.h"
#include <vector>


class QueryEvaluator{ 
private:
	std::vector<int> evaluateFollows(Relationship, std::unordered_map<std::string, STYPE>, std::string);
	std::vector<int> evaluateFollowsStar(Relationship);
	std::vector<int> evaluateParent(Relationship);
	std::vector<int> evaluateParentStar(Relationship);
	bool evaluateFollowsBoolean(Relationship, std::unordered_map<std::string, STYPE>);
	bool evaluateFollowsStarBoolean(Relationship);
	bool evaluateParentBoolean(Relationship);
	bool evaluateParentStarBoolean(Relationship);
	std::vector<int> intersectAnswers(std::vector<std::vector<int> >);
public:
	QueryEvaluator();
	std::vector<int> evaluateQuery(Query);
	bool evaluateQueryBoolean(Query);
};
#endif