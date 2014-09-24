//@author Yohanes Lim
//Next.h

#ifndef NEXT_H
#define NEXT_H

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
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
	unordered_map<STMTNUM, vector<STMTNUM>> nextTable;
	unordered_map<STMTNUM, STMTNUM> previousTable;
	static bool instanceFlag;
	static Next *next;
	TypeTable *typeTable;

public:	
	//! A constructor to initialize the Next class.
	Next(TypeTable*);
	//! A destructor to clear all the tables and set the instance flag of the singleton class to false.
	~Next();
	//! Returns the instance of Next singleton class.
	static Next* getInstance(TypeTable*);	// to be used to get instance of singleton class 
	//! Set the Follows relationship between the two statement numbers to be true.
	void setNext(STMTNUM, STMTNUM);

	//Temp method. lacie give me the correct one please
	vector<STMTNUM> getNext(STMTNUM);
	//Temp method. lacie give me the correct one please
	STMTNUM getPrevious(STMTNUM);

	//ADDITIONAL METHODS
	bool isNext(STMTNUM, STMTNUM);

};

#endif