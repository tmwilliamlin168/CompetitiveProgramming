#include <bits/stdc++.h>
using namespace std;

#define ll long long

class SubstringQueries {
public:
	int p[5000], c[26], p2[5000], s[5000];
	ll solve(string s2, ll k) {
		int n=s2.size(), la=0;
		for(int i=0; i<2*n; ++i)
			s[i]=s2[i%n]-'a';
		iota(p, p+n+n, 0);
		ll ans=0;
		for(int i=0; i<n; ++i) {
			memset(c, 0, sizeof(c));
			for(int j=0; j<n+n-1-i; ++j)
				++c[s[j]];
			for(int i=1; i<26; ++i)
				c[i]+=c[i-1];
			for(int j=n+n-i-1; ~j; --j)
				if(p[j])
					p2[--c[s[p[j]-1]]]=p[j]-1;
			memcpy(p, p2, 4*(n+n-1-i));
			int j=0;
			while(k==1&&p[j]+i>=n)
				++j;
			ans+=p[j];
			la=p[j];
		}	
		if(k>1) {
			ans+=(ll)la*(k-2)*n;
			for(int i=n-1; ~i; --i) {
				int j=0;
				while(p[j]>i)
					++j;
				ans+=p[j];
			}
		}
		return ans;
	}
};
