//@author Ipsita Mohapatra
//CFGNode.cpp

#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "CFGNode.h"

using namespace std;

CFGNode::CFGNode(std::string newType, int newProgLine) {
	type=newType;
	parent=NULL;
	progLine=newProgLine;
}

std::vector<CFGNode*> CFGNode::getMultiParent() {
	return multiParent;
}

CFGNode* CFGNode::getMultiParent(unsigned int index) {
	if (index<multiParent.size()) {
		return multiParent[index];
	}
	return NULL;
}

void CFGNode::setMultiParent(CFGNode* newParent) {
	multiParent.push_back(newParent);
}

std::vector<CFGNode*> CFGNode::getMultiChild() {
	return multiChild;
}

CFGNode* CFGNode::getMultiChild(unsigned int index) {
	if (index<multiChild.size()) {
		return multiChild[index];
	}
	return NULL;
}

void CFGNode::setMultiChild(CFGNode* newChild) {
	multiChild.push_back(newChild);
}


void CFGNode::printCFGNode() {
	cout << "CFGNode(" << progLine << ", " << type + ")";
}

void CFGNode::setEndOfIfNode(CFGNode* n) {
	endOfIfNode = n;
}

CFGNode* CFGNode::getEndOfIfNode() {
	return endOfIfNode; 
}
