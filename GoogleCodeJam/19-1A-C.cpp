#include <bits/stdc++.h>
using namespace std;

const int mxTS=5e4;
int t, n, ts, d[mxTS], c[mxTS][26];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> t;
	for(int i=1; i<=t; ++i) {
		cout << "Case #" << i << ": ";
		cin >> n;
		ts=1;
		memset(d, 0, sizeof(d));
		memset(c, 0, sizeof(c));
		for(int i=0; i<n; ++i) {
			string w;
			cin >> w;
			int u=0;
			for(int i=w.size()-1; ~i; --i) {
				if(!c[u][w[i]-'A']) {
					c[u][w[i]-'A']=ts++;
				}
				u=c[u][w[i]-'A'];
			}
			++d[u];
		}
		int ans=0;
		for(int i=ts-1; i; --i) {
			for(int j=0; j<26; ++j)
				if(c[i][j])
					d[i]+=d[c[i][j]];
			if(d[i]>=2) {
				ans+=2;
				d[i]-=2;
			}
		}
		cout << ans << "\n";
	}
}
