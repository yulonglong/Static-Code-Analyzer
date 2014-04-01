#ifndef PKB_H
#define PKB_H

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "Node.h"

typedef short PROC;
using namespace std;

class VarTable;  // no need to #include "VarTable.h" as all I need is pointer
class ProcTable;
class TypeTable;

class PKB {
private: 
	static bool instanceFlag; 
	static PKB *pkb;
	PKB(){} // private constructor 


public:
	static PKB* getInstance(); 
	VarTable* getVarTable();
	ProcTable* getProcTable();

	VarTable* varTable; 
	int setProcToAST(PROC p, Node* r);
	
	Node* getRootAST(PROC p);


	~PKB();
};

#endif