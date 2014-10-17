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
#include <set>
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
	vector<vector<int64_t>> modifiesTable;
	vector<vector<int64_t>> modifiedVarTable;
	vector<vector<int64_t>> modifiesProcTable;
	vector<vector<int64_t>> modifiedProcVarTable;
	static bool instanceFlag;
	static Modifies *modifies;
	VarTable *varTable;
	set<STMTNUM> modifiesList;
	set<VARINDEX> modifiedList;
	set<PROCINDEX> modifiesProcList;
	set<VARINDEX> modifiedProcList;
public:	
	//! A constructor to initialize the Modifies class.
	Modifies(VarTable*);
	//! A destructor to clear all the tables and set the instance flag of the singleton class to false.
	~Modifies();
	//! Returns the instance of Modifies singleton class.
	static Modifies* getInstance(VarTable*);	// to be used to get instance of singleton class 

	//! Set the Modifies relationship between a statement number and a variable name to be true.
	void setModifies(STMTNUM, VARNAME);
	//! Set the Modifies relationship between a statement number and a list of variable indexes to be true. Eliminate any duplicates
	void setModifies(STMTNUM, set<VARINDEX>);
	//! Set the Modifies relationship between a procedure index and a list of variable indexes to be true. Eliminate any duplicates
	void setModifiesProc(PROCINDEX, set<VARINDEX>);

	//! If the Modifies relationship between a statement number and a variable index is true, return true. Otherwise, return false.
	bool isModifies(STMTNUM, VARINDEX);
	//! Return a set of all variable indexes that the given statement number has modified. Return an empty set if not found.
	set<VARINDEX> getModified(STMTNUM);
	//! Return a set of all statement numbers that has modified the given variable index. Return an empty set if not found.
	set<STMTNUM> getModifies(VARINDEX);
	//! Return a set of all variable indexes that have been modified. Return an empty set if not found.
	set<VARINDEX> getAllModified();
	//! Return a set of all statement numbers that has modified any variables. Return an empty set if not found.
	set<STMTNUM> getAllModifies();

	//! If the Modifies relationship between a procedure index and a variable index is true, return true. Otherwise, return false.
	bool isModifiesProc(PROCINDEX, VARINDEX);
	//! Return a set of all variable indexes that the given procedure index has modified. Return an empty set if not found.
	set<VARINDEX> getModifiedProc(PROCINDEX);
	//! Return a set of all procedure indexes that has modified the given variable index. Return an empty set if not found.
	set<PROCINDEX> getModifiesProc(VARINDEX);
	//! Return a set of all variable indexes that have been modified. Return an empty set if not found.
	set<VARINDEX> getAllModifiedProc();
	//! Return a set of all procedure indexes that has modified any variables. Return an empty set if not found.
	set<PROCINDEX> getAllModifiesProc();
	
	/// @cond
	void printModifiesTable();
	/// @endcond
};

#endif