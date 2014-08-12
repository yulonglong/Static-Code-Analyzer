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
typedef TypeTable::SynType TYPE;


class Parent {
private:
	vector<vector<STMTNUM>> parentTable; //given the stmtnum of the parent, return the children stmt num
	vector<STMTNUM> childrenTable; //given the stmtnum of the children, return the parent stmt num 
	static bool instanceFlag;
	static Parent *parent;
	TypeTable *typeTable; // for the sake of unit testing.
public: 
	Parent();
	Parent(TypeTable*);
	~Parent();
	static Parent* getInstance();	// to be used to get instance of singleton class 
	static Parent* getInstance(TypeTable*);	// to be used to get instance of singleton class
	TypeTable* getTypeTable();

	void setParent(STMTNUM, STMTNUM);
	bool isParent(STMTNUM, STMTNUM);// Select BOOLEAN such that Parent(1,2)
	bool isParent(TYPE, TYPE); // Select BOOLEAN such that Parent(w,a)
	bool isParent(TYPE, STMTNUM); // Select BOOLEAN such that Parent(3,a)
	bool isChildren(TYPE, STMTNUM); // Select BOOLEAN such that Parent(w,3)
	vector<STMTNUM> getParent(TYPE, TYPE,STMTNUM); 
	vector<STMTNUM> getChildren(TYPE, TYPE,STMTNUM);
	vector<STMTNUM> getParent(TYPE, TYPE); // Select w such that Parent(w,a)
	vector<STMTNUM> getChildren(TYPE, TYPE); //Select a such that Parent(w,a)
	STMTNUM getParent(TYPE, STMTNUM); 
	vector<STMTNUM> getChildren(TYPE, STMTNUM); 

	//For parentStar
	STMTNUM getParent(STMTNUM); 
	vector<STMTNUM> getChildren(STMTNUM); 
};

#endif