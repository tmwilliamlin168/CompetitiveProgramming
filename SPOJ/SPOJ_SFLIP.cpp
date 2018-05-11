/*
	- The answer is sum of array - 2*(minimum sum of k subarrays)
	- Maximum sum of k-disjoint subarrays: http://chaoxuprime.com/posts/2014-10-13-maximum-sum-k-disjoint-subarrays.html
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5;

int l[mxN+2], r[mxN+2], v[mxN+2];

struct cmp {
	bool operator()(const int &a, const int &b) const {
		int c=abs(v[a])-abs(v[b]);
		return c?c<0:a<b;
	}
};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, k, t=0, s;
	cin >> n >> k;
	for(int i=1; i<=n; ++i) {
		cin >> v[i];
		t+=v[i];
		v[i]*=-2;
	}
	if(!k) {
		cout << t;
		return 0;
	}
	s=n;
	for(int i=1; i<=n; ++i) {
		r[i-1]=i;
		l[i+1]=i;
	}
	l[1]=0;
	r[n]=n+1;
	for(int i=r[0]; r[i]<=n; i=r[i]) {
		if(v[i]<=0&&v[r[i]]<=0||v[i]>0&&v[r[i]]>0) {
			l[r[i]]=l[i];
			r[l[i]]=r[i];
			v[r[i]]+=v[i];
			--s;
		}
	}
	if(v[r[0]]<=0) {
		l[r[r[0]]]=0;
		r[0]=r[r[0]];
		--s;
	}
	if(v[l[n+1]]<=0) {
		r[l[l[n+1]]]=n+1;
		l[n+1]=l[l[n+1]];
		--s;
	}
	set<int, cmp> ts;
	for(int i=r[0]; i<=n; i=r[i])
		ts.insert(i);
	while(s/2>=k) {
		int f=*ts.begin();
		ts.erase(ts.begin());
		ts.erase(l[f]);
		ts.erase(r[f]);
		v[f]+=v[l[f]]+v[r[f]];
		if(l[f]>=1) {
			r[l[l[f]]]=f;
			l[f]=l[l[f]];
		}
		if(r[f]<=n) {
			l[r[r[f]]]=f;
			r[f]=r[r[f]];
		}
		if(v[f]>0||r[0]!=f&&l[n+1]!=f)
			ts.insert(f);
		s-=2;
	}
	for(int i=r[0]; i<=n; i=r[i])
		if(v[i]>0)
			t+=v[i];
	cout << t;
}
