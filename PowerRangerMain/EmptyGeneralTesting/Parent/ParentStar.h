#ifndef PARENTSTAR_H
#define PARENTSTAR_H

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include "TypeTable.h"
#include "Query.h"
#include "Parent.h"

using namespace std;
typedef int STMTNUM;

class ParentStar {
public: 
	ParentStar();
	bool isParentStar(STMTNUM, STMTNUM);// Select BOOLEAN such that Parent*(1,2)
};

#endif