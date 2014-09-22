
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
#include <queue>
#include <vector>
#include "Node.h"
#include "CFGNode.h"
#include "PKB.h"
#include "QueueItem.h"

using namespace std;

/*! \brief A set of methods to extract more relationships after the CodeParser has parsed the SIMPLE source program.
 * \ingroup 
 * 
 * 
 */

void extractorDriver(PKB* pkb);

void extractRelationships(Node &ASTRoot, unordered_map<PROCINDEX, vector<CALLSPAIR>> callsTable, ProcTable &procTable, Modifies &modifies, Uses &uses, Parent &parent);
void runDFSDriver(unordered_map<PROCINDEX, vector<CALLSPAIR>> callsTable);
void DFS(int source, vector<int> progLine, unordered_map<PROCINDEX, vector<CALLSPAIR>> callsTable);
void buildCFGDriver(PKB &pkb, Node &ASTRoot, Node &CFGRoot);
void buildCFG(Node &ASTroot, PKB &pkb);
void createCFGForStmtLst(Node &ASTNode, PKB &pkb);
void createCFGForAssign(int progLine, PKB &pkb);
void createCFGForCall(int progLine, PKB &pkb);
void createCFGForWhile(vector<Node*> children, PKB &pkb);
void createCFGForIf(vector<Node*> children, PKB &pkb);
void createNewNodeAndAttachToCFG(string type, int progLine, PKB &pkb);
CFGNode* getCFGNode(int progLine);
void traverseGraph(CFGNode &node, int progLine);

int getFirstProgLine(int procIndex, Node &ASTRoot, ProcTable &procTable);
int getLastProgLine(int procIndex, Node &ASTRoot, ProcTable &procTable);

void clear(std::queue<QueueItem> &q);
void printCallsTable(unordered_map<PROCINDEX, vector<CALLSPAIR>> callsTable);
void printQueue();

#endif