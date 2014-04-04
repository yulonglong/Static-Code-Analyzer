#pragma once

#include "Follows.h"
#include <stdexcept>      // std::out_of_range
#include <iostream>

// constructor
Follows::Follows() {
	// Note: program line 0 is not to be used for the enumeration of program lines
	followsTable.assign(5, -1);
	followedByTable.assign(5, -1);
}

Follows::Follows(TypeTable tab) {
	table = tab;
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
	STMTNUM num = -1; 
	try {
		num = followsTable.at(s1);
	} 
	//const std::out_of_range& oor
	catch (...) {
		return false;
		// std::cerr << "Out of Range error: " << oor.what() << '\n';
	}
	if (num != -1 && num == s2){
		return true;
	} 
	return false; 

}

bool Follows::isFollows(TypeTable::SynType t, STMTNUM s) {
	STMTNUM result = getFollows(t, s);
	bool noResult = (result == -1);
	if (noResult) {
		return false;
	} 
	return true;
}

bool Follows::isFollowedBy(TypeTable::SynType t, STMTNUM s) {
	STMTNUM result = getFollowedBy(t, s);
	bool noResult = (result == -1);
	if (noResult) {
		return false;
	} 
	return true;
}

bool Follows::isFollows(TypeTable::SynType t1, TypeTable::SynType t2) {
	STMTNUM j = -1; 
	for (vector<STMTNUM>::size_type i = 0; i != followsTable.size(); i++) {
		j = -1; 
		try {
			// cout << "Try: i is " << i << endl; 
			j = followsTable[i];
			// cout << "Try: j is " << j << endl; 
			
		} catch (...) {
			//const std::out_of_range& oor
			// cout << "Catch: j is " << j << endl; 
			continue;
		}

		try {
			if (j != -1) {
				if (t1 == TypeTable::STMT && t2 == TypeTable::STMT) {
					// cout << i << "  " << j << endl; 
					return true;
				} else if (t1 == TypeTable::STMT && t2 != TypeTable::STMT && table.getType(j) == t2) {
					// cout << i << "  " << j << endl; 
					return true;
				} else if (t1 != TypeTable::STMT && t2 == TypeTable::STMT && table.getType(i) == t1) {
					// cout << i << "  " << j << endl; 
					return true;
				} else if (t1 != TypeTable::STMT && t2 != TypeTable::STMT && table.getType(i) == t1 && table.getType(j) == t2) {
					// cout << i << "  " << j << endl; 
					return true;
				}
			}
		} catch (...) {
			// if that stmtnum doesnt have a type in typetable
			continue; 
		}
	}
	return false;
}

STMTNUM Follows::getFollows(TypeTable::SynType t, STMTNUM s) {
	STMTNUM num = -1; 
	try {
		num = followsTable.at(s);
	} 
	//const std::out_of_range& oor
	catch (...) {
		// std::cerr << "Out of Range error: " << oor.what() << '\n';
		cout<<"In catch block"<<endl;
	}
	if (num != -1 && table.getType(num) == t){
		return num;
	} 
	return -1; 
}


STMTNUM Follows::getFollowedBy(TypeTable::SynType t, STMTNUM s) {
	STMTNUM num = -1; 
	try {
		cout<<"In Try Block"<<endl;
		num = followedByTable.at(s);
		cout<<"NUM="<<num<<endl;
	} 
	//const std::out_of_range& oor
	catch (...) {
		// std::cerr << "Out of Range error: " << oor.what() << '\n';
		cout<<"In catch block"<<endl;
	}
	if (num != -1 && table.getType(num) == t){
		cout<<"SHOULD BE IN HERE"<<endl;
		return num;
	} 
	return -1; 
}

vector<STMTNUM> Follows::getFollows(TypeTable::SynType t1, TypeTable::SynType t2) {
	vector<STMTNUM> list; 
	STMTNUM j = -1; 
	for (vector<STMTNUM>::size_type i = 0; i != followsTable.size(); i++) {
		j = -1; 
		try {
			// cout << "Try: i is " << i << endl; 
			j = followsTable[i];
			// cout << "Try: j is " << j << endl; 
			
		} catch (...) {
			//const std::out_of_range& oor
			// cout << "Catch: j is " << j << endl; 
			continue;
		}

		try {
			if (j != -1) {
				if (t1 == TypeTable::STMT && t2 == TypeTable::STMT) {
					// cout << i << "  " << j << endl; 
					list.push_back(i);
				} else if (t1 == TypeTable::STMT && t2 != TypeTable::STMT && table.getType(j) == t2) {
					// cout << i << "  " << j << endl; 
					list.push_back(i);
				} else if (t1 != TypeTable::STMT && t2 == TypeTable::STMT && table.getType(i) == t1) {
					// cout << i << "  " << j << endl; 
					list.push_back(i);

				} else if (t1 != TypeTable::STMT && t2 != TypeTable::STMT && table.getType(i) == t1 && table.getType(j) == t2) {
					// cout << i << "  " << j << endl; 
					list.push_back(i);

				}
			}
		} catch (...) {
			// if that stmtnum doesnt have a type in typetable
			continue; 
		}
	}
	return list;
}

vector<STMTNUM> Follows::getFollowedBy(TypeTable::SynType t1, TypeTable::SynType t2) {
	vector<STMTNUM> list; 
	STMTNUM j = -1; 
	for (vector<STMTNUM>::size_type i = 0; i != followsTable.size(); i++) {
		j = -1; 
		try {
			// cout << "Try: i is " << i << endl; 
			j = followsTable[i];
			// cout << "Try: j is " << j << endl; 
			
		} catch (...) {
			//const std::out_of_range& oor
			// cout << "Catch: j is " << j << endl; 
			continue;
		}

		try {
			if (j != -1) {
				if (t1 == TypeTable::STMT && t2 == TypeTable::STMT) {
					// cout << i << "  " << j << endl; 
					list.push_back(j);
				} else if (t1 == TypeTable::STMT && t2 != TypeTable::STMT && table.getType(j) == t2) {
					// cout << i << "  " << j << endl; 
					list.push_back(j);
				} else if (t1 != TypeTable::STMT && t2 == TypeTable::STMT && table.getType(i) == t1) {
					// cout << i << "  " << j << endl; 
					list.push_back(j);

				} else if (t1 != TypeTable::STMT && t2 != TypeTable::STMT && table.getType(i) == t1 && table.getType(j) == t2) {
					// cout << i << "  " << j << endl; 
					list.push_back(j);

				}
			}
		} catch (...) {
			// if that stmtnum doesnt have a type in typetable
			continue; 
		}
	}
	return list;
}


// TODO: Throw away
/*
vector<STMTNUM> Follows::getFollows(Query::SynType t1, Query::SynType t2,Query::SynType t3) {
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
*/

// TODO: Throw away
/*
vector<STMTNUM> Follows::getFollowedBy(Query::SynType t1, Query::SynType t2, Query::SynType t3) {
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
*/