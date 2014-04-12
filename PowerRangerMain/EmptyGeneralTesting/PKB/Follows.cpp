#pragma once

#include "Follows.h"
#include <stdexcept>      // std::out_of_range
#include <iostream>

bool Follows::instanceFlag=false;
Follows* Follows::follows=NULL;

// constructor
Follows::Follows() {
	// Note: program line 0 is not to be used for the enumeration of program lines
	followsTable.assign(5, -1);
	followedByTable.assign(5, -1);
}

Follows::Follows(TypeTable *table) {
	typeTable = table;
	// Note: program line 0 is not to be used for the enumeration of program lines
	followsTable.assign(5, -1);
	followedByTable.assign(5, -1);
}

Follows::~Follows() {
	vector<STMTNUM>().swap(followsTable);
	vector<STMTNUM>().swap(followedByTable);
}

Follows* Follows::getInstance() {
	if(!instanceFlag)
    {
        follows = new Follows();
        instanceFlag = true;
        return follows;
    }
    else
    {
        return follows;
    }
}

Follows* Follows::getInstance(TypeTable *table) {
	if(!instanceFlag)
    {
        follows = new Follows(table);
        instanceFlag = true;
        return follows;
    }
    else
    {
        return follows;
    }
}

void Follows::setFollows(STMTNUM s1, STMTNUM s2) {
	if (s1 >= followsTable.size()) {
		followsTable.resize(s1+1, -1);
	}
	followsTable[s1] = s2;

	if (s2 >= followedByTable.size()) {
		followedByTable.resize(s2+1, -1);
	}
	followedByTable[s2] = s1; 
	cout << "Set follows(" << s1 << ", " << s2 << ")" << endl; 
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
				} else if (t1 == TypeTable::STMT && t2 != TypeTable::STMT && typeTable->getType(j) == t2) {
					// cout << i << "  " << j << endl; 
					return true;
				} else if (t1 != TypeTable::STMT && t2 == TypeTable::STMT && typeTable->getType(i) == t1) {
					// cout << i << "  " << j << endl; 
					return true;
				} else if (t1 != TypeTable::STMT && t2 != TypeTable::STMT && typeTable->getType(i) == t1 && typeTable->getType(j) == t2) {
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
	catch (std::out_of_range) {
		// std::cerr << "Out of Range error: " << oor.what() << '\n';
		// cout<<"In catch block"<<endl;
	}
	if (num != -1 && typeTable->isType(t,num)){
		//cout<<"NUM IS"<<num<<endl;
		return num;
	} 
	return -1; 
}


STMTNUM Follows::getFollowedBy(TypeTable::SynType t, STMTNUM s) {
	int num = -1; 
	
	try {
		num = followedByTable[s];
	} 
	//const std::out_of_range& oor
	catch (...) {
		// std::cerr << "Out of Range error: " << oor.what() << '\n';
	}
	if (num != -1 && typeTable->isType(t, num)){
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
				} else if (t1 == TypeTable::STMT && t2 != TypeTable::STMT && typeTable->getType(j) == t2) {
					// cout << i << "  " << j << endl; 
					list.push_back(i);
				} else if (t1 != TypeTable::STMT && t2 == TypeTable::STMT && typeTable->getType(i) == t1) {
					// cout << i << "  " << j << endl; 
					list.push_back(i);

				} else if (t1 != TypeTable::STMT && t2 != TypeTable::STMT && typeTable->getType(i) == t1 && typeTable->getType(j) == t2) {
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
				} else if (t1 == TypeTable::STMT && t2 != TypeTable::STMT && typeTable->getType(j) == t2) {
					// cout << i << "  " << j << endl; 
					list.push_back(j);
				} else if (t1 != TypeTable::STMT && t2 == TypeTable::STMT && typeTable->getType(i) == t1) {
					// cout << i << "  " << j << endl; 
					list.push_back(j);

				} else if (t1 != TypeTable::STMT && t2 != TypeTable::STMT && typeTable->getType(i) == t1 && typeTable->getType(j) == t2) {
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
