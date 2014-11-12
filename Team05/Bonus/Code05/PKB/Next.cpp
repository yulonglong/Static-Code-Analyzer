#pragma once
#pragma warning( disable : 4018)

#include "Next.h"

bool Next::instanceFlag=false;
Next* Next::next=NULL;

//Constructor

Next::~Next(){
	nextTable.clear();
	instanceFlag=false;
}


Next* Next::getInstance() {
	if(!instanceFlag)
    {
        next = new Next();
        instanceFlag = true;
        return next;
    }
    else
    {
        return next;
    }
}


Next::Next(){
}


void Next::setNext(STMTNUM s1, STMTNUM s2){
	try{
		vector<STMTNUM> temp (1,s2);
		if(s1>=nextTable.size()){
			vector<STMTNUM> empty;
			nextTable.resize(s1+1,empty);
		}
		try{
			vector<STMTNUM> temp1 = nextTable.at(s1);
			temp1.push_back(s2);
			nextTable[s1] = temp1;
		} catch(...){
			nextTable[s1] = temp;
		}

		nextList.insert(s1);

		vector<STMTNUM> temp2 (1,s1);
		if(s2>=previousTable.size()){
			vector<STMTNUM> empty;
			previousTable.resize(s2+1,empty);
		}
		try{
			vector<STMTNUM> temp3 = previousTable.at(s2);
			temp3.push_back(s1);
			previousTable[s2] = temp3;
		} catch(...){
			previousTable[s2] = temp2;
		}

		previousList.insert(s2);
	}catch(...){
	}
}

set<STMTNUM> Next::getNext(STMTNUM s){
	set<STMTNUM> ans;
	try{
		vector<STMTNUM> tempVec = nextTable.at(s);
		for(vector<STMTNUM>::iterator it = tempVec.begin(); it !=tempVec.end();it++){
			ans.insert(*it);
		}
		return ans;
	} catch(...) {
		return ans;
	}
}

set<STMTNUM> Next::getPrevious(STMTNUM s){
	set<STMTNUM> ans;
	try{
		vector<STMTNUM> tempVec = previousTable.at(s);
		for(vector<STMTNUM>::iterator it = tempVec.begin(); it !=tempVec.end();it++){
			ans.insert(*it);
		}
		return ans;
	} catch(...) {
		return ans;
	}
}

bool Next::isNext(STMTNUM s1, STMTNUM s2){
	try{
		vector<STMTNUM> temp = nextTable.at(s1);
		vector<STMTNUM>::iterator iter;
		for (iter = temp.begin(); iter!=temp.end(); iter++) {
			if(*iter==s2)
				return true;
		}		
	} catch(...){
		return false;
	}
	return false;
}

set<STMTNUM> Next::getAllNext(){
	return nextList;
}
set<STMTNUM> Next::getAllPrevious(){
	return previousList;
}

void Next::setNextPair(STMTNUM s, pair<STMTNUM,STMTNUM> p){
	try{
		vector<pair<STMTNUM,STMTNUM>> temp (1,p);

		if(s>=nextPairTable.size()){
			vector<pair<STMTNUM,STMTNUM>> empty;
			nextPairTable.resize(s+1,empty);
		}
		try{
			vector<pair<STMTNUM,STMTNUM>> temp1 = nextPairTable.at(s);
			temp1.push_back(p);
			nextPairTable[s] = temp1;
		} catch(...){
			nextPairTable[s] = temp;
		}
	}catch(...){
	}
}

vector<pair<STMTNUM,STMTNUM>> Next::getNextPair(STMTNUM s){
	vector<pair<STMTNUM,STMTNUM>> ans;
	try{
		ans = nextPairTable.at(s);
		return ans;
	} catch(...){
		ans.clear();
		return ans;
	}
}

void Next::printNextTable() {
	cout<< "Next Table" << endl;
	int index=0;
	for(vector<vector<STMTNUM>>::iterator it = nextTable.begin(); it != nextTable.end(); it++,index++) {
		cout<< index << " has next consisting of ";
		vector<STMTNUM> temp = *it; 
		vector<STMTNUM>::iterator iter;
		for (iter = temp.begin(); iter!=temp.end(); iter++) {
			cout<< *iter<< ",";
		}		
		cout<<endl;
	}
}

void Next::printNextPairTableForTesting() {
	cout<< "Next pair Table" << endl;
	int index=0;
	for(vector<vector<pair<STMTNUM,STMTNUM>>>::iterator it = nextPairTable.begin(); it != nextPairTable.end(); it++,index++) {
		vector<pair<STMTNUM,STMTNUM>> temp1 = *it;
		if(!temp1.empty()){
			cout<<"("<< index<<"): [";
			vector<pair<STMTNUM,STMTNUM>> temp = *it; 
			vector<pair<STMTNUM,STMTNUM>>::iterator iter;
			for (iter = temp.begin(); iter!=temp.end(); iter++) {
				cout<<"("<< iter->first<<","<<iter->second<<")";
			}		
			cout<<"]"<<endl;
		}
	}
}

void Next::printNextTableForTesting() {
	cout<< "Next pair Table for testing" << endl;
	int index=0;
	for(vector<vector<STMTNUM>>::iterator it = nextTable.begin(); it != nextTable.end(); it++) {
		vector<STMTNUM> temp1 = *it;
		if(!temp1.empty()){
			cout<< index << "-";
			vector<STMTNUM> temp = *it; 
			vector<STMTNUM>::iterator iter;
			for (iter = temp.begin(); iter!=temp.end(); iter++) {
				cout<< *iter<< " ";
			}		
			cout<<"+";
		}
	}
}




