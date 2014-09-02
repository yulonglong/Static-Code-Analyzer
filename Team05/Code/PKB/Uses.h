#ifndef USES_H
#define USES_H

#pragma once
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include "TypeTable.h"
#include "VarTable.h"
#include "ProcTable.h"

using namespace std;
typedef TypeTable::SynType TYPE;

class Uses {
private:
	unordered_map<STMTNUM, vector<VARINDEX>> usesTable;
	unordered_map<PROCINDEX, vector<VARINDEX>> usesProcTable;
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
	vector<STMTNUM> getUses(TYPE, VARNAME);	//Select a such that Uses(a, "x")	return empty vector if doesn't exist
	vector<VARINDEX> getUses(STMTNUM);		//Select v such that Uses(1, v)	return variable indexes. otherwise return empty vector if doesnt exist
	vector<STMTNUM> getUses(TYPE);//Select a such that Uses(a, v); return empty vector if does not exist


	void setUsesProc(PROCINDEX, vector<VARINDEX>); // if there already were variables used by this procedure, then just add the 2 vectors
	void setUses(STMTNUM, vector<VARINDEX>); // IPSITA -> the parameters cant be the same (although PROCINDEX and STMTNUM looks different, they are both still int)
	vector<VARINDEX> getUsesProc(PROCINDEX); //for getting using procedure index

};

#endif