#pragma once

#include "QueryProcessor.h"
#include "iostream"
using namespace std;


void queryDriver(string query, list<string> &result, PKB *pkb){
	cout<<"Begin Parse query"<<endl;
	QueryParser qp;
	QueryEvaluator qe = QueryEvaluator::QueryEvaluator(pkb);

	bool isValid = qp.validate(query);
	if (isValid) {
		Query parsedQuery = qp.parse();
		if(parsedQuery.getSelectedSyn() == "BOOLEAN") {
			cout<<"End Parse query"<<endl;
			cout<<"Begin Evaluate query"<<endl;
			bool ans = qe.evaluateQueryBoolean(parsedQuery);
			if(ans)
				result.push_back("true");
			else
				result.push_back("false");
			cout<<"End Evaluate query"<<endl;
		}
		else {
			cout<<"End Parse query"<<endl;
			cout<<"Begin Evaluate query"<<endl;
			cout<< "autoteste 333 size " << pkb->getFollows()->followedByTable.size()<<endl;
			vector<int> ans = qe.evaluateQuery(parsedQuery);
			for(size_t i = 0; i < ans.size(); i++)
				if(ans.at(i) != -1)
					result.push_back(to_string(static_cast<long long>(ans.at(i))));
			cout<<"End Evaluate query"<<endl;
		
	}
}