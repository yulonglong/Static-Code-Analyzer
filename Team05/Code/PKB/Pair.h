#pragma once
#ifndef PAIR_H
#define PAIR_H

#include <iostream>
#include "PKB.h"
#include <vector>
#include <set>

class Pair {

public:
	int ans1;
	int ans2;

	Pair(int, int);
	Pair();

	bool operator <(const Pair &p) const;
	bool operator >(const Pair &p) const;
};

/*
bool operator==(Pair, Pair);	
*/
#endif