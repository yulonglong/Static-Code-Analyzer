#include "QueryParser.h"

using namespace std;

QueryParser::QueryParser(){
	declarationCounter = 0;
	selectCounter = 0;
	statementCounter = 0;
	tokenCounter = 0;
	expressionTokenCounter = 0;
	selectCase = 0;
}

// ===============VALIDATION PART OF THE CODES==================//

void QueryParser::bootstrap(){
	statements.clear();
	tokens.clear();
	expressionTokens.clear();
	selectStatement.clear();
	synMap.clear();

	declarationCounter = 0;
	selectCounter = 0;
	statementCounter = 0;
	tokenCounter = 0;
	expressionTokenCounter = 0;
	selectCase = 0;
}


bool QueryParser::validate(string st){
	s = st;
	bootstrap();
	
	if (!generateStatements()) return false;

	// FOR EACH STATEMENT, CHECK FOR VALIDITY
	for(size_t i = 0; i < statements.size(); i++){
		if(selectCounter > 0) return false;

		statement = getNextStatement();
		generateTokens();
		nextToken = getNextToken();

		if(declaration() || select()); 
		else return false;
		tokenCounter = 0;
	}

	if (selectCounter != 1) return false;

	//cout << endl << "selectStatement vector: " << endl;
	for (size_t i = 0; i < selectStatement.size(); i++){
		//cout << selectStatement.at(i) << endl;
	}

	return true;
}

bool QueryParser::generateStatements(){
	// DIVIDE THE QUERY STRING INTO STATEMENTS, SEPARATED BY SEMICOLON
	// STORE THEM INTO STATEMENTS VECTOR
	//cout << "generating statements..." << endl;
	statements.clear();

	//=====================================================================
	// comment this part out if you want the end semicolon to be flexible
	//=====================================================================

	// remove trailing spaces
	while(s.at(s.length()-1) == ' '){
		s = s.substr(0, s.length()-1);
	}

	// check if end is semicolon
	if(s.at(s.length()-1) == ';'){
		return false;
	}

	//=======================================================================

	char *str = new char[s.length() + 1];
	strcpy_s(str, s.length() + 1, s.c_str());

	char seps[] = ";";
	char *token = NULL;
	char *nextToken = NULL;

	token = strtok_s(str, seps, &nextToken);

	while (token != NULL)
	{
		//cout << "token: " << token << endl;
		string vs(token);
		// TRIM THE LEADING SPACES
		while(vs.at(0) == ' '){
			vs = vs.substr(1);
			// TAKES CARE OF STRING CONSISTING OF ONLY WHITESPACES
			if (vs.length() == 0) return false;
		}

		statements.push_back(vs);
		token = strtok_s(NULL, seps, &nextToken);
	}

	//cout << endl << "content of statements of size " << statements.size() << ": " << endl;
	for(size_t i = 0; i < statements.size(); i++){
		//cout << statements.at(i) << endl;
	}

	// TAKES CARE OF EMPTY STRING
	if (statements.size() > 0) return true;
	else return false;
}

void QueryParser::generateTokens(){
	//cout << "generating tokens..." <<endl;
	tokens.clear();
	// GENERATE TOKENS FROM STATEMENT, STORE THEM IN TOKENS VECTOR
	char *stat = new char[statement.length() + 1];
	strcpy_s(stat, statement.length()+1, statement.c_str());

	char seps[] = " ";
	char *token = NULL;
	char *nextToken = NULL;

	token = strtok_s(stat, seps, &nextToken);

	while (token != NULL)
	{
		tokens.push_back(token);
		token = strtok_s(NULL, seps, &nextToken);
	}

	//cout << endl;
	//cout << "tokens: " << endl;
	for (size_t i = 0; i < tokens.size(); i++){
		//cout << tokens.at(i) <<endl;
	}
	//cout << endl;
}

