#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5, M=998244353;
int n, a[3*mxN], d[4];
string s;
map<char, int> mp{{'R', 0}, {'G', 1}, {'B', 2}};
vector<int> v[3];
long long ans=1;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> s;
	for(int i=0; i<3*n; ++i)
		v[mp[s[i]]].push_back(i);
	for(int i=0; i<n; ++i) {
		a[min({v[0][i], v[1][i], v[2][i]})]=-1;
		a[max({v[0][i], v[1][i], v[2][i]})]=1;
	}
	d[0]=n;
	for(int i=0; i<3*n; ++i) {
		ans=ans*d[a[i]+1]%M;
		--d[a[i]+1];
		++d[a[i]+2];
	}
	cout << ans;
}
