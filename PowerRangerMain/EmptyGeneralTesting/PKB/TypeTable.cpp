#pragma once

#include "TypeTable.h"

bool TypeTable::instanceFlag=false;
TypeTable* TypeTable::typeTable=NULL;

// constructor
TypeTable::TypeTable() {
	typeMap.assign(1, INVALID);
}

TypeTable::~TypeTable(){
	typeMap.clear();
	instanceFlag=false;
}


TypeTable* TypeTable::getInstance() {
	if(!instanceFlag)
    {
        typeTable = new TypeTable();
        instanceFlag = true;
        return typeTable;
    }
    else
    {
        return typeTable;
    }
}


void TypeTable::insertStmtNumAndType(STMTNUM s,TypeTable::SynType t) {
	//Resize if needed
	if (s >= (signed int) typeMap.size()) {
		typeMap.resize(s+1, INVALID);
	}
	typeMap[s]=t;
}

TypeTable::SynType TypeTable::getType(STMTNUM s) {
	try{
		return typeMap.at(s);
	}catch(...){
		return INVALID;
	}
}

vector<STMTNUM> TypeTable:: getAllStmts (TypeTable::SynType t) {
	vector<STMTNUM> list;
	for (size_t i=1; i!=typeMap.size(); i++){
		if (t == STMT || typeMap.at(i) == t) {
			list.push_back (i);
		}
	}
	return list;
}

bool TypeTable::isType(TypeTable::SynType type, STMTNUM stmt) {
	try{
		if (type == STMT || typeMap.at(stmt) == type) {
			return true;
		}
		return false;
	}catch(...){
		return false;
	}
}