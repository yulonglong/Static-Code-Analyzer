#pragma once
#ifndef QUERYEVALUATOR_H
#define QUERYEVALUATOR_H

#include <iostream>
#include "Relationship.h"
#include "Query.h"
#include "PKB.h"
#include <vector>
#include <set>


class QueryEvaluator{ 
private:

	std::vector<int> evaluateFollows(Relationship, std::unordered_map<std::string, TypeTable::SynType>, std::string);
	std::vector<int> evaluateFollowsStar(Relationship, std::unordered_map<std::string, TypeTable::SynType>, std::string);
	std::vector<int> evaluateParent(Relationship, std::unordered_map<std::string, TypeTable::SynType>, std::string);
	std::vector<int> evaluateParentStar(Relationship);
	bool evaluateFollowsBoolean(Relationship, std::unordered_map<std::string, TypeTable::SynType>);
	bool evaluateFollowsStarBoolean(Relationship, std::unordered_map<std::string, TypeTable::SynType>);
	bool evaluateParentBoolean(Relationship, std::unordered_map<std::string, TypeTable::SynType>);
	bool evaluateParentStarBoolean(Relationship);
	std::vector<int> intersectAnswers(std::vector<std::vector<int> >);
	//std::set<int> evaluateFollowsStarWithOneStmtnum(TypeTable::SynType, int);
	//std::set<int> evaluateFollowedByStarWithOneStmtnum(TypeTable::SynType, int);

public:
	QueryEvaluator();
	PKB *pkb;
	std::vector<int> evaluateQuery(Query);
	bool evaluateQueryBoolean(Query);
};

#endif