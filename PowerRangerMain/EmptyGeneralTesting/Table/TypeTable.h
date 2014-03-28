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
typedef vector<STMTNUM> LIST;
enum STYPE { ASSIGN, WHILE, IF, CALL } ;

class TypeTable {
private:
	map<STMTNUM,STYPE> typeMap;
public: 
	TypeTable();
	void insertStmtNumAndType(STMTNUM,STYPE);
	STYPE getType (STMTNUM);
	LIST getStmtNum (STYPE);
};

#endif