bool QueryParser::generateSelectTokens(){
	//cout << endl << "entering generate select tokens..." << endl;
	tokens.clear();

	int patternIndex = statement.find("pattern");
	int suchthatIndex = statement.find("such that");

	string tok;
	string patternClause;
	string suchthatClause;

	if (patternIndex == -1 && suchthatIndex != -1){
		// ONLY SUCH THAT CLAUSE EXISTS
		suchthatClause = statement.substr(suchthatIndex, patternIndex);
		selectCase = 1;
	}
	if (patternIndex != -1 && suchthatIndex == -1){
		// ONLY PATTERN CLAUSE EXISTS
		patternClause = statement.substr(patternIndex, suchthatIndex);
		selectCase = 2;
	}
	if (patternIndex != -1 && suchthatIndex != -1){
		// BOTH SUCH THAT AND PATTERN EXIST
		if(patternIndex < suchthatIndex){
			// PATTERN APPEARS FIRST
			//cout << "such that index: " << suchthatIndex << endl;
			//cout << "statement: " << statement << endl;
			patternClause = statement.substr(patternIndex, suchthatIndex - 9);
			//cout << "pattern clause: " << patternClause << endl;
			suchthatClause = statement.substr(suchthatIndex);
			//cout << "such that clause: " << suchthatClause << endl;
			selectCase = 3;
		} else{
			// SUCH THAT APPEARS FIRST
			patternClause = statement.substr(patternIndex);
			//cout << "pattern clause: " << patternClause << endl;
			suchthatClause = statement.substr(suchthatIndex, patternIndex-9);
			//cout << "such that clause: " << suchthatClause << endl;
			selectCase = 4;
		}
	}

	char *stat = new char[statement.length() + 1];
	strcpy_s(stat, statement.length()+1, statement.c_str());

	char seps[] = " ";
	char *token = NULL;
	char *nextToken = NULL;

	token = strtok_s(stat, seps, &nextToken);

	// TOKENIZE STATEMENT UNTIL KEYWORD "SUCH THAT" OR "PATTERN" IS FOUND.
	while (token != NULL)
	{
		tok = token;
		int temp = tok.find("such");
		if(temp != -1){
			break;	
		}
		temp = tok.find("pattern");
		if(temp != -1){
			break;	
		}
		tokens.push_back(token);
		token = strtok_s(NULL, seps, &nextToken);
	}

	switch(selectCase){
	case 0: 
		return false;
	case 1: 
		if (!tokenizeSuchthat(suchthatClause)) return false;
		break;
	case 2:
		if (!tokenizePattern(patternClause)) return false;
		break;
	case 3:
		if (!tokenizePattern(patternClause)) return false;
	case 4:
		if (!tokenizeSuchthat(suchthatClause)) return false;
		if (selectCase == 3) break;
		else if (!tokenizePattern(patternClause)) return false;
	}

	//cout << endl << "SELECT TOKENS!!!: " << endl;
	for(size_t i = 0; i<tokens.size(); i++){
		//cout << tokens.at(i) <<endl;
	}
	return true;
}

bool QueryParser::tokenizePattern(string patternClause){
	tokens.push_back("pattern");
	string patternClause2 = patternClause;
	patternClause = patternClause.substr(7);

	// REMOVE LEADING SPACES
	while(patternClause.at(0) == ' '){
		if (patternClause.length() == 1) return false;
		patternClause = patternClause.substr(1);
	}

	int openBracketIndex = patternClause.find("(");
	if (openBracketIndex == 0 || openBracketIndex == -1){
		return false;
	}
	string synAssign = patternClause.substr(0, openBracketIndex);

	// REMOVE TRAILING SPACES
	while(synAssign.at(synAssign.length() -1) == ' '){
		if (synAssign.length() == 1) return false;
		synAssign = synAssign.substr(0, synAssign.length() -1);
	}

	tokens.push_back(synAssign);
	tokens.push_back("(");
	patternClause = patternClause.substr(openBracketIndex + 1);

	// REMOVE LEADING SPACES
	while(patternClause.at(0) == ' '){
		if (patternClause.length() == 1) return false;
		patternClause = patternClause.substr(1);
	}

	int comaIndex = patternClause.find(",");
	if (comaIndex == 0 || comaIndex == -1){
		return false;
	}

	string arg1 = patternClause.substr(0, comaIndex);

	// REMOVE TRAILING SPACES
	while(arg1.at(arg1.length() -1) == ' '){
		if (arg1.length() == 1) return false;
		arg1 = arg1.substr(0, arg1.length() -1);
	}

	tokens.push_back(arg1);
	tokens.push_back(",");
	patternClause = patternClause.substr(comaIndex + 1);

	// REMOVE LEADING SPACES
	while(patternClause.at(0) == ' '){
		if (patternClause.length() == 1) return false;
		patternClause = patternClause.substr(1);
	}

	int closeBracketIndex = patternClause.find(")");
	if (closeBracketIndex == 0 || closeBracketIndex == -1){
		return false;
	}

	string arg2 = patternClause.substr(0, closeBracketIndex);

	// REMOVE TRAILING SPACES
	while(arg2.at(arg2.length() -1) == ' '){
		if (arg2.length() == 1) return false;
		arg2 = arg2.substr(0, arg2.length() -1);
	}

	tokens.push_back(arg2);
	tokens.push_back(")");

	patternClause = patternClause.substr(closeBracketIndex + 1);
	//cout << "pattern clause: " << patternClause << endl;
	if(patternClause.length() > 0){
		//cout << "removing trailing spaces in pattern clause..." << endl;
		while(patternClause.at(patternClause.length() -1) == ' '){
			patternClause = patternClause.substr(0, patternClause.length() -1);
			if (patternClause.length() == 0) break;
		}
		if (patternClause.length() > 0) return false;
	}
	
	int s2Length = patternClause2.length() + 1;
	char *str2 = new char[s2Length];
	strcpy_s(str2, s2Length, patternClause2.c_str());

	char seps2[] = " ;,()";
	char *token2 = NULL;
	char *nextToken2 = NULL;

	token2 = strtok_s(str2, seps2, &nextToken2);

	while (token2 != NULL)
	{
		string vs2(token2);
		selectStatement.push_back(vs2);
		token2 = strtok_s(NULL, seps2, &nextToken2);
	}

	return true;
}

