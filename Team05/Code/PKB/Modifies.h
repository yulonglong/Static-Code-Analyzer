#ifndef MODIFIES_H
#define MODIFIES_H

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iterator>
#include "TypeTable.h"
#include "VarTable.h"
#include "ProcTable.h"

typedef TypeTable::SynType TYPE; 

class Modifies {
private:
	unordered_map<STMTNUM, vector<VARINDEX>> modifiesTable;
	unordered_map<PROCINDEX, vector<VARINDEX>> modifiesProcTable;
	static bool instanceFlag;
	static Modifies *modifies;
	TypeTable *typeTable; 
	VarTable *varTable;
	ProcTable *procTable;
public:	
	Modifies(TypeTable*, VarTable*, ProcTable*);
	Modifies();
	~Modifies();
	static Modifies* getInstance();	// to be used to get instance of singleton class
	static Modifies* getInstance(TypeTable*, VarTable*,ProcTable*);	// to be used to get instance of singleton class 
	unordered_map<STMTNUM, vector<VARINDEX>> getModifiesTable(); // only for unit testing.
	void setModifies(STMTNUM, VARNAME);
	bool isModifies(STMTNUM, VARNAME);	//Select w such that Modifies(1, "y")
	vector<STMTNUM> getModifies(TYPE);			//Returns STMTNUM of statements of type t that modifies any variable; If no such statments, then returns empty vector.
	vector<VARINDEX> getModifies(STMTNUM);		//Select v such that Modifies(1, v)	return empty vector if doesnt exist
	vector<STMTNUM> getModifies(TYPE, VARNAME);	//Select a such that Modifies(a, "x")	return empty vector if doesnt exist

	void setModifiesProc(PROCINDEX, vector<VARINDEX>); // if there already were variables modified by this procedure, then just add the 2 vectors.
	vector<VARINDEX> getModifiesProc(PROCINDEX); //for getting using procedure index
	vector<PROCINDEX> getModifiesProcVar(VARNAME); //get all the procedures that modifies the variable with varname
	bool isModifiesProc(PROCNAME, VARNAME); //returns true if procname modifies varname
	void setModifies(STMTNUM, vector<VARINDEX>); // same as above

};

#endif