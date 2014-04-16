#ifndef MODIFIES_H
#define MODIFIES_H

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include "TypeTable.h"
#include "VarTable.h"

typedef TypeTable::SynType TYPE; 

class Modifies {
private:
	vector<vector<VARINDEX>> modifiesTable;
	static bool instanceFlag;
	static Modifies *modifies;
	TypeTable *typeTable; 
	VarTable *varTable;

public:	
	Modifies(TypeTable*, VarTable*);
	Modifies();
	~Modifies();
	static Modifies* getInstance();	// to be used to get instance of singleton class
	static Modifies* getInstance(TypeTable*, VarTable*);	// to be used to get instance of singleton class 
	vector<vector<VARINDEX>> getModifiesTable(); // only for unit testing.
	void setModifies(STMTNUM, VARNAME);
	bool isModifies(STMTNUM, VARNAME);	//Select w such that Modifies(1, "y")
	vector<STMTNUM> getModifies(TYPE);			//Returns STMTNUM of statements of type t that modifies any variable; If no such statments, then returns empty vector.
	vector<VARINDEX> getModifies(STMTNUM);		//Select v such that Modifies(1, v)	return empty vector if doesnt exist
	vector<STMTNUM> getModifies(TYPE, VARNAME);	//Select a such that Modifies(a, "x")	return empty vector if doesnt exist
};

#endif