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
	BOOLEAN isParent(Query::SynType, Query::SynType); // Select BOOLEAN such that Parent(w,a)
	BOOLEAN isParent(Query::SynType, STMTNUM); // Select BOOLEAN such that Parent(3,a)
	BOOLEAN isChildren(Query::SynType, STMTNUM); // Select BOOLEAN such that Parent(w,3)
	vector<STMTNUM> getParent(Query::SynType, Query::SynType); // Select w such that Parent(w,a)
	vector<STMTNUM> getChildren(Query::SynType, Query::SynType); //Select a such that Parent(w,a)
	vector<STMTNUM> getParent(Query::SynType, STMTNUM); // Select w such that Parent(w,3)
	vector<STMTNUM> getChildren(Query::SynType, STMTNUM); //Select a such that Parent(1,a)
};

#endif