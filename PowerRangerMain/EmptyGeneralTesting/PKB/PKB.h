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

	
	
	VarTable varTable;
	ProcTable procTable;
	TypeTable typeTable;
	Parent parent;
	Follows follows;
	
public:
	//static PKB* getInstance();	// to be used to get instance of singleton class 
	PKB();
	~PKB();

	VarTable getVarTable();
	ProcTable getProcTable();
	TypeTable getTypeTable();
	Parent getParent();
	Follows getFollows();

	void setVarTable(VarTable newVarTable);
	void setProcTable(ProcTable newProcTable);
	void setTypeTable(TypeTable newTypeTable);
	void setParent(Parent newParent);
	void setFollows(Follows newFollows);
	
};

#endif