//@author Steven Kester Yuwono
//CodeParser.h

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


/*! \brief A CodeParser class to validate and parse Source code.
 *  
 *
 * Overview: CodeParser is responsible to :
 * - Read the source code
 * - Tokenize every line of source code
 * - Build and store the necessary into various table in PKB
 * 
 * CodeParser has only one public method:
 * \code
 * static void parserDriver(std::string filename,PKB *pkb);
 * \endcode
 *
 * It has many private functions and sub-functions to modularize the process
 * of parsing and validating user queries.
 * 
 * When parserDriver() is called, it will call the following private sub-methods:
 * \code
 * static Node* constructExpressionTree(vector<string> tokens,int newProgLine, PKB *pkb, const vector<Node*> &containerNode);
 * static vector<string> getPostfix(vector<string> tokens);
 * static void tokenizeTokens(string word, vector<string> &storage);
 * \endcode
 * 
 * 
 *
 */

//Node* parseCode(std::string,VarTable &varTable,ProcTable &procTable, TypeTable &typeTable, Follows &follows, Parent &parent);
class CodeParser{
private:
	static bool isAllDigit(string input);
	static Node* constructExpressionTree(vector<string> tokens,int newProgLine, PKB *pkb, const vector<Node*> &containerNode);
	static vector<string> getPostfix(vector<string> tokens);
	static void tokenizeTokens(string word, vector<string> &storage);
	static Node* parseCode(string filename,PKB *pkb);

public:
	/*! \brief CodeParser parser reads in the source code, tokenizes and detects the structure of the code, then create AST, and set the tables accordingly.
	* \param filename of the source file.
	* (e.g. "source1.txt")
	* \param pkb is a pointer to a pkb class, which contains all the tables and data needed to answer queries.
	* (e.g. VARTABLE,PROCTABLE,FOLLOWS,MODIFIES,PARENT,USES,AST, etc)
	*/
	static void parserDriver(std::string filename,PKB *pkb);
};

#endif