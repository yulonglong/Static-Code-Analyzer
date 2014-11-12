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
#include "TypeTable.h"
#include "VarTable.h"
#include "ProcTable.h"
#include "ConstTable.h"

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
	vector<vector<STMTNUM>> siblingStmtNumStmtNumTable; 
	vector<vector<VARINDEX>> siblingVarIndexVarIndexTable; 
	vector<vector<CONSTINDEX>> siblingVarIndexConstantTable;
	vector<vector<VARINDEX>> siblingConstantVarIndexTable; 
	vector<vector<CONSTINDEX>> siblingConstantConstantTable; 
	vector<vector<int>> siblingVarIndexMathOpTable; 
	vector<vector<STMTNUM>> siblingMathOpVarIndexTable; 
	vector<vector<int>> siblingConstantMathOpTable; 
	vector<vector<STMTNUM>> siblingMathOpConstantTable; 
	vector<vector<int>> siblingMathOpMathOpTable; 
	vector<vector<PROCINDEX>> siblingProcIndexProcIndexTable; 
	vector<vector<STMTNUM>> siblingVarIndexStmtListTable;
	vector<vector<VARINDEX>> siblingStmtListVarIndexTable; 
	vector<vector<STMTNUM>> siblingStmtListStmtListTable;

	vector<bool> flagStmtNumStmtNumTable; 
	vector<bool> flagVarIndexVarIndexTable; 
	vector<bool> flagConstantConstantTable; 
	vector<bool> flagMathOpMathOpTable; 
	vector<bool> flagProcIndexProcIndexTable; 
	vector<bool> flagStmtListStmtListTable;

	vector<int> indexStmtNumStmtNumTable; 
	vector<int> indexVarIndexVarIndexTable; 
	vector<int> indexConstantConstantTable; 
	vector<int> indexMathOpMathOpTable; 
	vector<int> indexProcIndexProcIndexTable; 
	vector<int> indexStmtListStmtListTable;

	set<STMTNUM> siblingStmtNumStmtNumList; 
	set<VARINDEX> siblingVarIndexVarIndexList; 
	set<VARINDEX> siblingVarIndexConstantList; 
	set<CONSTINDEX> siblingConstantVarIndexList; 
	set<CONSTINDEX> siblingConstantConstantList; 
	set<VARINDEX> siblingVarIndexMathOpList; 
	set<int> siblingMathOpVarIndexList; 
	set<CONSTINDEX> siblingConstantMathOpList; 
	set<int> siblingMathOpConstantList;
	set<int> siblingMathOpMathOpList; 
	set<PROCINDEX> siblingProcIndexProcIndexList; 
	set<VARINDEX> siblingVarIndexStmtListList; 
	set<STMTNUM> siblingStmtListVarIndexList; 
	set<STMTNUM> siblingStmtListStmtListList; 


	VarTable *varTable;
	ProcTable *procTable;
	ConstTable *constTable;
	TypeTable *typeTable;
	static bool instanceFlag;
	static Sibling *sibling;
