#ifndef VARTABLE_H
#define VARTABLE_H

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <unordered_map>

using namespace std;
typedef int VARINDEX;
typedef string VARNAME; 

class VarTable {
private: 
	unordered_map<VARINDEX, VARNAME> variableTable; 
	static bool instanceFlag;
	static VarTable *varTable;
	static VARINDEX currentIndex;
public: 
	VarTable();
	~VarTable();
	static VarTable* getInstance();	// to be used to get instance of singleton class 
	void insertVar(VARNAME);
	VARNAME getVarName (VARINDEX);
	VARINDEX getVarIndex (VARNAME);
};

#endif