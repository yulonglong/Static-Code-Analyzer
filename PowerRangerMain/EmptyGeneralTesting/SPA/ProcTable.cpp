#pragma once

#include "ProcTable.h"

class ProcTable {
	vector<PROCNAME> procTable; 

	// constructor
	ProcTable::ProcTable() {
	}

	// If procName is not in the ProcTable, inserts procName into the
	// ProcTable and returns its index. if procName already exists, return its index and the table remains unchanged.
	INDEX ProcTable::insertProc(PROCNAME procName) {
		int procIndex = getProcIndex(procName);
		bool containsVariable = (procIndex != -1);
		
		if (!containsVariable) {
			procTable.emplace_back(procName);
			return procTable.size()-1;  // return new index for this varName
		} else {
			return procIndex;
		}
	}

	// TODO: if ind is out of range, throw error!
	// Returns the name of a proc at ProTable [ind]
	// If ‘ind’ is out of range, error (or throw exception)
	PROCNAME ProcTable::getProcName (INDEX ind){
		if (ind >= procTable.size()) {
			// throw error
		}
		return procTable[ind];
	}

	// If procName is in procTable, returns its index; otherwise, returns -1 (special value)
	INDEX ProcTable::getProcIndex (PROCNAME procName){
		for(std::vector<PROCNAME>::size_type i = 0; i != procTable.size(); i++) {
			if (procName == procTable[i]) {
				return i; 
			}
		}
		return -1;
	}

	INDEX getNumProcedures() {
		return procTable.size();
	}
}