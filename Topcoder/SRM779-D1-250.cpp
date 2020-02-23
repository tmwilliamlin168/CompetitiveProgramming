#include <bits/stdc++.h>
using namespace std;

#define ar array

class ArraySorting {
public:
	int dp[2001][2001];
	vector<int> arraySort(vector<int> a) {
		int n=a.size();
		for(int i=n-1; ~i; --i) {
			int mn=1e9;
			for(int j=2000; j; --j) {
				mn=min(mn, dp[i+1][j]);
				dp[i][j]=mn+(j!=a[i]);
			}
		}
		vector<int> v(n);
		int s=1;
		for(int i=0; i<n; ++i) {
			ar<int, 2> b{(int)1e9};
			for(int j=s; j<=2000; ++j)
				b=min(b, ar<int, 2>{dp[i][j], j});
			v[i]=b[1];
			s=b[1];
		}
		return v;
	}
};
