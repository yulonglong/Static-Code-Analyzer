//@author Ipsita Mohapatra
//QueueItem.h

#pragma once
#ifndef QUEUEITEM_H
#define QUEUEITEM_H

#include <string>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stack>
#include <queue>
#include <vector>

using namespace std;

class QueueItem {
private: 
	int procIndex; 
	vector<int> callsProgLine; 
	
public:
	QueueItem(int, vector<int>); 
	int getProcIndex();
	vector<int> getCallsProgLine(); 
};	
#endif