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
	bool isFollows(Query::SynType, Query::SynType);	
	STMTNUM getFollows(Query::SynType, STMTNUM);	
	STMTNUM getFollowedBy(Query::SynType, STMTNUM);
	vector<STMTNUM> getFollows(Query::SynType, Query::SynType, Query::SynType); //Select s1 such that Follows(s1,s2)
	vector<STMTNUM> getFollowedBy(Query::SynType, Query::SynType, Query::SynType); // argument order: selectedSyn, token 1, token 2
	vector<STMTNUM> getAll(Query::SynType); // API that query evaluator needs but should be classified under extra APIs instead which doesnt exist yet // should not be under follows
}; 

#endif