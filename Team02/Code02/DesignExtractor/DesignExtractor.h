//@author Ipsita Mohapatra
//DesignExtractor.h

#pragma once
#ifndef DESIGNEXTRACTOR_H
#define DESIGNEXTRACTOR_H

#pragma once
#include <string>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stack>
#include <vector>
#include "Node.h"
#include "PKB.h"

class DesignExtractor{
private:
	// Node* currASTNode;
	// Node* currCFGNode;
	// Node* CFGRoot;
	// Node* ASTRoot;
	int progLineCounter; 

public:
	
};

void extractorDriver(PKB* pkb);
Node* buildCFG(Node &ASTroot);
	
#endif