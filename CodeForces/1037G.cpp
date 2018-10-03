#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5, A=26;
string s;
int n, m, lc[A], pos[A][mxN], prv[mxN][A], nxt[mxN][A], dpp[A][mxN], dps[A][mxN], pdp[A][mxN], gc[A+1];
vector<int> tp[mxN];

int cdp(int l, int r) {
	if(l>=r)
		return l==r;
	memset(gc, 0, sizeof(gc));
	for(int i=0; i<A; ++i) {
		int a=nxt[l][i], b=prv[r][i];
		if(a<=b)
			++gc[dps[i][l]^pdp[i][b]^pdp[i][a]^dpp[i][r]];
	}
	for(int i=0; ; ++i)
		if(!gc[i])
			return i;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> s >> m;
	n=s.size();
	for(int i=0; i<n; ++i) {
		int c=s[i]-'a';
		for(int j=0; j<A; ++j)
			prv[i][j]=j==c?lc[c]:(i?prv[i-1][j]:-1);
		pos[c][lc[c]++]=i;
	}
	for(int i=n-1; i>=0; --i) {
		for(int j=0; j<A; ++j)
			nxt[i][j]=s[i]-'a'==j?prv[i][j]:(i<n-1?nxt[i+1][j]:n);
		for(int j=i+1; j<n&&s[j]!=s[i]; ++j)
			tp[j].push_back(i+1);
	}
	for(int i=1; i<n; ++i) {
		int j1=i-1, j2=0, c=s[i]-'a', a=prv[i-1][c], b=a>=0?pos[c][a]:-1;
		while(j1>=b||j2<tp[i-1].size()) {
			if(j1==b&&j1>=0)
				pdp[c][a+1]=pdp[c][a]^dps[c][j1+1];
			if(j1>b)
				dps[c][j1]=cdp(j1, i-1);
			if(j2<tp[i-1].size()&&(j1==tp[i-1][j2]||j1<=b)) {
				dpp[s[tp[i-1][j2]-1]-'a'][i-1]=cdp(tp[i-1][j2], i-1);
				++j2;
			}
			--j1;
		}
	}
	for(int a : tp[n-1])
		dpp[s[a-1]-'a'][n-1]=cdp(a, n-1);
	while(m--) {
		int l, r;
		cin >> l >> r, --l, --r;
		cout << (cdp(l, r)?"Alice":"Bob") << "\n";
	}
}
