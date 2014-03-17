#pragma once

#include "CodeParser.h"
using namespace std;



void printPreOrderExpressionTree(Node* root){
	if(root->getParent()!=NULL){
		cout << "Parent " << root->getParent()->getProgLine() << ".) "<< root->getParent()->getData() << " : " << root->getParent()->getType() << endl;
	}
	cout << root->getProgLine() << ".) " << root->getData() << " : " << root->getType() << endl;
	
	for(unsigned i=0;i<root->getChild().size();i++){
		printPreOrderExpressionTree(root->getChild(i));
	}
	return;
}

void printInOrderExpressionTree(Node* root){
	if(root->getChild(0)!=NULL){
		printInOrderExpressionTree(root->getChild(0));
	}
	cout << root->getData() << " : " << root->getType() << " ";
	if(root->getChild(1)!=NULL){
		printInOrderExpressionTree(root->getChild(1));
	}
	return;
}
//end Node class

Node* constructExpressionTree(vector<string> tokens,int newProgLine){
	stack<Node*> st;
	int length = tokens.size();
	
	for(int i=0;i<length;i++){
		if((tokens[i]=="+")||(tokens[i]=="-")||(tokens[i]=="*")||(tokens[i]=="/")){
			Node* right = st.top();
			st.pop();
			Node* left = st.top();
			st.pop();
			Node* curr = new Node(left,right,tokens[i],"operator",newProgLine);
			left->setParent(curr);
			right->setParent(curr);
			st.push(curr);
		}
		else{
			string type;
			if(isdigit(tokens[i][0])){
				type="constant";
			}
			else{
				type="variable";
			}
			Node* curr = new Node(tokens[i],type,newProgLine);
			st.push(curr);
		}
	}
	Node* root = st.top();
	st.pop();
	return root;
}

vector<string> getPostfix(vector<string> tokens){
	vector<string> ans;
	stack<string> st;
	int size = tokens.size();
	for(int i=0;i<size;i++){
		if(tokens[i]=="("){
			st.push(tokens[i]);
		}
		else if(tokens[i]==")"){
			if(!st.empty()){
				ans.clear();
				ans.push_back("invalid");
				return ans;
			}
			string tempToken = st.top();
			st.pop();
			while(tempToken!="("){
				if(!st.empty()){
					ans.push_back(tempToken);
					tempToken=st.top();
					st.pop();
				}
				else{
					ans.clear();
					ans.push_back("invalid");
					return ans;
				}
			}
		}
		else if(tokens[i]=="+") {
			if(st.empty()){
				st.push("+");
				continue;
			}
			else{
				string tempToken = st.top();
				while((tempToken=="+")||(tempToken=="-")||(tempToken=="*")||(tempToken=="/")){
					ans.push_back(tempToken);
					st.pop();
					if(!st.empty()){
						tempToken=st.top();
					}
					else{
						break;
					}
				}
				st.push("+");
			}
		}
		else if(tokens[i]=="-") {
			if(st.empty()){
				st.push("-");
				continue;
			}
			else{
				string tempToken = st.top();
				while((tempToken=="+")||(tempToken=="-")||(tempToken=="*")||(tempToken=="/")){
					ans.push_back(tempToken);
					st.pop();
					if(!st.empty()){
						tempToken=st.top();
					}
					else{
						break;
					}
				}
				st.push("-");
			}
		}
		else if(tokens[i]=="*") {
			if(st.empty()){
				st.push("*");
				continue;
			}
			else{
				string tempToken = st.top();
				while((tempToken=="*")||(tempToken=="/")){
					ans.push_back(tempToken);
					st.pop();
					if(!st.empty()){
						tempToken=st.top();
					}
					else{
						break;
					}
				}
				st.push("*");
			}
		}
		else if(tokens[i]=="/") {
			if(st.empty()){
				st.push("/");
				continue;
			}
			else{
				string tempToken = st.top();
				while((tempToken=="*")||(tempToken=="/")){
					ans.push_back(tempToken);
					st.pop();
					if(!st.empty()){
						tempToken=st.top();
					}
					else{
						break;
					}
				}
				st.push("/");
			}
		}
		else {
			ans.push_back(tokens[i]);
		}
	}
	
	while(!st.empty()){
		ans.push_back(st.top());
		st.pop();
	}
	return ans;
}

