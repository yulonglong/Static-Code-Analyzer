#pragma once
#ifndef QUERYPROCESSOR_H
#define QUERYPROCESSOR_H

#pragma once
#include "QueryParser.h"
#include "QueryEvaluator.h"
#include "PKB.h"

#include "../AutoTester/source/AbstractWrapper.h"

/*! \brief QueryProcessor is the brain of Static-Code Analyser
 *  
 *
 * QueryProcessor is the main controller in the PQL.
 * It will call relevant methods and sub-methods from:
 * - QueryParser
 * - QueryEvaluator
 *
 * It has to control and handle all the forwarded data (Query, Relationship) and pass them to the correct module/sub-module.
 *
 * \see QueryParser, QueryEvaluator, Relationship, Query
 */

//! Static method queryDriver drives all the program flow
void queryDriver(std::string query, std::list<string>& result, PKB *pkb);
vector<vector<int>> createTupleTable(unordered_map<int, vector<Pair>>, vector<Relationship>, unordered_map<string, int> *);

#endif