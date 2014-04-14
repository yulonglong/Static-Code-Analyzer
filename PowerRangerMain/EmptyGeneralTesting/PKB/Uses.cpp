#pragma once

#include "Uses.h"

bool Uses::instanceFlag=false;
Uses* Uses::uses=NULL;

//Constructor
Uses::Uses(){
	vector<STMTNUM> temp (1,-1);
	usesTable.assign(5, temp);
}

Uses::~Uses(){
	usesTable.clear();
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
	vector<STMTNUM> temp (1,-1);
	usesTable.assign(5, temp);
}

void Uses::setUses(STMTNUM s,VARNAME v){
	try{
		VARINDEX index = varTable->getVarIndex(v);
		vector<STMTNUM> temp (1,-1);
		if (s >= (signed int) usesTable.size()) {
			usesTable.resize(s+1, temp);
		}
		vector<STMTNUM> temp1 = usesTable[s];
		if(temp1==temp)
			temp1.clear();
		temp1.push_back(index);
		usesTable[s] = temp1;
	}catch(...){
	}
}

bool Uses::isUses(STMTNUM s, VARNAME v){
	try{
		VARINDEX index = varTable->getVarIndex(v);
		vector<STMTNUM> temp = usesTable[s];
		vector<STMTNUM>::iterator it = temp.begin();
		for(;it!=temp.end();++it){
			if(index==*it)
				return true;
		}
		return false;
	}catch(...){
		return false;
	}
}

vector<int> Uses::getUses(TypeTable::SynType t, VARNAME v){	//Select a such that Uses(a, "x")	return -1 if doesn't exist
	try{
		VARINDEX index = varTable->getVarIndex(v);
		vector<STMTNUM> ans;
		for(size_t i=0;i<usesTable.size();i++){
			vector<STMTNUM> temp = usesTable[i];
			vector<STMTNUM>::iterator it = temp.begin();
			for(;it!=temp.end();++it){
				if(*it==index){
					if(t==TypeTable::STMT){
						ans.push_back(i);
					}
					else if(typeTable->isType(t,i)){
						ans.push_back(i);
					}
				}
			}
		}		
		if(ans.empty())
			return vector<int> (1,-1);
		else
			return ans;
	}catch(...){
		return vector<int> (1,-1);
	}
}

vector<VARINDEX> Uses::getUses(STMTNUM s){	//Select v such that Uses(1, v)	return variable indexes. otherwise return empty vector if doesnt exist
	try{
		vector<VARINDEX> temp = usesTable[s];
		if(temp==vector<int> (1,-1))
			temp.clear();
		return temp;
	}catch(...){
		vector<VARINDEX> temp;
		return temp;
	}
}

vector<VARINDEX> Uses::getUses(TypeTable::SynType type){	//Select a such that Uses(a, v); return empty vector if does not exist
	try{
		vector<VARINDEX> ans;
		for(size_t i=0;i<usesTable.size();i++){
			if(!usesTable[i].empty() && usesTable[i]!=vector<int> (1,-1)){
				if(typeTable->isType(type,i))
					ans.push_back(i);
			}
		}
		if(ans==vector<int> (1,-1))
			ans.clear();
		return ans;
	}catch(...){
		vector<VARINDEX> ans;
		return ans;
	}
}
