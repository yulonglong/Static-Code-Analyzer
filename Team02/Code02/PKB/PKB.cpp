#pragma once

#include "PKB.h"

bool PKB::instanceFlag=false;
PKB* PKB::pkb=NULL;


PKB::PKB(){
	varTable = VarTable::getInstance();
	procTable = ProcTable::getInstance();
	typeTable = TypeTable::getInstance();
	constTable = ConstTable::getInstance();
	parent = Parent::getInstance(typeTable);
	follows = Follows::getInstance(typeTable);
	modifies = Modifies::getInstance(typeTable,varTable);
	uses = Uses::getInstance(typeTable,varTable);
	calls = Calls::getInstance(procTable);
}

PKB::~PKB(){
	varTable->~VarTable();
	procTable->~ProcTable();
	typeTable->~TypeTable();
	constTable->~ConstTable();
	parent->~Parent();
	follows->~Follows();
	modifies->~Modifies();
	uses->~Uses();
	calls->~Calls();
	instanceFlag=false;
}


PKB* PKB::getInstance() {
	if(!instanceFlag)
    {
        pkb = new PKB();
        instanceFlag = true;
        return pkb;
    }
    else
    {
        return pkb;
    }
}


VarTable* PKB::getVarTable(){
	return varTable;
}

ProcTable* PKB::getProcTable(){
	return procTable;
}

TypeTable* PKB::getTypeTable(){
	return typeTable;
}

ConstTable* PKB::getConstTable(){
	return constTable;
}

Parent* PKB::getParent(){
	return parent;
}

Follows* PKB::getFollows(){
	return follows;
}

Modifies* PKB::getModifies(){
	return modifies;
}

Uses* PKB::getUses(){
	return uses;
}

Calls* PKB::getCalls(){
	return calls;
}

Node* PKB::getASTRoot(){
	return ASTRoot;
}

void PKB::setASTRoot(Node* newASTRoot){
	ASTRoot = newASTRoot;
}

Node* PKB::getCFGRoot(){
	return CFGRoot;
}

void PKB::setCFGRoot(Node* newCFGRoot){
	CFGRoot = newCFGRoot;
}