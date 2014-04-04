// Preconditions:
// Assume that first line is always the synonym declaration followed by queries
// Assume that syntax and usage is always correct
// limitations: relationships in query must be CAPITALIZED

#include "QueryParser.h"


QueryParser::QueryParser(){

}

Query QueryParser::parse(string s){
	vector<string> v;
	int sLength = s.length() + 1;

	string s2 = s;
	vector <string> v2;
	int s2Length = s2.length() + 1;
	char *str2 = new char[s2Length];
	strcpy_s(str2, s2Length, s2.c_str());

	char seps2[] = " ;,()";
	char *token2 = NULL;
	char *nextToken2 = NULL;

	token2 = strtok_s(str2, seps2, &nextToken2);

	while (token2 != NULL)
	{
		string vs2(token2);
		v2.push_back(vs2);
		token2 = strtok_s(NULL, seps2, &nextToken2);
	}

	int selectIndex = 0;
	try{
		while (v2.at(selectIndex).compare("Select") != 0){
			selectIndex++;
		}
	}
	catch(...){
		Query q("INVALID");
		return q;
	}
	
	if (selectIndex != 0){
		// DIVIDE THE STRING INTO TWO PARTS, DIVIDED BY ";"
		char *str = new char[sLength];
		strcpy_s(str, sLength, s.c_str());

		char seps[] = ";";
		char *token = NULL;
		char *nextToken = NULL;

		token = strtok_s(str, seps, &nextToken);

		while (token != NULL)
		{
			string vs(token);
			v.push_back(vs);
			token = strtok_s(NULL, seps, &nextToken);
		}
	
		string synLine = v.at(0);
		synMap = parseSynonyms(synLine);
		Query query = makeQuery(parseQuery(v.at(1)), synMap);
		addQuery(query);
		return query;

	} else {
		synMap.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
		Query query2 = makeQuery(parseQuery(s), synMap);
		addQuery(query2);
		return query2;
	}
}

vector<Query> QueryParser::getQueries(){
	return queries;
}

Query QueryParser::makeQuery(vector<string> v, unordered_map<string, TypeTable::SynType> map){
	Query query(v.at(0));
	query.addSynTable(map);

	for (size_t i = 1; i < v.size(); i++){
		Relationship rel(v.at(i), v.at(i+1), v.at(i+2));
		query.addRelationship(rel);
		i = i+2;
	}

	return query;
}

vector<string> QueryParser::parseQuery(string q){
	vector<string> v;
	int qLength = q.length() + 1;
	char *str = new char[qLength];
	strcpy_s(str, qLength, q.c_str());

	char seps[] = " ,();";
	char *token = NULL;
	char *nextToken = NULL;

	token = strtok_s(str, seps, &nextToken);

	while (token != NULL)
	{
		string vs(token);
		// getting synonym that is selected
		if (vs.compare("Select") == 0){
			token = strtok_s(NULL, seps, &nextToken);
			vs = token;
			v.push_back(vs);
		}

		// getting relationships
		if (vs.compare("Follows") == 0 || vs.compare("Parent") == 0 ||
			vs.compare("Follows*") == 0 || vs.compare("Parent*") == 0){
			v.push_back(vs);
			token = strtok_s(NULL, seps, &nextToken);
			vs = token;
			v.push_back(vs);
			token = strtok_s(NULL, seps, &nextToken);
			vs = token;
			v.push_back(vs);
		}

		token = strtok_s(NULL, seps, &nextToken);
	}
	return v;
}

unordered_map<string, TypeTable::SynType> QueryParser::parseSynonyms(string s)
{
	vector<string> v;
	int sLength = s.length() + 1;
	char * str = new char [sLength];
	strcpy_s(str, sLength, s.c_str());

	char seps[] = " ,;";
	char * token = NULL;
	char * nextToken = NULL;

	token = strtok_s(str, seps, &nextToken);

	while (token != NULL)
	{
		string vs(token);
		v.push_back(vs);
		token = strtok_s(NULL, seps, &nextToken);
	}
	
	unordered_map<string, TypeTable::SynType> map;
	
	for(size_t i = 0; i < v.size(); i++){
		string temp1 = v.at(i);
		i++;
		string temp2 = v.at(i);
		
		if (temp1.compare("assign") == 0){
			map.insert(make_pair(temp2, TypeTable::ASSIGN));
		} else if (temp1.compare("while") == 0) {
			map.insert(make_pair(temp2, TypeTable::WHILE));
		} else if (temp1.compare("stmt") == 0){
			map.insert(make_pair(temp2, TypeTable::STMT));
		}
		else {
			map.insert(make_pair(temp2, TypeTable::IF)); 
			// unsafe, create another type for invalid
		}
	}

	map.insert(make_pair("BOOLEAN", TypeTable::BOOLEAN));
	return map;
}

	void QueryParser::addQuery(Query q){
		queries.push_back(q);
	}

