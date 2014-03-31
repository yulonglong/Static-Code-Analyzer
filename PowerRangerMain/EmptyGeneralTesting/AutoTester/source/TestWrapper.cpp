#include "TestWrapper.h"
#include "QueryProcessor.h"
#include <vector>

using namespace std;

// implementation code of WrapperFactory - do NOT modify the next 5 lines
AbstractWrapper* WrapperFactory::wrapper = 0;
AbstractWrapper* WrapperFactory::createWrapper() {
  if (wrapper == 0) wrapper = new TestWrapper;
  return wrapper;
}
// Do not modify the following line
volatile bool TestWrapper::GlobalStop = false;

// a default constructor
TestWrapper::TestWrapper() {
  // create any objects here as instance variables of this class
  // as well as any initialization required for your spa program
}

// method for parsing the SIMPLE source
void TestWrapper::parse(std::string filename) {
	// call your parser to do the parsing
  // ...rest of your code...
}

// method to evaluating a query
void TestWrapper::evaluate(std::string query, std::list<std::string>& results){
	Query parsedQuery = parse(query);
	vector<int> answers = evaluateQuery(parsedQuery);

	for(vector<int>::iterator it = answers.begin(); it!=answers.end(); it++){
		int currAnswer = it->getToken1();
		string str = static_cast<ostringstream*>( &(ostringstream() << currAnswer) )->str();
		results.push_back(str);
	}

}
