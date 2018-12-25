#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=1e5, bs=300, bc=mxN/bs+1;
int n, ai, bi, mb;
ll w, a[mxN+1], lz[bc];
vector<int> v[mxN+2];

struct cht {
	int a[bs], qh, qt;
	ll b[bs];
	void al(int ai, ll bi) {
		while(qt-qh>1&&(b[qt-1]-b[qt-2])*(a[qt-2]-ai)>(bi-b[qt-2])*(a[qt-2]-a[qt-1]))
			--qt;
		a[qt]=ai, b[qt]=bi, ++qt;
	}
	pair<ll, int> qry(ll x) {
		while(qt-qh>1&&a[qh]*x+b[qh]<a[qh+1]*x+b[qh+1])
			++qh;
		return {a[qh]*x+b[qh], a[qh]};
	}
} cs[bc];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> w;
	for(int i=0; i<n; ++i) {
		cin >> ai >> bi;
		v[bi].push_back(ai);
		mb=max(bi, mb);
	}
	auto pb=[&](int i) {
		cs[i].qh=cs[i].qt=0;
		for(int j=i*bs; j<=min((i+1)*bs-1, mxN); ++j)
			cs[i].al(j, a[j]);
	};
	for(int i=0; i<bc; ++i)
		pb(i);
	for(int i=0, nl=n; i<mb+2; ++i) {
		pair<ll, int> a1{};
		for(int j=0; j<bc; ++j)
			a1=max(cs[j].qry(lz[j]), a1);
		cout << a1.first+w*i*nl << " " << a1.second << "\n";
		for(int vi : v[i]) {
			for(int j=0; j+bs<=vi; j+=bs)
				++lz[j/bs];
			for(int j=vi/bs*bs; j<=min((vi/bs+1)*bs-1, mxN); ++j)
				a[j]+=(lz[vi/bs]+(j<=vi))*j;
			lz[vi/bs]=0;
			pb(vi/bs);
		}
		nl-=v[i].size();	
	}
}
