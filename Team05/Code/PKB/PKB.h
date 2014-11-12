//@author Yohanes Lim
//PKB.h


#ifndef PKB_H
#define PKB_H

#pragma once
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "ProcTable.h"
#include "VarTable.h"
#include "TypeTable.h"
#include "ConstTable.h"
#include "Parent.h"
#include "Follows.h"
#include "Node.h"
#include "Modifies.h"
#include "Uses.h"
#include "Calls.h"
#include "Next.h"
#include "Sibling.h"
#include "CFGNode.h"

/* TO USE PKB:
	PKB *pkb;
	pkb = PKB::getInstance();
	pkb->method(); 
*/

/*! \brief A PKB class to store all the datas needed for the program.
 *  
 *
 * Overview: CodeParser is responsible to :
 * - Store all the tables and relationships
 * - Allow speedy access to the required datas
 * 
 * PKB is a singleton class, it can be invoked using:
 * \code
 * static PKB* getInstance();
 * \endcode
 *
 * List of tables that PKB contains:
 * - VarTable
 * - ProcTable
 * - TypeTable
 * - ConstTable
 * 
 * List of relationships that PKB contains:
 * - Parent
 * - Follows
 * - Modifies
 * - Uses
 * - Calls
 * - Next
 * - Sibling
 *
 */

class PKB {
private: 
	static bool instanceFlag; 
	static PKB *pkb;	
	
	VarTable *varTable;
	ProcTable *procTable;
	TypeTable *typeTable;
	ConstTable *constTable;
	Parent *parent;
	Follows *follows;
	Modifies *modifies;
	Uses *uses;
	Calls *calls;
	Next *next;
	Sibling *sibling;
	Node* ASTRoot;
	CFGNode* CFGRoot; 
	
public:
	//! A constructor to initialize the PKB.
	PKB();
	//! A constructor to clear all the tables, relationships and other parameters.
	~PKB();
	//! Returns the instance of PKB singleton class.
	static PKB* getInstance();

	//! Set a variable to the variable table.
	void setToVarTable(VARNAME);
	//! Set a procedure to the procedure table.
	void setToProcTable(PROCNAME);
	//! Set a constant to the constant table.
	void setToConstTable(CONSTVALUE);
	//! Set a SynType to the statement number at the type table.
	void setToTypeTable(STMTNUM,TypeTable::SynType);
	//! Set a Parent relationship between the two given statement numbers.
	void setToParent(STMTNUM, STMTNUM);
	//! Set a Follows relationship between the two given statement numbers.
	void setToFollows(STMTNUM, STMTNUM);
	//! Set a Modifies relationship between the given statement number and variable name.
	void setToModifies(STMTNUM, VARNAME);
	//! Set a Modifies relationship between the given statement number and vector of variable indexes.
	void setToModifies(STMTNUM, set<VARINDEX>);
	//! Set a Modifies relationship between the given procedure index and vector of variable indexes.
	void setToModifiesProc(PROCINDEX, set<VARINDEX>);
	//! Set a Uses relationship between the given statement number and variable name.
	void setToUses(STMTNUM, VARNAME);
	//! Set a Uses relationship between the given statement number and vector of variable indexes.
	void setToUses(STMTNUM, set<VARINDEX>);
	//! Set a Uses relationship between the given procedure index and vector of variable indexes.
	void setToUsesProc(PROCINDEX, set<VARINDEX>);
	//! Set a Calls relationship between the two given procedure name at the specified statement number.
	void setToCalls(PROCNAME, PROCNAME, STMTNUM);
	//! Set a Next relationship between the two given statement numbers.
	void setToNext(STMTNUM, STMTNUM);
	//! Set the new AST Root.
	void setASTRoot(Node* newASTRoot);
	//! Set the new CFG Root.
	void setCFGRoot(CFGNode* newCFGRoot);

	//! Return the variable name given the variable index. If it is not found, return an empty string.
	VARNAME getVarName (VARINDEX);
	//! Return the variable index given the variable name. If it is not found, return an -1.
	VARINDEX getVarIndex (VARNAME);
	//! Return the total number of variables in the variable tables.
	int getNumVar(); 
	//! Return a set of all variable indexes in the variable tables.
	set<VARINDEX> getAllVarIndex();

	//! Return the procedure name given the procedure index. If it is not found, return an empty string.
	PROCNAME getProcName (PROCINDEX);
	//! Return the procedure index given the procedure name. If it is not found, return an -1.
	PROCINDEX getProcIndex (PROCNAME);
	//! Return the total number of procedures in the procedure tables. 
	int getNumProcedures(); 
	//! Return a set of all procedure indexes in the procedure tables.
	set<PROCINDEX> getAllProcIndexes();

	//! Return the constant value given the constant index. If it is not found, return an empty string.
	CONSTVALUE getConstValue (CONSTINDEX);
	//! Return the constant index given the constant value. If it is not found, return an -1.
	CONSTINDEX getConstIndex (CONSTVALUE);
	//! Return a set of all constant indexes in the constant tables.
	set<int> getAllConstIndex();

	//! Return the SynType given the statement number. If the statement number, return INVALID.
	TypeTable::SynType getSynType(STMTNUM);
	//! Return all the statement numbers given the SynType.
	set<STMTNUM> getAllStmts(TypeTable::SynType);
	//! Return true if the given statement number has the given SynType.
	bool isSynType(TypeTable::SynType, STMTNUM);
	//! Return the last statement number of the program. Return -1 if there is no source code
	STMTNUM getStmtRange(); 

