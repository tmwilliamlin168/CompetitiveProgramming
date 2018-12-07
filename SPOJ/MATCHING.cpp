#include <bits/stdc++.h>
using namespace std;

const int maxN=50000;

vector<int> canMatch[maxN];
bool used[maxN], vis[maxN];
int matching[maxN], dist[maxN], qu[maxN];

bool dfs(int u1) {
	vis[u1]=1;
	for(int v : canMatch[u1]) {
		int u2=matching[v];
		if(u2==-1||!vis[u2]&&dist[u2]==dist[u1]+1&&dfs(u2)) {
			used[u1]=1;
			matching[v]=u1;
			return 1;
		}
	}
	return 0;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, m, p;
	cin >> n >> m >> p;
	memset(matching, -1, 4*m);
	for(int i=0; i<p; ++i) {
		int a, b;
		cin >> a >> b;
		canMatch[a-1].push_back(b-1);
	}
	int qt, f, t=0;
	while(1) {
		memset(dist, 69, 4*n);
		qt=0;
		for(int i=0; i<n; ++i) {
			if(!used[i]) {
				qu[qt++]=i;
				dist[i]=0;
			}
		}
		for(int i=0; i<qt; ++i) {
			int u1=qu[i];
			for(int v : canMatch[u1]) {
				int u2=matching[v];
				if(u2!=-1&&dist[u2]>=n) {
					dist[u2]=dist[u1]+1;
					qu[qt++]=u2;
				}
			}
		}
		f=0;
		memset(vis, 0, n);
		for(int i=0; i<n; ++i)
			if(!used[i]&&dfs(i))
				++f;
		if(!f)
			break;
		t+=f;
	}
	cout << t;
}
