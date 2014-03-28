#ifndef FOLLOWS_H
#define FOLLOWS_H

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include "Query.h"
#include "TypeTable.h"

using namespace std;
typedef int STMTNUM;
// typedef void VOID;
// typedef bool BOOLEAN;

class Follows {
private: 
	vector<STMTNUM> followsTable;
	vector<STMTNUM> followedByTable;
	TypeTable table;
public: 
	Follows();
	void setFollows(STMTNUM, STMTNUM);
	BOOLEAN isFollows(STMTNUM, STMTNUM);
	BOOLEAN isFollows(SType, STMTNUM);
	BOOLEAN isFollowedBy(SType, STMTNUM);
	BOOLEAN	isFollows(SType, SType);
	STMTNUM getFollows(SType, STMTNUM);
	STMTNUM getFollowedBy(SType, STMTNUM);
	vector<STMTNUM> getFollows(SType, SType, SType);
	vector<STMTNUM> getFollowedBy(SType, SType, SType); // argument order: selectedSyn, token 1, token 2
	vector<STMTNUM> getAll(SType); // API that query evaluator needs but should be classified under extra APIs instead which doesnt exist yet
}; 

#endif