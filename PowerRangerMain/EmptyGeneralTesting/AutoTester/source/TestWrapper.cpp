#include "TestWrapper.h"
#include "QueryParser.h"
#include "CodeParser.h"

// implementation code of WrapperFactory - do NOT modify the next 5 lines
AbstractWrapper* WrapperFactory::wrapper = 0;
AbstractWrapper* WrapperFactory::createWrapper() {
  if (wrapper == 0) wrapper = new TestWrapper;
  return wrapper;
}
// Do not modify the following line
volatile bool TestWrapper::GlobalStop = false;

// a default constrSuctor
TestWrapper::TestWrapper() {
  // create any objects here as instance variables of this class
  // as well as any initialization required for your spa program
}

// method for parsing the SIMPLE source
void TestWrapper::parse(std::string filename) {

	//KESTER FILL IN THIS.. basically call your parser.. i will only pass you the pkb pointer..
	//So something like parser(pkb);

	VarTable varTable;
	ProcTable procTable;
	TypeTable typeTable;
	Follows follows;
	Parent parent;

	Node* ASTRoot = parseCode(filename,varTable,procTable,typeTable,follows,parent);
	// call your parser to do the parsing
  // ...rest of your code...
}

// method to evaluating a query
void TestWrapper::evaluate(std::string query, std::list<std::string>& results){
// call your evaluator to evaluate the query here
  // ...code to evaluate query...


	//HOWEVER DOING QUERY PLS FILL THIS IN.. WHICH METHOD YOU CALL.. I WILL PASS YOU THE WHOLE PKB
	//sth like evaluate(pkb);

  // store the answers to the query in the results list (it is initially empty)
  // each result must be a string.
}
