#include <bits/stdc++.h>
using namespace std;

#define ll long long

int n, k, m, kl;
vector<ll> p[100000];
ll base, fd[100000], mc, tc;

void solve(int i, ll cl) {
	if(!kl)
		return;
	if(i>=0)
		i=upper_bound(fd, fd+i+1, cl)-fd-1;
	if(i<0) {
		tc+=cl+1;
		--kl;
	} else {
		solve(i-1, cl);
		for(int j : p[i])
			if(j<=cl)
				solve(i-1, cl-j);
	}
}

int main() {
	//freopen("roboherd.in", "r", stdin);
	//freopen("roboherd.out", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> k;
	for(int i=0; i<n; ++i) {
		cin >> m;
		p[i].resize(m);
		for(int j=0; j<m; ++j)
			cin >> p[i][j];
		sort(p[i].begin(), p[i].end());
		base+=p[i][0];
		if(m==1) {
			--i;
			--n;
			continue;
		}
		for(int j=1; j<m; ++j)
			p[i][j]-=p[i][0];
		p[i].erase(p[i].begin());
	}
	sort(p, p+n);
	for(int i=0; i<n; ++i)
		fd[i]=p[i][0];
	ll l=0, r=1e13;
	while(l<=r) {
		mc=(l+r)/2;
		kl=k;
		solve(n-1, mc);
		if(kl)
			l=mc+1;
		else
			r=mc-1;
	}
	kl=k;
	tc=0;
	solve(n-1, l-1);
	cout << (base+l)*k-tc;
}
