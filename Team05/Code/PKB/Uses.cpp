#pragma once

#include "Uses.h"

bool Uses::instanceFlag=false;
Uses* Uses::uses=NULL;

//Constructor
Uses::Uses(){
}

Uses::~Uses(){
	usesTable.clear();
	instanceFlag=false;
}

Uses* Uses::getInstance() {
	if(!instanceFlag)
    {
        uses = new Uses();
        instanceFlag = true;
        return uses;
    }
    else
    {
        return uses;
    }
}

Uses* Uses::getInstance(TypeTable* tt, VarTable* vt) {
	if(!instanceFlag)
    {
        uses = new Uses(tt,vt);
        instanceFlag = true;
        return uses;
    }
    else
    {
        return uses;
    }
}


Uses::Uses(TypeTable *tt,VarTable *vt){
	typeTable = tt;
	varTable = vt;
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

vector<int> Uses::getUses(TYPE t, VARNAME v){	//Select a such that Uses(a, "x")	return -1 if doesn't exist
	try{
		VARINDEX index = varTable->getVarIndex(v);
		if(index==-1)
			return vector<VARINDEX> (1,-1);
		vector<VARINDEX> ans;
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
		if(ans.empty())
			return vector<VARINDEX> (1,-1);
		else
			sort(ans.begin(),ans.end());
			return ans;
	}catch(...){
		return vector<VARINDEX> (1,-1);
	}
}

vector<VARINDEX> Uses::getUses(STMTNUM s){	//Select v such that Uses(1, v)	return variable indexes. otherwise return empty vector if doesnt exist
	try{
		vector<VARINDEX> temp = usesTable.at(s);
		if(temp==vector<VARINDEX> (1,-1))
			temp.clear();
		return temp;
	}catch(...){
		vector<VARINDEX> temp;
		return temp;
	}
}

vector<VARINDEX> Uses::getUses(TYPE type){	//Select a such that Uses(a, v); return empty vector if does not exist
	try{
		vector<VARINDEX> ans;
		for(unordered_map<STMTNUM, vector<VARINDEX>>::iterator it = usesTable.begin(); it != usesTable.end(); it++) {
			if(!it->second.empty() && it->second!=vector<int> (1,-1)){
				if(typeTable->isType(type,it->first))
					ans.push_back(it->first);
			}
		}
		if(ans==vector<int> (1,-1))
			ans.clear();
		sort(ans.begin(),ans.end());
		return ans;
	}catch(...){
		vector<VARINDEX> ans;
		return ans;
	}
}

void Uses::setUsesProc(PROCINDEX p, vector<VARINDEX> v) {
	try {
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
	} catch (...){
	}
}

vector<VARINDEX> Uses::getUsesProc(PROCINDEX p) {	
	try {
		return usesProcTable.at(p);
	} catch(...){
		vector<VARINDEX> ans;
		return ans;
	}
}

void Uses::setUses(STMTNUM s, vector<VARINDEX> v) {
	try {
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
	} catch (...){
	}
}