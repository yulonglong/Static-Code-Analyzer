//@author Steven Kester Yuwono
//QueryParser.cpp

#include "QueryParser.h"
#include <regex>
#include <sstream>
using namespace std;

//GRAMMAR RULES DECLARATION BEGIN

//constant string
const string QueryParser::AND = "and";
const string QueryParser::SUCHTHAT = "such that";

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
const string QueryParser::OPERATOR = "(?:\\+|\\-|\\*)";
const string QueryParser::LETTERORINTEGER = "(?:[A-Za-z]+|[0-9]+)";

const string QueryParser::synonym = "(?:" + IDENT + ")";
const string QueryParser::attrName = "(?:procName|varName|value|stmt#)";
const string QueryParser::entRef = synonym + "|_|\"" + IDENT +"\"|" + INTEGER;
const string QueryParser::varRef = synonym + "|_|\"" + IDENT +"\"";
const string QueryParser::stmtRef = synonym + "|_|" + INTEGER;
const string QueryParser::lineRef = synonym + "|_|" + INTEGER;
const string QueryParser::designEntity = "procedure|stmtLst|stmt|assign|call|while|if|variable|constant|prog_line";
const string QueryParser::attrRef = "(?:" + synonym + "\\." + attrName + ")";
const string QueryParser::elem = "(?:" + attrRef + "|" + synonym + ")";
const string QueryParser::tuple = "(?:" + elem + ")" + "|" + "(?:" + "\\<" + "\\s*" + elem + "(?:" + "\\s*\\,\\s*" +  elem  + ")*" + "\\s*" + "\\>" + ")";
const string QueryParser::resultCl = "(?:" + tuple + "|" + BOOLEAN + ")";

const string QueryParser::ref = "(?:" + attrRef + "|" + synonym + "|" + "\""+IDENT+"\"" + "|" + INTEGER + ")";
const string QueryParser::attrCompare = "(?:" + ref + "\\s*=\\s*" + ref + ")";
const string QueryParser::attrCond = attrCompare + "(?:" + "\\s+" + "and" + "\\s+" + attrCompare + ")*";
//+ "\\s+(?:" +"and\\s+" + attrCompare + "\\s*)*";
const string QueryParser::withCl = "(?:[Ww]ith\\s+(?:" + attrCond + ")"+")";

const string QueryParser::select = "[Ss]elect";
const string QueryParser::such = "such";
const string QueryParser::that = "that";
const string QueryParser::freeString = "\\S+";
const string QueryParser::freeStringWithSpace = "[.]+";

const string QueryParser::expr = "\\s*" + LETTERORINTEGER +"(?:"+"\\s*" + OPERATOR + "\\s*" + LETTERORINTEGER + ")*" + "\\s*";


