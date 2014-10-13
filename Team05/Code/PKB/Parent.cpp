#pragma once

#include "Parent.h"

bool Parent::instanceFlag=false;
Parent* Parent::parent=NULL;

// constructor
Parent::Parent(TypeTable *table) {
	typeTable = table;
}

Parent::~Parent() {
	childrenTable.clear();
	parentTable.clear();
	instanceFlag=false;
}

Parent* Parent::getInstance(TypeTable *tt){
	if(!instanceFlag)
    {
        parent = new Parent(tt);
        instanceFlag = true;
        return parent;
    }
    else
    {
        return parent;
    }
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

		parentList.push_back(s1);
		sort( parentList.begin(), parentList.end() );
		parentList.erase( unique( parentList.begin(), parentList.end() ), parentList.end() );
		childrenList.push_back(s2);
		sort( childrenList.begin(), childrenList.end() );
		childrenList.erase( unique( childrenList.begin(), childrenList.end() ), childrenList.end() );
	}catch(...){
	}
}

//void Parent::setParent(STMTNUM s1, STMTNUM s2) {
//	try{
//		vector<int64_t> placeHolder (0,1);
//		vector<int64_t> temp (0,1);
//		try{
//			temp = parTable.at(s1);
//		}catch(...){
//			parTable.resize(s1+1,placeHolder);
//		}
//		int location =ceil((double)s2/63);
//		int bitPos = s2%63;
//
//		if(temp.size()<location)
//			temp.resize(location);
//
//		int64_t bitArray = temp.at(location-1);
//		bitArray = bitArray | (((int64_t)1)<<bitPos);
//
//		temp[location-1]=bitArray;
//		parTable[s1]=temp;
//		childrenTable[s2] = s1;
//
//		parentList.push_back(s1);
//		sort( parentList.begin(), parentList.end() );
//		parentList.erase( unique( parentList.begin(), parentList.end() ), parentList.end() );
//		childrenList.push_back(s2);
//		sort( childrenList.begin(), childrenList.end() );
//		childrenList.erase( unique( childrenList.begin(), childrenList.end() ), childrenList.end() );
//	}catch(...){
//	}
//}

bool Parent::isParent(STMTNUM s1, STMTNUM s2) {
	try{
		vector<int64_t> temp=parTable.at(s1);
		int location =ceil((double)s2/63);
		int bitPos = s2%63;
		if(temp.size()<location)
			return false;

		int64_t bitArray = temp.at(location-1);
		if((bitArray & ((int64_t)1<<bitPos))>0)
			return true;
	} catch(...){
	}
	return false;
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

vector<STMTNUM> Parent::getAllChildren(){
	return childrenList;
}

vector<STMTNUM> Parent::getAllParent(){
	return parentList;
}

vector<STMTNUM> Parent::getChildren(STMTNUM s){
	vector<STMTNUM> ans;
	try{
		ans = parentTable.at(s);
		return ans;
	} catch (...){
		return ans;
	}
}

//vector<STMTNUM> Parent::getChildren(STMTNUM s){
//	vector<STMTNUM> ans;
//	try{
//		vector<int64_t> temp=parTable.at(s);
//
//		for(size_t s = 0;s<temp.size();s++){
//			int64_t bitArray = temp.at(s);
//			while(bitArray>0){
//				int64_t bit = bitArray & -bitArray;
//				bitArray -= bit;
//				int number = log((double)bit)/log(2.0) + s*63;
//				ans.push_back(number);
//			}
//		}
//		return ans;
//	}
//	catch(...){
//		ans.clear();
//		return ans;
//	}
//}

STMTNUM Parent::getParent(STMTNUM s){
	STMTNUM ans;
	try{
		ans = childrenTable.at(s);
		return ans;
	} catch (...){
		return ans;
	}
}

bool Parent::isParent(SYNTYPE t1, SYNTYPE t2) {
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

bool Parent::isParent(SYNTYPE t, STMTNUM s) {
	try{
		STMTNUM temp = childrenTable.at(s);
		if (typeTable->isType(t,temp)) {
			return true;
		}
	}catch(...){
	}
	return false;
}

bool Parent::isChildren(SYNTYPE t, STMTNUM s){
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


vector<STMTNUM> Parent::getParent(SYNTYPE t1, SYNTYPE t2, STMTNUM s) {
	vector<STMTNUM> ans;
	try{
		STMTNUM temp = childrenTable.at(s);
		if(typeTable->isType(t2,temp)){
			ans = typeTable->getAllStmts(t1);
		}
		return ans;
	} catch(...){
		return ans;
	}
	
}

vector<STMTNUM> Parent::getChildren(SYNTYPE t1, SYNTYPE t2, STMTNUM s) {
	vector<STMTNUM> ans;
	try{
		vector<STMTNUM> temp = parentTable.at(s);
		vector<STMTNUM>::iterator it = temp.begin();
		for(;it!=temp.end();++it){
			if(typeTable->isType(t2,*it)){
				ans = typeTable->getAllStmts(t1);
			}
		}
		return ans;
	}catch(...){
		return ans;
	}
}

vector<STMTNUM> Parent::getChildren(SYNTYPE t1, SYNTYPE t2){
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
	sort(list.begin(),list.end());
	return list;
}

vector<STMTNUM> Parent::getParent(SYNTYPE t1, SYNTYPE t2){
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
	sort(ans.begin(),ans.end());
	return ans;
}

STMTNUM Parent::getParent(SYNTYPE t1, STMTNUM s){
	try{
		STMTNUM temp = childrenTable.at(s);
		if(typeTable->isType(t1,temp))
			return temp;
	}catch(...){
		return -1;
	}
	return -1;
}

vector<STMTNUM> Parent::getChildren(SYNTYPE t1, STMTNUM s){
	vector<STMTNUM> ans;
	try{
		vector<STMTNUM> temp = parentTable.at(s);
		vector<STMTNUM>::iterator it = temp.begin();
		for(;it!=temp.end();it++){
			if(typeTable->isType(t1,*it))
				ans.push_back(*it);
		}
		sort(ans.begin(),ans.end());
		return ans;
	}catch(...){
		ans.clear();
		return ans;
	}
}


//For parentStar
//STMTNUM Parent::getParent(STMTNUM s){
//	try{
//		return childrenTable.at(s);
//	} catch (...){
//		return -1;
//	}
//
//}
//
//vector<STMTNUM> Parent::getChildren(STMTNUM s){
//	vector<STMTNUM> ans;
//	try{
//		ans = parentTable.at(s);
//		return ans;
//	} catch (...){
//		return ans;
//	}
//}

void Parent::printParentTable() {
	cout<< "Parent Table" << endl;
	for(unordered_map<STMTNUM, vector<STMTNUM>>::iterator it = parentTable.begin(); it != parentTable.end(); it++) {
		cout<< it->first << " is parent of ";
		vector<STMTNUM> temp = it->second; 
		vector<STMTNUM>::iterator iter;
		for (iter = temp.begin(); iter!=temp.end(); iter++) {
			cout<< *iter<< ",";
		}		
		cout<<endl;
	}
}