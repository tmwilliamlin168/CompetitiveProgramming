#include <bits/stdc++.h>
using namespace std;

#define ar array

const int mxN=1e3;
int n[2], m, m2, ans, bad, c2[4*mxN];
string s[2][mxN][3], s2;
ar<int, 3> a[2][mxN];
map<string, int> mp[2];
vector<ar<int, 2>> m1[6*mxN];
short d[4*mxN][4*mxN];
vector<vector<int>> e[4*mxN];

int gi(string s, map<string, int>& mp) {
	auto a=mp.insert({s, m});
	m+=a.second;
	return a.first->second;
}

void am1(int a, int b, int x) {
	for(int k : {0, 1}) {
		bad-=(m1[a].size()>1)+(a<m2&&m1[a].size()&&e[a][c2[a]].size()&&find(e[a][c2[a]].begin(), e[a][c2[a]].end(), m1[a][0][0])==e[a][c2[a]].end());
		int p=0;
		while(p<m1[a].size()&&m1[a][p][0]^b)
			++p;
		if(p>=m1[a].size())
			m1[a].push_back({b, 0});
		m1[a][p][1]+=x;
		if(!m1[a][p][1])
			m1[a].erase(m1[a].begin()+p);
		bad+=(m1[a].size()>1)+(a<m2&&m1[a].size()&&e[a][c2[a]].size()&&find(e[a][c2[a]].begin(), e[a][c2[a]].end(), m1[a][0][0])==e[a][c2[a]].end());
		swap(a, b);
	}
}

void am2(int a, int b, int c, int x) {
	if(e[a][c2[a]].size()==1)
		am1(a, e[a][c2[a]][0], -1);
	bad-=(c2[a]&&!e[a][c2[a]].size())+(m1[a].size()&&e[a][c2[a]].size()&&find(e[a][c2[a]].begin(), e[a][c2[a]].end(), m1[a][0][0])==e[a][c2[a]].end());
	c2[a]+=x;
	if(c2[a]>=e[a].size())
		e[a].push_back({});
	d[a][b]+=x;
	if(d[a][b])
		e[a][d[a][b]].push_back(b);
	d[a][c]+=x;
	if(d[a][c])
		e[a][d[a][c]].push_back(c);
	vector<int> f;
	for(int g : e[a][c2[a]])
		if(d[a][g]==c2[a]&&find(f.begin(), f.end(), g)==f.end())
			f.push_back(g);
	e[a][c2[a]]=f;
	bad+=(c2[a]&&!f.size())+(m1[a].size()&&f.size()&&find(f.begin(), f.end(), m1[a][0][0])==f.end());
	if(f.size()==1)
		am1(a, f[0], 1);
}

void upd(ar<int, 3> a, ar<int, 3> b, int x) {
	am1(a[0], b[0], x);
	if(a[1]^a[2]) {
		if(b[1]^b[2]) {
			am2(a[1], b[1], b[2], x);
			am2(a[2], b[1], b[2], x);
			am2(b[1], a[1], a[2], x);
			am2(b[2], a[1], a[2], x);
		} else
			bad+=x;
	} else if(b[1]^b[2])
		bad+=x;
	else
		am1(a[1], b[1], x);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n[0] >> n[1];
	for(int k : {0, 1}) {
		for(int i=0; i<n[k]; ++i) {
			cin >> s[k][i][0] >> s2 >> s[k][i][1] >> s2 >> s[k][i][2];
			for(int j : {1, 2})
				a[k][i][j]=gi(s[k][i][j], mp[k]);
		}
	}
	m2=m;
	for(int i=0; i<m; ++i)
		e[i]={{}};
	for(int k : {0, 1})
		for(int i=0; i<n[k]; ++i)
			a[k][i][0]=gi(s[k][i][0], mp[k]);
	for(int o=1-n[0]; o<n[1]; ++o) {
		for(int i=max(0, -o), j=i; i<n[0]&&i+o<n[1]; ++i) {
			upd(a[0][i], a[1][i+o], 1);
			for(; bad; ++j)
				upd(a[0][j], a[1][j+o], -1);
			ans=max(i-j+1, ans);
			if(i+1>=n[0]||i+1+o>=n[1])
				for(; j<=i; ++j)
					upd(a[0][j], a[1][j+o], -1);
		}
	}
	cout << ans;
}
