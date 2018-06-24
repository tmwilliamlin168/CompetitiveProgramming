#include <bits/stdc++.h>
#include "lib1739.h"
using namespace std;

const int mxN=3e5;
int n, m, q, a[mxN];
vector<pair<int, int>> pos[mxN];

int main() {
	scanf("%d%d", &n, &m);
	for(int i=0; i<n; ++i)
		a[i]=i, pos[i].push_back({0, i+1});
	for(int i=1; i<=m; ++i) {
		int p;
		scanf("%d", &p);
		swap(a[p-1], a[p]);
		pos[a[p-1]].push_back({i, p}), pos[a[p]].push_back({i, p+1});
	}
	q=getNumQuestions();
	while(q--) {
		int k, j;
		getQuestion(k, j), --k;
		answer((--upper_bound(pos[k].begin(), pos[k].end(), make_pair(j, 696969)))->second);
	}
}
