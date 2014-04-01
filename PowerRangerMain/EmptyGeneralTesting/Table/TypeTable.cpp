#pragma once

#include "TypeTable.h"


// constructor
TypeTable::TypeTable() {
}


void TypeTable::insertStmtNumAndType(STMTNUM s,Query::SynType t) {
	typeMap[s]=t;
}

// Throws exception
Query::SynType TypeTable:: getType (STMTNUM s) {
	return typeMap.at(s);
}

vector<STMTNUM> TypeTable:: getAllStmts (Query::SynType t) {
	vector<STMTNUM> list;
	for (map<int,Query::SynType>::iterator it=typeMap.begin(); it!=typeMap.end(); ++it){
		if (t == Query::STMT || it->second == t) {
			list.push_back (it->first);
		}
	}
	return list;
}

