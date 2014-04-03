#pragma once

#include "PKB.h"

using namespace std;


PKB::PKB(){
	// private constructor
}

PKB::~PKB(){
	instanceFlag = false;
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
