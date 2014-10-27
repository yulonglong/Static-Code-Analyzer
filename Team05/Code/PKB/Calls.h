//@author Yohanes Lim
//Calls.h

#ifndef CALLS_H
#define CALLS_H

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <cstdint>
#include <algorithm>
#include <iterator>
#include "ProcTable.h"

/* Represents the statement number of the source code */
typedef int STMTNUM;
/* The pair of procedure index being called and the statement number where it is called */
typedef pair<PROCINDEX,STMTNUM> CALLSPAIR;

/*! \brief A Calls class to store the calls relationship.
 *  
 *
 * Overview: Calls is responsible to :
 * - Store all the Calls relationship between procedures
 * - Allow speedy access to the required datas
 * 
 * Calls is a singleton class, it can be invoked using:
 * \code
 * static Calls* getInstance(ProcTable*);
 * \endcode
 *
 */

class Calls {
private:
	unordered_map<PROCINDEX, vector<CALLSPAIR>> callsPairTable;
	vector<vector<int64_t>> callsTable;
	vector<vector<int64_t>> calledByTable;
	static bool instanceFlag;
	static Calls *calls;
	ProcTable *procTable;
	set<PROCINDEX> callsList;
	set<PROCINDEX> calledList;
	set<STMTNUM> callStmtNumList;

public:	
	//! A constructor to initialize the Calls class.
	Calls(ProcTable*);
	//! A destructor to clear all the tables and set the instance flag of the singleton class to false.
	~Calls();
	//! Returns the instance of Calls singleton class.
	static Calls* getInstance(ProcTable*);	// to be used to get instance of singleton class 

	//! Set the Calls relationship between the two procedure names to be true at the specified statement number.
	void setCalls(PROCNAME, PROCNAME, STMTNUM);

	//! If the Calls relationship between the two procedure indexes is true, return true. Otherwise, return false.
	bool isCalls(PROCINDEX,PROCINDEX);

	//! Return a vector of procedure indexes where the procedure index had called another procedure. Return an empty vector if not found.
	set<PROCINDEX> getAllCalls(); //Calls(p,q) Select p, return empty if not found
	//! Return a vector of procedure indexes where the procedure index had called the given procedure index. Return an empty vector if not found.
	set<PROCINDEX> getCalls(PROCINDEX); //Calls (p, "Second") Select p, return empty if not found
	//! Return a vector of procedure indexes where the procedure index had been called by another procedure. Return an empty vector if not found.
	set<PROCINDEX> getAllCalled(); //Calls(p,q) Select q, return empty if not found
	//! Return a vector of procedure indexes where the procedure index had been called by the given procedure index. Return an empty vector if not found.
	set<PROCINDEX> getCalled(PROCINDEX); //Calls("First", q) Select q, return empty if not found

	//! Return a set of all statement numbers that contain the call relationship
	set<STMTNUM> getAllCallStmt();

	/// @cond
	unordered_map<PROCINDEX, vector<CALLSPAIR>> getCallsTable();

	void printCallsTable();
	void printCallsPairTable();
	/// @endcond
};

#endif