//@author Ipsita Mohapatra
//DesignExtractor.cpp

#pragma once

#include "DesignExtractor.h"	
#include "TypeTable.h"	

using namespace std;

bool debugModeIteration1 = 0; 
bool debugModeIteration2 = 0;
bool debugModeIteration3 = 0; 
bool debugModeExtension = 1; 

int counter = 0;
vector<int> visited; 
CFGNode* foundNode; // for CFG traversal

CFGNode* rootCFGNode;
CFGNode* currCFGNode;
//Node* currASTNode;

queue<QueueItem> queueToProcess;

void DesignExtractor::extractorDriver(PKB *pkb) {
	cout << "Begin DesignExtractor" << endl;
	unordered_map<PROCINDEX, vector<CALLSPAIR>> callsTable; 
	// PKB GET:
	callsTable = pkb->getCallsTable();
	

	if (debugModeIteration1) {
		printCallsTable(callsTable);
		cout << "DE has obtained tables from PKB" << endl;
	}
	
	// PKB GET: 
	Node* ASTRoot = pkb->getASTRoot();
	Node* CFGRoot = pkb->getCFGRoot();
	
	extractRelationships(*ASTRoot, callsTable, *pkb);
	cout << "DE: Extracted Relationships" << endl;
	buildCFGDriver(*pkb, *ASTRoot, *CFGRoot);
	extractSiblingRelationshipDriver(*ASTRoot, *pkb);

	cout << "End DesignExtractor" << endl;
}

void DesignExtractor::extractSiblingRelationshipDriver(Node &ASTRoot, PKB &pkb) {
	cout << "Extracting Sibling" << endl;
	
	vector<Node*> procNodes = ASTRoot.getChild();
	setSiblingforProcedures(procNodes, pkb);

	for (unsigned int i=0; i<procNodes.size(); i++) {
		Node* n = procNodes[i];
		vector<Node*> stmtNodes = n->getChild(0)->getChild();
		setSiblingForStatements(stmtNodes, pkb);
	}

}

void DesignExtractor::setSiblingforProcedures(vector<Node*> procNodes, PKB &pkb) {
	for (unsigned int i=0; i<procNodes.size()-1; i++) {
		for (unsigned int j=i+1; j<procNodes.size(); j++) {
			std::string procName1 = procNodes[i]->getData();
			std::string procName2 = procNodes[j]->getData();
			// PKB SET: 
			if (debugModeExtension) {
				cout<<"setToSiblingProcNames("<<procName1<<", "<<procName2<<")"<<endl;
			}
			pkb.setToSiblingProcNames(procName1, procName2);
		}
	}
}

void DesignExtractor::setSiblingForStatements(vector<Node*> stmtNodes, PKB &pkb) {
	for (unsigned int i=0; i<stmtNodes.size()-1; i++) {
		for (unsigned int j=i+1; j<stmtNodes.size(); j++) {
			int stmtNum1 = stmtNodes[i]->getProgLine();
			int stmtNum2 = stmtNodes[j]->getProgLine();
			// PKB SET: 
			if (debugModeExtension) {
				cout<<"setToSiblingStmtNums("<<stmtNum1<<", "<<stmtNum2<<")"<<endl;
			}
			pkb.setToSiblingStmtNums(stmtNum1, stmtNum2);
		}
	}
	for (unsigned int i=0; i<stmtNodes.size(); i++) {
		Node* n = stmtNodes[i];
		string type = n->getType();
		if (type == "assign") {
			setSiblingForAssign(n->getChild(), pkb);
		} else if (type == "call") {
			continue;
		} else if (type == "if") {
			setSiblingForIf(n->getChild(), pkb);
		} else if (type == "while") {
			setSiblingForWhile(n->getChild(), pkb);
		}
	}

}

