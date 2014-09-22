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
	modifies = Modifies::getInstance(typeTable,varTable,procTable);
	uses = Uses::getInstance(typeTable,varTable);
	calls = Calls::getInstance(procTable);
	next = Next::getInstance(typeTable);
	ASTRoot = NULL;
	CFGRoot = NULL;
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
	next->~Next();
	delete ASTRoot;
	delete CFGRoot;
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

Next* PKB::getNext(){
	return next;
}

unordered_map<PROCINDEX, vector<CALLSPAIR>> PKB::getCallsTable(){
	return calls->getCallsTable();
}

void PKB::setToVarTable(VARNAME v){
	varTable = getVarTable();
	varTable->insertVar(v);
}

void PKB::setToProcTable(PROCNAME p){
	procTable = getProcTable();
	procTable->insertProc(p);
}

void PKB::setToConstTable(CONSTVALUE c){
	constTable = getConstTable();
	constTable->insertConst(c);
}


void PKB::setToParent(STMTNUM s1, STMTNUM s2){
	parent = getParent();
	parent->setParent(s1,s2);
}

void PKB::setToFollows(STMTNUM s1, STMTNUM s2){
	follows = getFollows();
	follows->setFollows(s1,s2);
}

void PKB::setToModifies(STMTNUM s, VARNAME v){
	modifies = getModifies();
	modifies->setModifies(s,v);
}

void PKB::setToUses(STMTNUM s, VARNAME v){
	uses = getUses();
	uses->setUses(s,v);
}

void PKB::setToCalls(PROCNAME p1, PROCNAME p2, STMTNUM s){
	calls = getCalls();
	calls->setCalls(p1,p2,s);
}

void PKB::setToNext(STMTNUM s1, STMTNUM s2){
	next = getNext();
	next->setNext(s1,s2);
}

void PKB::setToTypeTable(STMTNUM s,TypeTable::SynType t){
	typeTable = getTypeTable();
	typeTable->insertStmtNumAndType(s,t);
}

void PKB::setASTRoot(Node* newASTRoot){
	ASTRoot = newASTRoot;
}

void PKB::setCFGRoot(Node* newCFGRoot){
	CFGRoot = newCFGRoot;
}

Node* PKB::getASTRoot(){
	return ASTRoot;
}

Node* PKB::getCFGRoot(){
	return CFGRoot;
}
