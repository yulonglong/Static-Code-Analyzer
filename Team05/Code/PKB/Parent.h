//@author Yohanes Lim
//Parent.h

#ifndef PARENT_H
#define PARENT_H

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iterator>
#include "TypeTable.h"


using namespace std;
typedef TypeTable::SynType SYNTYPE;

/*! \brief A Parent class to store the Parent relationship.
 *  
 * Overview: Parent is responsible to :
 * - Store all the Parent relationship between statement numbers
 * - Allow speedy access to the required datas
 * 
 * Parent is a singleton class, it can be invoked using:
 * \code
 * static Parent* getInstance(TypeTable*);
 * \endcode
 *
 */

class Parent {
private:
	unordered_map<STMTNUM,vector<STMTNUM>> parentTable; //given the stmtnum of the parent, return the children stmt num
	unordered_map<STMTNUM,STMTNUM> childrenTable; //given the stmtnum of the children, return the parent stmt num 
	static bool instanceFlag;
	static Parent *parent;
	TypeTable *typeTable; 
public: 
	//! A constructor to initialize the Parent class.
	Parent(TypeTable*);
	//! A destructor to clear all the tables and set the instance flag of the singleton class to false.
	~Parent();
	//! Returns the instance of Parent singleton class.
	static Parent* getInstance(TypeTable*);	// to be used to get instance of singleton class

	//! Set the Parent relationship between the two statement numbers to be true.
	void setParent(STMTNUM, STMTNUM);
	//! If the Parent relationship between the two statement names is true, return true. Otherwise, return false.
	bool isParent(STMTNUM, STMTNUM);	
	
	//! If the Parent relationship between a SynType and a statement numbers exists, return true. Otherwise, return false.
	bool isParent(SYNTYPE, STMTNUM); // Select BOOLEAN such that Parent(3,a)
	//! If the Child relationship between a SynType and a statement numbers exists, return true. Otherwise, return false.
	bool isChildren(SYNTYPE, STMTNUM);	 // Select BOOLEAN such that Parent(w,3)
	//! If the Parent relationship between the two SynType exists, return true. Otherwise, return false.
	bool isParent(SYNTYPE, SYNTYPE); // Select BOOLEAN such that Parent(w,a)

	//! Return a statement number which has the given first SynType and has a parent relationship with the given statement number.
	STMTNUM getParent(SYNTYPE, STMTNUM); 
	//! Return all statement number such that each statement number has the given first SynType and has a child relationship with the given statement number. Return an empty vector if not found.
	vector<STMTNUM> getChildren(SYNTYPE, STMTNUM); 
	//! Return all statement numbers such that the each statement number has the given first SynType and has a parent relationship with the given statement number which has the given second SynType. Return an empty vector if not found.
	vector<STMTNUM> getParent(SYNTYPE, SYNTYPE,STMTNUM); 
	//! Return all statement numbers such that the each statement number has the given first SynType and has a child relationship with the given statement number which has the given second SynType. Return an empty vector if not found.
	vector<STMTNUM> getChildren(SYNTYPE, SYNTYPE,STMTNUM);
	//! Return all statement numbers such that the each statement number has the given first SynType and has a parent relationship with a statement number which has the given second SynType. Return an empty vector if not found.
	vector<STMTNUM> getParent(SYNTYPE, SYNTYPE); // Select w such that Parent(w,a)
	//! Return all statement numbers such that the each statement number has the given first SynType and has a child relationship with a statement number which has the given second SynType. Return an empty vector if not found.
	vector<STMTNUM> getChildren(SYNTYPE, SYNTYPE); //Select a such that Parent(w,a)
	

	//For parentStar
	STMTNUM getParent(STMTNUM); 
	vector<STMTNUM> getChildren(STMTNUM); 
};

#endif