void DesignExtractor::setSiblingForAssign(vector<Node*> vector, PKB &pkb) {
	string leftNodeType = vector[0]->getType();
	string rightNodeType = vector[1]->getType();
	if (leftNodeType == "constant" && rightNodeType == "constant") {
		// PKB SET:

	} else if (leftNodeType == "variable" && rightNodeType == "variable") {
		// PKB SET:

	} else if (leftNodeType == "operator" && rightNodeType == "operator") {
		// PKB SET:

	} else if (leftNodeType == "variable" && rightNodeType == "constant") {
		// PKB SET:

	} else if (leftNodeType == "constant" && rightNodeType == "variable") {
		// PKB SET:

	} else if (leftNodeType == "variable" && rightNodeType == "operator") {
		// PKB SET:

	} else if (leftNodeType == "operator" && rightNodeType == "variable") {
		// PKB SET:

	} else if (leftNodeType == "constant" && rightNodeType == "operator") {
		// PKB SET:

	} else if (leftNodeType == "operator" && rightNodeType == "constant") {
		// PKB SET:

	}
	if (vector[0]->getChild().size() == 2) {
		setSiblingForAssign(vector[0]->getChild(), pkb);
	}
	if (vector[1]->getChild().size() == 2) {
		setSiblingForAssign(vector[1]->getChild(), pkb);
	}
}

void DesignExtractor::setSiblingForIf(vector<Node*> vector, PKB &pkb) {
	string varName = vector[0]->getData();
	int firstStmtOfThenStmtLst = vector[1]->getChild(0)->getProgLine();
	int firstStmtOfElseStmtLst = vector[2]->getChild(0)->getProgLine();
	// PKB SET:
	if (debugModeExtension) {
		cout<<"setToSiblingVarNameStmtList("<<varName<<", "<<firstStmtOfThenStmtLst<<")"<<endl;
		cout<<"setToSiblingVarNameStmtList("<<varName<<", "<<firstStmtOfElseStmtLst<<")"<<endl;
		cout<<"setToSiblingStmtLists("<<firstStmtOfThenStmtLst<<", "<<firstStmtOfElseStmtLst<<")"<<endl;
	}
	pkb.setToSiblingVarNameStmtList(varName, firstStmtOfThenStmtLst);
	pkb.setToSiblingVarNameStmtList(varName, firstStmtOfElseStmtLst);
	pkb.setToSiblingStmtLists(firstStmtOfThenStmtLst, firstStmtOfElseStmtLst);

	setSiblingForStatements(vector[1]->getChild(), pkb);
	setSiblingForStatements(vector[2]->getChild(), pkb);
}

void DesignExtractor::setSiblingForWhile(vector<Node*> vector, PKB &pkb) {
	string varName = vector[0]->getData();
	int firstStmtOfStmtLst = vector[1]->getChild(0)->getProgLine();
	// PKB SET:
	if (debugModeExtension) {
		cout<<"setToSiblingVarNameStmtList("<<varName<<", "<<firstStmtOfStmtLst<<")"<<endl;
	}
	pkb.setToSiblingVarNameStmtList(varName, firstStmtOfStmtLst);

	setSiblingForStatements(vector[1]->getChild(), pkb);
}

void DesignExtractor::buildCFGDriver(PKB &pkb, Node &ASTRoot, Node &CFGRoot) {
	try {
		cout << "Building CFG" << endl;
		buildCFG(ASTRoot, pkb);
		setNextRelationshipDriver(pkb);
	} catch(const std::runtime_error& re) {
		// specific handling for runtime_error
		std::cerr << "Runtime error in DE: " << re.what() << std::endl;
	} catch(const std::exception& ex) {
		// specific handling for all exceptions extending std::exception, except
		// std::runtime_error which is handled explicitly
		std::cerr << "Error occurred in DE: " << ex.what() << std::endl; 
	} catch(...) {
		// catch any other errors (that we have no information about)
		std::cerr << "Unknown failure occured in DE. Possible memory corruption" << std::endl;
	}

	// PKB SET: 
	pkb.setCFGRoot(rootCFGNode);
	CFGNode* temp = pkb.getCFGRoot();
}

