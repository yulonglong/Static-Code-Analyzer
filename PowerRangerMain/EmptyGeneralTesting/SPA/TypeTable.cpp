#pragma once

#include "TypeTable.h"


// constructor
TypeTable::TypeTable() {
}


void TypeTable::insertStmtNumAndType(STMTNUM s,SType t) {
	typeMap[s]=t;
}


SType TypeTable:: getType (STMTNUM s) {
	return typeMap.at(s);
}

LIST TypeTable:: getStmtNum (SType t) {
	LIST list;
	for (map<int,string>::iterator it=typeMap.begin(); it!=typeMap.end(); ++it){
		if(it->second.compare(t) == 0) {
			list.push_back (it->first);
		}
	}

	return list;
}