#include "CodeParser.h"
#include "Node.h"
#include "VarTable.h"
#include "ProcTable.h"
#include <iostream>
using namespace std;

int main(){
	Node* ASTRoot;
	VarTable varTable;
	ProcTable procTable;
	ASTRoot = parse("testCodeInput.txt",varTable,procTable);
	//comment this function to stop printing
	ASTRoot->printPreOrderExpressionTree(ASTRoot);

	//testing varTable and procTable
	cout << varTable.getVarName(0) << endl;
	cout << varTable.getVarName(1) << endl;
	cout << varTable.getVarName(2) << endl;
	cout << varTable.getVarName(3) << endl;
	cout << procTable.getProcName(0) << endl;
	cout << procTable.getProcName(1) << endl;
	cout << procTable.getProcName(2) << endl;

	int a;
	std::cin >> a;
	return 0;
}