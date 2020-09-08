#include "paint.h"
#include <bits/stdc++.h>
using namespace std;

const int mxN=2e5, mxK=100;
int n, k, a[mxN+1], b1[mxN], b2[mxN+1];
bool dp1[mxN+1][mxK+1], dp2[mxN+1][mxK+1];

string solve_puzzle(string s, vector<int> c) {
	n=s.size();
	k=c.size();
	for(int i=0; i<n; ++i)
		a[i+1]=a[i]+(s[i]=='_');
	dp1[0][0]=dp2[n][k]=1;
	for(int i=0; i<n; ++i) {
		for(int j=0; j<=k; ++j) {
			if(s[i]^'X')
				dp1[i+1][j]|=dp1[i][j];
			if(j<k&&i+c[j]<n&&s[i+c[j]]^'X'&&a[i+c[j]]==a[i])
				dp1[i+c[j]+1][j+1]|=dp1[i][j];
		}
	}
	for(int i=n; i; --i) {
		for(int j=0; j<=k; ++j) {
			if(s[i-1]^'X')
				dp2[i-1][j]|=dp2[i][j];
			if(j&&i-c[j-1]>0&&s[i-c[j-1]-1]^'X'&&a[i]==a[i-c[j-1]])
				dp2[i-c[j-1]-1][j-1]|=dp2[i][j];
		}
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<=k; ++j)
			b1[i]|=dp1[i+1][j]&&dp2[i][j];
		for(int j=0; j<k; ++j) {
			if(i+c[j]<=n&&dp1[i][j]&&dp2[i+c[j]][j+1]&&a[i+c[j]]==a[i]) {
				++b2[i];
				--b2[i+c[j]];
			}
		}
		b2[i+1]+=b2[i];
		s[i]=(b1[i]&&b2[i]?'?':b1[i]?'_':'X');
	}
    return s;
}
