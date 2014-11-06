#pragma once
#pragma warning( disable : 4018)
#pragma warning( disable : 4244)

#include "Sibling.h"

bool Sibling::instanceFlag=false;
Sibling* Sibling::sibling=NULL;

// constructor
Sibling::Sibling() {
	flagTable.push_back(false);
	indexTable.push_back(-1);
}

Sibling::~Sibling() {
	siblingTable.clear();
	siblingList.clear();
	instanceFlag=false;
}

Sibling* Sibling::getInstance(){
	if(!instanceFlag)
    {
        sibling = new Sibling();
        instanceFlag = true;
        return sibling;
    }
    else
    {
        return sibling;
    }
}

void Sibling::setSibling(STMTNUM s1, STMTNUM s2) {
	try{
		if(s1>flagTable.size()-1)
			flagTable.resize(s1+1,false);
		if(s2>flagTable.size()-1)
			flagTable.resize(s2+1,false);
		if(s1>indexTable.size()-1)
			indexTable.resize(s1+1,-1);
		if(s2>indexTable.size()-1)
			indexTable.resize(s2+1,-1);
		
	
		if(!flagTable.at(s1) && !flagTable.at(s2)){
			flagTable[s1] = true;
			flagTable[s2] = true;

			int index = siblingTable.size();
			indexTable[s1] = index;
			indexTable[s2] = index;

			vector<STMTNUM> temp;
			temp.push_back(s1);
			temp.push_back(s2);
			siblingTable.push_back(temp);
		} else if (flagTable.at(s1) && !flagTable.at(s2)){
			flagTable[s2] = true;

			int index = indexTable.at(s1);
			indexTable[s2] = index;

			vector<STMTNUM> temp = siblingTable.at(index);
			temp.push_back(s2);
			siblingTable[index] = temp;
		} else if (!flagTable.at(s1) && flagTable.at(s2)){
			flagTable[s1] = true;

			int index = indexTable.at(s2);
			indexTable[s1] = index;

			vector<STMTNUM> temp = siblingTable.at(index);
			temp.push_back(s1);
			siblingTable[index] = temp;
		}
		siblingList.insert(s1);
		siblingList.insert(s2);
	}catch(...){
	}
}

bool Sibling::isSibling(STMTNUM s1, STMTNUM s2) {
	try{
		if(!flagTable.at(s1) || !flagTable.at(s2))
			return false;
		if(indexTable.at(s1) == -1 || indexTable.at(s2) == -1)
			return false;
		if(indexTable.at(s1) == indexTable.at(s2))
			return true;
	} catch(...){
	}
	return false;
}

set<STMTNUM> Sibling::getSibling(STMTNUM s){
	set<STMTNUM> ans;
	try{
		int index = indexTable.at(s);
		vector<STMTNUM> temp = siblingTable.at(index);
		for (vector<STMTNUM>::iterator it = temp.begin(); it != temp.end(); it++){
			if(*it!=s)
				ans.insert(*it);
		}
		return ans;
	} catch (...){
		return ans;
	}
}


set<STMTNUM> Sibling::getAllSibling(){
	return siblingList;
}

void Sibling::printSiblingTable() {
	cout<< "Sibling Table" << endl;
	for (vector<vector<STMTNUM>>::iterator it = siblingTable.begin(); it != siblingTable.end(); it++) {
		if(it->size()!=0){
			cout<< "Set of sibling = ";
			vector<STMTNUM> temp = *it; 
			for (vector<STMTNUM>::iterator iter = temp.begin(); iter != temp.end(); iter++){
				cout<< *iter<< ",";
			}
			cout<<endl;
		}
	}
}