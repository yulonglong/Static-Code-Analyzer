#pragma once

#include "Modifies.h"

bool Modifies::instanceFlag=false;
Modifies* Modifies::modifies=NULL;
	
Modifies::Modifies(VarTable *vt) {
	varTable = vt;
}


Modifies::~Modifies() {
	modifiesTable.clear();
	modifiedVarTable.clear();
	instanceFlag=false;
}


Modifies* Modifies::getInstance(VarTable* vt) {
	if(!instanceFlag) {
        modifies = new Modifies(vt);
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
		vector<int64_t> placeHolder (0,1);
		vector<int64_t> temp (0,1);
		try{
			temp = modifiesTable.at(s);
		}catch(...){
			modifiesTable.resize(s+1,placeHolder);
		}
		int location =ceil((double)index/63);
		int bitPos = index%63;

		if(temp.size()<location)
			temp.resize(location);

		int64_t bitArray = temp.at(location-1);
		bitArray = bitArray | (((int64_t)1)<<bitPos);

		temp[location-1]=bitArray;
		modifiesTable[s]=temp;

		modifiesList.insert(s);
	}catch(...){
	}

	try {
		VARINDEX index = varTable->getVarIndex(v);
		vector<int64_t> placeHolder (0,1);
		vector<int64_t> temp (0,1);
		try{
			temp = modifiedVarTable.at(index);
		}catch(...){
			modifiedVarTable.resize(index+1,placeHolder);
		}
		int location =ceil((double)s/63);
		int bitPos = s%63;

		if(temp.size()<location)
			temp.resize(location);

		int64_t bitArray = temp.at(location-1);
		bitArray = bitArray | (((int64_t)1)<<bitPos);

		temp[location-1]=bitArray;
		modifiedVarTable[index]=temp;

		modifiedList.insert(index);
	}catch(...){
	}
}

void Modifies::setModifies(STMTNUM s, set<VARINDEX> varSet) {
	for(set<VARINDEX>::iterator it = varSet.begin(); it!=varSet.end();it++){
		int index = *it;
		try {
			vector<int64_t> placeHolder (0,1);
			vector<int64_t> temp (0,1);
			try{
				temp = modifiesTable.at(s);
			}catch(...){
				modifiesTable.resize(s+1,placeHolder);
			}
			int location =ceil((double)index/63);
			int bitPos = index%63;

			if(temp.size()<location)
				temp.resize(location);

			int64_t bitArray = temp.at(location-1);
			bitArray = bitArray | (((int64_t)1)<<bitPos);

			temp[location-1]=bitArray;
			modifiesTable[s]=temp;

			modifiesList.insert(s);
		}catch(...){
		}

		try {
			vector<int64_t> placeHolder (0,1);
			vector<int64_t> temp (0,1);
			try{
				temp = modifiedVarTable.at(index);
			}catch(...){
				modifiedVarTable.resize(index+1,placeHolder);
			}
			int location =ceil((double)s/63);
			int bitPos = s%63;

			if(temp.size()<location)
				temp.resize(location);

			int64_t bitArray = temp.at(location-1);
			bitArray = bitArray | (((int64_t)1)<<bitPos);

			temp[location-1]=bitArray;
			modifiedVarTable[index]=temp;

			modifiedList.insert(index);
		}catch(...){
		}
	}
}

void Modifies::setModifiesProc(PROCINDEX p, set<VARINDEX> varSet) {
	for(set<VARINDEX>::iterator it = varSet.begin(); it!=varSet.end();it++){
		int index = *it;
		try {
			vector<int64_t> placeHolder (0,1);
			vector<int64_t> temp (0,1);
			try{
				temp = modifiesProcTable.at(p);
			}catch(...){
				modifiesProcTable.resize(p+1,placeHolder);
			}
			int location =ceil((double)index/63);
			int bitPos = index%63;

			if(temp.size()<location)
				temp.resize(location);

			int64_t bitArray = temp.at(location-1);
			bitArray = bitArray | (((int64_t)1)<<bitPos);

			temp[location-1]=bitArray;
			modifiesProcTable[p]=temp;

			modifiesProcList.insert(p);
		}catch(...){
		}

		try {
			vector<int64_t> placeHolder (0,1);
			vector<int64_t> temp (0,1);
			try{
				temp = modifiedProcVarTable.at(index);
			}catch(...){
				modifiedProcVarTable.resize(index+1,placeHolder);
			}
			int location =ceil((double)p/63);
			int bitPos = p%63;

			if(temp.size()<location)
				temp.resize(location);

			int64_t bitArray = temp.at(location-1);
			bitArray = bitArray | (((int64_t)1)<<bitPos);

			temp[location-1]=bitArray;
			modifiedProcVarTable[index]=temp;

			modifiedProcList.insert(index);
		}catch(...){
		}
	}
}

bool Modifies::isModifies(STMTNUM s, VARINDEX index){
	try {
		if (index == -1) {
			return false;
		}

		vector<int64_t> temp=modifiesTable.at(s);
		int location =ceil((double)index/63);
		int bitPos = index%63;
		if(temp.size()<location)
			return false;

		int64_t bitArray = temp.at(location-1);
		if((bitArray & ((int64_t)1<<bitPos))>0)
			return true;
	} catch (...){
		return false;
	}
	return false;
}

set<VARINDEX> Modifies::getModified(STMTNUM snum){
	set<STMTNUM> ans;
	try{
		vector<int64_t> temp=modifiesTable.at(snum);

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

set<STMTNUM> Modifies::getModifies(VARINDEX i){
	set<STMTNUM> ans;
	try{
		vector<int64_t> temp=modifiedVarTable.at(i);

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

set<VARINDEX> Modifies::getAllModified(){
	return modifiedList;
}

set<STMTNUM> Modifies::getAllModifies(){
	return modifiesList;
}

bool Modifies::isModifiesProc(PROCINDEX p, VARINDEX index){
	try {
		if (index == -1) {
			return false;
		}

		vector<int64_t> temp=modifiesProcTable.at(p);
		int location =ceil((double)index/63);
		int bitPos = index%63;
		if(temp.size()<location)
			return false;

		int64_t bitArray = temp.at(location-1);
		if((bitArray & ((int64_t)1<<bitPos))>0)
			return true;
	} catch (...){
		return false;
	}
	return false;
}

set<VARINDEX> Modifies::getModifiedProc(PROCINDEX p){
	set<VARINDEX> ans;
	try{
		vector<int64_t> temp=modifiesProcTable.at(p);

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

set<PROCINDEX> Modifies::getModifiesProc(VARINDEX i){
	set<PROCINDEX> ans;
	try{
		vector<int64_t> temp=modifiedProcVarTable.at(i);

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

set<VARINDEX> Modifies::getAllModifiedProc(){
	return modifiedProcList;
}

set<PROCINDEX> Modifies::getAllModifiesProc(){
	return modifiesProcList;
}


void Modifies::printModifiesTable() {
	cout<< "Modifies Table" << endl;
	int index =0;
	for(vector<vector<int64_t>>::iterator it = modifiesTable.begin(); it != modifiesTable.end(); it++,index++) {
		if(it->size()!=0){
			cout<< index << " modifies ";
			vector<int64_t> temp = *it; 
			for (size_t s =0; s!=temp.size(); s++) {
				int64_t bitArray = temp.at(s);
				while(bitArray>0){
					int64_t bit = bitArray & -bitArray;
					bitArray -= bit;
					int number = log((double)bit)/log(2.0) + s*63;
					string name = varTable->getVarName(number);
					cout<< name<< ",";
				}
			}		
			cout<<endl;
		}
	}
}