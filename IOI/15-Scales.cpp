#include "scales.h"
#include <bits/stdc++.h>
using namespace std;
 
int a[6];
vector<int> s;
vector<vector<int>> t, nxt;
 
int divide(vector<array<int, 6>> &v, int z) {
	int u=s.size();
	s.push_back(-1);
	t.push_back({});
	nxt.push_back({});
	if(v.empty())
		return u;
	if(z<2) {
		t[u]=vector<int>(v[0].begin(), v[0].end());
		return u;
	}
	nxt[u].resize(3);
	array<int, 6> a{0, 1, 2, 3, 4, 5};
	while(1) {
		random_shuffle(a.begin(), a.end());
		s[u]=rand()%4;
		vector<int> x(max(s[u]+1, 3));
		iota(x.begin(), x.end(), 0);
		t[u]=vector<int>(a.begin(), a.begin()+x.size());
		vector<array<int, 6>> b[3];
		for(array<int, 6> &p : v) {
			sort(x.begin(), x.end(), [&](const int &i, const int &j) {
				return p[a[i]]<p[a[j]];
			});
			b[s[u]<3?x[s[u]]:x[(find(x.begin(), x.end(), 3)-x.begin()+1)%4]].push_back(p);
		}
		if(max({b[0].size(), b[1].size(), b[2].size()})<=z/3) {
			for(int i=0; i<3; ++i)
				nxt[u][i]=divide(b[i], z/3);
			return u;
		}
	}
}
 
void init(int t) {
	srand(2);
	vector<array<int, 6>> v;
	array<int, 6> p{0, 1, 2, 3, 4, 5};
	do {
		if(p[0]<p[1]&&p[0]<p[2]&&(p[3]<p[4])!=(p[3]<p[5]))
			v.push_back(p);
	} while(next_permutation(p.begin(), p.end()));
	divide(v, 81);
}
 
int qry(int s, vector<int> t) {
	for(int &b : t)
		b=a[b];
	int x;
	if(s==0)
		x=getLightest(t[0], t[1], t[2]);
	else if(s==1)
		x=getMedian(t[0], t[1], t[2]);
	else if(s==2)
		x=getHeaviest(t[0], t[1], t[2]);
	else
		x=getNextLightest(t[0], t[1], t[2], t[3]);
	return find(t.begin(), t.end(), x)-t.begin();
}
 
void orderCoins() {
	iota(a, a+6, 1);
	swap(a[0], a[getLightest(1, 2, 3)-1]);
	swap(a[3], a[getMedian(4, 5, 6)-1]);
	int W[6], u=0;
	for(; ~s[u]; u=nxt[u][qry(s[u], t[u])]);
	for(int i=0; i<6; ++i)
		W[t[u][i]]=a[i];
	answer(W);
}
