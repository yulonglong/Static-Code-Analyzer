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
public: 
	VOID Follows::setFollows(STMTNUM s1, STMTNUM s2);
	BOOLEAN Follows::isFollows(STMTNUM s1, STMTNUM s2);
	STMTNUM Follows::getFollows(STMTNUM);
	STMTNUM Follows::getFollowedBy(STMTNUM);

private: 
	vector<STMTNUM> followsTable;
	vector<STMTNUM> followedByTable;
}; 