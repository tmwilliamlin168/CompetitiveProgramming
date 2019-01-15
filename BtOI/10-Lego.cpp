/*
	- dp[layer][places we can place a new block]
	- We can backtrack to find possible combinations in a layer and transition
		- Add blocks in increasing order of x+y so that if we place a block and it is seen in a sideview, it won't be blocked again
		- Useful for bounding the search
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

int n, a[6], b[6], ta[6][6], tb[6][6], mt[25];
unordered_map<int, ll> mp[7];
unordered_map<char, int> c2i{{'.', 0}, {'W', 1}, {'G', 2}, {'B', 3}};
string s;
ll ans;
array<int, 3> p[25];
bool c[6][6];

void dfs(int h, int cp, ll mu, int i=0, int np=0) {
	if(i>=25) {
		for(int j=0; j<6; ++j)
			if(a[j]!=ta[h][j]||b[j]!=tb[h][j])
				return;
		mp[h+1][np]+=mu;
		return;
	}
	dfs(h, cp, mu, i+1, np);
	int x=p[i][1], y=p[i][2], c1=c[x][y], c2=c[x][y+1], c3=c[x+1][y], c4=c[x+1][y+1], a1=a[x], a2=a[x+1], b1=b[y], b2=b[y+1], cn=-1;
	if(cp>>i&1^1||c1||c2||c3||c4)
		return;
	auto d=[&](int x) {
		if(cn!=-1&&cn!=x)
			cn=0;
		else
			cn=x;
	};
	if(!a1)
		d(ta[h][x]);
	if(!a2)
		d(ta[h][x+1]);
	if(!b1)
		d(tb[h][y]);
	if(!b2)
		d(tb[h][y+1]);
	c[x][y]=c[x][y+1]=c[x+1][y]=c[x+1][y+1]=1;
	if(cn>0) {
		if(!a1)
			a[x]=cn;
		if(!a2)
			a[x+1]=cn;
		if(!b1)
			b[y]=cn;
		if(!b2)
			b[y+1]=cn;
		dfs(h, cp, mu, i+1, np|mt[i]);
		a[x]=a1;
		a[x+1]=a2;
		b[y]=b1;
		b[y+1]=b2;
	} else if(cn==-1)
		dfs(h, cp, mu*3, i+1, np|mt[i]);
	c[x][y]=c[x][y+1]=c[x+1][y]=c[x+1][y+1]=0;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for(int i=0; i<n; ++i) {
		cin >> s;
		for(int j=0; j<6; ++j)
			ta[n-1-i][5-j]=c2i[s[j]];
	}
	for(int i=0; i<n; ++i) {
		cin >> s;
		for(int j=0; j<6; ++j)
			tb[n-1-i][j]=c2i[s[j]];
	}
	for(int i=0; i<5; ++i)
		for(int j=0; j<5; ++j)
			p[i*5+j]={i+j, i, j};
	sort(p, p+25);
	for(int i=0; i<25; ++i)
		for(int j=0; j<25; ++j)
			if(max(abs(p[i][1]-p[j][1]), abs(p[i][2]-p[j][2]))<2)
				mt[i]|=1<<j;
	++mp[0][(1<<25)-1];
	for(int i=0; i<n; ++i)
		for(auto it=mp[i].begin(); it!=mp[i].end(); ++it)
			dfs(i, it->first, it->second);
	for(auto it=mp[n].begin(); it!=mp[n].end(); ++it)
		ans+=it->second;
	cout << ans;
}
