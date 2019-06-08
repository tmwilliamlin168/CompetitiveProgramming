#include <bits/stdc++.h>
using namespace std;

const int mxN=1e3;
int n, r[mxN], c[mxN];
vector<array<int, 4>> ans;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for(int i=0, a; i<n; ++i)
		cin >> a, r[a-1]=i;
	for(int i=0, a; i<n; ++i)
		cin >> a, c[a-1]=i;
	for(int i=n-1; i; --i) {
		int j1=find(r, r+i+1, i)-r, j2=find(c, c+i+1, i)-c;
		swap(r[i], r[j1]);
		swap(c[i], c[j2]);
		if(i^j1||i^j2)
			ans.push_back({j1, i, i, j2});
	}
	cout << ans.size() << "\n";
	for(auto a : ans)
		cout << a[0]+1 << " " << a[1]+1 << " " << a[2]+1 << " " << a[3]+1 << "\n";
}
