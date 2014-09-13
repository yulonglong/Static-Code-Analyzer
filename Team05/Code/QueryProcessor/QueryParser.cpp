//@author Steven Kester Yuwono
//QueryParser.cpp

#include "QueryParser.h"
#include <regex>
#include <sstream>
using namespace std;

//GRAMMAR RULES DECLARATION BEGIN

//constant string
const string QueryParser::BOOLEAN = "BOOLEAN";
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
const string QueryParser::PATTERN = "pattern";
const string QueryParser::WITH = "with";

//constant string for regex pattern
const string QueryParser::DIGIT = "[0-9]";
const string QueryParser::LETTER = "[A-Za-z]";
const string QueryParser::INTEGER = "[0-9]+";
const string QueryParser::IDENT = "[A-Za-z][A-Za-z0-9#]*";

const string QueryParser::synonym = IDENT;
const string QueryParser::attrName = "(?:procName|varName|value|stmt#)";
const string QueryParser::entRef = synonym + "|_|\"" + IDENT +"\"|" + INTEGER;
const string QueryParser::varRef = synonym + "|_|\"" + IDENT +"\"";
const string QueryParser::stmtRef = synonym + "|_|" + INTEGER;
const string QueryParser::lineRef = synonym + "|_|" + INTEGER;
const string QueryParser::designEntity = "procedure|stmtLst|stmt|assign|call|while|if|variable|constant|prog_line";
const string QueryParser::attrRef = "(?:" + synonym + "." + attrName + ")";
const string QueryParser::elem = synonym + "|" + attrRef;
const string QueryParser::tuple = elem;
const string QueryParser::resultCl = tuple + "|" + BOOLEAN;

const string QueryParser::ref = "(?:" + attrRef + "|" + synonym + "|" + "\""+IDENT+"\"" + "|" + INTEGER + ")";
const string QueryParser::attrCompare = "(?:" + ref + "\\s*=\\s*" + ref + ")";
const string QueryParser::attrCond = attrCompare;
//+ "\\s+(?:" +"and\\s+" + attrCompare + "\\s*)*";
const string QueryParser::withCl = "(?:[Ww]ith\\s+(?:" + attrCond + ")"+"\\s*)";

const string QueryParser::select = "[Ss]elect";
const string QueryParser::such = "such";
const string QueryParser::that = "that";
const string QueryParser::freeString = "\\S+";
const string QueryParser::expr = "[^_]+";

const string QueryParser::ModifiesP = "(?:(?:[Mm]odifies)\\s*\\(\\s*(?:"+entRef+")"+ "\\s*,\\s*" +"(?:"+varRef+")" + "\\s*\\))";
const string QueryParser::ModifiesS = "(?:(?:[Mm]odifies)\\s*\\(\\s*(?:"+stmtRef+")"+ "\\s*,\\s*" +"(?:"+varRef+")" + "\\s*\\))";
const string QueryParser::UsesP = "(?:(?:[Uu]ses)\\s*\\(\\s*(?:"+entRef+")"+ "\\s*,\\s*" +"(?:"+varRef+")" + "\\s*\\))";
const string QueryParser::UsesS = "(?:(?:[Uu]ses)\\s*\\(\\s*(?:"+stmtRef+")"+ "\\s*,\\s*" +"(?:"+varRef+")" + "\\s*\\))";
const string QueryParser::Calls = "(?:(?:[Cc]alls)\\s*\\(\\s*(?:"+entRef+")"+ "\\s*,\\s*" +"(?:"+entRef+")" + "\\s*\\))";
const string QueryParser::CallsT = "(?:(?:[Cc]alls\\*)\\s*\\(\\s*(?:"+entRef+")"+ "\\s*,\\s*" +"(?:"+entRef+")" + "\\s*\\))";
const string QueryParser::Parent = "(?:(?:[Pp]arent)\\s*\\(\\s*(?:"+stmtRef+")"+ "\\s*,\\s*" +"(?:"+stmtRef+")" + "\\s*\\))";
const string QueryParser::ParentT = "(?:(?:[Pp]arent\\*)\\s*\\(\\s*(?:"+stmtRef+")"+ "\\s*,\\s*" +"(?:"+stmtRef+")" + "\\s*\\))";
const string QueryParser::Follows = "(?:(?:[Ff]ollows)\\s*\\(\\s*(?:"+stmtRef+")"+ "\\s*,\\s*" +"(?:"+stmtRef+")" + "\\s*\\))";
const string QueryParser::FollowsT = "(?:(?:[Ff]ollows\\*)\\s*\\(\\s*(?:"+stmtRef+")"+ "\\s*,\\s*" +"(?:"+stmtRef+")" + "\\s*\\))";
const string QueryParser::Next = "(?:(?:[Nn]ext)\\s*\\(\\s*(?:"+lineRef+")"+ "\\s*,\\s*" +"(?:"+lineRef+")" + "\\s*\\))";
const string QueryParser::NextT = "(?:(?:[Nn]ext\\*)\\s*\\(\\s*(?:"+lineRef+")"+ "\\s*,\\s*" +"(?:"+lineRef+")" + "\\s*\\))";
const string QueryParser::Affects = "(?:(?:[Aa]ffects)\\s*\\(\\s*(?:"+stmtRef+")"+ "\\s*,\\s*" +"(?:"+stmtRef+")" + "\\s*\\))";
const string QueryParser::AffectsT = "(?:(?:[Aa]ffects\\*)\\s*\\(\\s*(?:"+stmtRef+")"+ "\\s*,\\s*" +"(?:"+stmtRef+")" + "\\s*\\))";
const string QueryParser::TESTSTR = "\\s*\\(\\s*("+freeString+")"+ "\\s*,\\s*" +"("+freeString+")" + "\\s*\\)";

