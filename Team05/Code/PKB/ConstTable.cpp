#pragma once

#include "ConstTable.h"

bool ConstTable::instanceFlag=false;
ConstTable* ConstTable::constTable=NULL;

// constructor
ConstTable::ConstTable() {
}

ConstTable::~ConstTable(){
	constantTable.clear();
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
		constantTable.emplace_back(constant);
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