Node* parse(string filename){
	//freopen("in.txt","r",stdin);
	ifstream infile;
	infile.open(filename.c_str(),ios::in);
	if(infile.fail()){
		cout << "ERROR! Failed to open " << filename << endl;
		return NULL;
	}
	string word;
	int progLine=0;
	int progLineCounter=0;
	string stringProgLine;
	string currProcName;
	vector<Node*> containerNode;
	Node* root = new Node ("root","program");
	vector<int> container;
	stack<int> bracket;
	while(getline(infile,word)){

		if(word.length()==0){
			continue;
		}

		//initializing variables needed
		bool openBracket=false;
		bool closeBracket=false;
		bool valid=false;
		istringstream istream(word);
		vector<string> tokens;
		string singleToken;

		//getting all the tokens from the line
		while(istream>>singleToken){
			tokens.push_back(singleToken);
		}

		//checking syntax whether there are matching open and close curly bracket
		//and the presence of semi colon
		while(!valid){
			int tokenLastIndex = tokens.size()-1;
			if(tokens[tokenLastIndex]=="{"){
				openBracket=true;
				valid=true;
				tokens.erase(tokens.begin()+tokenLastIndex);
			}
			else if(tokens[tokenLastIndex]=="}"){
				closeBracket=true;
				tokens.erase(tokens.begin()+tokenLastIndex);
			}
			else if(tokens[tokenLastIndex]==";"){
				valid=true;
				tokens.erase(tokens.begin()+tokenLastIndex);
			}
			else if(tokens[tokenLastIndex]==";}"){
				closeBracket=true;
				tokens.erase(tokens.begin()+tokenLastIndex);
				valid=true;
			}
			else{
				int length=tokens[tokenLastIndex].length()-1;
				string lastChar = tokens[tokenLastIndex].substr(length);
				tokens[tokenLastIndex] = tokens[tokenLastIndex].substr(0,length);
				tokens.push_back(lastChar);
			}
		}

		//checking for curly bracket matching
		if(bracket.empty()){
			if(!openBracket){
				return NULL;
			}
			else if(tokens[0]!="procedure"){
				return NULL;
			}
		}
		
		//updating and editing the programLine number 
		if((tokens[0]!="procedure")&&(tokens[0]!="else")){
			char buffer[30];
			progLineCounter++;
			progLine=progLineCounter;
			_itoa_s(progLine,buffer,10);
			stringProgLine = buffer;
			stringProgLine = stringProgLine;
		}
		else{
			progLine = -1;
			stringProgLine ="   ";
		}

		//cout <<"bracket "<< bracket.size() << endl;
		//considering every case (while,if,call,assign)
		if (tokens[0]=="procedure"){
			if(tokens.size()!=2){
				return NULL;
			}
			string procName;
			procName=tokens[1];
			currProcName = procName;
			
			Node* stmtLst = new Node(procName, "stmtLst");
			Node* procRoot = new Node(procName,"procedure");
			
			root->setChild(procRoot);
			procRoot->setParent(root);
			
			procRoot->setChild(stmtLst);
			stmtLst->setParent(procRoot);
			containerNode.push_back(stmtLst);
			
			if(openBracket){
				bracket.push(1);
			} 
		}
		else if (tokens[0]=="call"){
			if(tokens.size()!=2){
				return NULL;
			}
			string procName;
			procName=tokens[1];
			
			Node* currCall = new Node(procName,"call",progLine);
			
			int index = containerNode.size()-1;
			Node* currParent = containerNode[index];
			
			currParent->setChild(currCall);
			currCall->setParent(currParent);
		}
		else if(tokens[0]=="while"){
			if(tokens.size()!=2){
				return NULL;
			}
			string controlVarName;
			controlVarName=tokens[1];
			
			int index = containerNode.size()-1;
			Node* currParent = containerNode[index];
			
			Node* controlVar = new Node(controlVarName,"variable",progLine);
			Node* stmtLst = new Node(stringProgLine, "stmtLst",progLine);
			Node* whileRoot = new Node(controlVar,stmtLst,stringProgLine,"while",progLine);
			controlVar->setParent(whileRoot);
			stmtLst->setParent(whileRoot);
			
			currParent->setChild(whileRoot);
			whileRoot->setParent(currParent);
			containerNode.push_back(stmtLst);
			
			if(openBracket){
				bracket.push(1);
			} 
		
		}
		else if(tokens[0]=="if"){
			if(tokens.size()!=3){
				return NULL;
			}
			string controlVarName;
			controlVarName=tokens[1];
			
			int index = containerNode.size()-1;
			Node* currParent = containerNode[index];

			Node* controlVar = new Node(controlVarName,"variable",progLine);
			Node* thenStmt= new Node("then", "stmtLst",progLine);
			Node* elseStmt= new Node("else", "stmtLst",progLine);
			Node* ifRoot = new Node(stringProgLine,"if",progLine);
			ifRoot->setChild(controlVar);
			controlVar->setParent(ifRoot);
			ifRoot->setChild(thenStmt);
			thenStmt->setParent(ifRoot);
			ifRoot->setChild(elseStmt);
			elseStmt->setParent(ifRoot);
			
			currParent->setChild(ifRoot);
			ifRoot->setParent(currParent);
			containerNode.push_back(elseStmt);
			containerNode.push_back(thenStmt);
			
			if(openBracket){
				bracket.push(1);
			}  
		}
		else if (tokens[0]=="else"){
			if(tokens.size()!=1){
				return NULL;
			}
			
			if(openBracket){
				bracket.push(1);
			} 
		}
		else{//if it is an assignment
			Node* modifiedVar = new Node(tokens[0],"variable",progLine);
			Node* assignRoot = new Node(tokens[1],"assign",progLine);
			tokens.erase(tokens.begin(),tokens.begin()+2);
			vector<string> ans = getPostfix (tokens);
			Node* expressionRoot = constructExpressionTree(ans,progLine);
			assignRoot->setChild(modifiedVar);
			modifiedVar->setParent(assignRoot);
			assignRoot->setChild(expressionRoot);
			expressionRoot->setParent(assignRoot);
			//printInOrderExpressionTree(assignRoot);
			
			int index = containerNode.size()-1;
			Node* currParent = containerNode[index];
				
			currParent->setChild(assignRoot);
			assignRoot->setParent(currParent);
		}
		//cout << "close bracket "  << bracket.size() << endl;
		//int size = containerNode.size()-1;
		//cout << containerNode[size]->getData() << " "<<  containerNode[size]->getType()<< endl;
		
		if((bracket.size()==1)&&(closeBracket)){
			currProcName = "";
			bracket.pop();
		}
		else if((bracket.size()>1)&&(closeBracket)){
			bracket.pop();
			int size = containerNode.size()-1;
			//printInOrderExpressionTree(containerNode[size-1]);
			containerNode.erase(containerNode.begin()+size);
		}
		else if(bracket.size()==0){
			cout << "ERROR" << endl;
		}
		cout << stringProgLine << ". " << word << endl;
	}
	
	printPreOrderExpressionTree(root);
	return root;
}