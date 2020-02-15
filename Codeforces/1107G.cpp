#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=3e5;
int n, x, p[mxN];
ll c[mxN+1], d[mxN], ans, ms[mxN], mp[mxN], ts[mxN];
array<ll, 2> e[mxN];

int find(int x) {
	return x==p[x]?x:(p[x]=find(p[x]));
}

void join(int x, int y, ll d) {
	x=find(x);
	y=find(y);
	ans=max(ms[x]+mp[y]+d, ans);
	p[y]=x;
	ms[x]=max(ms[y], ts[y]+ms[x]);
	mp[x]=max(mp[x], ts[x]+mp[y]);
	ts[x]+=ts[y];
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> x;
	iota(p, p+n, 0);
	for(int i=0; i<n; ++i) {
		cin >> d[i] >> c[i];
		ms[i]=mp[i]=ts[i]=c[i]=x-c[i];
		ans=max(c[i], ans);
	}
	for(int i=0; i<n; ++i)
		e[i]={d[i+1]-d[i], i};
	sort(e, e+n-1);
	for(int i=0; i<n-1; ++i)
		join(e[i][1], e[i][1]+1, -e[i][0]*e[i][0]);
	cout << ans;
}
