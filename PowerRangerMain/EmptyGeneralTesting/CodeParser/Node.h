#ifndef NODE_H
#define NODE_H

#pragma once
#include <string>
#include <vector>
#include <iostream>

//begin Node class
class Node{
private:
	std::string type;
	std::string data;
	int progLine;
	std::vector<Node*> child;
	Node* parent;
public:
	Node();
	Node(std::string newData,std::string newType);
	Node(std::string newData,std::string newType,int newProgLine);
	Node(Node* newLeft, Node* newRight, std::string newData,std::string newType);
	Node(Node* newLeft, Node* newRight, std::string newData,std::string newType, int newProgLine);
	std::vector<Node*> getChild();
	Node* getChild(unsigned int index);
	Node* getParent();
	std::string getType();
	std::string getData();
	int getProgLine();
	void setChild(Node* newChild);
	void setData(std::string newData);
	void setType(std::string newType);
	void setParent(Node* newParent);
	void setProgLine(int newProgLine);
	void printPreOrderExpressionTree(Node* root);
	void stringPreOrderExpressionTree(Node* root,std::string &word);
};

#endif