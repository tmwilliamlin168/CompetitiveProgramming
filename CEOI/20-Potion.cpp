#include <bits/stdc++.h>
using namespace std;

#define ar array

const int mxN=1e5, B=10;
int n, d, u, q;
ar<int, 2> h[mxN];
map<ar<int, 2>, int> mp;
vector<ar<int, 3>> v[mxN];
vector<int> s[mxN];
vector<vector<int>> t[mxN], t2[mxN];

void pe(int a, int b, int i) {
	int& c=mp[{a, b}];
	if(c) {
		v[a].push_back({b, c, i});
		c=0;
	} else
		c=i;
}

int gi(int i, int j) {
	return upper_bound(s[i].begin(), s[i].end(), j)-s[i].begin()-1;
}

vector<int> mrg(vector<int>& a, vector<int>& b) {
	vector<int> r;
	for(int i=0, j=0; i<a.size()||j<b.size(); ) {
		if(j>=b.size()||(i<a.size()&&a[i]<b[j]))
			r.push_back(a[i++]);
		else
			r.push_back(b[j++]);
	}
	return r;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> d >> u >> q;
	for(int i=0; i<n; ++i) {
		cin >> h[i][0];
		h[i][1]=i;
	}
	sort(h, h+n);
	for(int i=1, a, b; i<=u; ++i) {
		cin >> a >> b;
		pe(a, b, i);
		pe(b, a, i);
	}
	for(auto p : mp)
		if(p.second)
			pe(p.first[0], p.first[1], u+1);
	for(int i=0; i<n; ++i)
		s[i]={0, u+1};
	for(int i=0; i<n; ++i) {
		for(auto a : v[i]) {
			s[a[0]].push_back(a[1]);
			s[a[0]].push_back(a[2]);
		}
	}
	for(int i=0; i<n; ++i) {
		sort(s[i].begin(), s[i].end());
		s[i].resize(unique(s[i].begin(), s[i].end())-s[i].begin());
		t[i].resize(s[i].size()-1);
		t2[i].resize((t[i].size()-1)/B+1);
	}
	for(int i=0; i<n; ++i) {
		for(auto a : v[h[i][1]]) {
			for(int j=gi(a[0], a[1]); s[a[0]][j]<a[2]; ++j) {
				if(j%B<1&&j+B<s[a[0]].size()&&s[a[0]][j+B]<=a[2]) {
					t2[a[0]][j/B].push_back(h[i][0]);
					j+=B-1;
				} else
					t[a[0]][j].push_back(h[i][0]);
			}
		}
	}
	for(int x, y, v; q--; ) {
		cin >> x >> y >> v;
		vector<int>& a1=t[x][gi(x, v)], a2=t2[x][gi(x, v)/B], b1=t[y][gi(y, v)], b2=t2[y][gi(y, v)/B], a=mrg(a1, a2), b=mrg(b1, b2);
		int ans=1e9;
		for(int i=0, j=0; i<a.size(); ++i) {
			while(j<b.size()&&b[j]<a[i])
				++j;
			if(j)
				ans=min(a[i]-b[j-1], ans);
			if(j<b.size())
				ans=min(b[j]-a[i], ans);
		}
		cout << ans << endl;
	}
}
