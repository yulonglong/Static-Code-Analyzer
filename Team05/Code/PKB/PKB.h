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
	int getNumVar(); 
	set<VARINDEX> getAllVarIndex();

	//! Return the procedure name given the procedure index. If it is not found, return an empty string.
	PROCNAME getProcName (PROCINDEX);
	//! Return the procedure index given the procedure name. If it is not found, return an -1.
	PROCINDEX getProcIndex (PROCNAME);
	int getNumProcedures(); 
	set<PROCINDEX> getAllProcIndexes();

	//! Return the constant value given the constant index. If it is not found, return an empty string.
	CONSTVALUE getConstValue (CONSTINDEX);
	//! Return the constant index given the constant value. If it is not found, return an -1.
	CONSTINDEX getConstIndex (CONSTVALUE);
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
	set<PROCINDEX> getAllCalls(); 
	set<PROCINDEX> getCalls(PROCINDEX); 	
	set<PROCINDEX> getAllCalled(); 
	set<PROCINDEX> getCalled(PROCINDEX);

	//! If the Follows relationship between the two statement names is true, return true. Otherwise, return false.
	bool isFollows(STMTNUM, STMTNUM);	
	STMTNUM getFollows(STMTNUM);	
	STMTNUM getFollowedBy(STMTNUM); 
	set<STMTNUM> getAllFollows();	 //Select s1 such that getFollows(s1, s2)
	set<STMTNUM> getAllFollowedBy();

	bool isParent(STMTNUM, STMTNUM);
	set<STMTNUM> getAllChildren(); 
	set<STMTNUM> getChildren(STMTNUM);
	set<STMTNUM> getAllParent();
	STMTNUM getParent(STMTNUM); 

	//! If the Modifies relationship between a statement number and a variable name is true, return true. Otherwise, return false.
	bool isModifies(STMTNUM, VARINDEX);	//Select w such that Modifies(1, "y")	
	set<VARINDEX> getModified(STMTNUM);
	set<STMTNUM> getModifies(VARINDEX); 
	set<VARINDEX> getAllModified();
	set<STMTNUM> getAllModifies();

	bool isModifiesProc(PROCINDEX, VARINDEX);	//Select w such that Modifies(1, "y")	
	set<VARINDEX> getModifiedProc(PROCINDEX);
	set<PROCINDEX> getModifiesProc(VARINDEX); 
	set<VARINDEX> getAllModifiedProc();
	set<PROCINDEX> getAllModifiesProc();

	bool isUses(STMTNUM, VARINDEX);	//Select w such that Modifies(1, "y")	
	set<VARINDEX> getUsed(STMTNUM);
	set<STMTNUM> getUses(VARINDEX); 
	set<VARINDEX> getAllUsed();
	set<STMTNUM> getAllUses();

	bool isUsesProc(PROCINDEX, VARINDEX);	//Select w such that Modifies(1, "y")	
	set<VARINDEX> getUsedProc(PROCINDEX);
	set<PROCINDEX> getUsesProc(VARINDEX); 
	set<VARINDEX> getAllUsedProc();
	set<PROCINDEX> getAllUsesProc();

	bool isNext(STMTNUM, STMTNUM);
	set<STMTNUM> getNext(STMTNUM);
	set<STMTNUM> getPrevious(STMTNUM);
	set<STMTNUM> getAllNext();
	set<STMTNUM> getAllPrevious();
	//printNextTable(); ??

	//Example = (1,(2,5)). If you need to insert two or more pairs, just call the insert method again. It will append the table
	void setToNextPair(STMTNUM, pair<STMTNUM,STMTNUM>);
	vector<pair<STMTNUM,STMTNUM>> getNextPair(STMTNUM);

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
	/// @endcond
};

#endif