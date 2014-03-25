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
typedef string SType;

class TypeTable {
private:
	map<STMTNUM,SType> typeMap;
public: 
	TypeTable();
	void insertStmtNumAndType(STMTNUM,SType);
	SType getType (STMTNUM);
	LIST getStmtNum (SType);
};

#endif