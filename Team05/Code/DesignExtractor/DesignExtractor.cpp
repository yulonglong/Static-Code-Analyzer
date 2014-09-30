//@author Ipsita Mohapatra
//DesignExtractor.cpp

#pragma once

#include "DesignExtractor.h"	
using namespace std;

bool debugModeIteration1 = 0; 
bool debugModeIteration2 = 1; 

int counter = 0;
vector<int> visited; 
CFGNode* foundNode; // for CFG traversal

CFGNode* rootCFGNode;
CFGNode* currCFGNode;
//Node* currASTNode;

queue<QueueItem> queueToProcess;

void DesignExtractor::extractorDriver(PKB *pkb) {
	cout << "Begin DesignExtractor" << endl;

	TypeTable* typeTable = pkb->getTypeTable();
	ConstTable* constTable = pkb->getConstTable();
	Parent* parent = pkb->getParent();
	Follows* follows = pkb->getFollows();
	Modifies* modifies = pkb->getModifies();
	Uses* uses = pkb->getUses();
	VarTable* varTable = pkb->getVarTable();
	ProcTable* procTable = pkb->getProcTable();

	unordered_map<PROCINDEX, vector<CALLSPAIR>> callsTable; 
	callsTable = pkb->getCallsTable();
	
	if (debugModeIteration1) {
		printCallsTable(callsTable);
		cout << "DE has obtained tables from PKB" << endl;
	}
	
	Node* ASTRoot = pkb->getASTRoot();
	Node* CFGRoot = pkb->getCFGRoot();
	
	extractRelationships(*ASTRoot, callsTable, *procTable, *modifies, *uses, *parent);
	cout << "DE: Extracted Relationships" << endl;
	
	buildCFGDriver(*pkb, *ASTRoot, *CFGRoot);

	cout << "End DesignExtractor" << endl;
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

	pkb.setCFGRoot(rootCFGNode);
	CFGNode* temp = pkb.getCFGRoot();
	if (temp == NULL) {
	cout << "here" << endl;
	}
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

	
	// if want end node, then after each iteration, push back the pointer to CFGNode into a vector.
	// after for loop ends, pop one by one and make it the parent of the terminating -1 node
	// THERE WILL BE A SINGLE -1 NODE TO DENOTE END OF CFG
}

// traverse the CFG and then set the next relationship in PKB
void DesignExtractor::setNextRelationshipDriver(PKB &pkb) {
	CFGNode* source = rootCFGNode;

	if (debugModeIteration2) {
		cout << "Max prog line now is: " << counter << "."<< endl;
	}
	vector<int> temp(counter+1);
	std::fill (temp.begin(), temp.end(), 0);
	visited = temp; 

	setNextRelationship(*source, pkb);

	visited.clear();
}

