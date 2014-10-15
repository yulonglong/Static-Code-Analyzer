#pragma once

#include "Modifies.h"

bool Modifies::instanceFlag=false;
Modifies* Modifies::modifies=NULL;
	
Modifies::Modifies(TypeTable *tt, VarTable *vt, ProcTable *pt) {
	typeTable = tt;
	varTable = vt;
	procTable = pt;
}


Modifies::~Modifies() {
	modifiesTable.clear();
	modifiesProcTable.clear();
	instanceFlag=false;
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

void Modifies::setModifies(STMTNUM s, VARNAME v) {
	try {
		VARINDEX index = varTable->getVarIndex(v);

		vector<VARINDEX> temp (1,index);

		try{
			vector<VARINDEX> temp1 = modifiesTable.at(s);
			temp1.push_back(index);
			sort( temp1.begin(), temp1.end() );
			temp1.erase( unique( temp1.begin(), temp1.end() ), temp1.end() );
			modifiesTable[s] = temp1;
		} catch(...){
			modifiesTable[s] = temp;
		}
		modifiesList.insert(s);
		modifiedList.insert(index);
	} catch (...){
	}
}

//void Modifies::setModifies(STMTNUM s, VARNAME v) {
//	try {
//		VARINDEX index = varTable->getVarIndex(v);
//		vector<int64_t> placeHolder (0,1);
//		vector<int64_t> temp (0,1);
//		try{
//			temp = modTable.at(s);
//		}catch(...){
//			modTable.resize(s+1,placeHolder);
//		}
//		int location =ceil((double)index/63);
//		int bitPos = index%63;
//
//		if(temp.size()<location)
//			temp.resize(location);
//
//		int64_t bitArray = temp.at(location-1);
//		bitArray = bitArray | (((int64_t)1)<<bitPos);
//
//		temp[location-1]=bitArray;
//		modTable[s]=temp;
//
//		modifiesList.push_back(s);
//		sort( modifiesList.begin(), modifiesList.end() );
//		modifiesList.erase( unique( modifiesList.begin(), modifiesList.end() ), modifiesList.end() );
//	}catch(...){
//	}
//
//	try {
//		VARINDEX index = varTable->getVarIndex(v);
//		vector<int64_t> placeHolder (0,1);
//		vector<int64_t> temp (0,1);
//		try{
//			temp = modVarTable.at(index);
//		}catch(...){
//			modVarTable.resize(index+1,placeHolder);
//		}
//		int location =ceil((double)s/63);
//		int bitPos = s%63;
//
//		if(temp.size()<location)
//			temp.resize(location);
//
//		int64_t bitArray = temp.at(location-1);
//		bitArray = bitArray | (((int64_t)1)<<bitPos);
//
//		temp[location-1]=bitArray;
//		modVarTable[index]=temp;
//
//		modifiedList.push_back(index);
//		sort( modifiedList.begin(), modifiedList.end() );
//		modifiedList.erase( unique( modifiedList.begin(), modifiedList.end() ), modifiedList.end() );
//	}catch(...){
//	}
//}
bool Modifies::isModifies(STMTNUM s, VARNAME v) {
	//Select w such that Modifies(1, "y")
	try {
		VARINDEX index = varTable->getVarIndex(v);
		if(isModifies(s,index))
			return true;
	} catch (...){
	}
	return false;
}


//bool Modifies::isModifies(STMTNUM s, VARINDEX index){
//	//Select w such that Modifies(1, "y")
//	try {
//		if (index == -1) {
//			return false;
//		}
//
//		vector<int64_t> temp=modTable.at(s);
//		int location =ceil((double)index/63);
//		int bitPos = index%63;
//		if(temp.size()<location)
//			return false;
//
//		int64_t bitArray = temp.at(location-1);
//		if((bitArray & ((int64_t)1<<bitPos))>0)
//			return true;
//	} catch (...){
//		return false;
//	}
//	return false;
//}

bool Modifies::isModifies(STMTNUM s, VARINDEX index){
	//Select w such that Modifies(1, "y")
	try {
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

//vector<VARINDEX> Modifies::getModified(STMTNUM snum){
//	vector<STMTNUM> ans;
//	try{
//		vector<int64_t> temp=modTable.at(snum);
//
//		for(size_t s = 0;s<temp.size();s++){
//			int64_t bitArray = temp.at(s);
//			while(bitArray>0){
//				int64_t bit = bitArray & -bitArray;
//				bitArray -= bit;
//				int number = log((double)bit)/log(2.0) + s*63;
//				ans.push_back(number);
//			}
//		}
//		return ans;
//	}
//	catch(...){
//		ans.clear();
//		return ans;
//	}
//}

set<VARINDEX> Modifies::getModifies(VARINDEX i){
	set<STMTNUM> ans;
	try{
		vector<int64_t> temp=modVarTable.at(i);

		for(size_t s = 0;s<temp.size();s++){
			int64_t bitArray = temp.at(s);
			while(bitArray>0){
				int64_t bit = bitArray & -bitArray;
				bitArray -= bit;
				int number = log((double)bit)/log(2.0) + s*63;
				ans.insert(number);
			}
		}
		return ans;
	}
	catch(...){
		ans.clear();
		return ans;
	}
}

set<VARINDEX> Modifies::getModified(STMTNUM s){
	set<STMTNUM> ans;
	try{
		vector<STMTNUM> tempVec = modifiesTable.at(s);
		for(vector<STMTNUM>::iterator it = tempVec.begin(); it !=tempVec.end();it++){
			ans.insert(*it);
		}
		return ans;
	} catch (...){
		return ans;
	}
}

set<VARINDEX> Modifies::getAllModified(){
	return modifiedList;
}

set<STMTNUM> Modifies::getAllModifies(){
	return modifiesList;
}

bool Modifies::isModifiesProc(PROCINDEX procIndex, VARINDEX index){
	try {
		if (index == -1 || procIndex == -1) {
			return false;
		}
		vector<VARINDEX> temp = modifiesProcTable.at(procIndex);
		vector<VARINDEX>::iterator it = temp.begin();
		for (; it!=temp.end(); it++){
			if (index == *it) {
				return true;
			}
		}
	} catch (...){
	}
	return false;
}

set<VARINDEX> Modifies::getModifiedProc(PROCINDEX s){
	set<STMTNUM> ans;
	try{
		vector<STMTNUM> tempVec = modifiesProcTable.at(s);
		for(vector<STMTNUM>::iterator it = tempVec.begin(); it !=tempVec.end();it++){
			ans.insert(*it);
		}
		return ans;
	} catch (...){
		return ans;
	}
}

set<VARINDEX> Modifies::getAllModifiedProc(){
	return modifiedProcList;
}

set<PROCINDEX> Modifies::getAllModifiesProc(){
	return modifiesProcList;
}

set<STMTNUM> Modifies::getModifies(SYNTYPE type) {	
	set<STMTNUM> ans;
	try {
		for(unordered_map<STMTNUM, vector<VARINDEX>>::iterator it = modifiesTable.begin(); it != modifiesTable.end(); it++) {
			if(!it->second.empty() && it->second!=vector<int> (1,-1)){
				if(typeTable->isType(type,it->first))
					ans.insert(it->first);
			}
		}
		return ans;
	} catch(...){
		ans.clear();
	}
	return ans;
}

set<STMTNUM> Modifies::getModifies(SYNTYPE t, VARNAME v) {	
	// Select a such that Modifies(a, "x")	return -1 if doesn't exist
	// iterate through all stmt numbers, if it is of type SYNTYPE, then get the list, for each of the items check if equals to v, if yes, then add the stmt number to the vector
	set<STMTNUM> ans;
	try {
		VARINDEX varIndex = varTable->getVarIndex(v);
		if (varIndex == -1) {
			return ans;
		}

		for(unordered_map<STMTNUM, vector<VARINDEX>>::iterator it = modifiesTable.begin(); it != modifiesTable.end(); it++) {
			if (typeTable->isType(t, it->first))  {
				vector<VARINDEX> temp = it->second; 
				vector<VARINDEX>::iterator iter;
				for (iter = temp.begin(); iter!=temp.end(); ++iter) {
					if (*iter == varIndex) {
						ans.insert(it->first);
						break;
					}
				}		
			}
		}
		return ans;
	} catch(...){
		ans.clear();
	}
	return ans;
}

void Modifies::setModifiesProc(PROCINDEX p, set<VARINDEX> v) {
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

		modifiesProcList.insert(p);
		for(set<VARINDEX>::iterator it = v.begin();it!=v.end();it++)
			modifiedProcList.insert(*it);

	} catch(...){
		vector<VARINDEX> temp;
		temp.insert(temp.end(), v.begin(), v.end());
		modifiesProcTable[p] = temp;
	}
}

set<VARINDEX> Modifies::getModifiesProc(PROCINDEX p) {	
	set<VARINDEX> ans;
	try {
		vector<STMTNUM> tempVec = modifiesProcTable.at(p);
		for(vector<STMTNUM>::iterator it = tempVec.begin(); it !=tempVec.end();it++){
			ans.insert(*it);
		}
		return ans;
	} catch(...){
		ans.clear();
	}
	return ans;
}

void Modifies::setModifies(STMTNUM s, set<VARINDEX> v) {
	try{
		vector<VARINDEX> temp;
		vector<VARINDEX> temp1 = modifiesTable.at(s);
		temp.reserve(temp1.size()+v.size());
		temp.insert(temp.end(), v.begin(), v.end());
		temp.insert(temp.end(), temp1.begin(), temp1.end());
		sort( temp.begin(), temp.end() );
		temp.erase( unique( temp.begin(), temp.end() ), temp.end() );
		modifiesTable[s] = temp;

		modifiesList.insert(s);
		for(set<VARINDEX>::iterator it = v.begin();it!=v.end();it++)
			modifiedList.insert(*it);
	} catch(...){
		vector<VARINDEX> temp;
		temp.insert(temp.end(), v.begin(), v.end());
		modifiesTable[s] = temp;
	}
}

set<PROCINDEX> Modifies::getModifiesProcVar(VARNAME v){
	set<PROCINDEX> ans;
	try {
		VARINDEX varIndex = varTable->getVarIndex(v);
		if (varIndex == -1 ) {
			return ans;
		}

		for(unordered_map<PROCINDEX, vector<VARINDEX>>::iterator it = modifiesProcTable.begin(); it != modifiesProcTable.end(); it++) {
			vector<VARINDEX> temp = it->second; 
			vector<VARINDEX>::iterator iter;
			for (iter = temp.begin(); iter!=temp.end(); iter++) {
				if (*iter == varIndex) {
					ans.insert(it->first);
					break;
				}
			}		
		}
		return ans;
	} catch (...){
		ans.clear();
	}
	return ans;
}

bool Modifies::isModifiesProc(PROCNAME p, VARNAME v){
	try {
		VARINDEX index = varTable->getVarIndex(v);
		PROCINDEX procIndex = procTable->getProcIndex(p);
		if (index == -1 || procIndex == -1) {
			return false;
		}
		vector<VARINDEX> temp = modifiesProcTable.at(procIndex);
		vector<VARINDEX>::iterator it = temp.begin();
		for (; it!=temp.end(); it++){
			if (index == *it) {
				return true;
			}
		}
	} catch (...){
	}
	return false;
}

void Modifies::printModifiesTable() {
	cout<< "Modifies Table" << endl;
	for(unordered_map<STMTNUM, vector<VARINDEX>>::iterator it = modifiesTable.begin(); it != modifiesTable.end(); it++) {
		cout<< it->first << " modifies ";
		vector<VARINDEX> temp = it->second; 
		vector<VARINDEX>::iterator iter;
		for (iter = temp.begin(); iter!=temp.end(); iter++) {
			string name = varTable->getVarName(*iter);
			cout<< name<< ",";
		}		
		cout<<endl;
	}
}