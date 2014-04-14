#ifndef VARTABLE_H
#define VARTABLE_H

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>

using namespace std;
typedef int VARINDEX;
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
	VARINDEX insertVar(VARNAME);
	VARNAME getVarName (VARINDEX);
	VARINDEX getVarIndex (VARNAME);
	int getNumVar(); 
	vector<VARINDEX> getAllVarIndex(); 
};

#endif