bool QueryParser::tokenizeSuchthat(string suchthatClause){
	tokens.push_back("such");
	string suchthatClause2 = suchthatClause;
	suchthatClause = suchthatClause.substr(4);

	// REMOVE LEADING SPACES
	while(suchthatClause.at(0) == ' '){
		if (suchthatClause.length() == 1) return false;
		suchthatClause = suchthatClause.substr(1);
	}

	int thatIndex = suchthatClause.find("that");
	if (thatIndex != 0 || thatIndex == -1){
		return false;
	}

	tokens.push_back("that");
	suchthatClause = suchthatClause.substr(4);

	// REMOVE LEADING SPACES
	while(suchthatClause.at(0) == ' '){
		if (suchthatClause.length() == 1) return false;
		suchthatClause = suchthatClause.substr(1);
	}

	int openBracketIndex = suchthatClause.find("(");
	if (openBracketIndex == 0 || openBracketIndex == -1){
		return false;
	}
	string relref = suchthatClause.substr(0, openBracketIndex);

	// REMOVE TRAILING SPACES
	while(relref.at(relref.length() -1) == ' '){
		if (suchthatClause.length() == 1) return false;
		relref = relref.substr(0, relref.length() -1);
	}

	tokens.push_back(relref);
	tokens.push_back("(");
	suchthatClause = suchthatClause.substr(openBracketIndex + 1);

	// REMOVE LEADING SPACES
	while(suchthatClause.at(0) == ' '){
		if (suchthatClause.length() == 1) return false;
		suchthatClause = suchthatClause.substr(1);
	}

	int comaIndex = suchthatClause.find(",");
	if (comaIndex == 0 || comaIndex == -1){
		return false;
	}

	string arg1 = suchthatClause.substr(0, comaIndex);

	// REMOVE TRAILING SPACES
	while(arg1.at(arg1.length() -1) == ' '){
		if (arg1.length() == 1) return false;
		arg1 = arg1.substr(0, arg1.length() -1);
	}

	tokens.push_back(arg1);
	tokens.push_back(",");
	suchthatClause = suchthatClause.substr(comaIndex + 1);

	// REMOVE LEADING SPACES
	while(suchthatClause.at(0) == ' '){
		if (suchthatClause.length() == 1) return false;
		suchthatClause = suchthatClause.substr(1);
	}

	int closeBracketIndex = suchthatClause.find(")");
	if (closeBracketIndex == 0 || closeBracketIndex == -1){
		return false;
	}

	string arg2 = suchthatClause.substr(0, closeBracketIndex);

	// REMOVE TRAILING SPACES
	while(arg2.at(arg2.length() -1) == ' '){
		if (arg2.length() == 1) return false;
		arg2 = arg2.substr(0, arg2.length() -1);
	}

	tokens.push_back(arg2);
	tokens.push_back(")");

	suchthatClause = suchthatClause.substr(closeBracketIndex + 1);
	//cout << "such that clause: " << suchthatClause << endl;
	if(suchthatClause.length() > 0){
		//cout << "removing trailing spaces in such that clause..." << endl;
		while(suchthatClause.at(suchthatClause.length() -1) == ' '){
			suchthatClause = suchthatClause.substr(0, suchthatClause.length() -1);
			if (suchthatClause.length() == 0) break;
		}
		if (suchthatClause.length() > 0) return false;
	}

	int s2Length = suchthatClause2.length() + 1;
	char *str2 = new char[s2Length];
	strcpy_s(str2, s2Length, suchthatClause2.c_str());

	char seps2[] = " ;,()";
	char *token2 = NULL;
	char *nextToken2 = NULL;

	token2 = strtok_s(str2, seps2, &nextToken2);

	while (token2 != NULL)
	{
		string vs2(token2);
		selectStatement.push_back(vs2);
		token2 = strtok_s(NULL, seps2, &nextToken2);
	}

	return true;
}

