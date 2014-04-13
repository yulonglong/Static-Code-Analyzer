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
		cout<<"End Parse query"<<endl;
		cout<<"Begin Evaluate query"<<endl;
		if(parsedQuery.getSelectedSyn() == "BOOLEAN") {
			bool ans = qe.evaluateQueryBoolean(parsedQuery);
			if(ans)
				result.push_back("true");
			else
				result.push_back("false");
		}
		else {
			vector<int> ans = qe.evaluateQuery(parsedQuery);
			if(parsedQuery.getSelectedSyn().compare("v")==0) {
				VarTable* varTable = pkb->getVarTable();

				for(size_t i = 0; i < ans.size(); i++)
					if(ans.at(i) != -1)
						result.push_back(varTable->getVarName(ans.at(i)));
			}
			else {
			for(size_t i = 0; i < ans.size(); i++)
				if(ans.at(i) != -1)
					result.push_back(to_string(static_cast<long long>(ans.at(i))));
			}
		}
		cout<<"End Evaluate query"<<endl;
	}
}