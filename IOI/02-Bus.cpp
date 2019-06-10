/*
	- Iterate over O(n^2) pairs (H1, H2)
	- d1[i] and d2[i] are distances to the hubs
	- Answer for a pair is max(max d1 + second max d1, max d2 + second max d2, max d1 + max d2 + d1[H2])
	- If a, b connect to H1 where d1[a] <= d1[b], then there exists an optimal solution in which all i such that d1[i] <= d1[a] are connected to H1
	- We can iterate through pairs (a, b) for an O(n^4) solution
	- If d1[b] <= d1[b2] and d2[b] > d2[b2], then (a, b2) will never be optimal
	- nxt[b] = b2 such that d1[b] <= d1[b2], d2[b] < d2[b2], and d1[b2] is minimum
	- We only have to try (a, a+1), (a, nxt[a+1]), (a, nxt[nxt[a+1]]), ...
	- If there exist a, b, c, d such that d1[a] <= d1[b] <= d1[c] <= d1[d] and d2[a] <= d2[b] <= d2[c] <= d2[d], we can remove a
		- There exists a hub with at least 2 of b, c, d, we can add a to that hub without changing the answer
		- nxt will have a depth of at most 3
	- We can use radix sort to reduce time from O(n^3logn) to O(n^3)
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=500;
int n, x[mxN], y[mxN], ans=1e9, nxt[mxN+1], d[mxN], e[mxN];
array<int, 2> a[mxN], mx[mxN+2][3], c[mxN][mxN];
vector<array<int, 2>> v;
bool b[mxN];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for(int i=0; i<n; ++i)
		cin >> x[i] >> y[i];
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j)
			c[i][j]={abs(x[i]-x[j])+abs(y[i]-y[j]), j};
		sort(c[i], c[i]+n);
	}
	for(int i=0; i<n; ++i) {
		for(int j=0, k=0; j<n; j=k)
			for(; k<n&&c[i][k][0]==c[i][j][0]; ++k)
				d[c[i][k][1]]=j;
		for(int j=i+1; j<n; ++j) {
			iota(e, e+n, 0);
			for(int k=0; k<n; ++k)
				a[e[d[c[j][k][1]]]++]={abs(x[i]-x[c[j][k][1]])+abs(y[i]-y[c[j][k][1]]), c[j][k][0]};
			for(int l=0; l<3; ++l) {
				array<int, 2> c{};
				for(int k=n-1; ~k; --k) {
					if(!b[k]&&a[k][1]>c[1]) {
						c=a[k];
						b[k]=1;
					}
				}
			}
			v.push_back({});
			for(int k=0; k<n; ++k)
				if(b[k])
					v.push_back(a[k]);
			memset(b, 0, n);
			memset(mx[v.size()], 0, 24);
			for(int k=v.size()-1; ~k; --k) {
				array<int, 2> c{v[k][1], k};
				memcpy(mx[k], mx[k+1], 24);
				for(int l=0; l<3; ++l)
					if(mx[k][l]<c)
						swap(mx[k][l], c);
			}
			for(int k=v.size()-1; ~k; --k)
				for(nxt[k]=k+1; nxt[k]<v.size()&&v[nxt[k]][1]<v[k][1]; nxt[k]=nxt[nxt[k]]);
			for(int k=0, dab=abs(x[i]-x[j])+abs(y[i]-y[j]); k<v.size(); ++k) {
				for(int l=k+1; l<v.size(); l=nxt[l]) {
					array<int, 2> b0=mx[k+1][0], b1=mx[k+1][1];
					if(b0[1]==l)
						swap(b0, b1);
					if(b1[1]==l)
						b1=mx[k+1][2];
					ans=min(max({v[k][0]+v[l][0], b0[0]+b1[0], v[l][0]+dab+b0[0]}), ans);
				}
			}
			v.clear();
		}
	}
	cout << ans;
}
