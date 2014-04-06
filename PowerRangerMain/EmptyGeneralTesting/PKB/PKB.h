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
#include "Parent.h"
#include "Follows.h"
#include "Node.h"
#include "Modifies.h"
#include "Uses.h"

using namespace std;

/* TO USE PKB:
	PKB *pkb;
	pkb = PKB::getInstance();
	pkb->method(); 
*/

class PKB {
private: 
	/*static bool instanceFlag;*/ 
	//static PKB *pkb;

	
	Node* ASTRoot;
	VarTable varTable;
	ProcTable procTable;
	TypeTable typeTable;
	Parent parent;
	Follows follows;
	Modifies modifies;
	Uses uses;
	
public:
	//static PKB* getInstance();	// to be used to get instance of singleton class 
	PKB();
	~PKB();

	VarTable getVarTable();
	ProcTable getProcTable();
	TypeTable getTypeTable();
	Parent getParent();
	Follows getFollows();
	Modifies getModifies();
	Uses getUses();
	Node* getASTRoot();

	void setVarTable(VarTable newVarTable);
	void setProcTable(ProcTable newProcTable);
	void setTypeTable(TypeTable newTypeTable);
	void setParent(Parent newParent);
	void setFollows(Follows newFollows);
	void setModifies(Modifies newModifies);
	void setUses(Uses newUses);
	void setASTRoot(Node* newASTRoot);
	
	void updateVarTable();
	void updateProcTable();
	void updateTypeTable();
};

#endif