//#include <iostream>
#include <string>
#include <algorithm>
#include "Pair.h"
#include <ctype.h>
#include <set>
#include <stack>

using namespace std;

Pair::Pair(){
}

Pair::Pair(string a1, string a2, string tk1, string tk2){
	ans1=a1;
	ans2=a2;
	token1 = tk1;
	token2 = tk2;
}
