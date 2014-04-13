#pragma once

#include "Modifies.h"

bool Modifies::instanceFlag=false;
Modifies* Modifies::modifies=NULL;

Modifies::Modifies() {
	vector<STMTNUM> temp;
	temp.assign(1,-1);
	modifiesTable.assign(5, temp);
}

	
Modifies::Modifies(TypeTable *tt, VarTable *vt) {
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


Modifies* Modifies::getInstance() {
	if(!instanceFlag)
    {
        modifies = new Modifies();
        instanceFlag = true;
        return modifies;
    }
    else
    {
        return modifies;
    }
}

Modifies* Modifies::getInstance(TypeTable* tt, VarTable* vt) {
	if(!instanceFlag)
    {
        modifies = new Modifies(tt,vt);
        instanceFlag = true;
        return modifies;
    }
    else
    {
        return modifies;
    }
}

vector<vector<STMTNUM>> Modifies::getModifiesTable() {
	return modifiesTable;

}
void Modifies::setModifies(STMTNUM s, VARNAME v) {
	vector<STMTNUM> temp;
	temp.assign(1,-1);
	if (s >= (signed int) modifiesTable.size()) {
		modifiesTable.resize(s+1, temp);
	}
	
	vector<int> temp1 = modifiesTable.at(s);
	int varIndex = varTable->getVarIndex(v);

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
	cout << "Set modifies(" << s << ", " << v << ")" << endl; 

}


bool Modifies::isModifies(STMTNUM s, VARNAME v) {
	//Select w such that Modifies(1, "y")
	int varIndex = varTable->getVarIndex(v);
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

vector<STMTNUM> Modifies::getModifies(TYPE t) {	
	vector<STMTNUM> toReturn;
	vector<VARINDEX> list; 

	for (vector<STMTNUM>::size_type i = 1; i != modifiesTable.size(); i++) {
		if (t == TypeTable::STMT || typeTable->isType(t,i)) {
			list = modifiesTable.at(i);
			if (list.size() != 0 && list.at(0) != -1) {
				toReturn.push_back(i);
			}
		}
	}

	return toReturn;
}

vector<STMTNUM> Modifies::getModifies(TYPE t, VARNAME v) {	
	// Select a such that Modifies(a, "x")	return -1 if doesn't exist
	// iterate through all stmt numbers, if it is of type TYPE, then get the list, for each of the items check if equals to v, if yes, then add the stmt number to the vector
	vector<STMTNUM> toReturn; 
	int varIndex = varTable->getVarIndex(v);
	
	for (vector<int>::size_type i = 1; i != modifiesTable.size(); i++) {
		if (t == TypeTable::STMT || typeTable->isType(t,i)) {
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

vector<VARINDEX> Modifies::getModifies(STMTNUM stmt) {	
	//Select v such that Modifies(1, v)	return empty vector if doesnt exist };
	vector<VARINDEX> toReturn;
	
	try {
		toReturn = modifiesTable.at(stmt);
	} catch (...) {
	}

	if (toReturn.size() == 1 && toReturn.at(0) == -1) {
		vector<VARINDEX> vec;
		toReturn = vec; 
	}
	/*
	vector<int>::iterator it = varIndexVector.begin();
	for (; it!=varIndexVector.end(); ++it) {
		if (*it == -1) {
			return toReturn; // return empty vector
		}
		toReturn.push_back(varTable->getVarName(*it));

	}
	*/
	return toReturn;
}

