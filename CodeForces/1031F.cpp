#include <bits/stdc++.h>
using namespace std;

const int mxN=1e6, MG1=289, MG2=9036, MG3=245760, MG4=1188, MG5=10;
int t, a, b, lp[mxN+1], c[MG2], d[MG2], qt, e[MG3+1], es, f[MG1][MG4], g[mxN+1], q2[MG2];
vector<int> ps, q1[MG2], adj[MG2];
map<vector<int>, int> mp;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	for(int i=2; i<=mxN; ++i) {
		if(!lp[i]) {
			lp[i]=i;
			ps.push_back(i);
		}
		for(int j=0; j<ps.size()&&ps[j]<=lp[i]&&i*ps[j]<=mxN; ++j)
			lp[i*ps[j]]=ps[j];
	}
	memset(d, 1, sizeof(d));
	auto av=[&](vector<int> v, int p=-1) {
		sort(v.begin(), v.end());
		auto it=mp.find(v);
		if(it==mp.end()) {
			it=mp.insert({v, qt}).first;
			d[qt]=p==-1?0:d[p]+1;
			q1[qt++]=v;
		}
		return it->second;
	};
	for(int i=1; i<=mxN; ++i) {
		vector<int> v;
		int i2=i;
		while(i2>1) {
			int e=0, p=lp[i2];
			for(; i2%p==0; i2/=p, ++e);
			v.push_back(e);
		}
		g[i]=av(v);
	}
	for(int qh=0; qh<qt&&d[qh]<MG5; ++qh) {
		vector<int> uv=q1[qh];
		for(int i=0; i<uv.size(); ++i) {
			++uv[i];
			adj[qh].push_back(av(uv, qh));
			uv[i]-=2;
			if(uv[i]>0)
				adj[qh].push_back(av(uv, qh));
			++uv[i];
		}
		uv.push_back(1);
		adj[qh].push_back(av(uv, qh));
	}
	memset(e, -1, sizeof(e));
	for(int i=0; i<MG2; ++i) {
		c[i]=1;
		for(int j : q1[i])
			c[i]*=j+1;
		if(e[c[i]]==-1)
			e[c[i]]=es++;
		c[i]=e[c[i]];
	}
	memset(f, 1, sizeof(f));
	for(int i=0; i<MG1; ++i) {
		memset(d, 1, sizeof(d));
		qt=0;
		q2[qt++]=i;
		d[i]=0;
		for(int qh=0; qh<qt&&d[q2[qh]]<MG5; ++qh) {
			int u=q2[qh];
			for(int v : adj[u]) {
				if(d[v]>1e7) {
					q2[qt++]=v;
					d[v]=d[u]+1;
				}
			}
		}
		for(int j=0; j<MG2; ++j)
			f[i][c[j]]=min(d[j], f[i][c[j]]);
	}
	cin >> t;
	while(t--) {
		cin >> a >> b, a=g[a], b=g[b];
		int ans=1e7;
		for(int i=0; i<MG4; ++i)
			ans=min(f[a][i]+f[b][i], ans);
		cout << ans << "\n";
	}
}
