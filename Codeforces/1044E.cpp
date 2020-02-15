#include <bits/stdc++.h>
using namespace std;

const int mxN=20;
int n, m, a[mxN][mxN], c[4][2]={{0, 0}, {0, 1}, {1, 1}, {1, 0}};
vector<vector<int>> ops, cs{{0, 2, 3, 1}, {2, 4, 5, 3}, {0, 2, 4, 5, 3, 1}};
array<int, 2> p[mxN*mxN+1];
set<vector<int>> vis;

void oc(int i1, int j1, bool b) {
	ops.push_back({});
	for(int i=0; i<4; ++i)
		ops.back().push_back(a[i1+c[i^b][0]][j1+c[i^b][1]]);
	for(int i=2; i>=0; --i)
		swap(a[i1+c[i^b][0]][j1+c[i^b][1]], a[i1+c[(i+1)^b][0]][j1+c[(i+1)^b][1]]);
	for(int i=0; i<4; ++i)
		p[a[i1+c[i][0]][j1+c[i][1]]]={i1+c[i][0], j1+c[i][1]};
}

void cr(bool b) {
	for(int i=n-1; i>2-b; --i) {
		for(int j=m-1; j>=0; --j) {
			int d=b?(j<2?j^1:j)*n+i+1:i*m+(j<2?j^1:j)+1, ti=j?i:i-1, tj=j?j:1;
			if(!j&&p[d][0]==i) {
				oc(i-1, 0, 0);
				oc(i-2, 0, 0);
				oc(i-2, 0, 0);
				oc(i-1, 0, 1);
				oc(i-2, 0, 0);
				break;
			}
			if(!p[d][0])
				oc(0, p[d][1]-(p[d][1]>0), !p[d][1]);
			if(!p[d][1])
				oc(p[d][0]-1, 0, 1);
			while(p[d][1]<tj)
				oc(p[d][0]-1, p[d][1], 1);
			while(p[d][1]>tj)
				oc(p[d][0]-1, p[d][1]-1, 0);
			while(p[d][0]<ti)
				oc(p[d][0], p[d][1]-1, 0);
		}
		oc(i-1, 0, 0);
	}
}

bool dfs(vector<int> &u) {
	bool ok=1;
	for(int i=0; i<5&&ok; ++i)
		ok=u[i]<u[i+1];
	if(ok)
		return 1;
	vis.insert(u);
	for(vector<int> &c : cs) {
		vector<int> v=u;
		ops.push_back({});
		for(int ci : c)
			ops.back().push_back(u[ci]);
		for(int i=c.size()-2; i>=0; --i)
			swap(v[c[i]], v[c[i+1]]);
		if(vis.find(v)==vis.end()&&dfs(v))
			return 1;
		ops.pop_back();
	}
	return 0;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	for(int i=0; i<n; ++i)
		for(int j=0; j<m; ++j)
			cin >> a[i][j], p[a[i][j]]={i, j};
	cr(0);
	for(int i=0; i<n; ++i)
		for(int j=i+1; j<m; ++j)
			swap(a[i][j], a[j][i]);
	for(int i=1; i<=n*m; ++i)
		swap(p[i][0], p[i][1]);
	swap(n, m);
	cr(1);
	vector<int> v;
	for(int j=0; j<3; ++j)
		for(int i=0; i<2; ++i)
			v.push_back(a[i][j]);
	dfs(v);
	cout << ops.size();
	for(vector<int> op : ops) {
		cout << "\n" << op.size();
		for(int oi : op)
			cout << " " << oi;
	}
}
