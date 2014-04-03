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
	static bool instanceFlag; 
	static PKB *pkb;

	PKB();
	
	VarTable varTable;
	ProcTable procTable;
	TypeTable typeTable;
	Parent parent;
	Follows follows;
	
public:
	static PKB* getInstance();	// to be used to get instance of singleton class 
	
	~PKB();

	VarTable getVarTable();
	ProcTable getProcTable();
	TypeTable getTypeTable();
	Parent getParent();
	Follows getFollows();
	
};

#endif