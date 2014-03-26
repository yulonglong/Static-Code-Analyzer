#ifndef QUERYPARSER_H
#define QUERYPARSER_H

#include "Query.h"
#include <string>

using namespace std;

class QueryParser{
private:

public:
	Query parse(string);
}
#endif // QUERYPARSER_H_INCLUDED