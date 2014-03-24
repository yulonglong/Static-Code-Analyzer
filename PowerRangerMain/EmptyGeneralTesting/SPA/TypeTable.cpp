#pragma once

#include "TypeTable.h"


// constructor
TypeTable::TypeTable() {
}


VOID TypeTable::insertStmtNumAndType(STMTNUM,TYPE) {
	typeMap[STMTNUM]=TYPE;
}


TYPE TypeTable:: getTYPE (STMTNUM) {
	return typeMap.at(STMTNUM);
}

LIST TypeTable:: getStmtNum (TYPE) {
	LIST list;
	for (map<char,int>::iterator it=typeMap.begin(); it!=typeMap.end(); ++it){
		if(it->second.compare(TYPE) == 0) {
			list.push_back (it->first);
		}
	}

	return list;
}