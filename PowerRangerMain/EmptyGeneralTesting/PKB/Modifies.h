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
	vector<vector<STMTNUM>> modifiesTable; 
	TypeTable typeTable; 
	VarTable varTable; 

public:	
	Modifies(TypeTable, VarTable);
	~Modifies();

	void setModifies(STMTNUM, VARNAME);
	bool isModifies(STMTNUM, VARNAME);	//Select w such that Modifies(1, "y")
	bool isModifies(TYPE, TYPE);		//Select s such that Modifies(a, v) parameter order: selected type, first token, second token (first parameter can be w or a or s)
	vector<STMTNUM> getModifies(TYPE, VARNAME);	//Select a such that Modifies(a, "x")	return empty vector if doesnt exist
	vector<VARNAME> getModifies(STMTNUM);		//Select v such that Modifies(1, v)	return empty vector if doesnt exist
};

#endif