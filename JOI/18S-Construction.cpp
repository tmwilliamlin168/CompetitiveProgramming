/*
	- We can find inversions in an array in O(nlogn)
	- Use HLD to reduce tree into chains
	- We will group neighboring elements with the same value to optimize
	- Entire process becomes O(nlog^2n) amortized
		- If you have to process a lot of elements with different values, they will become the same after the process
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5;
int n, c[mxN], a[mxN], b[mxN], p[mxN], pr[mxN], ap[mxN], hv[mxN], ft[mxN+1];
vector<int> adj[mxN];
map<int, int> mp;
vector<array<int, 3>> v;

int dfs(int u=0) {
	int s=1, mcs=0;
	for(int v : adj[u]) {
		int cs=dfs(v);
		if(cs>mcs) {
			hv[u]=v;
			mcs=cs;
		}
		s+=cs;
	}
	return s;
}

void upd(int i, int x) {
	for(++i; i<=v.size(); i+=i&-i)
		ft[i]+=x;
}

int qry(int i) {
	int r=0;
	for(; i; i-=i&-i)
		r+=ft[i];
	return r;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for(int i=0; i<n; ++i)
		cin >> c[i];
	for(int i=1; i<n; ++i) {
		cin >> a[i] >> b[i], --a[i], --b[i];
		p[b[i]]=a[i];
		adj[a[i]].push_back(b[i]);
	}
	memset(hv, -1, 4*n);
	p[0]=-1;
	dfs();
	for(int i=0, j=0; i<n; ++i) {
		if(i&&hv[p[i]]==i)
			continue;
		for(int k=i; k!=-1; k=hv[k]) {
			pr[k]=i;
			mp[j]=c[k];
			ap[k]=j++;
		}
	}
	mp[n]=-1;
	for(int i=1; i<n; ++i) {
		for(; a[i]!=-1; a[i]=p[pr[a[i]]]) {
			mp.insert({ap[pr[a[i]]], (--mp.upper_bound(ap[pr[a[i]]]))->second});
			auto it=mp.insert({ap[a[i]]+1, (--mp.upper_bound(ap[a[i]]+1))->second}).first;
			for(int lc=ap[a[i]]+1; lc>ap[pr[a[i]]]; ) {
				v.push_back({(--it)->second, v.size(), lc-it->first});
				lc=it->first;
				it=mp.erase(it);
			}
			mp[ap[pr[a[i]]]]=c[b[i]];
		}
		sort(v.begin(), v.end());
		long long ans=0;
		for(int j=0; j<v.size(); ) {
			int k=j;
			while(++k<v.size()&&v[k][0]==v[j][0]);
			for(int l=j; l<k; ++l)
				ans+=(long long)qry(v[l][1])*v[l][2];
			for(int l=j; l<k; ++l)
				upd(v[l][1], v[l][2]);
			j=k;
		}
		for(array<int, 3> vi : v)
			upd(vi[1], -vi[2]);
		v.clear();
		cout << ans << "\n";
	}
}
