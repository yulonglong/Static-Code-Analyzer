#pragma once

#include "ConstTable.h"

bool ConstTable::instanceFlag=false;
ConstTable* ConstTable::constTable=NULL;
CONSTINDEX ConstTable::currentIndex = 0;

// constructor
ConstTable::ConstTable() {
	currentIndex = 0;
}

ConstTable::~ConstTable(){
	constantTable.clear();
	instanceFlag=false;
}


ConstTable* ConstTable::getInstance() {
	if(!instanceFlag)
    {
        constTable = new ConstTable();
        instanceFlag = true;
        return constTable;
    }
    else
    {
        return constTable;
    }
}

void ConstTable::insertConst(CONSTVALUE constant) {
	int constantIndex = getConstIndex(constant);
	bool containsConstant = (constantIndex != -1);
		
	if (!containsConstant) {
		constantTable[currentIndex] = constant;
		currentIndex++;
	}
}

CONSTVALUE ConstTable::getConst (CONSTINDEX ind){
	try{
		return constantTable.at(ind);
	}catch(...){
	}
	return "";
}

CONSTINDEX ConstTable::getConstIndex (CONSTVALUE constValue){
	for(unordered_map<CONSTINDEX, CONSTVALUE>::iterator it = constantTable.begin(); it != constantTable.end(); it++) {
		if (constValue == it->second) {
			return it->first; 
		}
	}
	return -1;
}

vector<int> ConstTable::getAllConstValue(){
	vector<int> ans;
	for(unordered_map<CONSTINDEX, CONSTVALUE>::iterator it = constantTable.begin(); it != constantTable.end(); it++) {
		ans.push_back(stoi(it->second));
	}
	return ans;
}


