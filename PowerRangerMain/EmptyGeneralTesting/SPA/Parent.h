#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>

using namespace std;
typedef int STMTNUM;
typedef void VOID;
typedef bool BOOLEAN;

class Parent {
public: 
	VOID Parent::setParent(STMTNUM, STMTNUM);
	BOOLEAN Parent::isParent(STMTNUM, STMTNUM);
	STMTNUM Parent::getParent(STMTNUM);
	STMTNUM Parent::getChildren(STMTNUM);
private: 
	vector<vector<STMTNUM>> parentTable;
};