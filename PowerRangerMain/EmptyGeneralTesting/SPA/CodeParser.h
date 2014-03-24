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

Node* parseCode(std::string,VarTable varTable,ProcTable procTable);

#endif