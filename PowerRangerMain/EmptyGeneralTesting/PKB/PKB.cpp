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
}

PKB::~PKB(){
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

Node* PKB::getASTRoot(){
	return ASTRoot;
}

void PKB::setASTRoot(Node* newASTRoot){
	ASTRoot = newASTRoot;
}

//
//void PKB::setVarTable(VarTable newVarTable){
//	varTable = newVarTable;
//}
//
//void PKB::setProcTable(ProcTable newProcTable){
//	procTable = newProcTable;
//}
//
//void PKB::setTypeTable(TypeTable newTypeTable){
//	typeTable = newTypeTable;
//}
//
//void PKB::setParent(Parent newParent){
//	parent = newParent;
//}
//void PKB::setFollows(Follows newFollows){
//	follows = newFollows;
//}
//
//void PKB::setModifies(Modifies newModifies){
//	modifies = newModifies;
//}
//
//void PKB::setUses(Uses newUses){
//	uses = newUses;
//}
//

//
//void PKB::updateTypeTable(){
//	parent.updateTable(typeTable);
//	follows.updateTable(typeTable);
//}
//
//void PKB::updateProcTable(){
//}
//
//void PKB::updateVarTable(){
//}