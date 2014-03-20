#pragma once

#include "Follows.h"

// constructor
Follows::Follows() {
	// Note: program line 0 is not to be used for the enumeration of program lines
	followsTable.assign(5, -1);
	followedByTable.assign(5, -1);
}

VOID Follows::setFollows(STMTNUM s1, STMTNUM s2) {
	if (s1 >= (signed int) followsTable.size()) {
		followsTable.resize(s1+1, -1);
	}
	followsTable[s1] = s2;

	if (s2 >= (signed int) followedByTable.size()) {
		followedByTable.resize(s2+1, -1);
	}
	followedByTable[s2] = s1; 
}

BOOLEAN Follows::isFollows(STMTNUM s1, STMTNUM s2) {
	//Need to add exception handling
	if (followsTable[s1] == s2) {
		return true;
	}
	return false;
}

STMTNUM Follows::getFollows(STMTNUM s1) {
	return followsTable[s1];
}

STMTNUM Follows::getFollowedBy(STMTNUM s2) {
	return followedByTable[s2];	
}