// actual building of CFG 
void DesignExtractor::buildCFG(Node &ASTRroot, PKB &pkb) {
	// create CFG Root Node with progLine = 0
	Node* currASTNode;
	currASTNode = &ASTRroot; 
	currCFGNode = new CFGNode("program", 0);
	rootCFGNode = currCFGNode;
	if (currASTNode == NULL) {
		cout << "Why is the AST root null?" << endl;
	}

	// iteratively traverse each of the type = procedure nodes in AST
	// for each AST Node :
	//		- update the currCFGNode to point to CFGRoot 
	//		- create CFG for procedure and connect it to the CFGRoot 
	//		- update parent pointer 
	vector<Node*> children = currASTNode->getChild();

	for (unsigned int i=0; i<children.size(); i++) {
		currASTNode = children[i]->getChild(0);
		currCFGNode = rootCFGNode; 	
		createCFGForStmtLst(*currASTNode, pkb);
	}

	
}

// traverse the CFG
// then set the next relationship in PKB
// set the next ranges relationship in NextPair in PKB
void DesignExtractor::setNextRelationshipDriver(PKB &pkb) {
	CFGNode* source = rootCFGNode;

	if (debugModeIteration2) {
		cout << "Max prog line now is: " << counter << "."<< endl;
	}
	vector<int> temp(counter+1);
	std::fill (temp.begin(), temp.end(), 0);
	visited = temp; 

	setNextRelationship(*source, pkb);
	setNextPairRelationship(pkb);

	visited.clear();
}

void DesignExtractor::setNextPairRelationship(PKB &pkb) {
	// PKB GET: 
	set<int> allStmts = pkb.getAllStmts(TypeTable::STMT);
	set<int>::iterator it1;
	for (it1 = allStmts.begin(); it1 != allStmts.end(); ++it1) {
		int stmtNum = *it1;
		if (debugModeIteration3) {
			//cout << "StmtNum is " << stmtNum << endl;
		}
		// PKB GET:
		set<int> v = pkb.getNext(stmtNum);
		set<int>::iterator it2;
		for (it2 = v.begin(); it2 != v.end(); ++it2) {
			int i = *it2;
			if (debugModeIteration3) {
				//cout << "Child is " << i << endl;
			}
			pair<int, int> pairToAdd = findPair(i, pkb);
			if (debugModeIteration3) {
				cout << "setToNextPair(" << stmtNum  << "): ["<< pairToAdd.first << ", " << pairToAdd.second << "]" << endl;
			}
			// PKB SET: 
			pkb.setToNextPair(stmtNum, pairToAdd);
		}
	}

}

pair<int, int> DesignExtractor::findPair(int fromIndex, PKB &pkb) {
	// PKB GET: 
	set<int> v = pkb.getNext(fromIndex);
	// cout << "getNext(" << fromIndex << ") " << "set size is: " << v.size() << endl; 
	int toIndex = fromIndex; 
	
	while (true) {
		const bool is_in = v.find(toIndex+1) != v.end();
		if (is_in) {
			/* v contains toIndex+1*/
			toIndex += 1; 
			//PKB GET: 
			v = pkb.getNext(toIndex);
		} else {
			/* v does not contain toIndex+1*/
			break;
		}
	}
	return pair<int, int>(fromIndex, toIndex);
}

