/*
	- Let nl(i, j) = leftmost station we can go to with j rides (similar case for nr)
	- max(l[a], nl(i, j) < a < nr(i, j)) <= min(l[nl(i, j)], l[nr(i, j)])
		- WLOG max(l[a]) > l[nl(i, j)]
		- Must've reached station a at some point to reach nl(i, j) or nr(i, j), using less than j rides
		- We can use 1 ride with level l[a] to the left from the leftmost a and get farther than nl(i, j), contradiction
	- If l[nl(i, j)] = l[nr(i, j)], nl(i, j+k) = nl(nl(i, j), k) (similar case for nr)
	- Else, WLOG l[nl(i, j)] < l[nr(i, j)]
		- Moving once to the left from nr(i, j) will get us at least as far left as moving from nl(i, j)
		- nl(i, j+k) = nl(nr(i, j), k), nr(i, j+k) = nr(nr(i, j), k)
	- We can now create a sparse table to find nl(i, j) and nr(i, j) efficiently for arbitrary i, j
	- For each query (a, b)
		- Find the maximum i such that nr(a, i) < b
		- Find the maximum j such that nl(b, j) > nr(a, i)
		- i+j is obviously necessary, but is also sufficient
		- We just need to prove that we can connect one of nl(a, i) and nr(a, i) with one of nl(b, j) and nr(b, j) in 1 ride
		- l[nl(a, i)] <= l[nr(a, i)]
			- We know that l[c] < min(l[nr(a, i)], l[b]) for all nr(a, i) < c < b by the maximality of i
			- nl(nl(b, j), 1) <= nr(a, i)
				- nr(a, i) < nl(b, j) < b, so l[nl(b, j)] < l[nr(a, i)] and nl(nl(b, j), 1) = nr(a, i)
			- nl(nr(b, j), 1) <= nr(a, i) (or j = 0)
				- If nr(a, i) and nr(b, j) can't be connected with 1 ride, there must be d such that nr(a, i) < d < nr(b, j) and l[nr(a, i)] <= l[d] <= l[nr(b, j)]
				- We know that d >= b since l[d] >= min(l[nr(a, i)], l[b])
					- If j = 0, we already have d < b
				- But then the leftmost d can go to nr(a, i) in 1 ride, which contradicts nl(b, j) > nr(a, i)
		- l[nl(a, i)] > l[nr(a, i)]
			- nl(nl(b, j), 1) <= nr(a, i)
				- l[nl(b, j)] <= l[nr(a, i)]
					- nl(nl(b, j), 1) = nr(a, i)
				- l[nl(b, j)] > l[nr(a, i)]
					- By maximality of i, l[nl(b, j)] < l[nl(a, i)], so nl(nl(b, j), 1) = nl(a, i)
			- nl(nr(b, j), 1) <= nr(a, i)
				- l[nr(b, j)] <= l[nr(a, i)]
					- nl(nr(b, j), 1) = nr(a, i)
				- l[nr(a, i)] < l[nr(b, j)] < l[nl(a, i)]
					- nl(nr(b, j), 1) = nl(a, i)
				- l[nr(b, j)] >= l[nl(a, i)]
					- nr(nl(a, i), 1) = nr(b, j)
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5;
int n, k, q, l[mxN], nl[17][mxN], nr[17][mxN];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> k >> q;
	for(int i=0; i<n; ++i) {
		cin >> l[i];
		nl[0][i]=i-1;
		while(~nl[0][i]&&l[nl[0][i]]<l[i])
			nl[0][i]=nl[0][nl[0][i]];
	}
	nl[0][0]=0;
	for(int i=n-1; ~i; --i) {
		nr[0][i]=i+1;
		while(nr[0][i]<n&&l[nr[0][i]]<l[i])
			nr[0][i]=nr[0][nr[0][i]];
	}
	nr[0][n-1]=n-1;
	for(int i=1; i<17; ++i) {
		for(int j=0; j<n; ++j) {
			nl[i][j]=min(nl[i-1][nl[i-1][j]], nl[i-1][nr[i-1][j]]);
			nr[i][j]=max(nr[i-1][nl[i-1][j]], nr[i-1][nr[i-1][j]]);
		}
	}
	for(int a, b; q--; ) {
		cin >> a >> b, --a, --b;
		if(a>b)
			swap(a, b);
		int l=a, r=a, ans=0, c;
		for(int i=16; ~i; --i) {
			if(max(nr[i][l], nr[i][r])<b) {
				tie(l, r)=make_pair(min(nl[i][l], nl[i][r]), max(nr[i][l], nr[i][r]));
				ans+=1<<i;
			}
		}
		c=r;
		l=b, r=b;
		for(int i=16; ~i; --i) {
			if(min(nl[i][l], nl[i][r])>c) {
				tie(l, r)=make_pair(min(nl[i][l], nl[i][r]), max(nr[i][l], nr[i][r]));
				ans+=1<<i;
			}
		}
		cout << ans << "\n";
	}
}
