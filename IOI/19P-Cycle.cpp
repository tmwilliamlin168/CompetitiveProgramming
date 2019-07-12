#include "cycle.h"
#include <bits/stdc++.h>
using namespace std;

void escape(int n) {
	if(n<3) {
		jump(1);
		return;
	}
	int a=jump(0)?0:n/2;
	for(int i=28; ~i; --i) {
		int l=min(1<<i, n-n/2-1);
		a=jump((a+l)%n)?0:(n-l)%n;
	}
	jump(a);
}
