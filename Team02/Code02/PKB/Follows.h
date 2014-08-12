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
typedef TypeTable::SynType TYPE; 

class Follows {
private: 
	vector<STMTNUM> followsTable;
	vector<STMTNUM> followedByTable;
	static bool instanceFlag;
	static Follows *follows;
	TypeTable *typeTable; // public for the sake of unit testing
	
public: 
	Follows(TypeTable*);
	Follows();
	~Follows();
	static Follows* getInstance();
	static Follows* getInstance(TypeTable*);	
	
	void setFollows(STMTNUM, STMTNUM);

	// testIsFollowsUsingStmtNum
	bool isFollows(STMTNUM, STMTNUM);	

	// testFollowsUsingStmtType
	bool isFollows(TYPE, STMTNUM);	
	bool isFollowedBy(TYPE, STMTNUM);	
	bool isFollows(TYPE, TYPE);

	// testGetFollowsUsingStmtType
	STMTNUM getFollows(TYPE, STMTNUM);	
	STMTNUM getFollowedBy(TYPE, STMTNUM); 
	vector<STMTNUM> getFollows(TYPE, TYPE);	 //Select s1 such that getFollows(s1, s2)
	vector<STMTNUM> getFollowedBy(TYPE, TYPE);	 //Select s2 such that getFollows(s1, s2)
}; 

#endif