/*
	- Binary search by answer
	- We can move the polygon inward by r and check that the maximum distance is at least 2*r
	- The first part can be done with half-plane intersection
	- The second part can be done with rotating calipers
*/

#include <bits/stdc++.h>
using namespace std;

#define ld long double

const int mxN=5e4;
int n, x[mxN], y[mxN];

vector<array<ld, 2>> convexHull(vector<array<ld, 2>> l, ld xl, ld xr) {
	sort(l.begin(), l.end(), greater<array<ld, 2>>());
	vector<array<ld, 2>> v, p;
	for(array<ld, 2> li : l) {
		while(v.size()>1&&(v.back()[1]-v[v.size()-2][1])/(v[v.size()-2][0]-v.back()[0])>(li[1]-v.back()[1])/(v.back()[0]-li[0]))
			v.pop_back();
		v.push_back(li);
	}
	int jl=0;
	while(jl+1<v.size()&&v[jl+1][0]*xl+v[jl+1][1]<v[jl][0]*xl+v[jl][1])
		++jl;
	p.push_back({xl, v[jl][0]*xl+v[jl][1]});
	int jr=jl;
	while(jr+1<v.size()&&v[jr+1][0]*xr+v[jr+1][1]<v[jr][0]*xr+v[jr][1])
		++jr;
	for(int i=jl; i+1<=jr; ++i) {
		ld x=(v[i+1][1]-v[i][1])/(v[i][0]-v[i+1][0]), y=v[i][0]*x+v[i][1];
		p.push_back({x, y});
	}
	p.push_back({xr, v[jr][0]*xr+v[jr][1]});
	return p;
}

ld gy(array<ld, 2> p1, array<ld, 2> p2, ld x) {
	return p1[1]+(p2[1]-p1[1])/(p2[0]-p1[0])*(x-p1[0]);
}

array<ld, 2> segmentIntersection(array<ld, 2> a, array<ld, 2> b, array<ld, 2> c, array<ld, 2> d) {
	ld x=(gy(c, d, 0)-gy(a, b, 0))/((a[1]-b[1])/(a[0]-b[0])-(c[1]-d[1])/(c[0]-d[0]));
	return {x, gy(a, b, x)};
}

vector<array<ld, 2>> halfplaneIntersection(vector<array<array<ld, 2>, 2>> a, ld xl, ld xr) {
	if(xl>xr)
		return vector<array<ld, 2>>();
	vector<array<ld, 2>> tl, bl;
	for(array<array<ld, 2>, 2> ai : a) {
		if(ai[0][0]>ai[1][0]) {
			tl.push_back({(ai[1][1]-ai[0][1])/(ai[1][0]-ai[0][0])});
			tl.back()[1]=gy(ai[0], ai[1], 0);
		} else {
			ai[0][1]=-ai[0][1];
			ai[1][1]=-ai[1][1];
			bl.push_back({(ai[1][1]-ai[0][1])/(ai[1][0]-ai[0][0])});
			bl.back()[1]=gy(ai[0], ai[1], 0);
		}
	}
	vector<array<ld, 2>> tp=convexHull(tl, xl, xr), bp=convexHull(bl, xl, xr);
	for(array<ld, 2> &p : bp)
		p[1]=-p[1];
	vector<array<ld, 2>> tp2, bp2;
	int i1=0, i2=0;
	if(tp[0][1]<bp[0][1]) {
		i1=i2=1;
		while(i1<tp.size()&&i2<bp.size()) {
			if(tp[i1][0]<bp[i2][0]) {
				if(tp[i1][1]>gy(bp[i2-1], bp[i2], tp[i1][0])) {
					tp2.push_back(segmentIntersection(tp[i1-1], tp[i1], bp[i2-1], bp[i2]));
					break;
				}
				++i1;
			} else {
				if(bp[i2][1]<gy(tp[i1-1], tp[i1], bp[i2][0])) {
					tp2.push_back(segmentIntersection(tp[i1-1], tp[i1], bp[i2-1], bp[i2]));
					break;
				}
				++i2;
			}
		}
	}
	if(i1>=tp.size()||i2>=bp.size())
		return vector<array<ld, 2>>();
	if(tp.back()[1]<bp.back()[1]) {
		while(1) {
			if(tp[i1][0]<bp[i2][0]) {
				if(tp[i1][1]<gy(bp[i2-1], bp[i2], tp[i1][0])) {
					tp2.push_back(segmentIntersection(tp[i1-1], tp[i1], bp[i2-1], bp[i2]));
					break;
				}
				tp2.push_back(tp[i1++]);
			} else {
				if(bp[i2][1]>gy(tp[i1-1], tp[i1], bp[i2][0])) {
					tp2.push_back(segmentIntersection(tp[i1-1], tp[i1], bp[i2-1], bp[i2]));
					break;
				}
				bp2.push_back(bp[i2++]);
			}
		}
	} else {
		while(i1<tp.size())
			tp2.push_back(tp[i1++]);
		while(i2<bp.size())
			bp2.push_back(bp[i2++]);
	}
	reverse(tp2.begin(), tp2.end());
	tp2.insert(tp2.end(), bp2.begin(), bp2.end());
	return tp2;
}

bool chk(ld r) {
	vector<array<array<ld, 2>, 2>> a;
	ld xl=-1e8, xr=1e8;
	for(int i=0; i<n; ++i) {
		int j=(i+1)%n;
		if(x[i]==x[j]) {
			if(y[i]>y[j])
				xl=max(x[i]+r, xl);
			else
				xr=min(x[i]-r, xr);
		} else {
			ld sm=hypot(x[j]-x[i], y[j]-y[i]), tx=-(y[j]-y[i])*r/sm, ty=(x[j]-x[i])*r/sm;
			a.push_back({{{x[i]+tx, y[i]+ty}, {x[j]+tx, y[j]+ty}}});
		}
	}
	vector<array<ld, 2>> p=halfplaneIntersection(a, xl, xr);
	if(!p.size())
		return 0;
	for(int i1=0, i2=0; i1<p.size(); ++i1) {
		while(hypot(p[(i2+1)%p.size()][0]-p[i1][0], p[(i2+1)%p.size()][1]-p[i1][1])>hypot(p[i2][0]-p[i1][0], p[i2][1]-p[i1][1]))
			i2=(i2+1)%p.size();
		if(hypot(p[i2][0]-p[i1][0], p[i2][1]-p[i1][1])>2*r)
			return 1;
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for(int i=0; i<n; ++i)
		cin >> x[i] >> y[i];
	ld lb=0, rb=1e7;
	while(rb-lb>1e-4) {
		ld mb=(lb+rb)/2;
		if(chk(mb))
			lb=mb;
		else
			rb=mb;
	}
	cout << fixed << setprecision(3) << lb;
}
