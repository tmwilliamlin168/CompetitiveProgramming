/*
	- https://codeforces.com/blog/entry/59650
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=3e5;
int n, p[mxN], p2[mxN], a[mxN], k=30;
ll x[mxN], y[mxN], r[mxN];
unordered_map<int, vector<int>> mp;

struct cmp1 {
	__attribute__((always_inline)) bool operator()(const int &a, const int &b) {
		return y[a]>>k<b;
	}
};

void rs(int k) {
	mp.clear();
	for(int i=0; i<n; ++i)
		if(a[p2[i]]==-1)
			mp[x[p2[i]]>>k].push_back(p2[i]);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=0; i<n; ++i) {
		cin >> x[i] >> y[i] >> r[i];
		p[i]=p2[i]=i;
	}
	sort(p, p+n, [&](const int &a, const int &b) {
		return r[a]==r[b]?a<b:r[a]>r[b];
	});
	sort(p2, p2+n, [&](const int &a, const int &b) {
		return y[a]<y[b];
	});
	memset(a, -1, 4*n);
	for(int i=-1; i+1<n; --i, --k) {
		rs(k);
		while(++i<n&&r[p[i]]>=1<<(k-1)) {
			if(a[p[i]]!=-1)
				continue;
			for(ll b=(x[p[i]]>>k)-2; b<=(x[p[i]]>>k)+2; ++b) {
				auto mf=mp.find(b);
				if(mf==mp.end())
					continue;
				vector<int> &v=mf->second;
				for(int j=lower_bound(v.begin(), v.end(), (y[p[i]]>>k)-2, cmp1())-v.begin(); j<v.size()&&y[v[j]]>>k<=(y[p[i]]>>k)+2; ++j) {
					ll dx=x[p[i]]-x[v[j]], dy=y[p[i]]-y[v[j]], rs=r[p[i]]+r[v[j]];
					if(dx*dx+dy*dy<=rs*rs&&a[v[j]]==-1)
						a[v[j]]=p[i];
				}
			}
		}
	}
	for(int i=0; i<n; ++i)
		cout << a[i]+1 << " ";
}
