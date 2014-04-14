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
	
	static bool instanceFlag;
	static Follows *follows;
	
public: 
	TypeTable *typeTable; // public for the sake of unit testing
	Follows(TypeTable*);
	Follows();
	~Follows();
	static Follows* getInstance();	// to be used to get instance of singleton class
	static Follows* getInstance(TypeTable*);	// to be used to get instance of singleton class

	vector<STMTNUM> followedByTable;

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