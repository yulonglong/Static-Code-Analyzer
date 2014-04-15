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

		vector<STMTNUM> existing;
		try{
			existing = usesTable.at(s);
			usesTable.erase(s);
		}
		catch(...){
		}
		existing.push_back(index);
		usesTable.insert(pair<STMTNUM,vector<STMTNUM>>(s,existing));
		cout<<"setUses("<<s<<","<<v<<")"<<" var Index = "<<index<<endl;
	}catch(...){
	}
}

bool Uses::isUses(STMTNUM s, VARNAME v){
	try{
		VARINDEX index = varTable->getVarIndex(v);
		vector<STMTNUM> temp = usesTable.at(s);
		vector<STMTNUM>::iterator it = temp.begin();
		for(;it!=temp.end();it++){
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
		for(map<STMTNUM,vector<STMTNUM>>::iterator i = usesTable.begin(); i != usesTable.end(); i++){
			vector<STMTNUM> temp = i->second;
			vector<STMTNUM>::iterator it = temp.begin();
			for(;it!=temp.end();++it){
				if(*it==index){
					if(t==TypeTable::STMT){
						ans.push_back(i->first);
						break;
					}
					else if(typeTable->isType(t,i->first)){
						ans.push_back(i->first);
						break;
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
		vector<VARINDEX> temp = usesTable.at(s);
		return temp;
	}catch(...){
		vector<VARINDEX> temp;
		return temp;
	}
}

vector<VARINDEX> Uses::getUses(TypeTable::SynType type){	//Select a such that Uses(a, v); return empty vector if does not exist
	try{
		vector<VARINDEX> ans;
		for(map<STMTNUM,vector<STMTNUM>>::iterator i = usesTable.begin(); i != usesTable.end(); i++){
			if(!i->second.empty()){
				if(typeTable->isType(type,i->first))
					ans.push_back(i->first);
			}
		}
		return ans;
	}catch(...){
		vector<VARINDEX> ans;
		return ans;
	}
}
