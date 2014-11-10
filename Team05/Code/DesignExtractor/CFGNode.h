//@author Ipsita Mohapatra
//CFGNode.h

#pragma once
#ifndef CFGNODE_H
#define CFGNODE_H

#pragma once
#include <string>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stack>
#include <queue>
#include <vector>
#include "Node.h"


/*! \brief A set of methods to extract more relationships after the CodeParser has parsed the SIMPLE source program.
 * \ingroup 
 * 
 * Overview: CFGNode is the node structure of CFG nodes.
 * This is a derived class that inherits the Node Class.
 * In addition to the orginal Node Class's public and private attributes, it has a LIST of multiple parents.
 * Also, it includes the corresponding getters and setters for the multiParent attribute.
 * 
 */

class CFGNode: public Node {
private:
	std::vector<CFGNode*> multiParent;
	std::vector<CFGNode*> multiChild;
	CFGNode* endOfIfNode;
public: 
	//! A constructor to create a node with newType, and progLine as its attributes.
	CFGNode(std::string newType, int newProgLine);
	//! Add a new parent to the current Node to the list of parents
	void setMultiParent(CFGNode* newParent);
	//! Returns a LIST of Node pointers of the current node’s parents.
	std::vector<CFGNode*> getMultiParent();
	//! Get the pointer of the parent of the Node (at the specified index)
	CFGNode* getMultiParent(unsigned int index);

	//! Add a new child to the current Node to the list of children
	void setMultiChild(CFGNode* newParent);
	//! Returns a LIST of Node pointers of the current node’s children.
	std::vector<CFGNode*> getMultiChild();
	//! Get the pointer of the child of the Node (at the specified index)
	CFGNode* getMultiChild(unsigned int index);

	void printCFGNode();

	void setEndOfIfNode(CFGNode*);
	CFGNode* getEndOfIfNode();
};

#endif