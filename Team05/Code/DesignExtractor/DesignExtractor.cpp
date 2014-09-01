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

vector<vector<pair<int, int>>> callsTree; 
std::queue<QueueItem> queueToProcess; 

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
		// cout << "Building CFG..." << endl;
		// CFGRoot = buildCFG(*ASTRoot);
		extractRelationships(*ASTRoot);
	} catch (...) {
		cout << "Error in Design Extractor" << endl; 
	}

	// pkb->setCFGRoot(CFGRoot);
}

// extracting of modifies and uses relationship for procedures and statements.
// set the modifies and uses relationships for statements and procedures. 
void extractRelationships(Node &ASTRoot) {
	// get callsTree from CFG

	// Run DFS on callsTree to generate toposort queue

	// For each of the entries in the queue, dequeue and do the following 

	// For the procedure, find the min and max prog line 

	// Find all the variables modified, then set modifies relationship

	// Find all the varaibles used, then set uses relationship 
}

/*
void DFS(int source, vector<int> progLine) {
	for (int i=0; i<(int) callsTree[source].size(); i++) {
		vector<int> tempProgLine = progLine; 
		tempProgLine.push_back(callsTree[source][i].second);
		DFS(callsTree[source][i].first, tempProgLine); 
	}
	// put into queue

}
*/


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
