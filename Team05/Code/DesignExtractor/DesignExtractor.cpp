//@author Ipsita Mohapatra
//DesignExtractor.cpp

#pragma once

#include "DesignExtractor.h"
using namespace std;

int counter = -1;
Node* rootCFGNode;
Node* currASTNode;
Node* currCFGNode;
// Node* CFGRoot;
// Node* ASTRoot;

//unordered_map<PROCINDEX, vector<CALLSPAIR>> callsTable; 
// VarTable* varTable; 
// ProcTable* procTable; 
queue<QueueItem> queueToProcess;

void extractorDriver(PKB *pkb) {
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

	// printCallsTable(callsTable);
	// cout << "DE has obtained tables from PKB" << endl;
	
	Node* ASTRoot = pkb->getASTRoot();
	Node* CFGRoot = pkb->getCFGRoot();
	
	extractRelationships(*ASTRoot, callsTable, *procTable, *modifies, *uses, *parent);
	cout << "DE: Extracted Relationships" << endl;
	
	/*
	try {
		// cout << "Building CFG..." << endl;
		// CFGRoot = buildCFG(*ASTRoot);
		extractRelationships(*ASTRoot, callsTable);
	} catch(const std::runtime_error& re) {
		// speciffic handling for runtime_error
		std::cerr << "Runtime error: " << re.what() << std::endl;
	} catch(const std::exception& ex) {
		// speciffic handling for all exceptions extending std::exception, except
		// std::runtime_error which is handled explicitly
		std::cerr << "Error occurred: " << ex.what() << std::endl; 
	} catch(...) {
		// catch any other errors (that we have no information about)
		std::cerr << "Unknown failure occured. Possible memory corruption" << std::endl;
	}
	*/
	// pkb->setCFGRoot(CFGRoot);
}



// extracting of modifies and uses relationship for procedures and statements.
// set the modifies and uses relationships for statements and procedures. 
void extractRelationships(Node &ASTRoot, unordered_map<PROCINDEX, vector<CALLSPAIR>> callsTable, ProcTable &procTable, Modifies &modifies, Uses &uses, Parent &parent) {
	// Run DFS on callsTree to generate toposort queue
	runDFSDriver(callsTable); 

	// printQueue();
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
		// cout << "Min: " << firstProgLine << ", Max: " << lastProgLine << endl;

		
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

					// cout << "progLine: " << progLine << endl;
					int parentProgLine = parent.getParent(progLine);
					bool existsParent = (parentProgLine != -1);
					while (existsParent) {
						// cout << "parentProgLine: " << parentProgLine << endl;
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

void clear( std::queue<QueueItem> &q ) {
   std::queue<QueueItem> empty;
   std::swap( q, empty );
}

void runDFSDriver(unordered_map<PROCINDEX, vector<CALLSPAIR>> callsTable) {
	// cout << "printing queue again: " << endl;
	// printQueue();
	vector<int> emptyVector = vector<int>();
	DFS(0, emptyVector, callsTable);
}

void DFS(int source, vector<int> progLine, unordered_map<PROCINDEX, vector<CALLSPAIR>> callsTable) {
	try {
		// cout << callsTable.at(source).empty() << endl;
		vector<CALLSPAIR> v;
		v = vector<CALLSPAIR>();
		// cout << "empty v created" << endl;
		v = callsTable.at(source);
		// cout << "v updated" << endl;
		if (!v.empty()) {
			for (unsigned int i=0; i<callsTable.at(source).size(); i++) {
				vector<int> tempProgLine = progLine; 
				tempProgLine.push_back(callsTable.at(source).at(i).second);
				DFS(callsTable.at(source).at(i).first, tempProgLine, callsTable); 
			}
			// cout << "push to queue: ";
			// QueueItem(source, progLine).print();
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

// actual building of CFG 
Node* buildCFG(Node &ASTNode) {
	currASTNode = &ASTNode; 
	counter++; 

	string ASTNodeType = ASTNode.getType();
	if (ASTNodeType == "program") {
		currCFGNode = new Node("program", counter);
		rootCFGNode = currCFGNode;
	} else if (ASTNodeType == "procedure") {
		cout << "this is a procedure" << endl; 
	} else {
		cout << "yay!" << endl; 
	}

	// go through all children of current AST node 
	for (unsigned i=0;i<ASTNode.getChild().size();i++) {
		currCFGNode = buildCFG(*ASTNode.getChild(i));	
	}
	return currCFGNode;
}

void printCallsTable(unordered_map<PROCINDEX, vector<CALLSPAIR>> callsTable) {
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

void printQueue() {
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

int getFirstProgLine(int procIndex, Node &ASTRoot, ProcTable &procTable) {
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


int getLastProgLine(int procIndex, Node &ASTRoot, ProcTable &procTable) {
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

