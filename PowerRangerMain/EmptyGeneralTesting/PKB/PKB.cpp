#pragma once

#include "PKB.h"

using namespace std;


PKB::PKB(){

}

PKB::~PKB(){
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
