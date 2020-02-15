#include <bits/stdc++.h>
using namespace std;

#define ll long long

struct MCF {
	static const int mxN=6e3;
	int n, prio[mxN], curflow[mxN], prevedge[mxN], prevnode[mxN], pot[mxN];
	priority_queue<ll, vector<ll>, greater<ll>> q;

	struct Edge {
		int to, f, cap, cost, rev;
	};
	vector<Edge> adj[mxN];

	inline void addEdge(int s, int t, int cap, int cost) {
		Edge a = {t, 0, cap, cost, adj[t].size()};
		Edge b = {s, 0, 0, -cost, adj[s].size()};
		adj[s].push_back(a);
		adj[t].push_back(b);
	}

	inline pair<int, int> minCostFlow(int s, int t, int maxf) {
		int flow=0, flowCost=0;
		while(flow<maxf) {
			q.push(s);
			fill(prio, prio+n, INT_MAX);
			prio[s]=0;
			curflow[s]=INT_MAX;
			while(!q.empty()) {
				ll cur=q.top();
				int d=cur>>32, u=cur;
				q.pop();
				if(d!=prio[u])
					continue;
				for(int i=0; i<adj[u].size(); ++i) {
					Edge &e=adj[u][i];
					int v=e.to;
					if (e.cap<=e.f)
						continue;
					int nprio=prio[u]+e.cost+pot[u]-pot[v];
					if (prio[v]>nprio) {
						prio[v]=nprio;
						q.push(((ll)nprio<<32)+v);
						prevnode[v]=u;
						prevedge[v]=i;
						curflow[v]=min(curflow[u], e.cap-e.f);
					}
				}
			}
			if(prio[t]==INT_MAX)
				break;
			for(int i=0; i<n; ++i)
				pot[i]+=prio[i];
			int df=min(curflow[t], maxf-flow);
			flow+=df;
			for(int v=t; v!=s; v=prevnode[v]) {
				Edge &e=adj[prevnode[v]][prevedge[v]];
				e.f+=df;
				adj[v][e.rev].f-=df;
				flowCost+=df*e.cost;
			}
		}
		return make_pair(flow, flowCost);
	}
} mcf;

const int mxN=50;
int n, m, k, c, d, a[mxN], t, source, sink;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> k >> c >> d;
	t=n+k-1;
	source=n*t;
	sink=n*t+1;
	for(int i=0; i<t; ++i) {
		mcf.addEdge(i, sink, k, 0);
	}
	for(int i=0, ai; i<k; ++i) {
		cin >> ai, --ai;
		mcf.addEdge(source, ai*t, 1, 0);
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j+1<t; ++j) {
			mcf.addEdge(i*t+j, i*t+j+1, k, c);
		}
	}
	auto processEdge=[](int u, int v) {
		for(int i=0; i+1<t; ++i) {
			for(int j=0; j<k; ++j) {
				mcf.addEdge(u*t+i, v*t+i+1, 1, d*(2*j+1)+c);
			}
		}
	};
	for(int i=0, u, v; i<m; ++i) {
		cin >> u >> v, --u, --v;
		processEdge(u, v);
		processEdge(v, u);
	}
	mcf.n=sink+1;
	pair<int, int> p=mcf.minCostFlow(source, sink, k);
	cout << p.second;
}
