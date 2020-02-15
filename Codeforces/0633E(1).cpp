/*
	- First, given each l, let's find the best value of p(l, r)
		- If you fix l and increase r, max(l...r) will never decrease and min(l...r) will never increase
		- There is one point of interesection, where everything to the left has v*100 smaller than c
		- If you increase l, max(l...r) will never increase and min(l...r) will never decrease
		- So as you increase l, the intersection point can only move right
	- Sort all p(l)
	- Answer is (p(1)*C(n-1, k-1)+p(2)*C(n-2, k-1)+...+p(n-k+1)*C(k-1, k-1))/C(n, k)
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=1e6;
int n, k, v[mxN], c[mxN], p[mxN], qu1[mxN], qh1, qt1, qu2[mxN], qh2, qt2, lmx;
double ans, cp=1;

inline void pn(int i) {
	while(qt1>qh1&&v[i]>=v[qu1[qt1-1]])
		--qt1;
	qu1[qt1++]=i;
	while(qt2>qh2&&c[i]<=c[qu2[qt2-1]])
		--qt2;
	qu2[qt2++]=i;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k;
	for(int i=0; i<n; ++i)
		cin >> v[i], v[i]*=100;
	for(int i=0; i<n; ++i)
		cin >> c[i];
	for(int i1=0, i2=-1; i1<n; ++i1) {
		if(i2<i1)
			pn(++i2);
		if(qu1[qh1]<i1)
			++qh1;
		if(qu2[qh2]<i1)
			++qh2;
		if(v[qu1[qh1]]>c[qu2[qh2]])
			lmx=0;
		while(v[qu1[qh1]]<=c[qu2[qh2]]) {
			lmx=v[qu1[qh1]];
			if(i2+1>=n)
				break;
			pn(++i2);
		}
		p[i1]=lmx;
		if(v[qu1[qh1]]>c[qu2[qh2]])
			p[i1]=max(c[qu2[qh2]], p[i1]);
	}
	sort(p, p+n);
	for(int i=0; i<=n-k; cp=cp*(n-k-i)/(n-1-i), ++i)
		ans+=(double)p[i]*cp;
	cout << fixed << setprecision(9) << ans*k/n;
}
