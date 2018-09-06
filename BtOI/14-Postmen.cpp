/*
	- Process the euler tour from left to right
	- If a suffix forms a cycle, remove it
	- IO optimization required to pass the strict TL
*/

#include <bits/stdc++.h>
using namespace std;

int in() {
	char c=getchar_unlocked();
	while(c<'0'||c>'9')
		c=getchar_unlocked();
	int r=0;
	while(c>='0'&&c<='9') {
		r=r*10+c-'0';
		c=getchar_unlocked();
	}
	return r;
}

void out(int x) {
	int lz=0, r=0;
	while(x%10==0) {
		++lz;
		x/=10;
	}
	while(x) {
		r=r*10+x%10;
		x/=10;
	}
	while(r) {
		putchar_unlocked('0'+r%10);
		r/=10;
	}
	while(lz--)
		putchar_unlocked('0');
}

const int mxN=5e5;
int n, m, eu[mxN], ev[mxN];
vector<int> adj[mxN], a1, a2;
bool a[mxN], b[mxN];

void dfs(int u) {
	while(adj[u].size()) {
		int e=adj[u].back();
		adj[u].pop_back();
		if(a[e])
			continue;
		a[e]=1;
		dfs(eu[e]^ev[e]^u);
	}
	a1.push_back(u);
}

int main() {
	n=in(), m=in();
	for(int i=0; i<m; ++i) {
		eu[i]=in()-1, ev[i]=in()-1;
		adj[eu[i]].push_back(i);
		adj[ev[i]].push_back(i);
	}
	dfs(0);
	for(int i=0; i<a1.size(); ++i) {
		if(b[a1[i]]) {
			while(a2.back()!=a1[i]) {
				out(a2.back()+1);
				putchar_unlocked(' ');
				b[a2.back()]=0;
				a2.pop_back();
			}
			out(a1[i]+1);
			putchar_unlocked('\n');
		} else {
			a2.push_back(a1[i]);
			b[a1[i]]=1;
		}
	}
}
