#pragma once

#include "Follows.h"
#include <stdexcept>      // std::out_of_range
#include <iostream>

bool Follows::instanceFlag=false;
Follows* Follows::follows=NULL;

// constructor
Follows::Follows() {
	vector<STMTNUM> temp (1,-1);
	followsTable = temp;
	followedByTable=temp;
}

Follows::~Follows() {
	followsTable.clear();
	followedByTable.clear();
	instanceFlag=false;
}

Follows* Follows::getInstance() {
	if (!instanceFlag) {
        follows = new Follows();
        instanceFlag = true;
        return follows;
    } else {
        return follows;
    }
}

void Follows::setFollows(STMTNUM s1, STMTNUM s2) {
	if(s1>=followsTable.size())
		followsTable.resize(s1+1,-1);
	followsTable[s1] = s2;

	if(s2>=followedByTable.size())
		followedByTable.resize(s2+1,-1);
	followedByTable[s2] = s1;

	followsList.insert(s1);
	followedByList.insert(s2);
}

bool Follows::isFollows(STMTNUM s1, STMTNUM s2) {
	try {
		STMTNUM num = followsTable.at(s1);
		if(num==s2)
			return true; 
	}
	catch (...) {
		return false;
	}
	return false; 
}

STMTNUM Follows::getFollows(STMTNUM s){
	try{
		return followsTable.at(s);
	} catch (...){
		return -1;
	}
}

STMTNUM Follows::getFollowedBy(STMTNUM s){
	try{
		return followedByTable.at(s);
	} catch (...){
		return -1;
	}
}

set<STMTNUM> Follows::getAllFollows(){
	return followsList;
}

set<STMTNUM> Follows::getAllFollowedBy(){
	return followedByList;
}

void Follows::printFollowsTable() {
	cout<< "Follows Table" << endl;
	int index = 0;
	for(vector<STMTNUM>::iterator it = followsTable.begin(); it != followsTable.end(); it++) {
		cout<< index << " follows "<< *it<< endl;
		index++;
	}
}