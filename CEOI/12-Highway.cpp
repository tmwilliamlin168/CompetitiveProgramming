#include "office.h"
#include <bits/stdc++.h>
using namespace std;

vector<int> a[2];

int ol(int b) {
	return isOnLine(a[1][0], a[1][0]+1, b);
}

void ans(int b, int c) {
	Answer(a[1][0], a[1][0]+1, b, c);
}

int main() {
	int n=GetN();
	for(int i=1; i+2<=n; i+=3)
		a[isOnLine(i, i+1, i+2)].push_back(i);
	if(a[0].size()>=2) {
		int b[2];
		for(int i=0; i<2; ++i)
			for(b[i]=a[0][i]; ol(b[i]); ++b[i]);
		ans(b[0], b[1]);
	}
	for(int i=1; i+1<a[1].size(); i+=2) {
		if(isOnLine(a[1][0], a[1][i], a[1][i+1]))
			continue;
		int j=ol(a[1][i]);
		ans(a[1][i+j], a[1][i+j]+1);
	}
	if(a[1].size()%2==0&&!ol(a[1].back()))
		ans(a[1].back(), a[1].back()+1);
	if(n%3==1) {
		if(!ol(a[0][0]))
			ans(a[0][0], n);
		else if(!ol(a[0][0]+1))
			ans(a[0][0]+1, n);
		else
			ans(a[0][0]+2, n);
	} else {
		vector<int> b;
		for(int i=0; i<3; ++i)
			if(!ol(a[0][0]+i))
				b.push_back(a[0][0]+i);
		b.push_back(n);
		ans(b[0], b[1]);
	}
}
