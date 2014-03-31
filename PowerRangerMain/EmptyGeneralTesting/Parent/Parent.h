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
	BOOLEAN isParent(STMTNUM, STMTNUM);// Select BOOLEAN such that Parent(1,2)
	BOOLEAN isParent(STYPE, STYPE); // Select BOOLEAN such that Parent(w,a)
	BOOLEAN isParent(STYPE, STMTNUM); // Select BOOLEAN such that Parent(3,a)
	BOOLEAN isChildren(STYPE, STMTNUM); // Select BOOLEAN such that Parent(w,3)
	vector<STMTNUM> getParent(STYPE, STYPE); // Select w such that Parent(w,a)
	vector<STMTNUM> getChildren(STYPE, STYPE); //Select a such that Parent(w,a)
	vector<STMTNUM> getParent(STYPE, STMTNUM); // Select w such that Parent(w,3)
	vector<STMTNUM> getChildren(STYPE, STMTNUM); //Select a such that Parent(1,a)
};

#endif