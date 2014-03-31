#pragma once

#include "Follows.h"

// constructor
Follows::Follows() {
	// Note: program line 0 is not to be used for the enumeration of program lines
	followsTable.assign(5, -1);
	followedByTable.assign(5, -1);
}

Follows::~Follows() {
	vector<STMTNUM>().swap(followsTable);
	vector<STMTNUM>().swap(followedByTable);
}

void Follows::setFollows(STMTNUM s1, STMTNUM s2) {
	if (s1 >= (signed int) followsTable.size()) {
		followsTable.resize(s1+1, -1);
	}
	followsTable[s1] = s2;

	if (s2 >= (signed int) followedByTable.size()) {
		followedByTable.resize(s2+1, -1);
	}
	followedByTable[s2] = s1; 
}

bool Follows::isFollows(STMTNUM s1, STMTNUM s2) {
	if (followsTable[s1] == s2) {
		return true;
	}
	return false;
}

/*bool Follows::isFollows(STYPE t, STMTNUM s) {
	STMTNUM result = getFollows(t, s);
	bool noResult = (result == -1);
	if (noResult) {
		return false;
	} 
	return true;
}

bool Follows::isFollowedBy(STYPE t, STMTNUM s) {
	STMTNUM result = getFollowedBy(t, s);
	bool noResult = (result == -1);
	if (noResult) {
		return false;
	} 
	return true;
}*/

bool Follows::isFollows(STYPE t1, STYPE t2) {
	vector<STMTNUM>::iterator it = followsTable.begin();
	for(;it!= followsTable.end();++it){
		for(vector<STMTNUM>::iterator it2 = it;it2!=followsTable.end();++it2){
			if(table.getType(*it)== (table.getType(*it2)))
				return true;
		}
	}	
	return false;
}

// TODO: add exception handling
STMTNUM Follows::getFollows(STYPE t, STMTNUM s) {
	if(table.getType(followsTable[s]) == t){
		return followsTable[s];
	}
	return -1;
}

// TODO: add exception handling
STMTNUM Follows::getFollowedBy(STYPE t, STMTNUM s) {
	if(table.getType(followedByTable[s]) == t){
		return followedByTable[s];
	}
	return -1;
}

// TODO: add exception handling
vector<STMTNUM> Follows::getFollows(STYPE t1, STYPE t2,STYPE t3) {
	vector<STMTNUM> v (1,-1);
	vector<STMTNUM>::iterator it = followsTable.begin();
	for(;it!= followsTable.end();++it){
		for(vector<STMTNUM>::iterator it2 = it;it2!=followsTable.end();++it2){
			if(table.getType(*it) == t2){
				if(table.getType(*it2) == t3){
					v = table.getStmtNum(t1);
					return v;
				}
			}		
		}
	}
	return v;
}

// TODO: add exception handling
vector<STMTNUM> Follows::getFollowedBy(STYPE t1, STYPE t2,STYPE t3) {
	vector<STMTNUM> v (1,-1);
	vector<STMTNUM>::iterator it = followsTable.begin();
	for(;it!= followedByTable.end();++it){
		for(vector<STMTNUM>::iterator it2 = it;it2!=followedByTable.end();++it2){
			if(table.getType(*it) == t2){
				if(table.getType(*it2) == t3){
					v = table.getStmtNum(t1);
					return v;
				}
			}		
		}
	}
	return v;
}
