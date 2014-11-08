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
	//! Evaluate all Follows Relationships
	void evaluateFollows(Relationship, std::unordered_map<std::string, TypeTable::SynType>, int);

	//! Evaluate all Follows* Relationships
	void evaluateFollowsStar(Relationship, std::unordered_map<std::string, TypeTable::SynType>, int);

	//! Evaluate all Parent Relationships
	void evaluateParent(Relationship, std::unordered_map<std::string, TypeTable::SynType>, int);

	//! Evaluate all Parent* Relationships
	void evaluateParentStar(Relationship, std::unordered_map<std::string, TypeTable::SynType>, int);

	//! Evaluate all Uses Relationships
	void evaluateUses(Relationship, std::unordered_map<std::string, TypeTable::SynType>, int);

	//! Evaluate all Modifies Relationships
	void evaluateModifies(Relationship, std::unordered_map<std::string, TypeTable::SynType>, int);

	//! Evaluate all Calls Relationships
	void evaluateCalls(Relationship, int);

	//! Evaluate all Calls* Relationships
	void evaluateCallsStar(Relationship,int);
	//! A Recursive Method used in Call* to aid in finding the respective answers
	void recursiveCall(int, int, std::set<Pair> *, std::vector<int>*);
	void recursiveInverseCall(int, int, std::set<Pair> *, std::vector<int>*);
	void recursiveCallBoolean(int, int, int, std::set<Pair> *, std::vector<int>*);

	//! Evaluate all Next Relationships
	void evaluateNext(Relationship, std::unordered_map<string, TypeTable::SynType>, int);

	//! Evaluate all Next* Relationships
	void evaluateNextStar(Relationship, std::unordered_map<string, TypeTable::SynType>, int);
	//! A Recursive Method used in Next* to aid in finding the respective answers
	void recursiveNext(int, int, std::set<Pair> *, TypeTable::SynType, std::vector<int>*);
	void recursiveNextReverse(int, int, std::set<Pair> *, TypeTable::SynType, std::vector<int>*);
	void recursiveNextTarget(int, int, int, std::set<Pair> *, std::vector<int>*);

	//! Evaluate all Affects Relationships
	void evaluateAffects(Relationship, std::unordered_map<std::string, TypeTable::SynType>, int);
	bool findPath(int, int, set<int>);
	bool isAffects(int, int);

	//! Evaluate all Affects* Relationships
	void evaluateAffectsStar(Relationship, std::unordered_map<std::string, TypeTable::SynType>, int);	
	bool isAffectsStar(int, int, unordered_map<Pair, bool> *, vector<int>);

	//! Evaluate all With Relationships
	void evaluateWith(Relationship, std::unordered_map<string, TypeTable::SynType>, int);

	//! Evaluate Pattern Relationships
	void evaluatePattern(Relationship, std::unordered_map<string, TypeTable::SynType>, int);
	//! Helper functions used to evaluate Pattern Relationships
	std::vector<Pair> findAssign(Node, string, string, Relationship);
	std::vector<Pair> findIf(Node, string, string, Relationship);
	std::vector<Pair> findWhile(Node, string, string, Relationship);
	bool matchPattern(Node, string, string, bool);
	bool matchTree(Node, Node);
	static Node* constructExpressionTree(vector<string> tokens);
	static vector<string> getPostfix(vector<string> tokens);
	static void tokenizeTokens(string word, vector<string> &storage);
	static bool isAllDigit(string input);

	//! Final answer intersection function
	void intersectPairs(std::string, std::string, std::vector<Pair> *, int);

	//! General helper functions
	std::vector<Relationship> orderRelationship(vector<Relationship>);
	std::vector<int> * findAnswerVectorFromToken(std::string);
	//std::vector<std::string> findLinks(std::string);
	std::set<int> retrieveTokenEvaluatedAnswers(std::string );
	void removePairs(std::vector<Pair>, std::string, int);
	void removePairsFromRelAns(std::vector<Pair> *,std::string, int);
	void insertLinks(std::string, int);
	bool isExistInLinkages(std::string);


	static std::unordered_map<string, std::vector<int>> linkages;
	static std::unordered_map<int, std::vector<Pair>> relAns;
	static std::unordered_map<int, vector<std::string>> relParameters;
	static std::unordered_map<int,std::set<int>> nextStarTable;
	PKB *pkb;

public:
	//! Constructor for QueryEvaluator. Takes in the singleton PKB as input parameter
	QueryEvaluator(PKB*);
	~QueryEvaluator();	

	//! To evaluate Queries, the Query Processor will call evaluateQuery and pass in the Query object returned by the Query Parser. This method will then return an unordered_map that has every selected syn and their corresponding vector of answers
	std::unordered_map<int, std::vector<Pair>> evaluateQuery(Query, vector<Relationship> *newRelations);
		std::string convertEnumToString(TypeTable::SynType);
};

#endif

