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
	vector<PROCNAME> procTable; 

public:
	ProcTable();
	INDEX insertProc(PROCNAME);
	PROCNAME getProcName (INDEX);
	INDEX getProcIndex (PROCNAME);
	INDEX getNumProcedures(); 

};

#endif