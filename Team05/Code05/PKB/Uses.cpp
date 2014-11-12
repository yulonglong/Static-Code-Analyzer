#pragma once
#pragma warning( disable : 4018)
#pragma warning( disable : 4244)

#include "Uses.h"

bool Uses::instanceFlag=false;
Uses* Uses::uses=NULL;

//Constructor
Uses::Uses(VarTable *vt){
	varTable = vt;
}

Uses::~Uses(){
	usesTable.clear();
	instanceFlag=false;
}

Uses* Uses::getInstance(VarTable* vt) {
	if(!instanceFlag)
    {
        uses = new Uses(vt);
        instanceFlag = true;
        return uses;
    }
    else
    {
        return uses;
    }
}

void Uses::setUses(STMTNUM s, VARNAME v) {
	try {
		VARINDEX index = varTable->getVarIndex(v);
		vector<int64_t> placeHolder (0,1);
		vector<int64_t> temp (0,1);
		try{
			temp = usesTable.at(s);
		}catch(...){
			usesTable.resize(s+1,placeHolder);
		}
		int location =ceil((double)index/63);
		int bitPos = index%63;

		if(temp.size()<location)
			temp.resize(location);

		int64_t bitArray = temp.at(location-1);
		bitArray = bitArray | (((int64_t)1)<<bitPos);

		temp[location-1]=bitArray;
		usesTable[s]=temp;

		usesList.insert(s);
	}catch(...){
	}

	try {
		VARINDEX index = varTable->getVarIndex(v);
		vector<int64_t> placeHolder (0,1);
		vector<int64_t> temp (0,1);
		try{
			temp = usedVarTable.at(index);
		}catch(...){
			usedVarTable.resize(index+1,placeHolder);
		}
		int location =ceil((double)s/63);
		int bitPos = s%63;

		if(temp.size()<location)
			temp.resize(location);

		int64_t bitArray = temp.at(location-1);
		bitArray = bitArray | (((int64_t)1)<<bitPos);

		temp[location-1]=bitArray;
		usedVarTable[index]=temp;

		usedList.insert(index);
	}catch(...){
	}
}

void Uses::setUses(STMTNUM s, set<VARINDEX> varSet) {
	for(set<VARINDEX>::iterator it = varSet.begin(); it!=varSet.end();it++){
		int index = *it;
		try {
			vector<int64_t> placeHolder (0,1);
			vector<int64_t> temp (0,1);
			try{
				temp = usesTable.at(s);
			}catch(...){
				usesTable.resize(s+1,placeHolder);
			}
			int location =ceil((double)index/63);
			int bitPos = index%63;

			if(temp.size()<location)
				temp.resize(location);

			int64_t bitArray = temp.at(location-1);
			bitArray = bitArray | (((int64_t)1)<<bitPos);

			temp[location-1]=bitArray;
			usesTable[s]=temp;

			usesList.insert(s);
		}catch(...){
		}

		try {
			vector<int64_t> placeHolder (0,1);
			vector<int64_t> temp (0,1);
			try{
				temp = usedVarTable.at(index);
			}catch(...){
				usedVarTable.resize(index+1,placeHolder);
			}
			int location =ceil((double)s/63);
			int bitPos = s%63;

			if(temp.size()<location)
				temp.resize(location);

			int64_t bitArray = temp.at(location-1);
			bitArray = bitArray | (((int64_t)1)<<bitPos);

			temp[location-1]=bitArray;
			usedVarTable[index]=temp;

			usedList.insert(index);
		}catch(...){
		}
	}
}

void Uses::setUsesProc(PROCINDEX p, set<VARINDEX> varSet) {
	for(set<VARINDEX>::iterator it = varSet.begin(); it!=varSet.end();it++){
		int index = *it;
		try {
			vector<int64_t> placeHolder (0,1);
			vector<int64_t> temp (0,1);
			try{
				temp = usesProcTable.at(p);
			}catch(...){
				usesProcTable.resize(p+1,placeHolder);
			}
			int location =ceil((double)index/63);
			int bitPos = index%63;

			if(temp.size()<location)
				temp.resize(location);

			int64_t bitArray = temp.at(location-1);
			bitArray = bitArray | (((int64_t)1)<<bitPos);

			temp[location-1]=bitArray;
			usesProcTable[p]=temp;

			usesProcList.insert(p);
		}catch(...){
		}

		try {
			vector<int64_t> placeHolder (0,1);
			vector<int64_t> temp (0,1);
			try{
				temp = usedProcVarTable.at(index);
			}catch(...){
				usedProcVarTable.resize(index+1,placeHolder);
			}
			int location =ceil((double)p/63);
			int bitPos = p%63;

			if(temp.size()<location)
				temp.resize(location);

			int64_t bitArray = temp.at(location-1);
			bitArray = bitArray | (((int64_t)1)<<bitPos);

			temp[location-1]=bitArray;
			usedProcVarTable[index]=temp;

			usedProcList.insert(index);
		}catch(...){
		}
	}
}

bool Uses::isUses(STMTNUM s, VARINDEX index){
	try {
		if (index == -1) {
			return false;
		}

		vector<int64_t> temp=usesTable.at(s);
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

set<VARINDEX> Uses::getUsed(STMTNUM snum){
	set<VARINDEX> ans;
	try{
		vector<int64_t> temp=usesTable.at(snum);

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

set<STMTNUM> Uses::getUses(VARINDEX i){
	set<STMTNUM> ans;
	try{
		vector<int64_t> temp=usedVarTable.at(i);

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

set<VARINDEX> Uses::getAllUsed(){
	return usedList;
}

set<STMTNUM> Uses::getAllUses(){
	return usesList;
}

bool Uses::isUsesProc(PROCINDEX p, VARINDEX index){
	try {
		if (index == -1) {
			return false;
		}

		vector<int64_t> temp=usesProcTable.at(p);
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

set<VARINDEX> Uses::getUsedProc(PROCINDEX p){
	set<VARINDEX> ans;
	try{
		vector<int64_t> temp=usesProcTable.at(p);

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

set<PROCINDEX> Uses::getUsesProc(VARINDEX i){
	set<PROCINDEX> ans;
	try{
		vector<int64_t> temp=usedProcVarTable.at(i);

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

set<VARINDEX> Uses::getAllUsedProc(){
	return usedProcList;
}

set<PROCINDEX> Uses::getAllUsesProc(){
	return usesProcList;
}


void Uses::printUsesTable() {
	cout<< "Uses Table" << endl;
	int index =0;
	for(vector<vector<int64_t>>::iterator it = usesTable.begin(); it != usesTable.end(); it++,index++) {
		if(it->size()!=0){
			cout<< index << " uses ";
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