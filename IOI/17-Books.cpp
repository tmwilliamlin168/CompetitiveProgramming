#include "books.h"
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ar array

const int mxN=1e6;
int n, a, b, who[mxN];
vector<int> adj[mxN], adj2[mxN], st, adj3[mxN], c;
bool vis[mxN];
ar<int, 3> dp[mxN];

void dfs1(int u) {
	vis[u]=1;
	for(int v : adj[u])
		if(!vis[v])
			dfs1(v);
	st.push_back(u);
}

void dfs2(int u, int r) {
	vis[u]=0;
	c.push_back(u);
	who[u]=r;
	for(int v : adj2[u])
		if(vis[v])
			dfs2(v, r);
}

ll minimum_walk(vector<int> p, int s) {
	n=p.size();
	ll ans=0;
	for(; a<s&&p[a]==a; ++a);
	for(b=n-1; b>s&&p[b]==b; --b);
	for(int i=a; i<s; ++i)
		adj[i].push_back(i+1);
	for(int i=b; i>s; --i)
		adj[i].push_back(i-1);
	for(int i=a; i<=b; ++i) {
		ans+=abs(i-p[i]);
		adj[i].push_back(p[i]);
	}
	for(int i=a; i<=b; ++i)
		if(!vis[i])
			dfs1(i);
	for(int i=a; i<=b; ++i)
		for(int j : adj[i])
			adj2[j].push_back(i);
	for(int i=b-a; ~i; --i) {
		if(!vis[st[i]])
			continue;
		dfs2(st[i], st[i]);
		dp[st[i]]={n, n, n};
		if(!vis[a]&&st[i]==who[a])
			dp[st[i]][0]=0;
		if(!vis[b]&&st[i]==who[b])
			dp[st[i]][1]=0;
		for(int u : c)
			for(int v : adj2[u])
				for(int k : {0, 1, 2})
					dp[st[i]][k]=min(dp[who[v]][k]+1, dp[st[i]][k]);
		dp[st[i]][2]=min(dp[st[i]][0]+dp[st[i]][1], dp[st[i]][2]);
		c.clear();
	}
	return ans+2*dp[who[s]][2];
}
