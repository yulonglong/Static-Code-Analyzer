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
	std::vector<int> evaluateParentStar(Relationship, std::unordered_map<std::string, TypeTable::SynType>, std::string);
	std::vector<int> evaluateModifies(Relationship, std::unordered_map<std::string, TypeTable::SynType>, std::string);
	std::vector<int> evaluateUses(Relationship, std::unordered_map<std::string, TypeTable::SynType>, std::string);
	std::vector<int> evaluatePattern(std::string, std::string);
	bool evaluateRightHandSide(std::string, Node);
	bool evaluateLeftHandSide(std::string, Node);
	bool evaluateFollowsBoolean(Relationship, std::unordered_map<std::string, TypeTable::SynType>);
	bool evaluateFollowsStarBoolean(Relationship, std::unordered_map<std::string, TypeTable::SynType>);
	bool evaluateParentBoolean(Relationship, std::unordered_map<std::string, TypeTable::SynType>);
	bool evaluateParentStarBoolean(Relationship, std::unordered_map<std::string, TypeTable::SynType>);
	bool evaluateModifiesBoolean(Relationship, std::unordered_map<std::string, TypeTable::SynType>);
	bool evaluateUsesBoolean(Relationship, std::unordered_map<std::string, TypeTable::SynType>);
	std::vector<int> intersectAnswers(std::vector<std::vector<int> >);
	std::string convertEnumToString(TypeTable::SynType);

public:
	QueryEvaluator(PKB*);
	~QueryEvaluator();
	PKB *pkb;
	std::vector<int> evaluateQuery(Query);
	bool evaluateQueryBoolean(Query);
};

#endif