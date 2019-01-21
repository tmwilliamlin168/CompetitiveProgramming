#include <bits/stdc++.h>
using namespace std;

const int mxN=1<<18, MG1=1<<9;
int n, q, a[MG1][mxN], ki, xi;

int dfs(int i, int j) {
	if(i>n)
		return 0;
	if(j<MG1)
		return a[j][i];
	int b=1<<(31-__builtin_clz(j));
	return dfs(i, j^b)^dfs(i+b, j^b);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> q;
	for(int i=0; i<n; ++i)
		cin >> a[0][i];
	for(int i=1; i<MG1; ++i)
		for(int j=0; j<n; ++j)
			a[i][j]=a[i-1][j]^a[i-1][j+1];
	while(q--) {
		cin >> ki >> xi, --xi;
		cout << dfs(xi, ki%mxN) << "\n";
	}
}
