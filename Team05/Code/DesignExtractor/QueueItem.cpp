#pragma once

#include "QueueItem.h"

QueueItem::QueueItem() {
	callsProgLine = vector<int>(); 
}

QueueItem::QueueItem(int newProcIndex, vector<int> newCallsProgLine) {
	procIndex = newProcIndex;
	callsProgLine = newCallsProgLine; 
}

vector<int> QueueItem::getCallsProgLine() {
	return callsProgLine; 
}

int QueueItem::getProcIndex() {
	return procIndex; 
}

void QueueItem::print() {
	cout << "(" << procIndex << ", [";
	for(std::vector<int>::size_type i = 0; i != callsProgLine.size(); i++) {
		cout << callsProgLine[i] << ", ";
	}
	cout << "]" << endl; 
}