const string QueryParser::relRef = "(?:" + ModifiesP + "|" + ModifiesS + "|" + UsesP + "|" + UsesS + "|" + Calls + "|" + CallsT
+ "|" + Parent + "|" + ParentT + "|" + Follows + "|" + FollowsT + "|" + Next + "|" + NextT + "|" + Affects + "|" + AffectsT + ")";
//const string QueryParser::relRef = "(?:" + ModifiesP + "|" + ModifiesS + "|" + UsesP + "|" + UsesS + "|" +  Follows +")";
const string QueryParser::allClause = "([Mm]odifies|[Uu]ses|[Ff]ollows|[Ff]ollows\\*|[Pp]arent|[Pp]arent\\*|[Cc]alls|[Cc]alls\\*|[Nn]ext|[Nn]ext\\*|[Aa]ffects|[Aa]ffects\\*)";

const string QueryParser::relCond = relRef;
const string QueryParser::suchThatCl = "(such)\\s+(that)\\s+" + relCond +"\\s*";
//const string QueryParser::suchThatCl = "(such)\\s+(that)";

const string QueryParser::expressionSpec = "\"" + expr + "\"" + "|" + "_\"" + expr + "\"_" + "|" + "_";
const string QueryParser::assignCl = "(?:("+synonym +")" + "\\s*\\(\\s*" + "("+varRef+")" + "\\s*,\\s*" + "("+expressionSpec+")" + "\\s*\\))";
const string QueryParser::ifCl = "(?:("+synonym+")" + "\\s*\\(\\s*" + "("+varRef+")" + ",\\s*" + "("+"_"+")" + "\\s*,\\s*" + "("+"_"+")" + "\\s*\\))";
const string QueryParser::whileCl = "(?:("+synonym+")" + "\\s*\\(\\s*" + "("+varRef+")" + ",\\s*" + "("+"_"+")" + "\\s*\\))";
const string QueryParser::pattern = "(?:" + assignCl + "|" + whileCl + "|" + ifCl + ")";
const string QueryParser::patternCond = pattern;
const string QueryParser::patternCl = "(?:(?:[Pp]attern)\\s+" + patternCond + "\\s*)";

//select clause
const string QueryParser::selectCl = "([Ss]elect)\\s+("+resultCl+")"+"\\s+"+"(?:"+suchThatCl+"|"+patternCl+"|"+withCl+")*";

//clauses parameter
const string QueryParser::modifiesParam[] = {entRef + "|" + stmtRef , varRef};
const string QueryParser::usesParam[] = {entRef + "|" + stmtRef , varRef};
const string QueryParser::callsParam[] = {entRef , entRef};
const string QueryParser::callsStarParam[] = {entRef , entRef};
const string QueryParser::parentParam[] = {stmtRef , stmtRef};
const string QueryParser::parentStarParam[] = {stmtRef , stmtRef};
const string QueryParser::followsParam[] = {stmtRef , stmtRef};
const string QueryParser::followsStarParam[] = {stmtRef , stmtRef};
const string QueryParser::nextParam[] = {lineRef , lineRef};
const string QueryParser::nextStarParam[] = {lineRef , lineRef};
const string QueryParser::affectsParam[] = {stmtRef , stmtRef};
const string QueryParser::affectsStarParam[] = {stmtRef , stmtRef};

