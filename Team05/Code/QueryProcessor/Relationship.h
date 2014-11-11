#pragma once
#ifndef RELATIONSHIP_H
#define RELATIONSHIP_H

#include "PKB.h"
#include <string>
#include <iostream>
#include <string>

using namespace std;

/*! \brief A Relationship class which contains structured clauses
 *  
 *
 * A Relationship object contains the necessary information with regard to a clause
 * There are three types of clauses:
 * - Such-that clause
 * - Pattern clause
 * - With clause
 *
 * An example of the clause will be \"such that Next(x,1)\"
 * - The clause type, NEXT, will be set as the relationship type
 * - x will be stored in token1
 * - SYNONYM will be stored in token1Type
 * - 1 will be stored in token2
 * - INTEGER will be stored in token2Type
 * 
 * 
 * Relationship class contains the following relevant data:
 * \code
 * string relName;
 * RelType relType;
 * string patternSyn; //for pattern
 * TypeTable::SynType callSynType;
 * string token1;
 * string token2;
 * TokenType token1Type;
 * TokenType token2Type;
 * \endcode
 *
 *
 * \see Query, QueryParser, QueryEvaluator, Relationship
 */

class Relationship
{	
	public:
		enum RelType{FOLLOWS, FOLLOWSSTAR, PARENT, PARENTSTAR, MODIFIES, USES, CALLS, CALLSSTAR, NEXT, NEXTSTAR, AFFECTS, AFFECTSSTAR, WITH, PATTERN, SIBLING, INVALIDREL};
		static RelType getRelType(string);
		enum TokenType{ SYNONYM, IDENTIFIER, INTEGER, UNDERSCORE, UNDERSCOREEXPR, EXPR, INVALIDTOKEN};
		static TokenType getTokenType(string);

    private:
		string relName;
		RelType relType;
		string patternSyn; //for pattern
		TypeTable::SynType callSynType;
        string token1;
        string token2;
		TokenType token1Type;
		TokenType token2Type;

    public:
		//! blank relationship
		Relationship();
		//! constructor for clause, token1, token2
        Relationship(string, string, string);
		//! constructor for clause, patternSyn, token1, token2
		Relationship(string, string, string, string);
		//! constructor for clause, token1, token1type, token2, token2type
		Relationship(string, string, TokenType, string, TokenType);
		//! constructor for with-clause, token1, token1type, token2, token2type, callSynTypeProc
		Relationship(string, string, TokenType, string, TokenType, bool);
		//! constructor for clause, patternSyn, token1, token1type, token2, token2type
		Relationship(string, string, string, TokenType, string ,TokenType);
        
		//getter
		string getRelName();
		RelType getRelType();
		string getPatternSyn();
        string getToken1();
        string getToken2();
		TokenType getToken1Type();
		TokenType getToken2Type();
		TypeTable::SynType getCallSynType();
		
		//setter
		void setRelName(string);
		void setRelType(RelType);
		void setToken1(string);
		void setToken2(string);
		void setToken1Type(TokenType);
		void setToken2Type(TokenType);
		void setPatternSyn(string);
		void setCallSynType(TypeTable::SynType);

};

#endif // RELATIONSHIP_H_INCLUDED