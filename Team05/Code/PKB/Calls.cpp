#pragma once

#include "Calls.h"

bool Calls::instanceFlag=false;
Calls* Calls::calls=NULL;

//Constructor
Calls::Calls(){
}

Calls::~Calls(){
	callsTable.clear();
	instanceFlag=false;
}

Calls* Calls::getInstance() {
	if(!instanceFlag)
    {
        calls = new Calls();
        instanceFlag = true;
        return calls;
    }
    else
    {
        return calls;
    }
}

Calls* Calls::getInstance(ProcTable* pt) {
	if(!instanceFlag)
    {
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

vector<int> Calls::getCalls(){
	vector<int> ans;
	return ans;
}

vector<int> Calls::getCalled(){
	vector<int> ans;
	return ans;
}

vector<int> Calls::getCalls(PROCNAME p){
	vector<int> ans;
	return ans;
}

vector<int> Calls::getCalled(PROCNAME p){
	vector<int> ans;
	return ans;
}