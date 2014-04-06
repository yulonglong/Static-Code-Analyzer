#ifndef FOLLOWS_H
#define FOLLOWS_H

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include "TypeTable.h"

using namespace std;
typedef int STMTNUM;

class Follows {
private: 
	vector<STMTNUM> followsTable;
	vector<STMTNUM> followedByTable;
	
public: 
	TypeTable table; // public for the sake of unit testing
	Follows(TypeTable);
	Follows();
	~Follows();

	void setFollows(STMTNUM, STMTNUM);

	// testIsFollowsUsingStmtNum
	bool isFollows(STMTNUM, STMTNUM);	

	// testFollowsUsingStmtType
	bool isFollows(TypeTable::SynType, STMTNUM);	// done testing!!
	bool isFollowedBy(TypeTable::SynType, STMTNUM);	 // done testing!!
	bool isFollows(TypeTable::SynType, TypeTable::SynType);	// done testing!!

	// testGetFollowsUsingStmtType
	STMTNUM getFollows(TypeTable::SynType, STMTNUM);	// done testing!!
	STMTNUM getFollowedBy(TypeTable::SynType, STMTNUM); // done testing!!
	vector<STMTNUM> getFollows(TypeTable::SynType, TypeTable::SynType);	 //Select s1 such that getFollows(s1, s2)
	vector<STMTNUM> getFollowedBy(TypeTable::SynType, TypeTable::SynType);	 //Select s2 such that getFollows(s1, s2)

	void updateTable(TypeTable);
}; 

#endif