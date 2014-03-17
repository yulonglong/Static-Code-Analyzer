#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>

using namespace std;
typedef int INDEX;
typedef string VARNAME; 

class VarTable {
public: 
	VarTable();
	INDEX insertVar(VARNAME);
	VARNAME getVarName (INDEX);
	INDEX getVarIndex (VARNAME);
};