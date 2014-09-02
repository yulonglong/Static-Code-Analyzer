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

//unordered_map<PROCINDEX, vector<CALLSPAIR>> callsTable; 
// VarTable* varTable; 
// ProcTable* procTable; 

void extractorDriver(PKB *pkb) {
	TypeTable* typeTable = pkb->getTypeTable();
	ConstTable* constTable = pkb->getConstTable();
	Parent* parent = pkb->getParent();
	Follows* follows = pkb->getFollows();
	Modifies* modifies = pkb->getModifies();
	Uses* uses = pkb->getUses();
	VarTable* varTable = pkb->getVarTable();
	ProcTable* procTable = pkb->getProcTable();

	unordered_map<PROCINDEX, vector<CALLSPAIR>> callsTable; 
	callsTable = pkb->getCallsTable();

	// testing of callsTable
	for (auto it1 = callsTable.begin(); it1 != callsTable.end(); ++it1) {
		cout << it1->first  << ": "; 
		vector<CALLSPAIR> v = it1->second;
		for (vector<CALLSPAIR>::iterator it2 = v.begin(); it2 != v.end(); ++it2) {
			cout << "(" << it2->first << ", " << it2->second << ") ";
		}
		cout << endl; 
	}

	cout << "DE has obtained tables from PKB" << endl;
	
	Node* ASTRoot = pkb->getASTRoot();
	Node* CFGRoot = pkb->getCFGRoot();
	
	try {
		// cout << "Building CFG..." << endl;
		// CFGRoot = buildCFG(*ASTRoot);
		extractRelationships(*ASTRoot, callsTable);
	} catch (...) {
		cout << "Error in Design Extractor" << endl; 
	}

	// pkb->setCFGRoot(CFGRoot);
}


// extracting of modifies and uses relationship for procedures and statements.
// set the modifies and uses relationships for statements and procedures. 
void extractRelationships(Node &ASTRoot, unordered_map<PROCINDEX, vector<CALLSPAIR>> callsTable) {
	// Run DFS on callsTree to generate toposort queue
	queue<QueueItem> queueToProcess = runDFSDriver(callsTable); 

	// For each of the entries in the queue, dequeue and do the following 

	// For the procedure, find the min and max prog line 

	// Find all the variables modified, then set modifies relationship

	// Find all the varaibles used, then set uses relationship 
}

queue<QueueItem> runDFSDriver(unordered_map<PROCINDEX, vector<CALLSPAIR>> callsTable) {
	DFS(0, vector<int>(), callsTable);
}


void DFS(int source, vector<int> progLine, unordered_map<PROCINDEX, vector<CALLSPAIR>> callsTable) {
	for (int i=0; i<(int) callsTable.at(source).size(); i++) {
		vector<int> tempProgLine = progLine; 
		tempProgLine.push_back(callsTable.at(source).at(i).second);
		DFS(callsTable.at(source).at(i).first, tempProgLine, callsTable); 
	}
	// put into queue
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
