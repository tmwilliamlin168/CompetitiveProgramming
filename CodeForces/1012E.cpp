#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second

const int mxN=2e5;
int n, s, a[mxN];
map<int, int> mp1;
map<int, vector<int>> mp2;
vector<vector<int>> ans;

void dfs(int u) {
	while(!mp2[u].empty()) {
		int i=mp2[u].back();
		mp2[u].pop_back();
		dfs(a[i]);
		ans.back().push_back(i);
	}
	mp2.erase(u);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> s;
	for(int i=0; i<n; ++i) {
		cin >> a[i];
		++mp1[a[i]];
	}
	int j=0;
	for(auto it=mp1.begin(); it!=mp1.end(); ++it) {
		for(int i=j; i<j+it->se; ++i)
			if(a[i]!=it->fi)
				mp2[it->fi].push_back(i);
		j+=it->se;
	}
	while(!mp2.empty()) {
		ans.push_back(vector<int>());
		dfs(mp2.begin()->fi);
		reverse(ans.back().begin(), ans.back().end());
		s-=ans.back().size();
	}
	if(s<0) {
		cout << -1;
		return 0;
	}
	int b=min(s, (int)ans.size()), d=0;
	cout << ans.size()-(b>=3?b-2:0) << "\n";
	if(b>=3) {
		for(int i=0; i<b; ++i)
			d+=ans[i].size();
		cout << d << "\n";
		for(int i=0; i<b; ++i)
			for(int c : ans[i])
				cout << c+1 << " ";
		cout << "\n" << b << "\n";
		for(int i=b-1; i>=0; --i)
			cout << ans[i][0]+1 << " ";
		cout << "\n";
	}
	for(int i=(b>=3?b:0); i<ans.size(); ++i) {
		cout << ans[i].size() << "\n";
		for(int c : ans[i])
			cout << c+1 << " ";
		cout << "\n";
	}
}