string QueryParser::getFirstToken(){
	//cout << "getting first token..." << endl;
	char *stat = new char[statement.length() + 1];
	strcpy_s(stat, statement.length() + 1, statement.c_str());

	char seps[] = " ";
	char *token = NULL;
	char *nextToken = NULL;

	token = strtok_s(stat, seps, &nextToken);
	string toString = token;
	return toString;
}

string QueryParser::getNextToken(){
	//cout << "getting next token... ";
	string nextToken = tokens.at(tokenCounter);
	tokenCounter++;
	//cout << nextToken << endl;
	return nextToken;
}

string QueryParser::getNextExpressionToken(){
	//cout << "getting next expression token... ";
	string nextExpressionToken = expressionTokens.at(expressionTokenCounter);
	expressionTokenCounter++;
	//cout << nextExpressionToken << endl;
	return nextExpressionToken;
}

string QueryParser::getNextStatement(){
	//cout << "getting next statement..." << endl;
	string nextStatement = statements.at(statementCounter);
	statementCounter++;
	return nextStatement;
}

bool QueryParser::declaration(){
	//cout << "entering declaration..." << endl;
	if (!designEntity()) return false;

	if(!generateDeclarationTokens()) return false;

	string design_entity = tokens.at(0);
	TypeTable::SynType syntype;

	if (design_entity == "assign"){
		syntype = TypeTable::ASSIGN;
	} else if (design_entity == "stmt"){
		syntype = TypeTable::STMT;
	} else if (design_entity == "while"){
		syntype = TypeTable::WHILE;
	} else if (design_entity == "variable"){
		syntype = TypeTable::VARIABLE;
	} else if (design_entity == "constant"){
		syntype = TypeTable::CONSTANT;
	} else if (design_entity == "prog_line"){
		syntype = TypeTable::PROGLINE;
	} else return false;

	for (size_t i = 1; i < tokens.size(); i++){
		nextToken = tokens.at(i);
		if(synonym()){
			synMap.insert(make_pair(tokens.at(i), syntype));
		} else return false;
	}

	declarationCounter++;
	return true;
}

bool QueryParser::generateDeclarationTokens(){
	//cout << "enter generate declaration tokens..." << endl;

	tokens.clear();
	//cout << "finding the first word..." << endl;
	// find the first word
	
	int spaceIndex = statement.find(" ");
	if(spaceIndex == -1) return false;

	string keyword = statement.substr(0, spaceIndex);
	//cout << "keyword is: " << keyword << endl;
	tokens.push_back(keyword);

	statement = statement.substr(spaceIndex);
	//cout << "statement is: " << statement << endl;

	// remove leading spaces
	while(statement.at(0) == ' '){
		//cout << "removing leading space..."<< endl;
		statement = statement.substr(1);
		//cout << "statement is: " << statement << endl;
		if (statement.length() == 0) return false;
	}

	int comaIndex = statement.find(",");

	while(comaIndex!=-1){
		string syn = statement.substr(0, comaIndex);
		//cout << "synonym is: " << syn << endl;
		
		// remove leading spaces
		while(syn.at(0) == ' '){
			//cout << "removing leading spaces..." << endl;
			syn = syn.substr(1);
			if (syn.length() == 0) return false;
		}


		// remove trailing spaces
		while (syn.at(syn.length() -1) == ' '){
			//cout << "removing trailing spaces..." << endl;
			syn = syn.substr(0, syn.length()-1);
			if (syn.length() == 0) return false;
		}

		tokens.push_back(syn);
		statement = statement.substr(comaIndex+1);
		comaIndex = statement.find(",");
	}

	if (statement.length() != 0){
		// remove leading spaces
		while(statement.at(0) == ' '){
			statement = statement.substr(1);
			if (statement.length() == 0) break;
		}

		// remove trailing spaces
		while (statement.at(statement.length() -1) == ' '){
			statement = statement.substr(0, statement.length()-1);
			if (statement.length() == 0) break;
		}

		tokens.push_back(statement);
	}

	//cout << endl << "DECLARATION TOKENS" << endl;
	for(size_t i = 0; i < tokens.size(); i++){
		//cout << tokens.at(i) << endl;
	}

	return true;
}

