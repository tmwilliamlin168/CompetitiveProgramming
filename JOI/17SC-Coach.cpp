/*
	- For each refilling point, we can choose the last x people who need to drink before the arriving at the refilling point to leave
	- These last x people correspond to a continuous interval of people when sorted by d[i]
	- We first compute the answer given that nobody will leave
	- We then choose several non-intersecting intervals ending at refilling points and make the people in the intervals leave
		- Can be computed efficiently with dp + convex hull trick
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=2e5;
int n, m;
ll x, w, t, s[mxN+1], a1, pc[mxN+1], dp[mxN+1];
array<ll, 2> s1[mxN+1], d[mxN], st[1<<19];

void upd(array<ll, 2> a, int i=1, int l2=0, int r2=m-1) {
	int m2=(l2+r2)/2;
	if(st[i][0]*m2+st[i][1]>a[0]*m2+a[1])
		swap(st[i], a);
	if(l2==r2)
		return;
	if(a[0]*l2+a[1]<st[i][0]*l2+st[i][1])
		upd(a, 2*i, l2, m2);
	else
		upd(a, 2*i+1, m2+1, r2);
}

ll qry(int x, int i=1, int l2=0, int r2=m-1) {
	int m2=(l2+r2)/2;
	return min(st[i][0]*x+st[i][1], l2<r2?(x<=m2?qry(x, 2*i, l2, m2):qry(x, 2*i+1, m2+1, r2)):pc[m]);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> x >> n >> m >> w >> t;
	for(int i=0; i<n; ++i) {
		cin >> s[i];
		s1[i]={s[i]%t, i};
	}
	s[n]=x;
	s1[n]={x%t, n};
	sort(s1, s1+n+1);
	a1=x/t+1;
	for(int i=0; i<m; ++i) {
		cin >> d[i][0] >> d[i][1];
		a1+=(x-d[i][0]+t)/t;
	}
	sort(d, d+m);
	for(int i=0; i<m; ++i)
		pc[i+1]=pc[i]+d[i][1];
	fill(st, st+(1<<19), array<ll, 2>{0ll, pc[m]});
	for(int i1=m-1, i2=n; i1>=0; --i1) {
		while(i2>=0&&s1[i2][0]>d[i1][0]) {
			int l2=lower_bound(d, d+i1+1, array<ll, 2>{x%t+1, 0ll})-d;
			ll b=s[s1[i2--][1]]/t-x/t;
			upd({-w*b, pc[i1+1]+(i1+1)*w*b+dp[i1+1]});
			upd({-w*(b-1), pc[i1+1]+(i1-l2+1)*w*b+l2*w*(b-1)+dp[i1+1]});
		}
		dp[i1]=min(qry(i1)-pc[i1], dp[i1+1]);
	}
	cout << a1*w+dp[0];
}
