//@author Yohanes Lim
//Uses.h

#ifndef USES_H
#define USES_H

#pragma once
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <cstdint>
#include <set>
#include "TypeTable.h"
#include "VarTable.h"
#include "ProcTable.h"

using namespace std;
typedef TypeTable::SynType SYNTYPE;

/*! \brief A Uses class to store the Modifies relationship.
 *  
 * Overview: Uses is responsible to :
 * - Store all the Uses relationship between statement number and variable index
 * - Store all the Uses relationship between procedure index and variable index
 * - Allow speedy access to the required datas
 * 
 * Uses is a singleton class, it can be invoked using:
 * \code
 * static Uses* getInstance(TypeTable*, VarTable*, ProcTable*);
 * \endcode
 *
 */

class Uses {
private:
	vector<vector<int64_t>> usesTable;
	vector<vector<int64_t>> usedVarTable;
	vector<vector<int64_t>> usesProcTable;
	vector<vector<int64_t>> usedProcVarTable;
	static bool instanceFlag;
	static Uses *uses;
	TypeTable *typeTable;
	VarTable *varTable;
	ProcTable *procTable;
	set<STMTNUM> usesList;
	set<VARINDEX> usedList;
	set<PROCINDEX> usesProcList;
	set<VARINDEX> usedProcList;
public:
	//! A constructor to initialize the Uses class.
	Uses(VarTable*);
	//! A destructor to clear all the tables and set the instance flag of the singleton class to false.
	~Uses();
	//! Returns the instance of Uses singleton class.
	static Uses* getInstance(VarTable*);	// to be used to get instance of singleton class
	
	//! Set the Uses relationship between a statement number and a variable name to be true.
	void setUses(STMTNUM, VARNAME);
	//! Set the Uses relationship between a statement number and a list of variable indexes to be true. Eliminate any duplicates
	void setUses(STMTNUM, set<VARINDEX>);
	//! Set the Uses relationship between a procedure index and a list of variable indexes to be true. Eliminate any duplicates
	void setUsesProc(PROCINDEX, set<VARINDEX>);

	//! If the Uses relationship between a statement number and a variable index is true, return true. Otherwise, return false.
	bool isUses(STMTNUM, VARINDEX);
	//! Return a set of all variable indexes that the given statement number has used. Return an empty set if not found.
	set<VARINDEX> getUsed(STMTNUM);
	//! Return a set of all statement numbers that has used the given variable index. Return an empty set if not found.
	set<STMTNUM> getUses(VARINDEX);
	//! Return a set of all variable indexes that have been used. Return an empty set if not found.
	set<VARINDEX> getAllUsed();
	//! Return a set of all statement numbers that has used any variables. Return an empty set if not found.
	set<STMTNUM> getAllUses();

	//! If the Uses relationship between a procedure index and a variable index is true, return true. Otherwise, return false.
	bool isUsesProc(PROCINDEX, VARINDEX);
	//! Return a set of all variable indexes that the given procedure index has used. Return an empty set if not found.
	set<VARINDEX> getUsedProc(PROCINDEX);
	//! Return a set of all procedure indexes that has used the given variable index. Return an empty set if not found.
	set<PROCINDEX> getUsesProc(VARINDEX);
	//! Return a set of all variable indexes that have been used. Return an empty set if not found.
	set<VARINDEX> getAllUsedProc();
	//! Return a set of all procedure indexes that has used any variables. Return an empty set if not found.
	set<PROCINDEX> getAllUsesProc();

	/// @cond
	void printUsesTable();
	/// @endcond
};

#endif