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
	}catch(...){
	}
}

bool Uses::isUses(STMTNUM s, VARNAME v){
	try{
		VARINDEX index = varTable->getVarIndex(v);
		if(index==-1)
			return false;
		vector<VARINDEX> temp = usesTable.at(s);
		vector<VARINDEX>::iterator it = temp.begin();
		for(;it!=temp.end();it++){
			if(index==*it)
				return true;
		}
		return false;
	}catch(...){
		return false;
	}
}

vector<STMTNUM> Uses::getUses(SYNTYPE t, VARNAME v){	//Select a such that Uses(a, "x")	Return an empty vector if not found.
	vector<VARINDEX> ans;
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
						ans.push_back(it->first);
						break;
					}
					else if(typeTable->isType(t,it->first)){
						ans.push_back(it->first);
						break;
					}
				}
			}
		}
		sort(ans.begin(),ans.end());
		return ans;
	}catch(...){
		ans.clear();
		return ans;
	}
}

vector<VARINDEX> Uses::getUses(STMTNUM s){	//Select v such that Uses(1, v)	return variable indexes. otherwise return empty vector if doesnt exist
	vector<VARINDEX> ans;
	try{
		ans = usesTable.at(s);
		return ans;
	}catch(...){
		return ans;
	}
}

vector<VARINDEX> Uses::getUses(SYNTYPE type){	//Select a such that Uses(a, v); return empty vector if does not exist
	vector<VARINDEX> ans;
	try{
		for(unordered_map<STMTNUM, vector<VARINDEX>>::iterator it = usesTable.begin(); it != usesTable.end(); it++) {
			if(!it->second.empty() && it->second!=vector<int> (1,-1)){
				if(typeTable->isType(type,it->first))
					ans.push_back(it->first);
			}
		}
		sort(ans.begin(),ans.end());
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
	} catch(...){
		usesProcTable[p] = v;
	} 
}

vector<VARINDEX> Uses::getUsesProc(PROCINDEX p) {	
	vector<VARINDEX> ans;
	try {
		ans = usesProcTable.at(p);
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

vector<PROCINDEX> Uses::getUsesProcVar(VARNAME v){
	vector<PROCINDEX> ans;
	try {
		VARINDEX varIndex = varTable->getVarIndex(v);
		if (varIndex == -1 ) {
			ans = vector<PROCINDEX> (1,-1);
			return ans;
		}

		for(unordered_map<PROCINDEX, vector<VARINDEX>>::iterator it = usesProcTable.begin(); it != usesProcTable.end(); it++) {
			vector<VARINDEX> temp = it->second; 
			vector<VARINDEX>::iterator iter;
			for (iter = temp.begin(); iter!=temp.end(); iter++) {
				if (*iter == varIndex) {
					ans.push_back(it->first);
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