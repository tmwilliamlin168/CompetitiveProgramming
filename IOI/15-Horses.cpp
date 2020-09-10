#include "horses.h"
#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=5e5, M=1e9+7;
int n, sty[2*mxN], cy[mxN];
ll stx[2*mxN];
set<int> s;

ll qryx(int l, int r) {
	ll b=1;
	for(l+=n, r+=n; l<r; ++l/=2, r/=2) {
		if(l&1)
			b=b*stx[l]%M;
		if(r&1)
			b=b*stx[r-1]%M;
	}
	return b;
}

int qryy(int l, int r) {
	int b=0;
	for(l+=n, r+=n; l<r; ++l/=2, r/=2) {
		if(l&1)
			b=max(sty[l], b);
		if(r&1)
			b=max(sty[r-1], b);
	}
	return b;
}

int c() {
	ll mx=0;
	auto it=s.end();
	while(mx<1e9&&*it) {
		--it;
		mx=max((ll)cy[*it], mx);
		mx*=stx[n+*it];
	}
	return mx%M*qryx(0, *it)%M;
}

int updateX(int i, int x) {
	s.erase(i);
	if(!i||x>1)
		s.insert(i);
	int j=n+i;
	for(stx[j]=x; j/=2;)
		stx[j]=stx[2*j]*stx[2*j+1]%M;
	auto it=s.upper_bound(i);
	int r=*it, l=*--it;
	cy[l]=qryy(l, r);
	if(l) {
		r=*it, l=*--it;
		cy[l]=qryy(l, r);
	}
	return c();
}

int updateY(int i, int x) {
	int j=n+i;
	for(sty[j]=x; j/=2;)
		sty[j]=max(sty[2*j], sty[2*j+1]);
	auto it=s.upper_bound(i);
	int r=*it, l=*--it;
	cy[l]=qryy(l, r);
	return c();
}

int init(int n, int* x, int* y) {
	::n=n;
	for(int i=0; i<n; ++i) {
		stx[n+i]=x[i];
		sty[n+i]=y[i];
		if(!i||x[i]>1)
			s.insert(s.end(), i);
	}
	s.insert(s.end(), n);
	for(int i=n-1; i; --i) {
		stx[i]=stx[2*i]*stx[2*i+1]%M;
		sty[i]=max(sty[2*i], sty[2*i+1]);
	}
	for(auto it=s.begin(); *it<n;) {
		int l=*it, r=*++it;
		cy[l]=qryy(l, r);
	}
	return c();
}
