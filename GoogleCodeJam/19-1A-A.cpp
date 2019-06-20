#include <bits/stdc++.h>
using namespace std;

int t, n, m;
vector<array<int, 2>> g;
bool u[20][20];

bool rec(int s=0, int li=0, int lj=0) {
	if(s>=n*m)
		return 1;
	vector<array<int, 2>> v;
	for(int i=0; i<n; ++i)
		for(int j=0; j<m; ++j)
			if(!u[i][j])
				v.push_back({i, j});
	random_shuffle(v.begin(), v.end());
	for(array<int, 2> vi : v) {
		if(s&&(li==vi[0]||lj==vi[1]||li+lj==vi[0]+vi[1]||li-lj==vi[0]-vi[1]))
			continue;
		g.push_back(vi);
		u[vi[0]][vi[1]]=1;
		if(rec(s+1, vi[0], vi[1]))
			return 1;
		g.pop_back();
		u[vi[0]][vi[1]]=0;
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> t;
	for(int i=1; i<=t; ++i) {
		cout << "Case #" << i << ": ";
		cin >> n >> m;
		if(rec()) {
			cout << "POSSIBLE\n";
			for(array<int, 2> x : g)
				cout << x[0]+1 << " " << x[1]+1 << "\n";
		} else
			cout << "IMPOSSIBLE\n";
		g.clear();
		memset(u, 0, sizeof(u));
	}
}
