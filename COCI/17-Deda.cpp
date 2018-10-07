/*
	- Create a segment tree with the indicies as the numbers of the children
	- Maintain minimum stops rode for each segment
	- Kind of like doing a binary search on a segment tree to find the minimum r with smaller than y number of stops
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=2e5;
int n, q, a, b, st[1<<19];
char qt;

void upd(int l1, int x, int i=1, int l2=0, int r2=n-1) {
	st[i]=min(x, st[i]);
	if(l2==r2)
		return;
	int m2=(l2+r2)/2;
	if(l1<=m2)
		upd(l1, x, 2*i, l2, m2);
	else
		upd(l1, x, 2*i+1, m2+1, r2);
}

int qry(int l1, int x, int i=1, int l2=0, int r2=n-1) {
	if(st[i]>x)
		return -2;
	if(l2==r2)
		return l2;
	int m2=(l2+r2)/2;
	int r=-2;
	if(l1<=m2)
		r=qry(l1, x, 2*i, l2, m2);
	if(r==-2)
		r=qry(l1, x, 2*i+1, m2+1, r2);
	return r;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> q;
	memset(st, 0x3f, sizeof(st));
	while(q--) {
		cin >> qt >> a >> b, --b;
		if(qt=='M')
			upd(b, a);
		else
			cout << qry(b, a)+1 << "\n";
	}
}
