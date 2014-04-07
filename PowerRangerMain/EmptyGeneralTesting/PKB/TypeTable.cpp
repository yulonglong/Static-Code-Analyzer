#pragma once

#include "TypeTable.h"

bool TypeTable::instanceFlag=false;
TypeTable* TypeTable::typeTable=NULL;

// constructor
TypeTable::TypeTable() {
}

TypeTable::~TypeTable(){
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
	typeMap[s]=t;
}

// Throws exception; whoever calls please catch
TypeTable::SynType TypeTable::getType(STMTNUM s) {
	return typeMap.at(s);
}

vector<STMTNUM> TypeTable:: getAllStmts (TypeTable::SynType t) {
	vector<STMTNUM> list;
	for (map<int,TypeTable::SynType>::iterator it=typeMap.begin(); it!=typeMap.end(); ++it){
		if (t == STMT || it->second == t) {
			list.push_back (it->first);
		}
	}
	return list;
}

bool TypeTable::isType(TypeTable::SynType type, STMTNUM stmt) {
	if (type == STMT || typeMap.at(stmt) == type) {
		return true;
	}
	return false;
}