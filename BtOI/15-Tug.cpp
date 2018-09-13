/*
	- If a spot has 0 contestants who can use it, the answer is no
	- If a spot has 1 contestant, that contestant has to be assigned to that spot
	- If all spots left have at least 2 contestants, we can prove that all spots have exactly 2 contestants
	- When you view the spots as nodes and contestants as edges, the graph is just composed of cycles
	- Each cycle has 2 possibilities
	- We can use bitset for the knapsack dp
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=6e4;
int n, k, l[mxN], r[mxN], s[mxN], dp0;
set<int> pc[mxN];
bitset<20*mxN+1> dp;
queue<int> qu;
vector<int> vc;

void fk() {
	cout << "NO";
	exit(0);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k;
	n*=2;
	for(int i=0; i<n; ++i) {
		cin >> l[i] >> r[i] >> s[i], --l[i], r[i]+=n/2-1;
		pc[l[i]].insert(i);
		pc[r[i]].insert(i);
	}
	for(int i=0; i<n; ++i) {
		if(!pc[i].size())
			fk();
		else if(pc[i].size()==1)
			qu.push(i);
	}
	dp0=10*n;
	while(qu.size()) {
		int u=qu.front();
		if(!pc[u].size())
			fk();
		qu.pop();
		int a=*pc[u].begin(), v=u^l[a]^r[a];
		dp0+=u<n/2?s[a]:-s[a];
		pc[v].erase(a);
		if(pc[v].size()==1)
			qu.push(v);
	}
	for(int i=0; i<n; ++i) {
		if(pc[i].size()<2)
			continue;
		int c=0;
		for(int j=i; pc[j].size(); ) {
			int a=*pc[j].begin();
			c+=j<n/2?s[a]:-s[a];
			pc[l[a]].erase(a);
			pc[r[a]].erase(a);
			j^=l[a]^r[a];
		}
		c=abs(c);
		dp0-=c;
		vc.push_back(2*c);
	}
	dp[dp0]=1;
	for(int c : vc)
		dp|=dp<<c;
	bool ok=0;
	for(int i=10*n-k; i<=10*n+k&&!ok; ++i)
		ok=dp[i];
	if(!ok)
		fk();
	cout << "YES";
}
