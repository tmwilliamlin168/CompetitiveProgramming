#include <bits/stdc++.h>
using namespace std;

struct maxflow {
	static const int mxN=200;
	int n=mxN, s, t, d[mxN], q[mxN], w[mxN];
	struct edge {
		int to, rev, f, cap;
	};
	vector<edge> g[mxN];
	void addEdge(int s, int t, int cap){
		edge a={t, g[t].size(), 0, cap}, b={s, g[s].size(), cap, cap};
		g[s].push_back(a);
		g[t].push_back(b);
	}
	bool dinic_bfs() {
		memset(d, -1, 4*n);
		d[s]=0;
		int qt=0;
		q[qt++]=s;
		for(int qh=0; qh<qt; ++qh) {
			int u=q[qh];
			for(int j=0; j<g[u].size(); ++j) {
				edge &e=g[u][j];
				int v=e.to;
				if(d[v]<0&&e.f<e.cap) {
					d[v]=d[u]+1;
					q[qt++]=v;
				}
			}
		}
		return ~d[t];
	}
	int dinic_dfs(int u, int f) {
		if(u==t)
			return f;
		for(int &i=w[u]; i<g[u].size(); ++i) {
			edge &e=g[u][i];
			if(e.cap<=e.f)
				continue;
			int v=e.to;
			if(d[v]==d[u]+1) {
				int df=dinic_dfs(v, min(f, e.cap-e.f));
				if(df) {
					e.f+=df;
					g[v][e.rev].f-=df;
					return df;
				}
			}
		}
		return 0;
	}
	int maxFlow(int _s, int _t) {
		s=_s;
		t=_t;
		int r=0;
		while(dinic_bfs()) {
			memset(w, 0, 4*n);
			while(int d=dinic_dfs(s, INT_MAX))
				r+=d;
		}
		return r;
	}
} mf;

const int mxM=50;
int n, m, ax[mxM], ay[mxM], bx[mxM], by[mxM];
vector<int> vx, vy;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	if(!m) {
		cout << 0;
		return 0;
	}
	for(int i=0; i<m; ++i) {
		cin >> ax[i] >> ay[i] >> bx[i] >> by[i], ++bx[i], ++by[i];
		vx.push_back(ax[i]);
		vx.push_back(bx[i]);
		vy.push_back(ay[i]);
		vy.push_back(by[i]);
	}
	sort(vx.begin(), vx.end());
	vx.resize(unique(vx.begin(), vx.end())-vx.begin());
	sort(vy.begin(), vy.end());
	vy.resize(unique(vy.begin(), vy.end())-vy.begin());
	for(int i=0; i<m; ++i) {
		ax[i]=lower_bound(vx.begin(), vx.end(), ax[i])-vx.begin();
		bx[i]=lower_bound(vx.begin(), vx.end(), bx[i])-vx.begin();
		ay[i]=lower_bound(vy.begin(), vy.end(), ay[i])-vy.begin();
		by[i]=lower_bound(vy.begin(), vy.end(), by[i])-vy.begin();
	}
	int source=vx.size()+vy.size()-2, sink=source+1;
	for(int i=0; i<vx.size()-1; ++i)
		mf.addEdge(source, i, vx[i+1]-vx[i]);
	for(int i=0; i<vy.size()-1; ++i)
		mf.addEdge(vx.size()-1+i, sink, vy[i+1]-vy[i]);
	for(int i=0; i<m; ++i)
		for(int j=ax[i]; j<bx[i]; ++j)
			for(int k=ay[i]; k<by[i]; ++k)
				mf.addEdge(j, vx.size()-1+k, 1e9);
	cout << mf.maxFlow(source, sink);
}
