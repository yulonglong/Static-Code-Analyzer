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
	INDEX VarTable::insertVar(VARNAME);
	VARNAME VarTable::getVarName (INDEX);
	INDEX VarTable::getVarIndex (VARNAME);
};