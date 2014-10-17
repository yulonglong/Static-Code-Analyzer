#pragma once

#include "Parent.h"

bool Parent::instanceFlag=false;
Parent* Parent::parent=NULL;

// constructor
Parent::Parent() {
}

Parent::~Parent() {
	childrenTable.clear();
	parentTable.clear();
	parentList.clear();
	childrenList.clear();
	instanceFlag=false;
}

Parent* Parent::getInstance(){
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

void Parent::setParent(STMTNUM s1, STMTNUM s2) {
	try{
		vector<int64_t> placeHolder (0,1);
		vector<int64_t> temp (0,1);
		try{
			temp = parentTable.at(s1);
		}catch(...){
			parentTable.resize(s1+1,placeHolder);
		}
		int location =ceil((double)s2/63);
		int bitPos = s2%63;

		if(temp.size()<location)
			temp.resize(location);

		int64_t bitArray = temp.at(location-1);
		bitArray = bitArray | (((int64_t)1)<<bitPos);

		temp[location-1]=bitArray;
		parentTable[s1]=temp;
		if(s2>=childrenTable.size())
			childrenTable.resize(s2+1,-1);
		childrenTable[s2] = s1;

		parentList.insert(s1);
		childrenList.insert(s2);
	}catch(...){
	}
}

bool Parent::isParent(STMTNUM s1, STMTNUM s2) {
	try{
		if(s1==-1)
			return false;
		if (childrenTable.at(s2) == s1) 
			return true;
	} catch(...){
	}
	return false;
}

set<STMTNUM> Parent::getChildren(STMTNUM s){
	set<STMTNUM> ans;
	try{
		vector<int64_t> temp=parentTable.at(s);

		for(size_t s = 0;s<temp.size();s++){
			int64_t bitArray = temp.at(s);
			while(bitArray>0){
				int64_t bit = bitArray & -bitArray;
				bitArray -= bit;
				int number = log((double)bit)/log(2.0) + s*63;
				ans.insert(number);
			}
		}
		return ans;
	}
	catch(...){
		ans.clear();
		return ans;
	}
}

STMTNUM Parent::getParent(STMTNUM s){
	STMTNUM ans;
	try{
		ans = childrenTable.at(s);
		return ans;
	} catch (...){
		return -1;
	}
}

set<STMTNUM> Parent::getAllChildren(){
	return childrenList;
}

set<STMTNUM> Parent::getAllParent(){
	return parentList;
}

void Parent::printParentTable() {
	cout<< "Parent Table" << endl;
	int index=0;
	for(vector<vector<int64_t>>::iterator it = parentTable.begin(); it != parentTable.end(); it++,index++) {
		if(it->size()!=0){
			cout<< index << " is parent of ";
			vector<int64_t> temp = *it; 
			for (size_t s =0; s!=temp.size(); s++) {
				int64_t bitArray = temp.at(s);
				while(bitArray>0){
					int64_t bit = bitArray & -bitArray;
					bitArray -= bit;
					int number = log((double)bit)/log(2.0) + s*63;
					cout<< number<< ",";
				}
			}		
			cout<<endl;
		}
	}
}