void DesignExtractor::setNextRelationship(CFGNode &node, PKB &pkb) {
	int fromProgLine = node.getProgLine();
	visited[fromProgLine] = 1; 
	vector<CFGNode*> children = node.getMultiChild();
	for (unsigned int i=0; i<children.size(); i++) {
		CFGNode* child = children[i];
		int toProgLine = child->getProgLine();
		if (fromProgLine != -1 && toProgLine != -1 && fromProgLine != 0) {
			// PKB SET: 
			pkb.setToNext(fromProgLine, toProgLine);
			if (debugModeIteration2) {
				cout << "setToNext(" << fromProgLine << ", " << toProgLine << ")" <<endl;
			}
		}
		if (toProgLine == -1) {
			while (toProgLine == -1) {
				if (child->getMultiChild().size() == 0) {
					return;
				}
				child = child->getMultiChild(0);
				toProgLine = child->getProgLine();
			}
			if (fromProgLine != 0) {
				// PKB SET:
				pkb.setToNext(fromProgLine, toProgLine);
			}
			if (debugModeIteration2) {
				cout << "setToNext(" << fromProgLine << ", " << toProgLine << ")" <<endl;
			}
		}
		if (visited[toProgLine] == 0) {
			setNextRelationship(*child, pkb);
		}
	}
}

// ASTNode is a pointer to the subtree rooted at the AST Node ":stmtLst"
void DesignExtractor::createCFGForStmtLst(Node &ASTNode, PKB &pkb) {
	Node* tempASTNode;
	tempASTNode = &ASTNode; 

	vector<Node*> children = tempASTNode->getChild();
	if (debugModeIteration2) {
		cout << "size is " << children.size() << endl;
	}
	for (unsigned int i=0; i<children.size(); i++) {
		string type = children[i]->getType();
		int progLine = children[i]->getProgLine();
		if (type == "assign") {
			createCFGForAssign(progLine, pkb);
		} else if (type == "call") {
			createCFGForCall(progLine, pkb);
		} else if (type == "while") {
			createCFGForWhile(children[i]->getChild(), pkb);
		} else if (type == "if") {
			createCFGForIf(children[i]->getChild(), pkb);
		}
	}

	if (currCFGNode->getProgLine() !=  -1) {
		// create new CFGNode with progLine = -1 and attach to current CFGNode 
		//createNewNodeAndAttachToCFG("end", -1);
	}

}

void DesignExtractor::createCFGForAssign(int progLine, PKB &pkb) {
	createNewNodeAndAttachToCFG("assign", progLine, pkb);
}

void DesignExtractor::createCFGForCall(int progLine, PKB &pkb) {
	createNewNodeAndAttachToCFG("call", progLine, pkb);

}

void DesignExtractor::createCFGForWhile(vector<Node*> children, PKB &pkb) {
	int progLine = children[0]->getProgLine();
	createNewNodeAndAttachToCFG("while", progLine, pkb);

	CFGNode* toNode = currCFGNode;
	Node* stmtLst = children[1];
	createCFGForStmtLst(*stmtLst, pkb);

	Node* fromASTNode = children[1]->getChild(children[1]->getChild().size()-1);
	int fromProgLine = fromASTNode->getProgLine();
	CFGNode* fromNode = getCFGNode(fromProgLine);
	foundNode = NULL; 

	if (fromNode != NULL) {
		if (fromNode->getType() == "if") {
			// get the child which is -1 and set that as the fromNode 
			while (fromNode->getProgLine() != -1) {
				if (fromNode->getMultiChild().size() != 0) {
					//fromNode = fromNode->getMultiChild(0);
					fromNode = fromNode->getMultiChild(fromNode->getMultiChild().size()-1);
				} else {
					cout << "Error in DE 1!" << endl;
					break;
				}
			}
		}

		if (debugModeIteration2) {
			cout << "fromNode is found" << endl;
		}
		fromNode->setMultiChild(toNode);
		toNode->setMultiParent(fromNode);
		
		if (debugModeIteration2) {
			cout << "Parent: ";
			fromNode->printCFGNode();
			cout << " Child: ";
			toNode->printCFGNode();
			cout << endl;
		}
	} else {
		cout << "Error in DE 2!" << endl;
	}
	currCFGNode = toNode;
}