bool QueryParser::designEntity(){
	//cout << "entering design entity..." << endl;
	if (nextToken.compare("stmt") == 0 || nextToken.compare("assign") == 0 ||
		nextToken.compare("while") == 0 || nextToken.compare("variable") == 0 ||
		nextToken.compare ("constant") == 0 || nextToken.compare("prog_line") == 0){
			return true;
	} else return false;
}

bool QueryParser::synonym(){
	//cout << "entering synonym..." << endl;
	if (!ident()){
		return false;	
	}
	return true;
}

bool QueryParser::ident(){
	//cout << "entering ident..." << endl;
	int nextTokenLength = nextToken.length() + 1;
	char *id = new char[nextTokenLength];
	strcpy_s(id, nextTokenLength, nextToken.c_str());

	//cout << endl << endl << "IDENT() --> nextToken is..." << nextToken << endl;

	// CHECK IF THE FIRST CHARACTER IS A LETTER
	int ascii = id[0];
	if((ascii > 64 && ascii < 93) || (ascii > 96 && ascii < 123));
	else return false;

	// IF THERE IS MORE THAN ONE CHARACTER, CHECK IF OTHER CHARAS ARE NOT LETTER OR DIGIT OR HEX SIGN
	// hex sign: 35
	// numbers: 48-57
	// uppercase letters: 65-90
	// lowercase letters: 97-122

	//cout << nextToken << endl;
	int len = nextToken.length();
	if (len > 1){
		for(size_t i = 0; i < (unsigned int) len; i++){
			//cout << "id " << i << ": " << id[i] << endl;
			ascii = id[i];
			if((ascii >=97 && ascii <=122) || (ascii >= 65 && ascii <=90) ||
				(ascii >= 48 && ascii <=57 || ascii == 35)){
					// do nothing, move on to next character
			} else return false;
		}
	}
	return true;
}

bool QueryParser::select(){
	//cout << "entering select..." << endl;
	
	if (!match("Select")) return false;
	selectStatement.push_back("Select");
	tokenCounter = 1;
	nextToken = getNextToken();

	if(declarationCounter == 0){
		// THERE IS NO DECLARATION BEFORE SELECT CLAUSE
		if(!match("BOOLEAN")) return false;
		if (tokens.size() == 2) return false;
		selectStatement.push_back("BOOLEAN");
	} else {
		// THERE ARE SOME DECLARATIONS BEFORE SELECT CLAUSE
		if(!synonym()) return false;
		selectStatement.push_back(nextToken);
	}

	if(tokens.size() > 2){
		if (!generateSelectTokens()) return false;
		nextToken = getNextToken();
		
		switch(selectCase){
		case 0: 
			return false;
		case 1:
			if (!suchThat()) return false;
			break;
		case 2:
			if (!pattern()) return false;
			break;
		case 3:
			if (!pattern()) return false;
			nextToken = getNextToken();
			if (!suchThat()) return false;
			break;
		case 4:
			if (!suchThat()) return false;
			nextToken = getNextToken();
			if (!pattern()) return false;
			break;
		}
	}
	selectCounter++;
	return true;
}

bool QueryParser::suchThat(){
	if(!match("such")) return false;
	nextToken = getNextToken();
		
	if (!match("that")) return false;
	nextToken = getNextToken();

	if (!relRef()) return false;

	return true;
}

bool QueryParser::pattern(){
	if(!match("pattern")) return false;
	nextToken = getNextToken();

	if(!synAssign()) return false;
	nextToken = getNextToken();

	if(!match("(")) return false;
	nextToken = getNextToken();

	if (!entRef()) return false;
	nextToken = getNextToken();

	if (!match(",")) return false;
	nextToken = getNextToken();

	if (!generateExpressionTokens()) return false;
	nextToken = getNextExpressionToken();

	if(!expressionSpec()) return false;
	nextToken = getNextToken();

	if (!match(")")) return false;

	return true;
}

