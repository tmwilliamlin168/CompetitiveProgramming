/*
	- https://ioinformatics.org/files/ioi2014solutions.zip
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=1e5;
int n, s, d, *a, p[mxN], b[mxN], cl;
ll ans, c1[2*mxN+mxN/2+1], c2[2*mxN+mxN/2+1];
array<ll, 2> ft[mxN+1];
vector<int> v;

void upd(int i, array<ll, 2> x) {
	for(++i; i<=n; i+=i&-i) {
		ft[i][0]+=x[0];
		ft[i][1]+=x[1];
	}
}

void ml(int nl) {
	while(cl<nl) {
		++cl;
		if(v[cl]!=-1)
			upd(b[v[cl]], {1, a[v[cl]]});
	}
	while(cl>nl) {
		if(v[cl]!=-1)
			upd(b[v[cl]], {-1, -a[v[cl]]});
		--cl;
	}
}

void s3(int l1, int r1, int l2, int r2, ll c[2*mxN+mxN/2+1]) {
	if(l1>r1)
		return;
	int m1=(l1+r1)/2;
	array<ll, 2> m2{-1};
	for(int i=l2; i<=r2; ++i) {
		ml(i);
		ll s2=0;
		for(int j=16, lb=0, s1=0; j>=0; --j) {
			if(lb+(1<<j)<=n&&s1+ft[lb+(1<<j)][0]<=m1-i) {
				lb+=1<<j;
				s1+=ft[lb][0];
				s2+=ft[lb][1];
			}
		}
		m2=max(array<ll, 2>{s2, -i}, m2);
	}
	c[m1]=m2[0];
	s3(l1, m1-1, l2, -m2[1], c);
	s3(m1+1, r1, -m2[1], r2, c);
}

void s2(ll c[2*mxN+mxN/2+1]) {
	memset(ft, 0, sizeof(ft));
	cl=-1;
	s3(0, d, 0, v.size()-1, c);
	v.clear();
}

void s1() {
	sort(p, p+n, [&](const int &i, const int &j) {
		return a[i]>a[j];
	});
	for(int i=0; i<n; ++i)
		b[p[i]]=i;
	for(int i=s; i>=0; --i)
		v.push_back(i);
	s2(c1);
	v.push_back(-1);
	for(int i=s+1; i<n; ++i) {
		v.push_back(-1);
		v.push_back(i);
	}
	s2(c2);
	for(int i=0; i<=d; ++i)
		ans=max(c1[i]+c2[d-i], ans);
}

ll findMaxAttraction(int n2, int s2, int d2, int a2[]) {
	n=n2;
	s=s2;
	d=d2;
	a=a2;
	for(int i=0; i<n; ++i)
		p[i]=i;
	s1();
	s=n-1-s;
	for(int i=0; i<n-1-i; ++i)
		swap(a[i], a[n-1-i]);
	s1();
	return ans;
}
