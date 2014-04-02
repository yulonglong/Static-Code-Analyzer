#include "Query.h"
#include "Relationship.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

int main()
{
	/*
	QUERY EXAMPLE:
	assign a, while w, if i;
	SELECT a such that Follows (a,2) and Parent (w, a);
	*/

	/*
	Query pre-processor will create the following
	*/
	unordered_map<string, Query::SType> mmap;
	mmap.insert(make_pair("a", Query::ASSIGN));
	mmap.insert(make_pair("w", Query::WHILE));
	mmap.insert(make_pair("i", Query::IF));

	Relationship relOne("FOLLOWS", "a", "2");
	Relationship relTwo("PARENT", "w", "a");

	Query myQuery("a");
	myQuery.addSynTable(mmap);
	myQuery.addRelationship(relOne);
	myQuery.addRelationship(relTwo);
	
	/*
	Testing Query operations
	Sample operations that query evaluator can use to extract info from Query object
	*/

	// GETTING THE SYNONYM TO SELECT
	string selectSyn = myQuery.getSelectSyn();
	cout << "selectSyn: " << selectSyn << "\n";

	// GETTING A MAP OF SYNONYMS AND THEIR TYPE
	// YOU CAN USE ITERATOR TO GO THROUGH THE MAP ELEMENTS ONE BY ONE
	unordered_map<string, Query::SType> myMap;
	myMap = myQuery.getSynTable();

	// RETRIEVING THE TYPE OF A SYNONYM
	Query::SType statementType = myMap["a"];
	
	// SOME TEST JUST FOR FUN
	if (statementType == Query::ASSIGN){
		cout << "Statement type of synonym a: ASSIGN\n";
	} else {
		cout << "Mismatch in retrieving statement type!";
	}
	
	// GETTING THE RELATIONSHIP VECTORS
	vector<Relationship> myVect = myQuery.getRelVect();

	for(int i = 0; i < myVect.size(); i++){

		// GETTING THE TYPE OF THE RELATIONSHIP AT VECTOR[I]
		Relationship::RelType relationshipType = myVect.at(i).getRelType();

		cout << "\n";

		if (relationshipType == Relationship::FOLLOWS) {
			cout << "Vector elem " << i << " relType: FOLLOWS\n";
		} else if (relationshipType == Relationship::FOLLOWSSTAR){
			cout << "Vector elem " << i << " relType: FOLLOWSSTAR\n";
		} else if (relationshipType == Relationship::PARENT){
			cout << "Vector elem " << i << " relType: PARENT\n";;
		} else if (relationshipType == Relationship::PARENTSTAR){
			cout << "Vector elem " << i << " relType: PARENTSTAR\n";
		} else {
			cout << "There's an error retrieving the relationship type\n";
		}

		// GETTING TOKEN1 AND TOKEN2 FROM RELATIONSHIP AT VECTOR[I]
		string token1 = myVect.at(i).getToken1();
		string token2 = myVect.at(i).getToken2();
		
		cout << "Vector elem " << i << " token1: " << token1 << "\n";
		cout << "Vector elem " << i << " token2: " << token2 << "\n";
	}

	return 0;
}