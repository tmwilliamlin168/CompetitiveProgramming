/*
	- Sort a and b first
	- Binary search by answer
	- For each a_i, find the minimum j such that b_j can be paired with it using two pointers, and let k_i = j-i
	- Note that if there is a solution, there exists a solution such that for all i, a_i is paired with b_(i+k), where k is constant
	- Now we want to make all k_i the same
	- The j we found for each a_i was the minimum possible j, therefore we can only increase j, which increases k_i
	- So set k = max(ki) and check if it works
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=2e5;
int n, l, a[mxN], b[mxN*3];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> l;
	for(int i=0; i<n; ++i)
		cin >> a[i];
	sort(a, a+n);
	for(int i=0; i<n; ++i)
		cin >> b[i+n];
	sort(b+n, b+2*n);
	for(int i=0; i<n; ++i)
		b[i]=b[i+n]-l, b[i+2*n]=b[i+n]+l;
	int lb=0, rb=l/2-1;
	while(lb<=rb) {
		int mb=(lb+rb)/2, k=0;
		for(int i1=0, i2=0; i1<n; k=max(i2-i1, k), ++i1)
			while(b[i2]+mb<a[i1])
				++i2;
		bool ok=1;
		for(int i=0; i<n&&ok; ++i)
			ok=abs(a[i]-b[i+k])<=mb;
		if(ok)
			rb=mb-1;
		else
			lb=mb+1;
	}
	cout << lb;
}
