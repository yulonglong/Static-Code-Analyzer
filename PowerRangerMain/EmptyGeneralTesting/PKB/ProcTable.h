#ifndef PROCTABLE_H
#define PROCTABLE_H

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>

using namespace std;
typedef int INDEX;
typedef string PROCNAME; 

class ProcTable {
private: 
	vector<PROCNAME> procedureTable; 
	static bool instanceFlag;
	static ProcTable *procTable;
public:
	ProcTable();
	~ProcTable();
	static ProcTable* getInstance();	// to be used to get instance of singleton class 
	INDEX insertProc(PROCNAME);
	PROCNAME getProcName (INDEX);
	INDEX getProcIndex (PROCNAME);
	INDEX getNumProcedures(); 

};

#endif