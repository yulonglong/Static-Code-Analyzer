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

void Calls::setCalls(PROCNAME p1, PROCNAME p2){
	try{
		PROCINDEX index1 = procTable->getProcIndex(p1);
		PROCINDEX index2 = procTable->getProcIndex(p2);

		vector<PROCINDEX> temp (1,index2);

		try{
			vector<PROCINDEX> temp1 = callsTable.at(index1);
			temp1.push_back(index2);
			callsTable.erase(index1);
			callsTable[index1] = temp1;
		} catch(...){
			callsTable[index1] = temp;
		}
	}catch(...){
	}
}

bool Calls::isCalled(PROCNAME p1, PROCNAME p2){
	try{
		PROCINDEX index1 = procTable->getProcIndex(p1);
		PROCINDEX index2 = procTable->getProcIndex(p2);

		if(index1==-1 || index2==-1)
			return false;

		vector<PROCINDEX> temp = callsTable.at(index1);
		vector<PROCINDEX>::iterator it = temp.begin();
		for(;it!=temp.end();it++){
			if(index2==*it)
				return true;
		}
		return false;
	}catch(...){
		return false;
	}
}