#pragma once

#include "Uses.h"

//Constructor
Uses::Uses(){
	vector<STMTNUM> temp (1,-1);
	usesTable.assign(5, temp);
}


Uses::Uses(VarTable table){
	varTable = table;
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
	}catch(...){
	}
};