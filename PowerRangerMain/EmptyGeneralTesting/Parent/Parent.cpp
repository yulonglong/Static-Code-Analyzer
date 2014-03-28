#pragma once

#include "Parent.h"

// constructor
Parent::Parent() {
	// program line 0 is not to be used for the enumeration
	// parentTable.emplace_back();
	vector<STMTNUM> temp;
	temp.assign(1,-1);
	parentTable.assign(5, temp);
	childrenTable.assign(5, -1);
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

	if (s2 >= (signed int)childrenTable.size()) {
		childrenTable.resize(s2+1, -1);
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

BOOLEAN Parent::isParent(SType t, STMTNUM s) {
	STMTNUM temp = childrenTable[s];
	//Need to add exception handling
	if (table.getType(temp).compare(t)==0) {
		return true;
	}
	return false;
}

BOOLEAN Parent::isChildren(SType t, STMTNUM s ){
	LIST temp = parentTable[s];
	LIST::iterator it = temp.begin();
	for(;it!=temp.end();++it){
		if(table.getType(*it)==t)
			return true;
	}
	return false;
}

vector<STMTNUM> Parent::getParent(SType t1, SType t2, STMTNUM s) {
	STMTNUM temp = childrenTable[s];
	if(table.getType(temp).compare(t2)==0){
		return table.getStmtNum(t1);
	}
	return vector<STMTNUM> (1,-1);
}

vector<STMTNUM> Parent::getChildren(SType t1, SType t2, STMTNUM s) {
	vector<STMTNUM> temp = parentTable[s];
	vector<STMTNUM>::iterator it = temp.begin();
	for(;it!=temp.end();++it){
		if(table.getType(*it).compare(t2)==0){
			return table.getStmtNum(t1);
		}
	}
	return vector<STMTNUM> (1,-1);
}