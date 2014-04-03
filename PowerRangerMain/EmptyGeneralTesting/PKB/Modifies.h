#ifndef MODIFIES_H
#define MODIFIES_H

#pragma once
#include <iostream>
#include "TypeTable.h"

using namespace std;
typedef int STMTNUM;

class Modifies {
public:
	Modifies();
	bool isModifies(STMTNUM, string);	//Select w such that Modifies(1, "y")
	bool isModifies(TypeTable::SynType, TypeTable::SynType, TypeTable::SynType);	//Select s such that Modifies(a, v) parameter order: selected type, first token, second token
	vector<int> getModifies(TypeTable::SynType, string);	//Select a such that Modifies(a, "x")	return -1 if doesn't exist
	vector<string> getModified(TypeTable::SynType);		//Select v such that Modifies(1, v)	return -1 if doesnt exist
};

#endif