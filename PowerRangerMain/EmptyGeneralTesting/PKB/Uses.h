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
	vector<int> getUses(TypeTable::SynType, VARNAME);	//Select a such that Uses(a, "x")	return empty vector if doesn't exist
	vector<INDEX> getUses(STMTNUM);		//Select v such that Uses(1, v)	return variable indexes. otherwise return empty vector if doesnt exist
	vector<int> getUses(TypeTable::SynType);//Select a such that Uses(a, v); return empty vector if does not exist
};

#endif