#pragma once
#ifndef CODEPARSER_H
#define CODEPARSER_H

#pragma once
#include <string>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stack>
#include <vector>
#include "Node.h"
#include "ProcTable.h"
#include "VarTable.h"
#include "Follows.h"
#include "Parent.h"

Node* parseCode(std::string,VarTable &varTable,ProcTable &procTable, Follows &follows, Parent &parent);

#endif