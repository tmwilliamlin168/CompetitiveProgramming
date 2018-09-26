/*
	- If we fix the slope of the line, the problem becomes finding the maximum subarray sum
	- Maintain the points sorted while rotating through O(n^2) possible rotations
	- Each time we rotate, the order of some points changes, so we just need a segment tree to find the maximum subarray sum with updates
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=2e3;
int n, p[mxN], l[mxN];
ll x[mxN], y[mxN], w[mxN], ans;
array<ll, 4> st[1<<12];
array<ll, 6> ss[mxN*(mxN-1)/2];

void upd(int l1, ll x, int i=1, int l2=0, int r2=n-1) {
	if(l2==r2) {
		st[i]={x, max(x, 0ll), max(x, 0ll), max(x, 0ll)};
		return;
	}
	int m2=(l2+r2)/2;
	if(l1<=m2)
		upd(l1, x, 2*i, l2, m2);
	else
		upd(l1, x, 2*i+1, m2+1, r2);
	st[i]={st[2*i][0]+st[2*i+1][0], max(st[2*i][1], st[2*i][0]+st[2*i+1][1]), max(st[2*i+1][2], st[2*i+1][0]+st[2*i][2]), max({st[2*i][3], st[2*i+1][3], st[2*i][2]+st[2*i+1][1]})};
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=0; i<n; ++i) {
		cin >> x[i] >> y[i] >> w[i];
		p[i]=i;
	}
	for(int i=0, k=0; i<n; ++i)
		for(int j=0; j<n; ++j)
			if(i!=j&&(x[i]<x[j]||x[i]==x[j]&&y[i]>y[j]))
				ss[k++]={y[j]-y[i], x[j]-x[i], x[i]==x[j]?y[j]:-x[j], x[i]==x[j]?y[i]:-x[i], i, j};
	sort(p, p+n, [&](const int &a, const int b) {
		return x[a]==x[b]?y[a]>y[b]:x[a]<x[b];
	});
	for(int i=0; i<n; ++i) {
		upd(i, w[p[i]]);
		l[p[i]]=i;
	}
	sort(ss, ss+n*(n-1)/2, [&](const array<ll, 6> &a, const array<ll, 6> &b) {
		ll c=a[0]*b[1]-a[1]*b[0];
		return c?c<0:array<ll, 2>{a[2], a[3]}<array<ll, 2>{b[2], b[3]};
	});
	ans=st[1][3];
	for(int i=0; i<n*(n-1)/2; ++i) {
		int u=ss[i][4], v=ss[i][5];
		swap(l[u], l[v]);
		upd(l[u], w[u]);
		upd(l[v], w[v]);
		if(i>=n*(n-1)/2-1||ss[i][0]*ss[i+1][1]<ss[i][1]*ss[i+1][0])
			ans=max(st[1][3], ans);
	}
	cout << ans;
}
