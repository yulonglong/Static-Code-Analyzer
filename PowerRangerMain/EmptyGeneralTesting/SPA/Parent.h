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
public: 
	Parent();
	VOID setParent(STMTNUM, STMTNUM);
	BOOLEAN isParent(STMTNUM, STMTNUM);
	STMTNUM getParent(STMTNUM);
	LIST getChildren(STMTNUM);
};