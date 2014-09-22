#pragma once

#include "QueryProcessor.h"
#include <iostream>
using namespace std;


void queryDriver(string query, list<string> &result, PKB *pkb){
	/*
	cout<<"Begin parse query"<<endl;
	QueryParser qp;
	QueryEvaluator qe = QueryEvaluator::QueryEvaluator(pkb);

	//bool isValid = qp.validate(query);
	bool isValid = true;

	Query parsedQuery = qp.queryParse(query,isValid);

	if(!isValid){
		cout << "Query Invalid" << endl;
		return;
	}

	cout<<"End parse query"<<endl;
	cout<<"Begin evaluate query"<<endl;

	//Loophole here. I've changed getSelectedSyn to getSelectedSyn.at(0) for the time being since selected syn is a vector now
	if(parsedQuery.getSelectedSyn().at(0) == "BOOLEAN") {
		bool ans = qe.evaluateQueryBoolean(parsedQuery);
		if(ans)
			result.push_back("true");
		else
			result.push_back("false");
	}
	else {
		vector<int> ans = qe.evaluateQuery(parsedQuery);
		unordered_map<string, TypeTable::SynType> m = parsedQuery.getSynTable();
		unordered_map<string, TypeTable::SynType>::iterator i = m.find(parsedQuery.getSelectedSyn().at(0));//Same problem for selectedSyn
		TypeTable tt = *pkb->getTypeTable();

		if(i->second == 6) {
			VarTable* varTable = pkb->getVarTable();

			for(size_t i = 0; i < ans.size(); i++)
				if(ans.at(i) != -1)
					result.push_back(varTable->getVarName(ans.at(i)));
		}
		else if(i->second == 7) {
			ConstTable* constTable = pkb->getConstTable();

			for(size_t i = 0; i < ans.size(); i++)
				if(ans.at(i) != -1)
					result.push_back(constTable->getConst(ans.at(i)));
		}

		else {
		for(size_t i = 0; i < ans.size(); i++)
			if(ans.at(i) != -1)
				result.push_back(to_string(static_cast<long long>(ans.at(i))));
		}
	}
	cout<<"End evaluate query"<<endl;*/
}