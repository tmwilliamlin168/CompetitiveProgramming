#include "cross.h"
#include <bits/stdc++.h>
using namespace std;

array<int, 2> a[200000];

long long SelectCross(int k, vector<int> x, vector<int> y) {
	long long ans=0;
	for(int i=0; i<x.size(); ++i)
		a[i]={x[i], y[i]};
	sort(a, a+x.size(), greater<>());
	priority_queue<int, vector<int>, greater<int>> pq;
	for(int i=0; i<k-1; ++i)
		pq.push(a[i][1]);
	for(int i=k-1; i<x.size(); ++i) {
		pq.push(a[i][1]);
		ans=max((long long)a[i][0]*(2*pq.top()-a[i][0]), ans);
		pq.pop();
	}
	return ans;
}
