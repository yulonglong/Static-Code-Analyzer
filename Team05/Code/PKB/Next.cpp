#pragma once

#include "Next.h"

bool Next::instanceFlag=false;
Next* Next::next=NULL;

//Constructor

Next::~Next(){
	nextTable.clear();
	instanceFlag=false;
}


Next* Next::getInstance(TypeTable* tt) {
	if(!instanceFlag)
    {
        next = new Next(tt);
        instanceFlag = true;
        return next;
    }
    else
    {
        return next;
    }
}


Next::Next(TypeTable* tt){
	typeTable = tt;
}


void Next::setNext(STMTNUM s1, STMTNUM s2){
	try{
		vector<STMTNUM> temp (1,s2);

		try{
			vector<STMTNUM> temp1 = nextTable.at(s1);
			temp1.push_back(s2);
			nextTable[s1] = temp1;
		} catch(...){
			nextTable[s1] = temp;
		}

		vector<STMTNUM> temp2 (1,s1);

		try{
			vector<STMTNUM> temp3 = previousTable.at(s2);
			temp3.push_back(s1);
			previousTable[s2] = temp3;
		} catch(...){
			previousTable[s2] = temp2;
		}
	}catch(...){
	}
}

vector<STMTNUM> Next::getNext(STMTNUM s){
	vector<STMTNUM> ans;
	try{
		ans = nextTable.at(s);
		return ans;
	} catch(...) {
		return ans;
	}
}

vector<STMTNUM> Next::getPrevious(STMTNUM s){
	vector<STMTNUM> ans;
	try{
		ans = previousTable.at(s);
		return ans;
	} catch(...) {
		return ans;
	}
}

void Next::setNextPair(STMTNUM s, pair<STMTNUM,STMTNUM> p){
	try{
		vector<pair<STMTNUM,STMTNUM>> temp (1,p);

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

void Next::printNextTable() {
	cout<< "Next Table" << endl;
	for(unordered_map<STMTNUM, vector<STMTNUM>>::iterator it = nextTable.begin(); it != nextTable.end(); it++) {
		cout<< it->first << " has next consisting of ";
		vector<STMTNUM> temp = it->second; 
		vector<STMTNUM>::iterator iter;
		for (iter = temp.begin(); iter!=temp.end(); iter++) {
			cout<< *iter<< ",";
		}		
		cout<<endl;
	}
}

void Next::printNextTableForTesting() {
	for(unordered_map<STMTNUM, vector<STMTNUM>>::iterator it = nextTable.begin(); it != nextTable.end(); it++) {
		cout<< it->first << "-";
		vector<STMTNUM> temp = it->second; 
		vector<STMTNUM>::iterator iter;
		for (iter = temp.begin(); iter!=temp.end(); iter++) {
			cout<< *iter<< " ";
		}		
		cout<<"+";
	}
}

vector<STMTNUM> Next::getAllNext(){
	vector<STMTNUM> ans;
	try{
		for(unordered_map<STMTNUM, vector<STMTNUM>>::iterator it = nextTable.begin(); it != nextTable.end(); it++) {
			ans.push_back(it->first);
		}
	} catch(...) {
		ans.clear();
	}
	return ans;
}
vector<STMTNUM> Next::getAllPrevious(){
	vector<STMTNUM> ans;
	try{
		for(unordered_map<STMTNUM, vector<STMTNUM>>::iterator it = previousTable.begin(); it != previousTable.end(); it++) {
			ans.push_back(it->first);
		}
	} catch(...) {
		ans.clear();
	}
	return ans;
}


