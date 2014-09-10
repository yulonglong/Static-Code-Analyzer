#pragma once
#ifndef PAIR_H
#define PAIR_H

#include <iostream>
#include "Relationship.h"
#include "Query.h"
#include "PKB.h"
#include "QueryEvaluator.h"
#include <vector>
#include <set>

class Pair {

public:
	std::string ans1;
	std::string ans2;
	string token1;
	string token2;

	Pair(std::string, std::string, std::string, std::string);
	Pair();
	~Pair();

};

#endif