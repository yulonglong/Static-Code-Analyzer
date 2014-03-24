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
typedef vector<STMTNUM> LIST;

class Parent {
public: 
	Parent();
	VOID setParent(STMTNUM, STMTNUM);
	BOOLEAN isParent(STMTNUM, STMTNUM);
	BOOLEAN isParent(SType, STMTNUM); // isParent(while, s1) 
	BOOLEAN isChildren(SType, STMTNUM); 
	vector<STMTNUM> getParent(SType, SType, STMTNUM); // parent (w, s1) --> returns parents that are while statements
	// what you want to get, 2nd parameter of parent
	vector<STMTNUM> getChildren(SType, SType, STMTNUM);
	// Parent (s1, w) returns all the while stmts
	// vector<STMTNUM> getParent(SType, SType, SType);
};

#endif