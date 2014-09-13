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
	int ans1;
	int ans2;
	string token1;
	string token2;

	Pair(int, int, std::string, std::string);
	Pair();

	bool operator <(const Pair &p) const;
	bool operator >(const Pair &p) const;
};

/*
bool operator==(Pair, Pair);	
*/
#endif