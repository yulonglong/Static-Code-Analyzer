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

/*! \brief Query Evaluator class 
 *  
 * Overview: Query Evaluator is responsible for :
 * - Accepting Query object made by the Query Parser 
 * - And evaluate the set of answers resquested by the user
 * 
 * To evaluate query, call
 * \code
 * void unordered_map<string, vector<Pair>> evaluateQuery(Query);
 * \endcode
 *
 */

class QueryEvaluator{ 
private:
		//! Evaluate all Calls Relationships
	void evaluateCalls(Relationship, int);

	//! Evaluate all Calls* Relationships
	void evaluateCallsStar(Relationship,int);

	//! Evaluate all Uses Relationships
	void evaluateUses(Relationship, std::unordered_map<std::string, TypeTable::SynType>, int);

	//! Evaluate all Follows Relationships
	void evaluateFollows(Relationship, std::unordered_map<std::string, TypeTable::SynType>, int);

	//! Evaluate all Parent Relationships
	void evaluateParent(Relationship, std::unordered_map<std::string, TypeTable::SynType>, int);

	//! Evaluate all Modifies Relationships
	void evaluateModifies(Relationship, std::unordered_map<std::string, TypeTable::SynType>, int);

	//! Evaluate all Next* Relationships
	void evaluateNextStar(Relationship, std::unordered_map<string, TypeTable::SynType>, int);

	//! A Recursive Method used in Next* to aid in finding the respective answers
	void recursiveNext(int, int, std::set<Pair> *, TypeTable::SynType);

	void recursiveNextReverse(int, int, std::set<Pair> *, TypeTable::SynType);
	void recursiveNextTarget(int, int, int, std::set<Pair> *);

	//! Evaluate Follows* Relationships
	void evaluateFollowsStar(Relationship, std::unordered_map<std::string, TypeTable::SynType>, int);
	
	void evaluateParentStar(Relationship, std::unordered_map<std::string, TypeTable::SynType>, int);
	

	void evaluateWith(Relationship, std::unordered_map<string, TypeTable::SynType>, int);

	void evaluateNext(Relationship, std::unordered_map<string, TypeTable::SynType>, int);
	void recursiveCall(int, int, std::vector<Pair> *);
	void recursiveInverseCall(int, int, std::vector<Pair> *);
	void recursiveCallBoolean(int, int, int, std::vector<Pair> *);

	void intersectPairs(std::string, std::string, std::vector<Pair> *, int);

	//std::vector<int> evaluateCallsStar(Relationship);
	std::vector<int> evaluatePattern(Query, std::string, std::string);
	std::vector<Relationship> orderRelationship(vector<Relationship>);
	std::vector<int> * findAnswerVectorFromToken(std::string);
	//std::vector<std::string> findLinks(std::string);

	std::set<int> retrieveTokenEvaluatedAnswers(std::string );
	void removePairs(std::vector<Pair>, std::string, int);
	void removePairsFromRelAns(std::vector<Pair> *,std::string, int);
	void insertLinks(std::string, int);

	bool evaluateRightHandSide(std::string, Node);
	bool evaluateLeftHandSide(std::string, Node);
	bool isExistInLinkages(std::string);

	std::string convertEnumToString(TypeTable::SynType);
	static std::unordered_map<string, std::vector<int>> linkages;
	static std::unordered_map<int, std::vector<Pair>> relAns;
	static std::unordered_map<int, vector<std::string>> relParameters;
	PKB *pkb;

public:
	//! Constructor for QueryEvaluator. Takes in the singleton PKB as input parameter
	QueryEvaluator(PKB*);
	~QueryEvaluator();
	

	//! To evaluate Queries, the Query Processor will call evaluateQuery and pass in the Query object returned by the Query Parser. This method will then return an unordered_map that has every selected syn and their corresponding vector of answers
	std::unordered_map<std::string, std::vector<int>> evaluateQuery(Query);


};

#endif