#pragma once

#include "TypeTable.h"

bool TypeTable::instanceFlag=false;
TypeTable* TypeTable::typeTable=NULL;

// constructor
TypeTable::TypeTable() {
	typeMap.assign(1, INVALID);
}

TypeTable::~TypeTable(){
	typeMap.clear();
	instanceFlag=false;
}

TypeTable::SynType TypeTable::getSynType(std::string input){
	for(int i=0;i<(int)input.length();i++){
		input[i] = tolower(input[i]);
	}
	
	
	if(input=="assign"){
		return TypeTable::ASSIGN;
	}
	else if(input=="if"){
		return TypeTable::IF;
	}
	else if(input=="while"){
		return TypeTable::WHILE;
	}
	else if(input=="stmt"){
		return TypeTable::STMT;
	}
	else if(input=="boolean"){
		return TypeTable::BOOLEAN;
	}
	else if(input=="call"){
		return TypeTable::CALL;
	}
	else if(input=="variable"){
		return TypeTable::VARIABLE;
	}
	else if(input=="constant"){
		return TypeTable::CONSTANT;
	}
	else if(input=="prog_line"){
		return TypeTable::PROGLINE;
	}
	else if(input=="procedure"){
		return TypeTable::PROCEDURE;
	}
	else{
		return TypeTable::INVALID;
	}
}

TypeTable* TypeTable::getInstance() {
	if(!instanceFlag)
    {
        typeTable = new TypeTable();
        instanceFlag = true;
        return typeTable;
    }
    else
    {
        return typeTable;
    }
}


void TypeTable::insertStmtNumAndType(STMTNUM s,TypeTable::SynType t) {
	//Resize if needed
	if (s >= (signed int) typeMap.size()) {
		typeMap.resize(s+1, INVALID);
	}
	typeMap[s]=t;
}

TypeTable::SynType TypeTable::getType(STMTNUM s) {
	try{
		return typeMap.at(s);
	}catch(...){
		return INVALID;
	}
}

set<STMTNUM> TypeTable:: getAllStmts (TypeTable::SynType t) {
	set<STMTNUM> list;
	for (size_t i=1; i!=typeMap.size(); i++){
		if (t == STMT || typeMap.at(i) == t) {
			list.insert (i);
		}
	}
	return list;
}

bool TypeTable::isType(TypeTable::SynType type, STMTNUM stmt) {
	try{
		if (type == STMT || typeMap.at(stmt) == type) {
			return true;
		}
		return false;
	}catch(...){
		return false;
	}
}

STMTNUM TypeTable::getStmtRange(){
	if(typeMap.size()==1)
		return -1;
	return typeMap.size()-1;
}