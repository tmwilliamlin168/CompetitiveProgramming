#include <bits/stdc++.h>
using namespace std;

const int mxN=3e5;
int n, k, a[mxN+1], b[mxN+1], qu[mxN+1], qh, qt;
string s;
vector<int> fp[mxN+1], ft[mxN+1];

void upd(int i, int j, int x) {
	for(++i; i<=n; i+=i&-i)
		for(int j2=upper_bound(fp[i].begin(), fp[i].end(), j)-fp[i].begin(); j2<ft[i].size(); j2+=j2&-j2)
			ft[i][j2]=min(x, ft[i][j2]);
}

int qry(int i, int j) {
	int r=1e9;
	for(; i; i-=i&-i)
		for(int j2=lower_bound(fp[i].begin(), fp[i].end(), j)-fp[i].begin(); j2; j2-=j2&-j2)
			r=min(ft[i][j2], r);
	return r;
}

int main() {
	ifstream cin("redistricting.in");
	ofstream cout("redistricting.out");
	
	cin >> n >> k >> s;
	for(int i=n-1; i>=0; --i) {
		for(int j=i+1; j<=n; j+=j&-j)
			fp[j].push_back(a[i+1]);
		a[i]=a[i+1]+(s[i]=='H'?1:-1);
	}
	for(int i=1; i<=n; ++i) {
		sort(fp[i].begin(), fp[i].end());
		fp[i].resize(unique(fp[i].begin(), fp[i].end())-fp[i].begin());
		ft[i].resize(fp[i].size()+1, 1e9);
	}
	qu[qt++]=n;
	for(int i=n-1; i>=0; --i) {
		upd(i, a[i+1], b[i+1]);
		if(qu[qh]>i+k)
			++qh;
		b[i]=min(qry(min(i+k, n), a[i]), b[qu[qh]]+1);
		while(qt>qh&&b[i]<b[qu[qt-1]])
			--qt;
		qu[qt++]=i;
	}
	cout << b[0];
}
