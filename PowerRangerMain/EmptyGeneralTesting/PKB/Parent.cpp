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
	vector<STMTNUM> existing;
	try{
		existing = parentTable.at(s1);
		parentTable.erase(s1);
	}
	catch(...){
	}
	existing.push_back(s2);
	parentTable.insert(pair<STMTNUM,vector<STMTNUM>>(s1,existing));
	
	childrenTable.insert(pair<STMTNUM,STMTNUM>(s2,s1)); 

	cout << "Set parent (" << s1 << ", " << s2 << ")" << endl; 
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
	for (map<STMTNUM,vector<STMTNUM>>::iterator i = parentTable.begin(); i != parentTable.end(); i++) {
		try {
			temp = parentTable.at(i->first);
		} catch (...) {
			//const std::out_of_range& oor
			// cout << "Catch: j is " << j << endl; 
			continue;
		}
		for (vector<STMTNUM>::size_type k = 0; k != temp.size(); k++) { 
			STMTNUM j = temp.at(k);
			try {
				if (t1 == TypeTable::STMT && t2 == TypeTable::STMT) {
					// cout << i << "  " << j << endl; 
					return true;
				} else if (t1 == TypeTable::STMT && t2 != TypeTable::STMT && typeTable->isType(t2,j)) {
					// cout << i << "  " << j << endl; 
					return true;
				} else if (t1 != TypeTable::STMT && t2 == TypeTable::STMT && typeTable->isType(t1,i->first)) {
					// cout << i << "  " << j << endl; 
					return true;
				} else if (t1 != TypeTable::STMT && t2 != TypeTable::STMT && typeTable->isType(t1,i->first) && typeTable->isType(t2,j)) {
					// cout << i << "  " << j << endl; 
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
	for (map<STMTNUM,STMTNUM>::iterator i = childrenTable.begin(); i != childrenTable.end(); i++) {
		j = -1; 
		try {
			j = i->second;
		} catch (...) {
			//const std::out_of_range& oor
			// cout << "Catch: j is " << j << endl; 
			continue;
		}
		try {
			if (j != -1) {
				if (t1 == TypeTable::STMT && t2 == TypeTable::STMT) {
					// cout << i << "  " << j << endl; 
					list.push_back(i->first);
				} else if (t1 == TypeTable::STMT && t2 != TypeTable::STMT && typeTable->isType(t2,i->first)) {
					// cout << i << "  " << j << endl; 
					list.push_back(i->first);
				} else if (t1 != TypeTable::STMT && t2 == TypeTable::STMT && typeTable->isType(t1,j)) {
					// cout << i << "  " << j << endl; 
					list.push_back(i->first);
				} else if (t1 != TypeTable::STMT && t2 != TypeTable::STMT && typeTable->isType(t1,j) && typeTable->isType(t2,i->first)) {
					// cout << i << "  " << j << endl; 
					list.push_back(i->first);

				}
			}
		} catch (...) {
			// if that stmtnum doesnt have a type in typetable
			continue; 
		}
	}
	if(list.empty())
		return vector<STMTNUM> (1,-1);
	return list;
}

vector<STMTNUM> Parent::getParent(TYPE t1, TYPE t2){
	vector<STMTNUM> list; 
	vector<STMTNUM> temp;
	for (map<STMTNUM,vector<STMTNUM>>::iterator i = parentTable.begin(); i != parentTable.end(); i++) {
		try {
			temp = parentTable.at(i->first);
		} catch (...) {
			//const std::out_of_range& oor
			// cout << "Catch: j is " << j << endl; 
			continue;
		}
		if(temp.at(0)!=-1){
			for (vector<STMTNUM>::size_type k = 0; k != temp.size(); k++) { 
				STMTNUM j = temp.at(k);
				try {
					if (t1 == TypeTable::STMT && t2 == TypeTable::STMT) {
						// cout << i << "  " << j << endl; 
						list.push_back(i->first);
						break;
					} else if (t1 == TypeTable::STMT && t2 != TypeTable::STMT && typeTable->isType(t2,j)) {
						// cout << i << "  " << j << endl; 
						list.push_back(i->first);
						break;
					} else if (t1 != TypeTable::STMT && t2 == TypeTable::STMT && typeTable->isType(t1,i->first)) {
						// cout << i << "  " << j << endl; 
						list.push_back(i->first);
						break;
					} else if (t1 != TypeTable::STMT && t2 != TypeTable::STMT && typeTable->isType(t1,i->first) && typeTable->isType(t2,j)) {
						// cout << i << "  " << j << endl; 
						list.push_back(i->first);
						break;
					}
				} catch (...) {
					// if that stmtnum doesnt have a type in typetable
					continue; 
				}
			}
		}
	}
	if(list.empty())
		return vector<STMTNUM> (1,-1);
	return list;

	return vector<STMTNUM> (1,-1);
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

