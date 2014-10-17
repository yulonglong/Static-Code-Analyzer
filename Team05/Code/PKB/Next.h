//@author Yohanes Lim
//Next.h

#ifndef NEXT_H
#define NEXT_H

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <utility>
#include <iterator>
#include "TypeTable.h"

typedef int STMTNUM;

/*! \brief A Next class to store the Next relationship.
 *  
 * Overview: Next is responsible to :
 * - Store all the Next relationship between statement numbers
 * - Allow speedy access to the required datas
 * 
 * Next is a singleton class, it can be invoked using:
 * \code
 * static Next* getInstance(TypeTable*);
 * \endcode
 *
 */

class Next {
private:
	vector<vector<STMTNUM>> nextTable;
	vector<vector<STMTNUM>> previousTable;
	vector<vector<pair<STMTNUM,STMTNUM>>> nextPairTable;
	static bool instanceFlag;
	static Next *next;
	TypeTable *typeTable;
	set<STMTNUM> nextList;
	set<STMTNUM> previousList;
public:	
	//! A constructor to initialize the Next class.
	Next(TypeTable*);
	//! A destructor to clear all the tables and set the instance flag of the singleton class to false.
	~Next();
	//! Returns the instance of Next singleton class.
	static Next* getInstance(TypeTable*);	// to be used to get instance of singleton class 
	//! Set the Follows relationship between the two statement numbers to be true.
	void setNext(STMTNUM, STMTNUM);
	bool isNext(STMTNUM, STMTNUM);

	set<STMTNUM> getAllNext();
	set<STMTNUM> getAllPrevious();

	void setNextPair(STMTNUM, pair<STMTNUM,STMTNUM>);
	vector<pair<STMTNUM,STMTNUM>> getNextPair(STMTNUM);

	set<STMTNUM> getNext(STMTNUM);

	set<STMTNUM> getPrevious(STMTNUM);

	/// @cond
	//ADDITIONAL METHODS
	void printNextTable();
	void printNextTableForTesting();
	void printNextPairTableForTesting();
	/// @endcond
};

#endif