#pragma once
#pragma warning( disable : 4018)
#pragma warning( disable : 4244)

#include "Sibling.h"

bool Sibling::instanceFlag=false;
Sibling* Sibling::sibling=NULL;

// constructor
Sibling::Sibling(VarTable *vt,ProcTable *pt, ConstTable *ct, TypeTable *tt) {
	vector<int> placeHolder (1,-1);

	siblingVarIndexConstantTable.push_back(placeHolder);
	siblingConstantVarIndexTable.push_back(placeHolder);
	siblingVarIndexMathOpTable.push_back(placeHolder);
	siblingMathOpVarIndexTable.push_back(placeHolder);

	flagStmtNumStmtNumTable.push_back(false);
	flagVarIndexVarIndexTable.push_back(false);
	flagConstantConstantTable.push_back(false);
	flagMathOpMathOpTable.push_back(false);
	flagProcIndexProcIndexTable.push_back(false);
	flagStmtListStmtListTable.push_back(false);

	indexStmtNumStmtNumTable.push_back(-1);
	indexVarIndexVarIndexTable.push_back(-1);
	indexConstantConstantTable.push_back(-1);
	indexMathOpMathOpTable.push_back(-1);
	indexProcIndexProcIndexTable.push_back(-1);
	indexStmtListStmtListTable.push_back(-1);

	varTable = vt;
	procTable = pt;
	constTable = ct;
	typeTable = tt;
}

Sibling::~Sibling() {
	siblingStmtNumStmtNumTable.clear();
	siblingVarIndexVarIndexTable.clear();
	siblingVarIndexConstantTable.clear();
	siblingConstantVarIndexTable.clear();
	siblingConstantConstantTable.clear();
	siblingVarIndexMathOpTable.clear();
	siblingMathOpVarIndexTable.clear();
	siblingConstantMathOpTable.clear();
	siblingMathOpMathOpTable.clear();
	siblingProcIndexProcIndexTable.clear();
	siblingVarIndexStmtListTable.clear();
	siblingStmtListStmtListTable.clear();

	siblingStmtNumStmtNumList.clear();
	siblingVarIndexVarIndexList.clear();
	siblingVarIndexConstantList.clear();
	siblingConstantConstantList.clear();
	siblingVarIndexMathOpList.clear();
	siblingConstantMathOpList.clear();
	siblingMathOpMathOpList.clear();
	siblingProcIndexProcIndexList.clear();
	siblingVarIndexStmtListList.clear();
	siblingStmtListStmtListList.clear();

	instanceFlag=false;
}

Sibling* Sibling::getInstance(VarTable *vt,ProcTable *pt, ConstTable *ct, TypeTable *tt){
	if(!instanceFlag)
    {
        sibling = new Sibling(vt,pt,ct,tt);
        instanceFlag = true;
        return sibling;
    }
    else
    {
        return sibling;
    }
}

void Sibling::setToSiblingStmtNumStmtNum(STMTNUM s1, STMTNUM s2) {
	try{
		if(s1>flagStmtNumStmtNumTable.size()-1)
			flagStmtNumStmtNumTable.resize(s1+1,false);
		if(s2>flagStmtNumStmtNumTable.size()-1)
			flagStmtNumStmtNumTable.resize(s2+1,false);
		if(s1>indexStmtNumStmtNumTable.size()-1)
			indexStmtNumStmtNumTable.resize(s1+1,-1);
		if(s2>indexStmtNumStmtNumTable.size()-1)
			indexStmtNumStmtNumTable.resize(s2+1,-1);
	
		if(!flagStmtNumStmtNumTable.at(s1) && !flagStmtNumStmtNumTable.at(s2)){
			flagStmtNumStmtNumTable[s1] = true;
			flagStmtNumStmtNumTable[s2] = true;

			int index = siblingStmtNumStmtNumTable.size();
			indexStmtNumStmtNumTable[s1] = index;
			indexStmtNumStmtNumTable[s2] = index;

			vector<STMTNUM> temp;
			temp.push_back(s1);
			temp.push_back(s2);
			siblingStmtNumStmtNumTable.push_back(temp);
		} else if (flagStmtNumStmtNumTable.at(s1) && !flagStmtNumStmtNumTable.at(s2)){
			flagStmtNumStmtNumTable[s2] = true;

			int index = indexStmtNumStmtNumTable.at(s1);
			indexStmtNumStmtNumTable[s2] = index;

			vector<STMTNUM> temp = siblingStmtNumStmtNumTable.at(index);
			temp.push_back(s2);
			siblingStmtNumStmtNumTable[index] = temp;
		} else if (!flagStmtNumStmtNumTable.at(s1) && flagStmtNumStmtNumTable.at(s2)){
			flagStmtNumStmtNumTable[s1] = true;

			int index = indexStmtNumStmtNumTable.at(s2);
			indexStmtNumStmtNumTable[s1] = index;

			vector<STMTNUM> temp = siblingStmtNumStmtNumTable.at(index);
			temp.push_back(s1);
			siblingStmtNumStmtNumTable[index] = temp;
		}
		siblingStmtNumStmtNumList.insert(s1);
		siblingStmtNumStmtNumList.insert(s2);
	}catch(...){
	}
}

