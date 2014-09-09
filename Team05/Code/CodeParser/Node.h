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
	//! Blank Node Constructor
	Node();
	//! Constructor 1
	Node(std::string newData,std::string newType);
	//! Constructor 2
	Node(std::string newData,std::string newType,int newProgLine);
	//! Constructor 3
	Node(std::string newType,int newProgLine);
	//! Constructor 4
	Node(Node* newLeft, Node* newRight, std::string newData,std::string newType);
	//! Constructor 5, most detailed constructor
	Node(Node* newLeft, Node* newRight, std::string newData,std::string newType, int newProgLine);
	//! get the a list of pointers of all the children of the Node
	std::vector<Node*> getChild();
	//! get the pointer of the children of the Node (at the specified index)
	Node* getChild(unsigned int index);
	//! get the pointer of the parent of the Node
	Node* getParent();
	//! get the type of the Node
	std::string getType();
	//! get the data of the Node
	std::string getData();
	//! get the program line of the Node
	int getProgLine();
	//! add a children to the current Node
	void setChild(Node* newChild);
	//! set the data of the Node
	void setData(std::string newData);
	//! set the type of the Node
	void setType(std::string newType);
	//! set the parent of the Node
	void setParent(Node* newParent);
	//! set the program line of the Node
	void setProgLine(int newProgLine);
	//! Traverse and print the content of the AST in pre-order manner.
	void printPreOrderExpressionTree(Node* root);
	//! Traverse the AST in pre-order manner, and saves the content in a string.
	void stringPreOrderExpressionTree(Node* root,std::string &word);
};

#endif