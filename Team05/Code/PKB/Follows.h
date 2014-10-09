//@author Yohanes Lim
//Follows.h

#ifndef FOLLOWS_H
#define FOLLOWS_H

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <iterator>
#include "TypeTable.h"

using namespace std;
typedef TypeTable::SynType SYNTYPE;
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
	unordered_map<STMTNUM,STMTNUM> followsTable;
	unordered_map<STMTNUM,STMTNUM> followedByTable;
	static bool instanceFlag;
	static Follows *follows;
	TypeTable *typeTable; // public for the sake of unit testing
	
public: 
	//! A constructor to initialize the Follows class.
	Follows(TypeTable*);
	//! A destructor to clear all the tables and set the instance flag of the singleton class to false.
	~Follows();
	//! Returns the instance of Calls singleton class.
	static Follows* getInstance(TypeTable*);	// to be used to get instance of singleton class 

	//! Set the Follows relationship between the two statement numbers to be true.
	void setFollows(STMTNUM, STMTNUM);
	//! If the Follows relationship between the two statement names is true, return true. Otherwise, return false.
	bool isFollows(STMTNUM, STMTNUM);	

	STMTNUM getFollows(STMTNUM s);
	STMTNUM getFollowedBy(STMTNUM s);

	vector<STMTNUM> getAllFollows();
	vector<STMTNUM> getAllFollowedBy();
	

	//! If the Follows relationship between a SynType and a statement numbers exists, return true. Otherwise, return false.
	bool isFollows(SYNTYPE, STMTNUM);	
	//! If the FollowedBy relationship between a SynType and a statement numbers exists, return true. Otherwise, return false.
	bool isFollowedBy(SYNTYPE, STMTNUM);	
	//! If the Follows relationship between the two SynType is true, return true. Otherwise, return false.
	bool isFollows(SYNTYPE, SYNTYPE);

	//! Return the statement number that follows the given statement number and has the given SynType.
	STMTNUM getFollows(SYNTYPE, STMTNUM);	
	//! Return the statement number that is followed by the given statement number and has the given SynType.
	STMTNUM getFollowedBy(SYNTYPE, STMTNUM); 
	//! Return all statement numbers such that each statement number has the given first SynType and follows the given second SynType. Return an empty vector if not found.
	vector<STMTNUM> getFollows(SYNTYPE, SYNTYPE);	 //Select s1 such that getFollows(s1, s2)
	//! Return all statement numbers such that each statement number has the given first SynType and are followed by the given second SynType. Return an empty vector if not found.
	vector<STMTNUM> getFollowedBy(SYNTYPE, SYNTYPE);	 //Select s2 such that getFollows(s1, s2)

	/// @cond
	void printFollowsTable();
	/// @endcond
}; 

#endif