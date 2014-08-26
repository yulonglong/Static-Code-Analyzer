//@author Ipsita Mohapatra
//DesignExtractor.cpp

#pragma once

#include "DesignExtractor.h"
using namespace std;


void extractorDriver(PKB *pkb) {
	VarTable* varTable = pkb->getVarTable();
	ProcTable* procTable = pkb->getProcTable();
	TypeTable* typeTable = pkb->getTypeTable();
	ConstTable* constTable = pkb->getConstTable();
	Parent* parent = pkb->getParent();
	Follows* follows = pkb->getFollows();
	Modifies* modifies = pkb->getModifies();
	Uses* uses = pkb->getUses();

	Node* ASTroot = pkb->getASTRoot();
	// Node* CFGroot = pkb->getCFGRoot();

	//CFGroot = buildCFG(*ASTroot);
}

// actual building of CFG 
Node* buildCFG(Node &ASTroot) {}
