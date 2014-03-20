#ifndef PARENT_H
#define PARENT_H

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
typedef vector<int> LIST;

class Parent {
private: 
	vector<vector<STMTNUM>> parentTable;
	vector<STMTNUM> childrenTable;
public: 
	Parent();
	VOID setParent(STMTNUM, STMTNUM);
	BOOLEAN isParent(STMTNUM, STMTNUM);
	STMTNUM getParent(STMTNUM);
	LIST vector<STMTNUM> getChildren(STMTNUM);
};

#endif