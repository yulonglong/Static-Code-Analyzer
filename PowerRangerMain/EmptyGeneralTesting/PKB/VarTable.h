#ifndef VARTABLE_H
#define VARTABLE_H

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
private: 
	vector<VARNAME> variableTable; 
	static bool instanceFlag;
	static VarTable *varTable;
public: 
	VarTable();
	~VarTable();
	static VarTable* getInstance();	// to be used to get instance of singleton class 
	INDEX insertVar(VARNAME);
	VARNAME getVarName (INDEX);
	INDEX getVarIndex (VARNAME);
	INDEX getNumVar(); 
};

#endif