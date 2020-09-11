#include "shortcut.h"
#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll find_shortcut(int n, vector<int> l, vector<int> d, int c) {
	vector<ll> x(n);
	for(int i=0; i+1<n; ++i)
		x[i+1]=x[i]+l[i];
	vector<int> e{n-1};
	for(int i=n-2; ~i; --i)
		if(d[i]-x[i]>d[e.back()]-x[e.back()])
			e.push_back(i);
	ll lb=1, rb=2e15;
	while(lb<rb) {
		ll mb=(lb+rb)/2, a1, a2=-1e18, a3=-1e18, b1=-1e18, b2=1e18, b3=-1e18, b4=1e18;
		for(int i=n-1, j=0; ~i; --i) {
			if(j>=e.size()||i>e[j]) {
				if(d[e[j-1]]+x[e[j-1]]+d[i]-x[i]>mb) {
					b1=max(c-mb+d[e[j-1]]+x[e[j-1]]+d[i]+x[i], b1);
					b2=min(mb-c-d[e[j-1]]+x[e[j-1]]-d[i]+x[i], b2);
					b3=max(c-mb+d[e[j-1]]-x[e[j-1]]+d[i]+x[i], b3);
					b4=min(mb-c-d[e[j-1]]-x[e[j-1]]-d[i]+x[i], b4);
				}
			} else
				++j;
		}
		for(int i=e.size()-1, j=0; j<n;) {
			a1=d[j]+x[j];
			for(; ~i&&e[i]<j&&a1+d[e[i]]-x[e[i]]>mb; --i) {
				a2=max(d[e[i]]+x[e[i]], a2);
				a3=max(d[e[i]]-x[e[i]], a3);
			}
			b1=max(c-mb+a1+a2, b1);
			b2=min(mb-c-d[j]+x[j]-a3, b2);
			b3=max(c-mb+d[j]-x[j]+a2, b3);
			b4=min(mb-c-a1-a3, b4);
			for(int k=j; ++j<n&&d[j]+x[j]<a1;) {
				if(d[j]+x[j]+d[k]-x[k]>mb) {
					b1=max(c-mb+d[j]+x[j]+a1, b1);
					b2=min(mb-c-d[j]+x[j]-d[k]+x[k], b2);
					b3=max(c-mb+d[j]-x[j]+a1, b3);
					b4=min(mb-c-d[j]-x[j]-d[k]+x[k], b4);
				}
			}
		}
		bool ok=0;
		if(b1<=b2&&b3<=b4) {
			for(int i=0, j1=n, j2=n, j3=0, j4=0; i<n&&!ok; ++i) {
				for(; j1&&x[j1-1]>=b1-x[i]; --j1);
				for(; j2&&x[j2-1]>b2-x[i]; --j2);
				for(; j3<n&&x[j3]<b3+x[i]; ++j3);
				for(; j4<n&&x[j4]<=b4+x[i]; ++j4);
				ok|=max(j1, j3)<min(j2, j4);
			}
		}
		if(ok)
			rb=mb;
		else
			lb=mb+1;
	}
	return lb;
}
