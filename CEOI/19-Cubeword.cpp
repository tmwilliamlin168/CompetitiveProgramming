#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
 
const int M=998244353, A=62;
map<char, int> mp;
ll b[A][A], c[A][A][A], ans;
 
void solve(vector<string> &v) {
	memset(b, 0, sizeof(b));
	for(string &s : v)
		b[mp[s[0]]][mp[s.back()]]++;
	memset(c, 0, sizeof(c));
	for(int i=0; i<A; ++i) {
		for(int j=0; j<A; ++j) {
			for(int k=0; k<A; ++k) {
				if(i!=j&&j!=k&&i!=k&&(i>j||j>k)) {
					int a[3]={i, j, k};
					sort(a, a+3);
					c[i][j][k]=c[a[0]][a[1]][a[2]];
					continue;
				}
				for(int l=0; l<A; ++l)
					c[i][j][k]=(c[i][j][k]+b[i][l]*b[j][l]*b[k][l])%M;
			}
		}
	}
	for(int i=0; i<A; ++i) {
		for(int j=0; j<A; ++j) {
			for(int k=0; k<A; ++k) {
				for(int l=0; l<A; ++l) {
					if(i==j||i==k||i==l||j==k||j==l||k==l)
						ans=(ans+c[i][j][k]*c[i][j][l]%M*c[i][k][l]%M*c[j][k][l])%M;
					else if(i<j&&j<k&&k<l)
						ans=(ans+c[i][j][k]*c[i][j][l]%M*c[i][k][l]%M*c[j][k][l]%M*24)%M;
				}
			}
		}
	}
}
 
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
 
	vector<string> v[11];
	int n;
	cin >> n;
	for(int i=0; i<n; ++i) {
		string s;
		cin >> s;
		v[s.size()].push_back(s);
		reverse(s.begin(), s.end());
		v[s.size()].push_back(s);
	}
	for(int i=0; i<26; ++i)
		mp['a'+i]=i, mp['A'+i]=i+26;
	for(int i=0; i<10; ++i)
		mp['0'+i]=i+52;
	for(int i=3; i<=10; ++i) {
		sort(v[i].begin(), v[i].end());
		v[i].resize(unique(v[i].begin(), v[i].end())-v[i].begin());
		solve(v[i]);
	}
	cout << ans;
}
