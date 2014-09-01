#pragma once

#include "ConstTable.h"

bool ConstTable::instanceFlag=false;
ConstTable* ConstTable::constTable=NULL;

// constructor
ConstTable::ConstTable() {
}

ConstTable::~ConstTable(){
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

CONSTINDEX ConstTable::insertConst(CONSTVALUE constant) {
	int constantIndex = getConstIndex(constant);
	bool containsConstant = (constantIndex != -1);
		
	if (!containsConstant) {
		constantTable.emplace_back(constant);
		return constantTable.size()-1;  // return new index for this constant
	} else {
		return constantIndex;
	}
}

CONSTVALUE ConstTable::getConst (CONSTINDEX ind){
	if (ind >= (signed int) constantTable.size()) {
		return "-1";
	}
	return constantTable[ind];
}

CONSTINDEX ConstTable::getConstIndex (CONSTVALUE constValue){
	for(std::vector<CONSTVALUE>::size_type i = 0; i != constantTable.size(); i++) {
		if (constValue == constantTable[i]) {
			return i; 
		}
	}
	return -1;
}

int ConstTable::getNumConst() {
	return constantTable.size();
}

vector<CONSTINDEX> ConstTable::getAllConstIndex() {
	vector<CONSTINDEX> toReturn;
	for (int i=0; i< (signed int) constantTable.size(); i++) {
		toReturn.emplace_back(i);
	}
	return toReturn; 
}


