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
typedef string TYPE;
typedef vector<STMTNUM> LIST;

class TypeTable {
private:
	map<STMTNUM,TYPE> typeMap;
public: 
	TypeTable();
	void insertStmtNumAndType(STMTNUM,TYPE);
	TYPE getType (STMTNUM);
	LIST getStmtNum (TYPE);
};

#endif