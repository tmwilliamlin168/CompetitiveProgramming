#include <bits/stdc++.h>
using namespace std;

const int mxN=3e5;
int t, n, q, ki, ci, oc[mxN];
vector<array<int, 2>> b[mxN];

bool solve() {
	cin >> n >> q;
	vector<vector<int>> va, vb;
	while(q--) {
		cin >> ki;
		vector<int> v;
		while(ki--) {
			cin >> ci, --ci;
			v.push_back(ci);
		}
		if(v.size()>500)
			va.push_back(v);
		else
			vb.push_back(v);
	}
	for(vector<int> v : va) {
		memset(oc, -1, 4*n);
		for(int j=0; j<v.size(); ++j)
			oc[v[j]]=j;
		auto a=[&](vector<int> &w) {
			int fo=INT_MAX;
			for(int j=0; j<w.size(); ++j) {
				if(oc[w[j]]>fo&&v[oc[w[j]]-1]!=w[j-1])
					return 0;
				if(oc[w[j]]!=-1)
					fo=min(oc[w[j]], fo);
			}
			return 1;
		};
		for(vector<int> &w : va)
			if(!a(w))
				return 0;
		for(vector<int> &w : vb)
			if(!a(w))
				return 0;
	}
	for(int i=0; i<n; ++i)
		b[i].clear();
	for(int i=0; i<vb.size(); ++i)
		for(int j=0; j<vb[i].size(); ++j)
			b[vb[i][j]].push_back({i, j});
	memset(oc, -1, 4*n);
	for(int i=0; i<n; ++i) {
		for(array<int, 2> a : b[i]) {
			for(int j=a[1]+1; j<vb[a[0]].size(); ++j) {
				if(oc[vb[a[0]][j]]!=-1&&oc[vb[a[0]][j]]!=vb[a[0]][j-1])
					return 0;
				oc[vb[a[0]][j]]=vb[a[0]][j-1];
			}
		}
		for(array<int, 2> a : b[i])
			for(int j=a[1]+1; j<vb[a[0]].size(); ++j)
				oc[vb[a[0]][j]]=-1;
	}
	return 1;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> t;
	while(t--)
		cout << (solve()?"Robot":"Human") << "\n";
}
