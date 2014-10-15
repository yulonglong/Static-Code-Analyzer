#pragma once

#include "VarTable.h"

bool VarTable::instanceFlag=false;
VarTable* VarTable::varTable=NULL;

// constructor
VarTable::VarTable() {
	vector<VARNAME> temp (1,"");
	variableTable = temp;
}

VarTable::~VarTable(){
	variableTable.clear();
	variableMapTable.clear();
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
		variableMapTable[varName]=variableTable.size();
		varIndexList.insert(variableTable.size());
		variableTable.push_back(varName);
	}
}

// Returns the name of a variable at VarTable [ind]
// If ‘ind’ is out of range, return an empty string
VARNAME VarTable::getVarName (VARINDEX i){
	try{
		size_t index = i;
		if(index>=variableTable.size())
			return "";
		return variableTable.at(index);
	}catch(...){
		return "";
	}
}

// If varName is in VarTable, returns its index; otherwise, returns -1 (special value)
VARINDEX VarTable::getVarIndex (VARNAME varName){
	try{
		return variableMapTable.at(varName);
	}
	catch(...){
		return -1;
	}
}

int VarTable::getNumVar() {
	return variableTable.size();
}

set<VARINDEX> VarTable::getAllVarIndex() {
	return varIndexList;
}