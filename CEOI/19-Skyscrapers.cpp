#include <bits/stdc++.h>
using namespace std;
 
const int mxN=1.5e5, mxM=2*mxN+2, INF=2e9, dx[8]={-1, -1, 0, 1, 1, 1, 0, -1}, dy[8]={0, 1, 1, 1, 0, -1, -1, -1};
int n, t, m, x[mxM], yl[mxM], yr[mxM], ans[mxN], p[mxN+mxM], adj[mxN][8], d[13];
array<int, 2> a[mxN];
array<int, 3> b[mxN];
map<int, vector<array<int, 2>>> mp;
vector<int> v[mxN+mxM];
set<int> s;
bool ia[mxN], vis[mxN], c1[mxN], c2[mxN];

void fk() {
	cout << "NO";
	exit(0);
}
 
int dfs(int u=0) {
	int s=1;
	vis[u]=1;
	for(int k=0; k<8; ++k)
		if(adj[u][k]<n&&!vis[adj[u][k]])
			s+=dfs(adj[u][k]);
	return s;
}
 
int fc(int x, int y) {
	int p=lower_bound(b, b+n, array<int, 3>{x, y})-b;
	if(p<n&&b[p][0]==x&&b[p][1]==y)
		return b[p][2];
	auto it=lower_bound(mp[x].begin(), mp[x].end(), array<int, 2>{y+1, 0});
	return it==mp[x].begin()||yr[(*--it)[1]]<y?-1:(*it)[1]+n;
}

void upd(int u, bool b1, bool b2) {
	if(ia[u])
		return;
	if(c1[u]&&c2[u])
		s.erase(u);
	if(b1&&b2)
		s.insert(u);
	c1[u]=b1;
	c2[u]=b2;
}

int find(int x) {
	return x^p[x]?p[x]=find(p[x]):x;
}

void calc(int u) {
	for(int i=1; i<13; ++i)
		d[i]=d[i-1]+(adj[u][i%8]<n&&!ia[adj[u][i%8]]);
	for(int i=0; i<6; i+=2) {
		if(d[i+8]-d[i+7])
			continue;
		for(int j=i+2; j<8; j+=2) {
			if(!(d[j]-d[j-1])&&d[j-1]-d[i]&&d[i+7]-d[j]&&find(adj[u][i])==find(adj[u][j])) {
				upd(u, c1[u], 0);
				return;
			}
		}
	}
	upd(u, c1[u], 1);
}
 
void join(int x, int y) {
	if((x=find(x))==(y=find(y)))
		return;
	if(y==find(n))
		swap(x, y);
	if(x==find(n))
		for(int a : v[y])
			upd(a, 1, c2[a]);
	if(v[x].size()<v[y].size())
		swap(x, y);
	p[y]=x;
	for(int a : v[y])
		calc(a);
	v[x].insert(v[x].end(), v[y].begin(), v[y].end());
}
 
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
 
	cin >> n >> t;
	for(int i=0; i<n; ++i) {
		cin >> a[i][0] >> a[i][1];
		b[i]={a[i][0], a[i][1], i};
	}
	sort(b, b+n);
	auto ns=[](int xi, int yli, int yri) {
		x[m]=xi;
		yl[m]=yli;
		yr[m]=yri;
		mp[xi].push_back({yli, m});
		++m;
	};
	ns(b[0][0]-1, -INF, INF);
	ns(b[n-1][0]+1, -INF, INF);
	for(int i=0, j=0; i<n; ) {
		for(; j<n&&b[j][0]==b[i][0]; ++j);
		int l=-INF;
		for(; i<j; l=b[i++][1]+1)
			if(l<b[i][1])
				ns(b[i][0], l, b[i][1]-1);
		ns(b[j-1][0], l, INF);
	}
	for(auto &a : mp)
		sort(a.second.begin(), a.second.end());
	for(int i=0; i<n; ++i) {
		for(int k=0; k<8; ++k) {
			adj[i][k]=fc(a[i][0]+dx[k], a[i][1]+dy[k]);
			if(adj[i][k]<0)
				fk();
			if(k&1^1) {
				v[adj[i][k]].push_back(i);
				if(adj[i][k]==n)
					upd(i, 1, 0);
			}
		}
	}
	if(dfs()<n)
		fk();
	iota(p, p+n+m, 0);
	for(int i=0; i<m; ++i) {
		for(int k=0; k<8; k+=2) {
			int j=fc(x[i]+dx[k], yl[i]+dy[k]);
			if(j>=n)
				join(i+n, j);
		}
	}
	for(int i=0; i<n; ++i)
		calc(i);
	for(int i=n-1; ~i; --i) {
		ans[i]=*--s.end();
		s.erase(ans[i]);
		ia[ans[i]]=1;
		for(int k=0; k<8; k+=2)
			if(adj[ans[i]][k]>=n||ia[adj[ans[i]][k]])
				join(ans[i], adj[ans[i]][k]);
		for(int k=0; k<8; ++k)
			if(adj[ans[i]][k]<n)
				calc(adj[ans[i]][k]);
	}
	cout << "YES\n";
	for(int i=0; i<n; ++i)
		cout << ans[i]+1 << "\n";
}