const string QueryParser::ModifiesP = "(?:(?:[Mm]odifies)\\s*\\(\\s*(?:"+entRef+")"+ "\\s*\\,\\s*" +"(?:"+varRef+")" + "\\s*\\))";
const string QueryParser::ModifiesS = "(?:(?:[Mm]odifies)\\s*\\(\\s*(?:"+stmtRef+")"+ "\\s*\\,\\s*" +"(?:"+varRef+")" + "\\s*\\))";
const string QueryParser::UsesP = "(?:(?:[Uu]ses)\\s*\\(\\s*(?:"+entRef+")"+ "\\s*\\,\\s*" +"(?:"+varRef+")" + "\\s*\\))";
const string QueryParser::UsesS = "(?:(?:[Uu]ses)\\s*\\(\\s*(?:"+stmtRef+")"+ "\\s*\\,\\s*" +"(?:"+varRef+")" + "\\s*\\))";
const string QueryParser::Calls = "(?:(?:[Cc]alls)\\s*\\(\\s*(?:"+entRef+")"+ "\\s*\\,\\s*" +"(?:"+entRef+")" + "\\s*\\))";
const string QueryParser::CallsT = "(?:(?:[Cc]alls\\*)\\s*\\(\\s*(?:"+entRef+")"+ "\\s*\\,\\s*" +"(?:"+entRef+")" + "\\s*\\))";
const string QueryParser::Parent = "(?:(?:[Pp]arent)\\s*\\(\\s*(?:"+stmtRef+")"+ "\\s*\\,\\s*" +"(?:"+stmtRef+")" + "\\s*\\))";
const string QueryParser::ParentT = "(?:(?:[Pp]arent\\*)\\s*\\(\\s*(?:"+stmtRef+")"+ "\\s*\\,\\s*" +"(?:"+stmtRef+")" + "\\s*\\))";
const string QueryParser::Follows = "(?:(?:[Ff]ollows)\\s*\\(\\s*(?:"+stmtRef+")"+ "\\s*\\,\\s*" +"(?:"+stmtRef+")" + "\\s*\\))";
const string QueryParser::FollowsT = "(?:(?:[Ff]ollows\\*)\\s*\\(\\s*(?:"+stmtRef+")"+ "\\s*\\,\\s*" +"(?:"+stmtRef+")" + "\\s*\\))";
const string QueryParser::Next = "(?:(?:[Nn]ext)\\s*\\(\\s*(?:"+lineRef+")"+ "\\s*\\,\\s*" +"(?:"+lineRef+")" + "\\s*\\))";
const string QueryParser::NextT = "(?:(?:[Nn]ext\\*)\\s*\\(\\s*(?:"+lineRef+")"+ "\\s*\\,\\s*" +"(?:"+lineRef+")" + "\\s*\\))";
const string QueryParser::Affects = "(?:(?:[Aa]ffects)\\s*\\(\\s*(?:"+stmtRef+")"+ "\\s*\\,\\s*" +"(?:"+stmtRef+")" + "\\s*\\))";
const string QueryParser::AffectsT = "(?:(?:[Aa]ffects\\*)\\s*\\(\\s*(?:"+stmtRef+")"+ "\\s*\\,\\s*" +"(?:"+stmtRef+")" + "\\s*\\))";
const string QueryParser::TESTSTR = "\\s*\\(\\s*("+freeString+")"+ "\\s*\\,\\s*" +"("+freeString+")" + "\\s*\\)";

const string QueryParser::relRef = "(?:" + ModifiesP + "|" + ModifiesS + "|" + UsesP + "|" + UsesS + "|" + Calls + "|" + CallsT
+ "|" + Parent + "|" + ParentT + "|" + Follows + "|" + FollowsT + "|" + Next + "|" + NextT + "|" + Affects + "|" + AffectsT + ")";
//const string QueryParser::relRef = "(?:" + ModifiesP + "|" + ModifiesS + "|" + UsesP + "|" + UsesS + "|" +  Follows +")";
const string QueryParser::allClause = "([Mm]odifies|[Uu]ses|[Ff]ollows|[Ff]ollows\\*|[Pp]arent|[Pp]arent\\*|[Cc]alls|[Cc]alls\\*|[Nn]ext|[Nn]ext\\*|[Aa]ffects|[Aa]ffects\\*)";

const string QueryParser::relCond = relRef + "(?:" + "\\s+" + "and" + "\\s+" + relRef + ")*";
const string QueryParser::suchThatCl = "(such)\\s+(that)\\s+" + relCond;
//const string QueryParser::suchThatCl = "(such)\\s+(that)";

const string QueryParser::expressionSpec = "(?:\"" + expr + "\")" + "|" + "(?:_\"" + expr + "\"_)" + "|" + "(?:_)";
const string QueryParser::assignCl = "(?:("+synonym +")" + "\\s*\\(\\s*" + "("+varRef+")" + "\\s*\\,\\s*" + "("+expressionSpec+")" + "\\s*\\))";
const string QueryParser::ifCl = "(?:("+synonym+")" + "\\s*\\(\\s*" + "("+varRef+")" + "\\,\\s*" + "("+"_"+")" + "\\s*\\,\\s*" + "("+"_"+")" + "\\s*\\))";
const string QueryParser::whileCl = "(?:("+synonym+")" + "\\s*\\(\\s*" + "("+varRef+")" + "\\,\\s*" + "("+"_"+")" + "\\s*\\))";
const string QueryParser::pattern = "(?:" + ifCl + "|" + assignCl + "|" + whileCl + ")";
const string QueryParser::patternCond = pattern + "(?:" + "\\s+" + "and" + "\\s+" + pattern + ")*";
const string QueryParser::patternCl = "(?:(?:[Pp]attern)\\s+" + patternCond + ")";

