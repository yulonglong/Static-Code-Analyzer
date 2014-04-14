#pragma once

#include "VarTable.h"

bool VarTable::instanceFlag=false;
VarTable* VarTable::varTable=NULL;

// constructor
VarTable::VarTable() {
}

VarTable::~VarTable(){
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
// VarTable and returns its index. Otherwise, return its index and the table remains unchanged.
VARINDEX VarTable::insertVar(VARNAME varName) {
	int varIndex = getVarIndex(varName);
	bool containsVar = (varIndex != -1);
		
	if (!containsVar) {
		variableTable.emplace_back(varName);
		return variableTable.size()-1;  // return new index for this varName
	} else {
		return varIndex;
	}
}

// Returns the name of a variable at VarTable [ind]
// If ‘ind’ is out of range, error (or throw exception)
VARNAME VarTable::getVarName (VARINDEX ind){
	if (ind >= (signed int) variableTable.size()) {
		return "-1";
	}
	return variableTable[ind];
}

// If varName is in VarTable, returns its index; otherwise, returns -1 (special value)
VARINDEX VarTable::getVarIndex (VARNAME varName){
	for(std::vector<VARNAME>::size_type i = 0; i != variableTable.size(); i++) {
		if (varName == variableTable[i]) {
			return i; 
		}
	}
	return -1;
}

int VarTable::getNumVar() {
	return variableTable.size();
}
