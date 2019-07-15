#include <bits/stdc++.h>
using namespace std;

const int mxM=1e5, mxN=6.4e5, di[4]={-1, 1, 0, 0}, dj[4]={0, 0, -1, 1};
int m, r, c, n, b[mxN], a[mxM], ml[16], nb[mxN][4], vis[mxN];
string d;
array<int, 2> ans{1<<30};
unordered_map<int, int> ss[mxN];
vector<int> ta;

int dfs(int u, int s) {
	vis[u]=s;
	ss[u][u]=-1;
	vector<int> ca;
	for(int k=0; k<4; ++k) {
		int v=nb[u][k^1];
		if(v<0)
			continue;
		ss[u].insert(make_pair(v, 1<<k));
		if(ml[1<<k]>=b[v])
			ca.push_back(v);
	}
	while(ca.size()) {
		int v=ca.back();
		ca.pop_back();
		if(~vis[v]) {
			if(vis[v]^s)
				return -1;
			else {
				auto it=ss[u].find(v);
				if(it!=ss[u].end()&&it->second<0)
					continue;
				if(ca.size()>ta.size())
					swap(ta, ca);
				ta.insert(ta.end(), ca.begin(), ca.end());
				return v;
			}
		}
		ss[u][v]=-1;
		int w=dfs(v, s);
		if(w==-1)
			return -1;
		if(ss[v].size()>ss[u].size())
			swap(ss[v], ss[u]);
		for(pair<int, int> x : ss[v]) {
			auto it=ss[u].insert(make_pair(x.first, 0)).first;
			int y=it->second|x.second;
			if(y>=0&&ml[it->second]<b[x.first]&&ml[x.second]<b[x.first]&&ml[y]>=b[x.first])
				ta.push_back(x.first);
			it->second=y;
		}
		unordered_map<int, int>().swap(ss[v]);
		auto it=ss[u].find(w);
		if(it==ss[u].end()||it->second>=0) {
			if(ca.size()>ta.size())
				swap(ta, ca);
			ta.insert(ta.end(), ca.begin(), ca.end());
			return w;
		}
		ca.insert(ca.end(), ta.begin(), ta.end());
		ta.clear();
	}
	int cs=0;
	for(pair<int, int> p : ss[u])
		if(p.second<0)
			++cs;
	if(ans[0]>cs)
		ans={cs, 0};
	if(ans[0]==cs)
		ans[1]+=cs;
	return -1;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> m >> r >> c >> d, n=r*c;
	for(int i=0; i<r; ++i) {
		for(int j=0; j<c; ++j) {
			cin >> b[i*c+j];
			b[i*c+j]=b[i*c+j]?min(b[i*c+j], m):1e9;
			for(int k=0; k<4; ++k) {
				int ni=i+di[k], nj=j+dj[k];
				nb[i*c+j][k]=0<=ni&&ni<r&&0<=nj&&nj<c?ni*c+nj:-1;
			}
		}
	}
	for(int i=0; i<16; ++i) {
		for(int j=0; j<m; ++j)
			a[j]=i&1&&d[j]=='N'||i&2&&d[j]=='S'||i&4&&d[j]=='W'||i&8&&d[j]=='E';
		for(int j=0, k=0; j<m; j=k) {
			for(; k<m&&a[k]==a[j]; ++k);
			if(a[j])
				ml[i]=max(k-j, ml[i]);
		}
		if(ml[i]<m) {
			int l=0, r=m-1;
			while(a[l])
				++l;
			while(a[r])
				--r;
			ml[i]=max(m-(r-l+1), ml[i]);
		}
	}
	memset(vis, -1, 4*n);
	for(int s=0; s<n; ++s)
		if(vis[s]<0&&b[s]<=m)
			dfs(s, s);
	cout << ans[0] << "\n" << ans[1];
}
