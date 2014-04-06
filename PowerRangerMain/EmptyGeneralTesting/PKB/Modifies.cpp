#pragma once

#include "Modifies.h"

Modifies::Modifies() {
	vector<STMTNUM> temp;
	temp.assign(1,-1);
	modifiesTable.assign(5, temp);
}

	
Modifies::Modifies(TypeTable tt, VarTable vt) {
	typeTable = tt;
	varTable = vt;
	vector<STMTNUM> temp;
	temp.assign(1,-1);
	modifiesTable.assign(5, temp);
}

Modifies::~Modifies() {
	vector<vector<STMTNUM>> v;
	v.swap(modifiesTable);
}

/*
vector<vector<STMTNUM>> Modifies::getModifiesTable() {
	return modifiesTable;
}

TypeTable Modifies::getTypeTable() {
	return typeTable;
}

VarTable Modifies::getVarTable() {
	return varTable;
}
*/

void Modifies::setModifies(STMTNUM s, VARNAME v) {
	vector<STMTNUM> temp;
	temp.assign(1,-1);
	if (s >= (signed int) modifiesTable.size()) {
		modifiesTable.resize(s+1, temp);
	}
	
	vector<int> temp1 = modifiesTable.at(s);
	int varIndex = varTable.getVarIndex(v);

	if (temp1.at(0) == -1) { // may throw exception
		temp1[0] = varIndex;
	} else {
		for(std::vector<int>::iterator it = temp1.begin(); it != temp1.end(); ++it) {
			if (*it == varIndex) {
				return;
			}
		}
		temp1.push_back(varIndex);
	}
	modifiesTable[s] = temp1;

}

// TODO: Implementation
bool Modifies::isModifies(TYPE s, TYPE t) {	
	//Select s such that Modifies(a, v) parameter order: selected type, first token, second token (first parameter can be w or a or s)
	
	return true;
}

bool Modifies::isModifies(STMTNUM s, VARNAME v) {
	//Select w such that Modifies(1, "y")
	int varIndex = varTable.getVarIndex(v);
	vector<int> modifies; 

	if (varIndex == -1) {
		return false;
	}

	try {
		modifies = modifiesTable.at(s);
	} catch (...) {
		return false;
	}

	for(vector<int>::iterator it = modifies.begin(); it != modifies.end(); ++it) {
		if (*it == varIndex) {
			return true;
		}
	}

	return false;
}

vector<STMTNUM> Modifies::getModifies(TYPE t, VARNAME v) {	
	// Select a such that Modifies(a, "x")	return -1 if doesn't exist
	// iterate through all stmt numbers, if it is of type TYPE, then get the list, for each of the items check if equals to v, if yes, then add the stmt number to the vector
	vector<STMTNUM> toReturn; 
	int varIndex = varTable.getVarIndex(v);
	
	for (vector<int>::size_type i = 1; i != modifiesTable.size(); i++) {
		if (t == TypeTable::STMT || typeTable.getType(i) == t) {
			vector<int> list = modifiesTable.at(i); 
			vector<int>::iterator it = list.begin();
			for (; it!=list.end(); ++it) {
				if (*it == varIndex) {
					toReturn.push_back(i);
				}
			}
		}
	}
	return toReturn;
}


vector<VARNAME> Modifies::getModifies(STMTNUM stmt) {	
	//Select v such that Modifies(1, v)	return empty vector if doesnt exist };
	vector<VARNAME> v;
	vector<int> varIndexVector; 

	try {
		varIndexVector = modifiesTable.at(stmt);
	} catch (...) {
		return v; 	// return empty vector
	}

	vector<int>::iterator it = varIndexVector.begin();
	for (; it!=varIndexVector.end(); ++it) {
		if (*it == -1) {
			return v; // return empty vector
		}
		v.push_back(varTable.getVarName(*it));

	}

	return v;
}

