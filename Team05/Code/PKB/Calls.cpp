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

vector<PROCINDEX> Calls::getCalls(){
	vector<PROCINDEX> ans;
	for(unordered_map<PROCINDEX, vector<CALLSPAIR>>::iterator it = callsTable.begin();it!=callsTable.end();it++)
		ans.push_back(it->first);
	return ans;
}

vector<PROCINDEX> Calls::getCalled(){
	vector<PROCINDEX> ans;
	for(unordered_map<PROCINDEX, vector<CALLSPAIR>>::iterator it1 = callsTable.begin();it1!=callsTable.end();it1++){
		for(vector<CALLSPAIR>::iterator it2 = it1->second.begin();it2!=it1->second.end();it2++)
			ans.push_back(it2->first);
	}
	sort( ans.begin(), ans.end() );
	ans.erase( unique( ans.begin(), ans.end() ), ans.end() );
	return ans;
}

vector<PROCINDEX> Calls::getCalls(PROCNAME p){
	vector<PROCINDEX> ans;
	PROCINDEX index = procTable->getProcIndex(p);
	try{
		for(unordered_map<PROCINDEX, vector<CALLSPAIR>>::iterator it1 = callsTable.begin();it1!=callsTable.end();it1++){
			for(vector<CALLSPAIR>::iterator it2 = it1->second.begin();it2!=it1->second.end();it2++){
				if(it2->first == index){
					ans.push_back(it1->first);
					break;
				}
			}
		}
	}catch(...){
	}
	return ans;
}

vector<PROCINDEX> Calls::getCalled(PROCNAME p){
	vector<PROCINDEX> ans;
	PROCINDEX index = procTable->getProcIndex(p);
	try{
		vector<CALLSPAIR> temp;
		temp = callsTable.at(index);
		vector<CALLSPAIR>::iterator it = temp.begin();
		for(;it!=temp.end();it++)
			ans.push_back(it->first);
	}
	catch(...){
	}
	return ans;
}