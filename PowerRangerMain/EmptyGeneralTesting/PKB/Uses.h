#ifndef USES_H
#define USES_H

#pragma once
#include <iostream>
#include "TypeTable.h"

using namespace std;

class Uses {
public:
	Uses();
	bool isUses(STMTNUM, string);	//Select w such that Uses(1, "y")
	bool isUses(TypeTable::SynType, TypeTable::SynType);	//Select s such that Uses(a, v) parameter order: selected type, first token, second token
	vector<int> getUses(TypeTable::SynType, string);	//Select a such that Uses(a, "x")	return -1 if doesn't exist
	vector<string> getModified(TypeTable::SynType);		//Select v such that Uses(1, v)	return empty vector if doesnt exist
};

#endif