/*
	- https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/IOI/official/2006/ioi06_points_sol.pdf
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=5e4;
int g, r, x[2*mxN], y[2*mxN];

bool cp(int o, int a, int b) {
	return (long long)(x[a]-x[o])*(y[b]-y[o])<(long long)(x[b]-x[o])*(y[a]-y[o]);
}

void ans(int a, int b) {
	if(a<g)
		cout << a+1 << " " << b+1 << " g\n";
	else
		cout << a-g+1 << " " << b-g+1 << " r\n";
}

void solve(int a1, int a2, int b, vector<int> &v) {
	int nb=-1;
	for(int vi : v)
		if((vi<g)==(b<g))
			nb=vi;
	if(nb==-1) {
		for(int vi : v)
			ans(a1, vi);
		return;
	}
	ans(b, nb);
	vector<int> nv[3];
	for(int vi : v)
		if(vi!=nb)
			nv[cp(nb, a1, a2)==cp(nb, a1, vi)&&cp(nb, a2, a1)==cp(nb, a2, vi)?2:cp(b, nb, a2)==cp(b, nb, vi)].push_back(vi);
	solve(b, nb, a1, nv[0]);
	solve(b, nb, a2, nv[1]);
	solve(a1, a2, nb, nv[2]);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> g;
	for(int i=0; i<g; ++i)
		cin >> x[i] >> y[i];
	cin >> r;
	for(int i=g; i<g+r; ++i)
		cin >> x[i] >> y[i];
	ans(0, 1);
	ans(g, g+1);
	vector<int> v[2];
	for(int i=2; i<g+r; ++i)
		if(i<g||i>g+1)
			v[x[i]>y[i]].push_back(i);
	random_shuffle(v[0].begin(), v[0].end());
	random_shuffle(v[1].begin(), v[1].end());
	solve(0, 1, g, v[0]);
	solve(g, g+1, 1, v[1]);
}
