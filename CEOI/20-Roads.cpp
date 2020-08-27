#include <bits/stdc++.h>
using namespace std;

#define ar array

const int mxN=1e5;
int n, xa[mxN+1], ya[mxN+1], xb[mxN+1], yb[mxN+1];
ar<int, 2> e[2*mxN], l[mxN+1];

struct cmp {
	bool c(int i, int j) {
		return xa[i]<xb[i]?(long long)(xa[j]-xa[i])*(yb[i]-ya[i])<(long long)(ya[j]-ya[i])*(xb[i]-xa[i]):ya[i]<ya[j];
	}
	bool operator()(const int &i, const int &j) {
		return xa[i]>xa[j]?!c(j, i):c(i, j);
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=0; i<n; ++i) {
		cin >> xa[i] >> ya[i] >> xb[i] >> yb[i];
		if(make_pair(xa[i], ya[i])>make_pair(xb[i], yb[i])) {
			swap(xa[i], xb[i]);
			swap(ya[i], yb[i]);
		}
		e[2*i]={i};
		e[2*i+1]={i, 1};
	}
	xa[n]=ya[n]=yb[n]=-1e8;
	xb[n]=1e8;
	sort(e, e+2*n, [](const ar<int, 2> &a, const ar<int, 2> &b) {
		return make_tuple(a[1]?xb[a[0]]:xa[a[0]], a[1], ya[a[0]])<make_tuple(b[1]?xb[b[0]]:xa[b[0]], b[1], ya[b[0]]);
	});
	set<int, cmp> s{n};
	for(int i=0; i<2*n; ++i) {
		if(e[i][1]) {
			auto it=--s.erase(s.find(e[i][0]));
			l[*it]={xb[e[i][0]], yb[e[i][0]]};
		} else {
			auto it=--s.lower_bound(e[i][0]);
			if(i) {
				ar<int, 2> ans=xa[e[i][0]]<xb[e[i][0]]||l[*it][0]<xa[e[i][0]]||l[*it][1]<ya[e[i][0]]?ar<int, 2>{xa[e[i][0]], ya[e[i][0]]}:ar<int, 2>{xb[e[i][0]], yb[e[i][0]]};
				cout << l[*it][0] << " " << l[*it][1] << " " << ans[0] << " " << ans[1] << "\n";
			}
			l[*it]={xa[e[i][0]], ya[e[i][0]]};
			l[e[i][0]]=xa[e[i][0]]<xb[e[i][0]]?ar<int, 2>{xa[e[i][0]], ya[e[i][0]]}:ar<int, 2>{xb[e[i][0]], yb[e[i][0]]};
			s.insert(e[i][0]);
		}
	}
}
