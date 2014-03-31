#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "PKB.h"
using namespace std;



bool PKB::instanceFlag = false;
PKB* PKB::pkb = NULL;

PKB* PKB::getInstance() {
	pkb = new PKB();
	instanceFlag=true;
	return pkb; 
}



VarTable* PKB::getVarTable() {
	return NULL;
}

ProcTable* PKB::getProcTable() {
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
