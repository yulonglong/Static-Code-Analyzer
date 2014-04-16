#pragma once

#include "Modifies.h"

bool Modifies::instanceFlag=false;
Modifies* Modifies::modifies=NULL;

Modifies::Modifies() {
}

	
Modifies::Modifies(TypeTable *tt, VarTable *vt) {
	typeTable = tt;
	varTable = vt;
}

//TODO: delete
Modifies::~Modifies() {
	modifiesTable.clear();
	instanceFlag=false;
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
	if(!instanceFlag) {
        modifies = new Modifies(tt,vt);
        instanceFlag = true;
        return modifies;
    }
    else {
        return modifies;
    }
}

map<STMTNUM,vector<VARINDEX>> Modifies::getModifiesTable() {
	return modifiesTable;

}

void Modifies::setModifies(STMTNUM s, VARNAME v) {
	try {
		VARINDEX index = varTable->getVarIndex(v);
		vector<VARINDEX> existing;

		try {
			existing = modifiesTable.at(s);
			modifiesTable.erase(s);
		} catch (...){
		}

		existing.push_back(index);
		modifiesTable.insert(pair<STMTNUM,vector<VARINDEX>>(s,existing));
		cout<<"setModifies("<<s<<","<<v<<")"<<endl;

	} catch (...){
	}

}


bool Modifies::isModifies(STMTNUM s, VARNAME v) {
	//Select w such that Modifies(1, "y")
	try {
		VARINDEX index = varTable->getVarIndex(v);
		if (index == -1) {
			return false;
		}
		vector<VARINDEX> temp = modifiesTable.at(s);
		vector<VARINDEX>::iterator it = temp.begin();
		for (; it!=temp.end(); it++){
			if (index == *it) {
				return true;
			}
		}
	} catch (...){
		return false;
	}
	return false;
}

vector<STMTNUM> Modifies::getModifies(TYPE type) {	
	try {
		vector<STMTNUM> toReturn;
		for (map<STMTNUM,vector<VARINDEX>>::iterator i = modifiesTable.begin(); i != modifiesTable.end(); i++){
			if (!i->second.empty()) {
				if (typeTable->isType(type, i->first)) {
					toReturn.push_back(i->first);
				}
			}
		}
		return toReturn;
	} catch(...){
		vector<STMTNUM> toReturn;
		return toReturn;
	}
}

vector<STMTNUM> Modifies::getModifies(TYPE t, VARNAME v) {	
	// Select a such that Modifies(a, "x")	return -1 if doesn't exist
	// iterate through all stmt numbers, if it is of type TYPE, then get the list, for each of the items check if equals to v, if yes, then add the stmt number to the vector
	try {
		VARINDEX varIndex = varTable->getVarIndex(v);
		if (varIndex == -1) {
			return vector<VARINDEX> (1,-1);
		}
		vector<STMTNUM> toReturn;

		for (map<STMTNUM,vector<VARINDEX>>::iterator i = modifiesTable.begin(); i != modifiesTable.end(); i++) {
			if (typeTable->isType(t, i->first))  {
				vector<VARINDEX> temp = i->second;
				vector<VARINDEX>::iterator it;
				for (it = temp.begin(); it!=temp.end(); ++it) {
					if (*it == varIndex) {
						toReturn.push_back(i->first);
					}
				}		
			}
		}

		if(toReturn.empty())
			return vector<VARINDEX> (1,-1);
		else
			return toReturn;
	} catch(...){
		return vector<VARINDEX> (1,-1);
	}

}

vector<VARINDEX> Modifies::getModifies(STMTNUM stmt) {	
	//Select v such that Modifies(1, v)	return empty vector if doesnt exist };
	try {
		vector<VARINDEX> toReturn = modifiesTable.at(stmt);
		return toReturn;
	} catch(...) {
		vector<VARINDEX> toReturn;
		return toReturn;
	}
}

