#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "PKB.h"

bool PKB::instanceFlag = false;
PKB* PKB::pkb = NULL; 

// void PKB() {
// }

PKB* PKB::getInstance() {
	if (!instanceFlag) {
		pkb = new PKB();
		instanceFlag = true; 
	}
	return pkb; 
}

VarTable* getVarTable() {
	return NULL;
}

ProcTable* getProcTable() {
	return NULL;
}

int PKB::setProcToAST(PROC p, Node* r) {
	return NULL;
}

Node* PKB::getRootAST (PROC p){
	return NULL;
}


PKB::~PKB() {
	instanceFlag = false;
}
