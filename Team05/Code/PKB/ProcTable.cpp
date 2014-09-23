#pragma once

#include "ProcTable.h"

bool ProcTable::instanceFlag=false;
ProcTable* ProcTable::procTable=NULL;
PROCINDEX ProcTable::currentIndex = 0;

// constructor
ProcTable::ProcTable() {
	currentIndex = 0;
}

ProcTable::~ProcTable(){
	procedureTable.clear();
	instanceFlag=false;
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
// ProcTable. if procName already exists, the table remains unchanged.
void ProcTable::insertProc(PROCNAME procName) {
	PROCINDEX procIndex = getProcIndex(procName);
	bool containsVariable = (procIndex != -1);
		
	if (!containsVariable) {
		procedureTable[currentIndex] = procName;
		currentIndex++;
	}
}

// Returns the name of a proc at ProTable [ind]
// If ‘ind’ is out of range, error (or throw exception)
PROCNAME ProcTable::getProcName (PROCINDEX ind){
	try{
		return procedureTable.at(ind);
	}catch(...){
	}
	return "";
}

// If procName is in procTable, returns its index; otherwise, returns -1 (special value)
PROCINDEX ProcTable::getProcIndex (PROCNAME procName){
	for(unordered_map<PROCINDEX, PROCNAME>::iterator it = procedureTable.begin(); it != procedureTable.end(); it++) {
		if (procName == it->second) {
			return it->first; 
		}
	}
	return -1;
}