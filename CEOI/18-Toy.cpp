/*
	- DFS through all possible divisor combinations
	- Optimizations
		- Only keep dividing by larger divisors to avoid visiting a state twice
		- Remove divisors that are not divisible by the number of the current state from all states that it branches to
*/

#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> p, ans;

void dfs(int x, vector<int> &p, int i, int s) {
	ans.push_back(s+x-1);
	vector<int> p2;
	for(; i<p.size(); ++i)
		if(x%p[i]==0)
			p2.push_back(p[i]);
	for(i=0; i<p2.size(); ++i)
		if(x/p2[i]>=p2[i])
			dfs(x/p2[i], p2, i, s+p2[i]-1);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=2; i*i<=n; ++i)
		if(n%i==0)
			p.push_back(i);
	dfs(n, p, 0, 0);
	sort(ans.begin(), ans.end());
	ans.resize(unique(ans.begin(), ans.end())-ans.begin());
	cout << ans.size() << "\n";
	for(int ai : ans)
		cout << ai << " ";
}
