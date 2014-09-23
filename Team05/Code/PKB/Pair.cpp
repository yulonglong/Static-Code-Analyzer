#include <iostream>
#include <string>
#include <algorithm>
#include "Pair.h"
#include <ctype.h>
#include <set>
#include <stack>

using namespace std;

Pair::Pair(){
}

Pair::Pair(int a1, int a2){
	ans1=a1;
	ans2=a2;
}


bool Pair::operator< (const Pair &p1) const{

	return p1.ans1!=ans1 || p1.ans2!=ans2 ;
}

bool Pair::operator> (const Pair &p1) const{

	return p1.ans1!=ans1 || p1.ans2!=ans2 ;
}
