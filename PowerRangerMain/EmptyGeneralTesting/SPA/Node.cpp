#pragma once
#include "Node.h"
using namespace std;

Node::Node(){
	data="";
	type="";
	parent=NULL;
	progLine=-1;
}
Node::Node(string newData,string newType){
	data=newData;
	type=newType;
	parent=NULL;
	progLine=-1;
}
Node::Node(string newData,string newType,int newProgLine){
	data=newData;
	type=newType;
	parent=NULL;
	progLine=newProgLine;
}
Node::Node(Node* newLeft, Node* newRight, string newData,string newType){
	data=newData;
	type=newType;
	child.push_back(newLeft);
	child.push_back(newRight);
	parent=NULL;
	progLine=-1;
}
Node::Node(Node* newLeft, Node* newRight, string newData,string newType, int newProgLine){
	data=newData;
	type=newType;
	child.push_back(newLeft);
	child.push_back(newRight);
	parent=NULL;
	progLine=newProgLine;
}
vector<Node*> Node::getChild(){
	return child;
}
Node* Node::getChild(unsigned int index){
	if(index<child.size()){
		return child[index];
	}
	return NULL;
}
Node* Node::getParent(){
	return parent;
}
string Node::getType(){
	return type;
}
string Node::getData(){
	return data;
}
int Node::getProgLine(){
	return progLine;
}
void Node::setChild(Node* newChild){
	child.push_back(newChild);
}
void Node::setData(string newData){
	data = newData;
}
void Node::setType(string newType){
	type = newType;
}
void Node::setParent(Node* newParent){
	parent=newParent;
}
void Node::setProgLine(int newProgLine){
	progLine = newProgLine;
}