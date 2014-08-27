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
	Node* root; 
	string ASTNodeType = ASTNode.getType();
	if (ASTNodeType == "program") {
		root = new Node("program", "0");
		//CFGRoot = &currCFGNode;
	}

	// go through all children of current AST node 
	for (unsigned i=0;i<ASTNode.getChild().size();i++) {
		//currASTNode = *ASTRoot.getChild(i); 
		
	}
	return root;
}
