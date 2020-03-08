#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=1e6;
ll h[mxN], ans[mxN], l[mxN], lm[mxN], a2;

class Prominence {
public:
	void solve(int n) {
		for(int i=0; i<n; ++i) {
			for(l[i]=i-1, lm[i]=h[i]; ~l[i]&&h[i]>=h[l[i]]; l[i]=l[l[i]])
				lm[i]=min(lm[i], lm[l[i]]);
			if((i==0||h[i]>h[i-1])&&(i==n-1||h[i]>h[i+1])&&~l[i])
				ans[i]=min(ans[i], h[i]-lm[i]);
		}
	}
	ll sumOfProminences(int n, vector<int> coef, vector<int> idx, vector<int> val) {
		for(int i=0; i<n; ++i)
			h[i]=((((ll)coef[i%2*3]*i+coef[i%2*3+1])%1000000007)*i+coef[i%2*3+2])%1000000007;
		for(int j=0; j<idx.size(); ++j)
			h[idx[j]]=val[j];
		for(int i=0; i<n; ++i)
			if((i==0||h[i]>h[i-1])&&(i==n-1||h[i]>h[i+1]))
				ans[i]=h[i];
		solve(n);
		reverse(h, h+n);
		reverse(ans, ans+n);
		solve(n);
		for(int i=0; i<n; ++i)
			a2+=ans[i];
		return a2;
	}
};
