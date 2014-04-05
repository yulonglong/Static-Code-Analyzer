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
	enum SynType{ASSIGN, IF, WHILE, STMT, BOOLEAN, CALL, INVALID};
	static SynType getSynType(std::string);

private:
	map<STMTNUM,SynType> typeMap;

public: 
	TypeTable();
	void insertStmtNumAndType(STMTNUM,SynType);
	SynType getType(STMTNUM);
	vector<STMTNUM> getAllStmts(SynType);
};

#endif