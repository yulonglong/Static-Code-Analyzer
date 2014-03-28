// Preconditions:
// READ HEADER FILE

#include "QueryParser.h"


QueryParser::QueryParser(){

}

Query QueryParser::parse(string s){
	vector<string> v;
	int sLength = s.length() + 1;
	char *str = new char[sLength];
	strcpy_s(str, sLength, s.c_str());

	char seps[] = ";";
	char *token = NULL;
	char *nextToken = NULL;

	token = strtok_s(str, seps, &nextToken);

	while (token != NULL)
	{
		string vs(token);
		cout << vs << endl;
		v.push_back(vs);
		token = strtok_s(NULL, seps, &nextToken);
	}
	
	string synLine = v.at(0);
	synMap = parseSynonyms(synLine);
	Query query = makeQuery(parseQuery(v.at(1)), synMap);
	addQuery(query);
	return query;
}

vector<Query> QueryParser::getQueries(){
	return queries;
}

Query QueryParser::makeQuery(vector<string> v, unordered_map<string, Query::SType> map){
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
		if (vs.compare("select") == 0){
			token = strtok_s(NULL, seps, &nextToken);
			vs = token;
			v.push_back(vs);
		}

		// getting relationships
		if (vs.compare("FOLLOWS") == 0 || vs.compare("PARENT") == 0 ||
			vs.compare("FOLLOWSTAR") == 0 || vs.compare("PARENTSTAR") == 0){
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

unordered_map<string, Query::SType> QueryParser::parseSynonyms(string s)
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
	
	unordered_map<string, Query::SType> map;
	
	for(size_t i = 0; i < v.size(); i++){
		string temp1 = v.at(i);
		i++;
		string temp2 = v.at(i);
		
		if (temp1.compare("assign") == 0){
			map.insert(make_pair(temp2, Query::ASSIGN));
		} else if (temp1.compare("while") == 0) {
			map.insert(make_pair(temp2, Query::WHILE));
		} else {
			map.insert(make_pair(temp2, Query::IF)); 
			// unsafe, create another type for invalid
		}
	}

	return map;
}

	void QueryParser::addQuery(Query q){
		queries.push_back(q);
	}

