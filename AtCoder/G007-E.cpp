/*
	- Binary search by answer
	- Let dp[u][x] be the minimum length of a path coming back to u from a leaf if the length of the path from u to the first leaf is x
	- We can use merge-small-to-large to achieve a good time complexity
	- I have an extra log than the intended solution because I used binary search instead of two pointers
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=131071;
int n, lb, rb=1e7;
vector<array<int, 2>> c[mxN];
vector<array<ll, 2>> dp[mxN];

void dfs(int x, int u=0) {
	if(!c[u].size()) {
		dp[u]={{0, 0}};
		return;
	}
	dfs(x, c[u][0][0]);
	dfs(x, c[u][1][0]);
	if(dp[c[u][0][0]].size()>dp[c[u][1][0]].size())
		swap(c[u][0], c[u][1]);
	vector<array<ll, 2>> v1, v2;
	for(array<ll, 2> a : dp[c[u][0][0]]) {
		int p=lower_bound(dp[c[u][1][0]].begin(), dp[c[u][1][0]].end(), array<ll, 2>{x-a[1]-c[u][0][1]-c[u][1][1]+1})-dp[c[u][1][0]].begin()-1;
		if(~p) {
			v1.push_back({a[0]+c[u][0][1], dp[c[u][1][0]][p][1]+c[u][1][1]});
			if(!v2.size()||v2.back()[0]>dp[c[u][1][0]][p][1]+c[u][1][1])
				v2.push_back({dp[c[u][1][0]][p][1]+c[u][1][1], a[0]+c[u][0][1]});
		}
	}
	dp[u].clear();
	for(int i=0, j=v2.size(); i<v1.size()||j; ) {
		array<ll, 2> a;
		if(!j||(i<v1.size()&&v1[i]<v2[j-1]))
			a=v1[i++];
		else
			a=v2[--j];
		if(!dp[u].size()||dp[u].back()[1]>a[1])
			dp[u].push_back(a);
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for(int i=1, a, v; i<n; ++i) {
		cin >> a >> v, --a;
		c[a].push_back({i, v});
	}
	while(lb<rb) {
		int mb=(lb+rb)/2;
		dfs(mb);
		if(dp[0].size())
			rb=mb;
		else
			lb=mb+1;
	}
	cout << lb;
}
