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

/*! \brief A class that is used to create a queue item.		
 * \ingroup 
 * 
 *	This class is used for creating QueueItem objects which are part of the toposort order in the queue which is used to extract more relationships about the source SIMPLE program.
 *	The components of QueueItem include
 *	- procIndex: The index of the procedure.
 *	- callsProgLine: A list of all program lines on which the procedure with index "procIndex" is called either directly or indirectly.
 * 
 * \see DesignExtractor
 *	
 */

//begin QueueItem class
class QueueItem {
private: 
	int procIndex; 
	vector<int> callsProgLine; 
	
public:
	//! Blank Node Constructor.
	QueueItem();
	//! Constructor 1.
	QueueItem(int, vector<int>); 
	//! Get the procedure index.
	int getProcIndex();
	//! Get the list of program lines on which the procedure with index "procIndex" is called either directly or indirectly.
	vector<int> getCallsProgLine(); 
	//! Used to print out the queueItem in a pretty format. 
	//! For debugging purposes.
	void print();
};	
#endif