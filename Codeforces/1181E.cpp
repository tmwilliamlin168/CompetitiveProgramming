#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5;
int n, d[mxN];
array<array<int, 2>, 4> s[mxN];

bool dc(array<vector<int>, 4> v) {
	for(int i=0; i<4; ++i)
		reverse(v[i].begin(), v[i].end());
	for(int i : v[0])
		d[i]=-1;
	vector<array<vector<int>, 4>> vl;
	vector<int> ab[4];
	int r[4];
	while(1) {
		memset(r, 0xc0, 16);
		bool fs=0;
		while(!fs) {
			for(int j=0; j<4; ++j) {
				while(v[j].size()&&~d[v[j].back()]) {
					vl[d[v[j].back()]][j].push_back(v[j].back());
					v[j].pop_back();
				}
				if(v[j].empty()) {
					fs=1;
					continue;
				}
				if(ab[j].size()&&s[v[j].back()][j][0]>=r[j]) {
					for(int k : ab[j])
						d[k]=vl.size();
					fs=1;
					break;
				}
				ab[j].push_back(v[j].back());
				r[j]=max(s[v[j].back()][j][1], r[j]);
				v[j].pop_back();
			}
		}
		if(!v[3].size()) {
			if(ab[3].size()>1)
				return 0;
			break;
		}
		for(int j=0; j<4; ++j) {
			while(ab[j].size()) {
				v[j].push_back(ab[j].back());
				ab[j].pop_back();
			}
		}
		vl.push_back({});
	}
	for(array<vector<int>, 4> v : vl)
		if(!dc(v))
			return 0;
	return 1;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for(int i=0, a, b, c, d; i<n; ++i) {
		cin >> a >> b >> c >> d;
		s[i]={{{a, c}, {-c, -a}, {b, d}, {-d, -b}}};
	}
	array<vector<int>, 4> v;
	for(int i=0; i<4; ++i) {
		v[i]=vector<int>(n);
		iota(v[i].begin(), v[i].end(), 0);
		sort(v[i].begin(), v[i].end(), [&](const int &a, const int &b) {
			return s[a][i][0]<s[b][i][0];
		});
	}
	cout << (dc(v)?"YES":"NO");
}
