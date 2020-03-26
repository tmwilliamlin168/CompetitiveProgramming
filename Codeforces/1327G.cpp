#include <bits/stdc++.h>
using namespace std;

const int mxN=1e3, A=14;
int n;
string s;
long long dp1[mxN+1][1<<A], dp2[mxN+1][1<<A];

struct autoac {
	int sl[mxN+1], sz=1, c[mxN+1][A], d[mxN+1][A], w[mxN+1];
	void add(string s, int x) {
		int u=0;
		for(char a : s) {
			if(!c[u][a-'a'])
				c[u][a-'a']=sz++;
			u=c[u][a-'a'];
		}
		w[u]+=x;
	}
	void ac() {
		for(queue<int> q({0}); q.size(); q.pop()) {
			int u=q.front();
			w[u]+=w[sl[u]];
			for(int a=0; a<A; ++a) {
				int v=c[u][a], s=sl[u];
				if(v) {
					sl[v]=d[s][a];
					q.push(v);
				}
				d[u][a]=v?v:d[s][a];
			}
		}
	}
} ac;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for(int c; n--; ) {
		cin >> s >> c;
		ac.add(s, c);
	}
	ac.ac();
	cin >> s;
	int u=0, i=0;
	long long ans=-1e18, ad=0;
	for(; i<s.size()&&s[i]^'?'; ++i) {
		u=ac.d[u][s[i]-'a'];
		ad+=ac.w[u];
	}
	memset(dp1, 0xc0, sizeof(dp1));
	dp1[u][0]=ad;
	for(int j=i, a=0; i<s.size(); i=j, ++a) {
		memset(dp2, 0xc0, sizeof(dp2));
		for(int k=0; k<ac.sz; ++k)
			for(int l=0; l<1<<A; ++l)
				if(__builtin_popcount(l)==a)
					for(int m=0; m<A; ++m)
						if(l>>m&1^1)
							dp2[ac.d[k][m]][l|1<<m]=max(dp1[k][l]+ac.w[ac.d[k][m]], dp2[ac.d[k][m]][l|1<<m]);
		for(j=i+1; j<s.size()&&s[j]^'?'; ++j);
		memset(dp1, 0xc0, sizeof(dp1));
		for(int k=0; k<ac.sz; ++k) {
			u=k;
			ad=0;
			for(int l=i+1; l<j; ++l) {
				u=ac.d[u][s[l]-'a'];
				ad+=ac.w[u];
			}
			for(int l=0; l<1<<A; ++l)
				dp1[u][l]=max(dp2[k][l]+ad, dp1[u][l]);
		}
	}
	for(int i=0; i<ac.sz; ++i)
		for(int j=0; j<1<<A; ++j)
			ans=max(dp1[i][j], ans);
	cout << ans;
}
