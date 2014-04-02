#pragma once

#include "VarTable.h"


// constructor
VarTable::VarTable() {
}

// If varName is not in the VarTable, inserts varName into the
// VarTable and returns its index. Otherwise, return its index and the table remains unchanged.
INDEX VarTable::insertVar(VARNAME varName) {
	int varIndex = getVarIndex(varName);
	bool containsVar = (varIndex != -1);
		
	if (!containsVar) {
		varTable.emplace_back(varName);
		return varTable.size()-1;  // return new index for this varName
	} else {
		return varIndex;
	}
}

// Returns the name of a variable at VarTable [ind]
// If ‘ind’ is out of range, error (or throw exception)
VARNAME VarTable::getVarName (INDEX ind){
	if (ind >= (signed int) varTable.size()) {
		return "-1";
	}
	return varTable[ind];
}

// If varName is in VarTable, returns its index; otherwise, returns -1 (special value)
INDEX VarTable::getVarIndex (VARNAME varName){
	for(std::vector<VARNAME>::size_type i = 0; i != varTable.size(); i++) {
		if (varName == varTable[i]) {
			return i; 
		}
	}
	return -1;
}

INDEX VarTable::getNumVar() {
	return varTable.size();
}
