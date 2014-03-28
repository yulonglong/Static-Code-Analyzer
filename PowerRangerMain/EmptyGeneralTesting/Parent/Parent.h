#ifndef PARENT_H
#define PARENT_H

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include "TypeTable.h"

using namespace std;
typedef int STMTNUM;
typedef bool BOOLEAN;
typedef vector<STMTNUM> LIST;

class Parent {
private:
	vector<vector<STMTNUM>> parentTable;
	vector<STMTNUM> childrenTable;
	
public: 
	TypeTable table; // for the sake of unit testing.
	Parent();
	~Parent();
	void setParent(STMTNUM, STMTNUM);
	BOOLEAN isParent(STMTNUM, STMTNUM);
	BOOLEAN isParent(STYPE, STMTNUM); // isParent(while, s1) 
	BOOLEAN isChildren(STYPE, STMTNUM); 
	vector<STMTNUM> getParent(STYPE, STYPE, STMTNUM); // parent (w, s1) --> returns parents that are while statements
	// what you want to get, 2nd parameter of parent
	vector<STMTNUM> getChildren(STYPE, STYPE, STMTNUM);
	// Parent (s1, w) returns all the while stmts
	// vector<STMTNUM> getParent(STYPE, STYPE, STYPE);
};

#endif