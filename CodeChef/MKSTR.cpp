#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
 
const int mxN=1e4, mxM=1e3, mxP=100, INF=2e9;
int n, pf[mxP+1+mxM];
string p[mxN], t, s;
ll dp[mxM][mxM+1], cl[26], cr[26], kl[mxN], kr[mxN], tl[mxM][mxP+1], tr[mxM+1][mxP+1];
 
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=0; i<n; ++i)
		cin >> p[i];
	for(int i=0; i<26; ++i)
		cin >> cl[i];
	for(int i=0; i<26; ++i)
		cin >> cr[i];
	for(int i=0; i<n; ++i)
		cin >> kl[i];
	for(int i=0; i<n; ++i)
		cin >> kr[i];
	cin >> t;
	memset(tl, 0x7F, sizeof(tl));
	memset(tr, 0x7F, sizeof(tr));
	for(int i=0; i<n; ++i) {
		s=p[i]+"!"+t;
		int ps=p[i].size();
		for(int j=1; j<s.size(); ++j) {
			int k=pf[j-1];
			while(s[k]!=s[j]) {
				if(!k) {
					k=-1;
					break;
				}
				k=pf[k-1];
			}
			pf[j]=k+1;
			if(pf[j]>=ps) {
				tl[j-2*ps][ps]=min(kl[i], tl[j-2*ps][ps]);
				tr[j-ps][ps]=min(kr[i], tr[j-ps][ps]);
			}
		}
	}
	for(int j=1; j<=t.size(); ++j) {
		for(int i=j-1; i>=0; --i) {
			dp[i][j]=min(dp[i+1][j]+cl[t[i]-'a']*(j-i-1), dp[i][j-1]+cr[t[j-1]-'a']*(j-i-1));
			for(int k=1; k<=min(j-i, mxP); ++k) {
				if(tl[i][k]<INF)
					dp[i][j]=min(dp[i+k][j]+tl[i][k]*(j-i-k), dp[i][j]);
				if(tr[j][k]<INF)
					dp[i][j]=min(dp[i][j-k]+tr[j][k]*(j-i-k), dp[i][j]);
			}
		}
	}
	cout << dp[0][t.size()];
}
