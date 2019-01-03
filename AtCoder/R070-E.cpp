/*
	- Consider the function f(i, x) - minimum cost for the ith rectangle to have its left endpoint at x considering the first i rectangles
	- By adding a new rectangle
		- Split the original function in half and split both halves in opposite directions by the lengths of the rectangles
		- Now the function represents the minimum cost except for the cost of moving the last rectangle
		- Add |x-l[i]| to the function to add the cost of moving the last rectangle
	- We use slope trick (maintain the points where the function changes slope)
	- To efficiently perform the operations above, we will use 2 priority queues, one containing the left half of the function and the other containing the right half
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=1e5;
int n, l[mxN+1], r[mxN+1];
ll yi, ls, rs;
priority_queue<ll> lq;
priority_queue<ll, vector<ll>, greater<ll>> rq;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for(int i=1; i<=n; ++i)
		cin >> l[i] >> r[i];
	for(int i=1; i<=n; ++i) {
		ls+=r[i]-l[i];
		rs+=r[i-1]-l[i-1];
		ll lm=lq.size()?lq.top()-ls:LLONG_MIN, rm=rq.size()?rq.top()+rs:LLONG_MAX;
		if(lm<=l[i]&&l[i]<=rm) {
			lq.push(l[i]+ls);
			rq.push(l[i]-rs);
		} else if(lm>l[i]) {
			lq.pop();
			rq.push(lm-rs);
			lq.push(l[i]+ls);
			lq.push(l[i]+ls);
		} else {
			rq.pop();
			lq.push(rm+ls);
			rq.push(l[i]-rs);
			rq.push(l[i]-rs);
		}
		yi+=l[i]+ls;
	}
	lq.push(0);
	ll i=1, l=lq.top();
	while(lq.size()>1) {
		lq.pop();
		yi-=(l-lq.top())*i++;
		l=lq.top();
	}
	cout << yi;
}
