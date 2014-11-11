#pragma once
#ifndef QUERY_H
#define QUERY_H

#include "Relationship.h"
#include <string>
#include "TypeTable.h"
#include <vector>
#include <unordered_map>

using namespace std;

/*! \brief A Query class which contains structured queries
 *  
 *
 * A Query object will be created by QueryParser after validation and parsing the user query.
 * It will then be forwarded to QueryEvaluator for evaluation and to answer they query.
 * 
 *
 * 
 * Query class contains the following relevant data:
 * \code
 * vector<string> selectedSyn; 
 * vector<bool> selectedSynIsCallProcedure;
 * string patternSyn;
 * vector<Relationship> relVect;
 * unordered_map<string, TypeTable::SynType> synTable;
 * \endcode
 *
 * It contains the declared synonyms, selected synonyms, Relationship vector, etc.
 * It has public functions to retrieve the data mentioned above.
 *
 * \see QueryParser, QueryEvaluator, Relationship
 */

class Query
{
    public:
        Query();
		//! get selected synonyms
		vector<string> getSelectedSyn();
		//! Set selected synonyms
		void setSelectedSyn(vector<string>);
		//! get special call synonym
		vector<bool> getSelectedSynIsCallProcedure();
		//! set special call synonym
		void setSelectedSynIsCallProcedure(vector<bool>);
		//! get pattern synonym
		string getPatternSyn();
		//! set pattern synonym
		void setPatternSyn(string);
		//! get a list of Relationship objects
        vector<Relationship> getRelVect();
		//! get synonym table
		unordered_map<string, TypeTable::SynType> getSynTable();
		//! set synonym table
		void setSynTable(unordered_map<string, TypeTable::SynType>);
		//! add a Relationship object into the list
		void addRelationship(Relationship);

	private:
		vector<string> selectedSyn; 
		vector<bool> selectedSynIsCallProcedure;
		string patternSyn;
        vector<Relationship> relVect;
		unordered_map<string, TypeTable::SynType> synTable;
};

#endif // QUERY_H_INCLUDED
