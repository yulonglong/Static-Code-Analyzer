#pragma once

#include "Uses.h"

bool Uses::instanceFlag=false;
Uses* Uses::uses=NULL;

//Constructor
Uses::Uses(){
	vector<VARINDEX> temp (1,-1);
	usesTable.assign(1,temp);
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
	vector<VARINDEX> temp (1,-1);
	usesTable.assign(1,temp);
}

void Uses::setUses(STMTNUM s,VARNAME v){
	try{
		VARINDEX index = varTable->getVarIndex(v);

		vector<VARINDEX> temp (1,-1);
		if (s >= (signed int) usesTable.size()) {
			usesTable.resize(s+1, temp);
		}
		vector<VARINDEX> temp1 = usesTable.at(s);
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

vector<VARINDEX> Uses::getUses(TYPE t, VARNAME v){	//Select a such that Uses(a, "x")	return -1 if doesn't exist
	try{
		VARINDEX index = varTable->getVarIndex(v);
		vector<VARINDEX> ans;
		for(size_t i=1;i<usesTable.size();i++){
			vector<VARINDEX> temp = usesTable.at(i);
			vector<VARINDEX>::iterator it = temp.begin();
			for(;it!=temp.end();++it){
				if(*it==index){
					if(t==TypeTable::STMT){
						ans.push_back(i);
						break;
					}
					else if(typeTable->isType(t,i)){
						ans.push_back(i);
						break;
					}
				}
			}
		}
		if(ans.empty())
			return vector<VARINDEX> (1,-1);
		else
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
		for(size_t i=1;i<usesTable.size();i++){
			if(!usesTable.at(i).empty() && usesTable.at(i)!=vector<int> (1,-1)){
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
