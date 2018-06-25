/*
	- Consider the problem without changing parents
		- Toggling color of nodes and querying number of black nodes from u->v can be done with binary indexed tree, dfs order, and lca
		- For the kth black node from u->v, use binary search
	- Divide queries in blocks of at most sqrt(n) each
	- There are at most sqrt(n) parent changing queries => sqrt(n) connected components that don't change
	- For each block of queries, recalculate everything for the components in O(nlogn)
	- Kth black node query
		- Do O(sqrt(n)) dfs to find the path in the reduced graph
		- u->v is the union of sqrt(n) smaller paths, each within its own component
		- Do pretty much the same binary search
*/

#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define fi first
#define se second

const int mxN=1e5, sqN=1240;
int n, q, p[mxN], cci[mxN], st[mxN], en[mxN], dt[sqN+1], dst[mxN], e[mxN], sth, dep[mxN], anc[mxN][17], ft[sqN+1][mxN+1];
bool c[mxN], r[mxN]={1};
vector<int> rs, adj1[mxN], pt;
vector<pii> adj2[sqN+1];

struct query {
	int a, b, c;
} qs[sqN];

inline void upd(int i, int j, int x) {
	for(++j; j<=dt[i]; j+=j&-j)
		ft[i][j]+=x;
}

inline int qry(int i, int j) {
	int r=0;
	for(++j; j; j-=j&-j)
		r+=ft[i][j];
	return r;
}

inline int lca(int u, int v) {
	if(dep[u]<dep[v])
		swap(u, v);
	for(int i=16; i>=0; --i)
		if(dep[u]-(1<<i)>=dep[v])
			u=anc[u][i];
	if(u==v)
		return u;
	for(int i=16; i>=0; --i)
		if(anc[u][i]!=anc[v][i])
			u=anc[u][i], v=anc[v][i];
	return p[u];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> q;
	for(int i=0; i<n; ++i)
		cin >> c[i];
	for(int i=1; i<n; ++i)
		cin >> p[i], --p[i];
	for(int qi1=0; qi1<q; qi1+=sqN) {
		for(int qi2=0; qi2<sqN&&qi1+qi2<q; ++qi2) {
			qs[qi2]={-1, -1, -1};
			char qt;
			cin >> qt;
			if(qt=='T')
				cin >> qs[qi2].a, --qs[qi2].a;
			else if(qt=='C') {
				cin >> qs[qi2].a >> qs[qi2].b, --qs[qi2].a, --qs[qi2].b;
				r[qs[qi2].a]=1;
			} else
				cin >> qs[qi2].a >> qs[qi2].b >> qs[qi2].c, --qs[qi2].a, --qs[qi2].b;
		}
		for(int i=0; i<n; ++i) {
			if(r[i]) {
				cci[i]=rs.size();
				rs.push_back(i);
			} else
				adj1[p[i]].push_back(i);
		}
		for(int i=0; i<rs.size(); ++i) {
			dst[0]=rs[i];
			memset(anc[rs[i]], -1, sizeof(anc[rs[i]]));
			dep[rs[i]]=0;
			sth=1;
			while(sth) {
				int u=dst[sth-1];
				if(!e[u])
					st[u]=dt[i]++;
				if(e[u]>=adj1[u].size()) {
					en[u]=dt[i];
					--sth;
					continue;
				}
				int v=dst[sth]=adj1[u][e[u]++];
				cci[v]=i;
				anc[v][0]=u;
				for(int j=1; j<17; ++j)
					anc[v][j]=anc[v][j-1]==-1?-1:anc[anc[v][j-1]][j-1];
				dep[v]=dep[u]+1;
				++sth;
			}
		}
		memset(e, 0, 4*n);
		for(int i=0; i<n; ++i) {
			if(c[i]) {
				upd(cci[i], st[i], 1);
				upd(cci[i], en[i], -1);
			}
		}
		for(int qi2=0; qi2<sqN&&qi1+qi2<q; ++qi2) {
			if(qs[qi2].c!=-1) {
				for(int i=1; i<rs.size(); ++i) {
					adj2[i].push_back({rs[i], p[rs[i]]});
					adj2[cci[p[rs[i]]]].push_back({p[rs[i]], rs[i]});
				}
				dst[sth++]=cci[qs[qi2].a];
				pt.push_back(qs[qi2].a);
				while(sth) {
					int u=dst[sth-1];
					if(u==cci[qs[qi2].b])
						break;
					if(e[u]>=adj2[u].size()) {
						pt.pop_back();
						pt.pop_back();
						--sth;
						continue;
					}
					pii v=adj2[u][e[u]++];
					if(e[cci[v.se]])
						continue;
					pt.push_back(v.fi);
					pt.push_back(v.se);
					dst[sth++]=cci[v.se];
				}
				sth=0;
				pt.push_back(qs[qi2].b);
				for(int i=0; i<rs.size(); ++i)
					adj2[i].clear();
				memset(e, 0, 4*rs.size());
				for(int i=0; i<pt.size()&&qs[qi2].c; i+=2) {
					int w=lca(pt[i], pt[i+1]), c=cci[pt[i]], a=qry(c, st[pt[i]])-qry(c, st[w]), b=qry(c, st[pt[i+1]])-(r[w]?0:qry(c, st[p[w]]));
					if(a+b>=qs[qi2].c) {
						if(a<qs[qi2].c) {
							qs[qi2].c=b-(qs[qi2].c-a)+1;
							pt[i]=pt[i+1];
						}
						w=pt[i];
						for(int j=16; j>=0; --j)
							if(anc[w][j]!=-1&&qry(c, st[pt[i]])-qry(c, st[anc[w][j]])<qs[qi2].c)
								w=anc[w][j];
						qs[qi2].c=0;
						cout << w+1 << "\n";
					} else
						qs[qi2].c-=a+b;
				}
				if(qs[qi2].c)
					cout << "-1\n";
				pt.clear();
			} else if(qs[qi2].b==-1) {
				int u=qs[qi2].a;
				upd(cci[u], st[u], !c[u]-c[u]);
				upd(cci[u], en[u], c[u]-!c[u]);
				c[u]=!c[u];
			} else
				p[qs[qi2].a]=qs[qi2].b;
		}
		memset(r+1, 0, n-1);
		for(int i=0; i<n; ++i)
			adj1[i].clear();
		for(int i=0; i<rs.size(); ++i)
			memset(ft[i], 0, 4*(dt[i]+1));
		memset(dt, 0, 4*rs.size());
		rs.clear();
	}
}
