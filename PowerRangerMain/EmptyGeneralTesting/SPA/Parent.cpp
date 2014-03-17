#pragma once

#include "Parent.h"

// constructor
Parent::Parent() {
	// program line 0 is not to be used for the enumeration
	// parentTable.emplace_back();
}

VOID Parent::setParent(STMTNUM stmt1, STMTNUM stmt2) {
	return;
}

BOOLEAN Parent::isParent(STMTNUM stmt1, STMTNUM stmt2) {
	return false;
}

STMTNUM Parent::getParent(STMTNUM stmt1) {
	return -1;
}

LIST Parent::getChildren(STMTNUM stmt1) {
	LIST newList;
	return newList;
}
