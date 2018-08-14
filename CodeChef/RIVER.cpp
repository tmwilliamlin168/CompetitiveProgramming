#pragma GCC optimize ("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

const int mxN=1e6;
int t, n, css, a1[2*mxN-3], a2[2*mxN-3], b1[2*mxN-3], b2[2*mxN-3];
vector<int> adj[mxN], tc, na;

struct cluster {
	int u[2], c[2], p, dp[4];
	bool t;
} cs[2*mxN-3];

inline void solve() {
	cin >> n;
	adj[0].clear();
	css=0;
	tc=vector<int>(n);
	for(int i=1; i<n; ++i) {
		adj[i].clear();
		int pi;
		cin >> pi, --pi;
		adj[pi].push_back(css);
		adj[i].push_back(css);
		cs[css++]={{pi, i}, {-1, -1}, -1, {0, 0, 0, 0}};
		tc[i]=i;
	}
	while(css<2*n-3) {
		for(int i=0; i<tc.size(); ++i) {
			int u=tc[i];
			if(adj[u].size()==2&&cs[adj[u][0]].p==-1&&cs[adj[u][1]].p==-1) {
				int e1=adj[u][0], e2=adj[u][1];
				cs[e1].p=cs[e2].p=css;
				cs[css]={{u^cs[e1].u[0]^cs[e1].u[1], u^cs[e2].u[0]^cs[e2].u[1]}, {e1, e2}, -1, {0, 0, 0, 0}, 0};
				a1[css]=u==cs[e1].u[0]?1:2;
				a2[css]=3^a1[css];
				b1[css]=u==cs[e2].u[0]?1:2;
				b2[css]=3^b1[css];
				++css;
			} else {
				adj[u].push_back(adj[u][0]);
				for(int j=0; j<adj[u].size()-1; ++j) {
					int e1=adj[u][j], e2=adj[u][j+1];
					if(cs[e1].p==-1&&cs[e2].p==-1&&e1!=e2&&adj[u^cs[e2].u[0]^cs[e2].u[1]].size()<=1) {
						cs[e1].p=cs[e2].p=css;
						cs[css]={{u, u^cs[e1].u[0]^cs[e1].u[1]}, {e1, e2}, -1, {0, 0, 0, 0}, 1};
						a1[css]=u==cs[e1].u[0]?1:2;
						a2[css]=3^a1[css];
						b1[css]=u==cs[e2].u[0]?1:2;
						b2[css]=3^b1[css];
						++css;
						++j;
					}
				}
				adj[u].pop_back();
			}
		}
		int ns=0;
		for(int i=0; i<tc.size(); ++i) {
			int u=tc[i];
			na.clear();
			for(int e : adj[u]) {
				if(cs[e].p!=-1&&(cs[cs[e].p].u[0]==u||cs[cs[e].p].u[1]==u)&&(na.empty()||cs[e].p!=na.back()&&cs[e].p!=na[0]))
					na.push_back(cs[e].p);
				else if(cs[e].p==-1)
					na.push_back(e);
			}
			adj[u]=na;
			if(!adj[u].empty())
				tc[ns++]=u;
		}
		tc.resize(ns);
	}
	for(int i=1; i<n; ++i) {
		cs[i-1].dp[3]=1;
		for(int j=cs[i-1].p; j!=-1; j=cs[j].p) {
			int c0=cs[j].c[0], c1=cs[j].c[1];
			if(cs[j].t) {
				cs[j].dp[0]=cs[c0].dp[0]+cs[c1].dp[b2[j]];
				cs[j].dp[1]=max(cs[c0].dp[a1[j]]+cs[c1].dp[b2[j]], cs[c0].dp[0]+cs[c1].dp[3]);
				cs[j].dp[2]=cs[c0].dp[a2[j]]+cs[c1].dp[b2[j]];
				cs[j].dp[3]=max(cs[c0].dp[3]+cs[c1].dp[b2[j]], cs[c0].dp[a2[j]]+cs[c1].dp[3]);
			} else
				for(int k=0; k<4; ++k)
					cs[j].dp[k]=max(cs[c0].dp[k&1?3:a1[j]]+cs[c1].dp[k/2?b2[j]:0], cs[c0].dp[k&1?a2[j]:0]+cs[c1].dp[k/2?3:b1[j]]);
			cs[j].dp[1]=max(cs[j].dp[0], cs[j].dp[1]);
			cs[j].dp[2]=max(cs[j].dp[0], cs[j].dp[2]);
			cs[j].dp[3]=max(max(cs[j].dp[1], cs[j].dp[2]), cs[j].dp[3]);
		}
		cout << 1+cs[2*n-4].dp[3]+(cs[2*n-4].dp[3]==1&&i>2) << " ";
	}
	cout << "\n";
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> t;
	while(t--)
		solve();
}
