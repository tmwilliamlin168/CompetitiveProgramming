/*
	- The last animal can be found by looking at the first (or last) cell
	- Set the active group of cells to the first (or last) cell
	- While the active group of cells is not empty
		- Do a DFS from those cells
			- Only go to cells of the same animal
			- Mark cells and don't revisit them
			- If any neighbors are unmarked but of a different animal, add them to the next group of cells
	- The answer is the number of iterations
	- Hard to prove, but kind of intuitive
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=4e3;
int n, m, ans, nb[4][2]={{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
string g[mxN];
vector<array<int, 2>> tp[2];

bool a(int i, int j) {
	return i>=0&&i<n&&j>=0&&j<m&&g[i][j]!='.';
}

void dfs(int i, int j) {
	char pc=g[i][j];
	g[i][j]='.';
	for(int k=0; k<4; ++k) {
		int ni=i+nb[k][0], nj=j+nb[k][1];
		if(!a(ni, nj))
			continue;
		if(g[ni][nj]==pc)
			dfs(ni, nj);
		else
			tp[ans&1^1].push_back({ni, nj});
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	for(int i=0; i<n; ++i)
		cin >> g[i];
	tp[0].push_back({0, 0});
	for(; tp[ans&1].size(); ++ans) {
		for(array<int, 2> u : tp[ans&1])
			if(a(u[0], u[1]))
				dfs(u[0], u[1]);
		tp[ans&1].clear();
	}
	cout << ans;
}
