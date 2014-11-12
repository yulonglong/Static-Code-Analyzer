//@author Yohanes Lim
//ConstTable.h

#ifndef CONSTTABLE_H
#define CONSTTABLE_H

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <set>
#include <map>

using namespace std;
typedef int CONSTINDEX;
typedef string CONSTVALUE; 

/*! \brief A ConstTable class to store the constants from the source code.
 *  
 *
 * Overview: ConstTable is responsible to :
 * - Store all the constants from the source code
 * - Assign each constant an unique index
 * - Allow speedy access to the required datas
 * 
 * ConstTable is a singleton class, it can be invoked using:
 * \code
 * static ConstTable* getInstance();
 * \endcode
 *
 */

class ConstTable {
private: 
	map<CONSTVALUE,CONSTINDEX> constantMapTable;
	vector<CONSTVALUE> constantTable;
	set<CONSTINDEX> constIndexList;
	static bool instanceFlag;
	static ConstTable *constTable;
public:
	//! A constructor to initialize the ConstTable class.
	ConstTable();
	//! A destructor to clear all the tables and set the instance flag of the singleton class to false.
	~ConstTable();
	//! Returns the instance of ConstTable singleton class.
	static ConstTable* getInstance();
	//! Insert a constant value to the constant table
	void insertConst(CONSTVALUE);
	//! Return the constant value given the constant index. If it is not found, return an empty string.
	CONSTVALUE getConst (CONSTINDEX);
	//! Return the constant index given the constant value. If it is not found, return an -1.
	CONSTINDEX getConstIndex (CONSTVALUE);

	//! Return a set of all constant indexes in the constant tables.
	set<CONSTINDEX> getAllConstIndex();

};

#endif