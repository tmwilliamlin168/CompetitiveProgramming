#include <bits/stdc++.h>
using namespace std;

const int mxN=250;
int n, m, c[mxN][26], ans, p[2*mxN+1];
string g[mxN];
bool pr[mxN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	for(int i=0; i<n; ++i)
		cin >> g[i];
	auto e=[&](int l, int r, int i, int j) {
		if(i%2==0||j%2==0)
			return i%2==j%2;
		i/=2;
		j/=2;
		for(int k=0; k<26; ++k)
			if(c[i][k]!=c[j][k])
				return false;
		return pr[i]&&pr[j];
	};
	for(int l=0; l<m; ++l) {
		memset(c, 0, sizeof(c));
		memset(pr, 0, sizeof(pr));
		for(int r=l; r<m; ++r) {
			for(int i=0; i<n; ++i) {
				++c[i][g[i][r]-'a'];
				int no=0;
				for(int j=0; j<26; ++j)
					no+=c[i][j]&1;
				pr[i]=no<=1;
			}
			int c1=0, r1=0;
			for(int i=0; i<=2*n; ++i) {
				if(r1>i)
					p[i]=min(r1-i, p[2*c1-i]);
				else
					p[i]=0;
				while(i-p[i]-1>=0&&i+p[i]+1<=2*n&&e(l, r, i+p[i]+1, i-p[i]-1))
					++p[i];
				if(i+p[i]>r1) {
					c1=i;
					r1=i+p[i];
				}
				if(i%2==0||pr[i/2])
					ans+=(p[i]+1)/2;
			}
		}
	}
	cout << ans;
}
