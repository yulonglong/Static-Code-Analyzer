#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <iostream>
#include <CodeParser.h>
#include <VarTable.h>
#include <ProcTable.h>
// #include <QueryParser.h>

using namespace std;

int main(int argc, char* argv[])
{
// Get the top level suite from the registry
CPPUNIT_NS::Test *suite = CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest();
CppUnit::TextUi::TestRunner runner;

//parse the SIMPLE soource code into the parser
//Parse();

//Call of DesignExtractor
//Extract();

string fileName = "Source1"; 
VarTable varTable; 
ProcTable procTable;

Parse(fileName, varTable, procTable);

string s = "assign a; Select a;";

ParseAndEvaluate();

// ouput result to screen 

runner.addTest(suite);
bool wasSucessful = runner.run();

//getchar();

return wasSucessful ? 0 : 1;
}


void Parse(string fileName, VarTable &varTable, ProcTable &procTable) {
	//parse the SIMPLE source code into the parser
	parseCode(fileName, varTable, procTable);
}

void Extract() {
}

// TODO: include evaluation methods. 
void ParseAndEvaluate(string s) {
	// QueryParser qp;
	// Query query = qp.parse(s);
}
