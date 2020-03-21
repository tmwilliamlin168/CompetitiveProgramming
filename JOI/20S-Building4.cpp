#include <bits/stdc++.h>
using namespace std;

const int mxN=5e5;
int n;
pair<int, char> p[2][2*mxN];
bool b[2][2*mxN];
char ans[2*mxN];
vector<array<int, 4>> r;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int j : {0, 1}) {
		for(int i=0; i<2*n; ++i) {
			cin >> p[j][i].first;
			p[j][i].second='A'+j;
		}
	}
	for(int i=0; i<2*n; ++i) {
		if(p[0][i].first>p[1][i].first)
			swap(p[0][i], p[1][i]);
		if(i) {
			if(p[0][i-1].first>p[1][i].first) {
				cout << -1;
				return 0;
			}
			if(p[1][i-1].first>p[1][i].first) {
				b[0][i-1]=1;
			}
			if(p[0][i].first<p[0][i-1].first) {
				b[1][i]=1;
			}
			if(p[0][i].first<p[1][i-1].first) {
				//must choose 1 of (1, i) or (0, i-1)
				if(b[1][i-1])
					b[1][i]=1;
			}
		}
	}
	for(int i=2*n-1; i; --i) {
		if(p[0][i].first<p[1][i-1].first) {
			if(b[0][i])
				b[0][i-1]=1;
		}
	}
	for(int i=0; i<2*n; ++i) {
		if(b[0][i]&&b[1][i]) {
			cout << -1;
			return 0;
		}
	}
	int l[2]={n, n};
	for(int i=0; i<2*n; ++i) {
		for(int j : {0, 1}) {
			if(b[j][i]) {
				ans[i]=p[j][i].second;
				--l[p[j][i].second-'A'];
			}
		}
	}
	int mns=0, mxs=0;
	for(int i=0, j=0; i<2*n; i=j) {
		if(b[0][i]||b[1][i]) {
			++j;
			continue;
		}
		for(++j; j<2*n&&!b[0][j]&&!b[1][j]&&p[0][j].first<p[1][j-1].first; ++j);
		int c=0;
		for(int k=i; k<j; ++k)
			c+=p[0][k].second=='A';
		int mn=c, mx=c;
		for(int k=j-1; k>=i; --k) {
			c-=p[0][k].second=='A';
			c+=p[1][k].second=='A';
			mn=min(mn, c);
			mx=max(mx, c);
		}
		r.push_back({i, j, mn, mx});
		mns+=mn;
		mxs+=mx;
	}
	if(l[0]<mns||l[0]>mxs) {
		cout << -1;
		return 0;
	}
	l[0]-=mns;
	for(array<int, 4> ri : r) {
		int need=min(l[0], ri[3]-ri[2]);
		l[0]-=need;
		int c=0;
		for(int k=ri[0]; k<ri[1]; ++k) {
			c+=p[0][k].second=='A';
			ans[k]=p[0][k].second;
		}
		if(c-ri[2]==need)
			continue;
		for(int k=ri[1]-1; k>=ri[0]; --k) {
			c-=p[0][k].second=='A';
			c+=p[1][k].second=='A';
			ans[k]=p[1][k].second;
			if(c-ri[2]==need) {
				break;
			}
		}
	}
	for(int i=0; i<2*n; ++i)
		cout << ans[i];
}
