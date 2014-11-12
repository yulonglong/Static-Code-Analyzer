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
	sibling = Sibling::getInstance(varTable,procTable,constTable,typeTable);
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
	sibling->~Sibling();
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
	return calls->isCalls(p1,p2);
}

set<PROCINDEX> PKB::getAllCalls(){
	return calls->getAllCalls();
}

set<PROCINDEX> PKB::getCalls(PROCINDEX p){
	return calls->getCalls(p);
}

set<PROCINDEX> PKB::getAllCalled(){
	return calls->getAllCalled();
}

set<PROCINDEX> PKB::getCalled(PROCINDEX p){
	return calls->getCalled(p);
}

set<STMTNUM> PKB::getCallStmt(PROCINDEX p){
	return calls->getCallStmt(p);
}

set<STMTNUM> PKB::getAllCallStmt(){
	return calls->getAllCallStmt();
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

void PKB::setToSiblingStmtNumStmtNum(STMTNUM s1, STMTNUM s2){
	sibling->setToSiblingStmtNumStmtNum(s1,s2);
}

void PKB::setToSiblingVarNameVarName(VARNAME v1, VARNAME v2){
	sibling->setToSiblingVarNameVarName(v1,v2);
}

void PKB::setToSiblingVarNameConstant(VARNAME v, CONSTVALUE cv){
	sibling->setToSiblingVarNameConstant(v,cv);
}

void PKB::setToSiblingConstantConstant(CONSTVALUE cv1, CONSTVALUE cv2){
	sibling->setToSiblingConstantConstant(cv1,cv2);
}

void PKB::setToSiblingVarNameMathOp(VARNAME v, TypeTable::SynType t){
	sibling->setToSiblingVarNameMathOp(v,t);
}

void PKB::setToSiblingConstantMathOp(CONSTVALUE cv, TypeTable::SynType t){ 
	sibling->setToSiblingConstantMathOp(cv,t);
}

void PKB::setToSiblingMathOpMathOp(TypeTable::SynType t1, TypeTable::SynType t2){
	sibling->setToSiblingMathOpMathOp(t1,t2);
}

void PKB::setToSiblingProcNameProcName(PROCNAME p1, PROCNAME p2){
	sibling->setToSiblingProcNameProcName(p1,p2);
}

void PKB::setToSiblingVarNameStmtList(VARNAME v, STMTNUM s){
	sibling->setToSiblingVarNameStmtList(v,s);
}

void PKB::setToSiblingStmtListStmtList(STMTNUM s1, STMTNUM s2){
	sibling->setToSiblingStmtListStmtList(s1,s2);
}

bool PKB::isSiblingStmtNumStmtNum(STMTNUM s1, STMTNUM s2){
	return sibling->isSiblingStmtNumStmtNum(s1,s2);
}

bool PKB::isSiblingVarIndexVarIndex(VARINDEX v1, VARINDEX v2){
	return sibling->isSiblingVarIndexVarIndex(v1,v2);
}
bool PKB::isSiblingVarIndexConstant(VARINDEX v, CONSTINDEX cv){
	return sibling->isSiblingVarIndexConstant(v,cv);
}
bool PKB::isSiblingConstantConstant(CONSTINDEX cv1, CONSTINDEX cv2){
	return sibling->isSiblingConstantConstant(cv1,cv2);
}
bool PKB::isSiblingVarIndexMathOp(VARINDEX v, TypeTable::SynType t){
	return sibling->isSiblingVarIndexMathOp(v,t);
}
bool PKB::isSiblingConstantMathOp(CONSTINDEX cv, TypeTable::SynType t){ 
	return sibling->isSiblingConstantMathOp(cv,t);
}
bool PKB::isSiblingMathOpMathOp(TypeTable::SynType t1, TypeTable::SynType t2){
	return sibling->isSiblingMathOpMathOp(t1,t2);
}
bool PKB::isSiblingProcIndexProcIndex(PROCINDEX p1, PROCINDEX p2){
	return sibling->isSiblingProcIndexProcIndex(p1,p2);
}
bool PKB::isSiblingVarIndexStmtList(VARINDEX v, STMTNUM s){
	return sibling->isSiblingVarIndexStmtList(v,s);
}
bool PKB::isSiblingStmtListStmtList(STMTNUM s1, STMTNUM s2){
	return sibling->isSiblingStmtListStmtList(s1,s2);
}
	//! Return a statement number that is the parent of the given statement number.
set<STMTNUM> PKB::getSiblingStmtNumWithStmtNum(STMTNUM s){
	return sibling->getSiblingStmtNumWithStmtNum(s);
}
set<VARINDEX> PKB::getSiblingVarIndexWithVarIndex(VARINDEX v){
	return sibling->getSiblingVarIndexWithVarIndex(v);
}
set<VARINDEX> PKB::getSiblingVarIndexWithConstant(CONSTINDEX c){
	return sibling->getSiblingVarIndexWithConstant(c);
}
set<CONSTINDEX> PKB::getSiblingConstantWithVarIndex(VARINDEX v){
	return sibling->getSiblingConstantWithVarIndex(v);
}
set<CONSTINDEX> PKB::getSiblingConstantWithConstant(CONSTINDEX c){
	return sibling->getSiblingConstantWithConstant(c);
}
set<VARINDEX> PKB::getSiblingVarIndexWithMathOp(TypeTable::SynType t){
	return sibling->getSiblingVarIndexWithMathOp(t);
}
set<TypeTable::SynType> PKB::getSiblingMathOpWithVarIndex(VARINDEX v){
	return sibling->getSiblingMathOpWithVarIndex(v);
}
set<TypeTable::SynType> PKB::getSiblingMathOpWithConstant(CONSTINDEX c){
	return sibling->getSiblingMathOpWithConstant(c);
}
set<CONSTINDEX> PKB::getSiblingConstantWithMathOp(TypeTable::SynType t){
	return sibling->getSiblingConstantWithMathOp(t);
}
set<TypeTable::SynType> PKB::getSiblingMathOpWithMathOp(TypeTable::SynType t){
	return sibling->getSiblingMathOpWithMathOp(t);
}
set<PROCINDEX> PKB::getSiblingProcIndexWithProcIndex(PROCINDEX p){
	return sibling->getSiblingProcIndexWithProcIndex(p);
}
set<VARINDEX> PKB::getSiblingVarIndexWithStmtList(STMTNUM s){
	return sibling->getSiblingVarIndexWithStmtList(s);
}
set<STMTNUM> PKB::getSiblingStmtListWithVarIndex(VARINDEX v){
	return sibling->getSiblingStmtListWithVarIndex(v);
}
set<STMTNUM> PKB::getSiblingStmtListWithStmtList(STMTNUM s){
	return sibling->getSiblingStmtListWithStmtList(s);
}

set<STMTNUM> PKB::getAllSiblingStmtNumWithStmtNum(){
	return sibling->getAllSiblingStmtNumWithStmtNum();
}
set<VARINDEX> PKB::getAllSiblingVarIndexWithVarIndex(){
	return sibling->getAllSiblingVarIndexWithVarIndex();
}
set<VARINDEX> PKB::getAllSiblingVarIndexWithConstant(){
	return sibling->getAllSiblingVarIndexWithConstant();
}
set<CONSTINDEX> PKB::getAllSiblingConstantWithVarIndex(){
	return sibling->getAllSiblingConstantWithVarIndex();
}
set<CONSTINDEX> PKB::getAllSiblingConstantWithConstant(){
	return sibling->getAllSiblingConstantWithConstant();
}
set<VARINDEX> PKB::getAllSiblingVarIndexWithMathOp(){
	return sibling->getAllSiblingVarIndexWithMathOp();
}
set<TypeTable::SynType> PKB::getAllSiblingMathOpWithVarIndex(){
	return sibling->getAllSiblingMathOpWithVarIndex();
}
set<TypeTable::SynType> PKB::getAllSiblingMathOpWithConstant(){
	return sibling->getAllSiblingMathOpWithConstant();
}
set<CONSTINDEX> PKB::getAllSiblingConstantWithMathOp(){
	return sibling->getAllSiblingConstantWithMathOp();
}
set<TypeTable::SynType> PKB::getAllSiblingMathOpWithMathOp(){
	return sibling->getAllSiblingMathOpWithMathOp();
}
set<PROCINDEX> PKB::getAllSiblingProcIndexWithProcIndex(){
	return sibling->getAllSiblingProcIndexWithProcIndex();
}
set<VARINDEX> PKB::getAllSiblingVarIndexWithStmtList(){
	return sibling->getAllSiblingVarIndexWithStmtList();
}
set<STMTNUM> PKB::getAllSiblingStmtListWithVarIndex(){
	return sibling->getAllSiblingStmtListWithVarIndex();
}
set<STMTNUM> PKB::getAllSiblingStmtListWithStmtList(){
	return sibling->getAllSiblingStmtListWithStmtList();
}

set<STMTNUM> PKB::getAllStmtList(){
	return sibling->getAllStmtList();
}

void PKB::printNextTable(){
	return next->printNextTable();
}

void PKB::printNextTableForTesting(){
	return next->printNextTableForTesting();
}

void PKB::printNextPairTableForTesting(){
	return next->printNextPairTableForTesting();
}

void PKB::printCallsPairTable(){
	return calls->printCallsPairTable();
}