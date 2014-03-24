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

BOOLEAN Follows::isFollows(SType t, STMTNUM s) {
	STMTNUM temp = followsTable[s];
	//Need to add exception handling
	if (table.getType(temp).compare(t)==0) {
		return true;
	}
	return false;
}

BOOLEAN Follows::isFollowedBy(SType t, STMTNUM s) {
	STMTNUM temp = followedByTable[s];
	//Need to add exception handling
	if (table.getType(temp).compare(t)==0) {
		return true;
	}
	return false;
}

BOOLEAN Follows::isFollows(SType t1, SType t2) {
	vector<STMTNUM>::iterator it = followsTable.begin();
	for(;it!= followsTable.end();++it){
		for(vector<STMTNUM>::iterator it2 = it;it2!=followsTable.end();++it2){
			if(table.getType(*it).compare(table.getType(*it2)) == 0)
				return true;
		}
	}	
	return false;
}

STMTNUM Follows::getFollows(SType t, STMTNUM s) {
	if(table.getType(followsTable[s]).compare(t) == 0){
		return followsTable[s];
	}
	return -1;
}

STMTNUM Follows::getFollowedBy(SType t, STMTNUM s) {
	TypeTable table;
	if(table.getType(followedByTable[s]).compare(t) == 0){
		return followedByTable[s];
	}
	return -1;
}

vector<STMTNUM> Follows::getFollows(SType t1, SType t2,SType t3) {
	vector<STMTNUM> v (1,-1);
	vector<STMTNUM>::iterator it = followsTable.begin();
	for(;it!= followsTable.end();++it){
		for(vector<STMTNUM>::iterator it2 = it;it2!=followsTable.end();++it2){
			if(table.getType(*it).compare(t2) == 0){
				if(table.getType(*it2).compare(t3) == 0){
					v = table.getStmtNum(t1);
					return v;
				}
			}		
		}
	}
	return v;
}

vector<STMTNUM> Follows::getFollowedBy(SType t1, SType t2,SType t3) {
	vector<STMTNUM> v (1,-1);
	vector<STMTNUM>::iterator it = followsTable.begin();
	for(;it!= followedByTable.end();++it){
		for(vector<STMTNUM>::iterator it2 = it;it2!=followedByTable.end();++it2){
			if(table.getType(*it).compare(t2) == 0){
				if(table.getType(*it2).compare(t3) == 0){
					v = table.getStmtNum(t1);
					return v;
				}
			}		
		}
	}
	return v;
}

vector<STMTNUM> getAll(SType t){
	vector<STMTNUM> v (1,-1);
	return v;
}