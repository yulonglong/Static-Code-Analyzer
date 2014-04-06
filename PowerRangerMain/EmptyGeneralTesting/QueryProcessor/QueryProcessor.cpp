#pragma once

#include "QueryProcessor.h"
using namespace std;


void queryDriver(string query, list<string> &result, PKB &pkb){
	QueryParser qp;
	QueryEvaluator qe = QueryEvaluator::QueryEvaluator(pkb);
	Query parsedQuery = qp.parse(query);

	if(parsedQuery.getSelectedSyn() == "BOOLEAN") {
		bool ans = qe.evaluateQueryBoolean(parsedQuery);
		if(ans)
			result.push_back("true");
		else
			result.push_back("false");
	}
	else {
		vector<int> ans = qe.evaluateQuery(parsedQuery);
		for(int i=0; i<ans.size(); i++)
			result.push_back(to_string(static_cast<long long>(ans.at(i))));
	}
}