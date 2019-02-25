#include <bits/stdc++.h>
#include "grader.h"
using namespace std;

bool qry(int a, int b, int c) {
	vector<int> v(a, c);
	while(b--)
		v.push_back(c^1);
	return isSubsequence(v);
}

vector<int> findSequence(int n) {
	int c=0;
	for(int i=1; i<=n; ++i) {
		vector<int> v(i>n/2?n-i+1:i, i>n/2);
		if(qry(i>n/2?n-i+1:i, 0, i>n/2)^i<=n/2)
			break;
		c=i;
	}
	vector<int> ans;
	for(int i=1, j=0; i<=c; ++i) {
		for(; j<n-c; ++j) {
			if(j+c+1-i<=n/2?!qry(j+1, c+1-i, 1):qry(i, n-c-j, 0))
				break;
			ans.push_back(1);
		}
		ans.push_back(0);
	}
	while(ans.size()<n)
		ans.push_back(1);
    return ans;
}
