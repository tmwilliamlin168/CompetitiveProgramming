/*
	- It's obvious that we should take the smallest number
	- If there are multiple, we tiebreak A and B by:
		- If A is prefix of B, use B first
		- Else use the lexicographically smallest first
*/

#include <bits/stdc++.h>
using namespace std;

#define ull unsigned long long

const int mxN=1e3, B=1000696969;
int n, l[mxN], p[mxN][mxN+1];
ull hs[mxN][mxN+1], pB[mxN];

struct mc {
	bool operator()(array<int, 2> a, array<int, 2> b) {
		int lb=0, rb=min(l[a[0]]-a[1], l[b[0]]-b[1]);
		while(lb<rb) {
			int mb=(lb+rb+1)/2;
			if(hs[a[0]][a[1]+mb]-hs[a[0]][a[1]]*pB[mb]==hs[b[0]][b[1]+mb]-hs[b[0]][b[1]]*pB[mb])
				lb=mb;
			else
				rb=mb-1;
		}
		return p[a[0]][a[1]+lb]>p[b[0]][b[1]+lb];
	}
};
priority_queue<array<int, 2>, vector<array<int, 2>>, mc> pq;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	pB[0]=1;
	for(int i=1; i<mxN; ++i)
		pB[i]=pB[i-1]*B;
	cin >> n;
	for(int i=0; i<n; ++i) {
		cin >> l[i];
		for(int j=0; j<l[i]; ++j)
			cin >> p[i][j], hs[i][j+1]=p[i][j]+hs[i][j]*B;
		p[i][l[i]]=B;
		pq.push({i, 0});
	}
	while(pq.size()) {
		array<int, 2> a=pq.top();
		pq.pop();
		cout << p[a[0]][a[1]] << " ";
		if(a[1]+1<l[a[0]])
			pq.push({a[0], a[1]+1});
	}
}