//GRAMMAR RULES DECLARATION END



QueryParser::QueryParser(){
	selectStatement.clear();
	synMap.clear();
}

string QueryParser::stringToLower(string word){
	for(int i=0;i<(int)word.length();i++){
		word[i] = tolower(word[i]);
	}
	return word;
}

string QueryParser::getNextToken(istringstream &istream){
	string subQuery;
	while(getline(istream,subQuery,' ')){
		if(subQuery.length()>0){
			break;
		}
	}
	return subQuery;
}

bool QueryParser::regexMatch(string regexPattern, string word){
	tr1::cmatch subres;
	tr1::regex subrx(regexPattern);
	tr1::regex_match(word.c_str(), subres, subrx);
	if(subres.size()==0){
		return false;
	}
	return true;
}

bool QueryParser::regexMatchWithResult(string regexPattern, string word, vector<string> &result){
	tr1::cmatch subres;
	tr1::regex subrx(regexPattern);
	tr1::regex_match(word.c_str(), subres, subrx);
	if(subres.size()==0){
		return false;
	}
	else{
		for(unsigned int i=0;i<subres.size();i++){
			result.push_back(subres[i]);
		}
		return true;
	}
}

//Query Parsing to ensure it follow sthe proper format

bool QueryParser::parseDesignEntity(string query){
	vector<string> res;
	string regexPattern = "\\s*(" + designEntity + ")\\s+(\\s*(" + IDENT + ")\\s*,)*(\\s*(" + IDENT + ")\\s*)";
	//cout << endl << regexPattern << endl << endl;
	bool match = regexMatchWithResult(regexPattern,query,res);
	
	if(!match){
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
		vector<string> subRes;
		regexPattern = "\\s*(" + IDENT + ")\\s*";
		match = regexMatchWithResult(regexPattern,subQuery,subRes);
		string variableName = subRes[1];
		synMap.insert(make_pair(variableName, newType));
	}

	return true;
}

bool QueryParser::parseSelectCl(string query){
	vector<string> res;
	//string regexPattern = "\\s*(" + select + ")\\s+(" + IDENT + ")\\s+(" + such + ")\\s+(" + that + ")\\s+(" + relRef + ")\\s*\\(\\s*(" + freeString + ")\\s*,\\s*(" + freeString + ")\\s*\\)" + "\\s+(" + pattern + ")\\s+(" + IDENT + ")\\s*\\(\\s*(" + freeString + ")\\s*,\\s*(" + freeString + ")\\s*\\)\\s*";
	string regexPattern =  "\\s*" + selectCl + "\\s*";
	bool match = regexMatch(regexPattern,query);
	if(!match){
		return false;
	}
	
	istringstream istream(query);
	string token;

	token = getNextToken(istream);
	selectStatement.push_back(token);//Select
	token = getNextToken(istream);
	selectStatement.push_back(token);//result-Cl

	while(getline(istream,token,' ')){
		if (token.length()==0){
			continue;
		}
		if (token == such){
			selectStatement.push_back(token);//push such
			token = getNextToken(istream);//read that
			selectStatement.push_back(that);

			string generalToken[3];
			getline(istream,generalToken[0],'(');
			getline(istream,generalToken[1],',');
			getline(istream,generalToken[2],')');

			vector<string> subRes;
			regexPattern = "\\s*(" + allClause + ")\\s*";
			match = regexMatchWithResult(regexPattern,generalToken[0],subRes);
			string clauseName = subRes[1];
			selectStatement.push_back(clauseName);
			subRes.clear();

			for(int i=1;i<3;i++){
				regexPattern = "\\s*(" + freeString + ")\\s*";
				match = regexMatchWithResult(regexPattern,generalToken[i],subRes);
				string variableName = subRes[1];
				selectStatement.push_back(variableName);
				subRes.clear();
			}

		}
		else if(token == PATTERN){//read pattern
			selectStatement.push_back(token);//push pattern

			string patternToken[3];
			getline(istream,patternToken[0],'(');
			getline(istream,patternToken[1],',');
			getline(istream,patternToken[2],')');

			for(int i=0;i<3;i++){
				vector<string> subRes;
				regexPattern = "\\s*(" + freeString + ")\\s*";
				match = regexMatchWithResult(regexPattern,patternToken[i],subRes);
				string variableName = subRes[1];
				selectStatement.push_back(variableName);
			}
		}
		else if(token == WITH){//read with
			selectStatement.push_back(token);//push with

			string withToken[2];
			getline(istream,withToken[0],'=');
			withToken[1]=getNextToken(istream);

			for(int i=0;i<2;i++){
				vector<string> subRes;
				regexPattern = "\\s*(" + ref + ")\\s*";
				match = regexMatchWithResult(regexPattern,withToken[i],subRes);
				string variableName = subRes[1];
				selectStatement.push_back(variableName);
			}

		}
		else{ // general clause
		}
	}

	//for(int i=0;i<(int)selectStatement.size();i++){
	//	cout << selectStatement[i] << endl;
	//}


	return true;
}

