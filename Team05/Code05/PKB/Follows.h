//@author Yohanes Lim
//Follows.h

#ifndef FOLLOWS_H
#define FOLLOWS_H

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <iterator>

using namespace std;
typedef int STMTNUM;

/*! \brief A Follows class to store the Follows relationship.
 *  
 * Overview: Follows is responsible to :
 * - Store all the Follows relationship between statement numbers
 * - Allow speedy access to the required datas
 * 
 * Follows is a singleton class, it can be invoked using:
 * \code
 * static Follows* getInstance(TypeTable*);
 * \endcode
 *
 */

class Follows {
private: 
	vector<STMTNUM> followsTable;
	vector<STMTNUM> followedByTable;
	set<STMTNUM> followsList;
	set<STMTNUM> followedByList;
	static bool instanceFlag;
	static Follows *follows;
	
public: 
	//! A constructor to initialize the Follows class.
	Follows();
	//! A destructor to clear all the tables and set the instance flag of the singleton class to false.
	~Follows();
	//! Returns the instance of Calls singleton class.
	static Follows* getInstance();	// to be used to get instance of singleton class 

	//! Set the Follows relationship between the two statement numbers to be true.
	void setFollows(STMTNUM, STMTNUM);

	//! If the Follows relationship between the two statement names is true, return true. Otherwise, return false.
	bool isFollows(STMTNUM, STMTNUM);	

	//! Return the statement number that s follows. Return -1 if not found.
	STMTNUM getFollows(STMTNUM s);
	//! Return the statement number that s is followed by. Return -1 if not found.
	STMTNUM getFollowedBy(STMTNUM s);

	//! Return a set of all statement numbers that follows another statement number.
	set<STMTNUM> getAllFollows();
	//! Return a set of all statement numbers that is followed by another statement number.
	set<STMTNUM> getAllFollowedBy();

	/// @cond
	void printFollowsTable();
	/// @endcond
}; 

#endif