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
	vector<bool> flagProcIndexProcIndexTable; 
	vector<bool> flagStmtListStmtListTable;

	vector<int> indexStmtNumStmtNumTable; 
	vector<int> indexVarIndexVarIndexTable; 
	vector<int> indexConstantConstantTable; 
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
	set<STMTNUM> siblingAllStmtList; 


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

	//! Set a Sibling relationship between the two given statement numbers to be true.
	void setToSiblingStmtNumStmtNum(STMTNUM, STMTNUM);
	//! Set a Sibling relationship between the two given variable names to be true.
	void setToSiblingVarNameVarName(VARNAME, VARNAME);
	//! Set a Sibling relationship between the given variable name and constant value to be true.
	void setToSiblingVarNameConstant(VARNAME, CONSTVALUE);
	//! Set a Sibling relationship between the two given constant values to be true.
	void setToSiblingConstantConstant(CONSTVALUE, CONSTVALUE);
	//! Set a Sibling relationship between the given variable name and math operator to be true.
	void setToSiblingVarNameMathOp(VARNAME, TypeTable::SynType);
	//! Set a Sibling relationship between the given constant value and math operator to be true.
	void setToSiblingConstantMathOp(CONSTVALUE, TypeTable::SynType); 
	//! Set a Sibling relationship between the two given math operators to be true.
	void setToSiblingMathOpMathOp(TypeTable::SynType, TypeTable::SynType);
	//! Set a Sibling relationship between the two given procedure names to be true.
	void setToSiblingProcNameProcName(PROCNAME, PROCNAME);
	//! Set a Sibling relationship between the given variable name and statement list to be true.
	void setToSiblingVarNameStmtList(VARNAME, STMTNUM);
	//! Set a Sibling relationship between the two given statement lists to be true.
	void setToSiblingStmtListStmtList(STMTNUM, STMTNUM);
	//! Store the list of all statment list.
	void setToSiblingAllStmtList(STMTNUM);

	//! If the Sibling relationship between the two statement numbers is true, return true. Otherwise, return false.
	bool isSiblingStmtNumStmtNum(STMTNUM, STMTNUM);
	//! If the Sibling relationship between the two variable indexes is true, return true. Otherwise, return false.
	bool isSiblingVarIndexVarIndex(VARINDEX, VARINDEX);
	//! If the Sibling relationship between the variable index and constant index is true, return true. Otherwise, return false.
	bool isSiblingVarIndexConstant(VARINDEX, CONSTINDEX);
	//! If the Sibling relationship between the two constant indexes is true, return true. Otherwise, return false.
	bool isSiblingConstantConstant(CONSTINDEX, CONSTINDEX);
	//! If the Sibling relationship between the variable index and math operator is true, return true. Otherwise, return false.
	bool isSiblingVarIndexMathOp(VARINDEX, TypeTable::SynType);
	//! If the Sibling relationship between the constant index and math operator is true, return true. Otherwise, return false.
	bool isSiblingConstantMathOp(CONSTINDEX, TypeTable::SynType); 
	//! If the Sibling relationship between the two math operators is true, return true. Otherwise, return false.
	bool isSiblingMathOpMathOp(TypeTable::SynType, TypeTable::SynType);
	//! If the Sibling relationship between the two procedure indexes is true, return true. Otherwise, return false.
	bool isSiblingProcIndexProcIndex(PROCINDEX, PROCINDEX);
	//! If the Sibling relationship between the given variable index and statement list is true, return true. Otherwise, return false.
	bool isSiblingVarIndexStmtList(VARINDEX, STMTNUM);
	//! If the Sibling relationship between the two statement lists is true, return true. Otherwise, return false.
	bool isSiblingStmtListStmtList(STMTNUM, STMTNUM);

	//! Return a set of statement numbers that is the sibling of the given statement number.
	set<STMTNUM> getSiblingStmtNumWithStmtNum(STMTNUM);
	//! Return a set of variable indexes that is the sibling of the given variable index.
	set<VARINDEX> getSiblingVarIndexWithVarIndex(VARINDEX);
	//! Return a set of variable indexes that is the sibling of the given constant index.
	set<VARINDEX> getSiblingVarIndexWithConstant(CONSTINDEX);
	//! Return a set of constant indexes that is the sibling of the given variable index.
	set<CONSTINDEX> getSiblingConstantWithVarIndex(VARINDEX);
	//! Return a set of constant indexes that is the sibling of the given constant index.
	set<CONSTINDEX> getSiblingConstantWithConstant(CONSTINDEX);
	//! Return a set of variable indexes that is the sibling of the given math operator.
	set<VARINDEX> getSiblingVarIndexWithMathOp(TypeTable::SynType);
	//! Return a set of math operators that is the sibling of the given variable index.
	set<TypeTable::SynType> getSiblingMathOpWithVarIndex(VARINDEX);
	//! Return a set of math operators that is the sibling of the given constant index.
	set<TypeTable::SynType> getSiblingMathOpWithConstant(CONSTINDEX);
	//! Return a set of constant indexes that is the sibling of the given math operator.
	set<CONSTINDEX> getSiblingConstantWithMathOp(TypeTable::SynType);
	//! Return a set of math operators that is the sibling of the given math operator.
	set<TypeTable::SynType> getSiblingMathOpWithMathOp(TypeTable::SynType);
	//! Return a set of procedure indexes that is the sibling of the given procedure index.
	set<PROCINDEX> getSiblingProcIndexWithProcIndex(PROCINDEX);
	//! Return a set of variable indexes that is the sibling of the given statement list.
	set<VARINDEX> getSiblingVarIndexWithStmtList(STMTNUM);
	//! Return a set of statement lists that is the sibling of the given variable index.
	set<STMTNUM> getSiblingStmtListWithVarIndex(VARINDEX);
	//! Return a set of statement lists that is the sibling of the given statement list.
	set<STMTNUM> getSiblingStmtListWithStmtList(STMTNUM);

	//! Return a set of all statement numbers that has a sibling of statement number.
	set<STMTNUM> getAllSiblingStmtNumWithStmtNum();
	//! Return a set of all variable indexes that has a sibling of variable index.
	set<VARINDEX> getAllSiblingVarIndexWithVarIndex();
	//! Return a set of all variable indexes that has a sibling of constant index.
	set<VARINDEX> getAllSiblingVarIndexWithConstant();
	//! Return a set of all constant indexes that has a sibling of variable index.
	set<CONSTINDEX> getAllSiblingConstantWithVarIndex();
	//! Return a set of all constant indexes that has a sibling of constant index.
	set<CONSTINDEX> getAllSiblingConstantWithConstant();
	//! Return a set of all variable indexes that has a sibling of math operator.
	set<VARINDEX> getAllSiblingVarIndexWithMathOp();
	//! Return a set of all math operators that has a sibling of variable index.
	set<TypeTable::SynType> getAllSiblingMathOpWithVarIndex();
	//! Return a set of all math operators that has a sibling of constant index.
	set<TypeTable::SynType> getAllSiblingMathOpWithConstant();
	//! Return a set of all constant indexes that has a sibling of operator.
	set<CONSTINDEX> getAllSiblingConstantWithMathOp();
	//! Return a set of all math operators that has a sibling of operator.
	set<TypeTable::SynType> getAllSiblingMathOpWithMathOp();
	//! Return a set of all procedure indexes that has a sibling of procedure index.
	set<PROCINDEX> getAllSiblingProcIndexWithProcIndex();
	//! Return a set of all variable indexes that has a sibling of statement list.
	set<VARINDEX> getAllSiblingVarIndexWithStmtList();
	//! Return a set of all statement lists that has a sibling of variable index.
	set<STMTNUM> getAllSiblingStmtListWithVarIndex();
	//! Return a set of all statement lists that has a sibling of statement list.
	set<STMTNUM> getAllSiblingStmtListWithStmtList();
	//! Return a set of all statement lists inside the source.
	set<STMTNUM> getAllStmtList();

	/// @cond
	void printSiblingTable();
	/// @endcond
};

#endif