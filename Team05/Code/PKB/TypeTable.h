//@author Yohanes Lim
//TypeTable.h

#ifndef TYPETABLE_H
#define TYPETABLE_H

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <map>

using namespace std;
typedef int STMTNUM;

/*! \brief A TypeTable class to store the type of expression of a statement number from the source code.
 *  
 *
 * Overview: TypeTable is responsible to :
 * - Store all the type of expression of a statement number from the source code
 * - Allow speedy access to the required datas
 * 
 * TypeTable is a singleton class, it can be invoked using:
 * \code
 * static TypeTable* getInstance();
 * \endcode
 *
 */

class TypeTable {
public:
	enum SynType{ASSIGN, IF, WHILE, STMT, BOOLEAN, CALL, VARIABLE, CONSTANT, PROGLINE, PROCEDURE, INVALID};
	static SynType getSynType(std::string);
private:
	vector<SynType> typeMap;
	static bool instanceFlag;
	static TypeTable *typeTable;
public: 
	//! A constructor to initialize the TypeTable class.
	TypeTable();
	//! A destructor to clear all the tables and set the instance flag of the singleton class to false.
	~TypeTable();
	//! Returns the instance of TypeTable singleton class.
	static TypeTable* getInstance();	// to be used to get instance of singleton class 
	//! Insert a SynType to the given statement number.
	void insertStmtNumAndType(STMTNUM,SynType);
	//! Return the SynType given the statement number. If the statement number, return INVALID.
	SynType getType(STMTNUM);
	//! Return all the statement numbers given the SynType.
	vector<STMTNUM> getAllStmts(SynType);
	//! Return true if the given statement number has the given SynType.
	bool isType(SynType, STMTNUM); 

};

#endif