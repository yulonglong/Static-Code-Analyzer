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
#include "PKB.h"
#include "ProcTable.h"
#include "VarTable.h"
#include "TypeTable.h"
#include "Follows.h"
#include "Parent.h"
#include "Query.h"
#include "Modifies.h"
#include "Uses.h"


//Node* parseCode(std::string,VarTable &varTable,ProcTable &procTable, TypeTable &typeTable, Follows &follows, Parent &parent);
void parserDriver(std::string filename,PKB *pkb);

#endif