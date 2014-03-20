#ifndef QUERYEVALUATOR_H
#define QUERYEVALUATOR_H

#include <iostream>
#include "Relationship.h"
#include "Query.h"
#include <vector> 

class QueryEvaluator
{
private:jflsdkajflakjs
	std::vector<int> evaluateFollows(Relationship);
	std::vector<int> evaluateFollowsStar(Relationship);
	std::vector<int> evaluateParent(Relationship);
	std::vector<int> evaluateParentStar(Relationship);
public:
	QueryEvaluator();
	std::vector<int> evaluateQuery(Query);
};

#endif