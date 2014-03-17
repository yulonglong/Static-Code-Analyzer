#ifndef PKB_H
#define PKB_H

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "Node.h"

typedef short PROC;

class VarTable;  // no need to #include "VarTable.h" as all I need is pointer

class PKB {
public:
	static VarTable* varTable; 
	static int setProcToAST(PROC p, Node* r);
	static Node* getRootAST (PROC p);

};

#endif