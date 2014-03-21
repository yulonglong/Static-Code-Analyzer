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
	BOOLEAN isParent(SType, STMTNUM);
	BOOLEAN isChildren(SType, STMTNUM);
	BOOLEAN	isParent(SType, SType);
	STMTNUM getParent(SType, SType, STMTNUM);
	STMTNUM getChildren(SType, SType, STMTNUM);
	STMTNUM getParent(SType, SType, SType)
};

#endif