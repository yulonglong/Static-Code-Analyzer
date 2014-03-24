#pragma once

#include "TypeTable.h"


// constructor
TypeTable::TypeTable() {
}


void TypeTable::insertStmtNumAndType(STMTNUM s,TYPE t) {
	typeMap[s]=t;
}


TYPE TypeTable:: getType (STMTNUM s) {
	return typeMap.at(s);
}

LIST TypeTable:: getStmtNum (TYPE t) {
	LIST list;
	for (map<int,string>::iterator it=typeMap.begin(); it!=typeMap.end(); ++it){
		if(it->second.compare(t) == 0) {
			list.push_back (it->first);
		}
	}

	return list;
}