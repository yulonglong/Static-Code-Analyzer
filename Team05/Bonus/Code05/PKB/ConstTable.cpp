#pragma once

#include "ConstTable.h"

bool ConstTable::instanceFlag=false;
ConstTable* ConstTable::constTable=NULL;

// constructor
ConstTable::ConstTable() {
	vector<CONSTVALUE> temp (1,"");
	constantTable = temp;
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
		constantMapTable[constant]=constantTable.size();
		constIndexList.insert(constantTable.size());
		constantTable.push_back(constant);
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
	try{
		return constantMapTable.at(constValue);
	}
	catch(...){
		return -1;
	}
}

set<CONSTINDEX> ConstTable::getAllConstIndex(){
	return constIndexList;
}


