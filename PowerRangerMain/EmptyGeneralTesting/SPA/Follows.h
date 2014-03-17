#ifndef FOLLOWS_H
#define FOLLOWS_H

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>

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
	VOID setFollows(STMTNUM s1, STMTNUM s2);
	BOOLEAN isFollows(STMTNUM s1, STMTNUM s2);
	STMTNUM getFollows(STMTNUM);
	STMTNUM getFollowedBy(STMTNUM);
}; 

#endif