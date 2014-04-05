#pragma once

#include "CodeParser.h"
using namespace std;


void CodeParser::parserDriver(PKB pkb){
}

Node* constructExpressionTree(vector<string> tokens,int newProgLine, VarTable &varTable){
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
				//insert to var table
				varTable.insertVar(tokens[i]);
				//end insertion
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

void tokenizeTokens(string word, vector<string> &storage){
	string token ="";
	for(int i=0;i<(int) word.length();i++){
		if((word[i]=='+')||(word[i]=='-')||(word[i]=='/')||(word[i]=='*')||(word[i]=='=')){
			if(token.length()>0){
				storage.push_back(token);
			}
			token = word[i];
			storage.push_back(token);
			token ="";
		}
		else{
			token = token + word[i];
		}
	}
	if(token.length()>0){
		storage.push_back(token);
	}
	return;
}

//real parsing
Node* parseCode(string filename,VarTable &varTable,ProcTable &procTable, TypeTable &typeTable, Follows &follows,Parent &parent){
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
		int openBracket = 0;
		int closeBracket = 0;
		bool valid=false;
		istringstream istream(word);
		vector<string> tokens;
		string singleToken;

		//getting all the tokens from the line
		while(istream>>singleToken){
			tokenizeTokens(singleToken,tokens);
		}
		/*
		for(int i=0;i<tokens.size();i++){
			cout << tokens[i] << endl;
		}*/

		//checking syntax whether there are matching open and close curly bracket
		//and the presence of semi colon
		if(tokens.size()==1){
			if(tokens[0]=="}"){
				valid=true;
				closeBracket++;
			}
			else if(tokens[0]=="{"){
				valid=true;
				openBracket++;
			}
		}
		else if (tokens.size()==2){
			//cout << tokens[0] << endl;
			if((tokens[0]=="procedure")||(tokens[0]=="while")||(tokens[0]=="if")||(tokens[0]=="else")){
				int length=tokens[1].length()-1;
				string lastChar = tokens[1].substr(length);
				if(lastChar=="{"){
					tokens[1] = tokens[1].substr(0,length);
					openBracket++;
					valid=true;
				}
				else{
					valid=true;
				}
			}
		}


		while(!valid){
			int tokenLastIndex = tokens.size()-1;
			if(tokens[tokenLastIndex]=="{"){
				openBracket++;
				valid=true;
				tokens.erase(tokens.begin()+tokenLastIndex);
			}
			else if(tokens[tokenLastIndex]=="}"){
				closeBracket++;
				tokens.erase(tokens.begin()+tokenLastIndex);
				if(tokens.size()==0){
					valid=true;
				}
			}
			else if(tokens[tokenLastIndex]==";"){
				valid=true;
				tokens.erase(tokens.begin()+tokenLastIndex);
			}
			else if(tokens[tokenLastIndex]==";}"){
				closeBracket++;
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
		if(openBracket>0){
			bracket.push(1);
		} 
		
		//checking for curly bracket matching
		if((bracket.size()==0)&&(openBracket==0)&&(tokens.size()>0)&&(tokens[0]!="procedure")){
			cout << "ERROR in parsing code" << endl;
		}
		
		//updating and editing the programLine number 
		if((tokens[0]!="procedure")&&(tokens[0]!="else")&&(tokens.size()>=2)){
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

			//insert to proc table
			procTable.insertProc(procName);
			//end insertion

			currProcName = procName;
			
			Node* stmtLst = new Node(procName, "stmtLst");
			Node* procRoot = new Node(procName,"procedure");
			
			root->setChild(procRoot);
			procRoot->setParent(root);
			
			procRoot->setChild(stmtLst);
			stmtLst->setParent(procRoot);
			containerNode.push_back(stmtLst);
			
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

			//set parent
			int parentProgLine = currParent->getProgLine();
			if(parentProgLine!=-1){
				parent.setParent(parentProgLine,progLine);
			}
			//setFollows
			string parentType = currParent->getType();
			if(parentType=="stmtLst"){
				int parentChildSize = currParent->getChild().size();
				if(parentChildSize>=2){
					int prevProgLine = currParent->getChild(parentChildSize-2)->getProgLine();
					follows.setFollows(prevProgLine,progLine);
				}
			}
			//setTypeTable
			typeTable.insertStmtNumAndType(progLine,TypeTable::CALL);

		}
		else if(tokens[0]=="while"){
			if(tokens.size()!=2){
				return NULL;
			}
			string controlVarName;
			controlVarName=tokens[1];

			//insert to var table
			varTable.insertVar(controlVarName);
			//end insertion
			
			int index = containerNode.size()-1;
			Node* currParent = containerNode[index];
			
			Node* controlVar = new Node(controlVarName,"variable",progLine);
			Node* stmtLst = new Node(stringProgLine, "stmtLst",progLine);
			Node* whileRoot = new Node(controlVar,stmtLst,stringProgLine,"while",progLine);
			controlVar->setParent(whileRoot);
			stmtLst->setParent(whileRoot);

			currParent->setChild(whileRoot);
			whileRoot->setParent(currParent);

			//set parent
			int parentProgLine = currParent->getProgLine();
			if(parentProgLine!=-1){
				parent.setParent(parentProgLine,progLine);
			}
			//setFollows
			string parentType = currParent->getType();
			if(parentType=="stmtLst"){
				int parentChildSize = currParent->getChild().size();
				if(parentChildSize>=2){
					int prevProgLine = currParent->getChild(parentChildSize-2)->getProgLine();
					follows.setFollows(prevProgLine,progLine);
				}
			}
			//setTypeTable
			typeTable.insertStmtNumAndType(progLine,TypeTable::WHILE);

			containerNode.push_back(stmtLst);
			
		
		}
		else if(tokens[0]=="if"){
			if(tokens.size()!=3){
				return NULL;
			}
			string controlVarName;
			controlVarName=tokens[1];

			//insert to var table
			varTable.insertVar(controlVarName);
			//end insertion
			
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

			//set parent
			int parentProgLine = currParent->getProgLine();
			if(parentProgLine!=-1){
				parent.setParent(parentProgLine,progLine);
			}
			//setFollows
			string parentType = currParent->getType();
			if(parentType=="stmtLst"){
				int parentChildSize = currParent->getChild().size();
				if(parentChildSize>=2){
					int prevProgLine = currParent->getChild(parentChildSize-2)->getProgLine();
					follows.setFollows(prevProgLine,progLine);
				}
			}
			//setTypeTable
			typeTable.insertStmtNumAndType(progLine,TypeTable::IF);

			containerNode.push_back(elseStmt);
			containerNode.push_back(thenStmt);
			 
		}
		else if (tokens[0]=="else"){
			if(tokens.size()!=1){
				return NULL;
			}
			
		}
		else if((tokens.size()>=3)&&(tokens[1]=="=")){//if it is an assignment

			Node* modifiedVar = new Node(tokens[0],"variable",progLine);
			Node* assignRoot = new Node(tokens[1],"assign",progLine);
			tokens.erase(tokens.begin(),tokens.begin()+2);
			vector<string> ans = getPostfix (tokens);
			Node* expressionRoot = constructExpressionTree(ans,progLine,varTable);
			assignRoot->setChild(modifiedVar);
			modifiedVar->setParent(assignRoot);
			assignRoot->setChild(expressionRoot);
			expressionRoot->setParent(assignRoot);
			//printInOrderExpressionTree(assignRoot);
			
			int index = containerNode.size()-1;
			Node* currParent = containerNode[index];
				
			currParent->setChild(assignRoot);
			assignRoot->setParent(currParent);

			//set parent
			int parentProgLine = currParent->getProgLine();
			if(parentProgLine!=-1){
				parent.setParent(parentProgLine,progLine);
			}
			//setFollows
			string parentType = currParent->getType();
			if(parentType=="stmtLst"){
				int parentChildSize = currParent->getChild().size();
				if(parentChildSize>=2){
					int prevProgLine = currParent->getChild(parentChildSize-2)->getProgLine();
					follows.setFollows(prevProgLine,progLine);
				}
			}
			//setTypeTable
			typeTable.insertStmtNumAndType(progLine,TypeTable::ASSIGN);
			
		}


		//cout << "close bracket "  << bracket.size() << endl;
		//int size = containerNode.size()-1;
		//cout << containerNode[size]->getData() << " "<<  containerNode[size]->getType()<< endl;
		
		while(closeBracket>0){
			if((bracket.size()==1)&&(closeBracket==1)){
				currProcName = "";
				bracket.pop();
			}
			else if(bracket.size()>1){
				bracket.pop();
				int size = containerNode.size()-1;
				//printInOrderExpressionTree(containerNode[size-1]);
				containerNode.erase(containerNode.begin()+size);
			}
			else if(bracket.size()==0){
				cout << "ERROR in parsing code" << endl;
			}
			closeBracket--;
		}
	
		//cout << stringProgLine << ". " << word << endl;
	}
	
	//printPreOrderExpressionTree(root);
	return root;
}