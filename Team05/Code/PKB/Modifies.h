//@author Yohanes Lim
//Modifies.h

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
#include <cstdint>
#include "TypeTable.h"
#include "VarTable.h"
#include "ProcTable.h"

typedef TypeTable::SynType SYNTYPE; 

/*! \brief A Modifies class to store the Modifies relationship.
 *  
 * Overview: Modifies is responsible to :
 * - Store all the Modifies relationship between statement number and variable index
 * - Store all the Modifies relationship between procedure index and variable index
 * - Allow speedy access to the required datas
 * 
 * Modifies is a singleton class, it can be invoked using:
 * \code
 * static Modifies* getInstance(TypeTable*, VarTable*, ProcTable*);
 * \endcode
 *
 */

class Modifies {
private:
	unordered_map<STMTNUM, vector<VARINDEX>> modifiesTable;
	unordered_map<PROCINDEX, vector<VARINDEX>> modifiesProcTable;
	vector<vector<int64_t>> modTable;
	vector<vector<int64_t>> modVarTable;
	static bool instanceFlag;
	static Modifies *modifies;
	TypeTable *typeTable; 
	VarTable *varTable;
	ProcTable *procTable;
	vector<STMTNUM> modifiesList;
	vector<VARINDEX> modifiedList;
public:	
	//! A constructor to initialize the Modifies class.
	Modifies(TypeTable*, VarTable*, ProcTable*);
	//! A destructor to clear all the tables and set the instance flag of the singleton class to false.
	~Modifies();
	//! Returns the instance of Modifies singleton class.
	static Modifies* getInstance(TypeTable*, VarTable*,ProcTable*);	// to be used to get instance of singleton class 

	//! Set the Modifies relationship between a statement number and a variable name to be true.
	void setModifies(STMTNUM, VARNAME);
	//! If the Modifies relationship between a statement number and a variable name is true, return true. Otherwise, return false.
	bool isModifies(STMTNUM, VARNAME);	//Select w such that Modifies(1, "y")	
	
	bool isModifies(STMTNUM s, VARINDEX i);
	vector<VARINDEX> getModified(STMTNUM s);
	vector<STMTNUM> getModifies(VARINDEX i);
	vector<VARINDEX> getAllModified();
	vector<STMTNUM> getAllModifies();

	bool isModifiesProc(PROCINDEX p, VARINDEX i);
	vector<VARINDEX> getModifiedProc(PROCINDEX p);
	vector<PROCINDEX> getModifiesProc(VARINDEX i);
	vector<VARINDEX> getAllModifiedProc();
	vector<PROCINDEX> getAllModifiesProc();



	//! Return all statement numbers such that each statement number has the given SynType and modifies any variable. Return an empty vector if not found.
	vector<STMTNUM> getModifies(SYNTYPE);	//Returns STMTNUM of statements of type t that modifies any variable;
	//! Return all variable indexes such that each variable index is modified in the given statement number. Return an empty vector if not found.
//	vector<VARINDEX> getModifies(STMTNUM);		//Select v such that Modifies(1, v)	return empty vector if doesnt exist
	//! Return all statement numbers such that each statement number has the given SynType and modifies the given variable name. Return an empty vector if not found.
	vector<STMTNUM> getModifies(SYNTYPE, VARNAME);	//Select a such that Modifies(a, "x")	return empty vector if doesnt exist

	//! Set the Modifies relationship between a statement number and a list of variable indexes to be true. Eliminate any duplicates
	void setModifies(STMTNUM, vector<VARINDEX>);
	//! Set the Modifies relationship between a procedure index and a list of variable indexes to be true. Eliminate any duplicates
	void setModifiesProc(PROCINDEX, vector<VARINDEX>); // if there already were variables modified by this procedure, then just add the 2 vectors.
	//! Return all the variable indexes such that each variable index is modified by the given procedure index. Return an empty vector if not found.
	//vector<VARINDEX> getModifiesProc(PROCINDEX); //for getting using procedure index
	
	//! Return all the procedure indexes such that each procedure index modifies the given variable. Return an empty vector if not found.
	vector<PROCINDEX> getModifiesProcVar(VARNAME);
	//! If the Modifies relationship between a procedure name and a variable name is true, return true. Otherwise, return false.
	bool isModifiesProc(PROCNAME, VARNAME); 

	/// @cond
	void printModifiesTable();
	/// @endcond
};

#endif