bool QueryParser::generateExpressionTokens(){
	//cout << endl << "entering generate expression tokens..." << endl;
	expressionTokens.clear();
	// CONVERT NEXTTOKEN TO EXPRESSION TOKENS

	//cout<< "nextToken is..." << nextToken << endl;
	if (nextToken.length() == 0) return false;

	// FIRST CHARACTER MUST BE AN UNDERSCORE
	int underscoreIndex = nextToken.find("_");
	if (underscoreIndex != 0 || underscoreIndex == -1) return false;
	//cout << "first character passes..." << endl;
	expressionTokens.push_back("_");
	
	if(nextToken.length() > 1) {
		nextToken = nextToken.substr(1);
		//cout<< "nextToken is..." << nextToken << endl;
	} else return true;

	// THE REST IS OPTIONAL
	int doubleQuoteIndex = -1;
	if (nextToken.length() > 0){
		doubleQuoteIndex = nextToken.find("\"");
	}
	if (doubleQuoteIndex != -1 && doubleQuoteIndex == 0){
		expressionTokens.push_back("\"");
		nextToken = nextToken.substr(1);
		//cout<< "nextToken is..." << nextToken << endl;
	}

	int plusIndex = -1;
	if (nextToken.length() > 0){
		plusIndex = nextToken.find("+");
	}
	if (plusIndex != -1 && plusIndex != 0){
		string factor = nextToken.substr(0, plusIndex);
		expressionTokens.push_back(factor);
		expressionTokens.push_back("+");
		nextToken = nextToken.substr(plusIndex + 1);
		//cout<< "nextToken is..." << nextToken << endl;
	}

	doubleQuoteIndex = -1;
	if (nextToken.length() > 0){
		doubleQuoteIndex = nextToken.find("\"");
	}
	if (doubleQuoteIndex != -1 && doubleQuoteIndex != 0){
		string factor = nextToken.substr(0, doubleQuoteIndex);
		expressionTokens.push_back(factor);
		expressionTokens.push_back("\"");
		nextToken = nextToken.substr(doubleQuoteIndex + 1);
		//cout<< "nextToken is..." << nextToken << endl;
	}

	underscoreIndex = -1;
	if (nextToken.length() > 0){
		underscoreIndex = nextToken.find("_");
	}
	if (underscoreIndex != -1 && underscoreIndex == 0){
		expressionTokens.push_back("_");
		//cout << "nextToken.length()... " << nextToken.length() << endl;
		if (underscoreIndex != nextToken.length() - 1) return false;
	}
	//cout << "last character passes..." << endl << endl;

	//cout << endl << "expressionTokens: " << endl;
	for(size_t i = 0; i < expressionTokens.size(); i++){
		//cout << expressionTokens.at(i);
	}
	//cout << endl;
	return true;
}

bool QueryParser::synAssign(){
	if (declarationCounter == 0) return false;
	if (synMap.at(nextToken) != TypeTable::ASSIGN) return false;
	return true;
}

bool QueryParser::expressionSpec(){
	if(xpSpec1() || xpSpec2() || xpSpec3());
	else return false;

	return true;
}

bool QueryParser::xpSpec1(){
	if (expressionTokens.size() != 7) return false;
	
	if(!match("_")) {
		expressionTokenCounter = 0;
		return false;	
	}
	nextToken = getNextExpressionToken();

	if(!match("\"")) {
		expressionTokenCounter = 0;
		return false;	
	}
	nextToken = getNextExpressionToken();

	if(!factor()) {
		expressionTokenCounter = 0;
		return false;	
	}
	nextToken = getNextExpressionToken();

	if(!match("+")) {
		expressionTokenCounter = 0;
		return false;	
	}
	nextToken = getNextExpressionToken();

	if(!factor()) {
		expressionTokenCounter = 0;
		return false;	
	}
	nextToken = getNextExpressionToken();

	if(!match("\"")) {
		expressionTokenCounter = 0;
		return false;	
	}
	nextToken = getNextExpressionToken();

	if(!match("_")) {
		expressionTokenCounter = 0;
		return false;	
	}

	return true;
}