void DesignExtractor::createCFGForIf(vector<Node*> children, PKB &pkb) {
	int progLine = children[0]->getProgLine();	
	createNewNodeAndAttachToCFG("if", progLine, pkb);

	CFGNode* ifCFGNode = currCFGNode;
	if (debugModeIteration2) {
		cout << "If node is at: " << ifCFGNode->getProgLine() << endl;
	}
	Node* stmtLst = children[1];
	createCFGForStmtLst(*stmtLst, pkb);
	vector<CFGNode*> leafNodes;
	leafNodes.push_back(currCFGNode);	

	if (debugModeIteration2) {
		cout << "If node is at: " << ifCFGNode->getProgLine() << endl;
	}
	currCFGNode = ifCFGNode;
	stmtLst = children[2];
	createCFGForStmtLst(*stmtLst, pkb);
	leafNodes.push_back(currCFGNode);	

	CFGNode* dummyNode = new CFGNode("dummy", -1);
	while (!leafNodes.empty()) {
		currCFGNode = leafNodes.back();
		currCFGNode->setMultiChild(dummyNode);
		dummyNode->setMultiParent(currCFGNode);
		if (debugModeIteration2) {
			cout << "Parent: ";
			currCFGNode->printCFGNode();
			cout << " Child: ";
			dummyNode->printCFGNode();
			cout << endl;
		}

		if (debugModeIteration2) {
			vector<CFGNode*> temp = currCFGNode->getMultiChild();
			string s = "";
			for (unsigned int i=0; i<temp.size(); i++) {
				int j = temp[i]->getProgLine();
				std::string str;
				std::stringstream out;
				out << j;
				str = out.str();
				s += ( str + " ");
			}
			cout << "Curr node's chidren are: " << s << endl;
		}


		leafNodes.pop_back();
	}
	currCFGNode = dummyNode; 
}

void DesignExtractor::createNewNodeAndAttachToCFG(string type, int progLine, PKB &pkb) {
	CFGNode* newNode = new CFGNode(type, progLine);
	if (debugModeIteration2) {
		cout << "adding new ";
		newNode->printCFGNode();
		cout << endl;
	}	
	currCFGNode->setMultiChild(newNode);
	newNode->setMultiParent(currCFGNode);
	
	if (debugModeIteration2) {
		cout << "Parent: ";
		currCFGNode->printCFGNode();
		cout << " Child: ";
		newNode->printCFGNode();
		cout << endl;
	}
	currCFGNode = newNode; 
	counter = currCFGNode->getProgLine();
	

}

CFGNode* DesignExtractor::getCFGNode(int progLine) {
	if (debugModeIteration2) {
		cout << "getCFGNode(" << progLine << ")" << endl;
		cout << "Max prog line now is: " << counter << "."<< endl;
	}
	vector<int> temp(counter+1);
	std::fill (temp.begin(), temp.end(), 0);
	visited = temp; 

	/*for (std::vector<int>::iterator it=visited.begin(); it!=visited.end(); ++it)
	std::cout << ' ' << *it;
	std::cout << '\n';*/

	CFGNode* source;
	source = rootCFGNode;
	traverseGraph(*source, progLine);
	
	/*for (std::vector<int>::iterator it=visited.begin(); it!=visited.end(); ++it)
	std::cout << ' ' << *it;
	std::cout << '\n';*/
	
	visited.clear();
	return foundNode;
}

void DesignExtractor::traverseGraph(CFGNode &node, int progLine) {
	if (node.getProgLine() == progLine) {
		foundNode = &node;
	}
	try {
		if (node.getProgLine() != -1) {
			visited[node.getProgLine()] = 1;
		}
	} catch (...) {
		cout << "Error caught in DE" << endl;
	}
	vector<CFGNode*> children = node.getMultiChild();
	for (unsigned int i=0; i<children.size(); i++) {
		CFGNode* child = children[i];
		if (visited[child->getProgLine()] == 0 || child->getProgLine() == -1) {
			traverseGraph(*child, progLine);
		}
	}
}

