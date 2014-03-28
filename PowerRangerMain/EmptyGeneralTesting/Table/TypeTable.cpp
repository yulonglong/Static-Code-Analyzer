#pragma once

#include "TypeTable.h"


// constructor
TypeTable::TypeTable() {
}


void TypeTable::insertStmtNumAndType(STMTNUM s,STYPE t) {
	typeMap[s]=t;
}


STYPE TypeTable:: getType (STMTNUM s) {
	return typeMap.at(s);
}

LIST TypeTable:: getStmtNum (STYPE t) {
	LIST list;
	for (map<int,STYPE>::iterator it=typeMap.begin(); it!=typeMap.end(); ++it){
		if(it->second == t) {
			list.push_back (it->first);
		}
	}
	return list;
}