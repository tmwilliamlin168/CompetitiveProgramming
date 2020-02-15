#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=1e5, M=1e9+7;
int n, ai, prv[mxN], l[mxN], r[mxN], mn[1<<18], mx[1<<18], lz[1<<18];
map<int, int> mp;
set<int> si;
ll ch[mxN], ans, rs, s[1<<18];
vector<array<int, 4>> bl[mxN], br[mxN];

void app(int i, int x, int l2, int r2) {
	s[i]+=(ll)(r2-l2+1)*x;
	mn[i]+=x;
	mx[i]+=x;
	lz[i]+=x;
}

void psh(int i, int l2, int m2, int r2) {
	app(2*i, lz[i], l2, m2);
	app(2*i+1, lz[i], m2+1, r2);
	lz[i]=0;
}

void upd(int l1, int r1, int x, int i=1, int l2=1, int r2=n-2) {
	if(l1<=l2&&r2<=r1&&(mn[i]+x>=0||mx[i]==mn[i])) {
		app(i, max(x, -mn[i]), l2, r2);
		return;
	}
	int m2=(l2+r2)/2;
	psh(i, l2, m2, r2);
	if(l1<=m2)
		upd(l1, r1, x, 2*i, l2, m2);
	if(m2<r1)
		upd(l1, r1, x, 2*i+1, m2+1, r2);
	s[i]=s[2*i]+s[2*i+1];
	mn[i]=min(mn[2*i], mn[2*i+1]);
	mx[i]=max(mx[2*i], mx[2*i+1]);
}

ll qry(int l1, int r1, int i=1, int l2=1, int r2=n-2) {
	if(l1<=l2&&r2<=r1)
		return s[i];
	int m2=(l2+r2)/2;
	psh(i, l2, m2, r2);
	return (l1<=m2?qry(l1, r1, 2*i, l2, m2):0)+(m2<r1?qry(l1, r1, 2*i+1, m2+1, r2):0);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=0; i<n; ++i) {
		cin >> ai;
		prv[i]=mp.find(ai)==mp.end()?-1:mp[ai];
		mp[ai]=i;
	}
	si.insert(0);
	si.insert(1);
	for(int i=2; i<n; ++i) {
		si.erase(i-1);
		br[i-1].push_back({*si.rbegin()+1, i-1, i, 1});
		si.insert(i);
		if(prv[i]>0) {
			auto it=si.lower_bound(prv[i]);
			int r=*it-1, l=*--it+1;
			if(prv[i]-l<r-prv[i])
				for(int j=l; j<=prv[i]; ++j)
					bl[j].push_back({prv[i], r, i, -1});
			else
				for(int j=prv[i]; j<=r; ++j)
					br[j].push_back({l, prv[i], i, -1});
			si.insert(prv[i]);
		}
	}
	for(int i=n-2; i>0; --i) {
		upd(i, i, i-prv[i]);
		upd(i, n-2, -1);
		r[i]=i+1;
		while(r[i]<n-1&&prv[i]>prv[r[i]]) {
			upd(r[i], r[r[i]]-1, prv[r[i]]-prv[i]);
			r[i]=r[r[i]];
		}
		for(array<int, 4> a : bl[i])
			ch[a[2]]+=a[3]*qry(a[0], a[1]);
	}
	memset(s, 0, sizeof(s));
	memset(mn, 0, sizeof(mn));
	memset(mx, 0, sizeof(mx));
	memset(lz, 0, sizeof(lz));
	for(int i=1; i<n-1; ++i) {
		upd(i, i, i-prv[i]-1);
		l[i]=i-1;
		while(l[i]&&prv[i]>prv[l[i]]) {
			upd(l[l[i]]+1, l[i], prv[l[i]]-prv[i]);
			l[i]=l[l[i]];
		}
		for(array<int, 4> a : br[i])
			ch[a[2]]+=a[3]*qry(a[0], a[1]);
	}
	for(int i=2; i<n; ++i) {
		rs=(rs+ch[i]%M+M)%M;
		ans=(ans+rs)%M;
	}
	cout << ans;
}