void Sibling::setToSiblingVarNameVarName(VARNAME v1, VARNAME v2) {
	try{
		int varIndex1 = varTable->getVarIndex(v1);
		int varIndex2 = varTable->getVarIndex(v2);
		if(varIndex1 != -1 && varIndex2 != -1){
			if(varIndex1>flagVarIndexVarIndexTable.size()-1)
				flagVarIndexVarIndexTable.resize(varIndex1+1,false);
			if(varIndex2>flagVarIndexVarIndexTable.size()-1)
				flagVarIndexVarIndexTable.resize(varIndex2+1,false);
			if(varIndex1>indexVarIndexVarIndexTable.size()-1)
				indexVarIndexVarIndexTable.resize(varIndex1+1,-1);
			if(varIndex2>indexVarIndexVarIndexTable.size()-1)
				indexVarIndexVarIndexTable.resize(varIndex2+1,-1);

			if(!flagVarIndexVarIndexTable.at(varIndex1) && !flagVarIndexVarIndexTable.at(varIndex2)){
				flagVarIndexVarIndexTable[varIndex1] = true;
				flagVarIndexVarIndexTable[varIndex2] = true;

				int index = siblingVarIndexVarIndexTable.size();
				indexVarIndexVarIndexTable[varIndex1] = index;
				indexVarIndexVarIndexTable[varIndex2] = index;

				vector<STMTNUM> temp;
				temp.push_back(varIndex1);
				temp.push_back(varIndex2);
				siblingVarIndexVarIndexTable.push_back(temp);
			} else if (flagVarIndexVarIndexTable.at(varIndex1) && !flagVarIndexVarIndexTable.at(varIndex2)){
				flagVarIndexVarIndexTable[varIndex2] = true;

				int index = indexVarIndexVarIndexTable.at(varIndex1);
				indexVarIndexVarIndexTable[varIndex2] = index;

				vector<STMTNUM> temp = siblingVarIndexVarIndexTable.at(index);
				temp.push_back(varIndex2);
				siblingVarIndexVarIndexTable[index] = temp;
			} else if (!flagVarIndexVarIndexTable.at(varIndex1) && flagVarIndexVarIndexTable.at(varIndex2)){
				flagVarIndexVarIndexTable[varIndex1] = true;

				int index = indexVarIndexVarIndexTable.at(varIndex2);
				indexVarIndexVarIndexTable[varIndex1] = index;

				vector<STMTNUM> temp = siblingVarIndexVarIndexTable.at(index);
				temp.push_back(varIndex1);
				siblingVarIndexVarIndexTable[index] = temp;
			}
			siblingVarIndexVarIndexList.insert(varIndex1);
			siblingVarIndexVarIndexList.insert(varIndex2);
		}
	}catch(...){
	}
}

void Sibling::setToSiblingVarNameConstant(VARNAME v1, CONSTVALUE cv2) {
	try{
		int varIndex = varTable->getVarIndex(v1);
		int constVarIndex = constTable->getConstIndex(cv2);
		if(varIndex != -1 && constVarIndex != -1){
			vector<int> placeHolder (1,-1);
			if(varIndex>siblingVarIndexConstantTable.size()-1)
				siblingVarIndexConstantTable.resize(varIndex+1,placeHolder);
			if(constVarIndex>siblingConstantVarIndexTable.size()-1)
				siblingConstantVarIndexTable.resize(constVarIndex+1,placeHolder);
			vector<CONSTINDEX> temp = siblingVarIndexConstantTable.at(varIndex);
			if(temp.size()==1 && temp.at(0)==-1)
				temp.clear();
			
			temp.push_back(constVarIndex);
			siblingVarIndexConstantTable[varIndex] = temp;

			vector<VARINDEX> temp1 = siblingConstantVarIndexTable.at(constVarIndex);
			if(temp1.size()==1 && temp1.at(0)==-1)
				temp1.clear();
			
			temp1.push_back(varIndex);
			siblingConstantVarIndexTable[constVarIndex] = temp1;

			siblingVarIndexConstantList.insert(varIndex);
			siblingConstantVarIndexList.insert(constVarIndex);
		}
	}catch(...){
	}
}

