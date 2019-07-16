#include <bits/stdc++.h>
using namespace std;

const int mxN=100, M=998244353;
int n, dp[mxN+1][32][32][9][9][2], ans, fa[10], fb[10];
string s;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	auto am=[](int &a, int b) {
		a+=b;
		if(a>=M)
			a-=M;
	};
	cin >> s, n=s.size();
	for(int i=0; i<n; ++i)
		ans=((long long)ans*10+s[i]-'0')%M;
	for(int i1=1; i1<=9; ++i1) {
		for(int i2=i1+1; i2<=9; ++i2) {
			if(__gcd(i1, i2)>1)
				continue;
			memset(fa, -1, sizeof(fa));
			memset(fb, -1, sizeof(fb));
			int fps=0;
			for(int k=1; k<=9; ++k) {
				if(i2*k<=9) {
					fa[i1*k]=fps;
					fb[i2*k]=fps;
					++fps;
				}
			}
			memset(dp, 0, sizeof(dp));
			dp[0][0][0][0][0][1]=1;
			for(int j=0; j<n; ++j) {
				for(int d=0; d<=9; ++d) {
					for(int c1=0; c1<i1; ++c1) {
						int nd1=(d*i1+c1)%10, nc1=(d*i1+c1)/10;
						for(int c2=0; c2<i2; ++c2) {
							int nd2=(d*i2+c2)%10, nc2=(d*i2+c2)/10;
							for(int b1=0; b1<1<<fps; ++b1) {
								int nb1=b1|(~fa[nd1]?1<<fa[nd1]:0);
								for(int b2=0; b2<1<<fps; ++b2) {
									int nb2=b2|(~fb[nd2]?1<<fb[nd2]:0);
									for(int a : {0, 1}) {
										int na=nd2==s[n-1-j]-'0'?a:nd2<s[n-1-j]-'0';
										am(dp[j+1][nb1][nb2][nc1][nc2][na], dp[j][b1][b2][c1][c2][a]);
									}
								}
							}
						}
					}
				}
			}
			for(int b1=0; b1<1<<fps; ++b1)
				for(int b2=0; b2<1<<fps; ++b2)
					if(b1&b2)
						am(ans, dp[n][b1][b2][0][0][1]*2%M);
		}
	}
	cout << ans;
}
