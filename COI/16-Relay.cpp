/*
	- The points which can't be reached are bounded by the polygon and 2 tangent lines
	- We just need to find the tangent lines for each point and combine them
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=1e5;
int n, m, ans;
ll xa[mxN], ya[mxN], xb[2*mxN], yb[2*mxN];

struct ts {
	int li, ri;
	ll lx, ly, rx, ry;
};

ll cp(ll x1, ll y1, ll x2, ll y2, ll x3, ll y3) {
	return (y3-y1)*(x2-x1)-(y2-y1)*(x3-x1);
}

ts gts(ll x, ll y) {
	ts r;
	if(cp(x, y, xb[m-1], yb[m-1], xb[0], yb[0])<0) {
		int lb=0, rb=m-2;
		while(lb<rb) {
			int mb=(lb+rb+1)/2;
			if(cp(x, y, xb[m-1], yb[m-1], xb[mb], yb[mb])<0&&cp(x, y, xb[mb-1], yb[mb-1], xb[mb], yb[mb])<0)
				lb=mb;
			else
				rb=mb-1;
		}
		r.ri=lb;
		lb=1, rb=m-1;
		while(lb<rb) {
			int mb=(lb+rb)/2;
			if(cp(x, y, xb[mb], yb[mb], xb[0], yb[0])<0&&cp(x, y, xb[mb], yb[mb], xb[mb+1], yb[mb+1])<0)
				rb=mb;
			else
				lb=mb+1;
		}
		r.li=lb;
	} else {
		int lb=0, rb=m-2;
		while(lb<rb) {
			int mb=(lb+rb+1)/2;
			if(cp(x, y, xb[m-1], yb[m-1], xb[mb], yb[mb])>=0&&cp(x, y, xb[mb-1], yb[mb-1], xb[mb], yb[mb])>=0)
				lb=mb;
			else
				rb=mb-1;
		}
		r.li=lb;
		lb=1, rb=m-1;
		while(lb<rb) {
			int mb=(lb+rb)/2;
			if(cp(x, y, xb[mb], yb[mb], xb[0], yb[0])>=0&&cp(x, y, xb[mb], yb[mb], xb[mb+1], yb[mb+1])>=0)
				rb=mb;
			else
				lb=mb+1;
		}
		r.ri=lb;
	}
	r.lx=r.rx=x;
	r.ly=r.ry=y;
	return r;
}

bool wt(ll x, ll y, ts t) {
	return t.li>t.ri&&cp(xb[t.li], yb[t.li], xb[t.ri], yb[t.ri], x, y)>0&&cp(t.lx, t.ly, xb[t.li], yb[t.li], x, y)<0&&cp(t.rx, t.ry, xb[t.ri], yb[t.ri], x, y)>0;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for(int i=0; i<n; ++i)
		cin >> xa[i] >> ya[i];
	cin >> m;
	for(int i=0; i<m; ++i)
		cin >> xb[i] >> yb[i];
	memcpy(xb+m, xb, 8*m);
	memcpy(yb+m, yb, 8*m);
	ts re1=gts(xa[0], ya[0]);
	if(re1.li<re1.ri)
		re1.li+=m;
	ts re2=re1;
	for(int i=1; i<n; ++i) {
		ts tr=gts(xa[i], ya[i]);
		if(cp(xa[0], ya[0], xb[re1.li], yb[re1.li], xa[i], ya[i])>=0) {
			if(tr.li+m<=re1.li)
				tr.li+=m;
			if(tr.li^re2.li?tr.li<re2.li:cp(re2.lx, re2.ly, xb[tr.li], yb[tr.li], tr.lx, tr.ly)>0) {
				re2.li=tr.li;
				re2.lx=tr.lx;
				re2.ly=tr.ly;
			}
		}
		if(cp(xa[0], ya[0], xb[re1.ri], yb[re1.ri], xa[i], ya[i])<=0) {
			if(tr.ri<re1.ri)
				tr.ri+=m;
			if(tr.ri^re2.ri?tr.ri>re2.ri:cp(re2.rx, re2.ry, xb[tr.ri], yb[tr.ri], tr.rx, tr.ry)<0) {
				re2.ri=tr.ri;
				re2.rx=tr.rx;
				re2.ry=tr.ry;
			}
		}
	}
	for(int i=1; i<n; ++i)
		ans+=!wt(xa[i], ya[i], re2);
	cout << ans;
}
