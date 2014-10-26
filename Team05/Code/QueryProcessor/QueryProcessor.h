#pragma once
#ifndef QUERYPROCESSOR_H
#define QUERYPROCESSOR_H

#pragma once
#include "QueryParser.h"
#include "QueryEvaluator.h"
#include "PKB.h"

void queryDriver(std::string query, std::list<string>& result, PKB *pkb);
vector<vector<int>> createTupleTable(unordered_map<int, vector<Pair>>, vector<Relationship>, unordered_map<string, int> *);

#endif