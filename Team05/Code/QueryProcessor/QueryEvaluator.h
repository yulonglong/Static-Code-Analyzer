#pragma once
#ifndef QUERYEVALUATOR_H
#define QUERYEVALUATOR_H

#include <iostream>
#include "Relationship.h"
#include "Query.h"
#include "PKB.h"
#include "Pair.h"
#include <vector>
#include <set>


class QueryEvaluator{ 
private:
	static unordered_map<string, std::vector<int>> linkages;
	static unordered_map<int, std::vector<Pair>> relAns;
	static std::vector<Relationship> vecOfRelations;

	void evaluateFollows(Relationship, std::unordered_map<std::string, TypeTable::SynType>, int relIndex);
	void evaluateFollowsStar(Relationship, std::unordered_map<std::string, TypeTable::SynType>, int relIndex);
	std::vector<int> evaluateParent(Relationship, std::unordered_map<std::string, TypeTable::SynType>, std::string);
	std::vector<int> evaluateParentStar(Relationship, std::unordered_map<std::string, TypeTable::SynType>, std::string);
	std::vector<int> evaluateModifies(Relationship, std::unordered_map<std::string, TypeTable::SynType>, std::string);
	std::vector<int> evaluateUses(Relationship, std::unordered_map<std::string, TypeTable::SynType>, std::string);
	std::vector<int> evaluateCalls(Relationship, std::string);
	std::vector<int> evaluateCallsStar(Relationship);
	std::vector<int> evaluatePattern(Query, std::string, std::string);
	std::vector<Relationship> orderRelationship(vector<Relationship>);
	std::vector<int> * findAnswerVectorFromToken(std::string);
	std::vector<std::string> findLinks(std::string);

	std::set<int> retrieveTokenEvaluatedAnswers(std::string );
	void removePairs(std::vector<Pair>, std::string);
	void removePairsFromRelAns(std::vector<Pair> *,std::string, int);
	void insertLinks(std::string, int);

	bool evaluateCallsBoolean(Relationship);
	bool evaluateCallsStarBoolean(Relationship);
	bool evaluateRightHandSide(std::string, Node);
	bool evaluateLeftHandSide(std::string, Node);
	bool evaluateFollowsBoolean(Relationship, std::unordered_map<std::string, TypeTable::SynType>);
	//bool evaluateFollowsStarBoolean(Relationship, std::unordered_map<std::string, TypeTable::SynType>);
	bool evaluateParentBoolean(Relationship, std::unordered_map<std::string, TypeTable::SynType>);
	bool evaluateParentStarBoolean(Relationship, std::unordered_map<std::string, TypeTable::SynType>);
	bool evaluateModifiesBoolean(Relationship, std::unordered_map<std::string, TypeTable::SynType>);
	bool evaluateUsesBoolean(Relationship, std::unordered_map<std::string, TypeTable::SynType>);
	bool isExistInLinkages(std::string);
	bool isLinked(std::string, std::string);
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