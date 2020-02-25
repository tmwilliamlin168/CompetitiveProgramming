#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5;
int n, lb, rb, mb, dp[mxN];
vector<int> adj[mxN];
bool ok;

int br(vector<int> w) {
	int lb2=-1, rb2=w.size()-1;
	while(lb2<rb2) {
		int mb2=(lb2+rb2+1)/2;
		vector<int> w2;
		for(int i=0; i<w.size(); ++i)
			if(i^mb2)
				w2.push_back(w[i]);
		bool ok2=1;
		for(int i=0; i<(int)w2.size()-1-i; ++i)
			ok2&=w2[i]+w2[w2.size()-1-i]>=mb;
		if(ok2)
			lb2=mb2;
		else
			rb2=mb2-1;
	}
	return ~lb2?w[lb2]:-1;
}

void dfs(int u=0, int p=-1) {
	vector<int> w;
	for(int v : adj[u])
		if(v^p) {
			dfs(v, u);
			w.push_back(dp[v]+1);
		}
	dp[u]=0;
	sort(w.begin(), w.end());
	if(w.size()&1) {
		int wi=br(w);
		if(~wi)
			dp[u]=wi;
		else
			ok=0;
		if(!u)
			ok&=dp[u]>=mb;
	} else {
		for(int i=0; i<(int)w.size()-1-i; ++i)
			ok&=w[i]+w[w.size()-1-i]>=mb;
		if(w.size()&&w.back()>=mb) {
			w.pop_back();
			int wi=br(w);
			if(~wi)
				dp[u]=wi;
		}
	}
}

int main() {
	ifstream cin("deleg.in");
	ofstream cout("deleg.out");
	
	cin >> n;
	assert(n>1);
	for(int i=1, u, v; i<n; ++i) {
		cin >> u >> v, --u, --v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	rb=n-1;
	while(lb<rb) {
		mb=(lb+rb+1)/2;
		ok=1;
		dfs();
		if(ok)
			lb=mb;
		else
			rb=mb-1;
	}
	cout << lb;
}
