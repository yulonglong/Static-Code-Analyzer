#pragma once
#ifndef QUERYEVALUATOR_H
#define QUERYEVALUATOR_H

#include <iostream>
#include "Relationship.h"
#include "Query.h"
#include <vector>


class QueryEvaluator{ 
private:
	std::vector<int> evaluateFollows(Relationship);
	std::vector<int> evaluateFollowsStar(Relationship);
	std::vector<int> evaluateParent(Relationship);
	std::vector<int> evaluateParentStar(Relationship);
	std::bool evaluateFollowsBoolean(Relationship);
	std::bool evaluateFollowsStarBoolean(Relationship);
	std::bool evaluateParentBoolean(Relationship);
	std::bool evaluateParentStarBoolean(Relationship);
	std::vector<int> intersectAnswers(std::vector<std::vector<int> >);
public:
	QueryEvaluator();
	std::vector<int> evaluateQuery(Query);
	std::bool evaluateQueryBoolean(Query);
};
#endif