Query QueryParser::queryParse(string queryStr, bool &valid){
	synMap.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
	//cout << "here" << endl;
	istringstream istream(queryStr);

	string querySubStr;
	while(getline(istream,querySubStr,';')){
		bool validDesignEntity = parseDesignEntity(querySubStr);
		if(validDesignEntity){
			continue;
		}
		bool validSelectCl = parseSelectCl(querySubStr);
		if(validSelectCl){
			continue;
		}
		if((validDesignEntity|validSelectCl)==false){
			valid = false;
			Query queryDummy;
			return queryDummy;
		}
	}
	
	valid = true;
	Query query = constructAndValidateQuery(selectStatement, synMap, valid);
	return query;
}


//QueryValidation and Create Query

void QueryParser::deepCopyTableParam(string tableParam[2], string relationRef){
	if(relationRef == MODIFIES){
		for(int index=0;index<2;index++){
			tableParam[index] = modifiesParam[index];
		}
	}
	else if(relationRef == USES){
		for(int index=0;index<2;index++){
			tableParam[index] = usesParam[index];
		}
	}
	else if(relationRef == CALLS){
		for(int index=0;index<2;index++){
			tableParam[index] = callsParam[index];
		}
	}
	else if(relationRef == CALLSSTAR){
		for(int index=0;index<2;index++){
			tableParam[index] = callsStarParam[index];
		}
	}
	else if(relationRef == PARENT){
		for(int index=0;index<2;index++){
			tableParam[index] = parentParam[index];
		}
	}
	else if(relationRef == PARENTSTAR){
		for(int index=0;index<2;index++){
			tableParam[index] = parentStarParam[index];
		}
	}
	else if(relationRef == FOLLOWS){
		for(int index=0;index<2;index++){
			tableParam[index] = followsParam[index];
		}
	}
	else if(relationRef == FOLLOWSSTAR){
		for(int index=0;index<2;index++){
			tableParam[index] = followsStarParam[index];
		}
	}
	else if(relationRef == NEXT){
		for(int index=0;index<2;index++){
			tableParam[index] = nextParam[index];
		}
	}
	else if(relationRef == NEXTSTAR){
		for(int index=0;index<2;index++){
			tableParam[index] = nextStarParam[index];
		}
	}
	else if(relationRef == AFFECTS){
		for(int index=0;index<2;index++){
			tableParam[index] = affectsParam[index];
		}
	}
	else if(relationRef == AFFECTSSTAR){
		for(int index=0;index<2;index++){
			tableParam[index] = affectsStarParam[index];
		}
	}
}

