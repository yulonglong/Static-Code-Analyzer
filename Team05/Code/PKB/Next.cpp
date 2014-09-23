#pragma once

#include "Next.h"

bool Next::instanceFlag=false;
Next* Next::next=NULL;

//Constructor
Next::Next(){
}

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
		previousTable[s2] = s1; 
	}catch(...){
	}
}

vector<STMTNUM> Next::getNext(STMTNUM s){
	try{
		vector<STMTNUM> ans = nextTable.at(s);
		return ans;
	} catch(...) {
		return vector<STMTNUM> (1,-1);
	}
}

STMTNUM Next::getPrevious(STMTNUM s){
	try{
		STMTNUM ans = previousTable.at(s);
		return ans;
	} catch(...) {
		return -1;
	}
}


