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
	STMTNUM getFollows(STMTNUM s);
	//! Return the statement number that s is followed by. Return -1 if not found.
	STMTNUM getFollowedBy(STMTNUM s);
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
	bool isSiblingVarNameVarName(VARNAME, VARNAME);
	bool isSiblingVarNameConstant(VARNAME, CONSTVALUE);
	bool isSiblingConstantConstant(CONSTVALUE, CONSTVALUE);
	bool isSiblingVarNameMathOp(VARNAME, TypeTable::SynType);
	bool isSiblingConstantMathOp(CONSTVALUE, TypeTable::SynType); 
	bool isSiblingMathOpMathOp(TypeTable::SynType, TypeTable::SynType);
	bool isSiblingProcNameProcName(PROCNAME, PROCNAME);
	bool isSiblingVarNameStmtList(VARNAME, STMTNUM);
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

	/// @cond
	VarTable* getVarTable(); 
	ProcTable* getProcTable(); 
	TypeTable* getTypeTable();
	ConstTable* getConstTable();
	Parent* getParent();
	Follows* getFollows();
	Modifies* getModifies();
	Uses* getUses();
	Calls* getCalls();
	Next* getNext();
	Node* getASTRoot(); // do not delete this method from PKB.h (DE needs)
	CFGNode* getCFGRoot(); // do not delete this method from PKB.h (DE needs)

	unordered_map<PROCINDEX, vector<CALLSPAIR>> getCallsTable(); // do not delete this method from PKB.h
	void printNextTable();
	void printNextTableForTesting();
	void printNextPairTableForTesting();
	void printCallsPairTable();
	/// @endcond
};

#endif