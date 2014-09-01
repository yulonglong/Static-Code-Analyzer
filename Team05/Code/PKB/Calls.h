#ifndef CALLS_H
#define CALLS_H

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iterator>
#include "ProcTable.h"


class Calls {
private:
	unordered_map<PROCINDEX, vector<PROCINDEX>> callsTable;
	static bool instanceFlag;
	static Calls *calls;
	ProcTable *procTable;

public:	
	Calls(ProcTable*);
	Calls();
	~Calls();
	static Calls* getInstance();	// to be used to get instance of singleton class
	static Calls* getInstance(ProcTable*);	// to be used to get instance of singleton class 
	void setCalls(PROCNAME, PROCNAME);
	bool isCalled(PROCNAME,PROCNAME);
};

#endif