// extracting of modifies and uses relationship for procedures and statements.
// set the modifies and uses relationships for statements and procedures. 
void DesignExtractor::extractRelationships(Node &ASTRoot, unordered_map<PROCINDEX, vector<CALLSPAIR>> callsTable, PKB &pkb) {
	// Run DFS on callsTree to generate toposort queue

	runDFSDriver(callsTable, pkb); 
	if (debugModeIteration1) {
		printQueue();		
	}	
	// For each of the entries in the queue, dequeue and do the following 
	// For the procedure, find the min and max prog line 
	// Find all the variables modified, then set modifies relationship for proglines and procedures
	// Find all the varaibles used, then set uses relationship for proglines and procedures
	
	while (!queueToProcess.empty()) {

		QueueItem item;
		item = queueToProcess.front();
		queueToProcess.pop();
		
		vector<int> progLines = item.getCallsProgLine();
		int procIndex = item.getProcIndex();
		unsigned int firstProgLine = getFirstProgLine(procIndex, ASTRoot, pkb);
		unsigned int lastProgLine = getLastProgLine(procIndex, ASTRoot, pkb);
		if (debugModeIteration1) {
			cout << "Min: " << firstProgLine << ", Max: " << lastProgLine << endl;
		}

		
		for (unsigned int i=firstProgLine; i<=lastProgLine; i++) {
			// PKB GET:
			set<VARINDEX> variablesModifiedByProgLine = pkb.getModified(i);
			// PKB SET: procedure procIndex modifies these variables too
			pkb.setToModifiesProc(procIndex, variablesModifiedByProgLine);
			if (debugModeIteration1) {
				cout << "setToModifesProc(" << procIndex << ", " << "variablesModifiedByProgLine)" << endl;
			}
			// PKB GET: 
			set<VARINDEX> variablesUsedByProgLine = pkb.getUsed(i);
			// PKB SET: procedure procIndex uses these variables too
			pkb.setToUsesProc(procIndex, variablesUsedByProgLine); 
			if (debugModeIteration1) {
				cout << "setToUsesProc(" << procIndex << ", " << "variablesUsedByProgLine)" << endl;
			}
			try {
				for (signed int j=(progLines.size()-1); j>=0; j--) {
					int progLine = progLines[j];
					// PKB SET:
					pkb.setToModifies(progLine, variablesModifiedByProgLine); 
					// PKB SET:
					pkb.setToUses(progLine, variablesUsedByProgLine); 
					// check if progLine is in some container statement. if yes, then add the variables to the parent STMTNUM too.

					if (debugModeIteration1) {
						cout << "progLine: " << progLine << endl;
					} 
					// PKB GET: 
					int parentProgLine = pkb.getParent(progLine);
					bool existsParent = (parentProgLine != -1);
					while (existsParent) {
						if (debugModeIteration1) {
							cout << "parentProgLine: " << parentProgLine << endl;
						}
						// PKB SET:
						pkb.setToModifies(parentProgLine, variablesModifiedByProgLine); 
						if (debugModeIteration1) {
							cout << "setToModifes(" << parentProgLine << ", " << "variablesModifiedByProgLine)" << endl;
						}
						// PKB SET:
						pkb.setToUses(parentProgLine, variablesUsedByProgLine); 
						if (debugModeIteration1) {
							cout << "setToUses(" << parentProgLine << ", " << "variablesUsedByProgLine)" << endl;
						}

						// PKB GET: 
						parentProgLine = pkb.getParent(parentProgLine);
						existsParent = (parentProgLine != -1);
					}
				}
			} catch(const std::runtime_error& re) {
				// specific handling for runtime_error
				std::cerr << "DE: Runtime error: " << re.what() << std::endl;
			} catch(const std::exception& ex) {
				// specific handling for all exceptions extending std::exception, except
				// std::runtime_error which is handled explicitly
				std::cerr << "DE: Error occurred: " << ex.what() << std::endl; 
			} catch(...) {
				// catch any other errors (that we have no information about)
				std::cerr << "DE: Unknown failure occured. Possible memory corruption" << std::endl;
			}	

		}
	}

}

void DesignExtractor::clear( std::queue<QueueItem> &q ) {
   std::queue<QueueItem> empty;
   std::swap( q, empty );
}

