//@author Steven Kester Yuwono
//QueryParser.cpp

#include "QueryParser.h"
#include <regex>
#include <sstream>
using namespace std;

//constant string
const string QueryParser::MODIFIES = "modifies";
const string QueryParser::USES = "uses";
const string QueryParser::CALLS = "calls";
const string QueryParser::CALLSSTAR = "calls*";
const string QueryParser::PARENT = "parent";
const string QueryParser::PARENTSTAR = "parent*";
const string QueryParser::FOLLOWS = "follows";
const string QueryParser::FOLLOWSSTAR = "follows*";
const string QueryParser::NEXT = "next";
const string QueryParser::NEXTSTAR = "next*";
const string QueryParser::AFFECTS = "affects";
const string QueryParser::AFFECTSSTAR = "affects*";

//constant string for regex pattern
const string QueryParser::DIGIT = "[0-9]";
const string QueryParser::LETTER = "[A-Za-z]";
const string QueryParser::INTEGER = "[0-9]+";
const string QueryParser::IDENT = "[A-Za-z][A-Za-z0-9#]*";

const string QueryParser::synonym = IDENT;

const string QueryParser::select = "[Ss]elect";
const string QueryParser::such = "such";
const string QueryParser::that = "that";
const string QueryParser::freeString = "\\S+";
const string QueryParser::designEntity = "procedure|stmtLst|stmt|assign|call|while|if|variable|constant|prog_line";
const string QueryParser::relRef = "[Ff]ollows|[Ff]ollows\\*|[Mm]odifies|[Mm]odifies\\*|[Uu]ses|[Uu]ses\\*|[Pp]arent|[Pp]arent\\*|[Cc]alls|[Cc]alls\\*|[Nn]ext|[Nn]ext\\*|[Aa]ffects|[Aa]ffects\\*";
const string QueryParser::pattern = "pattern";

string stringToLower(string word){
	for(int i=0;i<(int)word.length();i++){
		word[i] = tolower(word[i]);
	}
	return word;
}

QueryParser::QueryParser(){
	selectStatement.clear();
	synMap.clear();
}

bool QueryParser::parseDesignEntity(string query){
	tr1::cmatch res;
	tr1::regex rx("\\s*(" + designEntity + ")\\s+(\\s*(" + IDENT + ")\\s*,)*(\\s*(" + IDENT + ")\\s*)");
    tr1::regex_match(query.c_str(), res, rx);
	
	if(res.size()==0){
		return false;
	}
	string specificDesignEnt = res[1];
	TypeTable::SynType newType = TypeTable::getSynType(specificDesignEnt);
    
	istringstream istream(query);
	string subQuery;
	while(subQuery!=specificDesignEnt){
		getline(istream,subQuery,' ');
	}
	while(getline(istream,subQuery,',')){
		tr1::cmatch subRes;
		tr1::regex subrx("\\s*(" + IDENT + ")\\s*");
		tr1::regex_match(subQuery.c_str(), subRes, subrx);
		string variableName = subRes[1];
		synMap.insert(make_pair(variableName, newType));
	}


	return true;
}

bool QueryParser::parseSelectOnly(string query){
	tr1::cmatch res;
	tr1::regex rx("\\s*(" + select + ")\\s+(" + IDENT + ")\\s*");
    tr1::regex_match(query.c_str(), res, rx);
	if(res.size()==0){
		return false;
	}
    for(int i=1;i<(int)res.size();i++){
		selectStatement.push_back(res[i]);
	}
	return true;

}

bool QueryParser::parsePattern(string query){
	tr1::cmatch res;

	tr1::regex rx("\\s*(" + select + ")\\s+(" + IDENT + ")\\s+(" + pattern + ")\\s+(" + IDENT + ")\\s*\\(\\s*(" + freeString + ")\\s*,\\s*(" + freeString + ")\\s*\\)\\s*");
    tr1::regex_match(query.c_str(), res, rx);

	if(res.size()==0){
		return false;
	}
    for(int i=1;i<(int)res.size();i++){
		selectStatement.push_back(res[i]);
	}
	return true;
}
bool QueryParser::parseRelational(string query){
	tr1::cmatch res;
	tr1::regex rx("\\s*(" + select + ")\\s+(" + IDENT + ")\\s+(" + such + ")\\s+(" + that + ")\\s+(" + relRef + ")\\s*\\(\\s*(" + freeString + ")\\s*,\\s*(" + freeString + ")\\s*\\)\\s*");
    tr1::regex_match(query.c_str(), res, rx);
	if(res.size()==0){
		return false;
	}
    for(int i=1;i<(int)res.size();i++){
		selectStatement.push_back(res[i]);
	}
	return true;

}

bool QueryParser::parseRelationalWithPattern(string query){
	tr1::cmatch res;
	tr1::regex rx("\\s*(" + select + ")\\s+(" + IDENT + ")\\s+(" + such + ")\\s+(" + that + ")\\s+(" + relRef + ")\\s*\\(\\s*(" + freeString + ")\\s*,\\s*(" + freeString + ")\\s*\\)" + "\\s+(" + pattern + ")\\s+(" + IDENT + ")\\s*\\(\\s*(" + freeString + ")\\s*,\\s*(" + freeString + ")\\s*\\)\\s*");
    tr1::regex_match(query.c_str(), res, rx);
	if(res.size()==0){
		return false;
	}
    for(int i=1;i<(int)res.size();i++){
		selectStatement.push_back(res[i]);
	}
	return true;
}

Query QueryParser::queryParse(string queryStr, bool &valid){
	synMap.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));

	istringstream istream(queryStr);

	string querySubStr;
	while(getline(istream,querySubStr,';')){
		bool validDesignEntity = parseDesignEntity(querySubStr);
		if(validDesignEntity){
			continue;
		}
		bool validRelationalWithPattern = parseRelationalWithPattern(querySubStr);
		if(validRelationalWithPattern){
			continue;
		}
		bool validRelational = parseRelational(querySubStr);
		if(validRelational){
			continue;
		}
		bool validPattern = parsePattern(querySubStr);
		if(validPattern){
			continue;
		}
		bool validSelectOnly = parseSelectOnly(querySubStr);
		if(validSelectOnly){
			continue;
		}
		if((validDesignEntity|validSelectOnly|validPattern|validRelational|validRelationalWithPattern)==false){
			valid = false;
			Query queryDummy;
			return queryDummy;
		}
	}
	valid = true;
	Query query = constructAndValidateQuery(selectStatement, synMap, valid);
	return query;
}

Query QueryParser::constructAndValidateQuery(vector<string> v, unordered_map<string, TypeTable::SynType> map, bool &valid){
	Query query;
	query.setSelectedSyn(v.at(1));
	query.setSynTable(map);

	for (size_t i = 2; i < v.size(); i++){
		if (v.at(i) == "Modifies" || v.at(i) == "Uses" || v.at(i) == "Follows" ||
			v.at(i) == "Follows*" || v.at(i) == "Parent" || v.at(i) == "Parent*"){
			Relationship rel(v.at(i), v.at(i+1), v.at(i+2));
			query.addRelationship(rel);
			i = i+2;
		} else if (v.at(i) == "pattern"){
			query.setPatternSyn(v.at(i+1));
			Relationship rel(v.at(i), v.at(i+2), v.at(i+3));
			query.addRelationship(rel);
			i = i+3;
		}
	}
	return query;
}