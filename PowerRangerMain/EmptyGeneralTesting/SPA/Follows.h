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
typedef void VOID;
typedef bool BOOLEAN;

class Follows {
private: 
	vector<STMTNUM> followsTable;
	vector<STMTNUM> followedByTable;
	TypeTable table;
public: 
	Follows();
	VOID setFollows(STMTNUM, STMTNUM);
	BOOLEAN isFollows(STMTNUM, STMTNUM);
	BOOLEAN isFollows(Query::SType, STMTNUM);
	BOOLEAN isFollowedBy(Query::SType, STMTNUM);
	BOOLEAN	isFollows(Query::SType, Query::SType);
	STMTNUM getFollows(Query::SType, STMTNUM);
	STMTNUM getFollowedBy(Query::SType, STMTNUM);
	vector<STMTNUM> getFollows(Query::SType, Query::SType, Query::SType);
	vector<STMTNUM> getFollowedBy(Query::SType, Query::SType, Query::SType); // argument order: selectedSyn, token 1, token 2
	vector<STMTNUM> getAll(Query::SType); // API that query evaluator needs but should be classified under extra APIs instead which doesnt exist yet
}; 

#endif