bool QueryParser::xpSpec2(){
	if (expressionTokens.size() != 5) return false;

	if(!match("_")) {
		expressionTokenCounter = 0;
		return false;	
	}
	nextToken = getNextExpressionToken();

	if(!match("\"")) {
		expressionTokenCounter = 0;
		return false;	
	}
	nextToken = getNextExpressionToken();

	if(!factor()) {
		expressionTokenCounter = 0;
		return false;	
	}
	nextToken = getNextExpressionToken();
	
	if(!match("\"")) {
		expressionTokenCounter = 0;
		return false;	
	}
	nextToken = getNextExpressionToken();

	if(!match("_")) {
		expressionTokenCounter = 0;
		return false;	
	}
	return true;
}

bool QueryParser::xpSpec3(){
	if (expressionTokens.size() != 1) return false;
	if(!match("_")) {
		expressionTokenCounter = 0;
		return false;	
	}
	return true;
}

bool QueryParser::factor(){
	if(integer() || varName())
		return true;
	else return false;
}

bool QueryParser::varName(){
	//cout << "entering varName..." << endl;
	int nextTokenLength = nextToken.length() + 1;
	char *id = new char[nextTokenLength];
	strcpy_s(id, nextTokenLength, nextToken.c_str());

	// CHECK IF THE FIRST CHARACTER IS A LETTER
	int ascii = id[0];
	if((ascii > 64 && ascii < 93) || (ascii > 96 && ascii < 123));
	else return false;

	// IF THERE IS MORE THAN ONE CHARACTER, CHECK IF OTHER CHARAS ARE NOT LETTER OR DIGIT
	if (nextToken.length() > 1){
		for(size_t i = 1; i < nextToken.length()-1; i++){
			ascii = id[i];
			if (ascii <= 47 || (ascii > 58 && ascii < 65) || (ascii > 90 && ascii < 97) || ascii > 122){
				return false;
				break;
			}
		}
	} 
	return true;
}

bool QueryParser::relRef(){
	if(modifiesS() || usesS() || parent() || parentT() || follows() || followsT()){
		return true;
	} else return false;
}

bool QueryParser::modifiesS(){
	//cout << "entering modifies..." << endl;

	if (!match("Modifies")) {
		//cout << "NOT A MODIFIES STATEMENT" << endl;
		return false;
	}
	nextToken = getNextToken();
	
	if (!match("(")) return false;
	nextToken = getNextToken();

	if (!stmtRef()) return false;
	nextToken = getNextToken();

	if(!match(",")) return false;
	nextToken = getNextToken();

	if (!entRef()) return false;
	nextToken = getNextToken();

	if (!match(")")) return false;

	return true;
}

bool QueryParser::entRef(){
	if (synonym() || match("_")){
		return true;
	} else if (nextToken.at(0) == '"'){
		if (nextToken.at(nextToken.length()-1) != '"') return false;
		string var = nextToken.substr(1, nextToken.length() -2);
		//cout << "var is: " << var << endl;
		nextToken = var;
		if(!ident()){
			//cout << "NOT A VALID IDENTIFIER" << endl;
			return false;
		}
	} else return false;

	//cout << "A VALID IDENTIFIER" << endl;
	return true;
}

bool QueryParser::stmtRef(){
	if (synonym() || match("_") || integer()){
		return true;
	} else return false;
}

bool QueryParser::integer(){
	//cout << "entering integer..." << endl;
	int nextTokenLength = nextToken.length() + 1;
	char *id = new char[nextTokenLength];
	strcpy_s(id, nextTokenLength, nextToken.c_str());

	// CHECK IF THE FIRST CHARACTER IS NOT A DIGIT
	int ascii = id[0];
	// 0-9 IN ASCII = 48-57
	if((ascii < 48 || ascii > 57)) return false;

	// IF THERE IS MORE THAN ONE CHARACTER, CHECK IF OTHER CHARAS ARE NOT LETTER OR DIGIT
	if (nextToken.length() > 1){
		for(size_t i = 1; i < nextToken.length()-1; i++){
			ascii = id[i];
			if (ascii < 47 || ascii > 57){
				return false;
			}
		}
	} 
	return true;
}

bool QueryParser::usesS(){
	//cout << "entering uses..." << endl;

	if (!match("Uses")) {
		//cout << "NOT A USES STATEMENT" << endl;
		return false;
	}
	nextToken = getNextToken();
	
	if (!match("(")) return false;
	nextToken = getNextToken();

	if (!stmtRef()) return false;
	nextToken = getNextToken();

	if(!match(",")) return false;
	nextToken = getNextToken();

	if (!entRef()) return false;
	nextToken = getNextToken();

	if (!match(")")) return false;

	return true;
}