Query QueryParser::constructAndValidateQuery(vector<string> v, unordered_map<string, TypeTable::SynType> map, bool &valid){
	Query query;
	vector<string> selectedSyn;
	selectedSyn.push_back(v.at(1));
	query.setSelectedSyn(selectedSyn);
	query.setSynTable(map);

	for (size_t i = 2; i < v.size(); i++){
		string relationRef = v.at(i);
		bool formatValid = true;
		bool synValid = true;

		tr1::cmatch res;
		tr1::regex rx("(" + allClause + ")");
		tr1::regex_match(relationRef.c_str(), res, rx);
		
		//if match relRef
		if(res.size()>0){
			relationRef = stringToLower(relationRef);

			string tableParam[2];
			deepCopyTableParam(tableParam,relationRef);

			string param[2];
			param[0] = v.at(i+1);
			param[1] = v.at(i+2);

			for(int index=0;index<2;index++){
				bool match = regexMatch("("+tableParam[index]+")",param[index]);
				if(!match){
					formatValid = false;
				}				
			}
			
			if(formatValid){
				for(int index=0;index<2;index++){
					bool match = regexMatch("("+synonym+")",param[index]);
					//if it is a synonym
					if(match){
						unordered_map<string, TypeTable::SynType>::iterator it;
						it = synMap.find(param[index]);
						if(it==synMap.end()){
							synValid=false;
						}
					}				
				}
			}

			if((formatValid)&&(synValid)){
				Relationship rel(v.at(i), v.at(i+1), v.at(i+2));
				query.addRelationship(rel);
				i = i+2;
			}
			else{
				valid = false;
				Query queryDummy;
				return queryDummy;
			}
		}
		//if doesnt match relRef
		else if (relationRef == PATTERN){
			bool patternSynValid = true;
			string patternSyn = v.at(i+1);
			unordered_map<string, TypeTable::SynType>::iterator it;
			it = synMap.find(patternSyn);
			if(it==synMap.end()){
				patternSynValid = false;
			}
			
			bool varRefValid = true;
			string firstParam = v.at(i+2);
			bool match = regexMatch("("+synonym+")",firstParam);
			//if it is a synonym
			if(match){
				it = synMap.find(firstParam);
				if(it==synMap.end()){
					varRefValid = false;
				}
			}

			if((patternSynValid)&&(varRefValid)){
				//query.setPatternSyn(v.at(i+1));
				//Relationship rel(v.at(i), v.at(i+2), v.at(i+3));
				Relationship rel(v.at(i),v.at(i+1),v.at(i+2),v.at(i+3));
				query.addRelationship(rel);
				i = i+3;
			}
			else{
				valid = false;
				Query queryDummy;
				return queryDummy;
			}
		}
		else if (relationRef == WITH){
			unordered_map<string, TypeTable::SynType>::iterator it;

			string withSyn[2];

			string withToken[2];
			withToken[0] = v.at(i+1);
			withToken[1] = v.at(i+2);

			//check whether first token is a single synonym, must be of type prog_line
			bool withValid1 = true;
			string firstParam = v.at(i+1);
			bool match = regexMatch("("+synonym+")",firstParam);

			if(match){
				it = synMap.find(firstParam);
				if(it==synMap.end()){//if synonym not found
					withValid1 = false;
				}
				else if(it->second != TypeTable::PROGLINE){
					withValid1 = false;
				}
			}
			else{//if not synonym
				vector<string> result;
				match = regexMatchWithResult("("+synonym+").("+attrName+")",firstParam,result);
				if(match){
					it = synMap.find(result[1]);
					if(it==synMap.end()){//if synonym not found
						withValid1 = false;
					}
					else if ((it->second != TypeTable::PROCEDURE)&&(result[2] == "procName")){
						withValid1 = false;
					}
					else if ((it->second != TypeTable::STMT)&&(result[2] == "stmt#")){
						withValid1 = false;
					}
					else if ((it->second != TypeTable::CONSTANT)&&(result[2] == "value")){
						withValid1 = false;
					}
					else if((it->second != TypeTable::VARIABLE)&&(result[2] == "varName")){
						withValid1 = false;
					}
					else{
						withToken[0]= result[1];
					}
				}
			}

			//check whether first token is a single synonym, must be of type prog_line
			bool withValid2 = true;
			string secondParam = v.at(i+2);
			match = regexMatch("("+synonym+")",secondParam);

			if(match){
				it = synMap.find(secondParam);
				if(it==synMap.end()){//if synonym not found
					withValid2 = false;
				}
				else if(it->second != TypeTable::PROGLINE){
					withValid2 = false;
				}
			}
			else{//if not synonym
				vector<string> result;
				match = regexMatchWithResult("("+synonym+").("+attrName+")",secondParam,result);
				if(match){
					it = synMap.find(result[1]);

					if(it==synMap.end()){//if synonym not found
						withValid2 = false;
					}
					else if ((it->second != TypeTable::PROCEDURE)&&(result[2] == "procName")){
						withValid2 = false;
					}
					else if ((it->second != TypeTable::STMT)&&(result[2] == "stmt#")){
						withValid2 = false;
					}
					else if ((it->second != TypeTable::CONSTANT)&&(result[2] == "value")){
						withValid2 = false;
					}
					else if((it->second != TypeTable::VARIABLE)&&(result[2] == "varName")){
						withValid2 = false;
					}
					else{
						withToken[1]= result[1];
					}
				}
			}

			if((withValid1)&&(withValid2)){
				Relationship rel(v.at(i), withToken[0], withToken[1]);
				query.addRelationship(rel);
				i = i+2;
			}
			else{
				valid = false;
				Query queryDummy;
				return queryDummy;
			}
		}

	}
	return query;
}