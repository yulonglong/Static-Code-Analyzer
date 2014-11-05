//@author Yohanes Lim
//Sibling.h

#ifndef SIBLING_H
#define SIBLING_H

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <cstdint>
#include <set>
#include <algorithm>
#include <iterator>


using namespace std;
typedef int STMTNUM;

/*! \brief A Sibling class to store the Sibling relationship.
 *  
 * Overview: Sibling is responsible to :
 * - Store all the Sibling relationship between statement numbers
 * - Allow speedy access to the required datas
 * 
 * Sibling is a singleton class, it can be invoked using:
 * \code
 * static Sibling* getInstance();
 * \endcode
 *
 */ 

class Sibling {
private:
	vector<vector<STMTNUM>> siblingTable; 
	vector<bool> flagTable;
	vector<int> indexTable;
	set<STMTNUM> siblingList;
	static bool instanceFlag;
	static Sibling *sibling;
public: 
	//! A constructor to initialize the Sibling class.
	Sibling();
	//! A destructor to clear all the tables and set the instance flag of the singleton class to false.
	~Sibling();
	//! Returns the instance of Sibling singleton class.
	static Sibling* getInstance();	// to be used to get instance of singleton class

	//! Set the Sibling relationship between the two statement numbers to be true.
	void setSibling(STMTNUM, STMTNUM);
	//! If the Sibling relationship between the two statement numbers is true, return true. Otherwise, return false.
	bool isSibling(STMTNUM, STMTNUM);	
	//! Return a statement number that is the parent of the given statement number.
	set<STMTNUM> getSibling(STMTNUM);
	//! Return a set of all statement numbers that has a sibling.
	set<STMTNUM> getAllSibling();

	
	/// @cond
	void printSiblingTable();
	/// @endcond
};

#endif