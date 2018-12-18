#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5;
int n, m, c, t[mxN];

int main() {
	ifstream cin("convention.in");
	ofstream cout("convention.out");
	
	//input
	cin >> n >> m >> c;
	for(int i=0; i<n; ++i)
		cin >> t[i];
	sort(t, t+n);
	//do the binary search
	int lb=0, rb=(int)1e9;
	while(lb<rb) {
		int mb=(lb+rb)/2, num=0;
		//greedily group cows
		for(int i=0; i<n; ++i, ++num) {
			int j=i;
			for(; j+1<n&&j-i+2<=c&&t[j+1]-t[i]<=mb; ++j);
			i=j;
		}
		if(num<=m)
			rb=mb;
		else
			lb=mb+1;
	}
	cout << lb;
}
