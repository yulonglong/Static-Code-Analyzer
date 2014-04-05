#pragma once

#include "PKB.h"

using namespace std;


PKB::PKB(){
	// private constructor
	parent = Parent(typeTable);
	follows = Follows(typeTable);
}

PKB::~PKB(){
}


//PKB* PKB::getInstance() {
//	if(!instanceFlag)
//    {
//        pkb = new PKB();
//        instanceFlag = true;
//        return pkb;
//    }
//    else
//    {
//        return pkb;
//    }
//}

VarTable PKB::getVarTable(){
	return varTable;
}

ProcTable PKB::getProcTable(){
	return procTable;
}

TypeTable PKB::getTypeTable(){
	return typeTable;
}

Parent PKB::getParent(){
	return parent;
}

Follows PKB::getFollows(){
	return follows;
}

void PKB::setVarTable(VarTable newVarTable){
	varTable = newVarTable;
}

void PKB::setProcTable(ProcTable newProcTable){
	procTable = newProcTable;
}

void PKB::setTypeTable(TypeTable newTypeTable){
	typeTable = newTypeTable;
}

void PKB::setParent(Parent newParent){
	parent = newParent;
}
void PKB::setFollows(Follows newFollows){
	follows = newFollows;
}