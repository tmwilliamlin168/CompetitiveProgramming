#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5;
int n, q, s[mxN], t[mxN], x, a[mxN], b[mxN], c[mxN], ans[mxN];
vector<int> vs, vt[mxN+1], ft[mxN+1];
array<int, 2> d[mxN], e[mxN];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> q;
	for(int i=0; i<n; ++i) {
		cin >> s[i] >> t[i], s[i]=-s[i], t[i]=-t[i];
		vs.push_back(s[i]);
		d[i]={s[i]+t[i], i};
	}
	sort(vs.begin(), vs.end());
	vs.resize(x=unique(vs.begin(), vs.end())-vs.begin());
	for(int i=0; i<n; ++i) {
		s[i]=lower_bound(vs.begin(), vs.end(), s[i])-vs.begin();
		for(int j=s[i]+1; j<=x; j+=j&-j)
			vt[j].push_back(t[i]);
	}
	for(int i=1; i<=x; ++i) {
		sort(vt[i].begin(), vt[i].end());
		vt[i].resize(unique(vt[i].begin(), vt[i].end())-vt[i].begin());
		ft[i].resize(vt[i].size()+1);
	}
	sort(d, d+n);
	for(int i=0; i<q; ++i) {
		cin >> a[i] >> b[i] >> c[i], a[i]=-a[i], b[i]=-b[i], c[i]=-c[i];
		e[i]={c[i], i};
	}
	sort(e, e+q);
	for(int i1=0, i2=0; i1<q; ++i1) {
		while(i2<n&&d[i2][0]<=e[i1][0]) {
			for(int i=s[d[i2][1]]+1; i<=x; i+=i&-i)
				for(int j=lower_bound(vt[i].begin(), vt[i].end(), t[d[i2][1]])-vt[i].begin()+1; j<=vt[i].size(); j+=j&-j)
					ft[i][j]++;
			++i2;
		}
		for(int i=upper_bound(vs.begin(), vs.end(), a[e[i1][1]])-vs.begin(); i; i-=i&-i)
			for(int j=upper_bound(vt[i].begin(), vt[i].end(), b[e[i1][1]])-vt[i].begin(); j; j-=j&-j)
				ans[e[i1][1]]+=ft[i][j];
	}
	for(int i=0; i<q; ++i)
		cout << ans[i] << "\n";
}
