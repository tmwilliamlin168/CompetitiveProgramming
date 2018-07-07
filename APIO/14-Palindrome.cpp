/*
	- There are at most n distinct palindromic substrings in a string, all of which can be found with manacher
	- Finding how many times a substring appears in a string is a classical suffix array + lcp problem
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=3e5, mxlgN=18;
string s;
int n, m=123, sa1[mxN], sa2[mxN], cl1[mxN*2], cl2[mxN], cnt[mxN], lcp[mxlgN+1][mxN], p[mxN*2+1];
char s2[mxN*2+3];

inline int lcpq(int l, int r) {
	int k=31-__builtin_clz(r-l+1);
	return min(lcp[k][l], lcp[k][r-(1<<k)+1]);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> s;
	n=s.size();
	for(int i=0; i<n; ++i)
		cl1[i]=s[i];
	for(int l=1; l<=n; l*=2) {
		memset(cnt, 0, 4*m);
		for(int i=0; i<n; ++i)
			++cnt[cl1[i+l]];
		for(int i=1; i<m; ++i)
			cnt[i]+=cnt[i-1];
		for(int i=n-1; i>=0; --i)
			sa2[--cnt[cl1[i+l]]]=i;
		memset(cnt, 0, 4*m);
		for(int i=0; i<n; ++i)
			++cnt[cl1[i]];
		for(int i=1; i<m; ++i)
			cnt[i]+=cnt[i-1];
		for(int i=n-1; i>=0; --i)
			sa1[--cnt[cl1[sa2[i]]]]=sa2[i];
		m=0;
		for(int i=0; i<n; ++i) {
			if(!i||cl1[sa1[i]]!=cl1[sa1[i-1]]||cl1[sa1[i]+l]!=cl1[sa1[i-1]+l])
				++m;
			cl2[sa1[i]]=m;
		}
		++m;
		memcpy(cl1, cl2, 4*n);
	}
	s+="$";
	for(int i=0, k=0; i<n; ++i, k-=k>0) {
		if(cl1[i]>=n)
			continue;
		for(int j=sa1[cl1[i]]; s[i+k]==s[j+k]; ++k);
		lcp[0][cl1[i]]=k;
	}
	for(int k=1; k<=mxlgN; ++k)
		for(int i=0; i<=n-(1<<k); ++i)
			lcp[k][i]=min(lcp[k-1][i], lcp[k-1][i+(1<<(k-1))]);
	int c=-1, r=-1;
	s2[0]='!', s2[1]='#', s2[2*n+2]='@';
	for(int i=0; i<n; ++i) {
		s2[2*i+2]=s[i];
		s2[2*i+3]='#';
	}
	ll ans=0;
	for(int i=1; i<=2*n+1; ++i) {
		if(r>=i)
			p[i]=min(r-i, p[2*c-i]);
		while(s2[i+p[i]]==s2[i-p[i]]) {
			if((i-p[i])%2==0) {
				int j=(i-p[i])/2-1, l=p[i]+1, tl=1, lb, rb;
				lb=1, rb=cl1[j]-1;
				while(lb<=rb) {
					int mb=(lb+rb)/2;
					if(lcpq(mb, cl1[j]-1)>=l)
						rb=mb-1;
					else
						lb=mb+1;
				}
				tl+=cl1[j]-lb;
				lb=cl1[j], rb=n-1;
				while(lb<=rb) {
					int mb=(lb+rb)/2;
					if(lcpq(cl1[j], mb)>=l)
						lb=mb+1;
					else
						rb=mb-1;
				}
				tl+=rb-cl1[j]+1;
				ans=max((long long)tl*l, ans);
			}
			++p[i];
		}
		--p[i];
		if(i+p[i]>r) {
			c=i;
			r=i+p[i];
		}
	}
	cout << ans;
}
