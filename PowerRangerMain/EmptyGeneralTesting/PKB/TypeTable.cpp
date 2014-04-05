#pragma once

#include "TypeTable.h"


// constructor
TypeTable::TypeTable() {
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

bool isType(TypeTable::SynType type, STMTNUM stmt) {
	if (type == STMT || typeMap[stmt] == type) {
		return true;
	}
	return false;
}