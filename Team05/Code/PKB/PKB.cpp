#pragma once

#include "PKB.h"

bool PKB::instanceFlag=false;
PKB* PKB::pkb=NULL;


PKB::PKB(){
	varTable = VarTable::getInstance();
	procTable = ProcTable::getInstance();
	typeTable = TypeTable::getInstance();
	constTable = ConstTable::getInstance();
	parent = Parent::getInstance();
	follows = Follows::getInstance();
	modifies = Modifies::getInstance(varTable);
	uses = Uses::getInstance(varTable);
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
	ASTRoot = NULL;
	CFGRoot = NULL;
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

void PKB::setToModifies(STMTNUM s, set<VARINDEX> v){
	modifies = getModifies();
	modifies->setModifies(s,v);
}

void PKB::setToModifiesProc(PROCINDEX i, set<VARINDEX> v){
	modifies = getModifies();
	modifies->setModifiesProc(i,v);
}

void PKB::setToUses(STMTNUM s, VARNAME v){
	uses = getUses();
	uses->setUses(s,v);
}

void PKB::setToUses(STMTNUM s, set<VARINDEX> v){
	uses = getUses();
	uses->setUses(s,v);
}

void PKB::setToUsesProc(PROCINDEX i, set<VARINDEX> v){
	uses = getUses();
	uses->setUsesProc(i,v);
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

void PKB::setCFGRoot(CFGNode* newCFGRoot){
	CFGRoot = newCFGRoot;
}

Node* PKB::getASTRoot(){
	return ASTRoot;
}

CFGNode* PKB::getCFGRoot(){
	return CFGRoot;
}

VARNAME PKB::getVarName (VARINDEX i){
	return varTable->getVarName(i);
}

VARINDEX PKB::getVarIndex (VARNAME n){
	return varTable->getVarIndex(n);
}

int PKB::getNumVar(){
	return varTable->getNumVar();
}

set<VARINDEX> PKB::getAllVarIndex(){
	return varTable->getAllVarIndex();
}

PROCNAME PKB::getProcName (PROCINDEX i){
	return procTable->getProcName(i);
}

PROCINDEX PKB::getProcIndex (PROCNAME n){
	return procTable->getProcIndex(n);
}

int PKB::getNumProcedures(){
	return procTable->getNumProcedures();
}

set<PROCINDEX> PKB::getAllProcIndexes(){
	return procTable->getAllProcIndexes();
}

CONSTVALUE PKB::getConstValue (CONSTINDEX i){
	return constTable->getConst(i);
}

CONSTINDEX PKB::getConstIndex (CONSTVALUE v){
	return constTable->getConstIndex(v);
}

set<int> PKB::getAllConstIndex(){
	return constTable->getAllConstIndex();
}

TypeTable::SynType PKB::getSynType(STMTNUM s){
	return typeTable->getType(s);
}

set<STMTNUM> PKB::getAllStmts(TypeTable::SynType t){
	return typeTable->getAllStmts(t);
}

bool PKB::isSynType(TypeTable::SynType t, STMTNUM s){
	return typeTable->isType(t,s);
}

STMTNUM PKB::getStmtRange(){
	return typeTable->getStmtRange();
}

bool PKB::isCalls(PROCINDEX p1,PROCINDEX p2){
	return calls->isCalls2(p1,p2);
}

set<PROCINDEX> PKB::getAllCalls(){
	return calls->getCalls();
}

set<PROCINDEX> PKB::getCalls(PROCINDEX p){
	return calls->getCalls2(p);
}

set<PROCINDEX> PKB::getAllCalled(){
	return calls->getCalled();
}

set<PROCINDEX> PKB::getCalled(PROCINDEX p){
	return calls->getCalled2(p);
}

bool PKB::isFollows(STMTNUM s1, STMTNUM s2){
	return follows->isFollows(s1,s2);
}

STMTNUM PKB::getFollows(STMTNUM s){
	return follows->getFollows(s);
}
	
STMTNUM PKB::getFollowedBy(STMTNUM s){
	return follows->getFollowedBy(s);
}

set<STMTNUM> PKB::getAllFollows(){
	return follows->getAllFollows();
}

set<STMTNUM> PKB::getAllFollowedBy(){
	return follows->getAllFollowedBy();
}


bool PKB::isParent(STMTNUM s1, STMTNUM s2){
	return parent->isParent(s1,s2);
}

set<STMTNUM> PKB::getAllChildren(){
	return parent->getAllChildren();
}

set<STMTNUM> PKB::getChildren(STMTNUM s){
	return parent->getChildren(s);
}

set<STMTNUM> PKB::getAllParent(){
	return parent->getAllParent();
}

STMTNUM PKB::getParent(STMTNUM s){
	return parent->getParent(s);
}


bool PKB::isModifies(STMTNUM s, VARINDEX i){
	return modifies->isModifies(s, i);
}

set<VARINDEX> PKB::getModified(STMTNUM s){
	return modifies->getModified(s);
}

set<STMTNUM> PKB::getModifies(VARINDEX i){
	return modifies->getModifies(i);
}

set<VARINDEX> PKB::getAllModified(){
	return modifies->getAllModified();
}

set<STMTNUM> PKB::getAllModifies(){
	return modifies->getAllModifies();
}


bool PKB::isModifiesProc(PROCINDEX s, VARINDEX p){
	return modifies->isModifiesProc(s,p);
}

set<VARINDEX> PKB::getModifiedProc(PROCINDEX i){
	return modifies->getModifiedProc(i);
}

set<PROCINDEX> PKB::getModifiesProc(VARINDEX i){
	return modifies->getModifiesProc(i);
}

set<VARINDEX> PKB::getAllModifiedProc(){
	return modifies->getAllModifiedProc();
}

set<PROCINDEX> PKB::getAllModifiesProc(){
	return modifies->getAllModifiesProc();
}

bool PKB::isUses(STMTNUM s, VARINDEX i){
	return uses->isUses(s, i);
}

set<VARINDEX> PKB::getUsed(STMTNUM s){
	return uses->getUsed(s);
}

set<STMTNUM> PKB::getUses(VARINDEX i){
	return uses->getUses(i);
}
set<VARINDEX> PKB::getAllUsed(){
	return uses->getAllUsed();
}
set<STMTNUM> PKB::getAllUses(){
	return uses->getAllUses();
}

bool PKB::isUsesProc(PROCINDEX s, VARINDEX i){
	return uses->isUsesProc(s, i);
}
set<VARINDEX> PKB::getUsedProc(PROCINDEX i){
	return uses->getUsedProc(i);
}
set<PROCINDEX> PKB::getUsesProc(VARINDEX i){
	return uses->getUsesProc(i);
}
set<VARINDEX> PKB::getAllUsedProc(){
	return uses->getAllUsedProc();
}
set<PROCINDEX> PKB::getAllUsesProc(){
	return uses->getAllUsesProc();
}

bool PKB::isNext(STMTNUM s1, STMTNUM s2){
	return next->isNext(s1,s2);
}

set<STMTNUM> PKB::getNext(STMTNUM s){
	return next->getNext(s);
}
set<STMTNUM> PKB::getPrevious(STMTNUM s){
	return next->getPrevious(s);
}
set<STMTNUM> PKB::getAllNext(){
	return next->getAllNext();
}
set<STMTNUM> PKB::getAllPrevious(){
	return next->getAllPrevious();
}

void PKB::setToNextPair(STMTNUM s, pair<STMTNUM,STMTNUM> p){
	next->setNextPair(s,p);
}

vector<pair<STMTNUM,STMTNUM>> PKB::getNextPair(STMTNUM s){
	return next->getNextPair(s);
}