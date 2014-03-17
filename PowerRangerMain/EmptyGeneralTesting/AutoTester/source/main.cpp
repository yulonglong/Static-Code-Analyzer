#include "CodeParser.h"
#include "Node.h"
#include <iostream>
using namespace std;

int main(){
	Node* ASTRoot;
	ASTRoot = parse("testCodeInput.txt");
	//comment this function to stop printing
	printPreOrderExpressionTree(ASTRoot);
	int a;
	std::cin >> a;
	return 0;
}