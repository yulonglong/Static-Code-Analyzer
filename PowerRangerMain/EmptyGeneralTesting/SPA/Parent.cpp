#pragma once

#include "Parent.h"

class Parent {
	vector<vector<STMTNUM>> parentTable;

	// constructor
	Parent::Parent() {
		// program line 0 is not to be used for the enumeration
		// parentTable.emplace_back();
	}

	VOID Parent::setParent(STMTNUM, STMTNUM) {

	}

	BOOLEAN Parent::isParent(STMTNUM, STMTNUM) {
	
	}

	STMTNUM Parent::getParent(STMTNUM) {
	
	}

	LIST Parent::getChildren(STMTNUM) {
	
	}
}