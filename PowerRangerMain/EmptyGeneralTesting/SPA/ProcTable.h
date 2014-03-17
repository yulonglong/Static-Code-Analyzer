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
public: 
	INDEX ProcTable::insertProc(PROCNAME);
	PROCNAME ProcTable::getProcName (INDEX);
	INDEX ProcTable::getProcIndex (PROCNAME);
};