/*
	- https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/COCI/official/2015/contest5_solutions/solutions.pdf
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5, mxS=2e6+1;
int n, a[mxN], q, qt, d[mxS], ds[mxS], de[mxS], anc[mxS][21], ft[mxS+1], dt, qa, b[mxS];
string s;
vector<int> c[mxS];

struct autoac {
	int n=1, c[mxS][26], sl[mxS], qu[mxS], qt=1;
	int add(string &s) {
		int u=0;
		for(int i=0; i<s.size(); u=c[u][s[i]-'a'], ++i)
			if(!c[u][s[i]-'a'])
				c[u][s[i]-'a']=n++;
		return u;
	}
	void ac() {
		sl[0]=-1;
		for(int qh=0; qh<n; ++qh) {
			int u=qu[qh];
			for(int a=0; a<26; ++a) {
				int v=c[u][a], w=sl[u];
				if(!v)
					continue;
				while(w!=-1&&!c[w][a])
					w=sl[w];
				if(w!=-1)
					sl[v]=c[w][a];
				qu[qt++]=v;
			}
		}
	}
	int feed(int u, char a) {
		while(u&&!c[u][a-'a'])
			u=sl[u];
		u=c[u][a-'a'];
		return u;
	}
} ac;

void dfs(int u=0, int p=-1) {
	ds[u]=dt++;
	anc[u][0]=p;
	d[u]=p==-1?0:d[p]+1;
	for(int i=1; i<21; ++i)
		anc[u][i]=anc[u][i-1]==-1?-1:anc[anc[u][i-1]][i-1];
	for(int v : c[u])
		dfs(v, u);
	de[u]=dt;
}

int lca(int u, int v) {
	if(d[u]<d[v])
		swap(u, v);
	for(int i=20; i>=0; --i)
		if(anc[u][i]!=-1&&d[anc[u][i]]>=d[v])
			u=anc[u][i];
	if(u==v)
		return u;
	for(int i=20; i>=0; --i) {
		if(anc[u][i]!=anc[v][i]) {
			u=anc[u][i];
			v=anc[v][i];
		}
	}
	return anc[u][0];
}

void upd(int i, int x) {
	for(++i; i<=ac.n; i+=i&-i)
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
		cin >> s, a[i]=ac.add(s);
	ac.ac();
	for(int i=1; i<ac.n; ++i)
		c[ac.sl[i]].push_back(i);
	dfs();
	cin >> q;
	while(q--) {
		cin >> qt;
		if(qt==1) {
			cin >> s;
			for(int i=0; i<s.size(); ++i)
				b[i]=ac.feed(i?b[i-1]:0, s[i]);
			sort(b, b+s.size(), [&](const int &i, const int &j) {
				return ds[i]<ds[j];
			});
			for(int i=0; i<s.size(); ++i) {
				if(i&&b[i]==b[i-1])
					continue;
				upd(ds[b[i]], 1);
				if(i)
					upd(ds[lca(b[i], b[i-1])], -1);
			}
		} else {
			cin >> qa, --qa;
			cout << qry(de[a[qa]])-qry(ds[a[qa]]) << "\n";
		}
	}
}
