#pragma once

#include "TypeTable.h"


// constructor
TypeTable::TypeTable() {
}


void TypeTable::insertStmtNumAndType(STMTNUM s,Query::SynType t) {
	typeMap[s]=t;
}


Query::SynType TypeTable:: getType (STMTNUM s) {
	return typeMap.at(s);
}

vector<STMTNUM> TypeTable:: getStmtNum (Query::SynType t) {
	vector<STMTNUM> list;
	for (map<int,Query::SynType>::iterator it=typeMap.begin(); it!=typeMap.end(); ++it){
		if(it->second == t) {
			list.push_back (it->first);
		}
	}
	return list;
}