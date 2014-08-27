//@author Ipsita Mohapatra
//DesignExtractor.cpp

#pragma once

#include "DesignExtractor.h"
using namespace std;

int counter = -1;
Node* rootCFGNode;
Node* currASTNode;
Node* currCFGNode;
// Node* CFGRoot;
// Node* ASTRoot;

void extractorDriver(PKB *pkb) {
	VarTable* varTable = pkb->getVarTable();
	ProcTable* procTable = pkb->getProcTable();
	TypeTable* typeTable = pkb->getTypeTable();
	ConstTable* constTable = pkb->getConstTable();
	Parent* parent = pkb->getParent();
	Follows* follows = pkb->getFollows();
	Modifies* modifies = pkb->getModifies();
	Uses* uses = pkb->getUses();

	Node* ASTRoot = pkb->getASTRoot();
	Node* CFGRoot = pkb->getCFGRoot();
	
	try {
		cout << "Building CFG..." << endl;
		CFGRoot = buildCFG(*ASTRoot);
	} catch (...) {
		cout << "Error in building CFG" << endl; 
	}

	pkb->setCFGRoot(CFGRoot);
}

// actual building of CFG 
Node* buildCFG(Node &ASTNode) {
	currASTNode = &ASTNode; 
	counter++; 

	string ASTNodeType = ASTNode.getType();
	if (ASTNodeType == "program") {
		currCFGNode = new Node("program", counter);
		rootCFGNode = currCFGNode;
	} else if (ASTNodeType == "procedure") {
		cout << "this is a procedure" << endl; 
	} else {
		cout << "yay!" << endl; 
	}

	// go through all children of current AST node 
	for (unsigned i=0;i<ASTNode.getChild().size();i++) {
		currCFGNode = buildCFG(*ASTNode.getChild(i));	
	}
	return currCFGNode;
}
