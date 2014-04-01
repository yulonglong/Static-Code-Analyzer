#ifndef TYPETABLE_H
#define TYPETABLE_H

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <map>
#include "Query.h"

using namespace std;
typedef int STMTNUM;

class TypeTable {
private:
	map<STMTNUM,Query::SynType> typeMap;
public: 
	TypeTable();

	void insertStmtNumAndType(STMTNUM,Query::SynType);
	Query::SynType getType (STMTNUM);
	vector<STMTNUM> getStmtNum (Query::SynType);
};

#endif