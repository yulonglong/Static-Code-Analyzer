//@author Yohanes Lim
//Parent.h

#ifndef PARENT_H
#define PARENT_H

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

/*! \brief A Parent class to store the Parent relationship.
 *  
 * Overview: Parent is responsible to :
 * - Store all the Parent relationship between statement numbers
 * - Allow speedy access to the required datas
 * 
 * Parent is a singleton class, it can be invoked using:
 * \code
 * static Parent* getInstance();
 * \endcode
 *
 */

class Parent {
private:
	vector<STMTNUM> childrenTable; //given the stmtnum of the children, return the parent stmt num 
	vector<vector<int64_t>> parentTable;
	set<STMTNUM> parentList;
	set<STMTNUM> childrenList;
	static bool instanceFlag;
	static Parent *parent;
public: 
	//! A constructor to initialize the Parent class.
	Parent();
	//! A destructor to clear all the tables and set the instance flag of the singleton class to false.
	~Parent();
	//! Returns the instance of Parent singleton class.
	static Parent* getInstance();	// to be used to get instance of singleton class

	//! Set the Parent relationship between the two statement numbers to be true.
	void setParent(STMTNUM, STMTNUM);
	//! If the Parent relationship between the two statement names is true, return true. Otherwise, return false.
	bool isParent(STMTNUM, STMTNUM);	
	//! Return a set of all statement numbers that is the children of the given statement number.
	set<STMTNUM> getChildren(STMTNUM);
	//! Return a statement number that is the parent of the given statement number. Return -1 if not found.
	STMTNUM getParent(STMTNUM);
	//! Return a set of all statement numbers that has children(s).
	set<STMTNUM> getAllChildren();
	//! Return a set of all statement numbers that has a parent.
	set<STMTNUM> getAllParent();

	
	/// @cond
	void printParentTable();
	/// @endcond
};

#endif