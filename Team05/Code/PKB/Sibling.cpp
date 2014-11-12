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
	siblingConstantMathOpTable.push_back(placeHolder);
	siblingMathOpConstantTable.push_back(placeHolder);
	siblingVarIndexStmtListTable.push_back(placeHolder);
	siblingStmtListVarIndexTable.push_back(placeHolder); 


	flagStmtNumStmtNumTable.push_back(false);
	flagVarIndexVarIndexTable.push_back(false);
	flagConstantConstantTable.push_back(false);
	flagProcIndexProcIndexTable.push_back(false);
	flagStmtListStmtListTable.push_back(false);

	indexStmtNumStmtNumTable.push_back(-1);
	indexVarIndexVarIndexTable.push_back(-1);
	indexConstantConstantTable.push_back(-1);
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
	siblingMathOpConstantTable.clear();
	siblingMathOpMathOpTable.clear();
	siblingProcIndexProcIndexTable.clear();
	siblingVarIndexStmtListTable.clear();
	siblingStmtListVarIndexTable.clear();
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
	siblingStmtListVarIndexList.clear();
	siblingStmtListStmtListList.clear();
	siblingAllStmtList.clear();

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
void Sibling::setToSiblingConstantMathOp(CONSTVALUE cv1, TypeTable::SynType t2) {
	try{
		int constIndex = constTable->getConstIndex(cv1);
		int typeIndex;
		if(t2==TypeTable::PLUS)
			typeIndex = 1;
		else if(t2==TypeTable::MINUS)
			typeIndex = 2;
		else if(t2==TypeTable::TIMES)
			typeIndex = 3;
		else
			typeIndex = -1;

		if(constIndex != -1 && typeIndex != -1){
			vector<int> placeHolder (1,-1);
			if(constIndex>siblingConstantMathOpTable.size()-1)
				siblingConstantMathOpTable.resize(constIndex+1,placeHolder);
			if(typeIndex>siblingMathOpConstantTable.size()-1)
				siblingMathOpConstantTable.resize(typeIndex+1,placeHolder);
			vector<int> temp = siblingConstantMathOpTable.at(constIndex);
			if(temp.size()==1 && temp.at(0)==-1)
				temp.clear();
			
			temp.push_back(typeIndex);
			siblingConstantMathOpTable[constIndex] = temp;

			vector<VARINDEX> temp1 = siblingMathOpConstantTable.at(typeIndex);
			if(temp1.size()==1 && temp1.at(0)==-1)
				temp1.clear();
			
			temp1.push_back(constIndex);
			siblingMathOpConstantTable[typeIndex] = temp1;

			siblingConstantMathOpList.insert(constIndex);
			siblingMathOpConstantList.insert(typeIndex);
		}
	}catch(...){
	}
}
void Sibling::setToSiblingMathOpMathOp(TypeTable::SynType t1, TypeTable::SynType t2) {
	try{
		int typeIndex1;
		if(t1==TypeTable::PLUS)
			typeIndex1 = 1;
		else if(t1==TypeTable::MINUS)
			typeIndex1 = 2;
		else if(t1==TypeTable::TIMES)
			typeIndex1 = 3;
		else
			typeIndex1 = -1;

		int typeIndex2;
		if(t2==TypeTable::PLUS)
			typeIndex2 = 1;
		else if(t2==TypeTable::MINUS)
			typeIndex2 = 2;
		else if(t2==TypeTable::TIMES)
			typeIndex2 = 3;
		else
			typeIndex2 = -1;

		if(typeIndex1 != -1 && typeIndex2 != -1){
			vector<int> placeHolder (1,-1);
			if(typeIndex1>siblingMathOpMathOpTable.size()-1)
				siblingMathOpMathOpTable.resize(typeIndex1+1,placeHolder);
			if(typeIndex2>siblingMathOpMathOpTable.size()-1)
				siblingMathOpMathOpTable.resize(typeIndex2+1,placeHolder);
			vector<int> temp = siblingMathOpMathOpTable.at(typeIndex1);
			if(temp.size()==1 && temp.at(0)==-1)
				temp.clear();
			
			temp.push_back(typeIndex2);
			siblingMathOpMathOpTable[typeIndex1] = temp;

			vector<int> temp1 = siblingMathOpMathOpTable.at(typeIndex2);
			if(temp1.size()==1 && temp1.at(0)==-1)
				temp1.clear();
			
			temp1.push_back(typeIndex1);
			siblingMathOpMathOpTable[typeIndex2] = temp1;

			siblingMathOpMathOpList.insert(typeIndex1);
			siblingMathOpMathOpList.insert(typeIndex2);
		}
	}catch(...){
	}
}
void Sibling::setToSiblingProcNameProcName(PROCNAME v1, PROCNAME v2) {
	try{
		int procIndex1 = procTable->getProcIndex(v1);
		int procIndex2 = procTable->getProcIndex(v2);
		if(procIndex1 != -1 && procIndex2 != -1){
			if(procIndex1>flagProcIndexProcIndexTable.size()-1)
				flagProcIndexProcIndexTable.resize(procIndex1+1,false);
			if(procIndex2>flagProcIndexProcIndexTable.size()-1)
				flagProcIndexProcIndexTable.resize(procIndex2+1,false);
			if(procIndex1>indexProcIndexProcIndexTable.size()-1)
				indexProcIndexProcIndexTable.resize(procIndex1+1,-1);
			if(procIndex2>indexProcIndexProcIndexTable.size()-1)
				indexProcIndexProcIndexTable.resize(procIndex2+1,-1);

			if(!flagProcIndexProcIndexTable.at(procIndex1) && !flagProcIndexProcIndexTable.at(procIndex2)){
				flagProcIndexProcIndexTable[procIndex1] = true;
				flagProcIndexProcIndexTable[procIndex2] = true;

				int index = siblingProcIndexProcIndexTable.size();
				indexProcIndexProcIndexTable[procIndex1] = index;
				indexProcIndexProcIndexTable[procIndex2] = index;

				vector<STMTNUM> temp;
				temp.push_back(procIndex1);
				temp.push_back(procIndex2);
				siblingProcIndexProcIndexTable.push_back(temp);
			} else if (flagProcIndexProcIndexTable.at(procIndex1) && !flagProcIndexProcIndexTable.at(procIndex2)){
				flagProcIndexProcIndexTable[procIndex2] = true;

				int index = indexProcIndexProcIndexTable.at(procIndex1);
				indexProcIndexProcIndexTable[procIndex2] = index;

				vector<STMTNUM> temp = siblingProcIndexProcIndexTable.at(index);
				temp.push_back(procIndex2);
				siblingProcIndexProcIndexTable[index] = temp;
			} else if (!flagProcIndexProcIndexTable.at(procIndex1) && flagProcIndexProcIndexTable.at(procIndex2)){
				flagProcIndexProcIndexTable[procIndex1] = true;

				int index = indexProcIndexProcIndexTable.at(procIndex2);
				indexProcIndexProcIndexTable[procIndex1] = index;

				vector<STMTNUM> temp = siblingProcIndexProcIndexTable.at(index);
				temp.push_back(procIndex1);
				siblingProcIndexProcIndexTable[index] = temp;
			}
			siblingProcIndexProcIndexList.insert(procIndex1);
			siblingProcIndexProcIndexList.insert(procIndex2);
		}
	}catch(...){
	}
}
void Sibling::setToSiblingVarNameStmtList(VARNAME v1, STMTNUM s2) {
	try{
		int varIndex = varTable->getVarIndex(v1);
		if(varIndex != -1 && s2 != -1){
			vector<int> placeHolder (1,-1);
			if(varIndex>siblingVarIndexStmtListTable.size()-1)
				siblingVarIndexStmtListTable.resize(varIndex+1,placeHolder);
			if(s2>siblingStmtListVarIndexTable.size()-1)
				siblingStmtListVarIndexTable.resize(s2+1,placeHolder);
			vector<CONSTINDEX> temp = siblingVarIndexStmtListTable.at(varIndex);
			if(temp.size()==1 && temp.at(0)==-1)
				temp.clear();
			
			temp.push_back(s2);
			siblingVarIndexStmtListTable[varIndex] = temp;

			vector<VARINDEX> temp1 = siblingStmtListVarIndexTable.at(s2);
			if(temp1.size()==1 && temp1.at(0)==-1)
				temp1.clear();
			
			temp1.push_back(varIndex);
			siblingStmtListVarIndexTable[s2] = temp1;

			siblingVarIndexStmtListList.insert(varIndex);
			siblingStmtListVarIndexList.insert(s2);
		}
	}catch(...){
	}
}
void Sibling::setToSiblingStmtListStmtList(STMTNUM s1, STMTNUM s2) {
	try{
		if(s1>flagStmtListStmtListTable.size()-1)
			flagStmtListStmtListTable.resize(s1+1,false);
		if(s2>flagStmtListStmtListTable.size()-1)
			flagStmtListStmtListTable.resize(s2+1,false);
		if(s1>indexStmtListStmtListTable.size()-1)
			indexStmtListStmtListTable.resize(s1+1,-1);
		if(s2>indexStmtListStmtListTable.size()-1)
			indexStmtListStmtListTable.resize(s2+1,-1);
	
		if(!flagStmtListStmtListTable.at(s1) && !flagStmtListStmtListTable.at(s2)){
			flagStmtListStmtListTable[s1] = true;
			flagStmtListStmtListTable[s2] = true;

			int index = siblingStmtListStmtListTable.size();
			indexStmtListStmtListTable[s1] = index;
			indexStmtListStmtListTable[s2] = index;

			vector<STMTNUM> temp;
			temp.push_back(s1);
			temp.push_back(s2);
			siblingStmtListStmtListTable.push_back(temp);
		} else if (flagStmtListStmtListTable.at(s1) && !flagStmtListStmtListTable.at(s2)){
			flagStmtListStmtListTable[s2] = true;

			int index = indexStmtListStmtListTable.at(s1);
			indexStmtListStmtListTable[s2] = index;

			vector<STMTNUM> temp = siblingStmtListStmtListTable.at(index);
			temp.push_back(s2);
			siblingStmtListStmtListTable[index] = temp;
		} else if (!flagStmtListStmtListTable.at(s1) && flagStmtListStmtListTable.at(s2)){
			flagStmtListStmtListTable[s1] = true;

			int index = indexStmtListStmtListTable.at(s2);
			indexStmtListStmtListTable[s1] = index;

			vector<STMTNUM> temp = siblingStmtListStmtListTable.at(index);
			temp.push_back(s1);
			siblingStmtListStmtListTable[index] = temp;
		}
		siblingStmtListStmtListList.insert(s1);
		siblingStmtListStmtListList.insert(s2);
	}catch(...){
	}
}

