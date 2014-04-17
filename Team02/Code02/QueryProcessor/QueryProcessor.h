#pragma once
#ifndef QUERYPROCESSOR_H
#define QUERYPROCESSOR_H

#pragma once
#include "QueryParser.h"
#include "QueryEvaluator.h"
#include "PKB.h"

void queryDriver(std::string query, std::list<string>& result, PKB *pkb);

#endif