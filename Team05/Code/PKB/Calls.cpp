#pragma once

#include "Calls.h"

bool Calls::instanceFlag=false;
Calls* Calls::calls=NULL;

//Constructor
Calls::~Calls(){
	callsTable.clear();
	instanceFlag=false;
}

Calls* Calls::getInstance(ProcTable* pt) {
	if(!instanceFlag){
        calls = new Calls(pt);
        instanceFlag = true;
        return calls;
    }
    else
    {
        return calls;
    }
}


Calls::Calls(ProcTable* pt){
	procTable = pt;
}

unordered_map<PROCINDEX, vector<CALLSPAIR>> Calls::getCallsTable(){
	return callsPairTable;
}

void Calls::setCalls(PROCNAME p1, PROCNAME p2, STMTNUM s){
	PROCINDEX index1 = procTable->getProcIndex(p1);
	PROCINDEX index2 = procTable->getProcIndex(p2);
	if(index1!=-1 && index2!=-1){
		try{
			CALLSPAIR tempPair (index2,s);
			vector<CALLSPAIR> temp (1,tempPair);
			
			try{
				vector<CALLSPAIR> temp1 = callsPairTable.at(index1);
				temp1.push_back(tempPair);
				callsPairTable[index1] = temp1;
			} catch(...){
				callsPairTable[index1] = temp;
			}
		}catch(...){
		}

		try {
			vector<int64_t> placeHolder (0,1);
			vector<int64_t> temp (0,1);
			try{
				temp = callsTable.at(index1);
			}catch(...){
				callsTable.resize(s+1,placeHolder);
			}
			int location =ceil((double)index2/63);
			int bitPos = index2%63;

			if(temp.size()<location)
				temp.resize(location);

			int64_t bitArray = temp.at(location-1);
			bitArray = bitArray | (((int64_t)1)<<bitPos);

			temp[location-1]=bitArray;
			callsTable[index1]=temp;

			callsList.insert(index1);
		}catch(...){
		}
		try {
			vector<int64_t> placeHolder (0,1);
			vector<int64_t> temp (0,1);
			try{
				temp = calledByTable.at(index2);
			}catch(...){
				calledByTable.resize(index2+1,placeHolder);
			}
			int location =ceil((double)index1/63);
			int bitPos = index1%63;

			if(temp.size()<location)
				temp.resize(location);

			int64_t bitArray = temp.at(location-1);
			bitArray = bitArray | (((int64_t)1)<<bitPos);

			temp[location-1]=bitArray;
			calledByTable[index2]=temp;

			calledList.insert(index2);
		}catch(...){
		}
	}
}

bool Calls::isCalls(PROCINDEX index1, PROCINDEX index2){
	try {
		if(index1==-1 || index2==-1)
			return false;

		vector<int64_t> temp=callsTable.at(index1);
		int location =ceil((double)index2/63);
		int bitPos = index2%63;
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


set<PROCINDEX> Calls::getAllCalls(){
	return callsList;
}

set<PROCINDEX> Calls::getAllCalled(){
	return calledList;
}


set<PROCINDEX> Calls::getCalls(PROCINDEX index){
	set<PROCINDEX> ans;
	try{
		vector<int64_t> temp=calledByTable.at(index);

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

set<PROCINDEX> Calls::getCalled(PROCINDEX index){
	set<PROCINDEX> ans;
	try{
		vector<int64_t> temp=callsTable.at(index);

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

void Calls::printCallsTable() {
	cout<< "Calls Table" << endl;
	int index =0;
	for(vector<vector<int64_t>>::iterator it = callsTable.begin(); it != callsTable.end(); it++,index++) {
		if(it->size()!=0){
			cout<< index << " calls ";
			vector<int64_t> temp = *it; 
			for (size_t s =0; s!=temp.size(); s++) {
				int64_t bitArray = temp.at(s);
				while(bitArray>0){
					int64_t bit = bitArray & -bitArray;
					bitArray -= bit;
					int number = log((double)bit)/log(2.0) + s*63;
					cout<< number<< ",";
				}
			}		
			cout<<endl;
		}
	}
}

void Calls::printCallsPairTable() {
	cout<< "Calls Table" << endl;
	for(unordered_map<PROCINDEX, vector<CALLSPAIR>>::iterator it = callsPairTable.begin(); it != callsPairTable.end(); it++) {
		string name1 = procTable->getProcName(it->first);
		cout<< name1 << " modifies ";
		vector<CALLSPAIR> temp = it->second; 
		vector<CALLSPAIR>::iterator iter;
		for (iter = temp.begin(); iter!=temp.end(); iter++) {
			string name = procTable->getProcName(iter->first);
			cout<< name<< " at line " << iter->second <<" , ";
		}		
		cout<<endl;
	}
}
