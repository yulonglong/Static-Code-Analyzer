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

	// testIsFollowsUsingStmtNum
	bool isFollows(STMTNUM, STMTNUM);	

	// testFollowsUsingStmtType
	bool isFollows(Query::SynType, STMTNUM);	// done testing!!
	bool isFollowedBy(Query::SynType, STMTNUM);	 // done testing!!
	bool isFollows(Query::SynType, Query::SynType);	// done testing!!

	// testGetFollowsUsingStmtType
	STMTNUM getFollows(Query::SynType, STMTNUM);	// done testing!!
	STMTNUM getFollowedBy(Query::SynType, STMTNUM); // done testing!!
	vector<STMTNUM> getFollows(Query::SynType, Query::SynType);	 //Select s1 such that getFollows(s1, s2)
	vector<STMTNUM> getFollowedBy(Query::SynType, Query::SynType);	 //Select s2 such that getFollows(s1, s2)
}; 

#endif