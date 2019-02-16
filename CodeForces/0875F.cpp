#include <bits/stdc++.h>
using namespace std;

const int mxN=2e5;
int n, m, ans, p[mxN];
array<int, 3> e[mxN];
bool c[mxN];

int find(int x) {
	return x==p[x]?x:(p[x]=find(p[x]));
}

bool join(int x, int y) {
	if((x=find(x))==(y=find(y))||c[x]&&c[y]) {
		if(c[x])
			return 0;
		return c[x]=1;
	}
	p[y]=x;
	c[x]|=c[y];
	return 1;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	for(int i=0; i<m; ++i)
		cin >> e[i][1] >> e[i][2] >> e[i][0], --e[i][1], --e[i][2];
	sort(e, e+m);
	iota(p, p+n, 0);
	while(m--)
		if(join(e[m][1], e[m][2]))
			ans+=e[m][0];
	cout << ans;
}
