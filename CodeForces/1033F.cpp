#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxW=12, mx3W=531441;
int w, n, m, a, c[1<<mxW], p3[mxW], e[mxW];
ll b[1<<mxW], d[mx3W];
string g;
unordered_map<char, int> mp{{'A', 3}, {'O', 1}, {'X', 5}, {'a', 4}, {'o', 6}, {'x', 2}};

ll rec(int i, int a) {
	if(i>=w)
		return d[a];
	ll r=0;
	for(int j=0; j<3; ++j)
		if(e[i]>>j&1)
			r+=rec(i+1, a+j*p3[w-1-i]);
	return r;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> w >> n >> m;
	while(n--) {
		cin >> a;
		++b[a];
	}
	p3[0]=1;
	for(int i=1; i<w; ++i)
		p3[i]=p3[i-1]*3;
	for(int i=0; i<1<<w; ++i)
		for(int j=0; j<w; ++j)
			c[i]+=(i>>j)%2*p3[j];
	for(int i=0; i<1<<w; ++i)
		for(int j=0; j<1<<w; ++j)
			d[c[i]+c[j]]+=b[i]*b[j];
	while(m--) {
		cin >> g;
		for(int i=0; i<w; ++i)
			e[i]=mp[g[i]];
		cout << rec(0, 0) << "\n";
	}
}
