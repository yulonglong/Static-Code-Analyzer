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

using namespace std;

/* TO USE PKB:
	PKB *pkb;
	pkb = PKB::getInstance();
	pkb->method(); 
*/

class PKB {
private: 
	static bool instanceFlag; 
	static PKB *pkb;	
	Node* ASTRoot;
	VarTable *varTable;
	ProcTable *procTable;
	TypeTable *typeTable;
	ConstTable *constTable;
	Parent *parent;
	Follows *follows;
	Modifies *modifies;
	Uses *uses;
	Calls *calls;
	Node* CFGRoot; 
	
public:
	PKB();
	~PKB();
	static PKB* getInstance();	// to be used to get instance of singleton class 

	VarTable* getVarTable();
	ProcTable* getProcTable();
	TypeTable* getTypeTable();
	ConstTable* getConstTable();
	Parent* getParent();
	Follows* getFollows();
	Modifies* getModifies();
	Uses* getUses();
	Calls* getCalls();
	Node* getASTRoot();
	Node* getCFGRoot();

	void setASTRoot(Node* newASTRoot);
	void setCFGRoot(Node* newCFGRoot);

};

#endif