void DesignExtractor::runDFSDriver(unordered_map<PROCINDEX, vector<CALLSPAIR>> callsTable, PKB &pkb) {
	if (debugModeIteration1) {
		cout << "printing queue again: " << endl;
		printQueue();
	}
	vector<int> emptyVector = vector<int>();

	vector<int> temp(pkb.getNumProcedures()+1);
	std::fill (temp.begin(), temp.end(), 0);
	visited = temp; 

	/*for (std::vector<int>::iterator it=visited.begin(); it!=visited.end(); ++it)
	std::cout << ' ' << *it;
	std::cout << '\n';
	*/

	// change to 1 because calls tree has root 1. All proc indices start with 1 
	DFS(1, emptyVector, callsTable, visited);
	visited.clear();

}

void DesignExtractor::DFS(int source, vector<int> progLine, unordered_map<PROCINDEX, vector<CALLSPAIR>> callsTable, vector<int> visited) {
	try {
		if (debugModeIteration1) {
			cout << "callsTable.at("<< source<< ").empty(): " << callsTable.at(source).empty() << endl;
		}

		vector<CALLSPAIR> v;
		v = vector<CALLSPAIR>();
		if (debugModeIteration1) {
			cout << "empty v created" << endl;
		}
		v = callsTable.at(source);
		if (debugModeIteration1) {
 			cout << "v updated" << endl;
		}
		
		if (visited[source] == 0 && v.empty() == 0) {
			for (unsigned int i=0; i<v.size(); i++) {
				vector<int> tempProgLine = progLine; 
				tempProgLine.push_back(v.at(i).second);

				vector<int> tempVisited = visited;
				tempVisited[source] = 1; 
				DFS(v.at(i).first, tempProgLine, callsTable, tempVisited); 
			}
			
		}

		if (debugModeIteration1) {
				cout << "push to queue: ";
				QueueItem(source, progLine).print();
		}
		queueToProcess.push(QueueItem(source, progLine));

	} catch(const std::runtime_error& re) {
		// specific handling for runtime_error
		std::cerr << "DE: Runtime error: " << re.what() << std::endl;
	} catch(const std::exception& ex) {
		// specific handling for all exceptions extending std::exception, except
		// std::runtime_error which is handled explicitly
		// cout << "Source: " << source << endl; 
		//std::cerr << "Error occurred: " << ex.what() << std::endl; 
		if (debugModeIteration1) {
			cout << "push to queue from catch: ";
			QueueItem(source, progLine).print();
		}
		queueToProcess.push(QueueItem(source, progLine));
		
	} catch(...) {
		// catch any other errors (that we have no information about)
		std::cerr << "DE: Unknown failure occured. Possible memory corruption" << std::endl;
	}

}