	//! If the Calls relationship between the two procedure names is true, return true. Otherwise, return false.
	bool isCalls(PROCINDEX,PROCINDEX);
	//! Return a set of procedure indexes where the procedure index had called another procedure. Return an empty vector if not found.
	set<PROCINDEX> getAllCalls(); 
	//! Return a set of procedure indexes where the procedure index had called the given procedure index. Return an empty vector if not found.
	set<PROCINDEX> getCalls(PROCINDEX); 
	//! Return a set of procedure indexes where the procedure index had been called by another procedure. Return an empty vector if not found.
	set<PROCINDEX> getAllCalled(); 
	//! Return a set of procedure indexes where the procedure index had been called by the given procedure index. Return an empty vector if not found.
	set<PROCINDEX> getCalled(PROCINDEX); 
	//! Return a set of all statement numbers that contain the calls relationship under the given procedure index
	set<STMTNUM> getCallStmt(PROCINDEX);
	//! Return a set of all statement numbers that contain the call relationship
	set<STMTNUM> getAllCallStmt();


	//! If the Follows relationship between the two statement names is true, return true. Otherwise, return false.
	bool isFollows(STMTNUM, STMTNUM);	
	//! Return the statement number that s follows. Return -1 if not found.
	STMTNUM getFollows(STMTNUM);
	//! Return the statement number that s is followed by. Return -1 if not found.
	STMTNUM getFollowedBy(STMTNUM);
	//! Return a set of all statement numbers that follows another statement number.
	set<STMTNUM> getAllFollows();
	//! Return a set of all statement numbers that is followed by another statement number.
	set<STMTNUM> getAllFollowedBy();

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

	//! If the Modifies relationship between a statement number and a variable name is true, return true. Otherwise, return false.
	bool isModifies(STMTNUM, VARINDEX);	//Select w such that Modifies(1, "y")	
	//! Return a set of all variable indexes that the given statement number has modified. Return an empty set if not found.
	set<VARINDEX> getModified(STMTNUM);
	//! Return a set of all statement numbers that has modified the given variable index. Return an empty set if not found.
	set<STMTNUM> getModifies(VARINDEX);
	//! Return a set of all variable indexes that have been modified. Return an empty set if not found.
	set<VARINDEX> getAllModified();
	//! Return a set of all statement numbers that has modified any variables. Return an empty set if not found.
	set<STMTNUM> getAllModifies();

	//! If the Modifies relationship between a procedure index and a variable index is true, return true. Otherwise, return false.
	bool isModifiesProc(PROCINDEX, VARINDEX);
	//! Return a set of all variable indexes that the given procedure index has modified. Return an empty set if not found.
	set<VARINDEX> getModifiedProc(PROCINDEX);
	//! Return a set of all procedure indexes that has modified the given variable index. Return an empty set if not found.
	set<PROCINDEX> getModifiesProc(VARINDEX);
	//! Return a set of all variable indexes that have been modified. Return an empty set if not found.
	set<VARINDEX> getAllModifiedProc();
	//! Return a set of all procedure indexes that has modified any variables. Return an empty set if not found.
	set<PROCINDEX> getAllModifiesProc();

	//! If the Uses relationship between a statement number and a variable index is true, return true. Otherwise, return false.
	bool isUses(STMTNUM, VARINDEX);
	//! Return a set of all variable indexes that the given statement number has used. Return an empty set if not found.
	set<VARINDEX> getUsed(STMTNUM);
	//! Return a set of all statement numbers that has used the given variable index. Return an empty set if not found.
	set<STMTNUM> getUses(VARINDEX);
	//! Return a set of all variable indexes that have been used. Return an empty set if not found.
	set<VARINDEX> getAllUsed();
	//! Return a set of all statement numbers that has used any variables. Return an empty set if not found.
	set<STMTNUM> getAllUses();

	//! If the Uses relationship between a procedure index and a variable index is true, return true. Otherwise, return false.
	bool isUsesProc(PROCINDEX, VARINDEX);
	//! Return a set of all variable indexes that the given procedure index has used. Return an empty set if not found.
	set<VARINDEX> getUsedProc(PROCINDEX);
	//! Return a set of all procedure indexes that has used the given variable index. Return an empty set if not found.
	set<PROCINDEX> getUsesProc(VARINDEX);
	//! Return a set of all variable indexes that have been used. Return an empty set if not found.
	set<VARINDEX> getAllUsedProc();
	//! Return a set of all procedure indexes that has used any variables. Return an empty set if not found.
	set<PROCINDEX> getAllUsesProc();

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


	//Example = (1,(2,5)). If you need to insert two or more pairs, just call the insert method again. It will append the table
	//! Set the Next relationship between a statement number and a pair of statement numbers which represent the range of the Next relationship of the first statement number.
	void setToNextPair(STMTNUM, pair<STMTNUM,STMTNUM>);
	//! Return a vector of ranges that the given statement number will have a Next relationship with.
	vector<pair<STMTNUM,STMTNUM>> getNextPair(STMTNUM);

	//SIBLINGS
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
	VarTable* getVarTable(); 
	ProcTable* getProcTable(); 
	TypeTable* getTypeTable();
	ConstTable* getConstTable();
	Node* getASTRoot();
	CFGNode* getCFGRoot();
	unordered_map<PROCINDEX, vector<CALLSPAIR>> getCallsTable(); 
	/// @endcond
};

#endif