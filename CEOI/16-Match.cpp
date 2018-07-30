/*
	- https://codeforces.com/blog/entry/46065?#comment-306472
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5;
string s, a;
int n, st[mxN+1], c[mxN+1][26], p[mxN+1], ts=1;
vector<int> occ[mxN+1];

inline int gc(int i, int j) {
	if(!c[i][j]) {
		c[i][j]=ts++;
		p[c[i][j]]=i;
	}
	return c[i][j];
}

void rec(int l, int r) {
	if(l>=r)
		return;
	int m=*--upper_bound(occ[st[l+1]].begin(), occ[st[l+1]].end(), r-1);
	a[l]='(';
	a[m]=')';
	rec(l+1, m);
	rec(m+1, r);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> s;
	n=s.size();
	occ[0].push_back(0);
	for(int i=0, j=0; i<n; ++i) {
		if(j&&s[occ[p[j]].back()]==s[i])
			j=p[j];
		else
			j=gc(j, s[i]-'a');
		st[i+1]=j;
		occ[j].push_back(i+1);
	}
	if(occ[0].back()!=n) {
		cout << -1;
		return 0;
	}
	a.resize(n);
	rec(0, n);
	cout << a;
}
