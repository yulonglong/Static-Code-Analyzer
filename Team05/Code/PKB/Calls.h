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

typedef int STMTNUM;
typedef pair<PROCINDEX,STMTNUM> CALLSPAIR;

class Calls {
private:
	unordered_map<PROCINDEX, vector<CALLSPAIR>> callsTable;
	static bool instanceFlag;
	static Calls *calls;
	ProcTable *procTable;

public:	
	Calls(ProcTable*);
	Calls();
	~Calls();
	static Calls* getInstance();	// to be used to get instance of singleton class
	static Calls* getInstance(ProcTable*);	// to be used to get instance of singleton class 
	unordered_map<PROCINDEX, vector<CALLSPAIR>> getCallsTable();
	void setCalls(PROCNAME, PROCNAME, STMTNUM);
	bool isCalls(PROCNAME,PROCNAME);
	
	vector<PROCINDEX> getCalls(); //Calls(p,q) Select p, return empty if not found
	vector<PROCINDEX> getCalls(PROCNAME); //Calls (p, "Second") Select p, return empty if not found
	vector<PROCINDEX> getCalled(); //Calls(p,q) Select q, return empty if not found
	vector<PROCINDEX> getCalled(PROCNAME); //Calls("First", q) Select q, return empty if not found
};

#endif