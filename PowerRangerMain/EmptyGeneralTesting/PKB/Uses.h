#ifndef USES_H
#define USES_H

#pragma once
#include <iostream>
#include "TypeTable.h"
#include "VarTable.h"

using namespace std;

class Uses {
private:
	vector<vector<STMTNUM>> usesTable;
	static bool instanceFlag;
	static Uses *uses;
	TypeTable *typeTable; // for the sake of unit testing.
	VarTable *varTable;
public:
	Uses();
	Uses(TypeTable*,VarTable*);
	~Uses();
	static Uses* getInstance();	// to be used to get instance of singleton class
	static Uses* getInstance(TypeTable*,VarTable*);	// to be used to get instance of singleton class
	void setUses(STMTNUM, VARNAME);
	bool isUses(STMTNUM, VARNAME);	//Select boolean such that Uses(1, "y")
	bool isUses(TypeTable::SynType, TypeTable::SynType);	//Select s such that Uses(a, v) parameter order: selected type, first token, second token
	vector<int> getUses(TypeTable::SynType, VARNAME);	//Select a such that Uses(a, "x")	return -1 if doesn't exist
	vector<string> getModified(TypeTable::SynType);		//Select v such that Uses(1, v)	return empty vector if doesnt exist
};

#endif