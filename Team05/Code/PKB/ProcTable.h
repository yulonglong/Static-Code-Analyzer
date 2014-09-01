#ifndef PROCTABLE_H
#define PROCTABLE_H

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>

using namespace std;
typedef int PROCINDEX;
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
	PROCINDEX insertProc(PROCNAME);
	PROCNAME getProcName (PROCINDEX);
	PROCINDEX getProcIndex (PROCNAME);
	int getNumProcedures(); 

};

#endif