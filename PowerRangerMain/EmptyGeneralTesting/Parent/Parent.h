#ifndef PARENT_H
#define PARENT_H

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include "TypeTable.h"
#include "Query.h"

using namespace std;
typedef int STMTNUM;

class Parent {
private:
	vector<vector<STMTNUM>> parentTable;
	vector<STMTNUM> childrenTable;
	
public: 
	TypeTable table; // for the sake of unit testing.
	Parent();
	~Parent();
	void setParent(STMTNUM, STMTNUM);
	bool isParent(STMTNUM, STMTNUM);// Select BOOLEAN such that Parent(1,2)
	bool isParent(Query::SynType, Query::SynType); // Select BOOLEAN such that Parent(w,a)
	bool isParent(Query::SynType, STMTNUM); // Select BOOLEAN such that Parent(3,a)
	bool isChildren(Query::SynType, STMTNUM); // Select BOOLEAN such that Parent(w,3)
	vector<STMTNUM> getParent(Query::SynType, Query::SynType,STMTNUM); 
	vector<STMTNUM> getChildren(Query::SynType, Query::SynType,STMTNUM);
	vector<STMTNUM> getParent(Query::SynType, Query::SynType); // Select w such that Parent(w,a)
	vector<STMTNUM> getChildren(Query::SynType, Query::SynType); //Select a such that Parent(w,a)
	STMTNUM getParent(Query::SynType, STMTNUM); 
	vector<STMTNUM> getChildren(Query::SynType, STMTNUM); 

	//For parentStar
	STMTNUM getParent(STMTNUM); 
	vector<STMTNUM> getChildren(STMTNUM); 
};

#endif