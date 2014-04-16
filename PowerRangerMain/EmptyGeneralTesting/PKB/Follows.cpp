#pragma once

#include "Follows.h"
#include <stdexcept>      // std::out_of_range
#include <iostream>

bool Follows::instanceFlag=false;
Follows* Follows::follows=NULL;

// constructor
Follows::Follows() {
}

Follows::Follows(TypeTable *table) {
	typeTable = table;
}

// TODO: delete
Follows::~Follows() {
	followsTable.clear();
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

Follows* Follows::getInstance(TypeTable *table) {
	if (!instanceFlag) {
        follows = new Follows(table);
        instanceFlag = true;
        return follows;
    } else {
        return follows;
    }
}

void Follows::setFollows(STMTNUM s1, STMTNUM s2) {
	followsTable.insert(pair<STMTNUM,STMTNUM>(s1,s2)); 
	cout << "Set follows(" << s1 << ", " << s2 << ")" << endl; 
}

bool Follows::isFollows(STMTNUM s1, STMTNUM s2) {
	try{
		if (followsTable.at(s1) == s2) {
			return true;
		}
	} catch(...){
	}
	return false;
}

bool Follows::isFollows(TYPE t, STMTNUM s) {
	STMTNUM result = getFollows(t, s);
	bool noResult = (result == -1);
	if (noResult) {
		return false;
	} 
	return true;
}

bool Follows::isFollowedBy(TYPE t, STMTNUM s) {
	STMTNUM result = getFollowedBy(t, s);
	bool noResult = (result == -1);
	if (noResult) {
		return false;
	} 
	return true;
}

bool Follows::isFollows(TYPE t1, TYPE t2) {
	vector<STMTNUM> temp = getFollows(t1, t2); 
	// cout <<"hello"<< temp.size() << " "<<temp.at(0)<<endl; 
	if (temp.size() == 1 && temp.at(0) == -1) {
		return false;
	}
	return true;
}

STMTNUM Follows::getFollows(TYPE t, STMTNUM s) {
	try {
		STMTNUM temp = followsTable.at(s);
		if (typeTable->isType(t, temp)) {
			return temp;
		}
	} catch(...){
		return -1;
	}
	return -1;
}

STMTNUM Follows::getFollowedBy(TYPE t, STMTNUM s) {
	try {
		for (map<STMTNUM, STMTNUM>::iterator i = followsTable.begin(); i != followsTable.end(); i++) {
			if (i->second == s && typeTable->isType(t, i->first))  {
				return i->first;
			}
		}
	} catch (...) {
		return -1;
	}
	return -1;  
}

vector<STMTNUM> Follows::getFollows(TYPE t1, TYPE t2) {
	vector<STMTNUM> list; 
	try {
		for (map<STMTNUM, STMTNUM>::iterator i = followsTable.begin(); i != followsTable.end(); ++i) {
			if (typeTable->isType(t1, i->first) && typeTable->isType(t2, i->second))  {
				//cout << i->first << " ,g "<< i->second<<endl; 
				list.push_back(i->second);
			}
		}
		if (list.empty()) {
			return vector<STMTNUM> (1,-1);
		}
		return list; 
	} catch (...) {
		return vector<STMTNUM> (1,-1);
	}

	//return vector<STMTNUM> (1,-1);
	// return list;
}

vector<STMTNUM> Follows::getFollowedBy(TYPE t1, TYPE t2) {
	vector<STMTNUM> list; 
	try {
		for (map<STMTNUM, STMTNUM>::iterator i = followsTable.begin(); i != followsTable.end(); i++) {
			if (typeTable->isType(t1, i->first) && typeTable->isType(t2, i->second))  {
				list.push_back(i->first);
			}
		}
		if (list.empty()) {
			return vector<STMTNUM> (1,-1);
		}
		return list; 
	} catch (...) {
		return vector<STMTNUM> (1,-1);
	}

	//return vector<STMTNUM> (1,-1);
}
