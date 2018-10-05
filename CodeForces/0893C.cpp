#include <bits/stdc++.h>

using namespace std;

#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define f(i,a,b) for (int i = (a); i < (b); i++)
#define fr(i,a,b) for (int i = (a); i >= b; i--)
#define all(a) a.begin(), a.end()
#define MOD 1e9+7

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector< pii > vii;

#define MAX 100010
bool visited[MAX];
vi adj[MAX];
int cost[MAX];

int bfs(int s) {
	int min_cost = cost[s];
	visited[s] = true;
	queue<int> q;
	q.push(s);
	while (!q.empty()) {
		int now = q.front(); q.pop();
		for (auto c: adj[now]) {
			if (!visited[c]) {
				q.push(c); min_cost = min(min_cost, cost[c]);
				visited[c] = true;
			}
		}
	}
	return min_cost;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	memset(visited, false, sizeof(visited));
	for (int i = 0; i < MAX; i++) adj[i].clear();
	int n, m, x, y; cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> cost[i];
	for (int i = 0; i < m; i++) {
		cin >> x >> y;
		adj[x].pb(y); adj[y].pb(x);
	}	
	ll ans = 0;
	for (int i = 1; i <= n; i++) {
		if (!visited[i]) {
			ans += bfs(i);
		}
	}
	cout << ans << endl;
	return 0;
}
