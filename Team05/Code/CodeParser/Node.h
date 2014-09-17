//@author Steven Kester Yuwono
//Node.h

#ifndef NODE_H
#define NODE_H

#pragma once
#include <string>
#include <vector>
#include <iostream>

/*! \brief A Node Structure for AST.
 * \ingroup 
 * 
 * Overview: Node is the node structure of AST nodes.
 *
 * An AST Node is used to store relevant data which is read/parsed from the source file.
 *
 * To create an AST, please follow the following steps:
 * - Create a Node, initialize and set the relevant data
 * - Link the Node to the parent (set as children) while necessary 
 * - set the root of the AST in PKB
 * 
 * 
 * \see CodeParser, DesignExtractor
 */

//begin Node class
class Node{
private:
	std::string type;
	std::string data;
	int progLine;
	std::vector<Node*> child;
	Node* parent;
public:
	//! A constructor to create a blank node.
	Node();
	//! A constructor to create a node with  newData and newType as its attributes.
	Node(std::string newData,std::string newType);
	//! A constructor to create a node with newData, newType, and progLine as its attributes.
	Node(std::string newData,std::string newType,int newProgLine);
	//! A constructor to create a node with newType, and progLine as its attributes.
	Node(std::string newType, int newProgLine);
	//! A constructor to create a node with leftChild, rightChild, newData, newType, as its attributes.
	Node(Node* newLeft, Node* newRight, std::string newData,std::string newType);
	//! A constructor to create a node with leftChild, rightChild, newData, newType, and progLine as its attributes.
	Node(Node* newLeft, Node* newRight, std::string newData,std::string newType, int newProgLine);
	//! Returns a LIST of Node pointers of the current node’s children.
	std::vector<Node*> getChild();
	//! Get the pointer of the children of the Node (at the specified index)
	Node* getChild(unsigned int index);
	//! Returns a pointer to a node which is the parent of the current Node. 
	Node* getParent();
	//! Returns the statement type of the current Node.
	std::string getType();
	//! Returns the data of the current Node
	std::string getData();
	//! Returns the program line of the current Node
	int getProgLine();
	//! Add a new children to the current Node
	void setChild(Node* newChild);
	//! Set the data of the Node
	void setData(std::string newData);
	//! Set the type of the Node
	void setType(std::string newType);
	//! Set the parent of the Node
	void setParent(Node* newParent);
	//! Set the program line of the Node
	void setProgLine(int newProgLine);
	//! Traverse and print the content of the AST in pre-order manner.
	void printPreOrderExpressionTree(Node* root);
	//! Traverse the AST in pre-order manner, and saves the content in a string passed by reference.
	void stringPreOrderExpressionTree(Node* root,std::string &word);
	//! Traverse the CFG in pre-order manner, and saves the content in a string passed by reference.
	void stringPreOrderExpressionGraph(Node* root,std::string &word);
	void printCFGNode();
};

#endif