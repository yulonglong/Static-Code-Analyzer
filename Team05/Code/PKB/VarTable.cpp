#pragma once

#include "VarTable.h"

bool VarTable::instanceFlag=false;
VarTable* VarTable::varTable=NULL;
VARINDEX VarTable::currentIndex = 0;

// constructor
VarTable::VarTable() {
	currentIndex = 0;
}

VarTable::~VarTable(){
	variableTable.clear();
	instanceFlag=false;
}


VarTable* VarTable::getInstance() {
	if(!instanceFlag)
    {
        varTable = new VarTable();
        instanceFlag = true;
        return varTable;
    }
    else
    {
        return varTable;
    }
}

// If varName is not in the VarTable, inserts varName into the
// VarTable. Otherwise, the table remains unchanged.
void VarTable::insertVar(VARNAME varName) {
	int varIndex = getVarIndex(varName);
	bool containsVar = (varIndex != -1);
		
	if (!containsVar) {
		variableTable[currentIndex] = varName;
		currentIndex++;
	}
}

// Returns the name of a variable at VarTable [ind]
// If ‘ind’ is out of range, return an empty string
VARNAME VarTable::getVarName (VARINDEX ind){
	try{
		return variableTable.at(ind);
	}catch(...){
	}
	return "";
}

// If varName is in VarTable, returns its index; otherwise, returns -1 (special value)
VARINDEX VarTable::getVarIndex (VARNAME varName){
	for(unordered_map<VARINDEX, VARNAME>::iterator it = variableTable.begin(); it != variableTable.end(); it++) {
		if (varName == it->second) {
			return it->first; 
		}
	}
	return -1;
}