void DesignExtractor::setNextRelationship(CFGNode &node, PKB &pkb) {
	int fromProgLine = node.getProgLine();
	visited[fromProgLine] = 1; 
	vector<CFGNode*> children = node.getMultiChild();
	for (unsigned int i=0; i<children.size(); i++) {
		CFGNode* child = children[i];
		int toProgLine = child->getProgLine();
		if (fromProgLine != -1 && toProgLine != -1) {
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
			pkb.setToNext(fromProgLine, toProgLine);
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

	cout << "here" << endl;
	if (fromNode != NULL) {
		if (fromNode->getType() == "if") {
			// get the child which is -1 and set that as the fromNode 
			while (fromNode->getProgLine() != -1) {
				if (fromNode->getMultiChild().size() != 0) {
					fromNode = fromNode->getMultiChild(0);
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

	//for (std::vector<int>::iterator it=visited.begin(); it!=visited.end(); ++it)
	//std::cout << ' ' << *it;
	//std::cout << '\n';

	visited.clear();

	if (foundNode != NULL) {
		return foundNode;
	} else {
		return NULL;
	}
}

void DesignExtractor::traverseGraph(CFGNode &node, int progLine) {
	if (node.getProgLine() == progLine) {
		foundNode = &node;
	}
	try {
		visited[node.getProgLine()] = 1; 
	} catch (...) {
		cout << "Error caught" << endl;
	}
	vector<CFGNode*> children = node.getMultiChild();
	for (unsigned int i=0; i<children.size(); i++) {
		CFGNode* child = children[i];
		if (visited[child->getProgLine()] == 0) {
			traverseGraph(*child, progLine);
		}
	}
}

// extracting of modifies and uses relationship for procedures and statements.
// set the modifies and uses relationships for statements and procedures. 
void DesignExtractor::extractRelationships(Node &ASTRoot, unordered_map<PROCINDEX, vector<CALLSPAIR>> callsTable, ProcTable &procTable, Modifies &modifies, Uses &uses, Parent &parent) {
	// Run DFS on callsTree to generate toposort queue
	runDFSDriver(callsTable); 

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
		unsigned int firstProgLine = getFirstProgLine(procIndex, ASTRoot, procTable);
		unsigned int lastProgLine = getLastProgLine(procIndex, ASTRoot, procTable);
		if (debugModeIteration1) {
			cout << "Min: " << firstProgLine << ", Max: " << lastProgLine << endl;
		}

		
		for (unsigned int i=firstProgLine; i<=lastProgLine; i++) {
			vector<VARINDEX> variablesModifiedByProgLine = modifies.getModifies(i);
			// SET: procedure procIndex modifies these variables too
			modifies.setModifiesProc(procIndex, variablesModifiedByProgLine);

			vector<VARINDEX> variablesUsedByProgLine = uses.getUses(i);
			// SET: procedure procIndex uses these variables too
			uses.setUsesProc(procIndex, variablesUsedByProgLine); 
			
			try {
				for (signed int j=(progLines.size()-1); j>=0; j--) {
					int progLine = progLines[j];
					// SET:
					modifies.setModifies(progLine, variablesModifiedByProgLine); 
					// SET:
					uses.setUses(progLine, variablesUsedByProgLine); 
					// check if progLine is in some container statement. if yes, then add the variables to the parent STMTNUM too.

					if (debugModeIteration1) {
						cout << "progLine: " << progLine << endl;
					} 
					int parentProgLine = parent.getParent(progLine);
					bool existsParent = (parentProgLine != -1);
					while (existsParent) {
						if (debugModeIteration1) {
							cout << "parentProgLine: " << parentProgLine << endl;
						}
						// SET:
						modifies.setModifies(parentProgLine, variablesModifiedByProgLine); 
						// SET:
						uses.setUses(parentProgLine, variablesUsedByProgLine); 
						parentProgLine = parent.getParent(parentProgLine);
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

void DesignExtractor::runDFSDriver(unordered_map<PROCINDEX, vector<CALLSPAIR>> callsTable) {
	if (debugModeIteration1) {
		cout << "printing queue again: " << endl;
		printQueue();
	}
	vector<int> emptyVector = vector<int>();
	DFS(0, emptyVector, callsTable);
}

void DesignExtractor::DFS(int source, vector<int> progLine, unordered_map<PROCINDEX, vector<CALLSPAIR>> callsTable) {
	try {
		if (debugModeIteration1) {
			cout << callsTable.at(source).empty() << endl;
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

		if (!v.empty()) {
			for (unsigned int i=0; i<callsTable.at(source).size(); i++) {
				vector<int> tempProgLine = progLine; 
				tempProgLine.push_back(callsTable.at(source).at(i).second);
				DFS(callsTable.at(source).at(i).first, tempProgLine, callsTable); 
			}
			if (debugModeIteration1) {
				cout << "push to queue: ";
				QueueItem(source, progLine).print();
			}
			queueToProcess.push(QueueItem(source, progLine));
		
		
		/*
		unordered_map<PROCINDEX, vector<CALLSPAIR>>::iterator it1;
		bool sourceFound = 0;
		for (it1 = callsTable.begin(); it1!=callsTable.end(); it1++){
			if (it1->first == source) {
				sourceFound = 1;
				break;
			}
		}
		if (sourceFound == 0) {
			return;
		}
		for (vector<CALLSPAIR>::iterator it2 = it1->second.begin(); it2!=it1->second.end(); it2++) {
			// it2->first is the PROCINDEX; it2->second is the PROGLINE
			vector<int> tempProgLine = progLine;
			tempProgLine.push_back(it2->second);
			DFS(it2->first, tempProgLine, callsTable);
		}
		cout << "push to queue: ";
		QueueItem(source, progLine).print();
		queueToProcess.push(QueueItem(source, progLine));
		*/

		}
	} catch(const std::runtime_error& re) {
		// specific handling for runtime_error
		std::cerr << "DE: Runtime error: " << re.what() << std::endl;
	} catch(const std::exception& ex) {
		// specific handling for all exceptions extending std::exception, except
		// std::runtime_error which is handled explicitly
		// cout << "Source: " << source << endl; 
		// std::cerr << "Error occurred: " << ex.what() << std::endl; 
		// cout << "push to queue from catch: ";
		 // QueueItem(source, progLine).print();
		queueToProcess.push(QueueItem(source, progLine));
	} catch(...) {
		// catch any other errors (that we have no information about)
		std::cerr << "DE: Unknown failure occured. Possible memory corruption" << std::endl;
	}

}


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

int DesignExtractor::getFirstProgLine(int procIndex, Node &ASTRoot, ProcTable &procTable) {
	Node* curr = &ASTRoot; 
	string currType = curr->getType();
	// vector<Node*> children = curr->getChild();
	for (unsigned int i=0;i<curr->getChild().size();i++) {
		if (procIndex == procTable.getProcIndex(curr->getChild(i)->getData())) {
			curr = (curr->getChild(i))->getChild(0);
			break;
		}
	}
	while (curr->getChild(0) != NULL) {
		curr = curr->getChild(0); 
	}
	return curr->getProgLine();
}

int DesignExtractor::getLastProgLine(int procIndex, Node &ASTRoot, ProcTable &procTable) {
	Node* curr = &ASTRoot; 
	string currType = curr->getType();
	// vector<Node*> children = curr->getChild();
	for (unsigned int i=0;i<curr->getChild().size();i++) {
		if (procIndex == procTable.getProcIndex(curr->getChild(i)->getData())) {
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

