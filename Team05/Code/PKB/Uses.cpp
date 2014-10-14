#pragma once

#include "Uses.h"

bool Uses::instanceFlag=false;
Uses* Uses::uses=NULL;

//Constructor
Uses::Uses(TypeTable *tt,VarTable *vt, ProcTable *pt){
	typeTable = tt;
	varTable = vt;
	procTable = pt;
}

Uses::~Uses(){
	usesTable.clear();
	instanceFlag=false;
}

Uses* Uses::getInstance(TypeTable* tt, VarTable* vt, ProcTable* pt) {
	if(!instanceFlag)
    {
        uses = new Uses(tt,vt,pt);
        instanceFlag = true;
        return uses;
    }
    else
    {
        return uses;
    }
}

void Uses::setUses(STMTNUM s,VARNAME v){
	try{
		VARINDEX index = varTable->getVarIndex(v);

		vector<VARINDEX> temp (1,index);

		try{
			vector<VARINDEX> temp1 = usesTable.at(s);
			temp1.push_back(index);
			sort( temp1.begin(), temp1.end() );
			temp1.erase( unique( temp1.begin(), temp1.end() ), temp1.end() );
			usesTable[s] = temp1;
		} catch(...){
			usesTable[s] = temp;
		}

		usesList.insert(s);

		usedList.insert(index);

	}catch(...){
	}
}


//void Uses::setUses(STMTNUM s, VARNAME v) {
//	try {
//		VARINDEX index = varTable->getVarIndex(v);
//		vector<int64_t> placeHolder (0,1);
//		vector<int64_t> temp (0,1);
//		try{
//			temp = usesBitTable.at(s);
//		}catch(...){
//			usesBitTable.resize(s+1,placeHolder);
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
//		usesBitTable[s]=temp;
//
//		usesList.push_back(s);
//		sort( usesList.begin(), usesList.end() );
//		usesList.erase( unique( usesList.begin(), usesList.end() ), usesList.end() );
//
//	}catch(...){
//	}
//
//	try {
//		VARINDEX index = varTable->getVarIndex(v);
//		vector<int64_t> placeHolder (0,1);
//		vector<int64_t> temp (0,1);
//		try{
//			temp = usesBitVarTable.at(index);
//		}catch(...){
//			usesBitVarTable.resize(index+1,placeHolder);
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
//		usesBitVarTable[index]=temp;
//
//		usedList.push_back(index);
//		sort( usedList.begin(), usedList.end() );
//		usedList.erase( unique( usedList.begin(), usedList.end() ), usedList.end() );
//	}catch(...){
//	}
//}



bool Uses::isUses(STMTNUM s, VARNAME v){
	try{
		VARINDEX index = varTable->getVarIndex(v);
		if(isUses(s,index))
			return true;
	}catch(...){
		return false;
	}
}

//bool Uses::isUses(STMTNUM s, VARINDEX index){
//	try {
//		if (index == -1) {
//			return false;
//		}
//
//		vector<int64_t> temp=usesBitTable.at(s);
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

