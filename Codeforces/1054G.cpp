#include <bits/stdc++.h>
using namespace std;

const int mxN=2e3;
int t, n, m, d[mxN][mxN];
bitset<mxN> b[mxN], c[mxN];
array<int, 2> qu[mxN*mxN], a[mxN-1];
bool e[mxN];

void solve() {
	cin >> n >> m;
	for(int i=0; i<n; ++i)
		c[i].reset();
	for(int i=0; i<m; ++i) {
		string s;
		cin >> s;
		reverse(s.begin(), s.end());
		b[i]=bitset<mxN>(s);
		if(b[i].count()>1)
			for(int j=0; j<n; ++j)
				c[j][i]=b[i][j];
	}
	for(int i=0; i<n; ++i)
		for(int j=0; j<n; ++j)
			d[i][j]=(c[i]&~c[j]).count();
	memset(e, 0, n);
	int qt=0;
	for(int i=0; i<n; ++i)
		for(int j=0; j<n; ++j)
			if(!d[i][j]&&j!=i)
				qu[qt++]={i, j};
	for(int qh=0, it=0; it<n-1; ++qh) {
		if(qh>=qt) {
			cout << "NO\n";
			return;
		}
		array<int, 2> u=qu[qh];
		if(e[u[0]]||e[u[1]])
			continue;
		e[u[0]]=1;
		a[it++]=u;
		for(int i=0; i<m; ++i) {
			if(b[i][u[0]]&&b[i].count()==2) {
				for(int j=0; j<n; ++j) {
					d[u[1]][j]-=j!=u[0];
					if(!d[u[1]][j]&&j!=u[1])
						qu[qt++]={u[1], j};
				}
			}
			b[i][u[0]]=0;
		}
	}
	cout << "YES\n";
	for(int i=0; i<n-1; ++i)
		cout << a[i][0]+1 << " " << a[i][1]+1 << "\n";
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> t;
	while(t--)
		solve();
}
