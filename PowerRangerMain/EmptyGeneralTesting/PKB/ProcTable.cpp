#pragma once

#include "ProcTable.h"

bool ProcTable::instanceFlag=false;
ProcTable* ProcTable::procTable=NULL;

// constructor
ProcTable::ProcTable() {
}

ProcTable::~ProcTable(){
}


ProcTable* ProcTable::getInstance() {
	if(!instanceFlag)
    {
        procTable = new ProcTable();
        instanceFlag = true;
        return procTable;
    }
    else
    {
        return procTable;
    }
}

// If procName is not in the ProcTable, inserts procName into the
// ProcTable and returns its index. if procName already exists, return its index and the table remains unchanged.
INDEX ProcTable::insertProc(PROCNAME procName) {
	int procIndex = getProcIndex(procName);
	bool containsVariable = (procIndex != -1);
		
	if (!containsVariable) {
		procedureTable.emplace_back(procName);
		return procedureTable.size()-1;  // return new index for this varName
	} else {
		return procIndex;
	}
}

// Returns the name of a proc at ProTable [ind]
// If ‘ind’ is out of range, error (or throw exception)
PROCNAME ProcTable::getProcName (INDEX ind){
	if (ind >= (signed int) procedureTable.size()) {
		return "-1";
	}
	return procedureTable[ind];
}

// If procName is in procTable, returns its index; otherwise, returns -1 (special value)
INDEX ProcTable::getProcIndex (PROCNAME procName){
	for(std::vector<PROCNAME>::size_type i = 0; i != procedureTable.size(); i++) {
		if (procName == procedureTable[i]) {
			return i; 
		}
	}
	return -1;
}

INDEX ProcTable::getNumProcedures() {
	return procedureTable.size();
}
