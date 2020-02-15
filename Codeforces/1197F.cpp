#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define ar array
#define mat vector<vector<ll>>

const int mxN=1e3, M=998244353;
int n, a[mxN], m, f[3][3], l;
vector<ar<int, 2>> v[mxN];
map<ar<int, 3>, int> mp;
mat ta[3], tc[30];
ll dp[mxN+1][4];

mat matMul(mat a, mat b, ll m) {
	mat r(a.size(), vector<ll>(b[0].size()));
	for(int i=0; i<a.size(); ++i) {
		for(int k=0; k<a[0].size(); ++k) {
			for(int j=0; j<b[0].size(); ++j) {
				r[i][j]+=a[i][k]*b[k][j];
				if(r[i][j]>=m*m)
					r[i][j]-=m*m;
			}
		}
	}
	for(int i=0; i<r.size(); ++i)
		for(int j=0; j<r[0].size(); ++j)
			r[i][j]%=m;
	return r;
}

int mex(vector<int> v) {
	sort(v.begin(), v.end());
	v.resize(unique(v.begin(), v.end())-v.begin());
	for(int i=0; ; ++i)
		if(i>=v.size()||v[i]>i)
			return i;
}

ar<ll, 4> solve(int a, vector<ar<int, 2>> v) {
	v.push_back({0, 0});
	v.push_back({a+1, 0});
	sort(v.begin(), v.end());
	mat b=mat(l, vector<ll>(1));
	b[mp[{1, 2, 3}]][0]=1;
	for(int i=1; i<v.size(); ++i) {
		int p=v[i][0]-v[i-1][0]-1;
		for(int j=29; ~j; --j)
			if(p>>j&1)
				b=matMul(tc[j], b, M);
		if(i<v.size()-1)
			b=matMul(ta[v[i][1]], b, M);
	}
	ar<ll, 4> c{};
	for(auto a : mp)
		c[a.first[2]]=(c[a.first[2]]+b[a.second][0])%M;
	return c;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=0; i<n; ++i)
		cin >> a[i];
	cin >> m;
	for(int x, y, c; m--; ) {
		cin >> x >> y >> c, --x, --c;
		v[x].push_back({y, c});
	}
	for(int i=0; i<3; ++i)
		for(int j=0; j<3; ++j)
			cin >> f[i][j];
	for(int i=0; i<4; ++i)
		for(int j=0; j<4; ++j)
			for(int k=0; k<4; ++k)
				if((i>2)+(j>2)+(k>2)<2&&(i>1)+(j>1)+(k>1)<3)
					mp[{i, j, k}]=l++;
	for(int c=0; c<3; ++c) {
		ta[c]=mat(l, vector<ll>(l));
		for(auto a : mp) {
			vector<int> v;
			for(int i=0; i<3; ++i)
				if(f[c][i])
					v.push_back(a.first[2-i]);
			ta[c][mp[{a.first[1], a.first[2], mex(v)}]][a.second]=1;
		}
	}
	tc[0]=mat(l, vector<ll>(l));
	for(int i=0; i<l; ++i)
		for(int j=0; j<l; ++j)
			for(int k=0; k<3; ++k)
				tc[0][i][j]=(tc[0][i][j]+ta[k][i][j])%M;
	for(int i=1; i<30; ++i)
		tc[i]=matMul(tc[i-1], tc[i-1], M);
	dp[0][0]=1;
	for(int i=0; i<n; ++i) {
		ar<ll, 4> b=solve(a[i], v[i]);
		for(int j=0; j<4; ++j)
			for(int k=0; k<4; ++k)
				dp[i+1][j^k]=(dp[i+1][j^k]+dp[i][j]*b[k])%M;
	}
	cout << dp[n][0];
}
