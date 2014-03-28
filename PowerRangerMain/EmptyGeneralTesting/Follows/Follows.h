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

class Follows {
private: 
	vector<STMTNUM> followsTable;
	vector<STMTNUM> followedByTable;
	
public: 
	TypeTable table; // public for the sake of unit testing
	Follows();
	~Follows();
	void setFollows(STMTNUM, STMTNUM);
	bool isFollows(STMTNUM, STMTNUM); 
	bool isFollows(STYPE, STMTNUM); // redundant!!; getFollows(STYPE, STMTNUM) returns -1 if no result
	bool isFollowedBy(STYPE, STMTNUM); // redundant!!
	bool isFollows(STYPE, STYPE);	
	STMTNUM getFollows(STYPE, STMTNUM);	
	STMTNUM getFollowedBy(STYPE, STMTNUM);
	vector<STMTNUM> getFollows(STYPE, STYPE, STYPE);
	vector<STMTNUM> getFollowedBy(STYPE, STYPE, STYPE); // argument order: selectedSyn, token 1, token 2
	vector<STMTNUM> getAll(STYPE); // API that query evaluator needs but should be classified under extra APIs instead which doesnt exist yet // should not be under follows
}; 

#endif