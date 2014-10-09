//@author Yohanes Lim
//Uses.h

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
	unordered_map<STMTNUM, vector<VARINDEX>> usesTable;
	unordered_map<PROCINDEX, vector<VARINDEX>> usesProcTable;
	static bool instanceFlag;
	static Uses *uses;
	TypeTable *typeTable;
	VarTable *varTable;
	ProcTable *procTable;
public:
	//! A constructor to initialize the Uses class.
	Uses(TypeTable*, VarTable*, ProcTable*);
	//! A destructor to clear all the tables and set the instance flag of the singleton class to false.
	~Uses();
	//! Returns the instance of Uses singleton class.
	static Uses* getInstance(TypeTable*,VarTable*,ProcTable*);	// to be used to get instance of singleton class
	//! Set the Uses relationship between a statement number and a variable name to be true.
	void setUses(STMTNUM, VARNAME);
	//! If the Uses relationship between a statement number and a variable name is true, return true. Otherwise, return false.
	bool isUses(STMTNUM, VARNAME);	//Select boolean such that Uses(1, "y")

	bool isUses(STMTNUM, VARINDEX);
	vector<VARINDEX> getUsed(STMTNUM);
	vector<STMTNUM> getUses(VARINDEX);
	vector<VARINDEX> getAllUsed();
	vector<STMTNUM> getAllUses();

	bool isUsesProc(PROCINDEX, VARINDEX);
	vector<VARINDEX> getUsedProc(PROCINDEX);
	vector<PROCINDEX> getUsesProc(VARINDEX);
	vector<VARINDEX> getAllUsedProc();
	vector<PROCINDEX> getAllUsesProc();




	//! Return all statement numbers such that each statement number has the given SynType and uses any variable. Return an empty vector if not found.
	vector<STMTNUM> getUses(SYNTYPE);//Select a such that Uses(a, v); 
	//! Return all variable indexes such that each variable index is used in the given statement number. Return an empty vector if not found.
	//vector<VARINDEX> getUses(STMTNUM);		//Select v such that Uses(1, v)	return variable indexes.
	//! Return all statement numbers such that each statement number has the given SynType and uses the given variable name. Return an empty vector if not found.
	vector<STMTNUM> getUses(SYNTYPE, VARNAME);	//Select a such that Uses(a, "x")	return empty vector if doesn't exist
	
	//! Set the Uses relationship between a statement number and a list of variable indexes to be true. Eliminate any duplicates
	void setUses(STMTNUM, vector<VARINDEX>);
	//! Set the Uses relationship between a procedure index and a list of variable indexes to be true. Eliminate any duplicates
	void setUsesProc(PROCINDEX, vector<VARINDEX>); 
	//! Return all the variable indexes such that each variable index is used by the given procedure index. Return an empty vector if not found.
	//vector<VARINDEX> getUsesProc(PROCINDEX); //for getting using procedure index
	
	//! Return all the procedure indexes such that each procedure index uses the given variable. Return an empty vector if not found.
	vector<PROCINDEX> getUsesProcVar(VARNAME);
	//! If the Uses relationship between a procedure name and a variable name is true, return true. Otherwise, return false.
	bool isUsesProc(PROCNAME, VARNAME);

	/// @cond
	void printUsesTable();
	/// @endcond
};

#endif