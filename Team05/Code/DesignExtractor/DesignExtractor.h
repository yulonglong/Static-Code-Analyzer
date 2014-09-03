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
#include "PKB.h"
#include "QueueItem.h"


void extractorDriver(PKB* pkb);
void extractRelationships(Node &ASTRoot, unordered_map<PROCINDEX, vector<CALLSPAIR>> callsTable, ProcTable &procTable, Modifies &modifies, Uses &uses, Parent &parent);
void runDFSDriver(unordered_map<PROCINDEX, vector<CALLSPAIR>> callsTable);
void DFS(int source, vector<int> progLine, unordered_map<PROCINDEX, vector<CALLSPAIR>> callsTable);
Node* buildCFG(Node &ASTroot);

int getFirstProgLine(int procIndex, Node &ASTRoot, ProcTable &procTable);
int getLastProgLine(int procIndex, Node &ASTRoot, ProcTable &procTable);

void printCallsTable(unordered_map<PROCINDEX, vector<CALLSPAIR>> callsTable);
void printQueue();

#endif