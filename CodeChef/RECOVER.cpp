#include <bits/stdc++.h>
using namespace std;

const int mxN=200;
int t, n, m, ui, vi, dc[mxN*mxN], a[mxN*mxN], dv[mxN*mxN], p[mxN*mxN];
vector<int> adj[mxN*mxN], ne[mxN*mxN], bd[2*mxN-1];

bool dfs(int d=0) {
	if(!d) {
		for(int i=0; i<n*n; ++i) {
			if(adj[i].size()==5) {
				a[0]=i;
				p[i]=0;
				return dfs(1);
			}
		}
	} else if(d==1) {
		vector<int> v;
		for(int i : adj[a[0]])
			if(adj[i].size()==ne[1].size())
				v.push_back(i);
		for(int i=0; i<v.size(); ++i) {
			a[1]=v[i];
			p[v[i]]=1;
			for(int j=0; j<v.size(); ++j) {
				if(i==j)
					continue;
				a[n]=v[j];
				p[v[j]]=n;
				if(dfs(2))
					return 1;
				p[v[j]]=-1;
			}
			p[v[i]]=-1;
		}
		return 0;
	} else if(d==2) {
		vector<int> v;
		int w=-1;
		for(int i : adj[a[0]]) {
			if(p[i]!=-1)
				continue;
			if(adj[i].size()==ne[n+1].size())
				w=i;
			else if(adj[i].size()==ne[2].size())
				v.push_back(i);
		}
		if(w==-1||v.size()<2)
			return 0;
		a[2]=v[0];
		p[v[0]]=2;
		a[2*n]=v[1];
		p[v[1]]=2*n;
		a[n+1]=w;
		p[w]=n+1;
		if(dfs(3))
			return 1;
		p[v[0]]=p[v[1]]=p[w]=-1;
		return 0;
	} else if(d==2*n-1) {
		for(int i=0; i<n*n; ++i) {
			if(ne[i].size()!=adj[a[i]].size())
				return 0;
			for(int j : ne[i])
				if(find(adj[a[i]].begin(), adj[a[i]].end(), a[j])==adj[a[i]].end())
					return 0;
		}
		return 1;
	}
	vector<int> v;
	for(int i : bd[d-2])
		for(int j : adj[a[i]])
			if(p[j]==-1)
				v.push_back(j);
	sort(v.begin(), v.end());
	v.resize(unique(v.begin(), v.end())-v.begin());
	unordered_map<int, int> mp;
	for(int i : bd[d]) {
		vector<int> w;
		for(int j : ne[i])
			if(dv[j]==d-1)
				w.push_back(a[j]);
		if(w.size()>2)
			return 0;
		w.push_back(n*n);
		sort(w.begin(), w.end());
		mp[w[0]+w[1]*n*n]=i;
	}
	for(int i : v) {
		vector<int> w;
		for(int j : adj[i])
			if(p[j]!=-1&&dv[p[j]]==d-1)
				w.push_back(j);
		if(w.size()>2)
			goto fk;
		w.push_back(n*n);
		sort(w.begin(), w.end());
		int x=w[0]+w[1]*n*n;
		if(mp.find(x)==mp.end())
			goto fk;
		p[i]=mp[x];
		a[p[i]]=i;
		mp.erase(x);
	}
	if(dfs(d+1))
		return 1;
	fk:
	for(int i : v)
		if(p[i]!=-1)
			p[i]=-1;
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> t;
	while(t--) {
		cin >> n >> m;
		for(int i=0; i<n*n; ++i)
			adj[i].clear();
		for(int i=0; i<m; ++i) {
			cin >> ui >> vi, --ui, --vi;
			adj[ui].push_back(vi);
			adj[vi].push_back(ui);
		}
		if(n==1) {
			cout << "1\n";
			continue;
		} else if(n==2) {
			cout << (m==6?"1 2\n3 4\n":"-1\n");
			continue;
		}
		memset(dc, 0, 4*n*n);
		for(int i=0; i<2*n-1; ++i)
			bd[i].clear();
		for(int i1=0; i1<n; ++i1) {
			for(int j1=0; j1<n; ++j1) {
				ne[i1*n+j1].clear();
				for(int i2=max(i1-2, 0); i2<min(i1+3, n); ++i2)
					for(int j2=max(j1-2, 0); j2<min(j1+3, n); ++j2)
						if((i1!=i2||j1!=j2)&&abs(i2-i1)+abs(j2-j1)<=2)
							ne[i1*n+j1].push_back(i2*n+j2);
				++dc[ne[i1*n+j1].size()];
				--dc[adj[i1*n+j1].size()];
				dv[i1*n+j1]=i1+j1;
				bd[i1+j1].push_back(i1*n+j1);
			}
		}
		for(int i=0; i<13; ++i)
			if(dc[i])
				goto fk;
		memset(p, -1, 4*n*n);
		memset(a, 0, 4*n*n);
		if(!dfs())
			goto fk;
		for(int i=0; i<n; ++i)
			for(int j=0; j<n; ++j)
				cout << a[i*n+j]+1 << " \n"[j==n-1];
		continue;
		fk:
		cout << "-1\n";
	}
}
