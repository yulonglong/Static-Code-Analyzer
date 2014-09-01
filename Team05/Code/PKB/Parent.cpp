#pragma once

#include "Parent.h"

bool Parent::instanceFlag=false;
Parent* Parent::parent=NULL;

// constructor
Parent::Parent() {
}

Parent::Parent(TypeTable *table) {
	typeTable = table;
}

Parent::~Parent() {
	childrenTable.clear();
	parentTable.clear();
	instanceFlag=false;
}

Parent* Parent::getInstance() {
	if(!instanceFlag)
    {
        parent = new Parent();
        instanceFlag = true;
        return parent;
    }
    else
    {
        return parent;
    }
}

Parent* Parent::getInstance(TypeTable *table) {
	parent = new Parent(table);
	instanceFlag = true;
	return parent;
}

TypeTable* Parent::getTypeTable(){
	return typeTable;
}

void Parent::setParent(STMTNUM s1, STMTNUM s2) {
	try{
		vector<STMTNUM> temp (1,s2);

		try{
			vector<STMTNUM> temp1 = parentTable.at(s1);
			temp1.push_back(s2);
			parentTable.erase(s1);
			parentTable[s1] = temp1;
		} catch(...){
			parentTable[s1] = temp;
		}

		childrenTable[s2] = s1; 
	}catch(...){
	}
}

bool Parent::isParent(STMTNUM s1, STMTNUM s2) {
	try{
		if (childrenTable.at(s2) == s1) {
			return true;
		}
	} catch(...){
	}
	return false;
}

bool Parent::isParent(TYPE t1, TYPE t2) {
	vector<STMTNUM> list; 
	vector<STMTNUM> temp;
	for (unordered_map<STMTNUM, vector<STMTNUM>>::iterator it = parentTable.begin(); it != parentTable.end(); it++) {
		try {
			temp = it->second;
		} catch (...) {
			continue;
		}
		for (vector<STMTNUM>::size_type k = 0; k != temp.size(); k++) { 
			STMTNUM j = temp.at(k);
			try {
				if (t1 == TypeTable::STMT && t2 == TypeTable::STMT) {
					return true;
				} else if (t1 == TypeTable::STMT && t2 != TypeTable::STMT && typeTable->isType(t2,j)) {
					return true;
				} else if (t1 != TypeTable::STMT && t2 == TypeTable::STMT && typeTable->isType(t1,it->first)) {
					return true;
				} else if (t1 != TypeTable::STMT && t2 != TypeTable::STMT && typeTable->isType(t1,it->first) && typeTable->isType(t2,j)) {
					return true;
				}
			} catch (...) {
				// if that stmtnum doesnt have a type in typetable
				continue; 
			}
		}
	}
	return false;
}

bool Parent::isParent(TYPE t, STMTNUM s) {
	try{
		STMTNUM temp = childrenTable.at(s);
		if (typeTable->isType(t,temp)) {
			return true;
		}
	}catch(...){
	}
	return false;
}

bool Parent::isChildren(TYPE t, STMTNUM s){
	try{
		vector<STMTNUM> temp = parentTable.at(s);
		vector<STMTNUM>::iterator it = temp.begin();
		for(;it!=temp.end();++it){
			if(typeTable->isType(t,*it))
				return true;
		}
	}catch(...){
	}
	return false;
}


vector<STMTNUM> Parent::getParent(TYPE t1, TYPE t2, STMTNUM s) {
	try{
		STMTNUM temp = childrenTable.at(s);
		if(typeTable->isType(t2,temp)){
			return typeTable->getAllStmts(t1);
		}
	}catch(...){
	}
	return vector<STMTNUM> (1,-1);
}

vector<STMTNUM> Parent::getChildren(TYPE t1, TYPE t2, STMTNUM s) {
	try{
		vector<STMTNUM> temp = parentTable.at(s);
		vector<STMTNUM>::iterator it = temp.begin();
		for(;it!=temp.end();++it){
			if(typeTable->isType(t2,*it)){
				return typeTable->getAllStmts(t1);
			}
		}
	}catch(...){
	}
	return vector<STMTNUM> (1,-1);
}