//
//void DesignExtractor::DFS(int source, vector<int> progLine, unordered_map<PROCINDEX, vector<CALLSPAIR>> callsTable) {
//	try {
//		if (debugModeIteration1) {
//			cout << "callsTable.at("<< source<< ").empty(): " << callsTable.at(source).empty() << endl;
//		}
//
//		vector<CALLSPAIR> v;
//		v = vector<CALLSPAIR>();
//		if (debugModeIteration1) {
//			cout << "empty v created" << endl;
//		}
//		v = callsTable.at(source);
//		if (debugModeIteration1) {
// 			cout << "v updated" << endl;
//		}
//		
//		if (v.empty() == 0) {
//			for (unsigned int i=0; i<v.size(); i++) {
//				vector<int> tempProgLine = progLine; 
//				tempProgLine.push_back(v.at(i).second);
//				DFS(v.at(i).first, tempProgLine, callsTable); 
//			}
//			if (debugModeIteration1) {
//				cout << "push to queue: ";
//				QueueItem(source, progLine).print();
//			}
//			queueToProcess.push(QueueItem(source, progLine));
//		
//		
//		/*
//		unordered_map<PROCINDEX, vector<CALLSPAIR>>::iterator it1;
//		bool sourceFound = 0;
//		for (it1 = callsTable.begin(); it1!=callsTable.end(); it1++){
//			if (it1->first == source) {
//				sourceFound = 1;
//				break;
//			}
//		}
//		if (sourceFound == 0) {
//			return;
//		}
//		for (vector<CALLSPAIR>::iterator it2 = it1->second.begin(); it2!=it1->second.end(); it2++) {
//			// it2->first is the PROCINDEX; it2->second is the PROGLINE
//			vector<int> tempProgLine = progLine;
//			tempProgLine.push_back(it2->second);
//			DFS(it2->first, tempProgLine, callsTable);
//		}
//		cout << "push to queue: ";
//		QueueItem(source, progLine).print();
//		queueToProcess.push(QueueItem(source, progLine));
//		*/
//
//		}
//	} catch(const std::runtime_error& re) {
//		// specific handling for runtime_error
//		std::cerr << "DE: Runtime error: " << re.what() << std::endl;
//	} catch(const std::exception& ex) {
//		// specific handling for all exceptions extending std::exception, except
//		// std::runtime_error which is handled explicitly
//		// cout << "Source: " << source << endl; 
//		std::cerr << "Error occurred: " << ex.what() << std::endl; 
//		if (debugModeIteration1) {
//			cout << "push to queue from catch: ";
//			QueueItem(source, progLine).print();
//		}
//		queueToProcess.push(QueueItem(source, progLine));
//		
//	} catch(...) {
//		// catch any other errors (that we have no information about)
//		std::cerr << "DE: Unknown failure occured. Possible memory corruption" << std::endl;
//	}
//
//}
//

void DesignExtractor::printCallsTable(unordered_map<PROCINDEX, vector<CALLSPAIR>> callsTable) {
	cout << "Calls Table is:" << endl; 
	for (auto it1 = callsTable.begin(); it1 != callsTable.end(); ++it1) {
		cout << it1->first  << ": "; 
		vector<CALLSPAIR> v = it1->second;
		for (vector<CALLSPAIR>::iterator it2 = v.begin(); it2 != v.end(); ++it2) {
			cout << "(" << it2->first << ", " << it2->second << ") ";
		}
		cout << endl; 
	}

}

void DesignExtractor::printQueue() {
	queue<QueueItem> backup;
	cout << "Toposort queue is: " << endl;
	while (!queueToProcess.empty()) {
		QueueItem item;
		item = queueToProcess.front();
		queueToProcess.pop();
		item.print();
		backup.push(item);
	}
	queueToProcess = backup; 
}

int DesignExtractor::getFirstProgLine(int procIndex, Node &ASTRoot, PKB &pkb) {
	Node* curr = &ASTRoot; 
	string currType = curr->getType();
	// vector<Node*> children = curr->getChild();
	for (unsigned int i=0;i<curr->getChild().size();i++) {
		// PKB GET: 
		if (procIndex == pkb.getProcIndex(curr->getChild(i)->getData())) {
			curr = (curr->getChild(i))->getChild(0);
			break;
		}
	}
	while (curr->getChild(0) != NULL) {
		curr = curr->getChild(0); 
	}
	return curr->getProgLine();
}

int DesignExtractor::getLastProgLine(int procIndex, Node &ASTRoot, PKB &pkb) {
	Node* curr = &ASTRoot; 
	string currType = curr->getType();
	// vector<Node*> children = curr->getChild();
	for (unsigned int i=0;i<curr->getChild().size();i++) {
		// PKB GET: 
		if (procIndex == pkb.getProcIndex(curr->getChild(i)->getData())) {
			curr = (curr->getChild(i))->getChild(0);
			break;
		}
	}
	vector<Node*> children = vector<Node*>(); 
	children = curr->getChild();
	while (!children.empty()) {
		curr = children[children.size()-1];
		children = curr->getChild();
	}
	return curr->getProgLine();
}

