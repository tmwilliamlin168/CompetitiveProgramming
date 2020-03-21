#include <bits/stdc++.h>
using namespace std;

#define ar array

const int mxN=1e5;
int n, m;
queue<ar<int, 2>> qu;
long long ans;

int p[mxN], s[mxN];
set<ar<int, 2>> to[mxN], from[mxN];

int find(int x) {
	return x^p[x]?p[x]=find(p[x]):x;
}

void cr(int u, int v) {
	auto it=to[u].lower_bound(ar<int, 2>{v});
	if(it!=to[u].end()&&(*it)[0]==v)
		qu.push({u, v});
}

int e1(set<ar<int, 2>> &s, int x) {
	auto it=s.lower_bound(ar<int, 2>{x});
	int r=0;
	while(it!=s.end()&&(*it)[0]==x)
		it=s.erase(it), ++r;
	return r;
}
	
void join(int u, int v) {
	if((u=find(u))==(v=find(v)))
		return;
	//remove self edges?
	e1(to[u], v);
	ans-=e1(from[u], v)*s[u];
	e1(to[v], u);
	ans-=e1(from[v], u)*s[v];
	//u to v
	if(to[u].size()+from[u].size()>to[v].size()+from[v].size())
		swap(u, v);
	//update ans
	ans+=(long long)2*s[u]*s[v];
	ans+=(long long)s[u]*from[v].size();
	ans+=(long long)s[v]*from[u].size();
	for(ar<int, 2> e : from[u])
		if(from[v].find(e)!=from[v].end())
			ans-=s[u]+s[v];
	//merge sets
	for(ar<int, 2> e : from[u])
		from[v].insert(e);
	for(ar<int, 2> e : to[u])
		to[v].insert(e);
	p[u]=v;
	s[v]+=s[u];
	//update references to u
	for(ar<int, 2> e : to[u]) {
		auto it=from[e[0]].lower_bound(ar<int, 2>{u});
		while(it!=from[e[0]].end()&&(*it)[0]==u) {
			from[e[0]].insert({v, (*it)[1]});
			it=from[e[0]].erase(it);
		}
	}
	for(ar<int, 2> e : from[u]) {
		auto it=to[e[0]].lower_bound(ar<int, 2>{u});
		while(it!=to[e[0]].end()&&(*it)[0]==u) {
			to[e[0]].insert({v, (*it)[1]});
			it=to[e[0]].erase(it);
		}
	}
	//check for new merges
	for(ar<int, 2> e : to[u])
		cr(e[0], v);
	for(ar<int, 2> e : from[u])
		cr(v, e[0]);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	iota(p, p+n, 0);
	fill(s, s+n, 1);
	for(int a, b; m--; ) {
		cin >> a >> b, --a, --b;
		if(find(a)!=find(b)) {
			//add edge
			to[find(a)].insert({find(b), b});
			ans+=from[find(b)].insert({find(a), a}).second*s[find(b)];
			//check relation
			cr(find(b), find(a));
			while(qu.size()) {
				ar<int, 2> u=qu.front();
				qu.pop();
				join(u[0], u[1]);
			}
		}
		cout << ans << "\n";
	}
}
