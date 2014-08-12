#ifndef TYPETABLE_H
#define TYPETABLE_H

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <map>

using namespace std;
typedef int STMTNUM;

class TypeTable {
public:
	enum SynType{ASSIGN, IF, WHILE, STMT, BOOLEAN, CALL, VARIABLE, CONSTANT, PROGLINE, INVALID};
	static SynType getSynType(std::string);

private:
	vector<SynType> typeMap;
	static bool instanceFlag;
	static TypeTable *typeTable;

public: 
	TypeTable();
	~TypeTable();
	static TypeTable* getInstance();	// to be used to get instance of singleton class 
	void insertStmtNumAndType(STMTNUM,SynType);
	SynType getType(STMTNUM);
	vector<STMTNUM> getAllStmts(SynType);
	bool isType(SynType, STMTNUM); 

};

#endif