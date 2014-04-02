#ifndef FOLLOWSSTAR_H
#define FOLLOWSSTAR_H

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include "Query.h"
#include "TypeTable.h"

using namespace std;
typedef int STMTNUM;

class FollowsStar {
public: 
	FollowsStar();
	bool isFollowsStar(STMTNUM, STMTNUM);// Select BOOLEAN such that Parent*(1,2)
};

#endif