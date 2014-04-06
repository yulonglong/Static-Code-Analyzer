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

class Parent {
private:
	vector<vector<STMTNUM>> parentTable; //given the stmtnum of the parent, return the children stmt num
	vector<STMTNUM> childrenTable; //given the stmtnum of the children, return the parent stmt num
	
	
public: 
	TypeTable table; // for the sake of unit testing.
	Parent(TypeTable);
	Parent();
	~Parent();
	void setParent(STMTNUM, STMTNUM);
	bool isParent(STMTNUM, STMTNUM);// Select BOOLEAN such that Parent(1,2)
	bool isParent(TypeTable::SynType, TypeTable::SynType); // Select BOOLEAN such that Parent(w,a)
	bool isParent(TypeTable::SynType, STMTNUM); // Select BOOLEAN such that Parent(3,a)
	bool isChildren(TypeTable::SynType, STMTNUM); // Select BOOLEAN such that Parent(w,3)
	vector<STMTNUM> getParent(TypeTable::SynType, TypeTable::SynType,STMTNUM); 
	vector<STMTNUM> getChildren(TypeTable::SynType, TypeTable::SynType,STMTNUM);
	vector<STMTNUM> getParent(TypeTable::SynType, TypeTable::SynType); // Select w such that Parent(w,a)
	vector<STMTNUM> getChildren(TypeTable::SynType, TypeTable::SynType); //Select a such that Parent(w,a)
	STMTNUM getParent(TypeTable::SynType, STMTNUM); 
	vector<STMTNUM> getChildren(TypeTable::SynType, STMTNUM); 
	void updateTable(TypeTable);

	//For parentStar
	STMTNUM getParent(STMTNUM); 
	vector<STMTNUM> getChildren(STMTNUM); 
};

#endif