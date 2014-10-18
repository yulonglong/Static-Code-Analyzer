//@author Yohanes Lim
//ProcTable.h

#ifndef PROCTABLE_H
#define PROCTABLE_H

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <set>
#include <map>

using namespace std;
typedef int PROCINDEX;
typedef string PROCNAME; 

/*! \brief A ProcTable class to store the procedure names from the source code.
 *  
 *
 * Overview: ProcTable is responsible to :
 * - Store all the procedure names from the source code
 * - Assign each procedure name an unique procedure index
 * - Allow speedy access to the required datas
 * 
 * ProcTable is a singleton class, it can be invoked using:
 * \code
 * static ProcTable* getInstance();
 * \endcode
 *
 */

class ProcTable {
private: 
	map<PROCNAME,PROCINDEX> procedureMapTable;
	vector<PROCNAME> procedureTable;
	set<PROCINDEX> procIndexList;
	static bool instanceFlag;
	static ProcTable *procTable;
	int size;
public:
	//! A constructor to initialize the ProcTable class.
	ProcTable();
	//! A destructor to clear all the tables and set the instance flag of the singleton class to false.
	~ProcTable();
	//! Returns the instance of ProcTable singleton class.
	static ProcTable* getInstance();	// to be used to get instance of singleton class 
	//! Insert a procedure name to the constant table
	void insertProc(PROCNAME);
	//! Return the procedure name given the procedure index. If it is not found, return an empty string.
	PROCNAME getProcName (PROCINDEX);
	//! Return the procedure index given the procedure name. If it is not found, return an -1.
	PROCINDEX getProcIndex (PROCNAME);

	//! Return the total number of procedures in the procedure tables. 
	int getNumProcedures(); 
	//! Return a set of all procedure indexes in the procedure tables.
	set<PROCINDEX> getAllProcIndexes();
	
};

#endif