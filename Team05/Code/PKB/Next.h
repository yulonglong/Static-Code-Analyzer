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
 * static Next* getInstance();
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
	set<STMTNUM> nextList;
	set<STMTNUM> previousList;
public:	
	//! A constructor to initialize the Next class.
	Next();
	//! A destructor to clear all the tables and set the instance flag of the singleton class to false.
	~Next();
	//! Returns the instance of Next singleton class.
	static Next* getInstance();	// to be used to get instance of singleton class 
	//! Set the Next relationship between the two statement numbers to be true.
	void setNext(STMTNUM, STMTNUM);
	//! Set the Next relationship between a statement number and a pair of statement numbers which represent the range of the Next relationship of the first statement number.
	void setNextPair(STMTNUM, pair<STMTNUM,STMTNUM>);

	//! If the Next relationship between the two numbers is true, return true. Otherwise, return false.
	bool isNext(STMTNUM, STMTNUM);
	//! Return a set of all statement numbers that will be executed after the given statement number in the same nesting level in a CFG.
	set<STMTNUM> getNext(STMTNUM);
	//! Return a set of all statement numbers that will be executed before the given statement number in the same nesting level in a CFG.
	set<STMTNUM> getPrevious(STMTNUM);
	//! Return a set of all statement numbers that has another statement number after it in a CFG.
	set<STMTNUM> getAllNext();
	//! Return a set of all statement numbers that has another statement number before it in a CFG.
	set<STMTNUM> getAllPrevious();
	//! Return a vector of ranges that the given statement number will have a Next relationship with.
	vector<pair<STMTNUM,STMTNUM>> getNextPair(STMTNUM);

	/// @cond
	//ADDITIONAL METHODS
	void printNextTable();
	void printNextTableForTesting();
	void printNextPairTableForTesting();
	/// @endcond
};

#endif