void Sibling::setToSiblingAllStmtList(STMTNUM s) {
	try{
		if(s!=-1)
			siblingAllStmtList.insert(s);
	}catch(...){
	}
}



bool Sibling::isSiblingStmtNumStmtNum(STMTNUM s1, STMTNUM s2) {
	try{
		if(s1==s2)
			return false;
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

bool Sibling::isSiblingVarIndexVarIndex(VARINDEX varIndex1, VARINDEX varIndex2) {
	try{
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

bool Sibling::isSiblingVarIndexConstant(VARINDEX varIndex, CONSTINDEX constVarIndex) {
	try{
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

bool Sibling::isSiblingConstantConstant(CONSTINDEX constVarIndex1, CONSTINDEX constVarIndex2) {
	try{
		if(constVarIndex1==constVarIndex2)
			return false;
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

bool Sibling::isSiblingVarIndexMathOp(VARINDEX varIndex, TypeTable::SynType t2) {
	try{
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

bool Sibling::isSiblingConstantMathOp(CONSTINDEX constIndex, TypeTable::SynType t2) {
	try{
		int typeIndex;
		if(t2==TypeTable::PLUS)
			typeIndex = 1;
		else if(t2==TypeTable::MINUS)
			typeIndex = 2;
		else if(t2==TypeTable::TIMES)
			typeIndex = 3;
		else
			typeIndex = -1;
		if(constIndex != -1 && typeIndex != -1){
			vector<int> temp = siblingConstantMathOpTable.at(constIndex);
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

bool Sibling::isSiblingMathOpMathOp(TypeTable::SynType t1, TypeTable::SynType t2) {
	try{
		int typeIndex1;
		if(t1==TypeTable::PLUS)
			typeIndex1 = 1;
		else if(t1==TypeTable::MINUS)
			typeIndex1 = 2;
		else if(t1==TypeTable::TIMES)
			typeIndex1 = 3;
		else
			typeIndex1 = -1;

		int typeIndex2;
		if(t2==TypeTable::PLUS)
			typeIndex2 = 1;
		else if(t2==TypeTable::MINUS)
			typeIndex2 = 2;
		else if(t2==TypeTable::TIMES)
			typeIndex2 = 3;
		else
			typeIndex2 = -1;

		if(typeIndex1 != -1 && typeIndex2 != -1){
			vector<int> temp = siblingMathOpMathOpTable.at(typeIndex1);
			for(vector<int>::iterator it = temp.begin(); it != temp.end();it++){
				if(*it==typeIndex2)
					return true;
			}
		}
	} catch(...){
		return false;
	}
	return false;
}

bool Sibling::isSiblingProcIndexProcIndex(PROCINDEX procIndex1, PROCINDEX procIndex2) {
	try{
		if(procIndex1 != -1 && procIndex2 != -1){
			if(procIndex1==procIndex2)
				return false;
			if(!flagProcIndexProcIndexTable.at(procIndex1) || !flagProcIndexProcIndexTable.at(procIndex2))
				return false;
			if(indexProcIndexProcIndexTable.at(procIndex1) == -1 || indexProcIndexProcIndexTable.at(procIndex2) == -1)
				return false;
			if(indexProcIndexProcIndexTable.at(procIndex1) == indexProcIndexProcIndexTable.at(procIndex2))
				return true;
		}
	} catch(...){
	}
	return false;
}

bool Sibling::isSiblingVarIndexStmtList(VARINDEX varIndex, STMTNUM s2) {
	try{
		if(varIndex != -1 && s2 != -1){
			vector<STMTNUM> temp = siblingVarIndexStmtListTable.at(varIndex);
			for(vector<CONSTINDEX>::iterator it = temp.begin(); it != temp.end();it++){
				if(*it==s2)
					return true;
			}
		}
	} catch(...){
		return false;
	}
	return false;
}

bool Sibling::isSiblingStmtListStmtList(STMTNUM s1, STMTNUM s2) {
	try{
		if(s1==s2)
			return false;
		if(!flagStmtListStmtListTable.at(s1) || !flagStmtListStmtListTable.at(s2))
			return false;
		if(indexStmtListStmtListTable.at(s1) == -1 || indexStmtListStmtListTable.at(s2) == -1)
			return false;
		if(indexStmtListStmtListTable.at(s1) == indexStmtListStmtListTable.at(s2))
			return true;
	} catch(...){
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

set<CONSTINDEX> Sibling::getSiblingConstantWithConstant(CONSTINDEX cv){
	set<CONSTINDEX> ans;
	try{
		int index = indexConstantConstantTable.at(cv);
		vector<CONSTINDEX> temp = siblingConstantConstantTable.at(index);
		for (vector<CONSTINDEX>::iterator it = temp.begin(); it != temp.end(); it++){
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

set<CONSTINDEX> Sibling::getSiblingConstantWithMathOp(TypeTable::SynType t){
	set<CONSTINDEX> ans;
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
			vector<CONSTINDEX> temp = siblingMathOpConstantTable.at(typeIndex);
			for (vector<CONSTINDEX>::iterator it = temp.begin(); it != temp.end(); it++){
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

set<TypeTable::SynType> Sibling::getSiblingMathOpWithConstant(CONSTINDEX cv){
	set<TypeTable::SynType> ans;
	try{
		vector<int> temp = siblingConstantMathOpTable.at(cv);
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

set<TypeTable::SynType> Sibling::getSiblingMathOpWithMathOp(TypeTable::SynType t){
	set<TypeTable::SynType> ans;
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
			vector<int> temp = siblingMathOpMathOpTable.at(typeIndex);
			for (vector<int>::iterator it = temp.begin(); it != temp.end(); it++){
				if(*it==1)
					ans.insert(TypeTable::PLUS);
				else if(*it==2)
					ans.insert(TypeTable::MINUS);
				else if(*it==3)
					ans.insert(TypeTable::TIMES);
			}
			return ans;
		}
	} catch (...){
		ans.clear();
	}
	return ans;
}

set<PROCINDEX> Sibling::getSiblingProcIndexWithProcIndex(PROCINDEX p){
	set<PROCINDEX> ans;
	try{
		int index = indexProcIndexProcIndexTable.at(p);
		vector<STMTNUM> temp = siblingProcIndexProcIndexTable.at(index);
		for (vector<STMTNUM>::iterator it = temp.begin(); it != temp.end(); it++){
			if(*it!=p)
				ans.insert(*it);
		}
		return ans;
	} catch (...){
		ans.clear();
	}
	return ans;
}

set<VARINDEX> Sibling::getSiblingVarIndexWithStmtList(STMTNUM s){
	set<VARINDEX> ans;
	try{
		vector<VARINDEX> temp = siblingStmtListVarIndexTable.at(s);
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

set<STMTNUM> Sibling::getSiblingStmtListWithVarIndex(VARINDEX v){
	set<STMTNUM> ans;
	try{
		vector<STMTNUM> temp = siblingVarIndexStmtListTable.at(v);
		for (vector<STMTNUM>::iterator it = temp.begin(); it != temp.end(); it++){
			if(*it!=-1)
				ans.insert(*it);
		}
		return ans;
	} catch (...){
		ans.clear();
	}
	return ans;
}

set<STMTNUM> Sibling::getSiblingStmtListWithStmtList(STMTNUM s){
	set<STMTNUM> ans;
	try{
		int index = indexStmtListStmtListTable.at(s);
		vector<STMTNUM> temp = siblingStmtListStmtListTable.at(index);
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

set<CONSTINDEX> Sibling::getAllSiblingConstantWithMathOp(){
	return siblingConstantMathOpList;
}

set<TypeTable::SynType> Sibling::getAllSiblingMathOpWithConstant(){
	set<TypeTable::SynType> ans;
	for(set<int>::iterator it= siblingMathOpConstantList.begin(); it!=siblingMathOpConstantList.end();it++){
		if(*it==1)
			ans.insert(TypeTable::PLUS);
		else if(*it==2)
			ans.insert(TypeTable::MINUS);
		else if(*it==3)
			ans.insert(TypeTable::TIMES);
	}
	return ans;
}

set<PROCINDEX> Sibling::getAllSiblingProcIndexWithProcIndex(){
	return siblingProcIndexProcIndexList;
}

set<TypeTable::SynType> Sibling::getAllSiblingMathOpWithMathOp(){
	set<TypeTable::SynType> ans;
	for(set<int>::iterator it= siblingMathOpMathOpList.begin(); it!=siblingMathOpMathOpList.end();it++){
		if(*it==1)
			ans.insert(TypeTable::PLUS);
		else if(*it==2)
			ans.insert(TypeTable::MINUS);
		else if(*it==3)
			ans.insert(TypeTable::TIMES);
	}
	return ans;
}

set<VARINDEX> Sibling::getAllSiblingVarIndexWithStmtList(){
	return siblingVarIndexStmtListList;
}

set<VARINDEX> Sibling::getAllSiblingStmtListWithVarIndex(){
	return siblingStmtListVarIndexList;
}

set<STMTNUM> Sibling::getAllSiblingStmtListWithStmtList(){
	return siblingStmtListStmtListList;
}

set<STMTNUM> Sibling::getAllStmtList(){
	return siblingAllStmtList;
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