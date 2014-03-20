#pragma once

#include "Parent.h"

vector<vector<STMTNUM>> parentTable;
vector<STMTNUM> chidlrenTable;


// constructor
Parent::Parent() {
	// program line 0 is not to be used for the enumeration
	// parentTable.emplace_back();
	vector<STMTNUM> temp;
	temp.assign(1,-1);
	parentTable.assign(5, temp);
	chidlrenTable.assign(5, -1);
}

VOID Parent::setParent(STMTNUM s1, STMTNUM s2) {
	vector<STMTNUM> temp;
	temp.assign(1,-1);
	if (s1 >= (signed int) parentTable.size()) {
		parentTable.resize(s1+1, temp);
	}

	vector<STMTNUM> temp1 = parentTable[s1];
	temp1.push_back(s2);
	parentTable[s1] = temp1;

	if (s2 >= (signed int)chidlrenTable.size()) {
		chidlrenTable.resize(s2+1, -1);
	}
	childrenTable[s2] = s1; 
}

BOOLEAN Parent::isParent(STMTNUM s1, STMTNUM s2) {
	//Need to add exception handling
	if (childrenTable[s2] == s1) {
		return true;
	}
	return false;
}

STMTNUM Parent::getParent(STMTNUM s1) {
	//Need to add exception handling
	return childrenTable[s1];
}

LIST Parent::getChildren(STMTNUM s1) {
	//Need to add exception handling
	return parentTable[s1];
}
