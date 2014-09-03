#pragma once

#include "Modifies.h"

bool Modifies::instanceFlag=false;
Modifies* Modifies::modifies=NULL;

Modifies::Modifies() {

}

	
Modifies::Modifies(TypeTable *tt, VarTable *vt, ProcTable *pt) {
	typeTable = tt;
	varTable = vt;
	procTable = pt;
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

Modifies* Modifies::getInstance(TypeTable* tt, VarTable* vt, ProcTable *pt) {
	if(!instanceFlag) {
        modifies = new Modifies(tt,vt, pt);
        instanceFlag = true;
        return modifies;
    }
    else {
        return modifies;
    }
}

unordered_map<STMTNUM, vector<VARINDEX>> Modifies::getModifiesTable() {
	return modifiesTable;
}

void Modifies::setModifies(STMTNUM s, VARNAME v) {
	try {
		VARINDEX index = varTable->getVarIndex(v);

		vector<VARINDEX> temp (1,index);

		try{
			vector<VARINDEX> temp1 = modifiesTable.at(s);
			temp1.push_back(index);
			modifiesTable.erase(s);
			modifiesTable[s] = temp1;
		} catch(...){
			modifiesTable[s] = temp;
		}
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
		vector<VARINDEX> toReturn;
		for(unordered_map<STMTNUM, vector<VARINDEX>>::iterator it = modifiesTable.begin(); it != modifiesTable.end(); it++) {
			if(!it->second.empty() && it->second!=vector<int> (1,-1)){
				if(typeTable->isType(type,it->first))
					toReturn.push_back(it->first);
			}
		}
		if(toReturn==vector<int> (1,-1))
			toReturn.clear();
		sort(toReturn.begin(),toReturn.end());
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

		for(unordered_map<STMTNUM, vector<VARINDEX>>::iterator it = modifiesTable.begin(); it != modifiesTable.end(); it++) {
			if (typeTable->isType(t, it->first))  {
				vector<VARINDEX> temp = it->second; 
				vector<VARINDEX>::iterator iter;
				for (iter = temp.begin(); iter!=temp.end(); ++iter) {
					if (*iter == varIndex) {
						toReturn.push_back(it->first);
						break;
					}
				}		
			}
		}

		if(toReturn.empty())
			return vector<VARINDEX> (1,-1);
		else
			sort(toReturn.begin(),toReturn.end());
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
		return vector<VARINDEX> (1,-1);
	}
}

void Modifies::setModifiesProc(PROCINDEX p, vector<VARINDEX> v) {
	try {
		try{
			vector<VARINDEX> temp;
			vector<VARINDEX> temp1 = modifiesProcTable.at(p);
			temp.reserve(temp1.size()+v.size());
			temp.insert(temp.end(), v.begin(), v.end());
			temp.insert(temp.end(), temp1.begin(), temp1.end());
			modifiesProcTable.erase(p);
			sort( temp.begin(), temp.end() );
			temp.erase( unique( temp.begin(), temp.end() ), temp.end() );
			modifiesProcTable[p] = temp;
		} catch(...){
			modifiesProcTable[p] = v;
		}
	} catch (...){
	}
}

vector<VARINDEX> Modifies::getModifiesProc(PROCINDEX p) {	
	try {
		return modifiesProcTable.at(p);
	} catch(...){
		vector<VARINDEX> ans;
		return ans;
	}
}

void Modifies::setModifies(STMTNUM s, vector<VARINDEX> v) {
	try {
		try{
			vector<VARINDEX> temp;
			vector<VARINDEX> temp1 = modifiesTable.at(s);
			temp.reserve(temp1.size()+v.size());
			temp.insert(temp.end(), v.begin(), v.end());
			temp.insert(temp.end(), temp1.begin(), temp1.end());
			sort( temp.begin(), temp.end() );
			temp.erase( unique( temp.begin(), temp.end() ), temp.end() );
			modifiesTable[s] = temp;
		} catch(...){
			modifiesTable[s] = v;
		}
	} catch (...){
	}
}