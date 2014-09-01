#pragma once

#include "QueueItem.h"

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