bool Uses::isUses(STMTNUM s, VARINDEX index){
	//Select w such that Modifies(1, "y")
	try {
		if (index == -1) {
			return false;
		}
		vector<VARINDEX> temp = usesTable.at(s);
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

//vector<VARINDEX> Uses::getUsed(STMTNUM snum){
//	vector<STMTNUM> ans;
//	try{
//		vector<int64_t> temp=usesBitTable.at(snum);
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



set<VARINDEX> Uses::getUses(VARINDEX i){
	set<STMTNUM> ans;
	try{
		vector<int64_t> temp=usesBitVarTable.at(i);

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

set<VARINDEX> Uses::getUsed(STMTNUM s){
	set<STMTNUM> ans;
	try{
		vector<STMTNUM> tempVec = usesTable.at(s);
		for(vector<STMTNUM>::iterator it = tempVec.begin(); it !=tempVec.end();it++){
			ans.insert(*it);
		}
		return ans;
	} catch (...){
		return ans;
	}
}

set<VARINDEX> Uses::getAllUsed(){
	return usedList;
}

set<STMTNUM> Uses::getAllUses(){
	return usesList;
}

bool Uses::isUsesProc(PROCINDEX procIndex, VARINDEX index){
	try {
		if (index == -1 || procIndex == -1) {
			return false;
		}
		vector<VARINDEX> temp = usesProcTable.at(procIndex);
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

set<VARINDEX> Uses::getUsedProc(PROCINDEX s){
	set<STMTNUM> ans;
	try{
		vector<STMTNUM> tempVec = usesProcTable.at(s);
		for(vector<STMTNUM>::iterator it = tempVec.begin(); it !=tempVec.end();it++){
			ans.insert(*it);
		}
		return ans;
	} catch (...){
		return ans;
	}
}

set<VARINDEX> Uses::getAllUsedProc(){
	return usedProcList;
}

set<PROCINDEX> Uses::getAllUsesProc(){
	return usesProcList;
}



set<STMTNUM> Uses::getUses(SYNTYPE t, VARNAME v){	//Select a such that Uses(a, "x")	Return an empty vector if not found.
	set<VARINDEX> ans;
	try{
		VARINDEX index = varTable->getVarIndex(v);
		if(index==-1){
			return ans;
		}
		for(unordered_map<STMTNUM, vector<VARINDEX>>::iterator it = usesTable.begin(); it != usesTable.end(); it++) {
			vector<VARINDEX> temp = it->second;
			vector<VARINDEX>::iterator iter = temp.begin();
			for(;iter!=temp.end();++iter){
				if(*iter==index){
					if(t==TypeTable::STMT){
						ans.insert(it->first);
						break;
					}
					else if(typeTable->isType(t,it->first)){
						ans.insert(it->first);
						break;
					}
				}
			}
		}
		return ans;
	}catch(...){
		ans.clear();
		return ans;
	}
}

//vector<VARINDEX> Uses::getUses(STMTNUM s){	//Select v such that Uses(1, v)	return variable indexes. otherwise return empty vector if doesnt exist
//	vector<VARINDEX> ans;
//	try{
//		ans = usesTable.at(s);
//		return ans;
//	}catch(...){
//		return ans;
//	}
//}

set<VARINDEX> Uses::getUses(SYNTYPE type){	//Select a such that Uses(a, v); return empty vector if does not exist
	set<VARINDEX> ans;
	try{
		for(unordered_map<STMTNUM, vector<VARINDEX>>::iterator it = usesTable.begin(); it != usesTable.end(); it++) {
			if(!it->second.empty() && it->second!=vector<int> (1,-1)){
				if(typeTable->isType(type,it->first))
					ans.insert(it->first);
			}
		}
		return ans;
	}catch(...){
		ans.clear();
	}
	return ans;
}

void Uses::setUsesProc(PROCINDEX p, vector<VARINDEX> v) {
	try{
		vector<VARINDEX> temp;
		vector<VARINDEX> temp1 = usesProcTable.at(p);
		temp.reserve(temp1.size()+v.size());
		temp.insert(temp.end(), v.begin(), v.end());
		temp.insert(temp.end(), temp1.begin(), temp1.end());
		sort( temp.begin(), temp.end() );
		temp.erase( unique( temp.begin(), temp.end() ), temp.end() );
		usesProcTable[p] = temp;

		usesProcList.insert(p);
		for(vector<VARINDEX>::iterator it = v.begin();it!=v.end();it++)
			usedProcList.insert(*it);
	} catch(...){
		usesProcTable[p] = v;
	} 
}

set<VARINDEX> Uses::getUsesProc(PROCINDEX p) {	
	set<VARINDEX> ans;
	try {
		vector<STMTNUM> tempVec = usesProcTable.at(p);
		for(vector<STMTNUM>::iterator it = tempVec.begin(); it !=tempVec.end();it++){
			ans.insert(*it);
		}
		return ans;
	} catch(...){
		return ans;
	}
}

void Uses::setUses(STMTNUM s, vector<VARINDEX> v) {
	try{
		vector<VARINDEX> temp;
		vector<VARINDEX> temp1 = usesTable.at(s);
		temp.reserve(temp1.size()+v.size());
		temp.insert(temp.end(), v.begin(), v.end());
		temp.insert(temp.end(), temp1.begin(), temp1.end());
		sort( temp.begin(), temp.end() );
		temp.erase( unique( temp.begin(), temp.end() ), temp.end() );
		usesTable[s] = temp;
	} catch(...){
		usesTable[s] = v;
	}
}

set<PROCINDEX> Uses::getUsesProcVar(VARNAME v){
	set<PROCINDEX> ans;
	try {
		VARINDEX varIndex = varTable->getVarIndex(v);
		if (varIndex == -1 ) {
			return ans;
		}

		for(unordered_map<PROCINDEX, vector<VARINDEX>>::iterator it = usesProcTable.begin(); it != usesProcTable.end(); it++) {
			vector<VARINDEX> temp = it->second; 
			vector<VARINDEX>::iterator iter;
			for (iter = temp.begin(); iter!=temp.end(); iter++) {
				if (*iter == varIndex) {
					ans.insert(it->first);
					break;
				}
			}		
		}
	} catch (...){
		ans.clear();
	}
	return ans;
}

bool Uses::isUsesProc(PROCNAME p, VARNAME v){
	try {
		VARINDEX index = varTable->getVarIndex(v);
		PROCINDEX procIndex = procTable->getProcIndex(p);
		if (index == -1 || procIndex == -1) {
			return false;
		}
		vector<VARINDEX> temp = usesProcTable.at(procIndex);
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

void Uses::printUsesTable() {
	cout<< "Uses Table" << endl;
	for(unordered_map<STMTNUM, vector<VARINDEX>>::iterator it = usesTable.begin(); it != usesTable.end(); it++) {
		cout<< it->first << " uses ";
		vector<VARINDEX> temp = it->second; 
		vector<VARINDEX>::iterator iter;
		for (iter = temp.begin(); iter!=temp.end(); iter++) {
			string name = varTable->getVarName(*iter);
			cout<< name<< ",";
		}		
		cout<<endl;
	}
}