vector<STMTNUM> Parent::getChildren(TYPE t1, TYPE t2){
	vector<STMTNUM> list; 
	STMTNUM j = -1; 
	for (unordered_map<STMTNUM, STMTNUM>::iterator it = childrenTable.begin(); it != childrenTable.end(); it++) {
		j = -1; 
		try {
			j = it->second;
		} catch (...) {
			continue;
		}
		try {
			if (j != -1) {
				if (t1 == TypeTable::STMT && t2 == TypeTable::STMT) {
					list.push_back(it->first);
				} else if (t1 == TypeTable::STMT && t2 != TypeTable::STMT && typeTable->isType(t2,it->first)) {
					list.push_back(it->first);
				} else if (t1 != TypeTable::STMT && t2 == TypeTable::STMT && typeTable->isType(t1,j)) {
					list.push_back(it->first);
				} else if (t1 != TypeTable::STMT && t2 != TypeTable::STMT && typeTable->isType(t1,j) && typeTable->isType(t2,it->first)) {
					list.push_back(it->first);
				}
			}
		} catch (...) {
			// if that stmtnum doesnt have a type in typetable
			continue; 
		}
	}
	if(list.empty())
		return vector<STMTNUM> (1,-1);
	sort(list.begin(),list.end());
	return list;
}

vector<STMTNUM> Parent::getParent(TYPE t1, TYPE t2){
	vector<STMTNUM> ans; 
	vector<STMTNUM> temp;
	for (unordered_map<STMTNUM, vector<STMTNUM>>::iterator it = parentTable.begin(); it != parentTable.end(); it++) {
		try {
			temp = it->second;
		} catch (...) {
			continue;
		}
		for (vector<STMTNUM>::size_type k = 0; k != temp.size(); k++) { 
				STMTNUM j = temp.at(k);
				try {
					if (t1 == TypeTable::STMT && t2 == TypeTable::STMT) {
						// cout << i << "  " << j << endl; 
						ans.push_back(it->first);
						break;
					} else if (t1 == TypeTable::STMT && t2 != TypeTable::STMT && typeTable->isType(t2,j)) {
						// cout << i << "  " << j << endl; 
						ans.push_back(it->first);
						break;
					} else if (t1 != TypeTable::STMT && t2 == TypeTable::STMT && typeTable->isType(t1,it->first)) {
						// cout << i << "  " << j << endl; 
						ans.push_back(it->first);
						break;
					} else if (t1 != TypeTable::STMT && t2 != TypeTable::STMT && typeTable->isType(t1,it->first) && typeTable->isType(t2,j)) {
						// cout << i << "  " << j << endl; 
						ans.push_back(it->first);
						break;
					}
				} catch (...) {
					// if that stmtnum doesnt have a type in typetable
					continue; 
				}
		}
	}
	if(ans.empty())
		return vector<STMTNUM> (1,-1);
	sort(ans.begin(),ans.end());
	return ans;
}

STMTNUM Parent::getParent(TYPE t1, STMTNUM s){
	try{
		STMTNUM temp = childrenTable.at(s);
		if(typeTable->isType(t1,temp))
			return temp;
	}catch(...){
		return -1;
	}
	return -1;
}

vector<STMTNUM> Parent::getChildren(TYPE t1, STMTNUM s){
	try{
		vector<STMTNUM> temp = parentTable.at(s);
		vector<STMTNUM> ans;
		vector<STMTNUM>::iterator it = temp.begin();
		for(;it!=temp.end();it++){
			if(typeTable->isType(t1,*it))
				ans.push_back(*it);
		}
		if(ans.empty())
			return vector<STMTNUM> (1,-1);
		sort(ans.begin(),ans.end());
		return ans;
	}catch(...){
		return vector<STMTNUM> (1,-1);
	}
	return vector<STMTNUM> (1,-1);
}


//For parentStar
STMTNUM Parent::getParent(STMTNUM s){
	try{
		return childrenTable.at(s);
	} catch (...){
		return -1;
	}

}

vector<STMTNUM> Parent::getChildren(STMTNUM s){
	try{
		return parentTable.at(s);
	} catch (...){
		return vector<STMTNUM> (1,-1);
	}
}