//select clause
const string QueryParser::selectCl = "([Ss]elect)\\s+(?:"+resultCl+")"+"(?:\\s+(?:"+suchThatCl+"|"+patternCl+"|"+withCl+"))*";

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
	string prevToken;

	token = getNextToken(istream);
	//selectStatement.push_back(token); //Select

	//BEGIN SELECT STATEMENT PARSING
	token = getNextToken(istream);
	//case 1: no tuple
	if(token[0] != '<'){
		selectedSyn.push_back(token);//result-Cl
	}
	//case 2: tuple
	else {
		//case 2.1: token includes complete tuple, e.g. <p,q,r>
		if (token[token.length()-1] == '>'){
			token = token.substr(0,token.length()-1);
		}
		//case 2.2: token does not include complete tuple
		else{
			string secondToken;
			getline(istream,secondToken,'>');
			token = token + secondToken;
		}
		token = token.substr(1); // remove the '<' as the first character
		//separate the selected synonyms
		//and push to the vector
		istringstream selectedstream(token);
		string selectedToken;
		while(getline(selectedstream,selectedToken,',')){
			vector<string> subRes;
			regexPattern = "\\s*(" + synonym + ")\\s*";
			match = regexMatchWithResult(regexPattern,selectedToken,subRes);
			//if it is a synonym
			if (match){
				string selectedName = subRes[1];
				selectedSyn.push_back(selectedName);
				subRes.clear();
			}
			else{
				regexPattern = "\\s*(" + attrRef + ")\\s*";
				match = regexMatchWithResult(regexPattern,selectedToken,subRes);
				//if it is a attrRef
				if(match){
					string selectedName = subRes[1];
					selectedSyn.push_back(selectedName);
					subRes.clear();
				}
			}
		}
	}
	//END SELECT STATEMENT PARSING

	while(getline(istream,token,' ')){
		if (token.length()==0){
			continue;
		}
		if (token == such){
			string next = getNextToken(istream);//read that
			token = token + " " + next;
		}
		if (token == AND){
			token = prevToken;
		}
		if (token == SUCHTHAT){
			prevToken = SUCHTHAT;
			selectStatement.push_back(token);//push such that

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
			
			prevToken = PATTERN;
			selectStatement.push_back(token);//push pattern

			string patternToken[3];
			getline(istream,patternToken[0],'(');
			getline(istream,patternToken[1],',');
			getline(istream,patternToken[2],')');

			vector<string> subRes;
			string readToken;

			//the synonym before the bracket
			subRes.clear();
			match = false;
			regexPattern = "\\s*(" + synonym + ")\\s*";
			match = regexMatchWithResult(regexPattern,patternToken[0],subRes);
			readToken = subRes[1];
			selectStatement.push_back(readToken);

			//first argument
			subRes.clear();
			match = false;
			regexPattern = "\\s*(" + varRef + ")\\s*";
			match = regexMatchWithResult(regexPattern,patternToken[1],subRes);
			readToken = subRes[1];
			selectStatement.push_back(readToken);
			
			//second (and third argument)
			istringstream argStream(patternToken[2]);
			string tok[2];
			int index=0;
			while(getline(argStream,tok[index],',')&&(index<=1)){
				index++;
			}

			//if only second argument (no third argument)
			if(tok[1].length()==0){
				subRes.clear();
				match = false;
				regexPattern = "\\s*(" + expressionSpec + ")\\s*";
				match = regexMatchWithResult(regexPattern,tok[0],subRes);
				readToken = subRes[1];
				selectStatement.push_back(readToken);
			}
			//if have third argument
			else{
				for(int i=0;i<2;i++){
					subRes.clear();
					match = false;
					regexPattern = "\\s*(" + freeString +")\\s*"; // should be underscore though, but no boolean here, it is parsing, not validation
					match = regexMatchWithResult(regexPattern,tok[i],subRes);
					readToken = subRes[1];
					selectStatement.push_back(readToken);
				}
			}
		}
		else if(token == WITH){//read with
			prevToken = WITH;
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

Relationship::TokenType QueryParser::detectTokenType(string token){
	if( regexMatch("("+synonym+")",token) ){
		return Relationship::SYNONYM;
	}
	else if( regexMatch("(_)",token) ){
		return Relationship::UNDERSCORE;
	}
	else if( regexMatch("(\""+IDENT+"\")",token) ){
		return Relationship::IDENTIFIER;
	}
	else if( regexMatch("("+INTEGER+")",token) ){
		return Relationship::INTEGER;
	}
	else if( regexMatch("(_\""+expr+"\"_)",token) ){
		return Relationship::UNDERSCOREEXPR;
	}
	else if( regexMatch("(\""+expr+"\")",token) ){
		return Relationship::EXPR;
	}
	else{
		return Relationship::INVALIDTOKEN;
	}
}

bool QueryParser::isValidSynonymStatement(string syn){
	unordered_map<string, TypeTable::SynType>::iterator it;
	it = synMap.find(syn);
	if(it==synMap.end()){
		return false;
	}
	else if(it->second == TypeTable::PROGLINE){
		return true;
	}
	else if(it->second == TypeTable::ASSIGN){
		return true;
	}
	else if(it->second == TypeTable::IF){
		return true;
	}
	else if(it->second == TypeTable::WHILE){
		return true;
	}
	else if(it->second == TypeTable::CALL){
		return true;
	}
	else if(it->second == TypeTable::STMT){
		return true;
	}
	return false;
}

Relationship QueryParser::validateDefaultClauses(vector<string>& v, int& i, bool& clauseValid){
	v.at(i) = stringToLower(v.at(i));
	string relationRef = v.at(i);

	bool formatValid = true;
	bool synValid = true;

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
		//checking synonyms arguments whether they have been declared earlier

		//first argument
		int index = 0;
		bool match = regexMatch("("+synonym+")",param[index]);
		//if it is a synonym
		if(match){
			unordered_map<string, TypeTable::SynType>::iterator it;
			it = synMap.find(param[index]);
			if(it==synMap.end()){
				synValid=false;
			}
			else if((relationRef == CALLS) || (relationRef == CALLSSTAR)){
				if(!(it->second == TypeTable::PROCEDURE)){
					synValid = false;
				}
			}
			else if((relationRef == MODIFIES) || (relationRef == USES)){
				bool validStatement = isValidSynonymStatement(param[index]);
				if ((!validStatement)&&(it->second != TypeTable::PROCEDURE)){
					synValid = false;
				}
			}
			else if((relationRef == PARENT) || (relationRef == PARENTSTAR)){
				if(!((it->second == TypeTable::WHILE)||(it->second == TypeTable::IF)||(it->second == TypeTable::STMT))){
					synValid = false;
				}
			}
			else if((relationRef == FOLLOWS) || (relationRef == FOLLOWSSTAR)){
				bool validStatement = isValidSynonymStatement(param[index]);
				if (!validStatement){
					synValid = false;
				}
			}
			else if((relationRef == NEXT) || (relationRef == NEXTSTAR)){
				bool validStatement = isValidSynonymStatement(param[index]);
				if (!validStatement){
					synValid = false;
				}
			}
			else if((relationRef == AFFECTS) || (relationRef == AFFECTSSTAR)){
				if(!((it->second == TypeTable::ASSIGN)||(it->second == TypeTable::STMT))){
					synValid = false;
				}
			}
		}

		//second argument
		index = 1;
		match = regexMatch("("+synonym+")",param[index]);
		//if it is a synonym
		if(match){
			unordered_map<string, TypeTable::SynType>::iterator it;
			it = synMap.find(param[index]);
			if(it==synMap.end()){
				synValid=false;
			}
			else if((relationRef == CALLS) || (relationRef == CALLSSTAR)){
				if(!(it->second == TypeTable::PROCEDURE)){
					synValid = false;
				}
			}
			else if((relationRef == MODIFIES) || (relationRef == USES)){
				if(!(it->second == TypeTable::VARIABLE)){
					synValid = false;
				}
			}
			else if((relationRef == PARENT) || (relationRef == PARENTSTAR)){
				bool validStatement = isValidSynonymStatement(param[index]);
				if (!validStatement){
					synValid = false;
				}
			}
			else if((relationRef == FOLLOWS) || (relationRef == FOLLOWSSTAR)){
				bool validStatement = isValidSynonymStatement(param[index]);
				if (!validStatement){
					synValid = false;
				}
			}
			else if((relationRef == NEXT) || (relationRef == NEXTSTAR)){
				bool validStatement = isValidSynonymStatement(param[index]);
				if (!validStatement){
					synValid = false;
				}
			}
			else if((relationRef == AFFECTS) || (relationRef == AFFECTSSTAR)){
				if(!((it->second == TypeTable::ASSIGN)||(it->second == TypeTable::STMT))){
					synValid = false;
				}
			}
			
		}
		
	}

	if((formatValid)&&(synValid)){
		Relationship clauseRel(v.at(i), v.at(i+1), detectTokenType(v.at(i+1)), v.at(i+2),  detectTokenType(v.at(i+2)));
		i = i+2;
		clauseValid = true;
		return clauseRel;
	}
	else{
		clauseValid = false;
		return Relationship();
	}
}

Relationship QueryParser::validatePattern(vector<string>& v, int& i, bool& patternValid){
	v.at(i) = stringToLower(v.at(i));

	bool patternAssign = false;
	bool patternIf = false;
	bool patternWhile = false;


	bool patternSynValid = true;
	string patternSyn = v.at(i+1);
	unordered_map<string, TypeTable::SynType>::iterator it;
	it = synMap.find(patternSyn);
	if(it==synMap.end()){
		patternSynValid = false;
	}
	else if(it->second == TypeTable::ASSIGN){
		patternAssign = true;
	}
	else if(it->second == TypeTable::IF){
		patternIf = true;
	}
	else if(it->second == TypeTable::WHILE){
		patternWhile = true;
	}
	else{
		patternSynValid = false;
	}
	
	bool varRefValid = true;
	string firstParam = v.at(i+2);
	string secondParam = v.at(i+3);

	if(patternAssign){
		bool match = regexMatch("("+synonym+")",firstParam);
		//if it is a synonym, check whether it's declared
		if(match){
			it = synMap.find(firstParam);
			if(it==synMap.end()){
				varRefValid = false;
			}
		}
		//second param need not to be declared because it is in valid format from the first regex valdiation
	}
	else if(patternIf){
		bool match = regexMatch("("+synonym+")",firstParam);
		//if it is a synonym, check whether it's declared
		if(match){
			it = synMap.find(firstParam);
			if(it==synMap.end()){
				varRefValid = false;
			}
		}
		//if it is a while, the second param must be an underscore
		if(secondParam != "_"){
			varRefValid = false;
		}

		//checking for third param
		//check for index out of bounds, because third param is at i+4
		if((int)v.size()>(i+4)){
			string thirdParam = v.at(i+4);
			if(thirdParam != "_"){
				varRefValid = false;
			}
		}
		else {
			varRefValid = false;
		}
	}
	else if(patternWhile){
		bool match = regexMatch("("+synonym+")",firstParam);
		//if it is a synonym, check whether it's declared
		if(match){
			it = synMap.find(firstParam);
			if(it==synMap.end()){
				varRefValid = false;
			}
		}
		//if it is a while, the second param must be an underscore
		if(secondParam != "_"){
			varRefValid = false;
		}
	}
	else{
		varRefValid = false;
	}

	if((patternSynValid)&&(varRefValid)){
		Relationship patternRel(v.at(i), v.at(i+1), v.at(i+2), detectTokenType(v.at(i+2)), v.at(i+3), detectTokenType(v.at(i+3)));
		if(patternIf){
			i = i+4;
		}
		else{
			i = i+3;
		}
		patternValid = true;
		return patternRel;
	}
	else{
		patternValid = false;
		return Relationship();
	}
}

Relationship QueryParser::validateWith(vector<string>& v, int& i, bool& withValid){
	v.at(i) = stringToLower(v.at(i));
	unordered_map<string, TypeTable::SynType>::iterator it;

	bool callSynTypeProcedure[2];
	callSynTypeProcedure[0]=false;
	callSynTypeProcedure[1]=false;

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
		match = regexMatchWithResult("("+synonym+")\\.("+attrName+")",firstParam,result);
		if(match){
			it = synMap.find(result[1]);
			if(it==synMap.end()){//if synonym not found
				withValid1 = false;
			}
			else if ((it->second != TypeTable::PROCEDURE)&&(it->second != TypeTable::CALL)&&(result[2] == "procName")){
				withValid1 = false;
			}
			else if ((it->second != TypeTable::STMT)&&
				(it->second != TypeTable::IF)&&
				(it->second != TypeTable::WHILE)&&
				(it->second != TypeTable::ASSIGN)&&
				(it->second != TypeTable::CALL)&&
				(result[2] == "stmt#")){
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

			//check if it is call procedure
			if ((it->second == TypeTable::CALL)&&(result[2] == "procName")){
				callSynTypeProcedure[0] = true; // mark the callSynTypeProc as true
			}
		}
	}

	//check whether second token is a single synonym, must be of type prog_line
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
		match = regexMatchWithResult("("+synonym+")\\.("+attrName+")",secondParam,result);
		if(match){
			it = synMap.find(result[1]);

			if(it==synMap.end()){//if synonym not found
				withValid2 = false;
			}
			else if ((it->second != TypeTable::PROCEDURE)&&(it->second != TypeTable::CALL)&&(result[2] == "procName")){
				withValid2 = false;
			}
			else if ((it->second != TypeTable::STMT)&&
				(it->second != TypeTable::IF)&&
				(it->second != TypeTable::WHILE)&&
				(it->second != TypeTable::ASSIGN)&&
				(it->second != TypeTable::CALL)&&
				(result[2] == "stmt#")){
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

			//check if it is call procedure
			if ((it->second == TypeTable::CALL)&&(result[2] == "procName")){
				callSynTypeProcedure[1] = true; // mark the callSynTypeProc as true
			}
		}
	}

	bool combinedValid = false;
	if((withValid1)&&(withValid2)){
		combinedValid = validateWithLhsAndRhs(withToken,callSynTypeProcedure);
	}

	if(combinedValid){
		Relationship withRel(v.at(i), withToken[0], detectTokenType(withToken[0]), withToken[1], detectTokenType(withToken[1]), (callSynTypeProcedure[0]||callSynTypeProcedure[1]) );
		i = i+2;
		withValid = true;
		return withRel;
	}
	else{
		withValid = false;
		return Relationship();
	}
}

bool QueryParser::validateWithLhsAndRhs(string withToken[2], bool callSynTypeProcedure[2]){
	//synonym 5 type : STMT,CONSTANT,PROCEDURE,VARIABLE,PROGLINE
	//ref : IDENTIFIER, INTEGER
	//INTEGER category : INTEGER, STMT, IF, WHILE, ASSIGN, CONSTANT, PROGLINE, CALL(if booleanflag is false)
	//CHARSTRING category : IDENTIFIER, PROCEDURE, VARIABLE, CALL(if booleanflag is true)
	const int lhs = 0;
	const int rhs = 1;

	const int categoryInt = 1;
	const int categoryCharStr = 2;

	int category[2];
	category[lhs]= -1;
	category[rhs]= -2;

	for(int i=0;i<2;i++){
		if(detectTokenType(withToken[i]) == Relationship::INTEGER){
			category[i] = categoryInt;
		}
		else if(detectTokenType(withToken[i]) == Relationship::IDENTIFIER){
			category[i] = categoryCharStr;
		}
		else{
			unordered_map<string, TypeTable::SynType>::iterator it;
			it = synMap.find(withToken[i]);
			if((it->second == TypeTable::STMT)||
				(it->second == TypeTable::IF)||
				(it->second == TypeTable::WHILE)||
				(it->second == TypeTable::ASSIGN)||
				(it->second == TypeTable::CONSTANT)||(it->second == TypeTable::PROGLINE)){
					category[i] = categoryInt;
			}
			else if ((it->second == TypeTable::PROCEDURE)||(it->second == TypeTable::VARIABLE)){
				category[i] = categoryCharStr;
			}
			//if it is of type call, check whether is procName or stmt#
			else if (it->second == TypeTable::CALL){
				if(callSynTypeProcedure[i]){
					category[i] = categoryCharStr;
				}
				else{
					category[i] = categoryInt;
				}
			}
		}
	}

	if(category[lhs]==category[rhs]){
		return true;
	}
	else{
		return false;
	}
}

bool QueryParser::isValidSelectedSyn(string &refSelectedName, bool &selectedSynIsCallProcedure){
	string selectedName = refSelectedName;
	unordered_map<string, TypeTable::SynType>::iterator it;

	vector<string> result;
	bool match = regexMatchWithResult("("+synonym+")\\.("+attrName+")",selectedName,result);
	//if it is an attrRef
	if(match){
		it = synMap.find(result[1]);
		if(it==synMap.end()){//if synonym not found
			return false;
		}
		else if ((it->second != TypeTable::PROCEDURE)&&(it->second != TypeTable::CALL)&&(result[2] == "procName")){
			return false;
		}
		else if ((it->second != TypeTable::STMT)&&
				(it->second != TypeTable::IF)&&
				(it->second != TypeTable::WHILE)&&
				(it->second != TypeTable::ASSIGN)&&
				(it->second != TypeTable::CALL)&&
				(result[2] == "stmt#")){
			return false;
		}
		else if ((it->second != TypeTable::CONSTANT)&&(result[2] == "value")){
			return false;
		}
		else if((it->second != TypeTable::VARIABLE)&&(result[2] == "varName")){
			return false;
		}
		else{
			//if the statement is valid
			refSelectedName = result[1];
			if((it->second == TypeTable::CALL)&&(result[2] == "procName")){
				selectedSynIsCallProcedure = true;
			}
		}
	}
	//if it is a regular synonym
	else{
		it = synMap.find(selectedName);
		if(it==synMap.end()){
			return false;
		}
	}
	return true;
}

Query QueryParser::constructAndValidateQuery(vector<string> v, unordered_map<string, TypeTable::SynType> map, bool &valid){
	Query query;

	//set selected synonyms (supports tuple)
	vector<string> selectedSynForQuery;
	vector<bool> selectedSynIsCallProcedureForQuery;

	for (int i=0;i<(int)selectedSyn.size();i++){
		bool selectedSynIsProcedure = false;
		//semantic check on whether the selected syn is present
		if(isValidSelectedSyn(selectedSyn[i], selectedSynIsProcedure)){
			selectedSynForQuery.push_back(selectedSyn[i]);
			selectedSynIsCallProcedureForQuery.push_back(selectedSynIsProcedure);
		}
		else{
			valid = false;
			return Query();
		}
	}
	//set both table
	query.setSelectedSyn(selectedSynForQuery);
	query.setSelectedSynIsCallProcedure(selectedSynIsCallProcedureForQuery);

	//set synTable
	query.setSynTable(map);

	//validate all clauses
	for (int i = 0; i < (int) v.size(); i++){
		string relationRef = v.at(i);
		
		bool clauseMatch = regexMatch("(" + allClause + ")",relationRef);

		if(clauseMatch){
			bool clauseValid = false;
			Relationship clauseRel = validateDefaultClauses(v,i,clauseValid);
			if(clauseValid){
				query.addRelationship(clauseRel);
			}
			else{
				valid = false;
				return Query();
			}
		}
		else if (relationRef == PATTERN){
			bool patternValid = false;
			Relationship patternRel = validatePattern(v,i,patternValid);
			if(patternValid){
				query.addRelationship(patternRel);
			}
			else{
				valid = false;
				return Query();
			}
		}
		else if (relationRef == WITH){
			bool withValid = false;
			Relationship withRel = validateWith(v,i,withValid);
			if(withValid){
				query.addRelationship(withRel);
			}
			else{
				valid = false;
				return Query();
			}
		}

	}
	return query;
}

//public queryParse
Query QueryParser::queryParse(string queryStr, bool &valid){
	synMap.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
	//cout << "here" << endl;
	istringstream istream(queryStr);
	//cout << queryStr << endl;
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
			//cout << queryStr << endl;
			valid = false;
			return Query();
		}
	}
	valid = true;
	Query query = constructAndValidateQuery(selectStatement, synMap, valid);
	return query;
}