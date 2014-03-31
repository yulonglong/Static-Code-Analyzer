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

	runner.addTest(suite);
	bool wasSucessful = runner.run();

	getchar();

	return wasSucessful ? 0 : 1;
}