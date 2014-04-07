#pragma once

#include "Uses.h"

//Constructor
Uses::Uses(){
	vector<STMTNUM> temp (1,-1);
	usesTable.assign(5, temp);
}

Uses::~Uses(){
}


Uses::Uses(VarTable table,TypeTable table2){
	varTable = table;
	typeTable = table2;
	vector<STMTNUM> temp (1,-1);
	usesTable.assign(5, temp);
}

void Uses::setUses(STMTNUM s,VARNAME v){
	try{
		INDEX index = varTable.getVarIndex(v);
		vector<STMTNUM> temp (1,-1);
		if (s >= (signed int) usesTable.size()) {
			usesTable.resize(s+1, temp);
		}
		vector<STMTNUM> temp1 = usesTable[s];
		temp1.push_back(index);
		usesTable[s] = temp1;
	}catch(...){
	}
}

bool Uses::isUses(STMTNUM s, VARNAME v){
	try{
		INDEX index = varTable.getVarIndex(v);
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

bool Uses::isUses(TypeTable::SynType t1, TypeTable::SynType t2){
	vector<STMTNUM> list; 
	vector<STMTNUM> temp;
	for (vector<STMTNUM>::size_type i = 0; i != usesTable.size(); i++) {
		try {
			temp = usesTable[i];
		} catch (...) {
			//const std::out_of_range& oor
			// cout << "Catch: j is " << j << endl; 
			continue;
		}
		for (vector<STMTNUM>::size_type k = 0; k != temp.size(); k++) { 
			STMTNUM j = temp[k];
			try {
				if (t1 == TypeTable::STMT && t2 == TypeTable::STMT) {
					// cout << i << "  " << j << endl; 
					return true;
				} else if (t1 == TypeTable::STMT && t2 != TypeTable::STMT && typeTable.getType(j) == t2) {
					// cout << i << "  " << j << endl; 
					return true;
				} else if (t1 != TypeTable::STMT && t2 == TypeTable::STMT && typeTable.getType(i) == t1) {
					// cout << i << "  " << j << endl; 
					return true;
				} else if (t1 != TypeTable::STMT && t2 != TypeTable::STMT && typeTable.getType(i) == t1 && typeTable.getType(j) == t2) {
					// cout << i << "  " << j << endl; 
					return true;
				}
			} catch (...) {
				// if that stmtnum doesnt have a type in typetable
				continue; 
			}
		}
	}
	return false;
}

vector<int> Uses::getUses(TypeTable::SynType t, VARNAME v){	//Select a such that Uses(a, "x")	return -1 if doesn't exist
	try{
		INDEX index = varTable.getVarIndex(v);
		vector<STMTNUM> ans;
		vector<STMTNUM> temp = usesTable[index];
		vector<STMTNUM>::iterator it = temp.begin();
		for(;it!=temp.end();++it){
			if(typeTable.getType(*it)==t)
				ans.push_back(-1);
		}
		if(ans.empty())
			return vector<int> (1,-1);
		else
			return ans;
	}catch(...){
		return vector<int> (1,-1);
	}
}