void Sibling::setToSiblingConstantConstant(CONSTVALUE cv1, CONSTVALUE cv2) {
	try{
		int constVarIndex1 = constTable->getConstIndex(cv1);
		int constVarIndex2 = constTable->getConstIndex(cv2);
		if(constVarIndex1 != -1 && constVarIndex2 != -1){
			if(constVarIndex1>flagConstantConstantTable.size()-1)
				flagConstantConstantTable.resize(constVarIndex1+1,false);
			if(constVarIndex2>flagConstantConstantTable.size()-1)
				flagConstantConstantTable.resize(constVarIndex2+1,false);
			if(constVarIndex1>indexConstantConstantTable.size()-1)
				indexConstantConstantTable.resize(constVarIndex1+1,-1);
			if(constVarIndex2>indexConstantConstantTable.size()-1)
				indexConstantConstantTable.resize(constVarIndex2+1,-1);

			if(!flagConstantConstantTable.at(constVarIndex1) && !flagConstantConstantTable.at(constVarIndex2)){
				flagConstantConstantTable[constVarIndex1] = true;
				flagConstantConstantTable[constVarIndex2] = true;

				int index = siblingConstantConstantTable.size();
				indexConstantConstantTable[constVarIndex1] = index;
				indexConstantConstantTable[constVarIndex2] = index;

				vector<STMTNUM> temp;
				temp.push_back(constVarIndex1);
				temp.push_back(constVarIndex2);
				siblingConstantConstantTable.push_back(temp);
			} else if (flagConstantConstantTable.at(constVarIndex1) && !flagConstantConstantTable.at(constVarIndex2)){
				flagConstantConstantTable[constVarIndex2] = true;

				int index = indexConstantConstantTable.at(constVarIndex1);
				indexConstantConstantTable[constVarIndex2] = index;

				vector<STMTNUM> temp = siblingConstantConstantTable.at(index);
				temp.push_back(constVarIndex2);
				siblingConstantConstantTable[index] = temp;
			} else if (!flagConstantConstantTable.at(constVarIndex1) && flagConstantConstantTable.at(constVarIndex2)){
				flagConstantConstantTable[constVarIndex1] = true;

				int index = indexConstantConstantTable.at(constVarIndex2);
				indexConstantConstantTable[constVarIndex1] = index;

				vector<STMTNUM> temp = siblingConstantConstantTable.at(index);
				temp.push_back(constVarIndex1);
				siblingConstantConstantTable[index] = temp;
			}
			siblingConstantConstantList.insert(constVarIndex1);
			siblingConstantConstantList.insert(constVarIndex2);
		}
	}catch(...){
	}
}

void Sibling::setToSiblingVarNameMathOp(VARNAME v1, TypeTable::SynType t2) {
	try{
		int varIndex = varTable->getVarIndex(v1);
		int typeIndex;
		if(t2==TypeTable::PLUS)
			typeIndex = 1;
		else if(t2==TypeTable::MINUS)
			typeIndex = 2;
		else if(t2==TypeTable::TIMES)
			typeIndex = 3;
		else
			typeIndex = -1;
		

		if(varIndex != -1 && typeIndex != -1){
			vector<int> placeHolder (1,-1);
			if(varIndex>siblingVarIndexMathOpTable.size()-1)
				siblingVarIndexMathOpTable.resize(varIndex+1,placeHolder);
			if(typeIndex>siblingMathOpVarIndexTable.size()-1)
				siblingMathOpVarIndexTable.resize(typeIndex+1,placeHolder);
			vector<int> temp = siblingVarIndexMathOpTable.at(varIndex);
			if(temp.size()==1 && temp.at(0)==-1)
				temp.clear();
			
			temp.push_back(typeIndex);
			siblingVarIndexMathOpTable[varIndex] = temp;

			vector<VARINDEX> temp1 = siblingMathOpVarIndexTable.at(typeIndex);
			if(temp1.size()==1 && temp1.at(0)==-1)
				temp1.clear();
			
			temp1.push_back(varIndex);
			siblingMathOpVarIndexTable[typeIndex] = temp1;

			siblingVarIndexMathOpList.insert(varIndex);
			siblingMathOpVarIndexList.insert(typeIndex);
		}
	}catch(...){
	}
}















