#ifndef FOLLOWS_H
#define FOLLOWS_H

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include "Query.h"

using namespace std;
typedef int STMTNUM;
typedef void VOID;
typedef bool BOOLEAN;

class Follows {
private: 
	vector<STMTNUM> followsTable;
	vector<STMTNUM> followedByTable;
public: 
	Follows();
	VOID setFollows(STMTNUM, STMTNUM);
	BOOLEAN isFollows(STMTNUM, STMTNUM);
	BOOLEAN isFollows(SType, STMTNUM);
	BOOLEAN isFollowedBy(SType, STMTNUM);
	BOOLEAN	isFollows(SType, SType);
	STMTNUM getFollows(SType, SType, STMTNUM);
	STMTNUM getFollowedBy(SType, SType, STMTNUM);
	STMTNUM getFollows(SType, SType, SType)
}; 

#endif