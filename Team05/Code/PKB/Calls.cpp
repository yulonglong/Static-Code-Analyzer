#pragma once

#include "Calls.h"

bool Calls::instanceFlag=false;
Calls* Calls::calls=NULL;

//Constructor
Calls::~Calls(){
	callsTable.clear();
	instanceFlag=false;
}

Calls* Calls::getInstance(ProcTable* pt) {
	if(!instanceFlag){
        calls = new Calls(pt);
        instanceFlag = true;
        return calls;
    }
    else
    {
        return calls;
    }
}


Calls::Calls(ProcTable* pt){
	procTable = pt;
}

unordered_map<PROCINDEX, vector<CALLSPAIR>> Calls::getCallsTable(){
	return callsTable;
}

void Calls::setCalls(PROCNAME p1, PROCNAME p2, STMTNUM s){
	try{
		PROCINDEX index1 = procTable->getProcIndex(p1);
		PROCINDEX index2 = procTable->getProcIndex(p2);

		CALLSPAIR tempPair (index2,s);
		vector<CALLSPAIR> temp (1,tempPair);

		try{
			vector<CALLSPAIR> temp1 = callsTable.at(index1);
			temp1.push_back(tempPair);
			callsTable.erase(index1);
			callsTable[index1] = temp1;
		} catch(...){
			callsTable[index1] = temp;
		}
	}catch(...){
	}
}

bool Calls::isCalls(PROCNAME p1, PROCNAME p2){
	try{
		PROCINDEX index1 = procTable->getProcIndex(p1);
		PROCINDEX index2 = procTable->getProcIndex(p2);

		if(index1==-1 || index2==-1)
			return false;

		vector<CALLSPAIR> temp = callsTable.at(index1);
		vector<CALLSPAIR>::iterator it = temp.begin();
		for(;it!=temp.end();it++){
			if(index2==get<0>(*it))
				return true;
		}
		return false;
	}catch(...){
		return false;
	}
}

bool Calls::isCalls2(PROCINDEX index1, PROCINDEX index2){
	try{
		if(index1==-1 || index2==-1)
			return false;

		vector<CALLSPAIR> temp = callsTable.at(index1);
		vector<CALLSPAIR>::iterator it = temp.begin();
		for(;it!=temp.end();it++){
			if(index2==get<0>(*it))
				return true;
		}
		return false;
	}catch(...){
		return false;
	}
}

set<PROCINDEX> Calls::getCalls(){
	set<PROCINDEX> ans;
	for(unordered_map<PROCINDEX, vector<CALLSPAIR>>::iterator it = callsTable.begin();it!=callsTable.end();it++)
		ans.insert(it->first);
	return ans;
}

set<PROCINDEX> Calls::getCalled(){
	set<PROCINDEX> ans;
	for(unordered_map<PROCINDEX, vector<CALLSPAIR>>::iterator it1 = callsTable.begin();it1!=callsTable.end();it1++){
		for(vector<CALLSPAIR>::iterator it2 = it1->second.begin();it2!=it1->second.end();it2++)
			ans.insert(it2->first);
	}
	return ans;
}

set<PROCINDEX> Calls::getCalls(PROCNAME p){
	set<PROCINDEX> ans;
	PROCINDEX index = procTable->getProcIndex(p);
	try{
		for(unordered_map<PROCINDEX, vector<CALLSPAIR>>::iterator it1 = callsTable.begin();it1!=callsTable.end();it1++){
			for(vector<CALLSPAIR>::iterator it2 = it1->second.begin();it2!=it1->second.end();it2++){
				if(it2->first == index){
					ans.insert(it1->first);
					break;
				}
			}
		}
	}catch(...){
	}
	return ans;
}

set<PROCINDEX> Calls::getCalls2(PROCINDEX index){
	set<PROCINDEX> ans;
	try{
		for(unordered_map<PROCINDEX, vector<CALLSPAIR>>::iterator it1 = callsTable.begin();it1!=callsTable.end();it1++){
			for(vector<CALLSPAIR>::iterator it2 = it1->second.begin();it2!=it1->second.end();it2++){
				if(it2->first == index){
					ans.insert(it1->first);
					break;
				}
			}
		}
	}catch(...){
	}
	return ans;
}

set<PROCINDEX> Calls::getCalled(PROCNAME p){
	set<PROCINDEX> ans;
	PROCINDEX index = procTable->getProcIndex(p);
	try{
		vector<CALLSPAIR> temp;
		temp = callsTable.at(index);
		vector<CALLSPAIR>::iterator it = temp.begin();
		for(;it!=temp.end();it++)
			ans.insert(it->first);
	}
	catch(...){
	}
	return ans;
}

set<PROCINDEX> Calls::getCalled2(PROCINDEX index){
	set<PROCINDEX> ans;
	try{
		vector<CALLSPAIR> temp;
		temp = callsTable.at(index);
		vector<CALLSPAIR>::iterator it = temp.begin();
		for(;it!=temp.end();it++)
			ans.insert(it->first);
	}
	catch(...){
	}
	return ans;
}

void Calls::printCallsTable() {
	cout<< "Calls Table" << endl;
	for(unordered_map<PROCINDEX, vector<CALLSPAIR>>::iterator it = callsTable.begin(); it != callsTable.end(); it++) {
		string name1 = procTable->getProcName(it->first);
		cout<< name1 << " modifies ";
		vector<CALLSPAIR> temp = it->second; 
		vector<CALLSPAIR>::iterator iter;
		for (iter = temp.begin(); iter!=temp.end(); iter++) {
			string name = procTable->getProcName(iter->first);
			cout<< name<< ",";
		}		
		cout<<endl;
	}
}