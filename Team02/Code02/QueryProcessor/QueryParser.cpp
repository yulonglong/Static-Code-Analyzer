#include "QueryParser.h"
#include <regex>
#include <sstream>
using namespace std;

QueryParser::QueryParser(){
	varName = "([A-Za-z][A-Za-z0-9#_]*)";
	select = "([Ss]elect)";
	suchThat = "(such)\\s+(that)";
	freeString = "(.+)";
	designEntity = "(procedure|stmtLst|stmt|assign|call|while|if|variable|constant|prog_line|plus|minus|times)";
	relRef = "([Ff]ollows|[Ff]ollows\\*|[Mm]odifies|[Mm]odifies\\*|[Uu]ses|[Uu]ses\\*|[Pp]arent|[Pp]arent\\*|[Cc]alls|[Cc]alls\\*|[Nn]ext|[Nn]ext\\*|[Aa]ffects|[Aa]ffects\\*)";
	pattern = "(pattern)";

	selectStatement.clear();
	synMap.clear();
}

bool QueryParser::parseDesignEntity(string query){
	tr1::cmatch res;
	tr1::regex rx("\\s*" + designEntity + "\\s+(\\s*" + varName + "\\s*,)*(\\s*" + varName + "\\s*)");
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
		tr1::regex subrx("\\s*" + varName + "\\s*");
		tr1::regex_match(subQuery.c_str(), subRes, subrx);
		string variableName = subRes[1];
		synMap.insert(make_pair(variableName, newType));
	}


	return true;
}

bool QueryParser::parseSelectOnly(string query){
	tr1::cmatch res;
	tr1::regex rx("\\s*" + select + "\\s+" + varName + "\\s*");
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

	tr1::regex rx("\\s*" + select + "\\s+" + varName + "\\s+" + pattern + "\\s+" + varName + "\\s*\\(\\s*" + freeString + "\\s*,\\s*" + freeString + "\\s*\\)\\s*");
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
	tr1::regex rx("\\s*" + select + "\\s+" + varName + "\\s+" + suchThat + "\\s+" + relRef + "\\s*\\(\\s*" + freeString + "\\s*,\\s*" + freeString + "\\s*\\)\\s*");
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
	tr1::regex rx("\\s*" + select + "\\s+" + varName + "\\s+" + suchThat + "\\s+" + relRef + "\\s*\\(\\s*" + freeString + "\\s*,\\s*" + freeString + "\\s*\\)" + "\\s+" + pattern + "\\s+" + varName + "\\s*\\(\\s*" + freeString + "\\s*,\\s*" + freeString + "\\s*\\)\\s*");
    tr1::regex_match(query.c_str(), res, rx);
	if(res.size()==0){
		return false;
	}
    for(int i=1;i<(int)res.size();i++){
		selectStatement.push_back(res[i]);
	}
	return true;
}

Query QueryParser::parse(string queryStr, bool &valid){
	synMap.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));

	istringstream istream(queryStr);

	string querySubStr;
	while(getline(istream,querySubStr,';')){
		bool validDesignEntity = parseDesignEntity(querySubStr);
		bool validSelectOnly = parseSelectOnly(querySubStr);
		bool validPattern = parsePattern(querySubStr);
		bool validRelational = parseRelational(querySubStr);
		bool validRelationalWithPattern = parseRelationalWithPattern(querySubStr);
		if((validDesignEntity|validSelectOnly|validPattern|validRelational|validRelationalWithPattern)==false){
			valid = false;
			Query queryDummy;
			return queryDummy;
		}
	}
	valid = true;
	Query query = makeQuery(selectStatement, synMap);
	return query;
}

Query QueryParser::makeQuery(vector<string> v, unordered_map<string, TypeTable::SynType> map){
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