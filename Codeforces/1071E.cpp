#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5;
int n, w, h, s1, s2, t[mxN], x[mxN], y[mxN];
double lb, rb=1000, mb, a[8], b[8];

struct ev {
	int t;
	double y1, y2, nl, nr;
};
vector<ev> es;

bool chk(double mb) {
	int ct=0;
	double x1=s1, y1=s2, x2=s1, y2=s2;
	auto o=[&](double x1, double y1, double x2, double y2, double x3, double y3) {
		return (x1-x2)*(y2-y3)<(x2-x3)*(y1-y2);
	};
	for(ev e : es) {
		double ax=(e.t-ct)*mb, ay=(e.t-ct)*mb, nl=2, nr=-1;
		for(int j=0; j<4; swap(ax, ay), ax=-ax, ++j) {
			a[j]=x1+ax;
			b[j]=y1+ay;
			a[j+4]=x2+ax;
			b[j+4]=y2+ay;
		}
		auto ab=[&](int j1, int j2) {
			if(o(0, e.y1, w, e.y2, a[j1], b[j1])==o(0, e.y1, w, e.y2, a[j2], b[j2]))
				return;
			double c=(b[j1]*a[j2]-a[j1]*b[j2]+e.y1*(a[j1]-a[j2]))/((e.y2-e.y1)*(a[j2]-a[j1])/w-b[j2]+b[j1])/w;
			nl=min(c, nl);
			nr=max(c, nr);
		};
		for(int j=0; j<4; ++j) {
			ab(j, (j+1)%4);
			ab(j+4, (j+1)%4+4);
			ab(j, j+4);
		}
		nl=max(e.nl, nl);
		nr=min(e.nr, nr);
		if(nl>nr+1e-9)
			return 0;
		x1=w*nl;
		y1=e.y2*nl+e.y1*(1-nl);
		x2=w*nr;
		y2=e.y2*nr+e.y1*(1-nr);
		ct=e.t;
	}
	return 1;
}

void fk() {
	cout << -1;
	exit(0);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> w >> h >> s1 >> s2;
	for(int i=0; i<n; ++i)
		cin >> t[i] >> x[i] >> y[i];
	for(int i=0; i<n; ) {
		vector<array<int, 2>> ps{{x[i], y[i]}};
		while(++i<n&&t[i]==t[i-1])
			ps.push_back({x[i], y[i]});
		sort(ps.begin(), ps.end());
		ps.resize(unique(ps.begin(), ps.end())-ps.begin());
		for(int j=ps.size()-1; j>1; --j)
			if((ps[j][0]-ps[j-1][0])*(ps[j-1][1]-ps[j-2][1])!=(ps[j-1][0]-ps[j-2][0])*(ps[j][1]-ps[j-1][1]))
				fk();
		es.push_back({t[i-1], (double)h*ps[0][0]/ps[0][1], (double)(h*ps[0][0]-w*(h-ps[0][1]))/ps[0][1], max((double)(h*ps[0][0]-w*ps[0][1])/(h-ps[0][1])/w, 0.0), min((double)h*ps[0][0]/(h-ps[0][1])/w, 1.0)});
		if(ps.size()>1) {
			if(ps[0][1]==ps[1][1])
				fk();
			double a=(double)(ps[0][0]*ps[1][1]-ps[1][0]*ps[0][1])/(ps[1][1]-ps[0][1])/w;
			es.back().nl=max(a, es.back().nl);
			es.back().nr=min(a, es.back().nr);
			if(es.back().nl>es.back().nr+1e-9)
				fk();
			++i;
		}
	}
	while(1) {
		unsigned long long lb2, rb2, mb2;
		memcpy(&lb2, &lb, 8);
		memcpy(&rb2, &rb, 8);
		if(rb2-lb2<=1ll<<41)
			break;
		mb2=(lb2+rb2)/2;
		memcpy(&mb, &mb2, 8);
		if(chk(mb))
			rb=mb;
		else
			lb=mb;
	}
	cout << fixed << setprecision(9) << (lb+rb)/2;
}
