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

Pair::Pair(int a1, int a2, string tk1, string tk2){
	ans1=a1;
	ans2=a2;
	token1 = tk1;
	token2 = tk2;
}


bool Pair::operator< (const Pair &p1) const{

	return p1.ans1!=ans1 || p1.ans2!=ans2 || p1.token1!=token1 || p1.token2!=token2;
}

bool Pair::operator> (const Pair &p1) const{

	return p1.ans1!=ans1 || p1.ans2!=ans2 || p1.token1!=token1 || p1.token2!=token2;
}