public: 
	//! A constructor to initialize the Sibling class.
	Sibling(VarTable*,ProcTable*,ConstTable*,TypeTable*);
	//! A destructor to clear all the tables and set the instance flag of the singleton class to false.
	~Sibling();
	//! Returns the instance of Sibling singleton class.
	static Sibling* getInstance(VarTable*,ProcTable*,ConstTable*,TypeTable*);	// to be used to get instance of singleton class

	//! Set the Sibling relationship between the two statement numbers to be true.
	//void setSibling(STMTNUM, STMTNUM);
	////! If the Sibling relationship between the two statement numbers is true, return true. Otherwise, return false.
	//bool isSibling(STMTNUM, STMTNUM);	
	////! Return a statement number that is the parent of the given statement number.
	//set<STMTNUM> getSibling(STMTNUM);
	////! Return a set of all statement numbers that has a sibling.
	//set<STMTNUM> getAllSibling();

	//! Set a Sibling relationship between the two given statement numbers.
	void setToSiblingStmtNumStmtNum(STMTNUM, STMTNUM);
	void setToSiblingVarNameVarName(VARNAME, VARNAME);
	void setToSiblingVarNameConstant(VARNAME, CONSTVALUE);
	void setToSiblingConstantConstant(CONSTVALUE, CONSTVALUE);
	void setToSiblingVarNameMathOp(VARNAME, TypeTable::SynType);
	void setToSiblingConstantMathOp(CONSTVALUE, TypeTable::SynType); 
	void setToSiblingMathOpMathOp(TypeTable::SynType, TypeTable::SynType);
	void setToSiblingProcNameProcName(PROCNAME, PROCNAME);
	void setToSiblingVarNameStmtList(VARNAME, STMTNUM);
	void setToSiblingStmtListStmtList(STMTNUM, STMTNUM);
	//! If the Sibling relationship between the two statement numbers is true, return true. Otherwise, return false.
	bool isSiblingStmtNumStmtNum(STMTNUM, STMTNUM);
	bool isSiblingVarIndexVarIndex(VARINDEX, VARINDEX);
	bool isSiblingVarIndexConstant(VARINDEX, CONSTINDEX);
	bool isSiblingConstantConstant(CONSTINDEX, CONSTINDEX);
	bool isSiblingVarIndexMathOp(VARINDEX, TypeTable::SynType);
	bool isSiblingConstantMathOp(CONSTINDEX, TypeTable::SynType); 
	bool isSiblingMathOpMathOp(TypeTable::SynType, TypeTable::SynType);
	bool isSiblingProcIndexProcIndex(PROCINDEX, PROCINDEX);
	bool isSiblingVarIndexStmtList(VARINDEX, STMTNUM);
	bool isSiblingStmtListStmtList(STMTNUM, STMTNUM);

	//! Return a statement number that is the parent of the given statement number.
	set<STMTNUM> getSiblingStmtNumWithStmtNum(STMTNUM);
	set<VARINDEX> getSiblingVarIndexWithVarIndex(VARINDEX);
	set<VARINDEX> getSiblingVarIndexWithConstant(CONSTINDEX);
	set<CONSTINDEX> getSiblingConstantWithVarIndex(VARINDEX);
	set<CONSTINDEX> getSiblingConstantWithConstant(CONSTINDEX);
	set<VARINDEX> getSiblingVarIndexWithMathOp(TypeTable::SynType);
	set<TypeTable::SynType> getSiblingMathOpWithVarIndex(VARINDEX);
	set<TypeTable::SynType> getSiblingMathOpWithConstant(CONSTINDEX);
	set<CONSTINDEX> getSiblingConstantWithMathOp(TypeTable::SynType);
	set<TypeTable::SynType> getSiblingMathOpWithMathOp(TypeTable::SynType);
	set<PROCINDEX> getSiblingProcIndexWithProcIndex(PROCINDEX);
	set<VARINDEX> getSiblingVarIndexWithStmtList(STMTNUM);
	set<STMTNUM> getSiblingStmtListWithVarIndex(VARINDEX);
	set<STMTNUM> getSiblingStmtListWithStmtList(STMTNUM);

	//! Return a set of all statement numbers that has a sibling.
	set<STMTNUM> getAllSiblingStmtNumWithStmtNum();
	set<VARINDEX> getAllSiblingVarIndexWithVarIndex();
	set<VARINDEX> getAllSiblingVarIndexWithConstant();
	set<CONSTINDEX> getAllSiblingConstantWithVarIndex();
	set<CONSTINDEX> getAllSiblingConstantWithConstant();
	set<VARINDEX> getAllSiblingVarIndexWithMathOp();
	set<TypeTable::SynType> getAllSiblingMathOpWithVarIndex();
	set<TypeTable::SynType> getAllSiblingMathOpWithConstant();
	set<CONSTINDEX> getAllSiblingConstantWithMathOp();
	set<TypeTable::SynType> getAllSiblingMathOpWithMathOp();
	set<PROCINDEX> getAllSiblingProcIndexWithProcIndex();
	set<VARINDEX> getAllSiblingVarIndexWithStmtList();
	set<STMTNUM> getAllSiblingStmtListWithVarIndex();
	set<STMTNUM> getAllSiblingStmtListWithStmtList();
	set<STMTNUM> getAllStmtList();

	/// @cond
	void printSiblingTable();
	/// @endcond
};

#endif