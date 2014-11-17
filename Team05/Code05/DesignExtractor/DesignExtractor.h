//@author Ipsita Mohapatra
//DesignExtractor.h

#pragma once
#ifndef DESIGNEXTRACTOR_H
#define DESIGNEXTRACTOR_H


#pragma once
#include <utility>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stack>
#include <queue>
#include <vector>
#include "Node.h"
#include "CFGNode.h"
#include "PKB.h"
#include "QueueItem.h"

using namespace std;

/*! \brief A set of methods to extract more design abstractions and store them in the PKB after the CodeParser has parsed the SIMPLE source program.
 * \ingroup 
 *
 * Overview: DesignExtractor is responsible for :
 * - Extracting modifies and uses relationships for multiple procedures. 
 * - Storing the extracted relationships in the Modifies and Uses tables in PKB.
 * - Building the CFG given the AST.
 * - Storing the Next relationships in the Next table in PKB.
 * - Extract the Sibling relationship from AST and store in PKB. 
 * 
 * To invoke the DesignExtractor's methods, use the public method:
 * \code
 * static void extractorDriver(PKB* pkb);
 * \endcode
 *
 * When extractorDriver() is called, the following methods are called which execute DesignExtractor's responsibilities:
 * \code
 * static void extractRelationships(Node &ASTRoot, unordered_map<PROCINDEX, vector<CALLSPAIR>> callsTable, ProcTable &procTable, Modifies &modifies, Uses &uses, Parent &parent);
 * static void buildCFGDriver(PKB &pkb, Node &ASTRoot, Node &CFGRoot);
 * static void extractSiblingRelationshipDriver(Node &ASTRoot, PKB &pkb);
 * \endcode
 *
 *
 *
 */

class DesignExtractor {
public:
	static void extractorDriver(PKB* pkb);

	static void extractRelationships(Node &ASTRoot, unordered_map<PROCINDEX, vector<CALLSPAIR>> callsTable, PKB &pkb);
	static void buildCFGDriver(PKB &pkb, Node &ASTRoot, Node &CFGRoot);
	static void extractSiblingRelationshipDriver(Node &ASTRoot, PKB &pkb);

private:	
	static void DesignExtractor::setSiblingforProcedures(vector<Node*> procNodes, PKB &pkb);
	static void DesignExtractor::setSiblingForStatements(vector<Node*> stmtNodes, PKB &pkb);
	static void DesignExtractor::setSiblingForAssign(vector<Node*> vector, PKB &pkb);
	static void DesignExtractor::setSiblingForIf(vector<Node*> vector, PKB &pkb);
	static void DesignExtractor::setSiblingForWhile(vector<Node*> vector, PKB &pkb);

	static void runDFSDriver(unordered_map<PROCINDEX, vector<CALLSPAIR>> callsTable, PKB &pkb);
	static vector<int> DFS(int source, vector<int> progLine, unordered_map<PROCINDEX, vector<CALLSPAIR>> callsTable, vector<int> visited);
	static void buildCFG(Node &ASTroot, PKB &pkb);
	static void setNextRelationshipDriver(PKB &pkb);
	static void setNextRelationship(CFGNode &node, PKB &pkb);
	static void setNextPairRelationship(PKB &pkb);
	static pair<int, int> findPair(int fromIndex, PKB &pkb);
	static void createCFGForStmtLst(Node &ASTNode, PKB &pkb);
	static void createCFGForAssign(int progLine, PKB &pkb);
	static void createCFGForCall(int progLine, PKB &pkb);
	static void createCFGForWhile(vector<Node*> children, PKB &pkb);
	static void createCFGForIf(vector<Node*> children, PKB &pkb);
	static void createNewNodeAndAttachToCFG(string type, int progLine, PKB &pkb);
	static CFGNode* getCFGNode(int progLine);
	// traverse graph to look for CFGNode with given progLine 
	static void traverseGraph(CFGNode &node, int progLine);

	static int getFirstProgLine(int procIndex, Node &ASTRoot, PKB &pkb);
	static int getLastProgLine(int procIndex, Node &ASTRoot, PKB &pkb);

	static void clear(std::queue<QueueItem> &q);
	static void printCallsTable(unordered_map<PROCINDEX, vector<CALLSPAIR>> callsTable);
	static void printQueue();

	static string DesignExtractor::printVariables(set<int> v, PKB &pkb);

};
#endif