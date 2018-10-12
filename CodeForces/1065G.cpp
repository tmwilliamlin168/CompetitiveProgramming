#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=200;
int n, m;
ll k, dp[mxN+1];
string fp[mxN+1], fs[mxN+1];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k >> m;
	fp[0]=fs[0]="0";
	fp[1]=fs[1]="1";
	for(int i=2; i<=n; ++i) {
		fp[i]=fp[i-2]+fp[i-1];
		fp[i]=fp[i].substr(0, m);
	}
	for(int i=2; i<=n; ++i) {
		fs[i]=fs[i-2]+fs[i-1];
		fs[i]=fs[i].substr(max((int)fs[i].size()-m, 0));
	}
	string cs="";
	++k;
	for(int i=1; i<=m; ++i) {
		if(cs==fs[n].substr(max((int)fs[n].size()-i+1, 0)))
			--k;
		if(!k)
			break;
		cs+='0';
		dp[0]=i==1;
		for(int j=2; j<=n; ++j) {
			dp[j]=min(dp[j-2]+dp[j-1], (ll)1e18);
			for(int l=1; l<=i-1; ++l) {
				bool ok=fs[j-2].size()>=l&&fp[j-1].size()>=i-l;
				for(int o=1; o<=l&&ok; ++o)
					ok=fs[j-2][fs[j-2].size()-o]==cs[l-o];
				for(int o=l; o<i&&ok; ++o)
					ok=fp[j-1][o-l]==cs[o];
				dp[j]+=ok;
			}
		}
		if(k>dp[n]) {
			k-=dp[n];
			cs.back()='1';
		}
	}
	cout << cs;
}
