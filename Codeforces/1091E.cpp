#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=5e5;
int n, a[mxN+1], p;
ll st[1<<20], lz[1<<20], s;
map<int, int> mp;
vector<int> ans;

void app(int i, ll x) {
	st[i]+=x;
	lz[i]+=x;
}

void upd(int l1, int r1, ll x, int i=1, int l2=0, int r2=n) {
	if(l1<=l2&&r2<=r1) {
		app(i, x);
		return;
	}
	app(2*i, lz[i]);
	app(2*i+1, lz[i]);
	lz[i]=0;
	int m2=(l2+r2)/2;
	if(l1<=m2)
		upd(l1, r1, x, 2*i, l2, m2);
	if(m2<r1)
		upd(l1, r1, x, 2*i+1, m2+1, r2);
	st[i]=min(st[2*i], st[2*i+1]);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for(int i=0; i<n; ++i) {
		cin >> a[i];
		p^=a[i]&1;
	}
	a[n]=p;
	sort(a, a+n+1, greater<int>());
	for(int i=n; i>=0; --i) {
		upd(i, i, (ll)i*(i+1)+s);
		upd(i, n, -a[i]);
		++mp[a[i]];
		s+=a[i];
		while(1) {
			auto it=--mp.end();
			if(it->first<=i)
				break;
			mp[i]+=it->second;
			s-=it->second*(it->first-i);
			mp.erase(it);
		}
	}
	if(st[1]>=0)
		ans.push_back(p);
	for(int i=p, j=n; i<n; ++i) {
		while(j&&a[j-1]<=i)
			--j;
		if(i<j)
			upd(i, j-1, 1);
		upd(j, n, -1);
		if(i&1^p&&st[1]>=0)
			ans.push_back(i+1);
	}
	if(ans.size())
		for(int ai : ans)
			cout << ai << " ";
	else
		cout << -1;
}