bool QueryParser::parent(){
	//cout << "entering parent..." << endl;

	if (!match("Parent")) {
		//cout << "NOT A PARENT STATEMENT" << endl;
		return false;
	}
	nextToken = getNextToken();
	
	if (!match("(")) return false;
	nextToken = getNextToken();

	if (!stmtRef()) return false;
	nextToken = getNextToken();

	if(!match(",")) return false;
	nextToken = getNextToken();

	if (!stmtRef()) return false;
	nextToken = getNextToken();

	if (!match(")")) return false;

	return true;
}

bool QueryParser::parentT(){
	//cout << "entering parent*..." << endl;

	if (!match("Parent*")) {
		//cout << "NOT A PARENT* STATEMENT" << endl;
		return false;
	}
	nextToken = getNextToken();
	
	if (!match("(")) return false;
	nextToken = getNextToken();

	if (!stmtRef()) return false;
	nextToken = getNextToken();

	if(!match(",")) return false;
	nextToken = getNextToken();

	if (!stmtRef()) return false;
	nextToken = getNextToken();

	if (!match(")")) return false;

	return true;
}

bool QueryParser::follows(){
	//cout << "entering follows..." << endl;

	if (!match("Follows")) {
		//cout << "NOT A FOLLOWS STATEMENT" << endl;
		return false;
	}
	nextToken = getNextToken();
	
	if (!match("(")) return false;
	nextToken = getNextToken();

	if (!stmtRef()) return false;
	nextToken = getNextToken();

	if(!match(",")) return false;
	nextToken = getNextToken();

	if (!stmtRef()) return false;
	nextToken = getNextToken();

	if (!match(")")) return false;

	return true;
}

bool QueryParser::followsT(){
	//cout << "entering follows*..." << endl;

	if (!match("Follows*")) {
		//cout << "NOT A FOLLOWS* STATEMENT" << endl;
		return false;
	}
	nextToken = getNextToken();
	
	if (!match("(")) return false;
	nextToken = getNextToken();

	if (!stmtRef()) return false;
	nextToken = getNextToken();

	if(!match(",")) return false;
	nextToken = getNextToken();

	if (!stmtRef()) return false;
	nextToken = getNextToken();

	if (!match(")")) return false;

	return true;
}

bool QueryParser::match(string toMatch){
	if (nextToken.compare(toMatch) == 0){
		return true;
	} else {
		return false;
	}
}

vector<string> QueryParser::getStatements(){
	return statements;
}


// ===============PARSING PART OF THE CODES================ //

Query QueryParser::parse(){
	synMap.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
	Query query = makeQuery(selectStatement, synMap);
	addQuery(query);
	return query;
}

vector<Query> QueryParser::getQueries(){
	return queries;
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

//unordered_map<string, TypeTable::SynType> QueryParser::parseSynonyms()
//{
//	vector<string> v;
//	char * str = new char [declarationString.length() + 1];
//	strcpy_s(str, declarationString.length() + 1, declarationString.c_str());
//
//	char seps[] = " ";
//	char * token = NULL;
//	char * nextToken = NULL;
//
//	token = strtok_s(str, seps, &nextToken);
//
//	while (token != NULL)
//	{
//		string vs(token);
//		v.push_back(vs);
//		token = strtok_s(NULL, seps, &nextToken);
//	}
//	
//	unordered_map<string, TypeTable::SynType> map;
//	
//	for(size_t i = 0; i < v.size(); i++){
//		string temp1 = v.at(i);
//		i++;
//		string temp2 = v.at(i);
//		
//		if (temp1.compare("assign") == 0){
//			map.insert(make_pair(temp2, TypeTable::ASSIGN));
//		} else if (temp1.compare("while") == 0){
//			map.insert(make_pair(temp2, TypeTable::WHILE));
//		} else if (temp1.compare("stmt") == 0){
//			map.insert(make_pair(temp2, TypeTable::STMT));
//		} else if (temp1.compare("prog_line") == 0){
//			map.insert(make_pair(temp2, TypeTable::PROGLINE));
//		} else if (temp1.compare("variable") == 0){
//			map.insert(make_pair(temp2, TypeTable::VARIABLE));
//		} else if (temp1.compare("constant") == 0){
//			map.insert(make_pair(temp2, TypeTable::CONSTANT));
//		} else {
//			map.insert(make_pair(temp2, TypeTable::INVALID)); 
//		}
//	}
//
//	map.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
//	return map;
//}

void QueryParser::addQuery(Query q){
	queries.push_back(q);
}