bool Sibling::isSiblingStmtNumStmtNum(STMTNUM s1, STMTNUM s2) {
	try{
		if(!flagStmtNumStmtNumTable.at(s1) || !flagStmtNumStmtNumTable.at(s2))
			return false;
		if(indexStmtNumStmtNumTable.at(s1) == -1 || indexStmtNumStmtNumTable.at(s2) == -1)
			return false;
		if(indexStmtNumStmtNumTable.at(s1) == indexStmtNumStmtNumTable.at(s2))
			return true;
	} catch(...){
	}
	return false;
}

bool Sibling::isSiblingVarNameVarName(VARNAME v1, VARNAME v2) {
	try{
		int varIndex1 = varTable->getVarIndex(v1);
		int varIndex2 = varTable->getVarIndex(v2);
		if(varIndex1 != -1 && varIndex2 != -1){
			if(!flagVarIndexVarIndexTable.at(varIndex1) || !flagVarIndexVarIndexTable.at(varIndex2))
				return false;
			if(indexVarIndexVarIndexTable.at(varIndex1) == -1 || indexVarIndexVarIndexTable.at(varIndex2) == -1)
				return false;
			if(indexVarIndexVarIndexTable.at(varIndex1) == indexVarIndexVarIndexTable.at(varIndex2))
				return true;
		}
	} catch(...){
	}
	return false;
}

bool Sibling::isSiblingVarNameConstant(VARNAME v1, CONSTVALUE cv2) {
	try{
		int varIndex = varTable->getVarIndex(v1);
		int constVarIndex = constTable->getConstIndex(cv2);
		if(varIndex != -1 && constVarIndex != -1){
			vector<CONSTINDEX> temp = siblingVarIndexConstantTable.at(varIndex);
			for(vector<CONSTINDEX>::iterator it = temp.begin(); it != temp.end();it++){
				if(*it==constVarIndex)
					return true;
			}
		}
	} catch(...){
		return false;
	}
	return false;
}

bool Sibling::isSiblingConstantConstant(CONSTVALUE cv1, CONSTVALUE cv2) {
	try{
		int constVarIndex1 = constTable->getConstIndex(cv1);
		int constVarIndex2 = constTable->getConstIndex(cv2);
		if(!flagConstantConstantTable.at(constVarIndex1) || !flagConstantConstantTable.at(constVarIndex2))
			return false;
		if(indexConstantConstantTable.at(constVarIndex1) == -1 || indexConstantConstantTable.at(constVarIndex2) == -1)
			return false;
		if(indexConstantConstantTable.at(constVarIndex1) == indexConstantConstantTable.at(constVarIndex2))
			return true;
	} catch(...){
	}
	return false;
}

bool Sibling::isSiblingVarNameMathOp(VARNAME v1, TypeTable::SynType t2) {
	try{
		int varIndex = varTable->getVarIndex(v1);
		int typeIndex;
		if(t2==TypeTable::PLUS)
			typeIndex = 1;
		else if(t2==TypeTable::MINUS)
			typeIndex = 2;
		else if(t2==TypeTable::TIMES)
			typeIndex = 3;
		else
			typeIndex = -1;
		if(varIndex != -1 && typeIndex != -1){
			vector<int> temp = siblingVarIndexMathOpTable.at(varIndex);
			for(vector<int>::iterator it = temp.begin(); it != temp.end();it++){
				if(*it==typeIndex)
					return true;
			}
		}
	} catch(...){
		return false;
	}
	return false;
}





set<STMTNUM> Sibling::getSiblingStmtNumWithStmtNum(STMTNUM s){
	set<STMTNUM> ans;
	try{
		int index = indexStmtNumStmtNumTable.at(s);
		vector<STMTNUM> temp = siblingStmtNumStmtNumTable.at(index);
		for (vector<STMTNUM>::iterator it = temp.begin(); it != temp.end(); it++){
			if(*it!=s)
				ans.insert(*it);
		}
		return ans;
	} catch (...){
		ans.clear();
	}
	return ans;
}

set<VARINDEX> Sibling::getSiblingVarIndexWithVarIndex(VARINDEX v){
	set<VARINDEX> ans;
	try{
		int index = indexVarIndexVarIndexTable.at(v);
		vector<STMTNUM> temp = siblingVarIndexVarIndexTable.at(index);
		for (vector<STMTNUM>::iterator it = temp.begin(); it != temp.end(); it++){
			if(*it!=v)
				ans.insert(*it);
		}
		return ans;
	} catch (...){
		ans.clear();
	}
	return ans;
}

set<VARINDEX> Sibling::getSiblingVarIndexWithConstant(CONSTINDEX cv){
	set<VARINDEX> ans;
	try{
		vector<VARINDEX> temp = siblingConstantVarIndexTable.at(cv);
		for (vector<VARINDEX>::iterator it = temp.begin(); it != temp.end(); it++){
			if(*it!=-1)
				ans.insert(*it);
		}
		return ans;
	} catch (...){
		ans.clear();
	}
	return ans;
}

