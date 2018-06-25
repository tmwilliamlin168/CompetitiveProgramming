/*
	- Binary search by answer
	- When t=0, the problem is just checking if k flow can be sent from 0 to n-1
	- For each edge, create a duplicate edge with capacity t and cost 1
	- Find the minimum cost of the maximum flow
		- There must be k flow from 0 to n-1
		- The total cost should be <= t
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=2000;
int nodes, m, k, t, u[mxN], v[mxN], prio[mxN], curflow[mxN], prevedge[mxN], prevnode[mxN], q[mxN], pot[mxN];
bool inqueue[mxN];

struct Edge {
	int to, f, cap, cost, rev;
};
vector<Edge> graph[mxN];

inline void addEdge(int s, int t, int cap, int cost) {
Edge a = {t, 0, cap, cost, graph[t].size()};
Edge b = {s, 0, 0, -cost, graph[s].size()};
  graph[s].push_back(a);
  graph[t].push_back(b);
}

pair<int, int> minCostFlow(int s, int t, int maxf) {
  int flow = 0;
  int flowCost = 0;
  while (flow < maxf) {
    priority_queue<ll, vector<ll>, greater<ll> > q;
    q.push(s);
    fill(prio, prio + nodes, INT_MAX);
    prio[s] = 0;
    curflow[s] = INT_MAX;
    while (!q.empty()) {
      ll cur = q.top();
      int d = cur >> 32;
      int u = cur;
      q.pop();
      if (d != prio[u])
        continue;
      for (int i = 0; i < (int) graph[u].size(); i++) {
        Edge &e = graph[u][i];
        int v = e.to;
        if (e.cap <= e.f) continue;
        int nprio = prio[u] + e.cost + pot[u] - pot[v];
        if (prio[v] > nprio) {
          prio[v] = nprio;
          q.push(((ll) nprio << 32) + v);
          prevnode[v] = u;
          prevedge[v] = i;
          curflow[v] = min(curflow[u], e.cap - e.f);
        }
      }
    }
    if (prio[t] == INT_MAX)
      break;
    for (int i = 0; i < nodes; i++)
      pot[i] += prio[i];
    int df = min(curflow[t], maxf - flow);
    flow += df;
    for (int v = t; v != s; v = prevnode[v]) {
      Edge &e = graph[prevnode[v]][prevedge[v]];
      e.f += df;
      graph[v][e.rev].f -= df;
      flowCost += df * e.cost;
    }
  }
  return make_pair(flow, flowCost);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> nodes >> m >> k >> t;
	for(int i=0; i<m; ++i)
		cin >> u[i] >> v[i];
	int lb=1, rb=k;
	while(lb<=rb) {
		int mb=(lb+rb)/2;
		for(int i=0; i<nodes; ++i)
			graph[i].clear();
		for(int i=0; i<m; ++i) {
			addEdge(u[i], v[i], mb, 0);
			addEdge(v[i], u[i], mb, 0);
			addEdge(u[i], v[i], t, 1);
			addEdge(v[i], u[i], t, 1);
		}
		pair<int, int> res=minCostFlow(0, nodes-1, k);
		if(res.first>=k&&res.second<=t)
			rb=mb-1;
		else
			lb=mb+1;
	}
	cout << lb-1;
}
