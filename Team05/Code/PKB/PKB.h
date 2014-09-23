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
	//! Set a Uses relationship between the given statement number and variable name.
	void setToUses(STMTNUM, VARNAME);
	//! Set a Calls relationship between the two given procedure name at the specified statement number.
	void setToCalls(PROCNAME, PROCNAME, STMTNUM);
	//! Set a Next relationship between the two given statement numbers.
	void setToNext(STMTNUM, STMTNUM);
	//! Set the new AST Root.
	void setASTRoot(Node* newASTRoot);
	//! Set the new CFG Root.
	void setCFGRoot(CFGNode* newCFGRoot);


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
	Node* getASTRoot();
	CFGNode* getCFGRoot();

	unordered_map<PROCINDEX, vector<CALLSPAIR>> getCallsTable();
};

#endif