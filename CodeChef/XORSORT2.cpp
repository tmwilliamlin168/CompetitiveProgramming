/*
	- For each i from 1 to k, we can find a[i] and b[i] such that the number of inversions increases by a[i] if the ith bit of x is set and b[i] if it is not
		- O(n*k) for this part
	- A simple O(k*2^k) solution is to find the number of inversions for all x and sort them
	- We can improve the solution to O(k*2^(k/2)) with binary search and meet in the middle
*/

#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pli pair<ll, int>
#define fi first
#define se second
 
const int mxK=30;
int n, k, p;
vector<int> a;
ll ic[mxK][2];
pli ps1[1<<(mxK/2)], ps2[1<<((mxK+1)/2)];

void rec(vector<int> &a, int i) {
	if(a.empty())
		return;
	int s[2]={0, 0};
	vector<int> b[2];
	for(int ai : a) {
		++s[ai>>i&1];
		ic[i][ai>>i&1]+=s[ai>>i&1^1];
		b[ai>>i&1].push_back(ai);
	}
	if(i) {
		rec(b[0], i-1);
		rec(b[1], i-1);
	}
}

inline int chk(pli x) {
	int r=0;
	for(int i1=0, i2=(1<<((k+1)/2))-1; i1<1<<(k/2); ++i1) {
		while(i2>=0&&pli(ps1[i1].fi+ps2[i2].fi, ps1[i1].se<<((k+1)/2)|ps2[i2].se)>x)
			--i2;
		r+=i2+1;
	}
	return r;
}

inline void solve() {
	cin >> n >> k >> p;
	a.resize(n);
	for(int i=0; i<n; ++i)
		cin >> a[i];
	memset(ic, 0, sizeof(ic));
	rec(a, k-1);
	for(int i=0; i<1<<(k/2); ++i) {
		ps1[i]={0, i};
		for(int j=0; j<k/2; ++j)
			ps1[i].fi+=ic[j+(k+1)/2][i>>j&1];
	}
	for(int i=0; i<1<<((k+1)/2); ++i) {
		ps2[i]={0, i};
		for(int j=0; j<(k+1)/2; ++j)
			ps2[i].fi+=ic[j][i>>j&1];
	}
	sort(ps1, ps1+(1<<(k/2)));
	sort(ps2, ps2+(1<<((k+1)/2)));
	ll lb1=0, rb1=(ll)n*(n-1)/2;
	while(lb1<=rb1) {
		ll mb=(lb1+rb1)/2;
		if(chk({mb, 1<<k})>=p)
			rb1=mb-1;
		else
			lb1=mb+1;
	}
	ll lb2=0, rb2=(1<<k)-1;
	while(lb2<=rb2) {
		ll mb=(lb2+rb2)/2;
		if(chk({lb1, mb})>=p)
			rb2=mb-1;
		else
			lb2=mb+1;
	}
	cout << lb2 << "\n";
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int t;
	cin >> t;
	while(t--)
		solve();
}