set<CONSTINDEX> Sibling::getSiblingConstantWithVarIndex(VARINDEX v){
	set<CONSTINDEX> ans;
	try{
		vector<CONSTINDEX> temp = siblingVarIndexConstantTable.at(v);
		for (vector<VARINDEX>::iterator it = temp.begin(); it != temp.end(); it++){
			if(*it!=-1)
				ans.insert(*it);
		}
		return ans;
	} catch (...){
		ans.clear();
	}
	return ans;
}

set<CONSTINDEX> Sibling::getSiblingConstantWithConstant(CONSTINDEX s){
	set<CONSTINDEX> ans;
	try{
		int index = indexConstantConstantTable.at(s);
		vector<CONSTINDEX> temp = siblingConstantConstantTable.at(index);
		for (vector<CONSTINDEX>::iterator it = temp.begin(); it != temp.end(); it++){
			if(*it!=s)
				ans.insert(*it);
		}
		return ans;
	} catch (...){
		ans.clear();
	}
	return ans;
}

set<VARINDEX> Sibling::getSiblingVarIndexWithMathOp(TypeTable::SynType t){
	set<VARINDEX> ans;
	int typeIndex;
	if(t==TypeTable::PLUS)
		typeIndex = 1;
	else if(t==TypeTable::MINUS)
		typeIndex = 2;
	else if(t==TypeTable::TIMES)
		typeIndex = 3;
	else
		typeIndex = -1;
	try{
		if(typeIndex!=-1){
			vector<VARINDEX> temp = siblingMathOpVarIndexTable.at(typeIndex);
			for (vector<VARINDEX>::iterator it = temp.begin(); it != temp.end(); it++){
				if(*it!=-1)
					ans.insert(*it);
			}
			return ans;
		}
	} catch (...){
		ans.clear();
	}
	return ans;
}

set<TypeTable::SynType> Sibling::getSiblingMathOpWithVarIndex(VARINDEX v){
	set<TypeTable::SynType> ans;
	try{
		vector<int> temp = siblingVarIndexMathOpTable.at(v);
		for (vector<int>::iterator it = temp.begin(); it != temp.end(); it++){
			if(*it!=-1){
				if(*it==1)
					ans.insert(TypeTable::PLUS);
				else if(*it==2)
					ans.insert(TypeTable::MINUS);
				else if(*it==3)
					ans.insert(TypeTable::TIMES);
			}
		}
		return ans;
	} catch (...){
		ans.clear();
	}
	return ans;
}











set<STMTNUM> Sibling::getAllSiblingStmtNumWithStmtNum(){
	return siblingStmtNumStmtNumList;
}

set<VARINDEX> Sibling::getAllSiblingVarIndexWithVarIndex(){
	return siblingVarIndexVarIndexList;
}

set<VARINDEX> Sibling::getAllSiblingVarIndexWithConstant(){
	return siblingVarIndexConstantList;
}

set<CONSTINDEX> Sibling::getAllSiblingConstantWithVarIndex(){
	return siblingConstantVarIndexList;
}

set<CONSTINDEX> Sibling::getAllSiblingConstantWithConstant(){
	return siblingConstantConstantList;
}

set<VARINDEX> Sibling::getAllSiblingVarIndexWithMathOp(){
	return siblingVarIndexMathOpList;
}

set<TypeTable::SynType> Sibling::getAllSiblingMathOpWithVarIndex(){
	set<TypeTable::SynType> ans;
	int typeIndex;
	for(set<int>::iterator it= siblingMathOpVarIndexList.begin(); it!=siblingMathOpVarIndexList.end();it++){
		if(*it==1)
			ans.insert(TypeTable::PLUS);
		else if(*it==2)
			ans.insert(TypeTable::MINUS);
		else if(*it==3)
			ans.insert(TypeTable::TIMES);
	}
	return ans;
}





void Sibling::printSiblingTable() {
	cout<< "Sibling Table" << endl;
	for (vector<vector<STMTNUM>>::iterator it = siblingStmtNumStmtNumTable.begin(); it != siblingStmtNumStmtNumTable.end(); it++) {
		if(it->size()!=0){
			cout<< "Set of sibling = ";
			vector<STMTNUM> temp = *it; 
			for (vector<STMTNUM>::iterator iter = temp.begin(); iter != temp.end(); iter++){
				cout<< *iter<< ",";
			}
			cout<<endl;
		}
	}
}