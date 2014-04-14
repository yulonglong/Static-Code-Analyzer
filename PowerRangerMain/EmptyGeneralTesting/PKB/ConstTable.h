#ifndef CONSTTABLE_H
#define CONSTTABLE_H

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>

using namespace std;
typedef int CONSTINDEX;
typedef int CONSTVALUE; 

class ConstTable {
private: 
	vector<CONSTVALUE> constantTable; 
	static bool instanceFlag;
	static ConstTable *constTable;
public:
	ConstTable();
	~ConstTable();
	static ConstTable* getInstance();	// to be used to get instance of singleton class 
	CONSTINDEX insertConst(CONSTVALUE);
};

#endif