/*
	- dp[i][j][k][l] = frame i, we have j points, the next shot should have k points and the next next should shoud have l points
	- Some optimizations to pass
		- "frame &f" instead of "frame f"
		- The order of the nesting of the loops
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=10;
int q, n, a[mxN];
string s;
ll dp[mxN+1][301][11][11];

struct frame {
	vector<int> v;
	int b1, b2;
	string s;
};
vector<frame> vs, vf;

void solve() {
	cin >> n >> s;
	for(int i=0; i<n; ++i)
		cin >> a[i];
	memset(dp, 0, sizeof(dp));
	for(int i=0; i<=10; ++i)
		for(int j=0; j<=10; ++j)
			dp[0][0][i][j]=1;
	for(int i=0; i<n; ++i) {
		for(frame &f : (i<n-1?vs:vf)) {
			bool ok=1;
			for(int k=0; k<f.s.size()&&ok; ++k)
				ok=s[2*i+k]=='?'||s[2*i+k]==f.s[k];
			if(!ok)
				continue;
			for(int j=0; j<=300; ++j) {
				int bs=j;
				for(int b : f.v)
					bs+=b;
				for(int k=0; k<=10; ++k) {
					if(k^f.v[0])
						continue;
					for(int l=0; l<=10; ++l) {
						if((f.v.size()>1&&l^f.v[1])||!dp[i][j][k][l])
							continue;
						for(int k2=0; k2<=10; ++k2) {
							if(f.v.size()<2&&k2^l)
								continue;
							for(int l2=0; l2<=10; ++l2) {
								int j2=bs+f.b1*k2+f.b2*l2;
								if(a[i]<0||a[i]==j2)
									dp[i+1][j2][k2][l2]+=dp[i][j][k][l];
							}
						}
					}
				}
			}
		}
	}
	ll ans=0;
	for(int i=0; i<=300; ++i)
		ans+=dp[n][i][0][0];
	cout << ans << "\n";
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	vs.push_back({{10}, 1, 1, "x-"});
	for(int i=0; i<10; ++i)
		vs.push_back({{i, 10-i}, 1, 0, to_string(i)+"/"});
	for(int i=0; i<10; ++i)
		for(int j=0; j<10-i; ++j)
			vs.push_back({{i, j}, 0, 0, to_string(i)+to_string(j)});
	vf.push_back({{10, 10, 10}, 0, 0, "xxx"});
	for(int i=0; i<10; ++i)
		vf.push_back({{10, 10, i}, 0, 0, "xx"+to_string(i)});
	for(int i=0; i<10; ++i)
		vf.push_back({{10, i, 10-i}, 0, 0, "x"+to_string(i)+"/"});
	for(int i=0; i<10; ++i)
		for(int j=0; j<10-i; ++j)
			vf.push_back({{10, i, j}, 0, 0, "x"+to_string(i)+to_string(j)});
	for(int i=0; i<10; ++i)
		vf.push_back({{i, 10-i, 10}, 0, 0, to_string(i)+"/x"});
	for(int i=0; i<10; ++i)
		for(int j=0; j<10; ++j)
			vf.push_back({{i, 10-i, j}, 0, 0, to_string(i)+"/"+to_string(j)});
	for(int i=0; i<10; ++i)
		for(int j=0; j<10-i; ++j)
			vf.push_back({{i, j}, 0, 0, to_string(i)+to_string(j)+"-"});
	cin >> q;
	while(q--)
		solve();
}
