#ifndef NEXT_H
#define NEXT_H

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iterator>
#include "TypeTable.h"

typedef int STMTNUM;

class Next {
private:
	unordered_map<STMTNUM, vector<STMTNUM>> nextTable;
	unordered_map<STMTNUM, STMTNUM> previousTable;
	static bool instanceFlag;
	static Next *next;
	TypeTable *typeTable;

public:	
	Next(TypeTable*);
	Next();
	~Next();
	static Next* getInstance();	// to be used to get instance of singleton class
	static Next* getInstance(TypeTable*);	// to be used to get instance of singleton class 
	
	void setNext(STMTNUM, STMTNUM);
	vector<STMTNUM> getNext(STMTNUM);
	STMTNUM getPrevious(STMTNUM);
};

#endif